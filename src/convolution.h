#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

#include "maths.h"
#include "neural_network.h"

template<class T>
T mse(matrix<T> y, matrix<T> Y);

template<class T>
class convolution {
	public:
		convolution(int n_kernels, int l_kernel, T max_value, T min_value, int kern_stride);//constructor
		std::vector< matrix<T> > flow(matrix<T>& img);//apply each filter to the input and get out a layer for each filter
		
		//getters
		int get_depth();
		int get_stride();
		int get_kernel_length();

		template<class U>
			friend std::ostream& operator<< (std::ostream& os, convolution<U>& M);

		static int seed;

	private:
		const int depth,
		      stride,
		      kernel_length;//the length of 1 side of a square kernel in px
		std::vector< matrix<T> > kernel;//vector of clutches of filters
		std::vector<T> bias;
};

#include "convolution.cpp"
