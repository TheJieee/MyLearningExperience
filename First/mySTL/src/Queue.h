#pragma once

#include"List.h"

namespace my {
	template<typename T>
	class Queue {

		my::List<T> list;
	public:

		Queue() {}

		Queue(const T& data)
		{
			push_back(data);
		}

		void push_back(const T& data)
		{
			list.insert(data);
		}

		const T out()
		{
			T data = list.get(0);
			list.del(0);
			return data;
		}

		T get() const
		{
			return list.get(0);
		}

		int length()const { return list.length(); }

		~Queue()
		{
			list.~List();
		}
	};
}