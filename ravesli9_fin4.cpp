// ravesli9_fin4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>

using namespace std;

class FixedPoint
{
public:
	FixedPoint(int16_t x = 0, int8_t y = 0, bool min = false):a((x<0)?(-x):x), b((y<0)?(-y):(y)), minus(min)
	{
		if (x < 0 || y < 0)
			minus = true;
	};
	FixedPoint(double n)
	{
		if (n < 0)
		{
			minus = true;
			n = -n;
		}
		else
		{
			minus = false;
		}
		a = static_cast<int16_t>(n);
		n -= a;
		n *= 100;
		b = round(n);
	}
	~FixedPoint() {};
	friend ostream& operator<<(ostream& out, const FixedPoint& num)
	{
		if (num.minus)
			out << "-";
		out << num.a << ".";
		if (num.b < 10)
			out << "0";
		out << (int)num.b;
		return out;
	}
	friend istream& operator>>(istream& in, FixedPoint& num)
	{
		double tmp;
		in >> tmp;
		num = FixedPoint(tmp);
		return in;
	}
	FixedPoint operator-()
	{
		return FixedPoint(a, b, !minus);
	}
	friend FixedPoint operator+(const FixedPoint& num1, const FixedPoint& num2)
	{
		return FixedPoint(static_cast<double>(num1)+ static_cast<double>(num2));
	}
	operator double() const
	{
		if (minus)
			return (-1) * (a + b / 100.0);
		else
			return (a + b / 100.0);
	}
	friend bool operator==(const FixedPoint& num1, const FixedPoint& num2)
	{
		if ((num1.a == num2.a) && (num1.b == num2.b) && (num1.minus == num2.minus))
			return true;
		return false;
	}
private:
	int16_t a;
	int8_t b;
	bool minus;

};

void SomeTest()
{
	std::cout << std::boolalpha;
	std::cout << (FixedPoint(0.75) + FixedPoint(1.23) == FixedPoint(1.98)) << '\n'; // оба значения положительные, никакого переполнения
	std::cout << (FixedPoint(0.75) + FixedPoint(1.50) == FixedPoint(2.25)) << '\n'; // оба значения положительные, переполнение
	std::cout << (FixedPoint(-0.75) + FixedPoint(-1.23) == FixedPoint(-1.98)) << '\n'; // оба значения отрицательные, никакого переполнения
	std::cout << (FixedPoint(-0.75) + FixedPoint(-1.50) == FixedPoint(-2.25)) << '\n'; // оба значения отрицательные, переполнение
	std::cout << (FixedPoint(0.75) + FixedPoint(-1.23) == FixedPoint(-0.48)) << '\n'; // второе значение отрицательное, никакого переполнения
	std::cout << (FixedPoint(0.75) + FixedPoint(-1.50) == FixedPoint(-0.75)) << '\n'; // второе значение отрицательное, возможно переполнение
	std::cout << (FixedPoint(-0.75) + FixedPoint(1.23) == FixedPoint(0.48)) << '\n'; // первое значение отрицательное, никакого переполнения
	std::cout << (FixedPoint(-0.75) + FixedPoint(1.50) == FixedPoint(0.75)) << '\n'; // первое значение отрицательное, возможно переполнение
}

int main()
{
	SomeTest();

	FixedPoint a(-0.48);
	std::cout << a << '\n';

	std::cout << -a << '\n';

	std::cout << "Enter a number: "; // введите 5.678
	std::cin >> a;

	std::cout << "You entered: " << a << '\n';

	return 0;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
