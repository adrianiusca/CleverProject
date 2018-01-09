#pragma once

#include "Random.hpp"

namespace cp
{
    template <class T> T Random::get_linear(T min, T max)
	{
		return glm::linearRand(min, max);
	}

	template <class T> T Random::get_gauss(T min, T max)
	{
		return glm::gaussRand(min, max);
	}
}