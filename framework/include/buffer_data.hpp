#pragma once

namespace cgb
{
	/** Get a `buffer_member_format` instance, describing a record of [fp16, fp16, fp16, fp16]. */
	buffer_member_format format_4x_fp16();
	/** Get a `buffer_member_format` instance, describing a record of [fp16, fp16, fp16]. */
	buffer_member_format format_3x_fp16();
	/** Get a `buffer_member_format` instance, describing a record of [fp16, fp16]. */
	buffer_member_format format_2x_fp16();
	/** Get a `buffer_member_format` instance, describing a record of [fp16]. */
	buffer_member_format format_1x_fp16();
	/** Get a `buffer_member_format` instance, describing a record of [fp32, fp32, fp32, fp32]. */
	buffer_member_format format_4x_fp32();
	/** Get a `buffer_member_format` instance, describing a record of [fp32, fp32, fp32]. */
	buffer_member_format format_3x_fp32();
	/** Get a `buffer_member_format` instance, describing a record of [fp32, fp32]. */
	buffer_member_format format_2x_fp32();
	/** Get a `buffer_member_format` instance, describing a record of [fp32]. */
	buffer_member_format format_1x_fp32();
	/** Get a `buffer_member_format` instance, describing a record of [fp64, fp64, fp64, fp64]. */
	buffer_member_format format_4x_fp64();
	/** Get a `buffer_member_format` instance, describing a record of [fp64, fp64, fp64]. */
	buffer_member_format format_3x_fp64();
	/** Get a `buffer_member_format` instance, describing a record of [fp64, fp64]. */
	buffer_member_format format_2x_fp64();
	/** Get a `buffer_member_format` instance, describing a record of [fp64]. */
	buffer_member_format format_1x_fp64();
	/** Get a `buffer_member_format` instance, describing a record of [int8, int8, int8, int8]. */
	buffer_member_format format_4x_sint8();
	/** Get a `buffer_member_format` instance, describing a record of [int8, int8, int8]. */
	buffer_member_format format_3x_sint8();
	/** Get a `buffer_member_format` instance, describing a record of [int8, int8]. */
	buffer_member_format format_2x_sint8();
	/** Get a `buffer_member_format` instance, describing a record of [int8]. */
	buffer_member_format format_1x_sint8();
	/** Get a `buffer_member_format` instance, describing a record of [int16, int16, int16, int16]. */
	buffer_member_format format_4x_sint16();
	/** Get a `buffer_member_format` instance, describing a record of [int16, int16, int16]. */
	buffer_member_format format_3x_sint16();
	/** Get a `buffer_member_format` instance, describing a record of [int16, int16]. */
	buffer_member_format format_2x_sint16();
	/** Get a `buffer_member_format` instance, describing a record of [int16]. */
	buffer_member_format format_1x_sint16();
	/** Get a `buffer_member_format` instance, describing a record of [int32, int32, int32, int32]. */
	buffer_member_format format_4x_sint32();
	/** Get a `buffer_member_format` instance, describing a record of [int32, int32, int32]. */
	buffer_member_format format_3x_sint32();
	/** Get a `buffer_member_format` instance, describing a record of [int32, int32]. */
	buffer_member_format format_2x_sint32();
	/** Get a `buffer_member_format` instance, describing a record of [int32]. */
	buffer_member_format format_1x_sint32();
	/** Get a `buffer_member_format` instance, describing a record of [int64, int64, int64, int64]. */
	buffer_member_format format_4x_sint64();
	/** Get a `buffer_member_format` instance, describing a record of [int64, int64, int64]. */
	buffer_member_format format_3x_sint64();
	/** Get a `buffer_member_format` instance, describing a record of [int64, int64]. */
	buffer_member_format format_2x_sint64();
	/** Get a `buffer_member_format` instance, describing a record of [int64]. */
	buffer_member_format format_1x_sint64();
	/** Get a `buffer_member_format` instance, describing a record of [uint8, uint8, uint8, uint8]. */
	buffer_member_format format_4x_uint8();
	/** Get a `buffer_member_format` instance, describing a record of [uint8, uint8, uint8]. */
	buffer_member_format format_3x_uint8();
	/** Get a `buffer_member_format` instance, describing a record of [uint8, uint8]. */
	buffer_member_format format_2x_uint8();
	/** Get a `buffer_member_format` instance, describing a record of [uint8]. */
	buffer_member_format format_1x_uint8();
	/** Get a `buffer_member_format` instance, describing a record of [uint16, uint16, uint16, uint16]. */
	buffer_member_format format_4x_uint16();
	/** Get a `buffer_member_format` instance, describing a record of [uint16, uint16, uint16]. */
	buffer_member_format format_3x_uint16();
	/** Get a `buffer_member_format` instance, describing a record of [uint16, uint16]. */
	buffer_member_format format_2x_uint16();
	/** Get a `buffer_member_format` instance, describing a record of [uint16]. */
	buffer_member_format format_1x_uint16();
	/** Get a `buffer_member_format` instance, describing a record of [uint32, uint32, uint32, uint32]. */
	buffer_member_format format_4x_uint32();
	/** Get a `buffer_member_format` instance, describing a record of [uint32, uint32, uint32]. */
	buffer_member_format format_3x_uint32();
	/** Get a `buffer_member_format` instance, describing a record of [uint32, uint32]. */
	buffer_member_format format_2x_uint32();
	/** Get a `buffer_member_format` instance, describing a record of [uint32]. */
	buffer_member_format format_1x_uint32();
	/** Get a `buffer_member_format` instance, describing a record of [uint64, uint64, uint64, uint64]. */
	buffer_member_format format_4x_uint64();
	/** Get a `buffer_member_format` instance, describing a record of [uint64, uint64, uint64]. */
	buffer_member_format format_3x_uint64();
	/** Get a `buffer_member_format` instance, describing a record of [uint64, uint64]. */
	buffer_member_format format_2x_uint64();
	/** Get a `buffer_member_format` instance, describing a record of [uint64]. */
	buffer_member_format format_1x_uint64();
	/** Convenience overloads for some known data types, namely some glm types: */
	template <typename T>
	buffer_member_format format_for();

	/** Can be used to describe what kind of data a buffer member represents. */
	enum struct content_description
	{
		unspecified,
		index,
		position,
		normal,
		tangent,
		bitangent,
		color,
		texture_coordinate,
		bone_weight,
		bone_index,
		user_defined_01,
		user_defined_02,
		user_defined_03,
		user_defined_04,
		user_defined_05,
		user_defined_06,
		user_defined_07,
		user_defined_08,
		user_defined_09,
		user_defined_10,
		user_defined_11,
		user_defined_12,
		user_defined_13,
		user_defined_14,
		user_defined_15,
		user_defined_16
	};

	/** Meta data for a buffer element's member.
	 *	This is used to describe
	 */
	struct buffer_element_member_meta
	{
		uint32_t mLocation;
		size_t mOffset;
		buffer_member_format mFormat;
		content_description mContent;
	};

	/** This struct contains information for a generic buffer.
	*/
	class generic_buffer_meta
	{
	public:
		/** Total size of the data represented by the buffer. */
		size_t total_size() const { return mSize; }
		
		/** Create meta info from the total size of the represented data. */
		static generic_buffer_meta create_from_size(size_t pSize) 
		{ 
			generic_buffer_meta result; 
			result.mSize = pSize; 
			return result; 
		}

		/** Create meta info from a STL-container like data structure or a single struct.
		 *	Container types must provide a `size()` method and the index operator.
		 */
		template <typename T>
		static std::enable_if_t<!std::is_pointer_v<T>, generic_buffer_meta> create_from_data(const T& pData)
		{
			generic_buffer_meta result; 
			result.mSize = how_many_elements(pData) * sizeof(first_or_only_element(pData)); 
			return result; 
		}

	private:
		// The total size of the data
		size_t mSize;
	};

	/** This struct contains information for a uniform buffer.
	*/
	class uniform_buffer_meta
	{
	public:
		/** Total size of the data represented by the buffer. */
		size_t total_size() const { return mSize; }

		/** Create meta info from the total size of the represented data. */
		static uniform_buffer_meta create_from_size(size_t pSize) 
		{ 
			uniform_buffer_meta result; 
			result.mSize = pSize; 
			return result; 
		}

		/** Create meta info from a STL-container like data structure or a single struct.
		*	Container types must provide a `size()` method and the index operator.
		*/
		template <typename T>
		static std::enable_if_t<!std::is_pointer_v<T>, uniform_buffer_meta> create_from_data(const T& pData)
		{
			uniform_buffer_meta result; 
			result.mSize = how_many_elements(pData) * sizeof(first_or_only_element(pData)); 
			return result; 
		}

	private:
		// The total size of the data
		size_t mSize;
	};

	/** This struct contains information for a uniform texel buffer.
	*/
	class uniform_texel_buffer_meta
	{
public:
		/** Total size of the data represented by the buffer. */
		size_t total_size() const { return sizeof_one_element() * num_elements(); }
		/** The size of one element in the buffer. */
		size_t sizeof_one_element() const { return mSizeOfOneElement; }
		/** The total number of elements in the buffer. */
		size_t num_elements() const { return mNumElements; }
		/** Returns a reference to a collection of all member descriptions */
		const auto& member_descriptions() const { return mOrderedMemberDescriptions; }

		/** Create meta info from the size of one element and the number of elements. 
		 */
		static uniform_texel_buffer_meta create_from_element_size(size_t pSizeElement, size_t pNumElements) 
		{ 
			uniform_texel_buffer_meta result; 
			result.mSizeOfOneElement = pSizeElement;
			result.mNumElements = pNumElements;
			return result; 
		}

		/** Create meta info from the total size of all elements. */
		static uniform_texel_buffer_meta create_from_total_size(size_t pTotalSize, size_t pNumElements) 
		{ 
			uniform_texel_buffer_meta result; 
			result.mSizeOfOneElement = pTotalSize / pNumElements;
			result.mNumElements = pNumElements;
			return result; 
		}

		/** Create meta info from a STL-container like data structure or a single struct.
		*	Container types must provide a `size()` method and the index operator.
		*/
		template <typename T>
		static std::enable_if_t<!std::is_pointer_v<T>, uniform_texel_buffer_meta> create_from_data(const T& pData)
		{
			uniform_texel_buffer_meta result; 
			result.mSizeOfOneElement = sizeof(first_or_only_element(pData)); 
			result.mNumElements = how_many_elements(pData);
			return result; 
		}

		/** Describe which part of an element's member gets mapped to which shader locaton. */
		uniform_texel_buffer_meta& describe_member(size_t _Offset, buffer_member_format _Format, content_description _Content = content_description::unspecified)
		{
#if defined(_DEBUG)
			if (std::find_if(std::begin(mOrderedMemberDescriptions), std::end(mOrderedMemberDescriptions), [offs = _Offset](const buffer_element_member_meta& e) { return e.mOffset == offs; }) != mOrderedMemberDescriptions.end()) {
				LOG_WARNING(fmt::format("There is already a member described at offset {}.", _Offset));
			}
#endif
			// insert already in the right place
			buffer_element_member_meta newElement{ 0u, _Offset, _Format, _Content };
			auto it = std::lower_bound(std::begin(mOrderedMemberDescriptions), std::end(mOrderedMemberDescriptions), newElement,
				[](const buffer_element_member_meta& first, const buffer_element_member_meta& second) -> bool { 
					return first.mOffset < second.mOffset;
				});
			mOrderedMemberDescriptions.insert(it, newElement);
			return *this;
		}

		/** If the texel buffer is not a data structure which contains interleaved data, 
		 *	this method can be used to describe its only data member. It is assumed that
		 *	the only data member has the same size as `mSizeOfOneElement`.
		 *	
		 *	Usage example:
		 *	```
		 *	std::vector<vec3> normals;
		 *	uniform_texel_buffer_meta meta = uniform_texel_buffer_meta::create_from_data(normals)
		 *								.describe_only_member(normals[0], content_description::normal);
		 *	```
		 */
		template <typename M>
		uniform_texel_buffer_meta& describe_only_member(const M& _Member, content_description _Content = content_description::unspecified)
		{
			// Do NOT assert(sizeof(_Member) == mSizeOfOneElement), since for uniform_texel_buffers, this could be okay! 
			// => it means that the buffer view views the data in a different format, that can also combine multiple consecutive elements 
			return describe_member(0, format_for<M>(), _Content);
		}

		/** Describe the texel buffer's format in the most generic way. This method also enables
		 *	to set a format which combines several consecutive elements, but can generally be used
		 *	to just set an arbitrary format.
		 *	
		 *	Usage example:
		 *	```
		 *	std::vector<uint32_t> indices;
		 *	uniform_texel_buffer_meta meta = uniform_texel_buffer_meta::create_from_data(indices)
		 *										.set_format<glm::uvec3>(content_description::index);
		 *	```
		 */
		template <typename T>
		uniform_texel_buffer_meta& set_format(content_description _Content = content_description::unspecified)
		{
			// Do NOT assert(sizeof(_Member) == mSizeOfOneElement), since for uniform_texel_buffers, this could be okay! 
			// => it means that the buffer view views the data in a different format, that can also combine multiple consecutive elements 
			return describe_member(0, format_for<T>(), _Content);
		}

#if defined(_MSC_VER) && defined(__cplusplus)
		/** Describe a member and let the compiler figure out offset and format.
		 *	
		 *	Usage example:
		 *	```
		 *	struct MyData { int mFirst; float mSecond; };
		 *	std::vector<MyData> myData;
		 *	uniform_texel_buffer_meta meta = uniform_texel_buffer_meta::create_from_data(myData)
		 *								.describe_member(&MyData::mFirst,  0, content_description::position)
		 *								.describe_member(&MyData::mSecond, 1, content_description::texture_coordinate);
		 *	```
		 */
		template <class T, class M> 
		uniform_texel_buffer_meta& describe_member(M T::* _Member, content_description _Content = content_description::unspecified)
		{
			return describe_member(
				((::size_t)&reinterpret_cast<char const volatile&>((((T*)0)->*_Member))),
				format_for<M>(),
				_Content);
		}
#endif

	private:
		// The size of one record/element
		size_t mSizeOfOneElement;
		// The total number of records/elements
		size_t mNumElements;
		// Descriptions of buffer record/element members, ordered by their offsets
		std::vector<buffer_element_member_meta> mOrderedMemberDescriptions;
	};

	/** This struct contains information for a storage buffer.
	*/
	class storage_buffer_meta
	{
	public:
		/** Total size of the data represented by the buffer. */
		size_t total_size() const { return mSize; }

		/** Create meta info from the total size of the represented data. */
		static storage_buffer_meta create_from_size(size_t pSize) 
		{ 
			storage_buffer_meta result; 
			result.mSize = pSize; 
			return result; 
		}

		/** Create meta info from a STL-container like data structure or a single struct.
		*	Container types must provide a `size()` method and the index operator.
		*/
		template <typename T>
		static std::enable_if_t<!std::is_pointer_v<T>, storage_buffer_meta> create_from_data(const T& pData)
		{
			storage_buffer_meta result; 
			result.mSize = how_many_elements(pData) * sizeof(first_or_only_element(pData)); 
			return result; 
		}

	private:
		// The total size of the data
		size_t mSize;
	};

	/** This struct contains information for a storage texel buffer.
	*/
	class storage_texel_buffer_meta
	{
	public:
		/** Total size of the data represented by the buffer. */
		size_t total_size() const { return sizeof_one_element() * num_elements(); }
		/** The size of one element in the buffer. */
		size_t sizeof_one_element() const { return mSizeOfOneElement; }
		/** The total number of elements in the buffer. */
		size_t num_elements() const { return mNumElements; }
		/** Returns a reference to a collection of all member descriptions */
		const auto& member_descriptions() const { return mOrderedMemberDescriptions; }

		/** Create meta info from the size of one element and the number of elements. 
		 */
		static storage_texel_buffer_meta create_from_element_size(size_t pSizeElement, size_t pNumElements) 
		{ 
			storage_texel_buffer_meta result; 
			result.mSizeOfOneElement = pSizeElement;
			result.mNumElements = pNumElements;
			return result; 
		}

		/** Create meta info from the total size of all elements. */
		static storage_texel_buffer_meta create_from_total_size(size_t pTotalSize, size_t pNumElements) 
		{ 
			storage_texel_buffer_meta result; 
			result.mSizeOfOneElement = pTotalSize / pNumElements;
			result.mNumElements = pNumElements;
			return result; 
		}

		/** Create meta info from a STL-container like data structure or a single struct.
		*	Container types must provide a `size()` method and the index operator.
		*/
		template <typename T>
		static std::enable_if_t<!std::is_pointer_v<T>, storage_texel_buffer_meta> create_from_data(const T& pData)
		{
			storage_texel_buffer_meta result; 
			result.mSizeOfOneElement = sizeof(first_or_only_element(pData)); 
			result.mNumElements = how_many_elements(pData);
			return result; 
		}

		/** Describe which part of an element's member gets mapped to which shader locaton. */
		storage_texel_buffer_meta& describe_member(size_t _Offset, buffer_member_format _Format, content_description _Content = content_description::unspecified)
		{
#if defined(_DEBUG)
			if (std::find_if(std::begin(mOrderedMemberDescriptions), std::end(mOrderedMemberDescriptions), [offs = _Offset](const buffer_element_member_meta& e) { return e.mOffset == offs; }) != mOrderedMemberDescriptions.end()) {
				LOG_WARNING(fmt::format("There is already a member described at offset {}.", _Offset));
			}
#endif
			// insert already in the right place
			buffer_element_member_meta newElement{ 0u, _Offset, _Format, _Content };
			auto it = std::lower_bound(std::begin(mOrderedMemberDescriptions), std::end(mOrderedMemberDescriptions), newElement,
				[](const buffer_element_member_meta& first, const buffer_element_member_meta& second) -> bool { 
					return first.mOffset < second.mOffset;
				});
			mOrderedMemberDescriptions.insert(it, newElement);
			return *this;
		}

		/** If the texel buffer is not a data structure which contains interleaved data, 
		 *	this method can be used to describe its only data member. It is assumed that
		 *	the only data member has the same size as `mSizeOfOneElement`.
		 *	
		 *	Usage example:
		 *	```
		 *	std::vector<vec3> normals;
		 *	storage_texel_buffer_meta meta = storage_texel_buffer_meta::create_from_data(normals)
		 *								.describe_only_member(normals[0],  2, content_description::normal);
		 *	```
		 */
		template <typename M>
		storage_texel_buffer_meta& describe_only_member(const M& _Member, content_description _Content = content_description::unspecified)
		{
			assert(sizeof(_Member) == mSizeOfOneElement);
			return describe_member(0, format_for<M>(), _Content);
		}

#if defined(_MSC_VER) && defined(__cplusplus)
		/** Describe a member and let the compiler figure out offset and format.
		 *	
		 *	Usage example:
		 *	```
		 *	struct MyData { int mFirst; float mSecond; };
		 *	std::vector<MyData> myData;
		 *	storage_texel_buffer_meta meta = storage_texel_buffer_meta::create_from_data(myData)
		 *								.describe_member(&MyData::mFirst,  0, content_description::position)
		 *								.describe_member(&MyData::mSecond, 1, content_description::texture_coordinate);
		 *	```
		 */
		template <class T, class M> 
		storage_texel_buffer_meta& describe_member(M T::* _Member, content_description _Content = content_description::unspecified)
		{
			return describe_member(
				((::size_t)&reinterpret_cast<char const volatile&>((((T*)0)->*_Member))),
				format_for<M>(),
				_Content);
		}
#endif

	private:
		// The size of one record/element
		size_t mSizeOfOneElement;
		// The total number of records/elements
		size_t mNumElements;
		// Descriptions of buffer record/element members, ordered by their offsets
		std::vector<buffer_element_member_meta> mOrderedMemberDescriptions;
	};

	/**	This struct contains information for a buffer which is intended to be used as 
	*	vertex buffer, i.e. vertex attributes provided to a shader.
	*/
	class vertex_buffer_meta
	{
	public:
		/** Total size of the data represented by the buffer. */
		size_t total_size() const { return sizeof_one_element() * num_elements(); }
		/** The size of one element in the buffer. */
		size_t sizeof_one_element() const { return mSizeOfOneElement; }
		/** The total number of elements in the buffer. */
		size_t num_elements() const { return mNumElements; }
		/** Returns a reference to a collection of all member descriptions */
		const auto& member_descriptions() const { return mOrderedMemberDescriptions; }

		/** Create meta info from the size of one element and the number of elements. 
		 *	It is legal to omit the `pNumElements` parameter for only creating an input description
		 *	(e.g. for describing the pipeline layout)
		 */
		static vertex_buffer_meta create_from_element_size(size_t pSizeElement, size_t pNumElements = 0) 
		{ 
			vertex_buffer_meta result; 
			result.mSizeOfOneElement = pSizeElement;
			result.mNumElements = pNumElements;
			return result; 
		}

		/** Create meta info from the total size of all elements. */
		static vertex_buffer_meta create_from_total_size(size_t pTotalSize, size_t pNumElements) 
		{ 
			vertex_buffer_meta result; 
			result.mSizeOfOneElement = pTotalSize / pNumElements;
			result.mNumElements = pNumElements;
			return result; 
		}

		/** Create meta info from a STL-container like data structure or a single struct.
		*	Container types must provide a `size()` method and the index operator.
		*/
		template <typename T>
		static std::enable_if_t<!std::is_pointer_v<T>, vertex_buffer_meta> create_from_data(const T& pData)
		{
			vertex_buffer_meta result; 
			result.mSizeOfOneElement = sizeof(first_or_only_element(pData)); 
			result.mNumElements = how_many_elements(pData);
			return result; 
		}

		/** Describe which part of an element's member gets mapped to which shader locaton. */
		vertex_buffer_meta& describe_member(size_t _Offset, buffer_member_format _Format, uint32_t _ShaderLocation = 0u, content_description _Content = content_description::unspecified)
		{
#if defined(_DEBUG)
			if (std::find_if(std::begin(mOrderedMemberDescriptions), std::end(mOrderedMemberDescriptions), [loc = _ShaderLocation](const buffer_element_member_meta& e) { return e.mLocation == loc; }) != mOrderedMemberDescriptions.end()) {
				LOG_WARNING(fmt::format("There is already a member described at location {}. If you are not using the location (like with a ray-tracing pipeline), this could be okay, though.", _ShaderLocation));
			}
			if (std::find_if(std::begin(mOrderedMemberDescriptions), std::end(mOrderedMemberDescriptions), [offs = _Offset](const buffer_element_member_meta& e) { return e.mOffset == offs; }) != mOrderedMemberDescriptions.end()) {
				LOG_WARNING(fmt::format("There is already a member described at offset {}.", _Offset));
			}
#endif
			// insert already in the right place
			buffer_element_member_meta newElement{ _ShaderLocation, _Offset, _Format, _Content };
			auto it = std::lower_bound(std::begin(mOrderedMemberDescriptions), std::end(mOrderedMemberDescriptions), newElement,
				[](const buffer_element_member_meta& first, const buffer_element_member_meta& second) -> bool { 
					return first.mLocation < second.mLocation;
				});
			mOrderedMemberDescriptions.insert(it, newElement);
			return *this;
		}

		/** If the vertex buffer is not a data structure which contains interleaved data, 
		 *	this method can be used to describe its only data member. It is assumed that
		 *	the only data member has the same size as `mSizeOfOneElement`.
		 *	
		 *	Usage example:
		 *	```
		 *	std::vector<vec3> normals;
		 *	vertex_buffer_meta meta = vertex_buffer_meta::create_from_data(normals)
		 *								.describe_only_member(normals[0],  2, content_description::normal);
		 *	```
		 */
		template <typename M>
		vertex_buffer_meta& describe_only_member(const M& _Member, uint32_t _ShaderLocation = 0u, content_description _Content = content_description::unspecified)
		{
			assert(sizeof(_Member) == mSizeOfOneElement);
			return describe_member(0, format_for<M>(), _ShaderLocation, _Content);
		}

#if defined(_MSC_VER) && defined(__cplusplus)
		/** Describe which part of an element's member gets mapped to which shader locaton,
		 *	and let the compiler figure out offset and format.
		 *	
		 *	Usage example:
		 *	```
		 *	struct MyData { int mFirst; float mSecond; };
		 *	std::vector<MyData> myData;
		 *	vertex_buffer_meta meta = vertex_buffer_meta::create_from_data(myData)
		 *								.describe_member(&MyData::mFirst,  0, content_description::position)
		 *								.describe_member(&MyData::mSecond, 1, content_description::texture_coordinate);
		 *	```
		 */
		template <class T, class M> 
		vertex_buffer_meta& describe_member(M T::* _Member, uint32_t _ShaderLocation = 0u, content_description _Content = content_description::unspecified)
		{
			return describe_member(
				((::size_t)&reinterpret_cast<char const volatile&>((((T*)0)->*_Member))),
				format_for<M>(),
				_ShaderLocation,
				_Content);
		}
#endif

	private:
		// The size of one record/element
		size_t mSizeOfOneElement;
		// The total number of records/elements
		size_t mNumElements;
		// Descriptions of buffer record/element members, ordered by their location (unordered if their location is not specified, i.e. left to the default of 0)
		std::vector<buffer_element_member_meta> mOrderedMemberDescriptions;
	};

	/**	This struct contains information for a buffer which is intended to be used as 
	*	index buffer.
	*/
	class index_buffer_meta
	{
	public:
		/** Total size of the data represented by the buffer. */
		size_t total_size() const { return sizeof_one_element() * num_elements(); }
		/** The size of one index. */
		size_t sizeof_one_element() const { return mSizeOfOneElement; }
		/** The total number of indices in the buffer. */
		size_t num_elements() const { return mNumElements; }

		/** Create meta info from the size of one index and the number of elements.  */
		static index_buffer_meta create_from_element_size(size_t pSizeElement, size_t pNumElements = 0) 
		{ 
			index_buffer_meta result; 
			result.mSizeOfOneElement = pSizeElement;
			result.mNumElements = pNumElements;
			return result; 
		}

		/** Create meta info from the total size of all elements. */
		static index_buffer_meta create_from_total_size(size_t pTotalSize, size_t pNumElements) 
		{ 
			index_buffer_meta result; 
			result.mSizeOfOneElement = pTotalSize / pNumElements;
			result.mNumElements = pNumElements;
			return result; 
		}

		/** Create meta info from a STL-container like data structure or a single struct.
		*	Container types must provide a `size()` method and the index operator.
		*/
		template <typename T>
		static std::enable_if_t<!std::is_pointer_v<T>, index_buffer_meta> create_from_data(const T& pData)
		{
			index_buffer_meta result; 
			result.mSizeOfOneElement = sizeof(first_or_only_element(pData)); 
			result.mNumElements = how_many_elements(pData);
			return result; 
		}

	private:
		// The size of one index
		size_t mSizeOfOneElement;
		// The total number of indices
		size_t mNumElements;
	};

	/**	This struct contains information for a buffer which is intended to be used as 
	*	instance buffer, i.e. vertex attributes provided to a shader per instance.
	*/
	struct instance_buffer_meta
	{
	public:
		/** Total size of the data represented by the buffer. */
		size_t total_size() const { return sizeof_one_element() * num_elements(); }
		/** The size of one element in the buffer. */
		size_t sizeof_one_element() const { return mSizeOfOneElement; }
		/** The total number of elements in the buffer. */
		size_t num_elements() const { return mNumElements; }
		/** Returns a reference to a collection of all member descriptions */
		const auto& member_descriptions() const { return mOrderedMemberDescriptions; }

		/** Create meta info from the size of one element and the number of elements. 
		 *	It is legal to omit the `pNumElements` parameter for only creating an input description
		 *	(e.g. for describing the pipeline layout)
		 */
		static instance_buffer_meta create_from_element_size(size_t pSizeElement, size_t pNumElements = 0) 
		{ 
			instance_buffer_meta result; 
			result.mSizeOfOneElement = pSizeElement;
			result.mNumElements = pNumElements;
			return result; 
		}

		/** Create meta info from the total size of all elements. */
		static instance_buffer_meta create_from_total_size(size_t pTotalSize, size_t pNumElements) 
		{ 
			instance_buffer_meta result; 
			result.mSizeOfOneElement = pTotalSize / pNumElements;
			result.mNumElements = pNumElements;
			return result; 
		}

		/** Create meta info from a STL-container like data structure or a single struct.
		*	Container types must provide a `size()` method and the index operator.
		*/
		template <typename T>
		static std::enable_if_t<!std::is_pointer_v<T>, instance_buffer_meta> create_from_data(const T& pData)
		{
			instance_buffer_meta result; 
			result.mSizeOfOneElement = sizeof(first_or_only_element(pData)); 
			result.mNumElements = how_many_elements(pData);
			return result; 
		}

		/** Describe which part of an element's member gets mapped to which shader locaton. */
		instance_buffer_meta& describe_member(size_t _Offset, buffer_member_format _Format, uint32_t _ShaderLocation = 0u, content_description _Content = content_description::unspecified)
		{
#if defined(_DEBUG)
			if (std::find_if(std::begin(mOrderedMemberDescriptions), std::end(mOrderedMemberDescriptions), [loc = _ShaderLocation](const buffer_element_member_meta& e) { return e.mLocation == loc; }) != mOrderedMemberDescriptions.end()) {
				LOG_WARNING(fmt::format("There is already a member described at location {}. If you are not using the location (like with a ray-tracing pipeline), this could be okay, though.", _ShaderLocation));
			}
#endif
			// insert already in the right place
			buffer_element_member_meta newElement{ _ShaderLocation, _Offset, _Format, _Content };
			auto it = std::lower_bound(std::begin(mOrderedMemberDescriptions), std::end(mOrderedMemberDescriptions), newElement,
				[](const buffer_element_member_meta& first, const buffer_element_member_meta& second) -> bool { 
					return first.mLocation < second.mLocation;
				});
			mOrderedMemberDescriptions.insert(it, newElement);
			return *this;
		}

		/** If the vertex buffer is not a data structure which contains interleaved data, 
		 *	this method can be used to describe its only data member. It is assumed that
		 *	the only data member has the same size as `mSizeOfOneElement`.
		 */
		template <typename M>
		instance_buffer_meta& describe_only_member(const M& _Member, uint32_t _ShaderLocation = 0u, content_description _Content = content_description::unspecified)
		{
			assert(sizeof(_Member) == mSizeOfOneElement);
			return describe_member(0, format_for<M>(), _ShaderLocation, _Content);
		}

#if defined(_MSC_VER) && defined(__cplusplus)
		/** Describe which part of an element's member gets mapped to which shader locaton,
		 *	and let the compiler figure out offset and format.
		 */
		template <class T, class M> 
		instance_buffer_meta& describe_member(M T::* _Member, uint32_t _ShaderLocation = 0u, content_description _Content = content_description::unspecified)
		{
			return describe_member(
				((::size_t)&reinterpret_cast<char const volatile&>((((T*)0)->*_Member))),
				format_for<M>(),
				_ShaderLocation,
				_Content);
		}
#endif

	private:
		// The size of one record/element
		size_t mSizeOfOneElement;
		// The total number of records/elements
		size_t mNumElements;
		// Descriptions of buffer record/element members, ordered by their location (unordered if their location is not specified, i.e. left to the default of 0)
		std::vector<buffer_element_member_meta> mOrderedMemberDescriptions;
	};


	// f32
	template <>	inline buffer_member_format format_for<glm::vec<4, glm::f32, glm::defaultp>>()	{ return format_4x_fp32(); }
	template <>	inline buffer_member_format format_for<glm::vec<3, glm::f32, glm::defaultp>>()	{ return format_3x_fp32(); }
	template <>	inline buffer_member_format format_for<glm::vec<2, glm::f32, glm::defaultp>>()	{ return format_2x_fp32(); }
	template <>	inline buffer_member_format format_for<glm::vec<1, glm::f32, glm::defaultp>>()	{ return format_1x_fp32(); }
	template <>	inline buffer_member_format format_for<float>()								{ return format_1x_fp32(); }
	// f64
	template <>	inline buffer_member_format format_for<glm::vec<4, glm::f64, glm::defaultp>>()	{ return format_4x_fp64(); }
	template <>	inline buffer_member_format format_for<glm::vec<3, glm::f64, glm::defaultp>>()	{ return format_3x_fp64(); }
	template <>	inline buffer_member_format format_for<glm::vec<2, glm::f64, glm::defaultp>>()	{ return format_2x_fp64(); }
	template <>	inline buffer_member_format format_for<glm::vec<1, glm::f64, glm::defaultp>>()	{ return format_1x_fp64(); }
	template <>	inline buffer_member_format format_for<double>()								{ return format_1x_fp64(); }
	// i8
	template <>	inline buffer_member_format format_for<glm::vec<4, glm::i8, glm::defaultp>>()	{ return format_4x_sint8(); }
	template <>	inline buffer_member_format format_for<glm::vec<3, glm::i8, glm::defaultp>>()	{ return format_3x_sint8(); }
	template <>	inline buffer_member_format format_for<glm::vec<2, glm::i8, glm::defaultp>>()	{ return format_2x_sint8(); }
	template <>	inline buffer_member_format format_for<glm::vec<1, glm::i8, glm::defaultp>>()	{ return format_1x_sint8(); }
	template <>	inline buffer_member_format format_for<int8_t>()								{ return format_1x_sint8(); }
	// i16
	template <>	inline buffer_member_format format_for<glm::vec<4, glm::i16, glm::defaultp>>()	{ return format_4x_sint16(); }
	template <>	inline buffer_member_format format_for<glm::vec<3, glm::i16, glm::defaultp>>()	{ return format_3x_sint16(); }
	template <>	inline buffer_member_format format_for<glm::vec<2, glm::i16, glm::defaultp>>()	{ return format_2x_sint16(); }
	template <>	inline buffer_member_format format_for<glm::vec<1, glm::i16, glm::defaultp>>()	{ return format_1x_sint16(); }
	template <>	inline buffer_member_format format_for<int16_t>()								{ return format_1x_sint16(); }
	// i32
	template <>	inline buffer_member_format format_for<glm::vec<4, glm::i32, glm::defaultp>>()	{ return format_4x_sint32(); }
	template <>	inline buffer_member_format format_for<glm::vec<3, glm::i32, glm::defaultp>>()	{ return format_3x_sint32(); }
	template <>	inline buffer_member_format format_for<glm::vec<2, glm::i32, glm::defaultp>>()	{ return format_2x_sint32(); }
	template <>	inline buffer_member_format format_for<glm::vec<1, glm::i32, glm::defaultp>>()	{ return format_1x_sint32(); }
	template <>	inline buffer_member_format format_for<int32_t>()								{ return format_1x_sint32(); }
	// i64
	template <>	inline buffer_member_format format_for<glm::vec<4, glm::i64, glm::defaultp>>()	{ return format_4x_sint64(); }
	template <>	inline buffer_member_format format_for<glm::vec<3, glm::i64, glm::defaultp>>()	{ return format_3x_sint64(); }
	template <>	inline buffer_member_format format_for<glm::vec<2, glm::i64, glm::defaultp>>()	{ return format_2x_sint64(); }
	template <>	inline buffer_member_format format_for<glm::vec<1, glm::i64, glm::defaultp>>()	{ return format_1x_sint64(); }
	template <>	inline buffer_member_format format_for<int64_t>()								{ return format_1x_sint64(); }
	// u8
	template <> inline buffer_member_format format_for<glm::vec<4, glm::u8, glm::defaultp>>()	{ return format_4x_uint8(); }
	template <> inline buffer_member_format format_for<glm::vec<3, glm::u8, glm::defaultp>>()	{ return format_3x_uint8(); }
	template <> inline buffer_member_format format_for<glm::vec<2, glm::u8, glm::defaultp>>()	{ return format_2x_uint8(); }
	template <> inline buffer_member_format format_for<glm::vec<1, glm::u8, glm::defaultp>>()	{ return format_1x_uint8(); }
	template <> inline buffer_member_format format_for<uint8_t>()								{ return format_1x_uint8(); }
	// u16
	template <>	inline buffer_member_format format_for<glm::vec<4, glm::u16, glm::defaultp>>()	{ return format_4x_uint16(); }
	template <>	inline buffer_member_format format_for<glm::vec<3, glm::u16, glm::defaultp>>()	{ return format_3x_uint16(); }
	template <>	inline buffer_member_format format_for<glm::vec<2, glm::u16, glm::defaultp>>()	{ return format_2x_uint16(); }
	template <>	inline buffer_member_format format_for<glm::vec<1, glm::u16, glm::defaultp>>()	{ return format_1x_uint16(); }
	template <>	inline buffer_member_format format_for<uint16_t>()								{ return format_1x_uint16(); }
	// u32
	template <>	inline buffer_member_format format_for<glm::vec<4, glm::u32, glm::defaultp>>()	{ return format_4x_uint32(); }
	template <>	inline buffer_member_format format_for<glm::vec<3, glm::u32, glm::defaultp>>()	{ return format_3x_uint32(); }
	template <>	inline buffer_member_format format_for<glm::vec<2, glm::u32, glm::defaultp>>()	{ return format_2x_uint32(); }
	template <>	inline buffer_member_format format_for<glm::vec<1, glm::u32, glm::defaultp>>()	{ return format_1x_uint32(); }
	template <>	inline buffer_member_format format_for<uint32_t>()								{ return format_1x_uint32(); }
	// u64
	template <>	inline buffer_member_format format_for<glm::vec<4, glm::u64, glm::defaultp>>()	{ return format_4x_uint64(); }
	template <>	inline buffer_member_format format_for<glm::vec<3, glm::u64, glm::defaultp>>()	{ return format_3x_uint64(); }
	template <>	inline buffer_member_format format_for<glm::vec<2, glm::u64, glm::defaultp>>()	{ return format_2x_uint64(); }
	template <>	inline buffer_member_format format_for<glm::vec<1, glm::u64, glm::defaultp>>()	{ return format_1x_uint64(); }
	template <>	inline buffer_member_format format_for<uint64_t>()								{ return format_1x_uint64(); }

}
