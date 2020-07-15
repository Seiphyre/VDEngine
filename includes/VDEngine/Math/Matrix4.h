#ifndef VDENGINE_MATRIX_4_H_
#define VDENGINE_MATRIX_4_H_

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
// m_data[] = X.x X.y X.z 0 Y.x Y.y Y.z 0 Z.x Z.y Z.z 0 wx wy wz 1

struct Matrix4
{
  public:
    /********************************************************
     *               -- Constructors --                     *
     ********************************************************/

    /**
     * @brief Create an identity matrix.
     */
    Matrix4();

    /**
     * @brief Create matrix with all the data.
     */
    Matrix4(float m00, float m01, float m02, float m03,  // 1st column
            float m04, float m05, float m06, float m07,  // 2nd column
            float m08, float m09, float m10, float m11,  // 3rd column
            float m12, float m13, float m14, float m15); // 4th column

    // -- static constructors -----

    /**
     * @brief Create rotation matrix from a quaternion.
     */
    static Matrix4 CreateRotationMatrix(const Quaternion & rotation);

    /**
     * @brief Create translation matrix from a vector3.
     */
    static Matrix4 CreateTranslationMatrix(const Vector3 & translation);

    /**
     * @brief Create scale matrix from a vector3.
     */
    static Matrix4 CreateScaleMatrix(const Vector3 & scale);

    /**
     * @brief Create TRS matrix from a vector3. (Translation * Rotation * Scale, in this order)
     */
    static Matrix4 ComposeTRS(const Vector3 & translation, const Quaternion & rotation, const Vector3 & scale);

    /**
     * @brief Create an ortho projection matrix.
     * @exception     if `left == right`, return identity matrix.
     * @exception     if `bottom == top`, return identity matrix.
     * @exception     if `z_near == z_far`, return identity matrix.
     */
    static Matrix4 CreateOrtho(float left, float right, float bottom, float top, float z_near, float z_far);

    /**
     * @brief         Create a perspective projection matrix.
     *                It follow OpenGL convention ( i.e. clip space on Z-plane: [-1 < Z < 1] ).
     *
     * @param fov_y   Angle (in degrees). This should be the (full) angle of camera's field of view on the Y-plane.
     * @param aspect  Ratio between width and height of the screen (i.e. aspect = width / height).
     * @param z_near  Near depth clipping plane value.
     * @param z_far   Far depth clipping plane value.
     * @exception     if `fov_y == 0`, return identity matrix.
     * @exception     if `aspect == 0`, return identity matrix.
     * @exception     if `z_near == z_far`, return identity matrix.
     */
    static Matrix4 CreatePerspective(float fov_y, float aspect, float z_near, float z_far);

    /********************************************************
     *                  -- Setters --                       *
     ********************************************************/

    /**
     * @brief Set this matrix to an identity matrix.
     */
    void Identity();

    /**
     * @brief Set all the components of this matrix.
     */
    void Set(float m00, float m01, float m02, float m03,  // 1st column
             float m04, float m05, float m06, float m07,  // 2nd column
             float m08, float m09, float m10, float m11,  // 3rd column
             float m12, float m13, float m14, float m15); // 4th column

    /**
     * @brief       Set the components of the row number `index` of this matrix.
     *
     * @param index Select a row (range [0, 3]).
     * @param row   New row components (Vector4).
     */
    void SetRow(int index, const Vector4 & row);

    /**
     * @brief       Set the components of the row number `index` of this matrix.
     *
     * @param index Select a row (range [0, 3]).
     * @param row   New row components (Vector3).
     */
    void SetRow(int index, const Vector3 & row);

    /**
     * @brief       Set the components of the column number `index` of this matrix.
     *
     * @param index Select a column (range [0, 3]).
     * @param row   New column components (Vector4).
     */
    void SetColumn(int index, const Vector4 & column);

    /**
     * @brief       Set the components of the column number `index` of this matrix.
     *
     * @param index Select a column (range [0, 3]).
     * @param row   New column components (Vector3).
     */
    void SetColumn(int index, const Vector3 & column);

    /**
     * @brief       Transpose this matrix.
     */
    void Transpose(); // transpose itself and return reference

    /**
     * @brief       Invert this matrix ( i.e. M^-1 = adj(M) / det(M) ).
     */
    void Invert(); // check best inverse method before inverse

    /**
     * @brief       Make this matrix ortho-normale (Gram-Schmidt algorithm).
     */
    void Orthonormalize();

    /********************************************************
     *                  -- Getters --                       *
     ********************************************************/

    /**
     * @brief   Get the raw data of this matrix.
     *
     * @return  Matrix data (C-style array of range [0, 15]).
     */
    const float * Get() const;

    /**
     * @brief       Get the components of the row number `index` of this matrix.
     *
     * @param index Select a row (range [0, 3]).
     * @return      Selected row (Vector4)
     */
    Vector4 GetRow(int index) const;

    /**
     * @brief       Get the components of the column number `index` of this matrix.
     *
     * @param index Select a column (range [0, 3]).
     * @return      Selected column (Vector4)
     */
    Vector4 GetColumn(int index) const;

    /**
     * @brief       Get the direction of the left axis of this matrix.
     *
     * @return      left vector (not normalized).
     */
    Vector3 GetLeftAxis() const;

    /**
     * @brief       Get the direction of the up axis of this matrix.
     *
     * @return      up vector (not normalized).
     */
    Vector3 GetUpAxis() const;

    /**
     * @brief       Get the direction of the forward axis of this matrix.
     *
     * @return      forward vector (not normalized).
     */
    Vector3 GetForwardAxis() const;

    /**
     * @brief       Get the determinant of this matrix (based on first column values's cofactor).
     */
    float GetDeterminant() const;

    /**
     * @brief       Return a transposed copy of this matrix.
     */
    Matrix4 GetTransposed() const;

    /**
     * @brief       Return an inverted copy of this matrix ( i.e. M^-1 = adj(M) / det(M) ).
     * @exception   if `GetDeterminant < 0`, return an identity matrix.
     */
    Matrix4 GetInverted() const;

    /**
     * @brief       Return an ortho-normalized copy of this matrix (Gram-Schmidt algorithm).
     */
    Matrix4 GetOrthonormalized() const;

    // -- static getters --

    /**
     * @brief     Get translation, rotation and scale from an affine matrix.
     *
     * @exception if `one of the componant of scale is 0` return wrong rotation.
     * @exception if `scale is non-uniform` and `one of the componant is negative` return wrong rotation.
     */
    static void AffineDecompose(const Matrix4 & mat, Vector3 & translation, Quaternion & rotation, Vector3 & scale);

    /********************************************************
     *                 -- Operators --                      *
     ********************************************************/

    // -- compound assignment operators --

    Matrix4 & operator+=(const Matrix4 & rhs); // add rhs and update this object
    Matrix4 & operator-=(const Matrix4 & rhs); // subtract rhs and update this object
    Matrix4 & operator*=(const Matrix4 & rhs); // multiplication: M' = M1 * M2

    // -- arithmetic operators --

    Matrix4 operator+(const Matrix4 & rhs) const; // add rhs
    Matrix4 operator-(const Matrix4 & rhs) const; // subtract rhs
    Vector3 operator*(const Vector3 & rhs) const; // multiplication: v' = M * v
    Vector4 operator*(const Vector4 & rhs) const; // multiplication: v' = M * v
    Matrix4 operator*(const Matrix4 & rhs) const; // multiplication: M' = M1 * M2

    // -- comparison operators --

    bool operator==(const Matrix4 & rhs) const;
    bool operator!=(const Matrix4 & rhs) const;

    // -- member access, subscrip operators --

    float & operator[](int index);       // subscript operator mat[0], mat[1]
    float   operator[](int index) const; // subscript operator mat[0], mat[1]

    // -- other, function call operators --

    float & operator()(unsigned col, unsigned row);       // act like subscript operator mat[0][1]
    float   operator()(unsigned col, unsigned row) const; // act like subscript operator mat[0][1]

    // -- insertion operators --

    friend std::ostream & operator<<(std::ostream & os, const Matrix4 & m);

    /********************************************************
     *                    -- TODO --                        *
     ********************************************************/

    // static void QRDecompose(const Matrix4 & mat, Matrix4 & orth_mat, Matrix4 & up_triang_mat);
    // void InvertEuclidean(); // inverse of Euclidean transform matrix
    // void InvertAffine();    // inverse of affine transform matrix

    // -------------------

    // Matrix4 & Translate(const Vector3 & v);

    // Matrix4 & Rotate(float angle, const Vector3 & axis); // rotate angle(degree) along the given axix
    // Matrix4 & Rotate(float angle, float x, float y, float z);
    // Matrix4 & RotateX(float angle); // rotate on X-axis with degree
    // Matrix4 & RotateY(float angle); // rotate on Y-axis with degree
    // Matrix4 & RotateZ(float angle); // rotate on Z-axis with degree

    // Matrix4 & Scale(float scale);                  // uniform scale
    // Matrix4 & Scale(float sx, float sy, float sz); // scale by (sx, sy, sz) on each axis

    // Matrix4 & LookAt(const Vector3 & target, const Vector3 & up);

  private:
    float m_data[16];

    /**
     * @brief Cofactor of an element. Params are the elements of the 3x3 matrix you can get by removing row and column
     *        of that element from this matrix.
     */
    float GetCofactor(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8) const;

    /**
     * @brief Invert this matrix ( i.e. M^-1 = adj(M) / det(M) ).
     */
    void InvertGeneral();
};

} // namespace VDEngine

#endif /* VDENGINE_MATRIX_4_H_ */