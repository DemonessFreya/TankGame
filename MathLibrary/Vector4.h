#pragma once
#include <cmath>

namespace MathLibrary
{
    struct Vector4
    {
        // Contructors/destructors
        // ------------------------------------

        float x, y, z, w;

        // default constructor
        Vector4() : x(0), y(0), z(0), w(0) {}

        // destructor
        ~Vector4() {}

        // parameterised constructor
        Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

        // copy constructor
        Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}


        // Operator overloads
        // ------------------------------------

        // vector addition +
        Vector4 operator+(const Vector4& rhs) const {
            return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w);
        }

        // vector subtraction -
        Vector4 operator-(const Vector4& rhs) const {
            return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w);
        }

        // Hadamard product *
        Vector4 operator*(const Vector4& rhs) const {
            return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
        }

        // scalar product *
        Vector4 operator*(const float scalar) const {
            return Vector4(x * scalar, y * scalar, z * scalar, w);
        }

        // scalar division /
        Vector4 operator/(const float scalar) const {
            if (scalar == 0.0f) {
                return Vector4(0, 0, 0, w);
            }
            return Vector4(x / scalar, y / scalar, z / scalar, w);
        }

        // assignment operator =
        Vector4& operator=(const Vector4& rhs) {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            w = rhs.w;
            return *this;
        }

        // vector addition +=
        Vector4& operator+=(const Vector4& rhs) {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        // vector subtraction -=
        Vector4& operator-=(const Vector4& rhs) {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        // Hadamard product *=
        Vector4& operator*=(const Vector4& rhs) {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            w *= rhs.w;
            return *this;
        }

        // scalar product *=
        Vector4& operator*=(const float scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        // scalar division /=
        Vector4& operator/=(const float scalar) {
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
        Vector4 operator-() const {
            return Vector4(-x, -y, -z, w);
        }

        // equality operator ==
        bool operator==(const Vector4& rhs) const {
            return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
        }

        // inequality operator !=
        bool operator!=(const Vector4& rhs) const {
            return !(*this == rhs); // if parent vector and copy vector are unequal, return false
        }

        // less than operator < (magnitude comparison: |v| = sqrt(x^2 + y^2 + z^2))
        bool operator<(const Vector4& rhs) const {
            float magSqr1 = (x * x) + (y * y) + (z * z) + (w * w);
            float magSqr2 = (rhs.x * rhs.x) + (rhs.y * rhs.y) + (rhs.z * rhs.z) + (rhs.w * rhs.w);

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

        float Dot(const Vector4& rhs) const {
            return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + 0.0f; // 0.0f w component for readability
        }

        Vector4 Cross(const Vector4& rhs) const {
            return Vector4((y * rhs.z) - (z * rhs.y), (z * rhs.x) - (x * rhs.z), (x * rhs.y) - (y * rhs.x), 0.0f);
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

        Vector4 Normalised() const {
            float mag = Magnitude();
            if (mag > 0) {
                return Vector4(x / mag, y / mag, z / mag, w);
            }

            return Vector4(0, 0, 0, w);
        }

        bool IsApproximatelyEqual(const Vector4& rhs, float epsilon = 1e-4f) const {
            return (std::fabs(x - rhs.x) < epsilon &&
                std::fabs(y - rhs.y) < epsilon &&
                std::fabs(z - rhs.z) < epsilon) &&
                std::fabs(w - rhs.w) < epsilon; // if the absolute value of each component's difference is less than epsilon, return true
        }

        float AngleBetween(const Vector4& rhs) const {
            float dp = Normalised().Dot(rhs.Normalised());
            // clamp dot product values to 1.0 or -1.0 if it exceeds limits
            if (dp > 1.0f) dp = 1.0f;
            if (dp < -1.0f) dp = -1.0f;

            return std::acosf(dp);
        }

        float Distance(const Vector4& rhs) const {
            return (*this - rhs).Magnitude(); // take the difference of two vectors and return the magnitude
        }
    };
}
