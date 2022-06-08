#ifndef AGUAMENTI_PRECISION_H
#define AGUAMENTI_PRECISION_H

#include <random>

namespace Aguamenti
{
	using Real = float;
	

	#define REAL_POW pow;
	#define REAL_SQRT sqrt

	template<typename T>
	T GetRandomIntegerNumber(const T min, const T max)
	{
		std::random_device                  rand_dev;
		std::mt19937                        generator(rand_dev());
		std::uniform_int_distribution<int>  distr(min, max);
		return distr(generator);
	}

	template<typename T>
	T GetRandomRealNumber(const T min, const T max)
	{
		std::random_device                  rand_dev;
		std::mt19937                        generator(rand_dev());
		std::uniform_real_distribution<Real>  distr(min, max);
		return distr(generator);
	}
}

#endif