#ifndef RATIONAL
#define RATIONAL

#include <iostream>

namespace myrational {
	class rational {
	private:
		int son;
		int mom;
	public:
		rational(const int _son, const int _mom) {
			son = _son;
			mom = _mom;
			reduce(*this);
		}
		rational(const int _num = 0) {
			son = _num;
			mom = 1;
			reduce(*this);
		}
		rational & reduce(rational & rhs) {
			int i, j, temp;
			if (rhs.son < rhs.mom) i = rhs.mom, j = rhs.son;
			else i = rhs.son, j = rhs.mom;
			while (j != 0) {
				temp = j;
				j = i % j;
				i = temp;
			}
			rhs.son /= i;
			rhs.mom /= i;
			int mul = rhs.son * rhs.mom;
			if (rhs.mom < 0) {
				rhs.mom = -rhs.mom;
				rhs.son = -rhs.son;
			}
			return rhs;
		}
		rational & operator=(const rational & rhs) {
			son = rhs.son;
			mom = rhs.mom;
			return *this;
		}
		rational operator+(const rational & rhs) {
			rational temp(son, mom);
			temp.mom *= rhs.mom;
			temp.son = rhs.mom * son + rhs.son * mom;
			reduce(temp);
			return temp;
		}
		rational & operator+=(const rational & rhs) {
			rational temp(son, mom);
			temp.mom *= rhs.mom;
			temp.son = rhs.mom * son + rhs.son * mom;
			reduce(temp);
			*this = temp;
			return *this;
		}
		rational & operator-=(const rational & rhs) {
			rational temp(son, mom);
			temp.mom *= rhs.mom;
			temp.son = rhs.mom * son - rhs.son * mom;
			reduce(temp);
			*this = temp;
			return *this;
		}
		rational operator-(const rational & rhs) {
			rational temp(son, mom);
			temp.mom *= rhs.mom;
			temp.son = rhs.mom * son - rhs.son * mom;
			reduce(temp);
			return temp;
		}
		rational operator*(const rational & rhs) {
			rational temp(son, mom);
			temp.mom *= rhs.mom;
			temp.son *= rhs.son;
			reduce(temp);
			return temp;
		}
		rational & operator*=(const rational & rhs) {
			rational temp(son, mom);
			temp.mom *= rhs.mom;
			temp.son *= rhs.son;
			reduce(temp);
			*this = temp;
			return *this;
		}
		rational operator/(const rational & rhs) {
			rational temp(son, mom);
			temp.mom *= rhs.son;
			temp.son = rhs.mom * son;
			reduce(temp);
			return temp;
		}
		rational & operator/=(const rational & rhs) {
			rational temp(son, mom);
			temp.mom *= rhs.son;
			temp.son = rhs.mom * son;
			reduce(temp);
			*this = temp;
			return *this;
		}
		bool operator==(const rational tmp) const {
			return son == tmp.son && mom == tmp.mom;
		}
		bool operator!=(const rational tmp) const {
			return son != tmp.son || mom != tmp.mom;
		}
		friend std::istream & operator >> (std::istream &in, rational &rhs) {
			char c;
			in >> rhs.son;
			c = in.get();
			if (c == '/') in >> rhs.mom;
			else rhs.mom = 1;
			return in;
		}
		friend std::ostream & operator<<(std::ostream &out, const rational &rhs) {
			out << rhs.son;
			if (rhs.mom != 1) out << "/" << rhs.mom;
			return out;
		}
	};
}

#endif // RATIONAL
