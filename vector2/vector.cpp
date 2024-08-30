#define _USE_MATH_DEFINES
#include <cmath>
#include "vector.hpp"

static const double epsilon = 0.0000001;

Vector::Vector(void) {
	_x = 0;
	_y = 0;
}

Vector::Vector(double x, double y) {
	_x = x;
	_y = y;
}

Vector Vector::makePolar(double rad, double alpha) {
	Vector vector(rad * cos(alpha), rad * sin(alpha));
	return vector;
}

double Vector::x(void) const {
	return _x;
}
double Vector::y(void) const {
	return _y;
}

void Vector::x(double newX) {
	_x = newX;
}

void Vector::y(double newY) {
	_y = newY;
}

Vector Vector:: operator + (const Vector& that) const {
	Vector vector = *this;
	return vector += that;
}

Vector Vector::operator - (const Vector& that) const {
	Vector vector = *this;
	return vector -= that;
}

double Vector::operator * (const Vector& that) const {
	double multiplication = _x * that._x + _y * that._y;
	return multiplication;
}

Vector Vector::operator * (const double& that) const {
	Vector vector = *this;
	return vector *= that;
}

Vector Vector::operator / (const double& that) const {
	Vector vector = *this;
	return vector /= that;
}

Vector& Vector::operator += (const Vector& that) {
	_x = _x + that._x;
	_y = _y + that._y;
	return *this;
}

Vector& Vector::operator -= (const Vector& that) {
	_x = _x - that._x;
	_y = _y - that._y;
	return *this;
}

Vector& Vector::operator *= (const double& that) {
	_x = _x * that;
	_y = _y * that;
	return *this;
}

Vector& Vector::operator /= (const double& that) {
	_x = _x / that;
	_y = _y / that;
	return *this;
}

Vector Vector::operator -() const {
	return Vector(-_x, -_y);
}

bool Vector::operator != (const Vector& that)  const {
	return !(*this == that);
}

Vector& Vector::rotate(double angle) {
	*this = makePolar(this->length(), this->angle() + angle);
	return *this;
}

Vector& Vector::rotate(int quad) {
	while (quad < 0) {
		quad = quad + 4;
	}
	if (quad % 2 == 0) {
		if (quad % 4 == 0) {
			return *this;
		}
		else {
			_x = -_x;
			_y = -_y;
			return *this;
		}
	}
	quad++;
	double coordinate = _x;
	if (quad % 4 == 0) {
		_x = _y;
		_y = -coordinate;
		return *this;
	}
	else {
		_x = -_y;
		_y = coordinate;
		return *this;
	}
}

double Vector::module2(void)  const {
	return _x * _x + _y * _y;
}

double Vector::angle(void) const {
	double result = atan2(_y, _x);
	if (result == -M_PI) {
		return -result;
	}
	return result;
}

double Vector::angle(const Vector& that)  const {
	double angle = this->angle() - that.angle();
	if (angle > M_PI) {
		angle = angle - 2 * M_PI;
	}
	if (angle < -M_PI) {
		angle = angle + 2 * M_PI;
	}
	return angle;
}

double Vector::length(void)  const {
	return sqrt(module2());
}

double Vector::projection(const Vector& base) const {
	return this->length() * cos(this->angle(base));
}

Vector& Vector::normalize(void) {
	return (*this) /= this->length();
}

Vector& Vector::transformTo(const Vector& e1, const Vector& e2) {
	double detMatrix = e1._x * e2._y - e2._x * e1._y;
	if (abs(detMatrix) < epsilon) {
		return *this;
	}
	double inverseMatrix[2][2];
	inverseMatrix[0][0] = e2._y / detMatrix;
	inverseMatrix[0][1] = -e1._y / detMatrix;
	inverseMatrix[1][0] = -e2._x / detMatrix;
	inverseMatrix[1][1] = e1._x / detMatrix;
	double coordinate = _x;
	_x = inverseMatrix[0][0] * _x + inverseMatrix[1][0] * _y;
	_y = inverseMatrix[0][1] * coordinate + inverseMatrix[1][1] * _y;
	return *this;
}

Vector& Vector::transformFrom(const Vector& e1, const Vector& e2) {
	double Matrix_coeff[2][2];
	Matrix_coeff[0][0] = e1._x;
	Matrix_coeff[0][1] = e2._x;
	Matrix_coeff[1][0] = e1._y;
	Matrix_coeff[1][1] = e2._y;
	double coordinate = _x;
	_x = Matrix_coeff[0][0] * _x + Matrix_coeff[0][1] * _y;
	_y = Matrix_coeff[1][0] * coordinate + Matrix_coeff[1][1] * _y;
	return *this;
}

Vector operator * (const double& lhs, const Vector& rhs) {
	return rhs * lhs;
}

Vector rotate(const Vector& v, double angle) {
	Vector vector = v;
	return vector.rotate(angle);
}

Vector rotate(const Vector& v, int quad) {
	Vector vector = v;
	return vector.rotate(quad);
}

double module2(const Vector& v) {
	return v.module2();
}

double length(const Vector& v) {
	return v.length();
}

double angle(const Vector& v) {
	return v.angle();
}

double angle(const Vector& v1, const Vector& v2) {
	return v1.angle(v2);
}

double projection(const Vector& v, const Vector& base) {
	return v.projection(base);
}

Vector normalize(const Vector& v) {
	Vector vector = v;
	return vector.normalize();
}

Vector transformTo(const Vector& v, const Vector& e1, const Vector& e2) {
	Vector vector = v;
	return vector.transformTo(e1, e2);
}

Vector transformFrom(const Vector& v, const Vector& e1, const Vector& e2) {
	Vector vector = v;
	return vector.transformFrom(e1, e2);
}