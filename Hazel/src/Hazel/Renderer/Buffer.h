#pragma once

//PARENT FILE FOR ALL BUFFERS 

namespace Hazel {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}										//pure virtual interface*

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};

}

/*
pure virtual interface
- takes no storage
- all functions will be pure virtual thus no constructor is needed, only virtual destructor

static
- no matter how many objects of the class are created, there is only one copy of the static member
- a static member is shared by all objects of the class
- all static data is initialized to zero when the first object is created, if no other initialization is present

*/