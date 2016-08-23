#pragma once
//�������е������Ļ���
#include<cstddef>


namespace moon
{
	//ÿ�ֵ������������ṩ5����Ӧ�ͱ����ڿ��ܵı�������
	//Ϊ�˱���ÿ�ֵ�������ʵ��һ��5���ͱ���������ģ����������Ǽ̳�
	template<class Catagory,class T,class Distance=std::ptrdiff_t,class Pointer=T*,class Reference=T&>
	struct iterator {
		typedef typename Catagory		iterator_catagory;//���ڱ�ʶ����������
		typedef typename T					value_type;
		typedef typename Distance		difference_type;//ָ��֮��ľ�������
		typedef typename Pointer			pointer;
		typedef typename Reference		reference;
	};

	//���ֵ������ı�ǩ,֮�����һЩ�̳й�ϵ
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