#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <utility>
#include <atomic>

using std::size_t;

template <typename T>
class SharedPtr {
	T *data;
	std::atomic<size_t>* pointersAmount;
public:
	//SharedPtr();
	SharedPtr(T* ptr=nullptr);
	SharedPtr(const SharedPtr& r) { *this = r; }
	SharedPtr(SharedPtr&& r) { *this = std::move(r); }
	~SharedPtr();
	SharedPtr& operator= (const SharedPtr& r);
	SharedPtr& operator= (SharedPtr&& r);

	operator bool() const { return data != nullptr; }
	T& operator*() const { return *data; }
	T* operator->() const { return data; }
	T* get() { return data; }
	void reset(T* ptr = nullptr);
	void swap(SharedPtr& r);
	size_t use_count() const {
		return *pointersAmount;
	}
};


#endif // INCLUDE_HEADER_HPP_
