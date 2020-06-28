#ifndef VDENGINE_MATRIX_4X4_H_
#define VDENGINE_MATRIX_4X4_H_

// Standard c++ libs
#include <iostream>
#include <iomanip>

// Internal headers
#include "VDEngine/Math/Vectors.hpp"

namespace VDEngine
{

struct Matrix4
{
    // glm : column major
    // glm::mat4[col][row]

    // Opengl : column major ?
    // xx xy xz 0 yx yy yz 0 zx zy zz 0 wx wy wz 1

    // Unity : Row major

    // Column major : Columns represent X, Y and Z axis
    // -> [0] = X
    // -> [1] = Y
    // Column major :  need reverse ?

    // constructors
    Matrix4(); // init with identity
    Matrix4(const float src[16]);
    Matrix4(float m00, float m01, float m02, float m03,  // 1st column
            float m04, float m05, float m06, float m07,  // 2nd column
            float m08, float m09, float m10, float m11,  // 3rd column
            float m12, float m13, float m14, float m15); // 4th column

    void Set(const float src[16]);
    void Set(float m00, float m01, float m02, float m03,  // 1st column
             float m04, float m05, float m06, float m07,  // 2nd column
             float m08, float m09, float m10, float m11,  // 3rd column
             float m12, float m13, float m14, float m15); // 4th column
    void SetRow(int index, const float row[4]);
    void SetRow(int index, const Vector4 & v);
    void SetRow(int index, const Vector3 & v);
    void SetColumn(int index, const float col[4]);
    void SetColumn(int index, const Vector4 & v);
    void SetColumn(int index, const Vector3 & v);

    const float * Get() const;
    const float * GetTranspose();             // return transposed matrix
    Vector4       GetRow(int index) const;    // return the selected row vector
    Vector4       GetColumn(int index) const; // return the selected col vector
    float         GetDeterminant() const;
    Vector3       GetAngle() const;       // return (pitch, yaw, roll) in degree
    Vector3       GetLeftAxis() const;    // return left vector
    Vector3       GetUpAxis() const;      // return up vector
    Vector3       GetForwardAxis() const; // return forward vector

    Matrix4 & Identity();
    Matrix4 & Transpose();       // transpose itself and return reference
    Matrix4 & Invert();          // check best inverse method before inverse
    Matrix4 & InvertEuclidean(); // inverse of Euclidean transform matrix
    Matrix4 & InvertAffine();    // inverse of affine transform matrix
    Matrix4 & InvertGeneral();   // inverse of generic matrix

    // transform matrix
    Matrix4 & Translate(float x, float y, float z);      // translation by (x,y,z)
    Matrix4 & Translate(const Vector3 & v);              //
    Matrix4 & Rotate(float angle, const Vector3 & axis); // rotate angle(degree) along the given axix
    Matrix4 & Rotate(float angle, float x, float y, float z);
    Matrix4 & RotateX(float angle);                 // rotate on X-axis with degree
    Matrix4 & RotateY(float angle);                 // rotate on Y-axis with degree
    Matrix4 & RotateZ(float angle);                 // rotate on Z-axis with degree
    Matrix4 & Scale(float scale);                   // uniform scale
    Matrix4 & Scale(float sx, float sy, float sz);  // scale by (sx, sy, sz) on each axis
    Matrix4 & LookAt(float tx, float ty, float tz); // face object to the target direction
    Matrix4 & LookAt(float tx, float ty, float tz, float ux, float uy, float uz);
    Matrix4 & LookAt(const Vector3 & target);
    Matrix4 & LookAt(const Vector3 & target, const Vector3 & up);

    // /// <summary>
    // ///   <para>Creates an orthogonal projection matrix.</para>
    // /// </summary>
    // static Matrix4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar)

    // /// <summary>
    // ///   <para>Creates a perspective projection matrix.</para>
    // /// </summary>
    // static Matrix4 Perspective(float fov, float aspect, float zNear, float zFar)

    // operators
    Matrix4   operator+(const Matrix4 & rhs) const;  // add rhs
    Matrix4   operator-(const Matrix4 & rhs) const;  // subtract rhs
    Matrix4 & operator+=(const Matrix4 & rhs);       // add rhs and update this object
    Matrix4 & operator-=(const Matrix4 & rhs);       // subtract rhs and update this object
    Vector4   operator*(const Vector4 & rhs) const;  // multiplication: v' = M * v
    Vector3   operator*(const Vector3 & rhs) const;  // multiplication: v' = M * v
    Matrix4   operator*(const Matrix4 & rhs) const;  // multiplication: M3 = M1 * M2
    Matrix4 & operator*=(const Matrix4 & rhs);       // multiplication: M1' = M1 * M2
    bool      operator==(const Matrix4 & rhs) const; // exact compare, no epsilon
    bool      operator!=(const Matrix4 & rhs) const; // exact compare, no epsilon
    float     operator[](int index) const;           // subscript operator v[0], v[1]
    float &   operator[](int index);                 // subscript operator v[0], v[1]

    friend std::ostream & operator<<(std::ostream & os, const Matrix4 & m);

  protected:
  private:
    float GetCofactor(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8) const;

    float m_matrix[16];
};

} // namespace VDEngine

#endif /* VDENGINE_MATRIX_4X4_H_ */