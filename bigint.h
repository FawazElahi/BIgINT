// C++ program to implement
// the above approach
#include <bits/stdc++.h>

using namespace std;

class big{
	string digits;
public:

	//Constructors:
	big(unsigned long long n = 0);
	big(string &);
	big(const char *);
	big(big &);

	//Helper Functions:
	friend void divide_by_2(big &a);
	friend bool Null(const big &);
	friend int length(const big &);
	int operator[](const int)const;

			/* * * * Operator Overloading * * * */

	//Direct assignment
	big &operator=(const big &);

	//Post/Pre - Incrementation
	big &operator++();
	big operator++(int temp);
	big &operator--();
	big operator--(int temp);

	//Addition and Subtraction
	friend big &operator+=(big &, const big &);
	friend big operator+(const big &, const big &);
	friend big operator-(const big &, const big &);
	friend big &operator-=(big &, const big &);

	//Comparison operators
	friend bool operator==(const big &, const big &);
	friend bool operator!=(const big &, const big &);

	friend bool operator>(const big &, const big &);
	friend bool operator>=(const big &, const big &);
	friend bool operator<(const big &, const big &);
	friend bool operator<=(const big &, const big &);

	//Multiplication and Division
	friend big &operator*=(big &, const big &);
	friend big operator*(const big &, const big &);
	friend big &operator/=(big &, const big &);
	friend big operator/(const big &, const big &);

	//Modulo
	friend big operator%(const big &, const big &);
	friend big &operator%=(big &, const big &);

	//Power Function
	friend big &operator^=(big &,const big &);
	friend big operator^(big &, const big &);
	
	//Square Root Function
	friend big sqrt(big &a);

	//Read and Write
	friend ostream &operator<<(ostream &,const big &);
	friend istream &operator>>(istream &, big &);

	//Others
	friend big catalan(int n);
	friend big fibonacci(int n);
	friend big factorial(int n);
};

big::big(string & s){
	digits = "";
	int n = s.size();
	for (int i = n - 1; i >= 0;i--){
		if(!isdigit(s[i]))
			throw("ERROR");
		digits.push_back(s[i] - '0');
	}
}
big::big(unsigned long long nr){
	do{
		digits.push_back(nr % 10);
		nr /= 10;
	} while (nr);
}
big::big(const char *s){
	digits = "";
	for (int i = strlen(s) - 1; i >= 0;i--)
	{
		if(!isdigit(s[i]))
			throw("ERROR");
		digits.push_back(s[i] - '0');
	}
}
big::big(big & a){
	digits = a.digits;
}

bool Null(const big& a){
	if(a.digits.size() == 1 && a.digits[0] == 0)
		return true;
	return false;
}
int length(const big & a){
	return a.digits.size();
}
int big::operator[](const int index)const{
	if(digits.size() <= index || index < 0)
		throw("ERROR");
	return digits[index];
}
bool operator==(const big &a, const big &b){
	return a.digits == b.digits;
}
bool operator!=(const big & a,const big &b){
	return !(a == b);
}
bool operator<(const big&a,const big&b){
	int n = length(a), m = length(b);
	if(n != m)
		return n < m;
	while(n--)
		if(a.digits[n] != b.digits[n])
			return a.digits[n] < b.digits[n];
	return false;
}
bool operator>(const big&a,const big&b){
	return b < a;
}
bool operator>=(const big&a,const big&b){
	return !(a < b);
}
bool operator<=(const big&a,const big&b){
	return !(a > b);
}

big &big::operator=(const big &a){
	digits = a.digits;
	return *this;
}

big &big::operator++(){
	int i, n = digits.size();
	for (i = 0; i < n && digits[i] == 9;i++)
		digits[i] = 0;
	if(i == n)
		digits.push_back(1);
	else
		digits[i]++;
	return *this;
}
big big::operator++(int temp){
	big aux;
	aux = *this;
	++(*this);
	return aux;
}

big &big::operator--(){
	if(digits[0] == 0 && digits.size() == 1)
		throw("UNDERFLOW");
	int i, n = digits.size();
	for (i = 0; digits[i] == 0 && i < n;i++)
		digits[i] = 9;
	digits[i]--;
	if(n > 1 && digits[n - 1] == 0)
		digits.pop_back();
	return *this;
}
big big::operator--(int temp){
	big aux;
	aux = *this;
	--(*this);
	return aux;
}

big &operator+=(big &a,const big& b){
	int t = 0, s, i;
	int n = length(a), m = length(b);
	if(m > n)
		a.digits.append(m - n, 0);
	n = length(a);
	for (i = 0; i < n;i++){
		if(i < m)
			s = (a.digits[i] + b.digits[i]) + t;
		else
			s = a.digits[i] + t;
		t = s / 10;
		a.digits[i] = (s % 10);
	}
	if(t)
		a.digits.push_back(t);
	return a;
}
big operator+(const big &a, const big &b){
	big temp;
	temp = a;
	temp += b;
	return temp;
}

big &operator-=(big&a,const big &b){
	if(a < b)
		throw("UNDERFLOW");
	int n = length(a), m = length(b);
	int i, t = 0, s;
	for (i = 0; i < n;i++){
		if(i < m)
			s = a.digits[i] - b.digits[i]+ t;
		else
			s = a.digits[i]+ t;
		if(s < 0)
			s += 10,
			t = -1;
		else
			t = 0;
		a.digits[i] = s;
	}
	while(n > 1 && a.digits[n - 1] == 0)
		a.digits.pop_back(),
		n--;
	return a;
}
big operator-(const big& a,const big&b){
	big temp;
	temp = a;
	temp -= b;
	return temp;
}

big &operator*=(big &a, const big &b)
{
	if(Null(a) || Null(b)){
		a = big();
		return a;
	}
	int n = a.digits.size(), m = b.digits.size();
	vector<int> v(n + m, 0);
	for (int i = 0; i < n;i++)
		for (int j = 0; j < m;j++){
			v[i + j] += (a.digits[i] ) * (b.digits[j]);
		}
	n += m;
	a.digits.resize(v.size());
	for (int s, i = 0, t = 0; i < n; i++)
	{
		s = t + v[i];
		v[i] = s % 10;
		t = s / 10;
		a.digits[i] = v[i] ;
	}
	for (int i = n - 1; i >= 1 && !v[i];i--)
			a.digits.pop_back();
	return a;
}
big operator*(const big&a,const big&b){
	big temp;
	temp = a;
	temp *= b;
	return temp;
}

big &operator/=(big& a,const big &b){
	if(Null(b))
		throw("Arithmetic Error: Division By 0");
	if(a < b){
		a = big();
		return a;
	}
	if(a == b){
		a = big(1);
		return a;
	}
	int i, lgcat = 0, cc;
	int n = length(a), m = length(b);
	vector<int> cat(n, 0);
	big t;
	for (i = n - 1; t * 10 + a.digits[i] < b;i--){
		t *= 10;
		t += a.digits[i] ;
	}
	for (; i >= 0; i--){
		t = t * 10 + a.digits[i];
		for (cc = 9; cc * b > t;cc--);
		t -= cc * b;
		cat[lgcat++] = cc;
	}
	a.digits.resize(cat.size());
	for (i = 0; i < lgcat;i++)
		a.digits[i] = cat[lgcat - i - 1];
	a.digits.resize(lgcat);
	return a;
}
big operator/(const big &a,const big &b){
	big temp;
	temp = a;
	temp /= b;
	return temp;
}

big &operator%=(big& a,const big &b){
	if(Null(b))
		throw("Arithmetic Error: Division By 0");
	if(a < b){
		a = big();
		return a;
	}
	if(a == b){
		a = big(1);
		return a;
	}
	int i, lgcat = 0, cc;
	int n = length(a), m = length(b);
	vector<int> cat(n, 0);
	big t;
	for (i = n - 1; t * 10 + a.digits[i] < b;i--){
		t *= 10;
		t += a.digits[i];
	}
	for (; i >= 0; i--){
		t = t * 10 + a.digits[i];
		for (cc = 9; cc * b > t;cc--);
		t -= cc * b;
		cat[lgcat++] = cc;
	}
	a = t;
	return a;
}
big operator%(const big &a,big &b){
	big temp;
	temp = a;
	temp %= b;
	return temp;
}

big &operator^=(big & a,const big & b){
	big Exponent, Base(a);
	Exponent = b;
	a = 1;
	while(!Null(Exponent)){
		if(Exponent[0] & 1)
			a *= Base;
		Base *= Base;
		divide_by_2(Exponent);
	}
	return a;
}
big operator^(big & a,big & b){
	big temp(a);
	temp ^= b;
	return temp;
}

void divide_by_2(big & a){
	int add = 0;
	for (int i = a.digits.size() - 1; i >= 0;i--){
		int digit = (a.digits[i] >> 1) + add;
		add = ((a.digits[i] & 1) * 5);
		a.digits[i] = digit;
	}
	while(a.digits.size() > 1 && !a.digits.back())
		a.digits.pop_back();
}

big sqrt(big & a){
	big left(1), right(a), v(1), mid, prod;
	divide_by_2(right);
	while(left <= right){
		mid += left;
		mid += right;
		divide_by_2(mid);
		prod = (mid * mid);
		if(prod <= a){
			v = mid;
			++mid;
			left = mid;
		}
		else{
			--mid;
			right = mid;
		}
		mid = big();
	}
	return v;
}

big catalan(int n){
	big a(1),b;
	for (int i = 2; i <= n;i++)
		a *= i;
	b = a;
	for (int i = n + 1; i <= 2 * n;i++)
		b *= i;
	a *= a;
	a *= (n + 1);
	b /= a;
	return b;
}

big fibonacci(int n){
	big a(1), b(1), c;
	if(!n)
		return c;
	n--;
	while(n--){
		c = a + b;
		b = a;
		a = c;
	}
	return b;
}

big factorial(int n){
	big f(1);
	for (int i = 2; i <= n;i++)
		f *= i;
	return f;
}

istream &operator>>(istream &in,big&a){
	string s;
	in >> s;
	int n = s.size();
	for (int i = n - 1; i >= 0;i--){
		if(!isdigit(s[i]))
			throw("INVALID NUMBER");
		a.digits[n - i - 1] = s[i];
	}
	return in;
}

ostream &operator<<(ostream &out,const big &a){
	for (int i = a.digits.size() - 1; i >= 0;i--)
		cout << (short)a.digits[i];
	return cout;
}
