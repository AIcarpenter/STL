#pragma once
#include"mooniterator_base.h"
#include"moonallocator.h"
#include<cstddef>
#include<limits>
namespace moon
{
	//list节点
	template <class T>
	struct list_node {
		T data;
		list_node* prv;
		list_node* next;
	};

	//list迭代器
	template <class T>
	class list_iterator :public bidirectional_iterator<T> {
		typedef list_iterator<T> self_type;
		typedef list_node<T>	node_type;
		typedef T&					reference;//节点中数据的引用类型
	public:
		node_type* node;
		list_iterator() {}
		list_iterator(node_type& x) { node = &x; }//不需要显示的析构函数，因为指针变量会自动被销毁
		list_iterator(node_type* x) { node = x; }
#pragma region operator override
		bool operator==(self_type other) { return node == other.node; }
		bool operator!=(self_type other) { return node != other.node; }
		reference operator*() { return node->data; }
		pointer operator->() { return & node->data; }
		self_type operator++() { node = node->next; return *this; }
		self_type operator++(int)
		{
			self_type x(*node);
			node = node->next;
			return x;
		}
		self_type operator--() { node = node->prv; return *this; }
		self_type operator--(int)
		{
			self_type x(*node);
			node = node->prv;
			return x;
		}
#pragma endregion
	};

	//list
	template <class T, class Allocator = allocator<T>>
	class list {
		typedef typename T								value_type;
		typedef typename Allocator					allocator_type;
		typedef typename size_t						size_type;
		typedef typename ptrdiff_t					difference_type;
		typedef typename value_type&				reference;
		typedef typename const value_type&	const_reference;
		typedef typename value_type*				pointer;
		typedef typename const value_type*		const_pointer;
		typedef typename list_node<T>			node_type;
		typedef typename list_iterator<T>			iterator;
		list_node<value_type> guard;//哨兵节点
		allocator_type alloc;
		allocator<node_type> node_alloc;
#pragma region member functions
	protected:
		//-辅助函数
		node_type* create_node(const_reference x=T())
		{
			node_type* p=node_alloc.allocate(1);
			alloc.construct(&p->data,x);
			return p;

		}
		void destroy_node(iterator x)
		{
			alloc.destroy(&x.node->data);
			node_alloc.deallocate(x.node);
		}
		void empty_insert(const_reference x)
		{
			node_type* p = create_node(x);
			p->next = &guard;
			p->prv = &guard;
			guard.next = p;
			guard.prv = p;
		}
		void transfer(iterator position, iterator first, iterator last)
		{
			iterator tem1 = position, tem2 = first, tem3 = last;
			--tem1, --tem2, --tem3;
			tem1.node->next = first.node;
			first.node->prv = tem1.node;
			tem2.node->next = last.node;
			last.node->prv = tem2.node;
			tem3.node->next = position.node;
			position.node->prv = tem3.node;
		}
	public:
		list() { guard.next = &guard; guard.prv = &guard; }
		~list() { clear(); }
#pragma region iterators
		iterator begin() { return iterator(*guard.next); }
		iterator end() { return iterator(guard); }
#pragma endregion
#pragma region element access
		value_type front() { return *begin(); }
		value_type back() { return *--end(); }
#pragma endregion
#pragma region capacity
		bool empty() { return (guard.next==&guard)&&(guard.prv==&guard); }
		size_type size()
		{
			size_type count = 0;
			iterator position = begin();
			while (position != end())
			{
				++count;
				++position;
			}
			return count;
		}
#pragma  endregion
#pragma region modifiers
		void insert(iterator pos, const_reference value)
		{
			if (empty()) empty_insert(value);
			else
			{
				node_type* p = create_node(value);
				p->next = pos.node;
				pos.node->prv->next = p;
				p->prv = pos.node->prv;
				pos.node->prv = p;
			}
		}
		void push_back(const_reference value)
		{
			insert(end(), value);
		}
		void push_front(const_reference value)
		{
			insert(begin(), value());
		}
		void clear()
		{
			for (iterator curr = begin(); curr!= end();)
			{
				iterator next(curr.node->next);
				destroy_node(curr);
				curr = next;
			}
			guard.next = &guard;
			guard.prv = &guard;
		}
		void erase(iterator& x)
		{
			iterator next(x.node->next);
			iterator prv(x.node->prv);
			destroy_node(x.node);
			prv.node->next = next.node;
			next.node->prv = prv.node;
		}
		void pop_back() { iterator temp = end(); erase(--temp); }
		void pop_front() { erase(begin()); }
#pragma endregion
#pragma region operations
		void splice(iterator positon, list<value_type, allocator<value_type>>& other)
		{
			transfer(positon, other.begin(), other.end());
		}
		void splice(iterator postion, list<value_type, allocator_type>& other, iterator it)
		{
			auto next = it;
			transfer(postion, it, ++next);
		}
		void splice(iterator position, list < value_type, allocator_type > & other, iterator first, iterator last)
		{
			transfer(position, first, last);
		}
		void merge(list<value_type,allocator_type>& other)
		{
			iterator first_1 = this->begin(), last_1 = this->end();
			iterator first_2 = other.begin(), last_2 = other.end();
			while (first_1 != last_1&&first_2 != last_2)
			{
				if (*first_1 > *first_2)
				{
					iterator temp = first_2;
					transfer(first_1, first_2, ++first_2);
				}
				else ++first_1;
			}
			if (first_2 != last_2) transfer(first_1, first_2, last_2);

		}
		void reverse()
		{
			if (guard.next == guard.prv) return;//只有一个节点或空链表
			iterator first =this-> begin();
			iterator last = this->end();
			iterator pos=first,next,temp=guard;
			while (pos != last)
			{
				next = pos.node->next;
				pos.node->next = temp.node;
				temp = pos;
				pos = next;
			}
			pos.node->next = temp.node;
			temp = first;
			while (pos != first)
			{
				pos.node->prv = temp.node;
				temp = pos;
				pos = pos.node->next;
			}
			pos.node->prv = last.node;
		}
		void sort()
		{
			//-不会写。。。。。
		}
#pragma endregion

#pragma endregion
	};


















}