//============================================================================
// Name        : summ_matrix3.cpp
// Author      : Oleg Kostyuchenko
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <stdexcept>
#include <exception>
#include <fstream>

using namespace std;

class Matrix
{
private:
	int rows;
	int cols;

	vector<vector<int>> vm;

public:
	Matrix()
	{
		rows = 0;
		cols = 0;
	}

	Matrix(const int& n_rows, const int& n_cols)
	{
		if (n_rows < 0 || n_cols < 0)
		{
			throw out_of_range ("Out of range. Constructor Matrix.");
		}
		Reset (n_rows, n_cols);
	}

	void Reset (const int& n_rows, const int& n_cols)
	{
		if (n_rows < 0 || n_cols < 0)
		{
			throw out_of_range ("Out of range. Reset.");
		}
		rows = n_rows;
		cols = n_cols;
		vm.assign(n_rows, vector<int>(n_cols));
	}

	int At (const int& n_rows, const int& n_cols) const
	{
		if (n_rows < 0 || n_rows >= static_cast<int> (vm.size()) || n_cols < 0 || n_cols >= static_cast<int> (vm.at(0).size()))
		{
			throw out_of_range ("Out of range. At const.");
		}
		return vm.at(n_rows).at(n_cols);
	}

	int& At (const int& n_rows, const int& n_cols)
	{
		if (n_rows < 0 || n_rows >= static_cast<int> (vm.size()) || n_cols < 0 || n_cols >= static_cast<int> (vm.at(0).size()))
		{
			throw out_of_range ("Out of range. At no const.");
		}
		return vm.at(n_rows).at(n_cols);
	}

	int GetNumRows() const
	{
		return rows;
	}

	int GetNumColumns() const
	{
		return cols;
	}

	vector<vector<int>> GetVector () const
	{
		return vm;
	}
};

istream& operator>> (istream& stream, Matrix& matrix)
{
	int rows, cols;
	stream >> rows >> cols;
	matrix.Reset(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			stream >> matrix.At(i, j);
		}
	}
	return stream;
}

ostream& operator<< (ostream& stream, const Matrix& matrix)
{
	stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
	for (auto i : matrix.GetVector())
	{
		for (auto j : i)
		{
			stream << j << " ";
		}
		stream << endl;
	}
	return stream;
}

Matrix operator + (const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns())
	{
		throw invalid_argument ("Invalid argument in operator +");
	}
	Matrix sum;
	sum.Reset(lhs.GetNumRows(), lhs.GetNumColumns());
	for (int i = 0; i < lhs.GetNumRows(); i++)
	{
		for (int j = 0; j < lhs.GetNumColumns(); j++)
		{
			sum.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}
	return sum;
}

bool operator == (const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns())
	{
		for (int i = 0; i < lhs.GetNumRows(); i++)
		{
			for (int j = 0; j < lhs.GetNumColumns(); j++)
			{
				if (lhs.At(i, j) != rhs.At(i, j))
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool operator != (const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns())
	{
		for (int i = 0; i < lhs.GetNumRows(); i++)
		{
			for (int j = 0; j < lhs.GetNumColumns(); j++)
			{
				if (lhs.At(i, j) != rhs.At(i, j))
				{
					return true;
				}
			}
		}
	}
	else
	{
		return true;
	}
	return false;
}

int main()
{
	try
	{
	Matrix a, b, c;
	cin >> a >> b;

	c = a + b;
	cout << c;
	if (a != b)
	{
		cout << "Yahoo!";
	}
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}
	return 0;
}

