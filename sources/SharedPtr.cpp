#include <utility>
#include "SharedPtr.hpp"

using std::size_t;

/*
//конструктор без параметров
template <typename T>
SharedPtr<T>::SharedPtr() {
	SharedPtr(nullptr);
}
*/

//конструктор из сырого указателя
template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) {
	data = ptr;
	pointersAmount = new std::atomic<size_t>;
	(*pointersAmount) = size_t(ptr != nullptr);
}



//копирование
template <typename T>
SharedPtr<T>& SharedPtr<T>::operator= (const SharedPtr& r) {
	if (&r == this) return *this;
	~SharedPtr();
	data = r.data;
	pointersAmount = r.pointersAmount;
	++(*pointersAmount);
	return *this;
}

//перемещение
template <typename T>
SharedPtr<T>& SharedPtr<T>::operator= (SharedPtr&& r) {
	if (&r == this) return *this;
	~SharedPtr();
	data = r.data;
	pointersAmount = r.pointersAmount;
	r.data = nullptr;
	r.pointersAmount = nullptr;
	return *this;
}

//деструктор
template <typename T>
SharedPtr<T>::~SharedPtr() {
	if (pointersAmount == nullptr) return;
	--(*pointersAmount);
	if ((*pointersAmount) == 0) {
		delete pointersAmount;
		delete data;
	}
}

template <typename T>
void SharedPtr<T>::reset(T* ptr) {
	if (data == ptr) return;
	~SharedPtr();
	data = ptr;
	pointersAmount = new std::atomic<size_t>{ 1 };
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr& r){
	if (this == &r) return;
	std::swap(data, r.data);
	std::swap(pointersAmount, r.pointersAmount);
}