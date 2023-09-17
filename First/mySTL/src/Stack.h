#pragma once

namespace my {

	template<typename _data = int>
	class Stack
	{
	private:
		int m_InitialSize;
		int m_Increase;
		_data* m_base;
		_data* m_top;
		int m_length;
		int m_size;
	public:

		Stack()
			:m_InitialSize(50), m_Increase(2), m_base(new _data[m_InitialSize]), m_top(m_base), m_length(0), m_size(m_InitialSize)
		{

		}

		bool isEmpty() const
		{
			return m_length == 0 ? true : false;
		}

		_data get() const
		{
			return m_length > 0 ? *(m_top - 1) : 0;
		}

		_data pop()
		{
			m_length--;
			return m_length > -1 ? *--m_top : 0;
		}

		void push(const _data& data)
		{
			if (m_length == m_size - 1) {
				_data* p = new _data[m_size + m_Increase];
				for (int i = 0; i < m_length; i++) {
					p[i] = m_base[i];
				}
				m_size += m_Increase;
				m_base = p;
				m_top = &p[m_length];
			}
			*m_top++ = data;
			m_length++;
		}

		~Stack()
		{
			delete[] m_base;
		}
	};
}