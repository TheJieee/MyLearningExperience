#pragma once

#include<iostream>
#include<chrono>

namespace my {
	class Timer {

		std::chrono::time_point<std::chrono::steady_clock> start, end;
		std::chrono::duration<double> duration;
	public:
		Timer()
		{
			start = std::chrono::high_resolution_clock::now();
		}

		Timer(const char* output)
		{
			m_output = output;
			start = std::chrono::high_resolution_clock::now();
		}

		~Timer()
		{
			end = std::chrono::high_resolution_clock::now();
			duration = (end - start) * 1000.0;
			if (m_output)
				std::cout << m_output << " took time " << duration.count() << "ms" << std::endl;
			else
				std::cout << "Time took " << duration.count() << "ms" << std::endl;
		}
	private:
		const char* m_output =nullptr;
	};
}