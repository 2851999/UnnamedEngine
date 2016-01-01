/*****************************************************************************
 *
 *   Copyright 2015 - 2016 Joel Davies
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *****************************************************************************/

#ifndef CORE_VECTOR_H_
#define CORE_VECTOR_H_

#include "../utils/StringUtils.h"

/***************************************************************************************************
 * Vector class along with a few implementations
 ***************************************************************************************************/

template<typename T, unsigned int N>
class Vector {
private:
	T m_values[N];
public:
	Vector() {}
	//virtual ~Vector() { delete[] m_values; }

	T operator[](int a) const { return m_values[a]; }
	T& operator[](int a) { return m_values[a]; }
	inline Vector<T,N> operator+(Vector<T, N> vector) {
		Vector<T,N> result;
		for (int a = 0; a < N; a++)
			result[a] = m_values[a] + vector[a];
		return result;
	}
	inline Vector<T,N> operator-(Vector<T, N> vector) {
		Vector<T,N> result;
		for (int a = 0; a < N; a++)
			result[a] = m_values[a] - vector[a];
		return result;
	}
	inline Vector<T,N> operator*(Vector<T, N> vector) {
		Vector<T,N> result;
		for (int a = 0; a < N; a++)
			result[a] = m_values[a] * vector[a];
		return result;
	}
	inline Vector<T,N> operator/(Vector<T, N> vector) {
		Vector<T,N> result;
		for (int a = 0; a < N; a++)
			result[a] = m_values[a] / vector[a];
		return result;
	}

	inline Vector<T,N> operator+=(Vector<T, N> vector) {
		for (int a = 0; a < N; a++)
			m_values[a] = m_values[a] + vector[a];
		return (*this);
	}
	inline Vector<T,N> operator-=(Vector<T, N> vector) {
		for (int a = 0; a < N; a++)
			m_values[a] = m_values[a] - vector[a];
		return (*this);
	}
	inline Vector<T,N> operator*=(Vector<T, N> vector) {
		for (int a = 0; a < N; a++)
			m_values[a] = m_values[a] * vector[a];
		return (*this);
	}
	inline Vector<T,N> operator/=(Vector<T, N> vector) {
		for (int a = 0; a < N; a++)
			m_values[a] = m_values[a] / vector[a];
		return (*this);
	}
	inline Vector<T,N> operator+(T value) {
		Vector<T,N> result;
		for (int a = 0; a < N; a++)
			result[a] = m_values[a] + value;
		return result;
	}
	inline Vector<T,N> operator-(T value) {
		Vector<T,N> result;
		for (int a = 0; a < N; a++)
			result[a] = m_values[a] - value;
		return result;
	}
	inline Vector<T,N> operator*(T value) {
		Vector<T,N> result;
		for (int a = 0; a < N; a++)
			result[a] = m_values[a] * value;
		return result;
	}
	inline Vector<T,N> operator/(T value) {
		Vector<T,N> result;
		for (int a = 0; a < N; a++)
			result[a] = m_values[a] / value;
		return result;
	}

	inline Vector<T,N> operator+=(T value) {
		for (int a = 0; a < N; a++)
			m_values[a] = m_values[a] + value;
		return (*this);
	}
	inline Vector<T,N> operator-=(T value) {
		for (int a = 0; a < N; a++)
			m_values[a] = m_values[a] - value;
		return (*this);
	}
	inline Vector<T,N> operator*=(T value) {
		for (int a = 0; a < N; a++)
			m_values[a] = m_values[a] * value;
		return (*this);
	}
	inline Vector<T,N> operator/=(T value) {
		for (int a = 0; a < N; a++)
			m_values[a] = m_values[a] / value;
		return (*this);
	}

	inline T minV() {
		T min = m_values[0];
		for (int a = 1; a < N; a++) {
			if (m_values[a] < min)
				min = m_values[a];
		}
		return min;
	}

	inline T maxV() {
		T max = m_values[0];
		for (int a = 1; a < N; a++) {
			if (m_values[a] > max)
				max = m_values[a];
		}
		return max;
	}

	inline T length() {
		T length;
		for (int a = 0; a < N; a++)
			length += m_values[a] * m_values[a];
		return sqrt(length);
	}

	inline T dot(Vector<T, N> vector) {
		T dot;
		for (int a = 0; a < N; a++)
			dot += m_values[a] * vector[a];
		return dot;
	}

	inline Vector<T, N> normalised() {
		T l = length();
		Vector<T, N> result;
		for (int a = 0; a < N; a++)
			result[a] = m_values[a] / l;
		return result;
	}

	inline std::string toString() {
		std::string value = "(";
		for (unsigned int a = 0; a < N; a++) {
			value += to_string(m_values[a]);
			if (a != N - 1)
				value += ", ";
		}
		value += ")";
		return value;
	}
};

template<typename T>
class Vector2 : public Vector<T, 2> {
public:
	Vector2() {}
	Vector2(T x, T y) {
		(*this)[0] = x;
		(*this)[1] = y;
	}
	inline void setX(T x) { (*this)[0] = x; }
	inline void setY(T y) { (*this)[1] = y; }
	inline T getX() { return (*this)[0]; }
	inline T getY() { return (*this)[1]; }
};

template<typename T>
class Vector3 : public Vector<T, 3> {
public:
	Vector3() {}
	Vector3(T x, T y, T z) {
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
	}
	inline void setX(T x) { (*this)[0] = x; }
	inline void setY(T y) { (*this)[1] = y; }
	inline void setZ(T z) { (*this)[2] = z; }
	inline T getX() { return (*this)[0]; }
	inline T getY() { return (*this)[1]; }
	inline T getZ() { return (*this)[2]; }
};

template<typename T>
class Vector4 : public Vector<T, 4> {
public:
	Vector4() {}
	Vector4(T x, T y, T z, T w) {
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
		(*this)[3] = w;
	}
	inline void setX(T x) { (*this)[0] = x; }
	inline void setY(T y) { (*this)[1] = y; }
	inline void setZ(T z) { (*this)[2] = z; }
	inline void setW(T w) { (*this)[3] = w; }
	inline T getX() { return (*this)[0]; }
	inline T getY() { return (*this)[1]; }
	inline T getZ() { return (*this)[2]; }
	inline T getW() { return (*this)[3]; }
};

class Vector2i : public Vector2<int> {
public:
	Vector2i(int x = 0, int y = 0) : Vector2(x, y) {}
};

class Vector2f : public Vector2<float> {
public:
	Vector2f(float x = 0, float y = 0) : Vector2(x, y) {}
	Vector2f operator+(float value) {
		Vector2f result;
		result[0] = (*this)[0] + value;
		result[1] = (*this)[1] + value;
		return result;
	}
	Vector2f operator-(float value) {
		Vector2f result;
		result[0] = (*this)[0] - value;
		result[1] = (*this)[1] - value;
		return result;
	}
	Vector2f operator*(float value) {
		Vector2f result;
		result[0] = (*this)[0] * value;
		result[1] = (*this)[1] * value;
		return result;
	}
	Vector2f operator/(float value) {
		Vector2f result;
		result[0] = (*this)[0] / value;
		result[1] = (*this)[1] / value;
		return result;
	}
	Vector2f operator+(Vector2f value) {
		Vector2f result;
		result[0] = (*this)[0] + value.getX();
		result[1] = (*this)[1] + value.getY();
		return result;
	}
	Vector2f operator-(Vector2f value) {
		Vector2f result;
		result[0] = (*this)[0] + value.getX();
		result[1] = (*this)[1] + value.getY();
		return result;
	}
	Vector2f operator*(Vector2f value) {
		Vector2f result;
		result[0] = (*this)[0] * value.getX();
		result[1] = (*this)[1] * value.getY();
		return result;
	}
	Vector2f operator/(Vector2f value) {
		Vector2f result;
		result[0] = (*this)[0] / value.getX();
		result[1] = (*this)[1] / value.getY();
		return result;
	}
};

class Vector2d : public Vector2<double> {
public:
	Vector2d(double x = 0, double y = 0) : Vector2(x, y) {}
};

class Vector3i : public Vector3<int> {
public:
	Vector3i(int x = 0, int y = 0, int z = 0) : Vector3(x, y, z) {}
};

class Vector3f : public Vector3<float> {
public:
	Vector3f(float x = 0, float y = 0, float z = 0) : Vector3(x, y, z) {}
	Vector3f operator+(float value) {
		Vector3f result;
		result[0] = (*this)[0] + value;
		result[1] = (*this)[1] + value;
		result[2] = (*this)[2] + value;
		return result;
	}
	Vector3f operator-(float value) {
		Vector3f result;
		result[0] = (*this)[0] - value;
		result[1] = (*this)[1] - value;
		result[2] = (*this)[2] - value;
		return result;
	}
	Vector3f operator*(float value) {
		Vector3f result;
		result[0] = (*this)[0] * value;
		result[1] = (*this)[1] * value;
		result[2] = (*this)[2] * value;
		return result;
	}
	Vector3f operator/(float value) {
		Vector3f result;
		result[0] = (*this)[0] / value;
		result[1] = (*this)[1] / value;
		result[2] = (*this)[2] / value;
		return result;
	}
	Vector3f operator+(Vector3f value) {
		Vector3f result;
		result[0] = (*this)[0] + value.getX();
		result[1] = (*this)[1] + value.getY();
		result[2] = (*this)[2] + value.getZ();
		return result;
	}
	Vector3f operator-(Vector3f value) {
		Vector3f result;
		result[0] = (*this)[0] - value.getX();
		result[1] = (*this)[1] - value.getY();
		result[2] = (*this)[2] - value.getZ();
		return result;
	}
	Vector3f operator*(Vector3f value) {
		Vector3f result;
		result[0] = (*this)[0] * value.getX();
		result[1] = (*this)[1] * value.getY();
		result[2] = (*this)[2] * value.getZ();
		return result;
	}
	Vector3f operator/(Vector3f value) {
		Vector3f result;
		result[0] = (*this)[0] / value.getX();
		result[1] = (*this)[1] / value.getY();
		result[2] = (*this)[2] / value.getZ();
		return result;
	}
};

class Vector3d : public Vector3<double> {
public:
	Vector3d(double x = 0, double y = 0, double z = 0) : Vector3(x, y, z) {}
};

class Vector4i : public Vector4<int> {
public:
	Vector4i(int x = 0, int y = 0, int z = 0, int w = 0) : Vector4(x, y, z, w) {}
};

class Vector4f : public Vector4<float> {
public:
	Vector4f(float x = 0, float y = 0, float z = 0, float w = 0) : Vector4(x, y, z, w) {}
};

class Vector4d : public Vector4<double> {
public:
	Vector4d(double x = 0, double y = 0, double z = 0, double w = 0) : Vector4(x, y, z, w) {}
};

/***************************************************************************************************/

/***************************************************************************************************
 * Colour class
 ***************************************************************************************************/

class Colour : public Vector4f {
public:
	static Colour NONE;
	static Colour BLACK;
	static Colour GREY;
	static Colour LIGHT_GREY;
	static Colour RED;
	static Colour ORANGE;
	static Colour YELLOW;
	static Colour PINK;
	static Colour GREEN;
	static Colour BLUE;
	static Colour LIGHT_BLUE;
	static Colour WHITE;

	static Colour ARRAY_RGB[];
	static Colour ARRAY_GREY[];
	static Colour ARRAY_BLUE[];
	static Colour ARRAY_SUNSET[];

	Colour() : Vector4f(0.0f, 0.0f, 0.0f, 0.0f) {}
	Colour(float r, float g, float b) : Vector4f(r, g, b, 0.0f) {}
	Colour(float r, float g, float b, float a) : Vector4f(r, g, b, a) {}
	Colour(Colour colour, float a) : Vector4f(colour.getR(), colour.getG(), colour.getB(), a) {}
	inline float getR() { return getX(); }
	inline float getG() { return getY(); }
	inline float getB() { return getZ(); }
	inline float getA() { return getW(); }
};

/***************************************************************************************************/

#endif
