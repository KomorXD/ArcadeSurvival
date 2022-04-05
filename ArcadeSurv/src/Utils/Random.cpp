#include "Random.hpp"

#include <ctime>

int32_t Random::IntInRange(int32_t low, int32_t high)
{
	std::uniform_int_distribution<int> dist(low, high);

	return dist(m_Gen);
}

float Random::FloatInRange(float low, float high)
{
	std::uniform_real_distribution<float> dist(low, high);
	
	return dist(m_Gen);
}

Random& Random::Get()
{
	static Random rng;

	return rng;
}

Random::Random()
	: m_Gen((uint32_t)std::time(nullptr))
{ }
