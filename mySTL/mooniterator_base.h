#pragma once
//建立所有迭代器的基类
#include<cstddef>


namespace moon
{
	//每种迭代器都必须提供5个相应型别，用于可能的变量定义
	//为了避免每种迭代器都实现一次5个型别，索性做出模板基类让它们继承
	template<class Catagory,class T,class Distance=std::ptrdiff_t,class Pointer=T*,class Reference=T&>
	struct iterator {
		typedef typename Catagory		iterator_catagory;//用于标识迭代器种类
		typedef typename T					value_type;
		typedef typename Distance		difference_type;//指针之间的距离类型
		typedef typename Pointer			pointer;
		typedef typename Reference		reference;
	};

	//五种迭代器的标签,之间存在一些继承关系
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag :public input_iterator_tag {};
	struct bidirectional_iterator_tag:public forward_iterator_tag{};
	struct random_access_iterator_tag: public bidirectional_iterator_tag{};

	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::
	};













}