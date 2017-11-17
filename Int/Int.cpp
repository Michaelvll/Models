#include <iostream>
#include <string>
#include <vector>

#ifndef INT
#define INT

class Get_None_Num {};
class Num_In_Array_Out_Of_Range {};
class Divide_By_Zero {};

class Int {
    std::vector<int> num;
    int neg = 1;
    static bool isnum(char c) { return c <= '9' && c >= '0'; }
    void push(int a) { num.push_back(a); }
    int &end() { return *num.rbegin(); }
    inline static int max(int a, int b) { return a > b ? a : b; }
    inline static int mod10(int a) { return a > 0 ? a % 10 : -(-a % 10); }
    int subend(const Int &b, int pos) {
        Int tmp;
        int bsz = b.num.size();
        for (int i = 0; i < pos; ++i) {
            tmp.push(0);
        }
        for (int i = 0; i < bsz; ++i) {
            tmp.push(b.num[i]);
        }
        int qa = 0;
        for (; qa < 10; ++qa) {
            if (tmp > *this) return qa;
            *this -= tmp;
        }
        return qa;
    }

   public:
    friend std::istream &operator>>(std::istream &in, Int &now) {
        now.num.clear();
        std::string s;
        in >> s;
        for (std::string::reverse_iterator it = s.rbegin(); it != s.rend();
             ++it) {
            if (*it == '-')
                now.neg = -1;
            else if (!isnum(*it))
                throw(Get_None_Num());
            else
                now.num.push_back(*it - '0');
        }
        return in;
    }
    friend std::ostream &operator<<(std::ostream &out, const Int &now) {
        if (now.neg == -1) out << '-';
        for (std::vector<int>::const_reverse_iterator it = now.num.rbegin();
             it != now.num.rend(); ++it) {
            out << *it;
        }
        return out;
    }
    Int(){};
    Int(int a) {
        num.clear();
        if (a < 0) {
            neg = -1;
            a = -a;
        }
        if (a == 0) num.push_back(0);
        while (a > 0) {
            num.push_back(a % 10);
            a /= 10;
        }
    }
    Int(long long a) {
        num.clear();
        if (a < 0) {
            neg = -1;
            a = -a;
        }
        while (a > 0) {
            num.push_back(a % 10);
            a /= 10;
        }
    }
    Int(int a[], int len) {
        for (int i = 0; i < len; ++i) {
            if (a[i] < 10 && a[i] >= 0)
                num.push_back(a[i]);
            else
                throw Num_In_Array_Out_Of_Range();
        }
    }
    Int(const std::string &a) {
        for (std::string::const_reverse_iterator it = a.rbegin();
             it != a.rend(); ++it) {
            if (*it == '-')
                neg = -1;
            else if (!isnum(*it))
                throw(Get_None_Num());
            else
                num.push_back(*it - '0');
        }
    }
    Int(const char s[]) { Int(std::string(s)); }
    Int abs() const {
        Int tmp;
        tmp.num = num;
        return tmp;
    }
    friend bool operator==(const Int &a, const Int &b) {
        if (a.num.size() != b.num.size()) return false;
        for (size_t pos = 0; pos < a.num.size(); ++pos) {
            if (a.num[pos] != b.num[pos]) return false;
        }
        return true;
    }
    friend bool operator<(const Int &a, const Int &b) {
        if (a.neg < b.neg)
            return true;
        else if (a.neg > b.neg)
            return false;
        else {
            if (a.neg * a.num.size() < b.neg * b.num.size())
                return true;
            else if (a.neg * a.num.size() > b.neg * b.num.size())
                return false;
            else {
                for (int pos = a.num.size() - 1; pos >= 0; --pos) {
                    if (a.neg * a.num[pos] < b.neg * b.num[pos])
                        return true;
                    else if (a.neg * a.num[pos] > b.neg * b.num[pos])
                        return false;
                }
                return false;
            }
        }
    }
    friend bool operator<=(const Int &a, const Int &b) {
        return a < b || a == b;
    }
    friend bool operator>(const Int &a, const Int &b) {
        if (a.neg > b.neg)
            return true;
        else if (a.neg < b.neg)
            return false;
        else {
            if (a.neg * a.num.size() > b.neg * b.num.size())
                return true;
            else if (a.neg * a.num.size() < b.neg * b.num.size())
                return false;
            else {
                for (int pos = a.num.size() - 1; pos >= 0; --pos) {
                    if (a.neg * a.num[pos] > b.neg * b.num[pos])
                        return true;
                    else if (a.neg * a.num[pos] < b.neg * b.num[pos])
                        return false;
                }
                return false;
            }
        }
    }
    friend bool operator>=(const Int &a, const Int &b) {
        return a > b || a == b;
    }

    Int &operator=(const Int &a) {
        num.clear();
        num = a.num;
        neg = a.neg;
        return *this;
    }
    friend const Int operator+(const Int &a, const Int &b) {
        Int tmp;
        tmp.push(0);
        int asz = a.num.size(), bsz = b.num.size();
        int pos = 0;
        for (; pos < max(asz, bsz); ++pos) {
            int sum = a.neg * (pos < asz ? a.num[pos] : 0) +
                      b.neg * (pos < bsz ? b.num[pos] : 0);
            int &end = tmp.end();
            int res = end + sum;
            end = mod10(res);
            tmp.push(res / 10);
        }
        while (tmp.end() == 0) tmp.num.pop_back();
        int nowneg = (tmp.end() > 0 ? 1 : -1);
        tmp.neg = nowneg;
        int tmpsz = tmp.num.size();
        for (pos = 0; pos < tmpsz; ++pos) {
            if (nowneg * tmp.num[pos] < 0) {
                tmp.num[pos + 1] -= nowneg;
                tmp.num[pos] += nowneg * 10;
            }
            tmp.num[pos] *= nowneg;
        }
        while (tmp.end() == 0) tmp.num.pop_back();
        if (tmp.num.size() == 0) tmp.push(0);
        return tmp;
    }
    Int &operator+=(const Int &a) {
        *this = *this + a;
        return *this;
    }
    friend const Int operator-(const Int &a, const Int &b) {
        Int tmp = b;
        tmp.neg = -tmp.neg;
        return a + tmp;
    }
    Int &operator-=(const Int &a) {
        *this = *this - a;
        return *this;
    }
    friend const Int operator*(const Int &a, const Int &b) {
        Int ans = 0;
        if (a.neg * b.neg < 0)
            ans.neg = -1;
        else
            ans.neg = 1;

        Int tmp;
        tmp.neg = ans.neg;
        for (size_t posa = 0; posa < a.num.size(); ++posa) {
            tmp.num.clear();
            for (size_t i = 0; i <= posa; ++i) tmp.push(0);
            for (size_t posb = 0; posb < b.num.size(); ++posb) {
                int res = a.num[posa] * b.num[posb];
                int &end = tmp.end();
                end += res % 10;
                tmp.push(res / 10);
            }
            if (tmp.end() == 0) tmp.num.pop_back();
            ans += tmp;
        }
        return ans;
    }
    Int &operator*=(const Int &a) {
        *this = *this * a;
        return *this;
    }
    friend std::pair<Int, Int> divide(const Int &ta, const Int &tb) {
        if (tb == 0) throw Divide_By_Zero();
        Int ans = 0;
        Int a = ta.abs();
        Int b = tb.abs();
        if (a.abs() < b.abs()) return std::pair<Int, Int>(ans, a);
        if (a.neg * b.neg < 0)
            ans.neg = -1;
        else
            ans.neg = 1;
        int asz = a.num.size(), bsz = b.num.size();
        int ansz = asz - bsz + 1;
        int *tmpa = new int[ansz];
        for (int pos = ansz - 1; pos >= 0; --pos) {
            tmpa[pos] = a.subend(b, pos);
        }
        while (!tmpa[ansz - 1]) --ansz;
        ans.num = std::vector<int>(tmpa, tmpa + ansz);
        delete[] tmpa;
        return std::pair<Int, Int>(ans, a);
    }
    friend const Int operator/(const Int &a, const Int &b) {
        return divide(a, b).first;
    }
    Int &operator/=(const Int &a) {
        *this = *this / a;
        return *this;
    }
    friend const Int operator%(const Int &a, const Int &b) {
        std::pair<Int, Int> res = divide(a, b);
        return res.first.neg * res.second;
    }
    Int &operator%=(const Int &a) {
        *this = *this % a;
        return *this;
    }
};

#endif  // INT