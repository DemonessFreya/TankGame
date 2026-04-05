#pragma once
#include <cmath>

namespace MathLibrary
{
    struct Vector3
    {
        // Contructors/destructors
        // ------------------------------------

        float x, y, z;

        // default constructor
        Vector3() : x(0), y(0), z(0) {}

        // destructor
        ~Vector3() {}

        // parameterised constructor
        Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

        // copy constructor
        Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}


        // Operator overloads
        // ------------------------------------

        // vector addition +
        Vector3 operator+(const Vector3& rhs) const {
            return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        // vector subtraction -
        Vector3 operator-(const Vector3& rhs) const {
            return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        // Hadamard product *
        Vector3 operator*(const Vector3& rhs) const {
            return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
        }

        // scalar product *
        Vector3 operator*(const float scalar) const {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }

        // scalar division /
        Vector3 operator/(const float scalar) const {
            if (scalar == 0.0f) {
                return Vector3(0, 0, 0);
            }
            return Vector3(x / scalar, y / scalar, z / scalar);
        }

        // assignment operator =
        Vector3& operator=(const Vector3& other) {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        // vector addition +=
        Vector3& operator+=(const Vector3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        // vector subtraction -=
        Vector3& operator-=(const Vector3& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        // Hadamard product *=
        Vector3& operator*=(const Vector3& other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        // scalar product *=
        Vector3& operator*=(const float scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        // scalar division /=
        Vector3& operator/=(const float scalar) {
            if (scalar == 0.0f) {
                x = 0;
                y = 0;
                z = 0;
                return *this;
            }

            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        // unary -operand
        Vector3 operator-() const {
            return Vector3(-x, -y, -z);
        }

        // equality operator ==
        bool operator==(const Vector3& rhs) const {
            return (x == rhs.x && y == rhs.y && z == rhs.z);
        }

        // inequality operator !=
        bool operator!=(const Vector3& rhs) const {
            return !(*this == rhs); // if parent vector and copy vector are unequal, return false
        }

        // less than operator < (magnitude comparison: |v| = sqrt(x^2 + y^2 + z^2))
        bool operator<(const Vector3& rhs) const {
            float magSqr1 = (x * x) + (y * y) + (z * z);
            float magSqr2 = (rhs.x * rhs.x) + (rhs.y * rhs.y) + (rhs.z * rhs.z);

            return (magSqr1 < magSqr2); // can ignore root to save processing
        }

        // index operator []
        float& operator[](int index) {
            return (&x)[index];
        }

        // const-qualified index operator []
        const float& operator[](int index) const {
            return (&x)[index];
        }


        // Member functions
        // ------------------------------------

        float Dot(const Vector3& rhs) const {
            return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
        }

        Vector3 Cross(const Vector3& rhs) const {
            return Vector3((y * rhs.z) - (z * rhs.y), (z * rhs.x) - (x * rhs.z), (x * rhs.y) - (y * rhs.x));
        }

        float Magnitude() const {
            return std::sqrt((x * x) + (y * y) + (z * z)); // return length of vector
        }

        void Normalise() {
            float mag = Magnitude();
            if (mag > 0) {
                // normalise each component
                x /= mag;
                y /= mag;
                z /= mag;
            }
        }

        Vector3 Normalised() const {
            float mag = Magnitude();
            if (mag > 0) {
                return Vector3(x / mag, y / mag, z / mag);
            }

            return Vector3(0, 0, 0);
        }

        bool IsApproximatelyEqual(const Vector3& rhs, float epsilon = 1e-4f) const {
            return (std::fabs(x - rhs.x) < epsilon &&
                std::fabs(y - rhs.y) < epsilon &&
                std::fabs(z - rhs.z) < epsilon); // if the absolute value of each component's difference is less than epsilon, return true
        }

        float AngleBetween(const Vector3& rhs) const {
            Vector3 a = Normalised();
            Vector3 b = rhs.Normalised();
            float dp = a.Dot(b);
            return std::acosf(dp);
        }

        float Distance(const Vector3& rhs) const {
            return (*this - rhs).Magnitude(); // take the difference of two vectors and return the magnitude
        }

        float Angle2D() const {
            return std::atan2f(-y, x); // return angle clockwise from (1, 0) in range -PI to PI
        }
    };
}
