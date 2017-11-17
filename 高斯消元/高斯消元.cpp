#include <iostream>
#include "rational.hpp"
using namespace std;
using namespace myrational;

void swap(rational *a, rational *m, int &mem, const int length, const int j) {
	rational temp[100] = { 0 };
	for (int j_temp = 0; j_temp != length; ++j_temp) {
		temp[j_temp] = a[j_temp] ;
		a[j_temp] = m[j_temp] ;
		m[j_temp] = temp[j_temp] ;
	}
	rational tmp(m[j]);
	for (int j_temp = j; j_temp != length; ++j_temp) {
		m[j_temp] /= tmp;
	}
}

int main()
{
	char c;
	do {
		cout << "Please input the rows and columns: \n";
		int height, length, mem = 0;
		rational a[100][100] = { 0 };

		cin >> height >> length;
		cout << "Please input the matrix:\n";
		for (int i = 0; i != height; ++i) {
			for (int j = 0; j != length; ++j) {
				cin >> a[i][j];
			}
		}
		cout << "===================================" << "\n";
		for (int j = 0; j != length; ++j) {
			bool flag = true;
			for (int i = mem; i != height; ++i) {
				if (a[i][j] != 0) {
					swap(&a[i][0], &a[mem][0], mem, length, j);
					++mem;
					flag = false;
					break;
				}
			}
			if (flag) break;
			for (int i = 0; i != height; ++i) {
				if (i != mem - 1) {
					rational rate = a[i][j] / a[mem - 1][j];
					if (rate == 0) continue;
					for (int j_temp = j; j_temp != length; ++j_temp) {
						a[i][j_temp] -= (rate * a[mem - 1][j_temp]);
					}
				}
			}
			for (int i = 0; i != height; ++i) {
				for (int j = 0; j != length; ++j) {
					cout << a[i][j] << "\t";
				}
				cout << "\n";
			}
			cout << "===================================" << "\n";
			if (mem >= height) break;
		}
		cout << "Do you want to calculate another matrix?[y/n] ";
		cin >> c;
		cout << "\n";
	} while (c == 'y');

	return 0;
}