#pragma once
//vector实现
//参考cppreference上的vector定义，逐项实现之
//由于vector处理连续的存储空间，迭代器只需原生指针，实现较方便
//from:2016-08-22
//to:unknow

#include"moonallocator.h"
#include<cstddef>
#include<iostream>

namespace moon
{
	template <class T,class Allocator=moon::allocator<T>>
	class vector {
#pragma region type definetion
		//------member types except reverse_iterator and const_reverse_iterator
		typedef typename T		value_type;
		typedef typename Allocator allocator_type;
		typedef typename std::size_t size_type;
		typedef typename	 std::ptrdiff_t difference_type;
		typedef typename value_type& reference;
		typedef typename const value_type& const_reference;
		typedef typename T* pointer;
		typedef typename const T* const_pointer;
		typedef typename pointer iterator;
		typedef typename const_pointer const_iterator;
#pragma endregion

#pragma region member variables
	private:
		iterator start = 0;
		iterator	finish = 0;
		iterator end_of_storage = 0;
#pragma endregion

#pragma region constructors and destructors
	public:
		vector() {}
		vector(size_type count, const_reference value=value_type(), allocator_type alloc=allocator_type())
		{
			finish = start = alloc.allocate(2*count);
			for (int i = 0; i < count;++i)
			{
				alloc.construct(finish, value);
				++finish;
			}
			end_of_storage = start + count * 2;
		}
		~vector()
		{
			allocator_type alloc = allocator_type();
			iterator pos = start;
			if (start == finish) return;
			for (; pos != finish; ++pos)	alloc.destroy(pos);
			alloc.deallocate(start);
		}
		

#pragma endregion

#pragma region element access
	public:
		reference operator [](size_type count) { return *(start + count); }
		reference front() { return *start; }
		reference back() { return *finish; }
#pragma endregion

#pragma region iterators
	public:
		iterator begin() { return start; }
		const_iterator cbegin() { return const start; }
		iterator end() { return finish; }
		const_iterator cend() { return const finish; }
#pragma endregion

#pragma region capacity
	public:
		bool empty() { return start == finish; }
		size_type size() { return finish- start; }
		size_type capacity() { return end_of_storage - start; }
		void reserve(size_type new_cap)
		{
			if (new_cap > capacity())
			{
				allocator_type alloc;
				iterator new_start = alloc.allocate(new_cap);
				size_type count = 0;
				for (; count < size(); ++count)
					alloc.construct(new_start+count, *(start+count));
				start = new_start;
				finish = new_start + count;
				end_of_storage = new_start + new_cap;
			}
		}
#pragma endregion

#pragma region modifiers
	public:
		void clear()
		{
			allocator_type alloc;
			while (finish != start)
				alloc.destroy(--finish);
		}
		void push_back(const_reference value)
		{
			if (start == 0) reserve(2);
			if (finish == end_of_storage) reserve(capacity() * 2);
			allocator_type alloc;
			alloc.construct(finish++, value);
		}
		void pop_back()
		{
			if (size() == 0) return;
			allocator_type alloc;
			alloc.destroy(--finish);
		}
		void insert(iterator _pos, const_reference value)
		{
			size_type pos = _pos - start;
			allocator_type alloc;
			if (end_of_storage== finish)//需要扩容
			{
				size_type count = finish-start;
				iterator new_start = alloc.allocate(count * 2);
				for (int i = 0; i < pos; ++i)
					alloc.construct(new_start + i, *(start + i));
				alloc.construct(new_start+pos,value);
				for (int i = pos + 1; i < count + 1; ++i)
					alloc.construct(new_start + i, *(start + i - 1));
				start = new_start;
				finish = new_start + count+1;
				end_of_storage = count * 2 + new_start;
			}
			else
			{
				iterator guard = start + pos;
				iterator copy = finish++;
				while (copy != guard)
					alloc.construct(copy, *(copy - 1));
				alloc.construct(copy, value);
			}

		}
		void erase(iterator pos)
		{
			allocator_type alloc;
			for (; finish - pos != 1;++pos)
			{
				alloc.destroy(pos);
				alloc.construct(pos, *(pos + 1));

			}
			--finish;
		}
	};










}


//points
/*
	vector::reserve机制
		感觉很鸡肋，pushback操作可以动态调整内存，加倍容量，一定程度上和reserve功能重合，导致reserve很尴尬啊
*/