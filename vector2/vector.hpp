#pragma once
class Vector final {
public:
	Vector(void);
	explicit Vector(double x, double y);

public:
	Vector(const Vector& that) = default;
	Vector& operator =(const Vector& that) = default;

public:
	static Vector makePolar(double rad, double alpha);

public:
	double x(void) const;
	double y(void) const;
	void x(double newX);
	void y(double newY);

public:
	Vector operator + (const Vector& that) const;
	Vector operator - (const Vector& that) const;
	double operator * (const Vector& that) const;
	Vector operator * (const double& that) const;
	Vector operator / (const double& that) const;

public:
	Vector& operator += (const Vector& that);
	Vector& operator -= (const Vector& that);
	Vector& operator *= (const double& that);
	Vector& operator /= (const double& that);

public:
	Vector operator -() const;

public:
	bool operator == (const Vector& that) const = default;
	bool operator != (const Vector& that) const;

public:
	Vector& rotate(double angle);
	Vector& rotate(int quad);
	double module2(void) const;
	double angle(void) const;
	double angle(const Vector& that) const;
	double length(void) const;
	double projection(const Vector& base) const;
	Vector& normalize(void);
	Vector& transformTo(const Vector& e1, const Vector& e2);
	Vector& transformFrom(const Vector& e1, const Vector& e2);

private:
	double _x;
	double _y;
};

Vector operator * (const double& lhs, const Vector& rhs);

Vector rotate(const Vector& v, double angle);
Vector rotate(const Vector& v, int quad);
double module2(const Vector& v);
double length(const Vector& v);
double angle(const Vector& v);
double angle(const Vector& v1, const Vector& v2);
double projection(const Vector& v, const Vector& base);
Vector normalize(const Vector& v);
Vector transformTo(const Vector& v, const Vector& e1, const Vector& e2);
Vector transformFrom(const Vector& v, const Vector& e1, const Vector& e2);

