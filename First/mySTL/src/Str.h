#pragma once

#include<string>

namespace my {

	class Str
	{
	public:

		Str(){}

		Str(const char*);

		bool is_in(const Str& other) const;//normal

		bool is_in(const std::string& other) const;//KPM

		char& operator[] (int idx) { return m_buffer[idx]; }

		const char& operator[] (int idx) const { return m_buffer[idx]; }

		friend std::ostream& operator << (std::ostream& stream, Str string);

		~Str() { delete[] m_buffer; }
	private:
		char* m_buffer;
		size_t m_size;
	};

}

