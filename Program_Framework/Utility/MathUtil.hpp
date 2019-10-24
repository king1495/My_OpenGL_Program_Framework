#pragma once
#include <random>

template<typename T>
inline T getRand(T _min, T _max) {
	std::random_device rd;
	std::mt19937_64 rnd(rd());
	std::uniform_real_distribution<> range(_min, _max);
	return range(rnd);
}

template<typename T>
inline T getNormRand(T _min, T _max) {
	std::random_device rd;
	std::mt19937_64 rnd(rd());	
	std::normal_distribution<> range(_min, _max);
	return range(rnd);
}