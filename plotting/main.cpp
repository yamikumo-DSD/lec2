#include <iostream>

class Vector
{
private:
	double x_, y_;
public:
	constexpr Vector(double _x, double _y) :x_(_x),y_(_y) {}
	virtual ~Vector(void) {}

	void x(double _x) { x_ = _x; }
	void y(double _y) { y_ = _y; }
	constexpr double x(void) const { return x_; }
	constexpr double y(void) const { return y_; }

	//Operator overloadings.
	friend std::ostream& operator<<(std::ostream& _ost, const Vector& _val)
	{
		_ost << "(x, y) = " << '(' << _val.x_ << ", " << _val.y_ << ")";
		return _ost;
	}
	Vector operator+(const Vector& _rhs) const { return Vector(x_ + _rhs.x_, y_ + _rhs.y_); }
	Vector operator-(const Vector& _rhs) const { return Vector(x_ - _rhs.x_, y_ - _rhs.y_); }
	Vector& operator+=(const Vector& _rhs) 
	{
		*this = *this + _rhs;
		return *this;
	}
	Vector& operator-=(const Vector& _rhs) 
	{
		*this = *this - _rhs;
		return *this;
	}
	friend Vector operator*(double _k, const Vector& _p) { return Vector(_k * _p.x_, _k * _p.y_); }
};

class Point    : public Vector { using Vector::Vector; };
class Force    : public Vector { using Vector::Vector; };
class Velocity : public Vector { using Vector::Vector; };

class MassPoint : public Point
{
private:
	//Momentum
	double m;
	Velocity velocity;
public:
	MassPoint(double _m, Velocity _velocity, const Point& _p) :velocity(_velocity), Point(_p), m(_m) {}
	void move(double _duration/*sec*/)
	{
		*this += _duration * velocity;
	}
	void apply(const Force& _force, double _duration/*sec*/)
	{
		static constexpr double dt{0.0001};
		const auto accele{ (1 / m) * _force };
		for (;_duration > 0; _duration -= dt)
		{
			velocity += (dt * accele);
			move(dt);
		}
	}
};

#include <iostream>
#include <cmath>

int main(void)
{
	static constexpr double PI{ 3.141592 };
	static constexpr double G {9.8};
	static constexpr double M {1.0};
	static constexpr double V0 {50};

	MassPoint mass{M, Velocity(V0 * std::cos(PI / 4), V0 * std::cos(PI / 4)), Point(0, 0)};
	for (int i = 0; i != 100; ++i)
	{
		mass.apply(Force(0, -M * G), 0.1);
		std::cout << mass << std::endl;
	}

	std::cin.get();
}