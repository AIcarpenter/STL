#pragma once

#include "mooniterator_base.h"
#include"moonallocator.h"
#include<cstddef>
#include<limits>


namespace moon
{
	template<class T>
	struct bst_node {
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef const T& const_reference;
		typedef bst_node<T>* node_pointer;

		node_pointer parent=nullptr, left=nullptr, right=nullptr;
		value_type value_field;

		node_pointer minimum(node_pointer x)
		{
			while (x->left != nullptr)
				x=x->left;
			return x;
		}
		node_pointer maximum(node_pointer x)
		{
			node_pointer y = x;
			while (x->right != nullptr)
			{
				y = x;
				x = x->right;
			}
			return y;
		}
		node_pointer successor(node_pointer x)
		{
			if (x->right != nullptr) return minimum(x->right);
			node_pointer y = x->parent;
			while (y!= nullptr&&y->left != x)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}
		node_pointer predeccessor(node_pointer x)
		{
			if (x->left!=nullptr) return maximum(x->left);
			node_pointer y = x->parent;
			while (y != nullptr&&y->right != x)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}
	};

	template<class T>
	class bst_iterator {
		typedef moon::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef const T* const_pointer;
		typedef const T& const_reference;
		typedef bst_node<T> node_type;
		typedef bst_node<T>* node_pointer;
		typedef bst_iterator<T> self_type;
	public:
		node_pointer link;

#pragma region constructor and destructor
	public:
		bst_iterator() { link = nullptr; }
		bst_iterator(node_type& node) { link = &node; }
		bst_iterator(node_pointer node) { link = node; }
#pragma endregion
#pragma region operators
		bool operator ==(self_type& other) { return this->link == other.link; }
		bool operator !=(self_type& other) { return this->link != other.link; }
		reference operator*() { return link->value_field; }
		reference operator->() { return &link->value_field; }
		self_type& operator--()
		{
			link = link->predeccessor(link);
			return link;
		}
		self_type operator--(int)
		{
			self_type 	temp(link);
			--link;
			return temp;
		}
		self_type& operator++()
		{
			link = link->successor(link);
			return *this;
		}
		self_type operator++(int)
		{
			node_pointer temp = link;
			link = link->successor(link);
			return temp;
		}
	
#pragma endregion
		
	};

	template<class T,class Alloc=allocator<T>>
	class binary_search_tree {
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef const T* const_pointer;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef binary_search_tree<T> self_type;
		typedef bst_node<T> node_type;
		typedef bst_node<T>* node_pointer;
		typedef Alloc element_allcoator_type;
		typedef allocator<bst_node<T>> node_allcoator_type;
		typedef bst_iterator<T> iterator;
		typedef const bst_iterator<T> const_iterator;

		element_allcoator_type ele_alloc;
		node_allcoator_type node_alloc;
		node_pointer header;
		size_type count;
		
#pragma region insider functions
		node_pointer create_node(const T& value)
		{
			node_pointer temp = node_alloc.allocate(1);
			ele_alloc.construct(&temp->value_field, value);
			temp->left = nullptr;
			temp->right = nullptr;
			temp->parent = nullptr;
			return temp;
		}
		node_pointer create_node()
		{
			return node_alloc.allocate(1);
		}
		void delete_all_nodes(node_pointer root)
		{
			if (root != nullptr)
			{
				delete_all_nodes(root->left);
				delete_all_nodes(root->right);
				ele_alloc.destroy(&root->value_field);
				node_alloc.deallocate(root);
			}
		}
		void delete_node(iterator pos)
		{
			node_pointer x=pos.link;
			if (x->left == nullptr&&x->right == nullptr)
			{
				if (x->parent->left == x)
					x->parent->left = nullptr;
				else
					x->parent->right = nullptr;
			}
			else if (x -> left == nullptr)
			{
				if (x->parent->left == x)
					x->parent->left = x->right;
				else
					x->parent->right = x->right;
				x->right->parent = x->parent;
			}
			else if(x->right==nullptr)
			{
				if (x->parent->left == x)
					x->parent->left = x->left;
				else
					x->parent->right = x->left;
				x->left->parent = x->parent;
			}
			else 
			{
				node_pointer y = x->successor(x);
				y->left = x->left;
				x->left->parent = y;
				if (x->parent->left = x)
					x->parent->left = x->right;
				else
					x->parent->right = x->right;
				x->right->parent = x->parent;
			}
			ele_alloc.destroy(&x->value_field);
			node_alloc.deallocate(x);
		}
#pragma endregion

	public:
#pragma region constructors and destructors
		binary_search_tree()
		{
			header = create_node();
			header->left = header;
			header->right = header;
			header->parent = nullptr;
		}
		~binary_search_tree()
		{
			delete_all_nodes(header->left);
			node_alloc.deallocate(header);
		}

#pragma endregion
#pragma region iterators
		iterator begin() { return iterator(header->left->minimum(header->left)); }
		iterator end() { return iterator(header); }
#pragma endregion
#pragma region capacity
		bool empty() { return header == header->left; }
		size_type size() { return size; }
#pragma endregion
#pragma region modifiers
		void insert(const value_type& value)
		{
			if (empty())
			{
				node_pointer new_one=create_node(value);
				header->left = header->right = new_one;
				new_one->parent = header;
				count += 1;
				return;
			}
			node_pointer x = header->left;
			node_pointer y;
			while (true)
			{
				y = x;
				if (x->value_field < value)
					x = x->right;
				else
					x = x->left;
				if (x == nullptr) break;
			}
			node_pointer z = create_node(value);
			z->parent = y;
			if (y->value_field > value)
				y->left = z;
			else
				y->right = z;
			++count;
		}
		void insert(value_type&& value) { insert(value); }
		void insert_unique(const value_type& value)
		{
			if (empty())
			{
				node_pointer new_one = create_node(value);
				header->left = header->right = new_one;
				count+= 1;
				return;
			}
			node_pointer x = header->left;
			node_pointer y = nullptr;
			while (x!=nullptr)
			{
				y = x;
				if (x->value_field == value) return;
				else if (x->value_field < value)
					x = x->right;
				else
					x = x->left;
			}
			node_pointer z = create_node(value);
			z->parent = y;
			if (y->value_field < value)
				y->right = z;
			else
				y->left = z;
			++count;
		}
		void insert_unique(value_type&& value) { insert(value); }
		void clear()
		{
			delete_all_nodes(header->left);
			header->left = header->right = nullptr;
		}
		void erase(iterator pos)
		{
			delete_node(pos);
		}
		void erase(iterator first, iterator last)
		{
			while (first != last)
				delete_node(first);
		}
#pragma endregion
#pragma region lookup
		iterator find(const T& value)
		{
			node_pointer x=header->left;
			while (x != nullptr)
			{
				if (x->value_field > value)
					x = x->left;
				else if (x->value_field < value)
					x = x->right;
				else
					break;
			}
			return iterator(x);
		}
#pragma endregion

	};
}

