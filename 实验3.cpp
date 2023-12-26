#include <iostream>
#include <cmath>
//ģ���������
template <typename T>
class Complex {
private:
	//ʵ�����鲿
	T real;
	T imag;
public:
	Complex(T r = 0.0, T i = 0.0) : real(r), imag(i) {} // ���캯��
	Complex(const Complex& other) : real(other.real), imag(other.imag) {} // ����
	���캯��
		~Complex() {} // ��������
	T getReal() const { return real; } // ����ʵ��
	T getImag() const { return imag; } // �����鲿
	void setReal(T r) { real = r; } // ����ʵ��
	void setImag(T i) { imag = i; } // �����鲿
	Complex& operator=(const Complex& other); // ��ֵ�����
	Complex operator*(const Complex& other) const; // �˷������
	Complex operator/(const Complex& other) const; // ���������
	bool operator==(const Complex& other) const; // ��������
	template <typename U>
	friend std::ostream& operator<<(std::ostream& out, const Complex<U>& c); //
	��������
};
//���ڷ�����ʵ��
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
	// ���ڸ������ľ������⣬ͨ������ֱ�ӱȽ������������Ƿ����
	// ����ʹ��һ��С����ֵ���ж����������Ƿ���ȡ�
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