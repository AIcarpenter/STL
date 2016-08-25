#pragma once
//建立所有迭代器的基类
#include<cstddef>


namespace moon
{
	//五种迭代器的标签,之间存在一些继承关系
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag :public input_iterator_tag {};
	struct bidirectional_iterator_tag :public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<class T>
	struct output_iterator {
		typedef typename output_iterator_tag		iterator_catogory;
		typedef typename T									value_type;
		typedef typename T*								pointer;
		typedef typename T&								reference;
		typedef typename ptrdiff_t						difference_type;
	};

	template <class T>
	struct input_iterator {
		typedef typename input_iterator_tag			iterator_catogory;
		typedef typename T									value_type;
		typedef typename T*								pointer;
		typedef typename T&								reference;
		typedef typename ptrdiff_t						difference_type;
	};

	template <class T>
	struct forward_iterator {
		typedef typename forward_iterator_tag			iterator_catogory;
		typedef typename T									value_type;
		typedef typename T*								pointer;
		typedef typename T&								reference;
		typedef typename ptrdiff_t						difference_type;
	};

	template <class T>
	struct bidirectional_iterator {
		typedef typename bidirectional_iterator_tag			iterator_catogory;
		typedef typename T									value_type;
		typedef typename T*								pointer;
		typedef typename T&								reference;
		typedef typename ptrdiff_t						difference_type;
	};

	template <class T>
	struct random_access_iterator {
		typedef typename random_access_iterator_tag			iterator_catogory;
		typedef typename T									value_type;
		typedef typename T*								pointer;
		typedef typename T&								reference;
		typedef typename ptrdiff_t						difference_type;
	};

	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_catogory		iterator_category;
		typedef typename Iterator::value_type	value_type;
		typedef typename Iterator::pointer		pointer;
		typedef typename Iterator::reference		reference;
		typedef typename Iterator::difference_type	difference_type;
	};

	template<class T>
	struct iterator_traits<T*> {
		typedef typename random_access_iterator_tag		iterator_category;
		typedef typename T								value_type;
		typedef typename T*							pointer;
		typedef typename T&							reference;
		typedef typename ptrdiff_t					difference_type;
	};

	template<class T>
	struct iterator_traits<const T*> {
		typedef typename random_access_iterator_tag		iterator_category;
		typedef typename T								value_type;
		typedef typename T*							pointer;
		typedef typename T&							reference;
		typedef typename ptrdiff_t					difference_type;
	};


	template<class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator&)
	{
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
		distance_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::difference_type;
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}
}