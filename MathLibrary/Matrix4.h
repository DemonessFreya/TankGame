#pragma once
#include <cmath>
#include <string>

namespace MathLibrary
{
    struct Matrix4
    {
        // Matrix 4x4
        union {
            struct {
                float m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16;
            };

            float v[16];
        };


        // Constructor/destructor
        // ------------------------------------

        // default constructor
        Matrix4() {
            m2 = m3 = m4 = m5 = m7 = m8 = m9 = m10 = m12 = m13 = m14 = m15 = 0.0f;
            m1 = m6 = m11 = m16 = 1.0f;
        }

        // destructor
        ~Matrix4() {}

        // parameterised constructor
        Matrix4(float _m1, float _m2, float _m3, float _m4, float _m5, float _m6, float _m7, float _m8, float _m9, float _m10, float _m11, float _m12, float _m13, float _m14, float _m15, float _m16) :
            m1(_m1), m2(_m2), m3(_m3), m4(_m4), m5(_m5), m6(_m6), m7(_m7), m8(_m8), m9(_m9), m10(_m10), m11(_m11), m12(_m12), m13(_m13), m14(_m14), m15(_m15), m16(_m16) {
        }

        // copy constructor
        Matrix4(const Matrix4& other) :
            m1(other.m1), m2(other.m2), m3(other.m3), m4(other.m4), m5(other.m5), m6(other.m6), m7(other.m7), m8(other.m8), m9(other.m9), m10(other.m10), m11(other.m11), m12(other.m12), m13(other.m13), m14(other.m14), m15(other.m15), m16(other.m16) {
        }


        // Operator overloads
        // ------------------------------------

        // matrix assignment =
        Matrix4& operator=(const Matrix4& rhs) {
            m1 = rhs.m1;
            m2 = rhs.m2;
            m3 = rhs.m3;
            m4 = rhs.m4;
            m5 = rhs.m5;
            m6 = rhs.m6;
            m7 = rhs.m7;
            m8 = rhs.m8;
            m9 = rhs.m9;
            m10 = rhs.m10;
            m11 = rhs.m11;
            m12 = rhs.m12;
            m13 = rhs.m13;
            m14 = rhs.m14;
            m15 = rhs.m15;
            m16 = rhs.m16;

            return *this;
        }

        // vector transformation by matrix *
        Vector4 operator*(const Vector4& rhs) const {
            return Vector4((m1 * rhs.x) + (m5 * rhs.y) + (m9 * rhs.z) + (m13 * rhs.w),
                (m2 * rhs.x) + (m6 * rhs.y) + (m10 * rhs.z) + (m14 * rhs.w),
                (m3 * rhs.x) + (m7 * rhs.y) + (m11 * rhs.z) + (m15 * rhs.w),
                (m4 * rhs.x) + (m8 * rhs.y) + (m12 * rhs.z) + (m16 * rhs.w));
        }

        // matrix multiplication *
        Matrix4 operator*(const Matrix4& rhs) const {
            return Matrix4(
                m1 * rhs.m1 + m5 * rhs.m2 + m9 * rhs.m3 + m13 * rhs.m4,
                m2 * rhs.m1 + m6 * rhs.m2 + m10 * rhs.m3 + m14 * rhs.m4,
                m3 * rhs.m1 + m7 * rhs.m2 + m11 * rhs.m3 + m15 * rhs.m4,
                m4 * rhs.m1 + m8 * rhs.m2 + m12 * rhs.m3 + m16 * rhs.m4,

                m1 * rhs.m5 + m5 * rhs.m6 + m9 * rhs.m7 + m13 * rhs.m8,
                m2 * rhs.m5 + m6 * rhs.m6 + m10 * rhs.m7 + m14 * rhs.m8,
                m3 * rhs.m5 + m7 * rhs.m6 + m11 * rhs.m7 + m15 * rhs.m8,
                m4 * rhs.m5 + m8 * rhs.m6 + m12 * rhs.m7 + m16 * rhs.m8,

                m1 * rhs.m9 + m5 * rhs.m10 + m9 * rhs.m11 + m13 * rhs.m12,
                m2 * rhs.m9 + m6 * rhs.m10 + m10 * rhs.m11 + m14 * rhs.m12,
                m3 * rhs.m9 + m7 * rhs.m10 + m11 * rhs.m11 + m15 * rhs.m12,
                m4 * rhs.m9 + m8 * rhs.m10 + m12 * rhs.m11 + m16 * rhs.m12,

                m1 * rhs.m13 + m5 * rhs.m14 + m9 * rhs.m15 + m13 * rhs.m16,
                m2 * rhs.m13 + m6 * rhs.m14 + m10 * rhs.m15 + m14 * rhs.m16,
                m3 * rhs.m13 + m7 * rhs.m14 + m11 * rhs.m15 + m15 * rhs.m16,
                m4 * rhs.m13 + m8 * rhs.m14 + m12 * rhs.m15 + m16 * rhs.m16);
        }

        // matrix assignment operator *=
        Matrix4& operator*=(const Matrix4& rhs) {
            *this = *this * rhs; // use previously overloaded operator* to concatenate the two matrices
            return *this;
        }

        // equality operator ==
        bool operator==(const Matrix4& rhs) const {
            for (size_t i = 0; i < 16; ++i) {
                if (v[i] != rhs.v[i]) {
                    return false;
                }
            }
            return true;
        }

        // equality operator !=
        bool operator!=(const Matrix4& rhs) const {
            return !(*this == rhs);
        }

        // mutable access to each element []
        float& operator[](int dim) {
            return v[dim];
        }

        // const-qualified access to each element []
        const float& operator[](int dim) const {
            return v[dim];
        }


        // Member functions
        // ------------------------------------

        // convert matrix to string for debugging purposes
        std::string ToString() const
        {
            std::string str = std::to_string(v[0]);
            for (size_t i = 1; i < 16; ++i)
            {
                str += ", " + std::to_string(v[i]);
            }
            return str;
        }

        // returns rotated matrix by angle f radians around x-axis
        static Matrix4 MakeRotateX(float radians) {
            float cosine = std::cosf(radians);
            float sine = std::sinf(radians);
            return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, cosine, -sine, 0.0f,
                0.0f, sine, cosine, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
        }

        // returns rotated matrix by angle f radians around y-axis
        static Matrix4 MakeRotateY(float radians) {
            float cosine = std::cosf(radians);
            float sine = std::sinf(radians);

            return Matrix4(cosine, 0.0f, sine, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                -sine, 0.0f, cosine, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
        }

        // returns rotated matrix by angle f radians around z-axis
        static Matrix4 MakeRotateZ(float radians) {
            float cosine = std::cosf(radians);
            float sine = std::sinf(radians);

            return Matrix4(cosine, sine, 0.0f, 0.0f,
                -sine, cosine, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
        }

        // returns scaled matrix by floats x, y and z
        static Matrix4 MakeScale(float x, float y, float z) {
            return Matrix4(x, 0.0f, 0.0f, 0.0f,
                0.0f, y, 0.0f, 0.0f,
                0.0f, 0.0f, z, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
        }

        // returns translated matrix by V
        static Matrix4 MakeTranslation(float x, float y, float z) {
            return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                x, y, z, 1.0f); // column-major order; therefore, the translation components are in the last column (m13, m14, m15)
        }

        // returns translated matrix by Vector4
        void SetTranslate(const Vector4& v) {
            m13 = v.x;
            m14 = v.y;
            m15 = v.z;
        }

        // returns the right direction vector (x-axis) of the matrix
        Vector4 GetRight() const {
            return Vector4(m1, m2, m3, m4);
        }

        // returns the up direction vector (y-axis) of the matrix
        Vector4 GetUp() const {
            return Vector4(m5, m6, m7, m8);
        }

        // returns the forward direction vector (z-axis) of the matrix
        Vector4 GetForward() const {
            return Vector4(m9, m10, m11, m12);
        }

        // returns the position vector (w-axis) of the matrix
        Vector4 GetPosition() const {
            return Vector4(m13, m14, m15, m16);
        }

        // check if two matrices are equal within epsilon
        bool IsApproximatelyEqual(const Matrix4& rhs, float epsilon = 1e-4f) const {
            if (std::isnan(v[0]) || std::isnan(rhs.v[0])) {
                return false; // if either matrix contains NaN, they cannot be approximately equal
            }

            for (size_t i = 0; i < 16; ++i) {
                if (std::fabs(v[i] - rhs.v[i]) > epsilon) {
                    return false;
                }
            }
            return true;
        }
    };
}
