#include <gvk.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>
#ifdef _WIN32
  #define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3native.h>   // for glfwGetWin32Window
#include <imgui_internal.h>

namespace gvk
{
	void imgui_manager::initialize()
	{
		LOG_DEBUG_VERBOSE("Setting up IMGUI...");

		// Get the main window's handle:
		auto* wnd = gvk::context().main_window();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		//ImGui::StyleColorsDark();
		ImGui::StyleColorsClassic();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForVulkan(wnd->handle()->mHandle, true); // TODO: Don't install callbacks (get rid of them during 'fixed/varying-input Umstellung DOUBLECHECK')

		ImGui_ImplVulkan_InitInfo init_info = {};
	    init_info.Instance = context().vulkan_instance();
	    init_info.PhysicalDevice = context().physical_device();
	    init_info.Device = context().device();
		assert(mQueue);
	    init_info.QueueFamily = mQueue->family_index();
	    init_info.Queue = mQueue->handle();
	    init_info.PipelineCache = nullptr; // TODO: Maybe use a pipeline cache?

		// This factor is set to 1000 in the imgui example code but after looking through the vulkan backend code, we never
		// allocate more than one descriptor set, therefore setting this to 1 should be sufficient.
		const uint32_t magicImguiFactor = 1;
		auto allocRequest = avk::descriptor_alloc_request{};
		allocRequest.add_size_requirements(vk::DescriptorPoolSize{vk::DescriptorType::eSampler,				 magicImguiFactor});
		allocRequest.add_size_requirements(vk::DescriptorPoolSize{vk::DescriptorType::eCombinedImageSampler, std::max(magicImguiFactor, 32u)}); // User could alloc several of these via imgui_manager::get_or_create_texture_descriptor
		allocRequest.add_size_requirements(vk::DescriptorPoolSize{vk::DescriptorType::eSampledImage,		 magicImguiFactor});
		allocRequest.add_size_requirements(vk::DescriptorPoolSize{vk::DescriptorType::eStorageImage,		 magicImguiFactor});
		allocRequest.add_size_requirements(vk::DescriptorPoolSize{vk::DescriptorType::eUniformTexelBuffer,	 magicImguiFactor});
		allocRequest.add_size_requirements(vk::DescriptorPoolSize{vk::DescriptorType::eStorageTexelBuffer,	 magicImguiFactor});
		allocRequest.add_size_requirements(vk::DescriptorPoolSize{vk::DescriptorType::eUniformBuffer,		 magicImguiFactor});
		allocRequest.add_size_requirements(vk::DescriptorPoolSize{vk::DescriptorType::eStorageBuffer,		 magicImguiFactor});
		allocRequest.add_size_requirements(vk::DescriptorPoolSize{vk::DescriptorType::eUniformBufferDynamic, magicImguiFactor}); // TODO: Q1: Is this really required? Q2: Why is the type not abstracted through cgb::binding?
		allocRequest.add_size_requirements(vk::DescriptorPoolSize{vk::DescriptorType::eStorageBufferDynamic, magicImguiFactor}); // TODO: Q1: Is this really required? Q2: Why is the type not abstracted through cgb::binding?
		allocRequest.add_size_requirements(vk::DescriptorPoolSize{vk::DescriptorType::eInputAttachment,		 magicImguiFactor});
		allocRequest.set_num_sets(static_cast<uint32_t>(allocRequest.accumulated_pool_sizes().size() * magicImguiFactor));
		mDescriptorPool = gvk::context().create_descriptor_pool(allocRequest.accumulated_pool_sizes(), allocRequest.num_sets());;

		// DescriptorSet chache for user textures
		mImTextureDescriptorCache = gvk::context().create_descriptor_cache("imgui_manager's texture descriptor cache");

	    init_info.DescriptorPool = mDescriptorPool.handle();
	    init_info.Allocator = nullptr; // TODO: Maybe use an allocator?

		mCommandPool = &gvk::context().get_command_pool_for_resettable_command_buffers(*mQueue).get(); // TODO: Support other queues!
		mCommandBuffers = mCommandPool->alloc_command_buffers(static_cast<uint32_t>(wnd->number_of_frames_in_flight()));
		for (gvk::window::frame_id_t i = 0; i < wnd->number_of_frames_in_flight(); ++i) {
			mRenderFinishedSemaphores.push_back(gvk::context().create_semaphore());
			mRenderFinishedSemaphores.back().enable_shared_ownership();
		}

		// MinImageCount and ImageCount are related to the swapchain images. These are not Dear ImGui specific properties and your
		// engine should expose them. ImageCount lets Dear ImGui know how many framebuffers and resources in general it should
		// allocate. MinImageCount is not actually used even though there is a check at init time that its value is greater than 1.
		// Source: https://frguthmann.github.io/posts/vulkan_imgui/
		// ImGui has a hard-coded floor for MinImageCount which is 2.
		// Take the max of min image count supported by the phys. device and imgui:
		auto surfaceCap = gvk::context().physical_device().getSurfaceCapabilitiesKHR(wnd->surface());
	    init_info.MinImageCount = std::max(2u, surfaceCap.minImageCount);
	    init_info.ImageCount = std::max(init_info.MinImageCount, std::max(static_cast<uint32_t>(wnd->get_config_number_of_concurrent_frames()), wnd->get_config_number_of_presentable_images()));
	    init_info.CheckVkResultFn = gvk::context().check_vk_result;

		// copy current state of init_info in for later use
		// this shenanigans is necessary for ImGui to keep functioning when certain rendering properties (renderpass) are changed (and to give it new image count)
		auto restartImGui = [this, wnd, init_info]() {
			ImGui_ImplVulkan_Shutdown(); // shut imgui down and restart with base init_info
			ImGui_ImplVulkan_InitInfo new_init_info = init_info; // can't be temp
			mDescriptorPool.reset();
			new_init_info.ImageCount = std::max(init_info.MinImageCount, std::max(static_cast<uint32_t>(wnd->get_config_number_of_concurrent_frames()), wnd->get_config_number_of_presentable_images())); // opportunity to update image count
			ImGui_ImplVulkan_Init(&new_init_info, this->mRenderpass->handle()); // restart imgui
			// Have to upload fonts just like the first time:
			upload_fonts();

			// Re-create all the command buffers because the number of concurrent frames could have changed:
			mCommandBuffers = mCommandPool->alloc_command_buffers(static_cast<uint32_t>(wnd->number_of_frames_in_flight()));

			// Re-create all the semaphores because the number of concurrent frames could have changed:
			mRenderFinishedSemaphores.clear();
			for (gvk::window::frame_id_t i = 0; i < wnd->number_of_frames_in_flight(); ++i) {
				mRenderFinishedSemaphores.push_back(gvk::context().create_semaphore());
				mRenderFinishedSemaphores.back().enable_shared_ownership();
			}
		};

		// set up an updater
		mUpdater.emplace();
		if (!mRenderpass.has_value()) { // Not specified in the constructor => create a default one
			construct_render_pass();

			mUpdater->on(gvk::swapchain_format_changed_event(wnd),
						 gvk::swapchain_additional_attachments_changed_event(wnd)
			).invoke([this, restartImGui]() {
				ImGui::EndFrame(); //end previous (not rendered) frame
				construct_render_pass(); // reconstruct render pass
				restartImGui();
				ImGui::NewFrame(); // got to start a new frame since ImGui::Render is next
			});
		}
		mUpdater->on(gvk::concurrent_frames_count_changed_event(wnd)).invoke([restartImGui]() {
			ImGui::EndFrame(); //end previous (not rendered) frame
			restartImGui();
			ImGui::NewFrame(); // got to start a new frame since ImGui::Render is next
		});

		// Init it:
	    ImGui_ImplVulkan_Init(&init_info, mRenderpass->handle());

		// Setup back-end capabilities flags
	    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
	    //io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
	    io.BackendPlatformName = "imgui_impl_glfw";

	    //io.SetClipboardTextFn = ImGui_ImplGlfw_SetClipboardText; // TODO clipboard abstraction via cgb::input()
	    //io.GetClipboardTextFn = ImGui_ImplGlfw_GetClipboardText;
	    //io.ClipboardUserData = g_Window;

#if defined(_WIN32)
		gvk::context().dispatch_to_main_thread([](){
		    ImGui::GetMainViewport()->PlatformHandleRaw = (void*)glfwGetWin32Window(gvk::context().main_window()->handle()->mHandle);
		});
#endif

		// Upload fonts:
		upload_fonts();
	}

	void imgui_manager::update()
	{
		ImGuiIO& io = ImGui::GetIO();
		IM_ASSERT(io.Fonts->IsBuilt() && "Font atlas not built! It is generally built by the renderer back-end. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");
		auto wndSize = gvk::context().main_window()->resolution(); // TODO: What about multiple windows?
		io.DisplaySize = ImVec2((float)wndSize.x, (float)wndSize.y);
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f); // TODO: If the framebuffer has a different resolution as the window
	    io.DeltaTime = gvk::time().delta_time();

		if (mUserInteractionEnabled) {
			// Cursor position:
			const auto cursorPos = input().cursor_position();
			io.AddMousePosEvent(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));

			// Mouse buttons:
			for (int button = 0; button < 5; ++button) {
				io.AddMouseButtonEvent(button, input().mouse_button_down(button));
			}

			// Scroll position:
			io.AddMouseWheelEvent(static_cast<float>(input().scroll_delta().x),
								  static_cast<float>(input().scroll_delta().y));

			// Mouse cursor:
			if (!input().is_cursor_disabled()) {
				const auto mouseCursorCurValue = ImGui::GetMouseCursor();
				if (static_cast<int>(mouseCursorCurValue) != mMouseCursorPreviousValue) {
					switch (mouseCursorCurValue) {
					case ImGuiMouseCursor_None:
						input().set_cursor_mode(cursor::cursor_hidden);
						break;
					case ImGuiMouseCursor_Arrow:
						input().set_cursor_mode(cursor::arrow_cursor);
						break;
					case ImGuiMouseCursor_TextInput:
						input().set_cursor_mode(cursor::ibeam_cursor);
						break;
					case ImGuiMouseCursor_ResizeAll:
						input().set_cursor_mode(cursor::arrow_cursor);
						break;
					case ImGuiMouseCursor_ResizeNS:
						input().set_cursor_mode(cursor::vertical_resize_cursor);
						break;
					case ImGuiMouseCursor_ResizeEW:
						input().set_cursor_mode(cursor::horizontal_resize_cursor);
						break;
					case ImGuiMouseCursor_ResizeNESW:
						input().set_cursor_mode(cursor::arrow_cursor);
						break;
					case ImGuiMouseCursor_ResizeNWSE:
						input().set_cursor_mode(cursor::arrow_cursor);
						break;
					case ImGuiMouseCursor_Hand:
						input().set_cursor_mode(cursor::hand_cursor);
						break;
					case ImGuiMouseCursor_NotAllowed:
						input().set_cursor_mode(cursor::arrow_cursor);
						break;
					default:
						input().set_cursor_mode(cursor::arrow_cursor);
						break;
					}
					mMouseCursorPreviousValue = static_cast<int>(mouseCursorCurValue);
				}
			}

			// Update keys:
			io.AddKeyEvent(ImGuiKey_Tab, input().key_down(key_code::tab));
			io.AddKeyEvent(ImGuiKey_LeftArrow, input().key_down(key_code::left));
			io.AddKeyEvent(ImGuiKey_RightArrow, input().key_down(key_code::right));
			io.AddKeyEvent(ImGuiKey_UpArrow, input().key_down(key_code::up));
			io.AddKeyEvent(ImGuiKey_DownArrow, input().key_down(key_code::down));
			io.AddKeyEvent(ImGuiKey_PageUp, input().key_down(key_code::page_up));
			io.AddKeyEvent(ImGuiKey_PageDown, input().key_down(key_code::page_down));
			io.AddKeyEvent(ImGuiKey_Home, input().key_down(key_code::home));
			io.AddKeyEvent(ImGuiKey_End, input().key_down(key_code::end));
			io.AddKeyEvent(ImGuiKey_Insert, input().key_down(key_code::insert));
			io.AddKeyEvent(ImGuiKey_Delete, input().key_down(key_code::del));
			io.AddKeyEvent(ImGuiKey_Backspace, input().key_down(key_code::backspace));
			io.AddKeyEvent(ImGuiKey_Space, input().key_down(key_code::space));
			io.AddKeyEvent(ImGuiKey_Enter, input().key_down(key_code::enter));
			io.AddKeyEvent(ImGuiKey_Escape, input().key_down(key_code::escape));
			io.AddKeyEvent(ImGuiKey_KeypadEnter, input().key_down(key_code::numpad_enter));
			io.AddKeyEvent(ImGuiKey_A, input().key_down(key_code::a));
			io.AddKeyEvent(ImGuiKey_C, input().key_down(key_code::c));
			io.AddKeyEvent(ImGuiKey_V, input().key_down(key_code::v));
			io.AddKeyEvent(ImGuiKey_X, input().key_down(key_code::x));
			io.AddKeyEvent(ImGuiKey_Y, input().key_down(key_code::y));
			io.AddKeyEvent(ImGuiKey_Z, input().key_down(key_code::z));

			// Modifiers are not reliable across systems
			bool ctrl = input().key_down(key_code::left_control) || input().key_down(key_code::right_control);
			bool shift = input().key_down(key_code::left_shift) || input().key_down(key_code::right_shift);
			bool alt = input().key_down(key_code::left_alt) || input().key_down(key_code::right_alt);
			bool super = input().key_down(key_code::left_super) || input().key_down(key_code::right_super);
			ImGuiKeyModFlags mods = (ctrl ? ImGuiKeyModFlags_Ctrl : 0) | (shift ? ImGuiKeyModFlags_Shift : 0) | (alt ? ImGuiKeyModFlags_Alt : 0) | (super ? ImGuiKeyModFlags_Super : 0);
			io.AddKeyModsEvent(mods);


			// Characters:
			for (auto c : input().entered_characters()) {
				io.AddInputCharacter(c);
			}
			// Update gamepads:
			memset(io.NavInputs, 0, sizeof(io.NavInputs));
			if ((io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad) == ImGuiConfigFlags_NavEnableGamepad) {
				// TODO: Need abstraction for glfwGetJoystickButtons in cgb::input() for this to work properly
				//// Update gamepad inputs
				//#define MAP_BUTTON(NAV_NO, BUTTON_NO)       { if (buttons_count > BUTTON_NO && buttons[BUTTON_NO] == GLFW_PRESS) io.NavInputs[NAV_NO] = 1.0f; }
				//#define MAP_ANALOG(NAV_NO, AXIS_NO, V0, V1) { float v = (axes_count > AXIS_NO) ? axes[AXIS_NO] : V0; v = (v - V0) / (V1 - V0); if (v > 1.0f) v = 1.0f; if (io.NavInputs[NAV_NO] < v) io.NavInputs[NAV_NO] = v; }
				//int axes_count = 0, buttons_count = 0;
				//const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
				//const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttons_count);
				//MAP_BUTTON(ImGuiNavInput_Activate,   0);     // Cross / A
				//MAP_BUTTON(ImGuiNavInput_Cancel,     1);     // Circle / B
				//MAP_BUTTON(ImGuiNavInput_Menu,       2);     // Square / X
				//MAP_BUTTON(ImGuiNavInput_Input,      3);     // Triangle / Y
				//MAP_BUTTON(ImGuiNavInput_DpadLeft,   13);    // D-Pad Left
				//MAP_BUTTON(ImGuiNavInput_DpadRight,  11);    // D-Pad Right
				//MAP_BUTTON(ImGuiNavInput_DpadUp,     10);    // D-Pad Up
				//MAP_BUTTON(ImGuiNavInput_DpadDown,   12);    // D-Pad Down
				//MAP_BUTTON(ImGuiNavInput_FocusPrev,  4);     // L1 / LB
				//MAP_BUTTON(ImGuiNavInput_FocusNext,  5);     // R1 / RB
				//MAP_BUTTON(ImGuiNavInput_TweakSlow,  4);     // L1 / LB
				//MAP_BUTTON(ImGuiNavInput_TweakFast,  5);     // R1 / RB
				//MAP_ANALOG(ImGuiNavInput_LStickLeft, 0,  -0.3f,  -0.9f);
				//MAP_ANALOG(ImGuiNavInput_LStickRight,0,  +0.3f,  +0.9f);
				//MAP_ANALOG(ImGuiNavInput_LStickUp,   1,  +0.3f,  +0.9f);
				//MAP_ANALOG(ImGuiNavInput_LStickDown, 1,  -0.3f,  -0.9f);
				//#undef MAP_BUTTON
				//#undef MAP_ANALOG
				//if (axes_count > 0 && buttons_count > 0)
				//    io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
				//else
				//    io.BackendFlags &= ~ImGuiBackendFlags_HasGamepad;
			}
		}
		// start of new frame and callback invocations have to be in the update() call of the invokee,
		// ... to give the updater an opportunity to clean up (callbacks themselves may cause update events)
		mAlreadyRendered = false;
		ImGui_ImplVulkan_NewFrame();
		ImGui::NewFrame();
	}

	void imgui_manager::render_into_command_buffer(avk::resource_reference<avk::command_buffer_t> aCommandBuffer)
	{
		for (auto& cb : mCallback) {
			cb();
		}

		auto& cmdBfr = aCommandBuffer.get();

		auto mainWnd = gvk::context().main_window(); // TODO: ImGui shall not only support main_mindow, but all windows!

		// if no invokee has written on the attachment (no previous render calls this frame),
		// reset layout (cannot be "store_in_presentable_format").
		if (!mainWnd->has_consumed_current_image_available_semaphore()) {
			cmdBfr.begin_render_pass_for_framebuffer(const_referenced(mClearRenderpass), referenced(mainWnd->current_backbuffer()));
			cmdBfr.end_render_pass();
		}

		assert(mRenderpass.has_value());
		cmdBfr.begin_render_pass_for_framebuffer(const_referenced(mRenderpass), referenced(mainWnd->current_backbuffer()));

		ImGui::Render();
		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cmdBfr.handle());

		cmdBfr.end_render_pass();



		mAlreadyRendered = true;
	}

	void imgui_manager::render()
	{
		if (mAlreadyRendered) {
			return;
		}
		
		auto mainWnd = gvk::context().main_window(); // TODO: ImGui shall not only support main_mindow, but all windows!
		const auto ifi = mainWnd->current_in_flight_index();
		auto& cmdBfr = mCommandBuffers[ifi];

		cmdBfr->reset();

		cmdBfr->begin_recording();
		render_into_command_buffer(cmdBfr);
		cmdBfr->end_recording();

		auto submission = mQueue->submit(avk::referenced(cmdBfr))
			.signaling_upon_completion(avk::stage::color_attachment_output >> mRenderFinishedSemaphores[ifi])
			.store_for_now();

		// If this is the first render call (other invokees are disabled or only ImGui renders),
		// then consume imageAvailableSemaphore.
		if (!mainWnd->has_consumed_current_image_available_semaphore()) {
			submission
				.waiting_for(mainWnd->consume_current_image_available_semaphore() >> avk::stage::color_attachment_output);
		}

		// This is usually the last call, so someone needs to use the fence:
		// TODO: How to check if we have another invokee after this one?!
		if (!mainWnd->has_used_current_frame_finished_fence()) {
			submission
				.signaling_upon_completion(mainWnd->use_current_frame_finished_fence());
		}

		submission.submit();

		//                        As far as ImGui is concerned, the next frame using the same target image must wait before color attachment output:
		mainWnd->add_present_dependency_for_current_frame(avk::shared(mRenderFinishedSemaphores[ifi]));

		// Just let submission go out of scope => will submit in destructor, that's fine.
	}

	void imgui_manager::finalize()
	{
		ImGui_ImplVulkan_Shutdown();
	    ImGui_ImplGlfw_Shutdown();
	    ImGui::DestroyContext();
	}

	void imgui_manager::enable_user_interaction(bool aEnableOrNot)
	{
		mUserInteractionEnabled = aEnableOrNot;
	}

	void imgui_manager::upload_fonts()
	{
		auto cmdBfr = gvk::context().get_command_pool_for_single_use_command_buffers(*mQueue)->alloc_command_buffer(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
		cmdBfr->begin_recording();
		ImGui_ImplVulkan_CreateFontsTexture(cmdBfr->handle());
		cmdBfr->end_recording();
		cmdBfr->set_custom_deleter([]() { ImGui_ImplVulkan_DestroyFontUploadObjects(); });

		if (mUsingSemaphoreInsteadOfFenceForFontUpload) {
			auto semaphore = gvk::context().create_semaphore();
			mQueue->submit(cmdBfr)
				.signaling_upon_completion(avk::stage::transfer >> semaphore);

			// The following is not totally correct, i.e., living on the edge:
			auto* mainWnd = gvk::context().main_window();
			mainWnd->add_present_dependency_for_current_frame(avk::owned(semaphore));
		}
		else {
			auto fen = gvk::context().create_fence();
			mQueue->submit(cmdBfr)
				.signaling_upon_completion(fen);

			// This is totally correct, but incurs a fence wait:
			fen->wait_until_signalled();
		}
	}

	void imgui_manager::construct_render_pass()
	{
		using namespace avk;

		auto* wnd = gvk::context().main_window();
		std::vector<attachment> attachments;
		attachments.push_back(attachment::declare(format_from_window_color_buffer(wnd), on_load::load(), color(0), on_store::store().in_layout(image_layout::present_src)));
		for (auto a : wnd->get_additional_back_buffer_attachments()) {
			// Well... who would have guessed the following (and, who understands??):
			//
			// Load and store operations often cause synchronization errors
			//  - LOAD_OP_DONT_CARE generates WRITE accesses to your attachments
			//
			// I mean... yeah! Sure... :|
			// Source: https://www.lunarg.com/wp-content/uploads/2021/08/Vulkan-Synchronization-SIGGRAPH-2021.pdf
			//
			// Therefore ...
			// 
			a.mLoadOperation = on_load::dont_care();
			a.mStoreOperation = on_store::dont_care();
			attachments.push_back(a);
		}
		auto newRenderpass = context().create_renderpass(
			attachments,
			{
				subpass_dependency(
					subpass::external >> subpass::index(0),
					// ... we have to synchronize all these stages with color+dept_stencil write access:
					stage::color_attachment_output | stage::early_fragment_tests | stage::late_fragment_tests  >>  stage::color_attachment_output | stage::early_fragment_tests | stage::late_fragment_tests,
					access::color_attachment_write | access::depth_stencil_attachment_write                    >>  access::color_attachment_read | access::depth_stencil_attachment_write
				),
				subpass_dependency(
					subpass::index(0) >> subpass::external,
					stage::color_attachment_output   >>   stage::none, // assume semaphore afterwards
					access::color_attachment_write   >>   access::none
				)
			}
		);

		// setup render pass for the case where the invokee does not write anything on the backbuffer (and clean it)
		attachments[0] = avk::attachment::declare(format_from_window_color_buffer(wnd), avk::on_load::clear(), avk::color(0), avk::on_store::store());
		auto newClearRenderpass = context().create_renderpass(
			attachments
			//, {
			//	subpass_dependency(
			//		subpass::external >> subpass::index(0),
			//		stage::color_attachment_output >> stage::color_attachment_output,
			//		access::color_attachment_write >> access::color_attachment_read
			//	),
			//	subpass_dependency(
			//		subpass::index(0) >> subpass::external,
			//		stage::color_attachment_output >> stage::none, // assume semaphore afterwards
			//		access::color_attachment_write >> access::none
			//	)
			//}
		);

		auto lifetimeHandlerLambda = [wnd](avk::renderpass&& rp) { wnd->handle_lifetime(std::move(rp)); };
		avk::assign_and_lifetime_handle_previous(mRenderpass, std::move(newRenderpass), lifetimeHandlerLambda);
		avk::assign_and_lifetime_handle_previous(mClearRenderpass, std::move(newClearRenderpass), lifetimeHandlerLambda);
	}

	ImTextureID imgui_manager::get_or_create_texture_descriptor(avk::resource_reference<avk::image_sampler_t> aImageSampler, avk::image_layout::image_layout aImageLayout)
	{
		std::vector<avk::descriptor_set> sets = mImTextureDescriptorCache.get_or_create_descriptor_sets({
			avk::descriptor_binding(0, 0, aImageSampler->as_combined_image_sampler(aImageLayout), avk::shader_type::fragment)
		});

		// The vector should never contain more than 1 DescriptorSet for the provided image_sampler
		assert(sets.size() == 1);

		// Return the first DescriptorSet as ImTextureID
		return (ImTextureID)sets[0].handle();
	}
}
