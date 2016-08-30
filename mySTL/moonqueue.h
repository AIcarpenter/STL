#pragma once
#include"moonheap.h"
#include"moonvector.h"

namespace moon
{
#pragma region priority_queue
	template<class T,class Container=moon::vector<T>>
	class priority_queue {
		//-type definitions
		typedef typename Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference reference;
		//-member variables
		container_type col;//underlying container
#pragma region constructor and destructor
		priority_queue(): col() {}
		~priority_queue():~col(){}
#pragma endregion
#pragma region member functions
		//-element access
		const reference top() { return col.front(); }
		//-capacity
		bool empty() { return col.empty(); }
		size_type size() { return col.size(); }
		//-modifiers
		void push(const value_type& value) { col.push_back(value); moon::push_heap(col.begin(), col.end()); }
		void push(value_type&& value) { col.push_back(value); moon::push_heap(col.begin(), col.end()); }
		void pop() { pop_heap(col.begin(), col.end()); col.pop_back(); }

#pragma endregion

	};
#pragma endregion

}