#include "Str.h"
#include<iostream>
#include<memory>

namespace my {

	Str::Str(const char* string)
	{
		m_size = strlen(string);
		m_buffer = new char[m_size + 1];
		memcpy(m_buffer, string, m_size);
		m_buffer[m_size] = 0;
	}

	bool Str::is_in(const Str& other) const
	{
		bool ret = false;
		int j = 0;
		for (int i = 0; i < other.m_size - m_size + 1 && j < m_size;) {
			if (other[i] == m_buffer[j]) {
				i++; j++;
			}
			else {
				i -= j - 1; j = 0;
			}
		}
		if (j == m_size)
			ret = true;
		return ret;
	}
	
	bool my::Str::is_in(const std::string& other) const//KPM
	{
		bool ret = false;
		int i = 0, j = -1;
		int* next  = new int[m_size];
		next[0] = -1;
		//Get next[]
		while (i < m_size - 1) {
			if (j == -1 or m_buffer[i] == m_buffer[j]) {
				i++; j++;
				if (m_buffer[i] != m_buffer[j])
					next[i] = j;
				else
					next[i] = next[j];
			}
			else {
				j = next[j];
			}
		}
		//
		i = j = 0;
		while (i < other.size() && j < (int)m_size) {
			if (j == -1 or other[i] == m_buffer[j]) {
				i++; j++;
			}
			else {
				j = next[j];
			}
		}

		delete[] next;
		if (j == m_size)
			ret = true;
		return ret;
	}

	std::ostream& operator<<(std::ostream& stream, Str string)
	{
		stream << string.m_buffer;
		return stream;
	}
}
