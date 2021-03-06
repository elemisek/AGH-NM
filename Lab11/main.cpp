#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <string>

#define NRANSI
extern "C"
{
	#include "numerical_recipes.c/nrutil.h"
}
#undef NRANSI

#include "numerical_recipes.c/sinft.c"
#include "numerical_recipes.c/four1.c"
#include "numerical_recipes.c/realft.c"
#include "numerical_recipes.c/nr.h"


float funbezszumu(size_t i, size_t n)
{
	float omega = (4.f * M_PI) / n;
	return std::sin(omega*i) + std::sin(2.f * omega*i) + std::sin(3.f * omega*i);
}

float funzszumem(size_t i, size_t n)
{
	float omega = (4.f * M_PI) / n;
	return funbezszumu(i, n) + 2.f * ((rand() / (RAND_MAX + 1.f) > 0.5f) ? 1 : (-1))*(rand() / (RAND_MAX + 1.f));
}

void fill(size_t n, float* y)
{
	for (size_t i = 1; i <= n; i++)
	{
		y[i] = funzszumem(i, n);
	}
}

float max(float* y, size_t n)
{
	float max = y[1];
	for (size_t i = 2; i <= n; i++)
	{
		if (y[i] > max)
		{
			max = y[i];
		}
	}
	return max;
}

void print2FileTransformation(std::ofstream& file, size_t n, float* y)
{
	for (size_t i = 1; i <= n; i++)
	{
		file << i << "\t" << y[i] << std::endl;
	}
}

void print2File(std::ofstream& file, size_t n, float* y)
{
	for (size_t i = 1; i <= n; i++)
	{
		file << i << "\t" << funbezszumu(i, n) << "\t" << y[i] << std::endl;
	}
}

void discriminate(size_t n, float* y)
{
	for (size_t i = 1; i <= n; i++)
	{
		if (std::fabs(y[i]) <= (0.25f*max(y, n)))
		{
			y[i] = 0.f;
		}
	}
}

void multiply(size_t n, float* y)
{
	for (size_t i = 1; i <= n; i++)
	{
		y[i] *= (2.f / n);
	}
}

void fastFourierTransformation(size_t k)
{
	size_t n = std::pow(2, k);
	std::ofstream file1("wyniki_1_"+std::to_string(k)+".txt");
	std::ofstream file2("wyniki_2_"+std::to_string(k)+".txt");
	std::ofstream file3("wyniki_3_"+std::to_string(k)+".txt");

	float* y = new float[n];

	fill(n, y);

	print2File(file1, n, y);

	sinft(y, n);

	print2FileTransformation(file2, n, y);

	discriminate(n, y);

	sinft(y, n);

	multiply(n, y);

	print2File(file3, n, y);

	file1.close();
	file2.close();
	file3.close();
}


int main()
{
	srand(time(NULL));

	fastFourierTransformation(6);
	system("py .\\chart_script3.py 6");

	fastFourierTransformation(8);
	system("py .\\chart_script3.py 8");

	fastFourierTransformation(10);
	system("py .\\chart_script1.py 10");
	system("py .\\chart_script2.py 10");
	system("py .\\chart_script2_2.py 10");
	system("py .\\chart_script3.py 10");
}
