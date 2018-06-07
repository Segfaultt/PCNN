#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

#include "maths.h"
#include "neural_network.h"

template<class T>
class convolution {
	public:
		convolution(int n_kernels, int w_kernel, int h_kernel, T max_value, T min_value, int kern_stride);
		matrix< std::vector<T> > flow(matrix<T> &img);

		template<class U>
			friend std::ostream& operator<< (std::ostream& os, convolution<U>& M);

		static int seed;

	private:
		const int depth,
		      stride,
		      kernel_width,
		      kernel_height;
		std::vector< matrix<T> > kernel;
		std::vector<T> bias;
};

#include "convolution.cpp"
