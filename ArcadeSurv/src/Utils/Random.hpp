#pragma once

#include <random>
#include <stdint.h>

class Random
{
	public:
		int32_t IntInRange(int32_t low, int32_t high);
		float FloatInRange(float low, float high);

		static Random& Get();

	private:
		Random();

		std::mt19937 m_Gen;
};