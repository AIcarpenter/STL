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
	class list_iterator :public iterator<bidirectional_iterator_tag, T> {
		typedef list_iterator<T> self_type;
		typedef list_node<T>	node_type;
		typedef T&					reference;//节点中数据的引用类型
	public:
		node_type* node;

		list_iterator(node_type& x) { node = &x; }//不需要显示的构造函数，因为指针变量会自动被销毁
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

#pragma endregion
	};


















}