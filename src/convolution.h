#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

#include "maths.h"
#include "neural_network.h"

template<class T>
class convolution {
	public:
		convolution(int layers, int n_kernels, int l_kernel, T max_value, T min_value, int kern_stride);
		std::vector< matrix<T> > flow(std::vector< matrix<T> > &img);

		template<class U>
			friend std::ostream& operator<< (std::ostream& os, convolution<U>& M);

		static int seed;

	private:
		const int depth,
		      in_depth,
		      stride,
		      kernel_length;
		std::vector< std::vector< matrix<T> > > kernel;//vector of clutches of filters
		std::vector<T> bias;
};

#include "convolution.cpp"
