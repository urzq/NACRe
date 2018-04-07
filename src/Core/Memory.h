#ifndef MEMORY_H_
#define MEMORY_H_

#include <assert.h>
#include <memory>
#include <functional>

namespace memory
{
	// A unique_ptr with a custom deleter.
	template<typename T>
	using unique_ptr_del = std::unique_ptr<T, std::function<void(T*)>>;

	// A safer alternative to raw new, that check if the ptr is nullptr before construction
	template<class T>
	void safe_new(T*& obj)
	{
		assert(obj == nullptr);
		obj = new T();
	}

	// A safer alternative to raw delete, that nullify the ptr after its deletion.
	template<class T>
	void safe_delete(T*& obj)
	{
		delete obj;
		obj = nullptr;
	}
};

#endif