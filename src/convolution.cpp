#pragma once //the things I do for abstraction and generalisation 
#include "convolution.h"


template<class T>
int convolution<T>::seed = time(NULL) + 0xBAB;

	template<class T>
convolution<T>::convolution(int n_kernels, int w_kernel, int h_kernel, T max_value, T min_value, int kern_stride) : depth(n_kernels), stride(kern_stride), kernel_width(w_kernel), kernel_height(h_kernel)
{
	kernel.reserve(n_kernels);
	std::generate_n(kernel.begin(), n_kernels, [w_kernel, h_kernel, min_value, max_value] () 
			{
			srand(seed++);
			std::vector<T> init_data(w_kernel*h_kernel);
			std::generate_n(init_data.begin(), w_kernel*h_kernel, [min_value, max_value] () {
					srand(seed++);
					return (double)rand()/RAND_MAX * std::abs(min_value - max_value) + std::min(min_value, max_value);
					});
			matrix<T> M(h_kernel, w_kernel, init_data);
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
	for (int i = 0; i < conv.depth; i++) {
		os << std::endl << i << ":\n";
		os << conv.kernel[i];
		os << conv.bias[i] << std::endl;
	}
}

	template<class T>
matrix< std::vector<T> > convolution<T>::flow(matrix<T>& img)
{
	const int img_r = (img.get_rows() - kernel_height)/stride + 1,
	      img_c = (img.get_cols() - kernel_width)/stride + 1;
	matrix< std::vector<T> > convolved(img_r, img_c);
	convolved.for_each([this] (std::vector<T> &pixel)
			{
			pixel.resize(depth);
			return 0;
			});

	for (int r = 0; r < img_r; r++) {
		for (int c = 0; c < img_c; c++) {
			for (int d = 0; d < depth; d++) {
				convolved(r, c)[d] = dot(kernel[d], img.submatrix(r*stride, c*stride, kernel_width, kernel_height)) + bias[d];
			}
		}
	}

	return convolved;
}
