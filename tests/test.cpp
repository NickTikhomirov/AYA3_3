#include <gtest/gtest.h>
#include "SharedPtr.hpp"
#include "utility"
#include <iostream>
using std::size_t;

TEST(SharedPtrTests_base, EmptyConstructor) {
	SharedPtr<int> testingPtr(nullptr);
	EXPECT_EQ(testingPtr.use_count(), 1);
	EXPECT_EQ(testingPtr.get(), nullptr);
	EXPECT_TRUE(!testingPtr);
}

TEST(SharedPtrTests_base,Constructor) {
	int* a;
	a = new int;
	*a = 4;
	SharedPtr<int> testingPtr(a);
	EXPECT_EQ(testingPtr.use_count(),1);
	EXPECT_EQ(testingPtr.get(), a);
	EXPECT_TRUE(testingPtr);
}

TEST(SharedPtrTests_base, SimpleDestructor) {
	int* a;
	a = new int;
	*a = 1234;
	SharedPtr<int> testingPtr(a);
	testingPtr.~SharedPtr();
	EXPECT_EQ(testingPtr.get(), nullptr);	
	EXPECT_EQ(testingPtr.use_count(), 0);
	EXPECT_TRUE(!testingPtr);
}

TEST(SharedPtrTests_base, MemDestructor) {
	int* a;
	a = new int;
	*a = 1234;
	struct r {
		int* lakmus;
		r(int* f) {	lakmus = f;}
		~r() { *lakmus = 1; }
	};
	r *r1 = new r(a);
	SharedPtr<r> testingPtr(r1);
	testingPtr.~SharedPtr();
	EXPECT_EQ(*a,1);
}

TEST(SharedPtrTests_advanced, Copy) {
	int* a;
	a = new int;
	*a = 1234;
	SharedPtr<int> t1(a);
	SharedPtr<int> t2(t1);
	EXPECT_EQ(t1.get(), t2.get());
	EXPECT_EQ(t1.use_count(),2);
	EXPECT_EQ(t2.use_count(),2);
}

TEST(SharedPtrTests_advanced, Destructor2) {
	int* a;
	a = new int;
	*a = 1234;
	SharedPtr<int> t1(a);
	SharedPtr<int> t2(t1);
	t2.~SharedPtr();
	EXPECT_EQ(t1.use_count(), 1);
}

TEST(SharedPtrTests_advanced, Move) {
	int* a;
	a = new int;
	*a = 1234;
	SharedPtr<int> t1(a);
	SharedPtr<int> t2(std::move(t1));
	EXPECT_EQ(t2.use_count(), 1);
	EXPECT_EQ(t1.get(), nullptr);
	EXPECT_EQ(t2.get(), a);
}

TEST(SharedPtrTests_misc, ResetEmpty) {
	int* a;
	a = new int;
	*a = 1234;
	SharedPtr<int> t1(a);
	SharedPtr<int> t2(t1);
	t1.reset();
	EXPECT_EQ(t1.get(), nullptr);
	EXPECT_EQ(t1.use_count(),1);
	EXPECT_EQ(t2.use_count(),1);
}

TEST(SharedPtrTests_misc, Reset) {
	int* a;
	int* b;
	a = new int;
	b = new int;
	*a = 1234;
	*b = 5678;
	SharedPtr<int> t1(a);
	SharedPtr<int> t2(t1);
	t1.reset(b);
	EXPECT_EQ(t1.get(), b);
	EXPECT_EQ(t2.get(), a);
	EXPECT_EQ(t1.use_count(), 1);
	EXPECT_EQ(t2.use_count(), 1);
}

TEST(SharedPtrTests_misc, Swap) {
	int* a;
	a = new int;
	*a = 4;
	int* b = new int{ 5 };
	SharedPtr<int> t1(a);
	SharedPtr<int> t2(b);
	std::swap(t1, t2);
	EXPECT_EQ(t2.use_count(), 1);
	EXPECT_EQ(t1.use_count(), 1);
	EXPECT_EQ(t2.get(), a);
	EXPECT_EQ(t1.get(), b);
}

TEST(SharedPtrTests_misc, Operator) {
	int* a;
	a = new int;
	*a = 4;
	SharedPtr<int> testingPtr(a);
	EXPECT_EQ(*testingPtr, *a);
}

TEST(SharedPtrTests_self, Self1) {
	int* a;
	a = new int;
	*a = 4;
	SharedPtr<int> t1(a);
	SharedPtr<int> t2;
	t2 = t1;
	t2 = t2;
	EXPECT_EQ(t2.use_count(), 2);
	EXPECT_EQ(t1.use_count(), 2);
	EXPECT_EQ(t2.get(), t1.get());
}

TEST(SharedPtrTests_self, Self2) {
	int* a;
	a = new int;
	*a = 4;
	SharedPtr<int> t1(a);
	SharedPtr<int> t2;
	t2 = std::move(t1);
	EXPECT_EQ(t2.use_count(), 1);
	EXPECT_EQ(t1.get(), nullptr);
}

TEST(SharedPtrTests_self, Self3) {
	int* a;
	a = new int;
	*a = 4;
	SharedPtr<int> t1(a);
	std::swap(t1, t1);
	EXPECT_EQ(t1.get(),a);
	EXPECT_EQ(t1.use_count(), 1);
}
