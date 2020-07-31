#include "Vec2D.h"
#include "Utils.h"
#include <cassert>
#include <cmath>

const Vect2D Vect2D::Zero;


//**************OPERATORS***************
std::ostream& operator<<(std::ostream& consoleOut, const Vect2D& vec)
{
    std::cout << "X: " << vec.mX << ", Y: " << vec.mY << std::endl;
    return consoleOut;
}
Vect2D operator*(float scalar, const Vect2D& vec)
{
    return vec * scalar;
}

bool Vect2D::operator== (const Vect2D& vec2) const
{
    return IsEqual(mX, vec2.mX) && IsEqual(mY, vec2.mY);
}

bool Vect2D::operator!= (const Vect2D& vec2) const
{
    return !(*this == vec2);
}

Vect2D Vect2D::operator-() const 
{
    return Vect2D(-mX, -mY);
}

Vect2D Vect2D:: operator*(float scale) const
{
    return Vect2D(scale * mX, scale * mY);
}

Vect2D Vect2D:: operator/(float scale) const
{
    assert(fabsf(scale) > EPSILON);
    return Vect2D(mX / scale, mY / scale);
}

Vect2D& Vect2D::operator*=(float scale)
{
    *this = *this * scale;
    return *this;
}

Vect2D& Vect2D::operator/=(float scale)
{
    assert(fabsf(scale) > EPSILON);
    *this = *this / scale;
    return *this;
}

Vect2D Vect2D::operator+(const Vect2D& vec) const
{
    return Vect2D(mX + vec.mX, mY + vec.mY);
}

Vect2D Vect2D::operator-(const Vect2D& vec) const
{
    return Vect2D(mX - vec.mX, mY - vec.mY);
}

Vect2D& Vect2D::operator+=(const Vect2D& vec)
{
    *this = vec + *this;
    return *this;
}

Vect2D& Vect2D::operator-= (const Vect2D& vec)
{
    *this = *this -vec;
    return *this;
}

//********************************* MAGNITUDES************************************

float Vect2D:: Vect2D::Mag2() const // Magnitude au carré du vecteur composé
{
    return mX * mX + mY * mY;
}

float Vect2D::Vect2D::Mag() const // Magnitude  du vecteur composé
{
    return sqrt(Mag2());
}


//********************************VECTOR OPERATIONS***********************************

Vect2D  Vect2D:: GetUniteVec() const // retourne le vecteur unitaire, comme normalisation
{
    float mag = Mag();
    if (mag > EPSILON)
    {
        return *this / mag;
    }
    else
    {
        return Vect2D::Zero;
    }
}
Vect2D& Vect2D:: Normalize() // Normalisation du vecteur
{
    float mag = Mag();
    if (mag > EPSILON)
    {
        *this / mag;
    }
    return *this;
}

float Vect2D:: Distance(const Vect2D& vec) const // Distance entre deux vecteurs
{
    return (vec - *this).Mag();
}

float Vect2D:: Dot(const Vect2D& vec) const // produit scalaire
{
    return (mX * vec.mX + mY * vec.mY);
}

Vect2D Vect2D:: ProjectOnto(const Vect2D& vec2) const // donne la composante vertical du vecteur
{
    Vect2D unitVect2 = vec2.GetUniteVec();

    float dot = Dot(unitVect2);

    return unitVect2 * dot;
}

float Vect2D:: AngleBetween(const Vect2D& vec2) const // angle entre deux vecteurs
{
    return acos(GetUniteVec().Dot(vec2.GetUniteVec()));
}

Vect2D Vect2D::Reflect(const Vect2D& normal) const //retourne un vecteur symétrique par rapport à l'axe vertical (ex: rebond sur table horizontale)
{
    return *this - 2 * ProjectOnto(normal);
}

void Vect2D::Rotate(float angle, const Vect2D& aroundPoint)
{
    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vect2D thisVec(mX, mY);
    thisVec -= aroundPoint;

    float xRot = thisVec.mX * cosine - thisVec.mY * sine;
    float yRot = thisVec.mX * sine + thisVec.mY * cosine;

    Vect2D rot = Vect2D(xRot, yRot);

    *this = rot + aroundPoint;
   
}
Vect2D Vect2D::RotationResult(float angle, const Vect2D& aroundPoint) const
{
    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vect2D thisVec(mX, mY);
    thisVec -= aroundPoint;

    float xRot = thisVec.mX * cosine - thisVec.mY * sine;
    float yRot = thisVec.mX * sine + thisVec.mY * cosine;

    Vect2D rot = Vect2D(xRot, yRot);

    return rot + aroundPoint;
}