#pragma once
#include<iostream>
namespace moon
{
#pragma region about heap
	template<class RamIt>
	void _max_heapify(RamIt begin, RamIt end, size_t pos)
	{//-full closed range
		size_t max = pos;
		size_t left = pos * 2 + 1;
		size_t right = pos * 2 + 2;
		size_t length = end - begin;
		if (left <= length&&begin[left] > begin[pos])
			max = left;
		if (right <= length&&begin[right] > begin[max])
			max = right;
		if (max != pos)
		{			
			auto tem = begin[max];
			begin[max] = begin[pos];
			begin[pos] = tem;
			_max_heapify(begin, end, max);
		}
	}

	template<class RamIt>
	void _build_max_heap(RamIt begin, RamIt end)
	{//-full closed range
		size_t length = end - begin;
		for (int i = length; i >= 0; --i)
			_max_heapify(begin, end, i);
	}

	template<class RamIt>inline
		void make_heap(RamIt begin, RamIt end)
	{//-half closed range
		_build_max_heap(begin, --end);
	}

	template<class RamIt>inline
		void pop_heap(RamIt begin, RamIt end)
	{//-half  closed range
		swap(*begin, *(--end));
		_max_heapify(begin, --end, 0);
	}

	template<class RamIt>inline
		void push_heap(RamIt begin, RamIt end)
	{//-half closed range
		--end;
		size_t pos = (end - begin)-1;
		size_t parent = (pos-1) / 2;
		while (parent != 0)
		{
			_max_heapify(begin, end, parent);
			parent = (parent-1)/2;
		}
		_max_heapify(begin, end, 0);
	}

	template<class RamIt>
	void sort_heap(RamIt begin, RamIt end)
	{//-half closed range
		RamIt last = end - 1;
		while (last != begin)
		{
			swap(*begin, *last);
			_max_heapify(begin, --last,0);
		}


	}
#pragma endregion
}


