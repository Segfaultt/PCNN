#pragma once
#include "maths.h"

	template<class T>
int matrix<T>::get_rows()
{
	return rows;
}

	template<class T>
int matrix<T>::get_cols()
{
	return cols;
}

	template<class T>
T matrix<T>::operator () (unsigned int x, unsigned int y)
{
	return *(data + y*cols + x);
}

	template<class T>
T matrix<T>::operator () (unsigned int i)
{
	return *(data + i);
}

	template<class T>
matrix<T> matrix<T>::operator + (matrix B)
{
	if (rows == B.get_rows() && cols == B.get_cols()) {
		if (rows == 0 || cols == 0) {
			return *this;
		} else {
			std::vector<T> c_data;
			for (int i = 0; i < rows*cols; i++) {
				c_data.push_back(B(i) + data[i]);
			}
			matrix<T> C(rows, cols, c_data);
			return C;
		}
	} else {
		std::ostringstream message;
		message << "bad dimensions in addition of matrices: " << rows << "x" << cols << " + " << B.get_rows() << "x" << B.get_cols();
		throw message;
	}
}

	template<class T>
matrix<T>::matrix(int starting_rows, int starting_cols, std::vector<T> args)
{
	if (starting_rows * starting_cols != args.size()) {
		std::ostringstream message;
		message << "dimensions do not match given data: " << starting_rows << "x" << starting_cols << " != " << args.size() << " elements\n\tDATA: ";
		for (auto it : args)
			message << it << ", ";
		rows = 0;
		cols = 0;
		throw message.str();
	} else {
		rows = starting_rows;
		cols = starting_cols;
		data = new T[rows*cols];
		std::copy(args.begin(), args.end(), data);
	}
}

	template<class T>
std::ostream& operator << (std::ostream& os, matrix<T>& M)
{
	os << "_";
	for (int i = 0; i < M.cols; i++) {
		os << "\t";
	}
	os << "_\n";

	for (int r = 0; r < M.rows; r++) {
		os << "| ";
		for (int c = 0; c < M.cols; c++) {
			os << M(c, r) << '\t';
		}
		os << "|\n";
	}

	os << "-";
	for (int i = 0; i < M.cols; i++) {
		os << "\t";
	}
	os << "-\n";

	return os;
}
