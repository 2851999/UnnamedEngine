/*****************************************************************************
 *
 *   Copyright 2015 Joel Davies
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

#ifndef CORE_MATRIX_H_

/***************************************************************************************************
 * Matrix class along with a few implementations
 ***************************************************************************************************/

#include <cstring>
#include "../utils/MathUtils.h"
#include "../utils/StringUtils.h"

template<typename T, unsigned int N>
class Matrix {
public:
	float m_values[N][N];
	Matrix() {
		for (unsigned int a = 0; a < N; a++)
			for (unsigned int b = 0; b < N; b++)
				m_values[a][b] = 0;
	}
	inline const float* operator[](int n) const { return m_values[n]; }
	inline float* operator[](int n) { return m_values[n]; }
	inline Matrix<T, N> operator*(Matrix<T, N> matrix) {
		Matrix<T, N> result;
		//Column (2st)
		for (unsigned int a = 0; a < N; a++) {
			//Row (1nd)
			for (unsigned int b = 0; b < N; b++) {
				result.m_values[a][b] = 0;
				//Column (1st) / Row (2nd)
				for (unsigned int c = 0; c < N; c++) {
					result.m_values[a][b] += m_values[a][c] * matrix.m_values[c][b];
				}
			}
		}
		return result;
	}
	inline Matrix<T, N> setIdentity() {
		for (unsigned int y = 0; y < N; y++) {
			for (unsigned int x = 0; x < N; x++) {
				if (y == x)
					m_values[y][x] = 1;
				else
					m_values[y][x] = 0;
			}
		}
		return (*this);
	}
	inline Matrix<T, N> transpose() {
		Matrix<T, N> result;
		for (unsigned int x = 0; x < N; x++)
			for (unsigned int y = 0; y < N; y++)
				result[x][y] = m_values[y][x];
		return result;
	}
	inline void set(int x, int y, float value) { m_values[x][y] = value; }
	inline float get(int x, int y) { return m_values[x][y]; }

	inline std::string toString() {
		std::string value;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				value += to_string(m_values[y][x]);
				if (x != N - 1)
					value += " ";
				else
					value += "\n";
			}
		}
		return value;
	}
};

template<typename T>
class Matrix3 : public Matrix<T, 3> {

};

class Matrix3f : public Matrix3<float> {
public:
	inline Matrix3f operator*(Matrix3f matrix) {
		Matrix3f result;
		//Column (2st)
		for (unsigned int a = 0; a < 3; a++) {
			//Row (1nd)
			for (unsigned int b = 0; b < 3; b++) {
				result.m_values[a][b] = 0;
				//Column (1st) / Row (2nd)
				for (unsigned int c = 0; c < 3; c++) {
					result.m_values[a][b] += m_values[a][c] * matrix.m_values[c][b];
				}
			}
		}
		return result;
	}

	inline Matrix3f transpose() {
		Matrix3f result;
		for (unsigned int x = 0; x < 3; x++)
			for (unsigned int y = 0; y < 3; y++)
				result[x][y] = m_values[y][x];
		return result;
	}

	inline Matrix3f inverse() {
		Matrix3f result;

		float a = m_values[0][0];
		float b = m_values[0][1];
		float c = m_values[0][2];
		float d = m_values[1][0];
		float e = m_values[1][1];
		float f = m_values[1][2];
		float g = m_values[2][0];
		float h = m_values[2][1];
		float i = m_values[2][2];

		float A = (e * i - f * h);
		float B = -(d * i - f * g);
		float C = (d * h - e * g);
		float D = -(b * i - c * h);
		float E = (a * i - c * g);
		float F = -(a * h - b * g);
		float G = (b * f - c * e);
		float H = -(a * f - c * d);
		float I = (a * e - b * d);

		float invdet = 1.0f / ((a * A) + (b * B) + (c * C));

		result.set(0, 0, invdet * A);
		result.set(0, 1, invdet * D);
		result.set(0, 2, invdet * G);
		result.set(1, 0, invdet * B);
		result.set(1, 1, invdet * E);
		result.set(1, 2, invdet * H);
		result.set(2, 0, invdet * C);
		result.set(2, 1, invdet * F);
		result.set(2, 2, invdet * I);

		return result;
	}
};

template<typename T>
class Matrix4 : public Matrix<T, 4> {

};

class Matrix4f : public Matrix4<float> {
public:

	inline Matrix4f operator*(Matrix4f matrix) {
		Matrix4f result;
		//Column (2st)
		for (unsigned int a = 0; a < 4; a++) {
			//Row (1nd)
			for (unsigned int b = 0; b < 4; b++) {
				result.m_values[a][b] = 0;
				//Column (1st) / Row (2nd)
				for (unsigned int c = 0; c < 4; c++) {
					result.m_values[a][b] += m_values[a][c] * matrix.m_values[c][b];
				}
			}
		}
		return result;
	}

	inline Matrix4f transpose() {
		Matrix4f result;
		for (unsigned int x = 0; x < 4; x++)
			for (unsigned int y = 0; y < 4; y++)
				result[x][y] = m_values[y][x];
		return result;
	}

	/* Initialises an orthographic projection matrix */
	inline Matrix4f initOrthographic(float left, float right, float bottom, float top, float zNear, float zFar) {
		m_values[0][0] = 2.0f / (right - left);
		m_values[0][1] = 0;
		m_values[0][2] = 0;
		m_values[0][3] = -((right + left) / right - left);
		m_values[1][0] = 0;
		m_values[1][1] = 2.0f / (top - bottom);
		m_values[1][2] = 0;
		m_values[1][3] = -((top + bottom) / (top - bottom));
		m_values[2][0] = 0;
		m_values[2][1] = 0;
		m_values[2][2] = -2.0f / (zFar - zNear);
		m_values[2][3] = -((zFar + zNear) / (zFar - zNear));
		m_values[3][0] = 0;
		m_values[3][1] = 0;
		m_values[3][2] = 0;
		m_values[3][3] = 1;
		return (*this);
	}
	/* Initialises a perspective projection matrix */
	inline Matrix4f initPerspective(float fovy, float aspect, float zNear, float zFar) {
		float scale = (tan(fovy / 2 * (PI / 360)));
		float right = aspect * scale;
		float left = -right;
		float top = scale;
		float bottom = -top;
		return initFrustum(left, right, bottom, top, zNear, zFar);
	}
	inline Matrix4f initFrustum(float left, float right, float bottom, float top, float zNear, float zFar) {
		m_values[0][0] = 2 * zNear / (right - left);
		m_values[0][1] = 0;
		m_values[0][2] = 0;
		m_values[0][3] = 0;
		m_values[1][0] = 0;
		m_values[1][1] = 2 * zNear / (top - bottom);
		m_values[1][2] = 0;
		m_values[1][3] = 0;
		m_values[2][0] = (right + left) / (right - left);
		m_values[2][1] = (top + bottom) / (top - bottom);
		m_values[2][2] = -(zFar + zNear) / (zFar - zNear);
		m_values[2][3] = -1;
		m_values[3][0] = 0;
		m_values[3][1] = 0;
		m_values[3][2] = -2 * zFar * zNear / (zFar - zNear);
		m_values[3][3] = 1;
		return (*this);
	}
	inline Matrix4f initTranslation(Vector2f vector) {
		m_values[0][0] = 1;
		m_values[0][1] = 0;
		m_values[0][2] = 0;
		m_values[0][3] = vector.getX();
		m_values[1][0] = 0;
		m_values[1][1] = 1;
		m_values[1][2] = 0;
		m_values[1][3] = vector.getY();
		m_values[2][0] = 0;
		m_values[2][1] = 0;
		m_values[2][2] = 1;
		m_values[2][3] = 0;
		m_values[3][0] = 0;
		m_values[3][1] = 0;
		m_values[3][2] = 0;
		m_values[3][3] = 1;
		return (*this);
	}
	inline Matrix4f initTranslation(Vector3f vector) {
		m_values[0][0] = 1;
		m_values[0][1] = 0;
		m_values[0][2] = 0;
		m_values[0][3] = vector.getX();
		m_values[1][0] = 0;
		m_values[1][1] = 1;
		m_values[1][2] = 0;
		m_values[1][3] = vector.getY();
		m_values[2][0] = 0;
		m_values[2][1] = 0;
		m_values[2][2] = 1;
		m_values[2][3] = vector.getZ();
		m_values[3][0] = 0;
		m_values[3][1] = 0;
		m_values[3][2] = 0;
		m_values[3][3] = 1;
		return (*this);
	}
	inline Matrix4f initRotation(float angle, int x, int y, int z) {
		float c = (float) cos(to_radians(angle));
		float s = (float) sin(to_radians(angle));
		if (x == 1) {
			m_values[0][0] = 1;
			m_values[0][1] = 0;
			m_values[0][2] = 0;
			m_values[0][3] = 0;
			m_values[1][0] = 0;
			m_values[1][1] = c;
			m_values[1][2] = -s;
			m_values[1][3] = 0;
			m_values[2][0] = 0;
			m_values[2][1] = s;
			m_values[2][2] = c;
			m_values[2][3] = 0;
			m_values[3][0] = 0;
			m_values[3][1] = 0;
			m_values[3][2] = 0;
			m_values[3][3] = 1;
		} else if (y == 1) {
			m_values[0][0] = c;
			m_values[0][1] = 0;
			m_values[0][2] = s;
			m_values[0][3] = 0;
			m_values[1][0] = 0;
			m_values[1][1] = 1;
			m_values[1][2] = 0;
			m_values[1][3] = 0;
			m_values[2][0] = -s;
			m_values[2][1] = 0;
			m_values[2][2] = c;
			m_values[2][3] = 0;
			m_values[3][0] = 0;
			m_values[3][1] = 0;
			m_values[3][2] = 0;
			m_values[3][3] = 1;
		} else if (z == 1) {
			m_values[0][0] = c;
			m_values[0][1] = -s;
			m_values[0][2] = 0;
			m_values[0][3] = 0;
			m_values[1][0] = s;
			m_values[1][1] = c;
			m_values[1][2] = 0;
			m_values[1][3] = 0;
			m_values[2][0] = 0;
			m_values[2][1] = 0;
			m_values[2][2] = 1;
			m_values[2][3] = 0;
			m_values[3][0] = 0;
			m_values[3][1] = 0;
			m_values[3][2] = 0;
			m_values[3][3] = 1;
		}
		return (*this);
	}
	inline Matrix4f initScale(Vector2f vector) {
		m_values[0][0] = vector.getX();
		m_values[0][1] = 0;
		m_values[0][2] = 0;
		m_values[0][3] = 0;
		m_values[1][0] = 0;
		m_values[1][1] = vector.getY();
		m_values[1][2] = 0;
		m_values[1][3] = 0;
		m_values[2][0] = 0;
		m_values[2][1] = 0;
		m_values[2][2] = 1;
		m_values[2][3] = 0;
		m_values[3][0] = 0;
		m_values[3][1] = 0;
		m_values[3][2] = 0;
		m_values[3][3] = 1;
		return (*this);
	}
	inline Matrix4f initScale(Vector3f vector) {
		m_values[0][0] = vector.getX();
		m_values[0][1] = 0;
		m_values[0][2] = 0;
		m_values[0][3] = 0;
		m_values[1][0] = 0;
		m_values[1][1] = vector.getY();
		m_values[1][2] = 0;
		m_values[1][3] = 0;
		m_values[2][0] = 0;
		m_values[2][1] = 0;
		m_values[2][2] = vector.getZ();
		m_values[2][3] = 0;
		m_values[3][0] = 0;
		m_values[3][1] = 0;
		m_values[3][2] = 0;
		m_values[3][3] = 1;
		return (*this);
	}
	inline Matrix4f initIdentity() {
		setIdentity();
		return (*this);
	}
	inline void translate(Vector2f vector) {
		Matrix4f t = Matrix4f();
		t.initTranslation(vector);
		Matrix<float, 4> n = ((*this) * t);
		std::memcpy(m_values, n.m_values, sizeof(float) * 16);
	}
	inline void translate(Vector3f vector) {
		Matrix4f t = Matrix4f();
		t.initTranslation(vector);
		Matrix<float, 4> n = ((*this) * t);
		std::memcpy(m_values, n.m_values, sizeof(float) * 16);
	}
	inline void rotate(float angle, int x, int y, int z) {
		Matrix4f t = Matrix4f();
		t.initRotation(angle, x, y, z);
		Matrix<float, 4> n = ((*this) * t);
		std::memcpy(m_values, n.m_values, sizeof(float) * 16);
	}
	inline void rotate(float angle) {
		rotate(angle, 0, 0, 1);
	}
	inline void rotate(Vector2f angles) {
		rotate(angles.getX(), 1, 0, 0);
		rotate(angles.getY(), 0, 1, 0);
	}
	inline void rotate(Vector3f angles) {
		rotate(angles.getX(), 1, 0, 0);
		rotate(angles.getY(), 0, 1, 0);
		rotate(angles.getZ(), 0, 0, 1);
	}
	inline void scale(Vector2f vector) {
		Matrix4f t = Matrix4f();
		t.initScale(vector);
		Matrix<float, 4> n = ((*this) * t);
		std::memcpy(m_values, n.m_values, sizeof(float) * 16);
	}
	inline void scale(Vector3f vector) {
		Matrix4f t = Matrix4f();
		t.initScale(vector);
		Matrix<float, 4> n = ((*this) * t);
		std::memcpy(m_values, n.m_values, sizeof(float) * 16);
	}
	inline void transform(Vector2f t, float r, Vector2f s) {
		translate(t);
		rotate(r);
		scale(s);
	}
	inline void transform(Vector3f t, Vector3f r, Vector3f s) {
		translate(t);
		rotate(r);
		scale(s);
	}
	inline void transformR(Vector2f t, float r, Vector2f s) {
		scale(s);
		rotate(r);
		translate(t);
	}
	inline void transformR(Vector3f t, Vector3f r, Vector3f s) {
		scale(s);
		rotate(r);
		translate(t);
	}

	inline Matrix3f to3x3() {
		Matrix3f mat3;
		mat3.set(0, 0, get(0, 0));
		mat3.set(1, 0, get(1, 0));
		mat3.set(2, 0, get(2, 0));

		mat3.set(0, 1, get(0, 1));
		mat3.set(1, 1, get(1, 1));
		mat3.set(2, 1, get(2, 1));

		mat3.set(0, 2, get(0, 2));
		mat3.set(1, 2, get(1, 2));
		mat3.set(2, 2, get(2, 2));
		return mat3;
	}

	/* The method used to invert this matrix */
	Matrix4f inverse() {
		//Get the values of the matrix (Transposed)
		float mat0 = m_values[0][0];
		float mat4 = m_values[0][1];
		float mat8 = m_values[0][2];
		float mat12 = m_values[0][3];

		float mat1 = m_values[1][0];
		float mat5 = m_values[1][1];
		float mat9 = m_values[1][2];
		float mat13 = m_values[1][3];

		float mat2 = m_values[2][0];
		float mat6 = m_values[2][1];
		float mat10 = m_values[2][2];
		float mat14 = m_values[2][3];

		float mat3 = m_values[3][0];
		float mat7 = m_values[3][1];
		float mat11 = m_values[3][2];
		float mat15 = m_values[3][3];

		//Calculate the pairs
		float mp0 = mat10 * mat15;
		float mp1 = mat11 * mat14;
		float mp2 = mat9 * mat15;
		float mp3 = mat11 * mat13;
		float mp4 = mat9 * mat14;
		float mp5 = mat10 * mat13;
		float mp6 = mat8 * mat15;
		float mp7 = mat11 * mat12;
		float mp8 = mat8 * mat14;
		float mp9 = mat10 * mat12;
		float mp10 = mat8 * mat13;
		float mp11 = mat9 * mat12;

		float scof0 = mat2 * mat7;
		float scof1 = mat3 * mat6;
		float scof2 = mat1 * mat7;
		float scof3 = mat3 * mat5;
		float scof4 = mat1 * mat6;
		float scof5 = mat2 * mat5;
		float scof6 = mat0 * mat7;
		float scof7 = mat3 * mat4;
		float scof8 = mat0 * mat6;
		float scof9 = mat2 * mat4;
		float scof10 = mat0 * mat5;
		float scof11 = mat1 * mat4;

		//Calculate cofactors
		float fcof0 = (mp0 * mat5 + mp3 * mat6 + mp4 * mat7) - (mp1 * mat5 + mp2 * mat6 + mp5 * mat7);
		float fcof1 = (mp1 * mat4 + mp6 * mat6 + mp9 * mat7) - (mp0 * mat4 + mp7 * mat6 + mp8 * mat7);
		float fcof2 = (mp2 * mat4 + mp7 * mat5 + mp10 * mat7) - (mp3 * mat4 + mp6 * mat5 + mp11 * mat7);
		float fcof3 = (mp5 * mat4 + mp8 * mat5 + mp11 * mat6) - (mp4 * mat4 + mp9 * mat5 + mp10 * mat6);
		float fcof4 = (mp1 * mat1 + mp2 * mat2 + mp5 * mat3) - (mp0 * mat1 + mp3 * mat2 + mp4 * mat3);
		float fcof5 = (mp0 * mat0 + mp7 * mat2 + mp8 * mat3) - (mp1 * mat0 + mp6 * mat2 + mp9 * mat3);
		float fcof6 = (mp3 * mat0 + mp6 * mat1 + mp11 * mat3) - (mp2 * mat0 + mp7 * mat1 + mp10 * mat3);
		float fcof7 = (mp4 * mat0 + mp9 * mat1 + mp10 * mat2) - (mp5 * mat0 + mp8 * mat1 + mp11 * mat2);

		float fcof8 = (scof0 * mat13 + scof3 * mat14 + scof4 * mat15) - (scof1 * mat13 + scof2 * mat14 + scof5 * mat15);
		float fcof9 = (scof1 * mat12 + scof6 * mat14 + scof9 * mat15) - (scof0 * mat12 + scof7 * mat14 + scof8 * mat15);
		float fcof10 = (scof2 * mat12 + scof7 * mat13 + scof10 * mat15) - (scof3 * mat12 + scof6 * mat13 + scof11 * mat15);
		float fcof11 = (scof5 * mat12 + scof8 * mat13 + scof11 * mat14) - (scof4 * mat12 + scof9 * mat13 + scof10 * mat14);
		float fcof12 = (scof2 * mat10 + scof5 * mat11 + scof1 * mat9 ) - (scof4 * mat11 + scof0 * mat9 + scof3 * mat10);
		float fcof13 = (scof8 * mat11 + scof0 * mat8 + scof7 * mat10) - (scof6 * mat10 + scof9 * mat11 + scof1 * mat8);
		float fcof14 = (scof6 * mat9 + scof11 * mat11 + scof3 * mat8) - (scof10 * mat11 + scof2 * mat8 + scof7 * mat9);
		float fcof15 = (scof10 * mat10 + scof4 * mat8 + scof9 * mat9) - (scof8 * mat9 + scof11 * mat10 + scof5 * mat8);

		//Calculate the determinant
		float determinant = mat0 * fcof0 + mat1 * fcof1 + mat2 * fcof2 + mat3 * fcof3;

		//Make sure the determinant isn't 0
		if (determinant == 0.0f)
			//Return nothing
			return Matrix4f();

		//The inverted matrix's values
		Matrix4f mat;

		//Calculate the matrix inverse
		float value = 1.0f / determinant;
		mat.set(0, 0, fcof0 * value);
		mat.set(0, 1, fcof1 * value);
		mat.set(0, 2, fcof2 * value);
		mat.set(0, 3, fcof3 * value);

		mat.set(1, 0, fcof4 * value);
		mat.set(1, 1, fcof5 * value);
		mat.set(1, 2, fcof6 * value);
		mat.set(1, 3, fcof7 * value);

		mat.set(2, 0, fcof8 * value);
		mat.set(2, 1, fcof9 * value);
		mat.set(2, 2, fcof10 * value);
		mat.set(2, 3, fcof11 * value);

		mat.set(3, 0, fcof12 * value);
		mat.set(3, 1, fcof13 * value);
		mat.set(3, 2, fcof14 * value);
		mat.set(3, 3, fcof15 * value);
		return mat;
	}
};

typedef Matrix<int, 2> Matrix2i;
typedef Matrix<int, 3> Matrix3i;
typedef Matrix4<int> Matrix4i;

typedef Matrix<float, 2> Matrix2f;

typedef Matrix<double, 2> Matrix2d;
typedef Matrix<double, 3> Matrix3d;
typedef Matrix4<double> Matrix4d;

/***************************************************************************************************/

#endif
