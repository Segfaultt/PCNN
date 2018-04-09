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
T& matrix<T>::operator () (unsigned int x, unsigned int y)
{
	return *(data + y*cols + x);
}

	template<class T>
T& matrix<T>::operator () (unsigned int i)
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
		throw message.str();
	}
}

	template<class T>
matrix<T> matrix<T>::operator * (matrix B)
{
	if (cols == B.get_rows()) {
		matrix<T> C(rows, B.get_cols());
		for (int x = 0; x < B.get_cols(); x++) {
			for (int y = 0; y < rows; y++) {
				C(x, y) = dot(r(y), B.c(x));
			}
		}
		return C;
	} else {
		std::ostringstream message;
		message << "bad dimensions in multiplication of matrices: " << rows << "x" << cols << " * " << B.get_rows() << "x" << B.get_cols();
		message << "\nA:\n" << *this << "B:\n" << B;
		throw message.str();
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
matrix<T>::matrix(int starting_rows, int starting_cols)
{
	rows = starting_rows;
	cols = starting_cols;
	data = new T[rows*cols];
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

	template<class U, class V>
U dot (matrix<U> A, matrix<V> B)
{
	assert(A.get_rows() * A.get_cols() == B.get_rows() * B.get_cols());
	assert(A.get_rows() == 1 || A.get_cols() == 1);
	assert(B.get_rows() == 1 || B.get_cols() == 1);
	int length = A.get_rows() * A.get_cols();
	U sum = 0;
	for (int i = 0; i < length; i++)
		sum += A(i) * B(i);

	return sum;
}

template<class T>
template<class R>
matrix<R> matrix<T>::apply(R (* function)(T))
{
	std::vector<R> new_data;
	for (int i = 0; i < rows * cols; i++) {
		new_data.push_back((*function)(*(data + i)));
	}

	matrix<R> M(rows, cols, new_data);
	return M;
}

	template<class T>
T* matrix<T>::begin()
{
	return data;
}

	template<class T>
T* matrix<T>::end()
{
	return data + rows * cols - 1;
}

	template<class T>
matrix<T> matrix<T>::r(int row_number)
{
	assert(row_number < rows);
	assert(row_number >= 0);
	matrix<T> M(1, cols);
	memcpy(M.begin(), data + cols * row_number, cols * sizeof(T));
	return M;
}

	template<class T>
matrix<T> matrix<T>::c(int col_number)
{
	assert(col_number < cols);
	assert(col_number >= 0);
	matrix<T> M(rows, 1);
	for (int i = 0; i < rows; i++) {
		*(M.begin() + i) = *(data + col_number + cols*i);
	}
	return M;
}
