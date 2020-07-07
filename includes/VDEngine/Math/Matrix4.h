#ifndef VDENGINE_MATRIX_4X4_H_
#define VDENGINE_MATRIX_4X4_H_

// Standard c++ libs
#include <iostream>
#include <iomanip>

// Internal headers
#include "VDEngine/Math/Vectors.hpp"
#include "VDEngine/Math/Quaternion.h"

namespace VDEngine
{

// Column Major:
//
//   X  Y  Z  T
//   v  v  v  v
// +-------------+
// | 0  4  8  12 |
// | 1  5  9  13 |
// | 2  6  10 14 |
// | 3  7  11 15 |
// +-------------+
//
// X.x X.y X.z 0 Y.x Y.y Y.z 0 Z.x Z.y Z.z 0 wx wy wz 1

struct Matrix4
{
  public:
    // -- constructors ------------

    Matrix4(); // init as identity

    Matrix4(float m00, float m01, float m02, float m03,  // 1st column
            float m04, float m05, float m06, float m07,  // 2nd column
            float m08, float m09, float m10, float m11,  // 3rd column
            float m12, float m13, float m14, float m15); // 4th column

    // -- static constructors -----

    static Matrix4 CreateRotationMatrix(const Quaternion & orientation);
    static Matrix4 CreateTranslationMatrix(const Vector3 & translation);
    static Matrix4 CreateScaleMatrix(const Vector3 & scale);

    static Matrix4 ComposeTRS(const Vector3 & translation, const Quaternion & rotation, const Vector3 & scale);

    static Matrix4 CreateOrtho(float left, float right, float bottom, float top, float z_near, float z_far);
    static Matrix4 CreatePerspective(float fov, float aspect, float z_near, float z_far);

    // -- static getters --

    static void QRDecompose(const Matrix4 & mat, Matrix4 & orth_mat, Matrix4 & up_triang_mat);
    static void AffineDecompose(const Matrix4 & mat, Vector3 & translation, Quaternion & rotation, Vector3 & scale);

    // -- Setters -----------------

    void Set(float m00, float m01, float m02, float m03,  // 1st column
             float m04, float m05, float m06, float m07,  // 2nd column
             float m08, float m09, float m10, float m11,  // 3rd column
             float m12, float m13, float m14, float m15); // 4th column

    void SetRow(int index, const Vector4 & v);
    void SetRow(int index, const Vector3 & v);

    void SetColumn(int index, const Vector4 & v);
    void SetColumn(int index, const Vector3 & v);

    // -- Getters

    const float * Get() const;
    Vector4       GetRow(int index) const;    // return the selected row vector
    Vector4       GetColumn(int index) const; // return the selected col vector

    Vector3 GetLeftAxis() const;    // return left vector
    Vector3 GetUpAxis() const;      // return up vector
    Vector3 GetForwardAxis() const; // return forward vector

    float GetDeterminant() const;

    Matrix4 GetTransposed() const; // return transposed matrix
    Matrix4 GetInverted() const;
    Matrix4 GetOrthonormalized() const;

    // -- Functions --

    void Identity(); // set the matrix as an identity matrix

    void Transpose(); // transpose itself and return reference

    void Invert();          // check best inverse method before inverse
    void InvertEuclidean(); // inverse of Euclidean transform matrix
    void InvertAffine();    // inverse of affine transform matrix
    void InvertGeneral();   // inverse of generic matrix

    void Orthonormalize();

    // -- Operators --

    Matrix4 & operator+=(const Matrix4 & rhs); // add rhs and update this object
    Matrix4 & operator-=(const Matrix4 & rhs); // subtract rhs and update this object
    Matrix4 & operator*=(const Matrix4 & rhs); // multiplication: M' = M1 * M2

    Matrix4 operator+(const Matrix4 & rhs) const; // add rhs
    Matrix4 operator-(const Matrix4 & rhs) const; // subtract rhs
    Vector3 operator*(const Vector3 & rhs) const; // multiplication: v' = M * v
    Vector4 operator*(const Vector4 & rhs) const; // multiplication: v' = M * v
    Matrix4 operator*(const Matrix4 & rhs) const; // multiplication: M' = M1 * M2

    bool operator==(const Matrix4 & rhs) const;
    bool operator!=(const Matrix4 & rhs) const;

    float & operator[](int index);       // subscript operator v[0], v[1]
    float   operator[](int index) const; // subscript operator v[0], v[1]

    float & operator()(unsigned col, unsigned row);
    float   operator()(unsigned col, unsigned row) const;

    friend std::ostream & operator<<(std::ostream & os, const Matrix4 & m);

    // -- transform matrix ---

    // Matrix4 & Translate(float x, float y, float z); // translation by (x,y,z)
    // Matrix4 & Translate(const Vector3 & v);         //

    // Matrix4 & Rotate(float angle, const Vector3 & axis); // rotate angle(degree) along the given axix
    // Matrix4 & Rotate(float angle, float x, float y, float z);
    // Matrix4 & RotateX(float angle); // rotate on X-axis with degree
    // Matrix4 & RotateY(float angle); // rotate on Y-axis with degree
    // Matrix4 & RotateZ(float angle); // rotate on Z-axis with degree

    // Matrix4 & Scale(float scale);                  // uniform scale
    // Matrix4 & Scale(float sx, float sy, float sz); // scale by (sx, sy, sz) on each axis

    // Matrix4 & LookAt(float tx, float ty, float tz); // face object to the target direction
    // Matrix4 & LookAt(float tx, float ty, float tz, float ux, float uy, float uz);
    // Matrix4 & LookAt(const Vector3 & target);
    // Matrix4 & LookAt(const Vector3 & target, const Vector3 & up);

  private:
    float GetCofactor(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8) const;

    float m_matrix[16];
};

} // namespace VDEngine

#endif /* VDENGINE_MATRIX_4X4_H_ */