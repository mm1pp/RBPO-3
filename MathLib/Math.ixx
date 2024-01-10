module;
#include <math.h>
#include <iostream>
export module Math;
export class Complex
{
	double m_re;
	double m_im;
public:
	Complex() {
		m_re = 0;
		m_im = 0;
	}
	Complex(double real) {
		m_re = real;
		m_im = 0;
	}
	Complex(double real, double im) {
		m_re = real;
		m_im = im;
	}
	static Complex FromExponentialForm(double module, double arg) {
		Complex a;
		a.m_re = module * cos(arg);
		a.m_im = module * sin(arg);
		return a;
	}
	static Complex FromAlgebraicForm(double real, double im) {
		Complex a{ real, im };
		return a;
	}
	double Re() const {
		return m_re;
	}
	double Im() const {
		return m_im;
	}
	double Mod() const {
		return sqrt(m_re * m_re + m_im * m_im);
	}
	double Arg() const {
		return atan2(m_im, m_re);
	}
	explicit operator double() const {
		return m_re;
	}
	Complex operator- () {
		Complex a{ *this };
		a.m_im *= -1;
		a.m_re *= -1;
		return a;
	}
	Complex& operator++ () {
		m_re++;
		return *this;
	}
	Complex operator++ (int d) {
		Complex temp(*this);
		++(*this);
		return temp;
	}
	Complex& operator-- () {
		m_re--;
		return *this;
	}
	Complex operator-- (int d) {
		Complex temp(*this);
		--(*this);
		return temp;
	}
	Complex& operator+=(Complex a) {
		m_re += a.m_re;
		m_im += a.m_im;
		return *this;
	}
	Complex& operator-=(Complex a) {
		m_re -= a.m_re;
		m_im -= a.m_im;
		return *this;
	}
	Complex& operator*=(Complex a) {
		double real = m_re;
		double im = m_im;
		m_re = real * a.m_re - im * a.m_im;
		m_im = real * a.m_im + im * a.m_re;
		return *this;
	}
	Complex& operator/=(Complex a) {
		double real1 = m_re, real2 = a.m_re;
		double im1 = m_im, im2 = a.m_im;
		m_re = (real1 * real2 + im1 * im2) / (real2 * real2 + im2 * im2);
		m_im = (real2 * im1 - real1 * im2) / (real2 * real2 + im2 * im2);
		return *this;
	}
	friend Complex operator+ (const Complex& lhs, const Complex& rhs);
	friend Complex operator- (const Complex& lhs, const Complex& rhs);
	friend Complex operator* (const Complex& lhs, const Complex& rhs);
	friend Complex operator/ (const Complex& lhs, const Complex& rhs);
	friend std::ostream& operator<<(std::ostream& stream, const Complex& instance);
	friend Complex operator ""i(long double im);
	friend Complex operator ""i(unsigned long long im);
	friend Complex pow(const Complex&, double);
	friend Complex cos(const Complex&);
};


export Complex pow(const Complex& obj, double exp) {
	Complex newObj = obj;

	for (int i = 0; i <= abs(exp); ++i) {
		newObj *= obj;
	}
	return newObj;
}

export Complex operator+(const Complex& lhs, const Complex& rhs)
{
	return Complex(lhs.m_re + rhs.m_re, lhs.m_im + rhs.m_im);
}

export Complex operator-(const Complex& lhs, const Complex& rhs)
{
	return Complex(lhs.m_re - rhs.m_re, lhs.m_im - rhs.m_im);
}

export Complex cos(const Complex& obj) {
	Complex newObj = obj;
	return Complex(cos((double)newObj));
}

export Complex operator*(const Complex& lhs, const Complex& rhs)
{
	double real = lhs.m_re * rhs.m_re - lhs.m_im * rhs.m_im;
	double im = lhs.m_re * rhs.m_im + lhs.m_im * rhs.m_re;
	return Complex(real, im);
}

export Complex operator/(const Complex& lhs, const Complex& rhs)
{
	double real1 = lhs.m_re, real2 = rhs.m_re, real;
	double im1 = lhs.m_im, im2 = rhs.m_im, im;
	real = (real1 * real2 + im1 * im2) / (real2 * real2 + im2 * im2);
	im = (real2 * im1 - real1 * im2) / (real2 * real2 + im2 * im2);
	return Complex(real, im);
}

export Complex operator ""i(unsigned long long im) {
	return Complex(0.0, static_cast<double>(im));
}
export Complex operator ""i(long double im) {
	return Complex(0.0, static_cast<double>(im));
}
export std::ostream& operator<<(std::ostream& stream, const Complex& instance) {
	if (instance.m_im < 0) {
		stream << instance.m_re << " " << instance.m_im << "i";
	}
	else {
		stream << instance.m_re << " +" << instance.m_im << "i";
	}
	return stream;
}

export int FindGreatestCommonDivisor(int a, int b) {
	if (a < 0) {
		a *= -1;
	}
	if (b < 0) {
		b *= -1;
	}
	while (a != 0 && b != 0) {
		if (a > b) {
			a %= b;
		}
		else {
			b %= a;
		}
	}
	return a + b;
}

export int FindLeastCommonMultiple(int a, int b) {
	return abs(a * b) / FindGreatestCommonDivisor(a, b);
}

export class Rational {
	int m_nominator;
	int m_denominaotor;
	void normalize() {
		int nod = FindGreatestCommonDivisor(m_nominator, m_denominaotor);
		m_nominator /= nod;
		m_denominaotor /= nod;
		if (m_denominaotor < 0) {
			m_denominaotor *= -1;
			m_nominator *= -1;
		}
	}
public:
	Rational() {
		m_nominator = 0;
		m_denominaotor = 1;
	}
	Rational(int nominator, int denominator) {
		m_denominaotor = denominator;
		m_nominator = nominator;
		normalize();
	}
	Rational(int nominator) {
		m_nominator = nominator;
		m_denominaotor = 1;
	}
	int Nominator() const {
		return m_nominator;
	}
	int Denominator() const {
		return m_denominaotor;
	}
	explicit operator double() const {
		return double(m_nominator) / m_denominaotor;
	}
	explicit operator int() const {
		return m_nominator / m_denominaotor;
	}
	Rational operator-() {
		Rational temp(*this);
		temp.m_nominator *= -1;
		return temp;
	}
	Rational& operator++ () {
		m_nominator += m_denominaotor;
		return *this;
	}
	Rational operator++ (int d) {
		Rational temp(*this);
		(*this).m_nominator += m_denominaotor;
		temp.normalize();
		return temp;
	}
	Rational& operator-- () {
		m_nominator -= m_denominaotor;
		normalize();
		return *this;
	}
	Rational operator-- (int d) {
		Rational temp(*this);
		(*this).m_nominator -= m_denominaotor;
		return temp;
	}
	Rational& operator+=(Rational a) {
		int new_den = FindLeastCommonMultiple(m_denominaotor, a.m_denominaotor);
		m_nominator = new_den / m_denominaotor * m_nominator;
		m_nominator += new_den / a.m_denominaotor * a.m_nominator;
		m_denominaotor = new_den;
		normalize();
		return *this;
	}
	Rational& operator-=(Rational a) {
		int new_d = FindGreatestCommonDivisor(m_denominaotor, a.m_denominaotor);
		m_nominator = new_d / m_denominaotor * m_nominator;
		m_nominator -= new_d / a.m_denominaotor * a.m_nominator;
		m_denominaotor = new_d;
		normalize();
		return *this;
	}
	Rational& operator*=(Rational a) {
		m_denominaotor *= a.m_denominaotor;
		m_nominator *= a.m_nominator;
		normalize();
		return *this;
	}
	Rational& operator/=(Rational a) {
		m_denominaotor *= a.m_nominator;
		m_nominator *= a.m_denominaotor;
		normalize();
		return *this;
	}
	friend Rational operator+ (const Rational& lhs, const Rational& rhs);
	friend Rational operator- (const Rational& lhs, const Rational& rhs);
	friend Rational operator* (const Rational& lhs, const Rational& rhs);
	friend Rational operator/(const Rational& lhs, const Rational& rhs);
	friend Rational pow(const Rational& base, double exponent);
	friend Rational cos(const Rational& value);
	friend bool operator==(const Rational& lhs, const Rational& rhs);
	friend bool operator>(const Rational& lhs, const Rational& rhs);
	friend bool operator<(const Rational& lhs, const Rational& rhs);
	friend bool operator>=(const Rational& lhs, const Rational& rhs);
	friend bool operator<=(const Rational& lhs, const Rational& rhs);
	friend std::ostream& operator<<(std::ostream& stream, const Rational& instance);
};

export Rational pow(const Rational& obj, double exp) {
	Rational newObj = obj;

	for (int i = 0; i <= abs(exp); ++i) {
		newObj *= obj;
	}
	return newObj;
}

export Rational operator+ (const Rational& lhs, const Rational& rhs) {
	int denominator = FindLeastCommonMultiple(lhs.m_denominaotor, rhs.m_denominaotor);
	int nominator = denominator / lhs.m_denominaotor * lhs.m_nominator;
	nominator += denominator / rhs.m_denominaotor * rhs.m_nominator;
	return Rational{ nominator, denominator };
}

export Rational operator-(const Rational& lhs, const Rational& rhs)
{
	int denominator = FindLeastCommonMultiple(lhs.m_denominaotor, rhs.m_denominaotor);
	int nominator = denominator / lhs.m_denominaotor * lhs.m_nominator;
	nominator -= denominator / rhs.m_denominaotor * rhs.m_nominator;
	return Rational{ nominator, denominator };
}

export Rational operator*(const Rational& lhs, const Rational& rhs)
{
	return Rational{ lhs.m_nominator * rhs.m_nominator, rhs.m_denominaotor * lhs.m_denominaotor };
}

export Rational operator/(const Rational& lhs, const Rational& rhs)
{
	return Rational{ lhs.m_nominator * rhs.m_denominaotor,lhs.m_denominaotor * rhs.m_nominator };
}

export bool operator==(const Rational& lhs, const Rational& rhs)
{
	return lhs.m_nominator == rhs.m_nominator && lhs.m_denominaotor == rhs.m_denominaotor;
}

export Rational cos(const Rational& value) {
	double result = cos((double)value);
	double intPart;
	double fracPart = modf(result, &intPart);

	int num = (int)intPart;
	int denom = (int)(1.0 / fracPart);

	return Rational(num, denom);
}

export bool operator>(const Rational& lhs, const Rational& rhs)
{
	int den = FindLeastCommonMultiple(lhs.m_denominaotor, rhs.m_denominaotor);
	return den / lhs.m_denominaotor * lhs.m_nominator > den / rhs.m_denominaotor * rhs.m_nominator;
}
export bool operator<(const Rational& lhs, const Rational& rhs)
{
	int den = FindLeastCommonMultiple(lhs.m_denominaotor, rhs.m_denominaotor);
	return den / lhs.m_denominaotor * lhs.m_nominator < den / rhs.m_denominaotor * rhs.m_nominator;
}
export bool operator>=(const Rational& lhs, const Rational& rhs)
{
	int den = FindLeastCommonMultiple(lhs.m_denominaotor, rhs.m_denominaotor);
	return den / lhs.m_denominaotor * lhs.m_nominator >= den / rhs.m_denominaotor * rhs.m_nominator;
}
export bool operator<=(const Rational& lhs, const Rational& rhs)
{
	int den = FindLeastCommonMultiple(lhs.m_denominaotor, rhs.m_denominaotor);
	return den / lhs.m_denominaotor * lhs.m_nominator <= den / rhs.m_denominaotor * rhs.m_nominator;
}

export std::ostream& operator<<(std::ostream& stream, const Rational& instance) {
	stream << instance.m_nominator << "/" << instance.m_denominaotor;
	return stream;
}

export Complex f(const Complex& u) {
	Complex a = Complex(1.0, 0.0);
	return a*pow(u,2)-cos(2*u);
}

export Rational f(const Rational& u) {
	Rational a(1, 1);
	return a * pow(u, 2) - cos(2 * u);
}

export double f(const double& u) {
	double a = 1.0;
	return a * pow(u, 2) - cos(2 * u);
}

