#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

template<class T>
class matrix {
	public:
		matrix(int starting_rows, int starting_cols, std::vector<T> args);
		int get_rows();
		int get_cols();

		T operator () (unsigned int x, unsigned int y);
		T operator () (unsigned int i);
		matrix<T> operator + (matrix B);

		template<class U>
			friend std::ostream& operator<< (std::ostream& os, matrix<U>& M);

	private:
		int rows, cols; 
		T *data;
};

#include "maths.cpp"
