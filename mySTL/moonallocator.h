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

		//allocator��stateless�ģ����캯������Ҫ�����κγ�Ա��������Ϊallocator������û�г�Ա����
		//����allocator��Ϊ���ṩ��ͬ��д�����ѣ�ûʵ������(����ʡ�ԣ���Ϊ������compiler�Զ��ṩ)
		allocator() {}
		allocator(const allocator& other){}
		template<class U>
		allocator(const allocator<U>& other) {}

		~allocator() {}

		//����δ��ʼ�����ڴ�ռ�
		//hint-referenceָ��һ���ڴ�ռ䣬����ṩ�ˣ���������ڴ�Ӧ����������hint;�˴��ݲ�ʵ��
		//------error-------Ϊʲômoon::allocator<void>::const_reference ���У�����Ҫ����const void 
		pointer allocate(size_type n, const void *hint = 0)
		{
//			DEBUG_WORDS
			return (pointer)::operator new((size_type)sizeof(value_type)*n);
		}

		//����allocate()������ڴ�ռ�
		void deallocate(pointer p, size_type n=0)
		{
			DEBUG_WORDS
			::operator delete((void*)p);
		}

		//���ú�ָ���ת��
		pointer address(referrence x) noexcept { return (pointer)(&x); }
		const_pointer address(const_reference x) noexcept { return (const_pointer)(&x); }

		size_type max_size() const noexcept { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

		void construct(pointer p, const_reference x)
		{
//			DEBUG_WORDS
			//ʹ�� placement-new:�������ڴ棬����ֱ�����ڴ���(p)�������
			 new (p) T(x);
		}

		void destroy(pointer p)
		{
//			DEBUG_WORDS
			//���ٶ��󣬵����ջ��ڴ�
			p->~value_type();
		}

		bool operator == (moon::allocator<class x> another) { return true; }
		bool operator !=  (moon::allocator<class x> another) { return false; }
	};	
}