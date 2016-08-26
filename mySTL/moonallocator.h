#pragma once
#include<cstddef>//size_t and ptrdiff_t
#include<limits>//numeric_limits
#include<iostream>
//#define DEBUG_WORDS std::cout<<"hello kitty-"<<__LINE__<<std::endl;
#define DEBUG_WORDS ;
namespace moon
{
	template <class T>
	class allocator {
	public:
		typedef T						value_type;
		typedef T*						pointer;
		typedef const T*			const_pointer;
		typedef T&					referrence;
		typedef const T&			const_reference;
		typedef size_t				size_type;
		typedef  ptrdiff_t			difference_type;

		//for rebind-------------->(what  is rebind?)
		//rebind seemed to make it possible to allocate a different type
		template<class U>
		struct rebind {
			typedef moon::allocator<U> other;
		};

		//allocator是stateless的，构造函数不需要构造任何成员变量，因为allocator根本就没有成员变量
		//三种allocator是为了提供不同的写法而已，没实际作用(可以省略，因为都可有compiler自动提供)
		allocator() {}
		allocator(const allocator& other){}
		template<class U>
		allocator(const allocator<U>& other) {}

		~allocator() {}

		//分配未初始化的内存空间
		//hint-reference指向一块内存空间，如果提供了，分配配的内存应当尽量靠近hint;此处暂不实现
		//------error-------为什么moon::allocator<void>::const_reference 不行？？？要换成const void 
		pointer allocate(size_type n, const void *hint = 0)
		{
//			DEBUG_WORDS
			return (pointer)::operator new((size_type)sizeof(value_type)*n);
		}

		//销毁allocate()分配的内存空间
		void deallocate(pointer p, size_type n=0)
		{
			DEBUG_WORDS
			::operator delete((void*)p);
		}

		//引用和指针的转化
		pointer address(referrence x) noexcept { return (pointer)(&x); }
		const_pointer address(const_reference x) noexcept { return (const_pointer)(&x); }

		size_type max_size() const noexcept { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

		void construct(pointer p, const_reference x)
		{
//			DEBUG_WORDS
			//使用 placement-new:不分配内存，而是直接在内存上(p)构造对象
			 new (p) T(x);
		}

		void destroy(pointer p)
		{
//			DEBUG_WORDS
			//销毁对象，但不收回内存
			p->~value_type();
		}

		bool operator == (moon::allocator<class x> another) { return true; }
		bool operator !=  (moon::allocator<class x> another) { return false; }
	};	
}