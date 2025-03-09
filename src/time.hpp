#ifndef TIME_HPP
#define TIME_HPP
#include<chrono>
class Timer{
	public: 
		std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
		void init(){
			time = std::chrono::high_resolution_clock::now();
		}
		double deltaTime(){
			auto now = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(now - time);
			time = now;
			return duration.count()/1e9;
		}
};
#endif
