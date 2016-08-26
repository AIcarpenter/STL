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

		static size_type bufferSize;
		map_pointer node;//-指向本缓冲区的指针的指针
		pointer cur;
		pointer first;
		pointer last;
		
		deque_iterator() {};
		deque_iterator(iterator& other) { node = other.node; cur = other.cur; first = other.node; last = other.node; }

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
				last = first + BufSiz - 1;
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
				first = *ode;
				cur = last = first + BufSiz - 1;
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
			size_type node_offset = offset / BufSiz;
			size_type step_offset = offset%BufSiz;
			node = node + node_offset;
			first = *node;
			last = first + BufSiz;
			cur = first + step_offset;
			return *this;
		}
		iterator operator+(difference_type step) {
			iterator temp(*this);
			temp += step;
			return *temp;
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
		allocator<map_pointer> node_alloc;
	public:
		deque() { buffer_size = BufferSize != 0 ? BufferSize : (BufferSize*sizeof(T) < 512 ? 512 / BufferSize : 512); }
		
		//-iterators
		iterator begin() { return start; }
		iterator end() { return finish; }
		//-capacity
		bool empty() { return start == finish; }
		size_t size() { return finish - start; }
		//-element access
		reference at(size_type pos) { return *(start + pos); }
		reference front() { return *start; }
		reference back() { return *(finish-1); }
		reference operator[](size_type pos) { return start[n]; }
		//-modifiers

	private://-insider functions
		void create_map_buffer(size_type count)//cretae the memory structure of the deque;
		{
			size_type blocks = count / buffer_size+1;
			map_size = max(8, blocks + 2);//reserved for future use
			map = node_alloc.allocate(map_size);
			for (size_t i = 0; i < map_size; ++i)
				map + i = elements_alloc.allocate(buffer_size);
			
		}
		
	};















}