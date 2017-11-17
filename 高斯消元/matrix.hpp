#ifndef SJTU_OOP_MATRIX
#define SJTU_OOP_MATRIX
#include <iostream>
#include <cstddef>
#include <stdexcept>
using std :: istream;
using std :: ostream;

namespace sjtu
{

	template <int n, typename type_real = double>
	class matrix
	{
	private:
		type_real **m;
	public:
		matrix()
		{
			m = new type_real*[n + 1];
			for (int i = 0; i <= n; ++i) {
				m[i] = new type_real[n + 1];
			}

		}
		matrix(const matrix & src)
		{
			m = new type_real*[n + 1];
			for (int i = 0; i <= n; ++i) {
				m[i] = new type_real[n + 1];
				for (int j = 1; j <= n; ++j) {
					m[i][j] = src.m[i][j];
				}
			}
		}
		matrix & operator=(const matrix & src)
		{

			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					m[i][j] = src.m[i][j];
				}
			}
			return *this;
		}
		type_real & operator()(size_t i, size_t j)
		{
			if (i > n || i < 1 || j > n || j < 1)
				throw std::runtime_error("The index is out of range");
			else return m[i][j];
		}
		const type_real & operator()(size_t i, size_t j) const 
		{
			if (i > n || i < 1 || j > n || j < 1)
				throw std::runtime_error("The index is out of range");
			else return m[i][j];
		}
		
		type_real * operator[](size_t i)
		{
			if (i > n || i < 1)
				throw std::runtime_error("The index is out of range");
			else return m[i];

		}
		const type_real * operator[](size_t i) const
		{
			if (i > n || i < 1)
				throw std::runtime_error("The index is out of range");
			else return m[i];
		}
		


		size_t size() const
		{
			return n;
		}
		matrix operator+(const matrix & rhs) const
		{
			matrix<n, type_real> temp(*this);
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					temp.m[i][j] += rhs.m[i][j];
				}
			}
			return temp;
		}
		matrix operator-(const matrix & rhs) const
		{
			matrix<n, type_real> temp(*this);
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					temp.m[i][j] -= rhs.m[i][j];
				}
			}
			return temp;
		}
		matrix operator*(const matrix & rhs) {
			matrix<n,type_real> temp;
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					temp.m[i][j] = 0;
				}
			}
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					for (int k = 1; k <= n; ++k) {
						temp.m[i][j] += m[i][k] * rhs.m[k][j];
					}
				}
			}
			return temp;
		}
		
		friend istream & operator>>(istream & fin, matrix & rhs)
		{
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					fin >> rhs.m[i][j];
				}
			}
			return fin;
		}
		friend ostream & operator<<(ostream & fout, const matrix & rhs)
		{
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					fout << rhs.m[i][j] << ' ';
				}
				if (i != n) fout << "\n";
			}
			return fout;
		}
		~matrix()
		{
			for (int i = 0; i <= n; ++i) {
				delete[]m[i];
			}
			delete[]m;
		}
	};
}
#endif
