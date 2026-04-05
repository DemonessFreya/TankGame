#pragma once
#include <cmath>
#include <string>

namespace MathLibrary
{
    struct Matrix3
    {
        // Matrix 3x3
        union {
            struct {
                float m1, m2, m3, m4, m5, m6, m7, m8, m9;
            };

            float v[9];
        };


        // Constructor/destructor
        // ------------------------------------

        // default constructor
        Matrix3() {
            m2 = m3 = m4 = m6 = m7 = m8 = 0.0f;
            m1 = m5 = m9 = 1.0f;
        }

        // destructor
        ~Matrix3() {}

        // parameterised constructor
        Matrix3(float _m1, float _m2, float _m3, float _m4, float _m5, float _m6, float _m7, float _m8, float _m9) :
            m1(_m1), m2(_m2), m3(_m3), m4(_m4), m5(_m5), m6(_m6), m7(_m7), m8(_m8), m9(_m9) {
        }

        // copy constructor
        Matrix3(const Matrix3& other) : m1(other.m1), m2(other.m2), m3(other.m3), m4(other.m4), m5(other.m5), m6(other.m6), m7(other.m7), m8(other.m8), m9(other.m9) {}


        // Operator overloads
        // ------------------------------------

        // matrix assignment =
        Matrix3& operator=(const Matrix3& rhs) {
            m1 = rhs.m1;
            m2 = rhs.m2;
            m3 = rhs.m3;
            m4 = rhs.m4;
            m5 = rhs.m5;
            m6 = rhs.m6;
            m7 = rhs.m7;
            m8 = rhs.m8;
            m9 = rhs.m9;

            return *this;
        }

        // vector transformation by matrix *
        Vector3 operator*(const Vector3& rhs) const {
            return Vector3(Vector3(m1, m4, m7).Dot(rhs), // (m1 * rhs.x) + (m4 * rhs.y) + (m7 * rhs.z)
                Vector3(m2, m5, m8).Dot(rhs), // (m2 * rhs.x) + (m5 * rhs.y) + (m8 * rhs.z)
                Vector3(m3, m6, m9).Dot(rhs)); // (m3 * rhs.x) + (m6 * rhs.y) + (m9 * rhs.z)
        }

        // matrix multiplication *
        Matrix3 operator*(const Matrix3& rhs) const {
            return Matrix3(
                m1 * rhs.m1 + m4 * rhs.m2 + m7 * rhs.m3,
                m2 * rhs.m1 + m5 * rhs.m2 + m8 * rhs.m3,
                m3 * rhs.m1 + m6 * rhs.m2 + m9 * rhs.m3,

                m1 * rhs.m4 + m4 * rhs.m5 + m7 * rhs.m6,
                m2 * rhs.m4 + m5 * rhs.m5 + m8 * rhs.m6,
                m3 * rhs.m4 + m6 * rhs.m5 + m9 * rhs.m6,

                m1 * rhs.m7 + m4 * rhs.m8 + m7 * rhs.m9,
                m2 * rhs.m7 + m5 * rhs.m8 + m8 * rhs.m9,
                m3 * rhs.m7 + m6 * rhs.m8 + m9 * rhs.m9);
        }

        // matrix assignment operator *=
        Matrix3& operator*=(const Matrix3& rhs) {
            *this = *this * rhs; // use previously overloaded operator* to concatenate the two matrices

            return *this;
        }

        // equality operator ==
        bool operator==(const Matrix3& rhs) const {
            return (m1 == rhs.m1 && m2 == rhs.m2 && m3 == rhs.m3 &&
                m4 == rhs.m4 && m5 == rhs.m5 && m6 == rhs.m6 &&
                m7 == rhs.m7 && m8 == rhs.m8 && m9 == rhs.m9);
        }

        // equality operator !=
        bool operator!=(const Matrix3 rhs) const {
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
            for (size_t i = 1; i < 9; ++i)
            {
                str += ", " + std::to_string(v[i]);
            }
            return str;
        }

        // returns rotated matrix by angle f radians
        static Matrix3 MakeRotate(float radians) {
            float cosine = std::cosf(radians);
            float sine = std::sinf(radians);

            return Matrix3(cosine, sine, 0, // column 1
                           -sine, cosine, 0, // column 2
                           0, 0, 1); // column 3
        }

        // returns scaled matrix by vec.x and vec.y
        static Matrix3 MakeScale(float x, float y) {
            return Matrix3(x, 0, 0,
                0, y, 0,
                0, 0, 1);
        }

        // returns translated matrix by vec.x and vec.y
        static Matrix3 MakeTranslate(const Vector3& rhs) {
            return Matrix3(1, 0, 0,
                0, 1, 0,
                rhs.x, rhs.y, 1);
        }

        // get direction of vector on x-axis
        Vector3 GetForward() const {
            return Vector3(m1, m2, m3);
        }

        // get direction of vector on y-axis
        Vector3 GetRight() const {
            return Vector3(m4, m5, m6);
        }

        // get position of matrix
        Vector3 GetTranslate() const {
            return Vector3(m7, m8, m9);
        }

        // check if two matrices are equal within epsilon
        bool IsApproximatelyEqual(const Matrix3& rhs, float epsilon = 1e-4f) const {
            return (std::fabs(m1 - rhs.m1) < epsilon &&
                std::fabs(m2 - rhs.m2) < epsilon &&
                std::fabs(m3 - rhs.m3) < epsilon &&
                std::fabs(m4 - rhs.m4) < epsilon &&
                std::fabs(m5 - rhs.m5) < epsilon &&
                std::fabs(m6 - rhs.m6) < epsilon &&
                std::fabs(m7 - rhs.m7) < epsilon &&
                std::fabs(m8 - rhs.m8) < epsilon &&
                std::fabs(m9 - rhs.m9) < epsilon);
        }
    };
}
