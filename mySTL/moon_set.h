#pragma once
#include"moonallocator.h"
#include"moon_binary_search_tree.h"

namespace moon
{

	template<class T>
	class set{
		typedef T value_type;
		typedef binary_search_tree<T> container_type;
		typedef binary_search_tree<T>::iterator iterator;
		typedef T* pointer;
		typedef T& reference;
		typedef binary_search_tree<T>::size_type size_type;
		container_type col;

	public:
#pragma region constructor and destructor
		set() { col(); }
		~set() { ~col(); }
#pragma endregion
#pragma region iterators
		iterator begin() { return col.begin(); }
		iterator end() { return col.end(); }
#pragma endregion
#pragma region capacity
		size_type size() { return col.size(); }
		bool empty() { return col.empty(); }
#pragma endregion
#pragma region modifiers
		void insert(const T& value) { col.insert_unique(value); }
		void insert(T&& value) { col.insert_unique(value); }
		void clear() { col.clear(); }
#pragma endregion
#pragma region lookup
		iterator find(const T&value) { return col.find(value); }
#pragma endregion



		



	};










}