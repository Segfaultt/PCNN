#pragma once
#include "convolution.h"

template<class T>
T mse(matrix<T> y, matrix<T> Y)
{
	auto diff  = (y-Y);
	std::cout << diff;
	return diff.norm_squared();
}

template<class T>
int convolution<T>::seed = time(NULL) + 0xBAB;

	template<class T>
convolution<T>::convolution(int n_kernels, int l_kernel, T max_value, T min_value, int kern_stride) : depth(n_kernels), stride(kern_stride), kernel_length(l_kernel)
{
	//randomly generate kernels
	kernel.reserve(n_kernels);
	std::generate_n(kernel.begin(), n_kernels, [l_kernel, min_value, max_value] () 
			{
			srand(seed++);
			std::vector<T> init_data(l_kernel*l_kernel);
			std::generate_n(init_data.begin(), l_kernel*l_kernel, [min_value, max_value] () {
					srand(seed++);
					return (double)rand()/RAND_MAX * std::abs(min_value - max_value) + std::min(min_value, max_value);
					});
			matrix<T> M(l_kernel, l_kernel, init_data);
			return M;
			});


	bias.reserve(n_kernels);
	std::generate_n(bias.begin(), n_kernels, [min_value, max_value] () {
			srand(seed++);
			return (double)rand()/RAND_MAX * std::abs(min_value - max_value) + std::min(min_value, max_value);
			});
}

	template<class U>
std::ostream& operator<< (std::ostream& os, convolution<U>& conv)
{
	os << "output depth/number of kernels: " << conv.depth << std::endl;
	os << "kernel dimensions: " << conv.kernel_length << "x" << conv.kernel_length << std::endl;
	os << "stride: " << conv.stride << std::endl;
	for (int i = 0; i < conv.depth; i++) {
		os << std::endl << i << ":\n";
		os << conv.kernel[i];
		os << conv.bias[i] << std::endl;
	}
}

	template<class T>
std::vector< matrix<T> > convolution<T>::flow(matrix<T> &img)
{
	const int img_r = (img.get_rows() - kernel_length)/stride + 1,
	      img_c = (img.get_cols() - kernel_length)/stride + 1;
	std::vector< matrix<T> > convolved;
	convolved.reserve(depth);
	for (int i = 0; i < depth; i++) {
		matrix<T> M(img_r, img_c);
		convolved.push_back(M);
	}

	for (int r = 0; r < img_r; r++) {
		for (int c = 0; c < img_c; c++) {
			for (int d = 0; d < depth; d++) {
				T sum = bias[d] + dot(kernel[d], img.submatrix(r*stride, c*stride, kernel_length, kernel_length));
				convolved[d](c, r) = sum;
			}
		}
	}

	return convolved;
}

	template<class T>
int convolution<T>::get_depth()
{
	return depth;
}

	template<class T>
int convolution<T>::get_stride()
{
	return stride;
}

	template<class T>
int convolution<T>::get_kernel_length()
{
	return kernel_length;
}
