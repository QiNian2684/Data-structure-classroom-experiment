#include <iostream>
#include <cmath>
//模板类的声明
template <typename T>
class Complex {
private:
	//实部和虚部
	T real;
	T imag;
public:
	Complex(T r = 0.0, T i = 0.0) : real(r), imag(i) {} // 构造函数
	Complex(const Complex& other) : real(other.real), imag(other.imag) {} // 拷贝
	构造函数
		~Complex() {} // 析构函数
	T getReal() const { return real; } // 返回实部
	T getImag() const { return imag; } // 返回虚部
	void setReal(T r) { real = r; } // 设置实部
	void setImag(T i) { imag = i; } // 设置虚部
	Complex& operator=(const Complex& other); // 赋值运算符
	Complex operator*(const Complex& other) const; // 乘法运算符
	Complex operator/(const Complex& other) const; // 除法运算符
	bool operator==(const Complex& other) const; // 相等运算符
	template <typename U>
	friend std::ostream& operator<<(std::ostream& out, const Complex<U>& c); //
	输出运算符
};
//类内方法的实现
template <typename T>
Complex<T>& Complex<T>::operator=(const Complex<T>& other) {
	if (this != &other) {
		real = other.real;
		imag = other.imag;
	}
	return *this;
}
template <typename T>
Complex<T> Complex<T>::operator*(const Complex<T>& other) const {
	return Complex<T>(real * other.real - imag * other.imag, real * other.imag +
		imag * other.real);
}
template <typename T>
Complex<T> Complex<T>::operator/(const Complex<T>& other) const {
	T denominator = other.real * other.real + other.imag * other.imag;
	if (denominator == 0) {
		3
			throw std::runtime_error("Attempted to divide by zero");
	}
	return Complex<T>((real * other.real + imag * other.imag) / denominator,
		(imag * other.real - real * other.imag) / denominator);
}
template <typename T>
bool Complex<T>::operator==(const Complex<T>& other) const {
	// 由于浮点数的精度问题，通常不能直接比较两个浮点数是否相等
	// 这里使用一个小的阈值来判断两个复数是否“相等”
	return std::abs(real - other.real) < 1e-9 && std::abs(imag - other.imag) <
		1e-9;
}
template <typename T>
std::ostream& operator<<(std::ostream& out, const Complex<T>& c) {
	out << '(' << c.getReal() << ',' << c.getImag() << ')';
	return out;
}
template<class T>
void bubble(T a[], int size, bool (*fp)(T& a, T& b))