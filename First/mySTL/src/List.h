#pragma once

namespace my {

	template<typename _data = int>
	class List
	{
	private:
		struct node {
			_data data;
			node* next;
		};
		node* m_head;
		node* m_tail;
		unsigned int m_length;

		node* find(unsigned int idx) const
		{
			node* ptr = nullptr;
			if (idx < m_length) {
				int i = 0;
				for (node* p = m_head; p; p = p->next, i++) {
					if (i == idx) {
						ptr = p;
						break;
					}
				}
			}
			return ptr;
		}

		void swap(unsigned int idx1, unsigned int idx2)
		{
			_data& a = find(idx1)->data;
			_data& b = find(idx2)->data;
			_data  c = a;
			a = b;
			b = c;
		}

	public:
		List() :m_head(nullptr), m_tail(nullptr), m_length(0) {}

		List(const _data& data)
			:m_length(1)
		{
			node* p = new node;
			m_head = p;
			m_tail = p;
			p->data = data;
			p->next = nullptr;
		}

		bool isEmpty() const
		{
			return m_length == 0 ? true : false;
		}

		void insert(const _data& data)
		{
			node* p = new node;
			p->data = data;
			p->next = nullptr;
			if (isEmpty()) {
				m_head = p;
				m_tail = p;
			}
			else {
				m_tail->next = p;
				m_tail = p;
			}
			m_length++;
		}

		bool insert(const _data& data, unsigned int idx)
		{
			node* p = new node;
			p->data = data;
			bool sus = false;
			if (idx < m_length && idx > 0) {
				sus = true;
				node* ptr = find(idx - 1);
				p->next = ptr->next;
				ptr->next = p;
			}
			if (idx == m_length)
				sus = true;
			insert(data);
			if (idx == 0) {
				sus = true;
				p->next = m_head;
				m_head = p;
			}
			m_length++;
			return sus;
		}

		_data get(unsigned int idx)const { return find(idx)->data; }

		_data& operator[] (unsigned int idx) { return find(idx)->data; }

		void del(unsigned int idx)
		{
			if (idx < m_length) {
				if (idx == 0) {
					node* p = m_head->next;
					delete m_head;
					m_head = p;
				}
				else if (idx == m_length - 1) {
					delete m_tail;
					m_tail = find(m_length - 2);
					m_tail->next = nullptr;
				}
				else {
					node* p = find(idx - 1);
					node* ptr = p->next->next;
					delete p->next;
					p->next = ptr;
				}
				m_length--;
			}
		}

		unsigned int length() const { return m_length; }

		void sort()
		{

		}

		void foreach(void (*function) (_data&) )
		{
			for (node* p = m_head; p; p = p->next) {
				function(p->data);
			}
		}

		List& operator += (const _data& data) { insert(data); return *this; }

		~List()
		{
			node* q;
			for (node* p = m_head; p; p = q) {
				q = p->next;
				delete p;
			}
		}

	};
}