#pragma once
#include"moonallocator.h"
#include"mooniterator_base.h"
#include<cstddef>

namespace moon
{
	template<class T,class Ref,class Ptr,size_t BufSiz>
	struct deque_iterator {
		typedef deque_iterator<T, T&, T*, BufSiz> iterator;
		typedef deque_iterator<T, const T&, const T*, BufSiz> const_iterator;
		
		typedef random_access_iterator_tag	iterator_category;
		typedef T	value_type;
		typedef T* pointer;
		typedef Ref reference;
		typedef ptrdiff_t	difference_type;
		typedef T**	map_pointer;
		typedef size_t	size_type;

		size_type buffer_size;
		map_pointer node=nullptr;//-指向本缓冲区的指针的指针
		pointer cur=nullptr;
		pointer first=nullptr;
		pointer last=nullptr;
		
		deque_iterator() { buffer_size = BufSiz != 0 ? BufSiz: (BufSiz*sizeof(T) < 512 ? 512 / sizeof(value_type) : 512); }
		deque_iterator(iterator& other) { node = other.node; cur = other.cur; first = other.first; last = other.last; buffer_size = other.buffer_size; }

		//-operator override
		bool operator == (iterator& other) { return cur== other.cur; }
		bool operator != (iterator& other) { return cur!= other.cur; }
		reference operator*() { return *cur; }
		pointer operator->() { return &(*cur); }
		iterator operator++(){
			if (cur != last) ++cur;
			else{
				++node;
				cur = *node;
				first = cur;
				last = first + buffer_size - 1;
			}
			return *this;
		}
		iterator operator++(int)	{
			iterator temp(*this);
			++*this;
			return temp;
		}
		iterator operator--(){
			if (first != cur) --cur;
			else{
				--node;
				first = *node;
				cur = last = first + buffer_size - 1;
			}
			return *this;
		}
		iterator operator--(int){
			iterator temp(*this);
			--*this;
			return temp;
		}
		iterator operator+=(difference_type step){ //step>=0
			size_type offset = cur - first + step;
			size_type node_offset = offset / buffer_size;
			size_type step_offset = offset%buffer_size;
			node = node + node_offset;
			first = *node;
			last = first + buffer_size;
			cur = first + step_offset;
			return *this;
		}
		iterator operator+(difference_type step) {
			iterator temp(*this);
			temp += step;
			return temp;
		}
		iterator operator-=(difference_type step) {
			size_type offset = cur - first - step;
			if (offset >= 0) cur = first + offset;//the same buffer
			else {//surpass the buffer
				offset *= -1 ;
				size_type node_offset = offset / BufSiz;
				size_type step_offset = offset%BufSiz;
				node -= node_offset+1;
				first = *node;
				last = first + BufSiz - 1;
				cur = last - step_offset+1;
			}
			return *this;
		}
		iterator operator-(difference_type step)
		{
			iterator temp(*this);
			temp -= step;
			return temp;
		}
		size_t operator-(iterator other)
		{
	//		cout << "........." << endl;
			size_t distance = (this->node - other.node)*buffer_size +(size_t) (this->cur - this->first) - (size_t)(other.cur - other.first);
	//		cout << ".........." << endl;
			return distance;
		}
		reference operator[](difference_type n)
		{
			return *((*this) + n);
		}
	};


	template<class T,class Allocator=moon::allocator<T>,size_t BufferSize=0>
	class deque {
		typedef T	value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef Allocator allocator_type;
		typedef size_t	size_type;
		typedef ptrdiff_t difference_type;
		typedef deque_iterator<T,T&,T*,BufferSize> iterator;
		typedef pointer*	map_pointer;

		//-member variable
		size_type map_size;//中控buffer指针的数量
		size_type buffer_size;
		map_pointer map;//指向中控器map
		iterator start;
		iterator finish;//[start,finish)
		allocator_type elements_alloc;
		allocator<pointer> node_alloc;
	public:
		deque() { buffer_size = BufferSize != 0 ? BufferSize : (BufferSize*sizeof(T) < 512 ? 512 / sizeof(value_type): 512); }
		~deque()
		{
			while (!empty())
			{
				elements_alloc.destroy(&*start);
				++start;
			}
			for (int i = 0; i != map_size; ++i)
				elements_alloc.deallocate(map[i]);
			node_alloc.deallocate(map);
		}
		//-iterators
		iterator begin() { return start; }
		iterator end() { return finish; }
		//-capacity
		bool empty() { return start == finish; }
		size_t size() { return finish - start; }
		size_t _mapsize() { return (size_t)map_size; }
		bool full() { return start.first == *map&&start.last == *(map + map_size - 1) + buffer_size - 1; }
		//-element access
		reference at(size_type pos) { return *(start + pos); }
		reference front() { return *start; }
		reference back() { return *(finish-1); }
		reference operator[](size_type pos) { return start[pos]; }
		//-modifiers
		void push_back(const T& value)
		{
			if (empty()) create_map_buffer(1);
			if (back_full())  reset_map();
			elements_alloc.construct(&*finish, value);
			++finish;
	//		cout << "---" << endl;
		}
		void push_back(T&& value)
		{
			if (empty()) create_map_buffer(1);
			if (back_full()) reset_map();
			elements_alloc.construct(&*finish, value);
			++finish;
		}
		void push_front(const T& value)
		{
			if (empty())  create_map_buffer(1);
			if (front_full())	reset_map();
			--start;
			elements_alloc.construct(&*start, value);
		}
		void push_front(T&& value)
		{
			if (empty())  create_map_buffer(1);
			if (front_full())	reset_map();
			--start;
			elements_alloc.construct(&*start, value);
		}
		void pop_back()
		{
			if (!empty())
			{
				--finish;
				elements_alloc.destroy(&*finish);
			}
		}
		void pop_front()
		{
			if (!empty())
			{
				elements_alloc.destroy(&*start);
				+start;
			}
		}
		void clear()
		{//destroy elements only
			for (iterator pos = start; pos != finish; ++pos)
				elements_alloc.destroy(&*pos);
		}

	private://-insider functions
		void create_map_buffer(size_type count)//cretae the memory structure of the deque;
		{
			size_type blocks = count / buffer_size+1;
			map_size =8>blocks + 2?8:blocks+2;//reserved for future use
			map = node_alloc.allocate(map_size);
			for (size_t i = 0; i < map_size; ++i)
				map[i] = elements_alloc.allocate(buffer_size);
			start.node = map + map_size / 2;
			start.cur=start.first = *start.node;
			start.last = start.first + buffer_size - 1;
			finish = start ;
		}
		void reset_map()
		{//-when map is full and we want to add an element, we expand the capacity to double size
		//	cout << "------" << endl;
			map_pointer new_map = node_alloc.allocate(map_size * 2);
			size_type distance = finish.node - start.node;
			size_type begin = map_size - distance / 2 - 1;
			size_type end = begin + finish.node - start.node;
			size_type old_begin = begin + map-start.node;
			size_type old_end = begin + (map+map_size) - start.node;
			size_type i = 0;
			for (; i != old_begin; ++i)
				new_map[i] = elements_alloc.allocate(buffer_size);
			for (; i != old_end; ++i)
				new_map[i] = *(map + i - old_begin);
			for (; i != map_size * 2; ++i)
				new_map[i] = elements_alloc.allocate(buffer_size);
			map = new_map;
			start.node = map+begin;
			finish.node = map+end;
			map_size *= 2;
		}
		bool front_full() { return start.first == *map; }
		bool back_full() { return finish.cur==map[map_size-1]+buffer_size-1; }
	};



}