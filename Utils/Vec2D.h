#ifndef Utils_Vec2D_H_
#define Utils_Vec2D_H_
#include <iostream>


class Vect2D
{
public:
    Vect2D() : Vect2D(0, 0) {};
    Vect2D(float x, float y) : mX(x), mY(y) {}

    static const Vect2D Zero;

    inline void SetX(float x) { mX = x; }
    inline void SetY(float y) { mY = y; }
    inline float GetX() const { return mX; }
    inline float GetY() const { return mY; }

    friend std::ostream& operator<<(std::ostream& consoleOut, const Vect2D& vec);

    bool operator== (const Vect2D& vec2) const;
    bool operator!= (const Vect2D& vec2) const;

    Vect2D operator-() const; // Negat the vector
    Vect2D operator*(float scale) const;  //Multiply
    Vect2D operator/(float scale) const;  //divide
    Vect2D& operator*=(float scale);  //times equal
    Vect2D& operator/=(float scale);   //divide equal
    
    Vect2D operator+(const Vect2D& vec) const;  // Add two vectors
    Vect2D operator-(const Vect2D& vec) const;  // Sub two vectors
    Vect2D& operator+=(const Vect2D& vec);  //+= *this vector with a second vector
    Vect2D& operator-=(const Vect2D& vec);  //-= *this vector with a second vector

    float Mag2() const; // Magnitude squared
    float Mag() const; // Magnitude

    Vect2D GetUniteVec() const;
    Vect2D& Normalize();

    float Distance(const Vect2D& vec) const;
    float Dot(const Vect2D& vec) const;

    Vect2D ProjectOnto(const Vect2D& vec2) const;

    float AngleBetween(const Vect2D& vec) const;

    Vect2D Reflect(const Vect2D& normal) const;

    void Rotate(float angle, const Vect2D& aroundPoint);

    Vect2D RotationResult(float angle, const Vect2D& aroundPoint) const;

    friend Vect2D operator*(float scalar, const Vect2D& vec2);

private:
    float mX, mY;
};

#endif // !Vec2D_H_