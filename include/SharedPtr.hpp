#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <utility>
#include <atomic>
//#include <iostream>

using std::size_t;

template <typename T>
class SharedPtr {
	T *data = nullptr;
	std::atomic<size_t>* pointersAmount = nullptr;
public:
	//SharedPtr();
	SharedPtr(T* ptr = nullptr) {
		data = ptr;
		pointersAmount = new std::atomic<size_t>;
		(*pointersAmount) = 1;
	}
	SharedPtr(const SharedPtr& r) { *this = r; }
	SharedPtr(SharedPtr&& r) { *this = std::move(r); }
	~SharedPtr() {
		if (pointersAmount == nullptr) return;
		--(*pointersAmount);
		if ((*pointersAmount) == 0) {
			delete pointersAmount;
			delete data;
		}
		pointersAmount = nullptr;
		data = nullptr;
	}
	SharedPtr& operator= (const SharedPtr& r) {
		if (&r == this) return *this;
		~SharedPtr();
		data = r.data;
		pointersAmount = r.pointersAmount;
		++(*pointersAmount);
		return *this;
	}
	SharedPtr& operator= (SharedPtr&& r) {
		if (&r == this) return *this;
		~SharedPtr();
		data = r.data;
		pointersAmount = r.pointersAmount;
		r.data = nullptr;
		r.pointersAmount = nullptr;
		return *this;
	}

	operator bool() const { return data != nullptr; }
	T& operator*() const { return *data; }
	T* operator->() const { return data; }
	T* get() { return data; }
	void reset(T* ptr = nullptr) {
		if (data == ptr) return;
		this->~SharedPtr();
		data = ptr;
		pointersAmount = new std::atomic<size_t>{1};
	}
	void swap(SharedPtr& r) {
		if (this == &r) return;
		std::swap(data, r.data);
		std::swap(pointersAmount, r.pointersAmount);
	}
	size_t use_count() const {
		if (pointersAmount == nullptr) return 0;
		return *pointersAmount;
	}
};


#endif // INCLUDE_HEADER_HPP_
