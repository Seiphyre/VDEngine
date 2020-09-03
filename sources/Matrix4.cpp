#include "VDEngine/Math/Matrix4.h"

using namespace VDEngine;

/////////////////////////////////////////////////
/////////////////////////////////////////////////

inline Matrix4::Matrix4()
{
    // initially identity matrix
    Identity();
}

inline Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m04, float m05, float m06, float m07,
                        float m08, float m09, float m10, float m11, float m12, float m13, float m14, float m15)
{
    Set(m00, m01, m02, m03, m04, m05, m06, m07, m08, m09, m10, m11, m12, m13, m14, m15);
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////

Matrix4 Matrix4::CreateRotationMatrix(const Quaternion & quat)
{
    // https://gabormakesgames.com/blog_quats_to_matrix.html

    Vector3 right   = quat * Vector3::VecPosX(); // Right basis vector
    Vector3 up      = quat * Vector3::VecPosY(); // Up basis vector
    Vector3 forward = quat * Vector3::VecPosZ(); // Forward basis vector

    Matrix4 mat;

    mat.SetColumn(0, right);
    mat.SetColumn(1, up);
    mat.SetColumn(2, forward);

    return mat;
}

Matrix4 Matrix4::CreateTranslationMatrix(const Vector3 & translation)
{
    Matrix4 mat;

    mat.SetColumn(3, translation);

    return mat;
}

Matrix4 Matrix4::CreateScaleMatrix(const Vector3 & scale)
{
    Matrix4 mat;

    mat[0]  = scale.x;
    mat[5]  = scale.y;
    mat[10] = scale.z;

    return mat;
}

Matrix4 Matrix4::ComposeTRS(const Vector3 & translation, const Quaternion & rotation, const Vector3 & scale)
{
    Matrix4 mat;

    mat = CreateTranslationMatrix(translation) * CreateRotationMatrix(rotation) * CreateScaleMatrix(scale);

    return mat;
}

Matrix4 Matrix4::CreateOrtho(float left, float right, float bottom, float top, float z_near, float z_far)
{
    if (left == right)
    {
        std::cout << "[Warning] [Matrix4::CreateOrtho] left cannot equal right. Otho will be set to identity."
                  << std::endl;
        return (Matrix4());
    }

    if (bottom == top)
    {
        std::cout << "[Warning] [Matrix4::CreateOrtho] bottom cannot equal top. Otho will be set to identity."
                  << std::endl;
        return (Matrix4());
    }

    if (z_near == z_far)
    {
        std::cout << "[Warning] [Matrix4::CreateOrtho] z_near cannot equal z_far. Otho will be set to identity."
                  << std::endl;
        return (Matrix4());
    }

    // http://www.songho.ca/opengl/gl_projectionmatrix_mathml.html
    // http://learnwebgl.brown37.net/08_projections/projections_ortho.html

    Matrix4 mat;

    mat(0, 0) = 2.0f / (right - left);
    mat(1, 1) = 2.0f / (top - bottom);
    mat(2, 2) = -2.0f / (z_far - z_near);

    mat(3, 0) = -(right + left) / (right - left);
    mat(3, 1) = -(top + bottom) / (top - bottom);
    mat(3, 2) = -(z_far + z_near) / (z_far - z_near);

    // +-----------------+
    // | 0:0 .   .   3:0 |
    // |                 |
    // | .   1:1 .   3:1 |
    // |                 |
    // | .   .   2:2 3:2 |
    // |                 |
    // | .   .   .   .   |
    // +-----------------+

    return mat;
}

Matrix4 Matrix4::CreatePerspective(float fov_y, float aspect, float z_near, float z_far)
{
    // assert(abs(aspect) > EPSILON_FLOAT);

    if (abs(aspect) <= EPSILON_FLOAT)
    {
        std::cout << "[Warning] [Matrix4::CreatePerspective] Aspect cannot be 0. Perspective will be set to identity."
                  << std::endl;
        return (Matrix4());
    }

    if (abs(fov_y) <= EPSILON_FLOAT)
    {
        std::cout << "[Warning] [Matrix4::CreatePerspective] fov_y cannot be 0. Perspective will be set to identity."
                  << std::endl;
        return (Matrix4());
    }

    if (z_near == z_far)
    {
        std::cout
            << "[Warning] [Matrix4::CreatePerspective] z_near cannot equal z_far. Perspective will be set to identity."
            << std::endl;
        return (Matrix4());
    }

    // http://www.songho.ca/opengl/gl_projectionmatrix_mathml.html
    // http://learnwebgl.brown37.net/08_projections/projections_perspective.html

    float tan_half_fov = tan(to_radians(fov_y) / 2.0f);

    // Divide the angle by 2 to work with a right angle triangle
    // So: tan(angle) = opposite / adjacent

    // With: ANGLE = fov / 2, OPPOSITE = max height (2) / 2, ADJACENT = distance camera<=>projection plane
    // tan (fov / 2) = 1 / distance
    // distance = 1 / tan (fov / 2)
    // * Since openGL camera is looking at -Z, distance is negative
    // distance = -1 / tan (fov / 2)

    // According to the rule of similar triangle:
    // y'/distance = y / z
    // y' = (y * distance) / z
    // y' = y / (z / distance)
    // y' = y / (z / (-1 / tan (fov / 2)))
    // y' = y / (-z * tan (fov / 2))

    // And so: x' = x / (z / tan (fov / 2))
    // But x' is bound to [-aspect, aspect] (because y' is bound to [-1, 1] and x' = aspect * y')
    // We need to normalize it to [-1, 1] by dividing x' by aspect
    // x' = x / (-z * tan (fov / 2)) * 1/aspect
    // x' = x / (aspect * -z * tan (fov / 2))

    // We can remove -Z from x' and y', because openGL will divide x' and y' by W (= -Z)

    Matrix4 mat;

    float x = 1.0f / (aspect * tan_half_fov); // Project x on the projection plane
    float y = 1.0f / (tan_half_fov);          // Project y on the projection plane
    float z = -1.0f; // this will set W to Z (-1 because opengl use -Z if compute after view matrix)
    float w = 0;

    float a = -(z_far + z_near) / (z_far - z_near);        // Remap z to [-1, 1]
    float b = -(2.0f * z_far * z_near) / (z_far - z_near); // Remap z to [-1, 1]

    mat(0, 0) = x;
    mat(1, 1) = y;
    mat(2, 3) = z;
    mat(3, 3) = w;

    mat(2, 2) = a;
    mat(3, 2) = b;

    // +-----------------+
    // | X   .   .   .   |
    // |                 |
    // | .   Y   .   .   |
    // |                 |
    // | .   .   A   B   |
    // |                 |
    // | .   .   Z   W   |
    // +-----------------+

    return mat;
}

//

void Matrix4::AffineDecompose(const Matrix4 & p_mat, Vector3 & translation, Quaternion & rotation, Vector3 & scale)
{
    // https://github.com/mrdoob/three.js/blob/master/src/math/Matrix4.js (l.740 : decompose)
    // https://github.com/godotengine/godot/blob/master/core/math/basis.cpp (l.266 : get_scale + l.368 :
    // get_rotation_quat)
    // https://gabormakesgames.com/blog_decomposition_intro.html

    Matrix4 mat = p_mat;

    // Extract Translation ---------------------

    // 1. get the translation
    translation.Set(mat[12], mat[13], mat[14]);

    // Extract Scale ---------------------------

    // 1. get scale values
    float scale_x = Vector3(mat[0], mat[1], mat[2]).GetMagnitude();
    float scale_y = Vector3(mat[4], mat[5], mat[6]).GetMagnitude();
    float scale_z = Vector3(mat[8], mat[9], mat[10]).GetMagnitude();
    std::cout << scale_y << std::endl;
    scale.Set(scale_x, scale_y, scale_z);

    // 2. find scale sign
    float determinant = mat.GetDeterminant();

    if (determinant < 0)
        scale = scale * -1.0f;

    // Create pure rotation matrix ------------------

    // 1. remove translation matrix from "mat"
    mat[12] = 0;
    mat[13] = 0;
    mat[14] = 0;

    // 2. remove scale matrix from "mat"
    if (abs(scale_x) > EPSILON_FLOAT)
    {
        mat[0] *= (1 / scale.x);
        mat[1] *= (1 / scale.x);
        mat[2] *= (1 / scale.x);
    }

    if (abs(scale_y) > EPSILON_FLOAT)
    {
        mat[4] *= (1 / scale.y);
        mat[5] *= (1 / scale.y);
        mat[6] *= (1 / scale.y);
    }

    if (abs(scale_z) > EPSILON_FLOAT)
    {
        mat[8] *= (1 / scale.z);
        mat[9] *= (1 / scale.z);
        mat[10] *= (1 / scale.z);
    }
    // 3. Make sur the matrix is ortho
    mat.Orthonormalize();

    // Extract rotation -------------------------
    float trace = mat[0] + mat[5] + mat[10];
    float quat_x, quat_y, quat_z, quat_w;

    if (trace > 0.0f)
    {
        std::cout << "1" << std::endl;
        float s = 0.5f / sqrtf(trace + 1.0f);

        quat_w = (0.25f / s);
        quat_x = (mat[6] - mat[9]) * s;
        quat_y = (mat[8] - mat[2]) * s;
        quat_z = (mat[1] - mat[4]) * s;
    }
    else if ((mat[0] > mat[5]) && (mat[0] > mat[10]))
    {
        std::cout << "2" << std::endl;
        float s = sqrtf(1.0f + mat[0] - mat[5] - mat[10]) * 2.0f;

        quat_w = (mat[6] - mat[9]) / s;
        quat_x = (s * 0.25f);
        quat_y = (mat[4] + mat[1]) / s;
        quat_z = (mat[8] + mat[2]) / s;
    }
    else if (mat[5] > mat[10])
    {
        std::cout << "3" << std::endl;
        float s = sqrtf(1.0f + mat[5] - mat[0] - mat[10]) * 2.0f;

        quat_w = (mat[8] - mat[2]) / s;
        quat_x = (mat[4] + mat[1]) / s;
        quat_y = (s * 0.25f);
        quat_z = (mat[9] + mat[6]) / s;
    }
    else
    {
        std::cout << "4" << std::endl;
        float s = sqrtf(1.0f + mat[10] - mat[0] - mat[5]) * 2.0f;

        quat_w = (mat[1] - mat[4]) / s;
        quat_x = (mat[8] + mat[2]) / s;
        quat_y = (mat[9] + mat[6]) / s;
        quat_z = (s * 0.25f);
    }

    rotation.Set(quat_x, quat_y, quat_z, quat_w);
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////

inline void Matrix4::Set(float m00, float m01, float m02, float m03, float m04, float m05, float m06, float m07,
                         float m08, float m09, float m10, float m11, float m12, float m13, float m14, float m15)
{
    m_data[0]  = m00;
    m_data[1]  = m01;
    m_data[2]  = m02;
    m_data[3]  = m03;
    m_data[4]  = m04;
    m_data[5]  = m05;
    m_data[6]  = m06;
    m_data[7]  = m07;
    m_data[8]  = m08;
    m_data[9]  = m09;
    m_data[10] = m10;
    m_data[11] = m11;
    m_data[12] = m12;
    m_data[13] = m13;
    m_data[14] = m14;
    m_data[15] = m15;
}

inline void Matrix4::SetRow(int index, const Vector4 & v)
{
    m_data[index]      = v.x;
    m_data[index + 4]  = v.y;
    m_data[index + 8]  = v.z;
    m_data[index + 12] = v.w;
}

inline void Matrix4::SetRow(int index, const Vector3 & v)
{
    m_data[index]     = v.x;
    m_data[index + 4] = v.y;
    m_data[index + 8] = v.z;
}

inline void Matrix4::SetColumn(int index, const Vector4 & v)
{
    m_data[index * 4]     = v.x;
    m_data[index * 4 + 1] = v.y;
    m_data[index * 4 + 2] = v.z;
    m_data[index * 4 + 3] = v.w;
}

inline void Matrix4::SetColumn(int index, const Vector3 & v)
{
    m_data[index * 4]     = v.x;
    m_data[index * 4 + 1] = v.y;
    m_data[index * 4 + 2] = v.z;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////

inline const float * Matrix4::Get() const
{
    return m_data.data();
}

inline Vector4 Matrix4::GetRow(int index) const
{
    return Vector4(m_data[index], m_data[index + 4], m_data[index + 8], m_data[index + 12]);
}

inline Vector4 Matrix4::GetColumn(int index) const
{
    return Vector4(m_data[index * 4], m_data[index * 4 + 1], m_data[index * 4 + 2], m_data[index * 4 + 3]);
}

//

inline Vector3 Matrix4::GetLeftAxis() const
{
    return Vector3(m_data[0], m_data[1], m_data[2]);
}

inline Vector3 Matrix4::GetUpAxis() const
{
    return Vector3(m_data[4], m_data[5], m_data[6]);
}

inline Vector3 Matrix4::GetForwardAxis() const
{
    return Vector3(m_data[8], m_data[9], m_data[10]);
}

//

float Matrix4::GetDeterminant() const
{
    // https://www.geeksforgeeks.org/determinant-of-a-matrix/

    float cofactor_0 = GetCofactor(m_data[5], m_data[6], m_data[7], m_data[9], m_data[10], m_data[11], m_data[13],
                                   m_data[14], m_data[15]);
    // +-------------+
    // | 0  .  .  .  |
    // | .  5  9  13 |
    // | .  6  10 14 |
    // | .  7  11 15 |
    // +-------------+

    float cofactor_1 = GetCofactor(m_data[4], m_data[6], m_data[7], m_data[8], m_data[10], m_data[11], m_data[12],
                                   m_data[14], m_data[15]);
    // +-------------+
    // | .  4  8  12 |
    // | 1  .  .  .  |
    // | .  6  10 14 |
    // | .  7  11 15 |
    // +-------------+

    float cofactor_2 = GetCofactor(m_data[4], m_data[5], m_data[7], m_data[8], m_data[9], m_data[11], m_data[12],
                                   m_data[13], m_data[15]);
    // +-------------+
    // | .  4  8  12 |
    // | .  5  9  13 |
    // | 2  .  .  .  |
    // | .  7  11 15 |
    // +-------------+

    float cofactor_3 = GetCofactor(m_data[4], m_data[5], m_data[6], m_data[8], m_data[9], m_data[10], m_data[12],
                                   m_data[13], m_data[14]);
    // +-------------+
    // | .  4  8  12 |
    // | .  5  9  13 |
    // | .  6  10 14 |
    // | 3  .  .  .  |
    // +-------------+

    return (m_data[0] * cofactor_0) - (m_data[1] * cofactor_1) + (m_data[2] * cofactor_2) - (m_data[3] * cofactor_3);
}

//

Matrix4 Matrix4::GetInverted() const
{
    Matrix4 mat = *this;

    mat.Invert();

    return (mat);
}

Matrix4 Matrix4::GetTransposed() const
{
    Matrix4 mat = *this;

    mat.Transpose();

    return mat;
}

Matrix4 Matrix4::GetOrthonormalized() const
{
    Matrix4 mat = *this;

    mat.Orthonormalize();

    return (mat);
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////

inline void Matrix4::Identity()
{
    m_data[0] = m_data[5] = m_data[10] = m_data[15] = 1.0f;
    m_data[1] = m_data[2] = m_data[3] = m_data[4] = m_data[6] = m_data[7] = m_data[8] = m_data[9] = m_data[11] =
        m_data[12] = m_data[13] = m_data[14] = 0.0f;
}

void Matrix4::Transpose()
{
    std::swap(m_data[1], m_data[4]);
    std::swap(m_data[2], m_data[8]);
    std::swap(m_data[3], m_data[12]);
    std::swap(m_data[6], m_data[9]);
    std::swap(m_data[7], m_data[13]);
    std::swap(m_data[11], m_data[14]);
}

void Matrix4::Invert()
{
    // If the 4th row is [0,0,0,1] then it is affine matrix and
    // it has no projective transformation.
    // if (m_matrix[3] == 0 && m_matrix[7] == 0 && m_matrix[11] == 0 && m_matrix[15] == 1)
    //     this->InvertAffine();
    // else
    // {
    this->InvertGeneral();
    // }
}

///////////////////////////////////////////////////////////////////////////////
// compute the inverse of a general 4x4 matrix using Cramer's Rule
// If cannot find inverse, return indentity matrix
// M^-1 = adj(M) / det(M)
///////////////////////////////////////////////////////////////////////////////
void Matrix4::InvertGeneral()
{
    // https://www.geeksforgeeks.org/adjoint-inverse-matrix/

    // get cofactors of minor matrices
    float cofactor0 = GetCofactor(m_data[5], m_data[6], m_data[7], m_data[9], m_data[10], m_data[11], m_data[13],
                                  m_data[14], m_data[15]);
    float cofactor1 = GetCofactor(m_data[4], m_data[6], m_data[7], m_data[8], m_data[10], m_data[11], m_data[12],
                                  m_data[14], m_data[15]);
    float cofactor2 = GetCofactor(m_data[4], m_data[5], m_data[7], m_data[8], m_data[9], m_data[11], m_data[12],
                                  m_data[13], m_data[15]);
    float cofactor3 = GetCofactor(m_data[4], m_data[5], m_data[6], m_data[8], m_data[9], m_data[10], m_data[12],
                                  m_data[13], m_data[14]);

    // get determinant
    float determinant = m_data[0] * cofactor0 - m_data[1] * cofactor1 + m_data[2] * cofactor2 - m_data[3] * cofactor3;

    if (fabs(determinant) <= EPSILON_FLOAT)
    {
        std::cout << "[Warning] [Matrix4::InvertGeneral] Determinant is negative. Cannot invert the matrix. (Did you "
                     "scale by zero ?)"
                  << std::endl;
        Identity();
        return;
    }

    // get rest of cofactors for adj(M)
    float cofactor4 = GetCofactor(m_data[1], m_data[2], m_data[3], m_data[9], m_data[10], m_data[11], m_data[13],
                                  m_data[14], m_data[15]);
    float cofactor5 = GetCofactor(m_data[0], m_data[2], m_data[3], m_data[8], m_data[10], m_data[11], m_data[12],
                                  m_data[14], m_data[15]);
    float cofactor6 = GetCofactor(m_data[0], m_data[1], m_data[3], m_data[8], m_data[9], m_data[11], m_data[12],
                                  m_data[13], m_data[15]);
    float cofactor7 = GetCofactor(m_data[0], m_data[1], m_data[2], m_data[8], m_data[9], m_data[10], m_data[12],
                                  m_data[13], m_data[14]);

    float cofactor8  = GetCofactor(m_data[1], m_data[2], m_data[3], m_data[5], m_data[6], m_data[7], m_data[13],
                                  m_data[14], m_data[15]);
    float cofactor9  = GetCofactor(m_data[0], m_data[2], m_data[3], m_data[4], m_data[6], m_data[7], m_data[12],
                                  m_data[14], m_data[15]);
    float cofactor10 = GetCofactor(m_data[0], m_data[1], m_data[3], m_data[4], m_data[5], m_data[7], m_data[12],
                                   m_data[13], m_data[15]);
    float cofactor11 = GetCofactor(m_data[0], m_data[1], m_data[2], m_data[4], m_data[5], m_data[6], m_data[12],
                                   m_data[13], m_data[14]);

    float cofactor12 = GetCofactor(m_data[1], m_data[2], m_data[3], m_data[5], m_data[6], m_data[7], m_data[9],
                                   m_data[10], m_data[11]);
    float cofactor13 = GetCofactor(m_data[0], m_data[2], m_data[3], m_data[4], m_data[6], m_data[7], m_data[8],
                                   m_data[10], m_data[11]);
    float cofactor14 =
        GetCofactor(m_data[0], m_data[1], m_data[3], m_data[4], m_data[5], m_data[7], m_data[8], m_data[9], m_data[11]);
    float cofactor15 =
        GetCofactor(m_data[0], m_data[1], m_data[2], m_data[4], m_data[5], m_data[6], m_data[8], m_data[9], m_data[10]);

    // build inverse matrix = adj(M) / det(M)
    // adjugate of M is the transpose of the cofactor matrix of M
    float invDeterminant = 1.0f / determinant;
    m_data[0]            = invDeterminant * cofactor0;
    m_data[1]            = -invDeterminant * cofactor4;
    m_data[2]            = invDeterminant * cofactor8;
    m_data[3]            = -invDeterminant * cofactor12;

    m_data[4] = -invDeterminant * cofactor1;
    m_data[5] = invDeterminant * cofactor5;
    m_data[6] = -invDeterminant * cofactor9;
    m_data[7] = invDeterminant * cofactor13;

    m_data[8]  = invDeterminant * cofactor2;
    m_data[9]  = -invDeterminant * cofactor6;
    m_data[10] = invDeterminant * cofactor10;
    m_data[11] = -invDeterminant * cofactor14;

    m_data[12] = -invDeterminant * cofactor3;
    m_data[13] = invDeterminant * cofactor7;
    m_data[14] = -invDeterminant * cofactor11;
    m_data[15] = invDeterminant * cofactor15;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////

void Matrix4::Orthonormalize()
{
    // Based on Gram-Schmidt algorithm
    // https://www.ucl.ac.uk/~ucahmdl/LessonPlans/Lesson10.pdf

    // TODO: Check if Vectors are already Orthogonal and Orthonormal to avoid useless calculations.

    Vector3 x = to_vector3(GetColumn(0));
    Vector3 y = to_vector3(GetColumn(1));
    Vector3 z = to_vector3(GetColumn(2));

    // -- 1. Make matrix vectors (X, Y, Z) orthogonal ---

    // Definition: We say that 2 vectors are ORTHOGONAL if they are perpendicular to each other.
    // i.e. the dot product of the two vectors is zero.

    // Definition: We say that a set of vectors are mutually ORTHOGONAL if every pair of vectors is
    // orthogonal.

    // Calculate Y (make it orthogonal with X)
    Vector3 proj_x_onto_y = x * (Vector3::Dot(x, y));

    y = y - proj_x_onto_y;

    // Calculate Z (Make it orthogonal with X and Y)
    Vector3 proj_x_onto_z = x * (Vector3::Dot(x, z));
    Vector3 proj_y_onto_z = y * Vector3::Dot(y, z);

    z = z - proj_x_onto_z - proj_y_onto_z;

    // -- 2. Normalize them ---

    // Definition: A set of vectors S is ORTHONORMAL if every vector in has magnitude 1 and the set of vectors are
    // mutually orthogonal.

    x.Normalize();
    y.Normalize();
    z.Normalize();

    // -- 3. Rebuild the matrix with the new vectors ----

    SetColumn(0, x);
    SetColumn(1, y);
    SetColumn(2, z);
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

inline Matrix4 Matrix4::operator+(const Matrix4 & rhs) const
{
    return Matrix4(m_data[0] + rhs[0], m_data[1] + rhs[1], m_data[2] + rhs[2], m_data[3] + rhs[3], m_data[4] + rhs[4],
                   m_data[5] + rhs[5], m_data[6] + rhs[6], m_data[7] + rhs[7], m_data[8] + rhs[8], m_data[9] + rhs[9],
                   m_data[10] + rhs[10], m_data[11] + rhs[11], m_data[12] + rhs[12], m_data[13] + rhs[13],
                   m_data[14] + rhs[14], m_data[15] + rhs[15]);
}

inline Matrix4 Matrix4::operator-(const Matrix4 & rhs) const
{
    return Matrix4(m_data[0] - rhs[0], m_data[1] - rhs[1], m_data[2] - rhs[2], m_data[3] - rhs[3], m_data[4] - rhs[4],
                   m_data[5] - rhs[5], m_data[6] - rhs[6], m_data[7] - rhs[7], m_data[8] - rhs[8], m_data[9] - rhs[9],
                   m_data[10] - rhs[10], m_data[11] - rhs[11], m_data[12] - rhs[12], m_data[13] - rhs[13],
                   m_data[14] - rhs[14], m_data[15] - rhs[15]);
}

inline Vector4 Matrix4::operator*(const Vector4 & rhs) const
{
    return Vector4(m_data[0] * rhs.x + m_data[4] * rhs.y + m_data[8] * rhs.z + m_data[12] * rhs.w,
                   m_data[1] * rhs.x + m_data[5] * rhs.y + m_data[9] * rhs.z + m_data[13] * rhs.w,
                   m_data[2] * rhs.x + m_data[6] * rhs.y + m_data[10] * rhs.z + m_data[14] * rhs.w,
                   m_data[3] * rhs.x + m_data[7] * rhs.y + m_data[11] * rhs.z + m_data[15] * rhs.w);
}

inline Vector3 Matrix4::operator*(const Vector3 & rhs) const
{
    return Vector3(m_data[0] * rhs.x + m_data[4] * rhs.y + m_data[8] * rhs.z + m_data[12],
                   m_data[1] * rhs.x + m_data[5] * rhs.y + m_data[9] * rhs.z + m_data[13],
                   m_data[2] * rhs.x + m_data[6] * rhs.y + m_data[10] * rhs.z + m_data[14]);
}

inline Matrix4 Matrix4::operator*(const Matrix4 & n) const
{
    return Matrix4(m_data[0] * n[0] + m_data[4] * n[1] + m_data[8] * n[2] + m_data[12] * n[3],
                   m_data[1] * n[0] + m_data[5] * n[1] + m_data[9] * n[2] + m_data[13] * n[3],
                   m_data[2] * n[0] + m_data[6] * n[1] + m_data[10] * n[2] + m_data[14] * n[3],
                   m_data[3] * n[0] + m_data[7] * n[1] + m_data[11] * n[2] + m_data[15] * n[3],
                   m_data[0] * n[4] + m_data[4] * n[5] + m_data[8] * n[6] + m_data[12] * n[7],
                   m_data[1] * n[4] + m_data[5] * n[5] + m_data[9] * n[6] + m_data[13] * n[7],
                   m_data[2] * n[4] + m_data[6] * n[5] + m_data[10] * n[6] + m_data[14] * n[7],
                   m_data[3] * n[4] + m_data[7] * n[5] + m_data[11] * n[6] + m_data[15] * n[7],
                   m_data[0] * n[8] + m_data[4] * n[9] + m_data[8] * n[10] + m_data[12] * n[11],
                   m_data[1] * n[8] + m_data[5] * n[9] + m_data[9] * n[10] + m_data[13] * n[11],
                   m_data[2] * n[8] + m_data[6] * n[9] + m_data[10] * n[10] + m_data[14] * n[11],
                   m_data[3] * n[8] + m_data[7] * n[9] + m_data[11] * n[10] + m_data[15] * n[11],
                   m_data[0] * n[12] + m_data[4] * n[13] + m_data[8] * n[14] + m_data[12] * n[15],
                   m_data[1] * n[12] + m_data[5] * n[13] + m_data[9] * n[14] + m_data[13] * n[15],
                   m_data[2] * n[12] + m_data[6] * n[13] + m_data[10] * n[14] + m_data[14] * n[15],
                   m_data[3] * n[12] + m_data[7] * n[13] + m_data[11] * n[14] + m_data[15] * n[15]);
}

//

inline Matrix4 & Matrix4::operator+=(const Matrix4 & rhs)
{
    m_data[0] += rhs[0];
    m_data[1] += rhs[1];
    m_data[2] += rhs[2];
    m_data[3] += rhs[3];
    m_data[4] += rhs[4];
    m_data[5] += rhs[5];
    m_data[6] += rhs[6];
    m_data[7] += rhs[7];
    m_data[8] += rhs[8];
    m_data[9] += rhs[9];
    m_data[10] += rhs[10];
    m_data[11] += rhs[11];
    m_data[12] += rhs[12];
    m_data[13] += rhs[13];
    m_data[14] += rhs[14];
    m_data[15] += rhs[15];
    return *this;
}

inline Matrix4 & Matrix4::operator-=(const Matrix4 & rhs)
{
    m_data[0] -= rhs[0];
    m_data[1] -= rhs[1];
    m_data[2] -= rhs[2];
    m_data[3] -= rhs[3];
    m_data[4] -= rhs[4];
    m_data[5] -= rhs[5];
    m_data[6] -= rhs[6];
    m_data[7] -= rhs[7];
    m_data[8] -= rhs[8];
    m_data[9] -= rhs[9];
    m_data[10] -= rhs[10];
    m_data[11] -= rhs[11];
    m_data[12] -= rhs[12];
    m_data[13] -= rhs[13];
    m_data[14] -= rhs[14];
    m_data[15] -= rhs[15];
    return *this;
}

inline Matrix4 & Matrix4::operator*=(const Matrix4 & rhs)
{
    *this = *this * rhs;
    return *this;
}

//

inline bool Matrix4::operator==(const Matrix4 & n) const
{
    return (m_data[0] == n[0]) && (m_data[1] == n[1]) && (m_data[2] == n[2]) && (m_data[3] == n[3]) &&
           (m_data[4] == n[4]) && (m_data[5] == n[5]) && (m_data[6] == n[6]) && (m_data[7] == n[7]) &&
           (m_data[8] == n[8]) && (m_data[9] == n[9]) && (m_data[10] == n[10]) && (m_data[11] == n[11]) &&
           (m_data[12] == n[12]) && (m_data[13] == n[13]) && (m_data[14] == n[14]) && (m_data[15] == n[15]);
}

inline bool Matrix4::operator!=(const Matrix4 & n) const
{
    return (m_data[0] != n[0]) || (m_data[1] != n[1]) || (m_data[2] != n[2]) || (m_data[3] != n[3]) ||
           (m_data[4] != n[4]) || (m_data[5] != n[5]) || (m_data[6] != n[6]) || (m_data[7] != n[7]) ||
           (m_data[8] != n[8]) || (m_data[9] != n[9]) || (m_data[10] != n[10]) || (m_data[11] != n[11]) ||
           (m_data[12] != n[12]) || (m_data[13] != n[13]) || (m_data[14] != n[14]) || (m_data[15] != n[15]);
}

//

inline const float & Matrix4::operator[](int index) const
{
    return m_data[index];
}

inline float & Matrix4::operator[](int index)
{
    return m_data[index];
}

float & Matrix4::operator()(unsigned col, unsigned row)
{
    // https: // isocpp.org/wiki/faq/operator-overloading#matrix-subscript-op

    assert(col < 4);
    assert(row < 4);

    return m_data[4 * col + row];
}

float Matrix4::operator()(unsigned col, unsigned row) const
{
    // https://isocpp.org/wiki/faq/operator-overloading#matrix-subscript-op

    assert(col < 4);
    assert(row < 4);

    return m_data[4 * col + row];
}

std::ostream & VDEngine::operator<<(std::ostream & os, const Matrix4 & m)
{
    os << std::fixed << std::setprecision(5);

    os << "[" << std::setw(10) << m(0, 0) << " " << std::setw(10) << m(1, 0) << " " << std::setw(10) << m(2, 0) << " "
       << std::setw(10) << m(3, 0) << "]\n"
       << "[" << std::setw(10) << m(0, 1) << " " << std::setw(10) << m(1, 1) << " " << std::setw(10) << m(2, 1) << " "
       << std::setw(10) << m(3, 1) << "]\n"
       << "[" << std::setw(10) << m(0, 2) << " " << std::setw(10) << m(1, 2) << " " << std::setw(10) << m(2, 2) << " "
       << std::setw(10) << m(3, 2) << "]\n"
       << "[" << std::setw(10) << m(0, 3) << " " << std::setw(10) << m(1, 3) << " " << std::setw(10) << m(2, 3) << " "
       << std::setw(10) << m(3, 3) << "]\n";

    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}

///////////////////////////////////////////////////////////////////////////////
// compute cofactor of 3x3 minor matrix without sign
// input params are 9 elements of the minor matrix
// NOTE: The caller must know its sign.
///////////////////////////////////////////////////////////////////////////////
float Matrix4::GetCofactor(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7,
                           float m8) const
{
    return m0 * (m4 * m8 - m5 * m7) - m1 * (m3 * m8 - m5 * m6) + m2 * (m3 * m7 - m4 * m6);
}

// void Matrix4::QRDecompose(const Matrix4 & input_mat, Matrix4 & orth_mat, Matrix4 & up_triang_mat)
// {
//     // Definition:
//     // A square matrix is called LOWER TRIANGULAR if all the entries above the main diagonal are zero.
//     // Similarly, a square matrix is called UPPER TRIANGULAR if all the entries below the main diagonal are zero.
//     // A TRIANGULAR MATRIX is one that is either lower triangular or upper triangular.
//     // A matrix that is both upper and lower triangular is called a DIAGONAL MATRIX.

//     // [A = Q.R] == [Qt.A = Q.Qt.R] == [Qt.A = I.R] == [R = Qt.A]
//     //
//     // where:
//     //          A -> Input matrix
//     //          Q -> Orthogonal matrix (can be found with Gram-Schimdt algorith)
//     //          R -> Upper Triangular matrix
//     //          Qt -> transpose of Q
//     //          I -> identity matrix

//     // https://gabormakesgames.com/blog_decomposition_qr.html

//     // Extract Orthogonal matrix
//     orth_mat = input_mat.GetOrthonormalized();

//     // Extract Upper Triangular matrix
//     up_triang_mat = Matrix4();

//     up_triang_mat = orth_mat.GetTransposed() * input_mat;
// }

///////////////////////////////////////////////////////////////////////////////
// compute the inverse of 4x4 Euclidean transformation matrix
//
// Euclidean transformation is translation, rotation, and reflection.
// With Euclidean transform, only the position and orientation of the object
// will be changed. Euclidean transform does not change the shape of an object
// (no scaling). Length and angle are reserved.
//
// Use inverseAffine() if the matrix has scale and shear transformation.
//
///////////////////////////////////////////////////////////////////////////////
// void Matrix4::InvertEuclidean()
// {
//     // transpose 3x3 rotation matrix part
//     float tmp;
//     tmp         = m_matrix[1];
//     m_matrix[1] = m_matrix[4];
//     m_matrix[4] = tmp;
//     tmp         = m_matrix[2];
//     m_matrix[2] = m_matrix[8];
//     m_matrix[8] = tmp;
//     tmp         = m_matrix[6];
//     m_matrix[6] = m_matrix[9];
//     m_matrix[9] = tmp;

//     // compute translation part -R^T * T
//     float x      = m_matrix[12];
//     float y      = m_matrix[13];
//     float z      = m_matrix[14];
//     m_matrix[12] = -(m_matrix[0] * x + m_matrix[4] * y + m_matrix[8] * z);
//     m_matrix[13] = -(m_matrix[1] * x + m_matrix[5] * y + m_matrix[9] * z);
//     m_matrix[14] = -(m_matrix[2] * x + m_matrix[6] * y + m_matrix[10] * z);

//     // last row should be unchanged (0,0,0,1)
// }

///////////////////////////////////////////////////////////////////////////////
// compute the inverse of a 4x4 affine transformation matrix
//
// Affine transformations are generalizations of Euclidean transformations.
// Affine transformation includes translation, rotation, reflection, scaling,
// and shearing. Length and angle are NOT preserved.
//
///////////////////////////////////////////////////////////////////////////////
// void Matrix4::InvertAffine()
// {
//     // R^-1
//     Matrix4 r(m_matrix[0], m_matrix[1], m_matrix[2], 0, m_matrix[4], m_matrix[5], m_matrix[6], 0, m_matrix[8],
//               m_matrix[9], m_matrix[10], 0, 0, 0, 0, 1);

//     r.InvertGeneral();

//     m_matrix[0] = r[0];
//     m_matrix[1] = r[1];
//     m_matrix[2] = r[2];

//     m_matrix[4] = r[4];
//     m_matrix[5] = r[5];
//     m_matrix[6] = r[6];

//     m_matrix[8]  = r[8];
//     m_matrix[9]  = r[9];
//     m_matrix[10] = r[10];

//     // -R^-1 * T
//     float x = m_matrix[12];
//     float y = m_matrix[13];
//     float z = m_matrix[14];

//     m_matrix[12] = -(r[0] * x + r[4] * y + r[8] * z);
//     m_matrix[13] = -(r[1] * x + r[5] * y + r[9] * z);
//     m_matrix[14] = -(r[2] * x + r[6] * y + r[10] * z);

//     // last row should be unchanged (0,0,0,1)
//     // m_matrix[3] = m_matrix[7] = m_matrix[11] = 0.0f;
//     // m_matrix[15] = 1.0f;
// }

// ///////////////////////////////////////////////////////////////////////////////
// // retrieve angles in degree from rotation matrix, M = Rx*Ry*Rz
// // Rx: rotation about X-axis, pitch
// // Ry: rotation about Y-axis, yaw(heading)
// // Rz: rotation about Z-axis, roll
// //    Rx           Ry          Rz
// // |1  0   0| | Cy  0 Sy| |Cz -Sz 0|   | CyCz        -CySz         Sy  |
// // |0 Cx -Sx|*|  0  1  0|*|Sz  Cz 0| = | SxSyCz+CxSz -SxSySz+CxCz -SxCy|
// // |0 Sx  Cx| |-Sy  0 Cy| | 0   0 1|   |-CxSyCz+SxSz  CxSySz+SxCz  CxCy|
// //
// // Pitch: atan(-m_matrix[9] / m_matrix[10]) = atan(SxCy/CxCy)
// // Yaw  : asin(m_matrix[8]) = asin(Sy)
// // Roll : atan(-m_matrix[4] / m_matrix[0]) = atan(SzCy/CzCy)
// ///////////////////////////////////////////////////////////////////////////////
// Vector3 Matrix4::GetAngle() const
// {
//     float pitch, yaw, roll; // 3 angles

//     // find yaw (around y-axis) first
//     yaw = asinf(m_matrix[8]);
//     yaw = to_degrees(yaw);

//     // NOTE: asin() returns -90~+90, so correct the angle range -180~+180
//     // using z value of forward vector (m_matrix[10])
//     if (m_matrix[10] < 0)
//     {
//         if (yaw >= 0)
//             yaw = 180.0f - yaw;
//         else
//             yaw = -180.0f - yaw;
//     }

//     // find roll (around z-axis) and pitch (around x-axis)
//     // if forward vector is (1,0,0) or (-1,0,0), then m_matrix[0]=m_matrix[4]=m_matrix[9]=m_matrix[10]=0
//     if (m_matrix[0] > -EPSILON_FLOAT && m_matrix[0] < EPSILON_FLOAT)
//     {
//         roll = 0; //@@ assume roll=0

//         pitch = atan2f(m_matrix[1], m_matrix[5]);
//         pitch = to_degrees(pitch);
//     }
//     else
//     {
//         roll = atan2f(-m_matrix[4], m_matrix[0]);
//         roll = to_degrees(roll);

//         pitch = atan2f(-m_matrix[9], m_matrix[10]);
//         pitch = to_degrees(pitch);
//     }

//     return Vector3(pitch, yaw, roll);
// }

// Matrix4 & Matrix4::Translate(const Vector3 & v)
// {
//     m_matrix[0] += m_matrix[3] * v.x;
//     m_matrix[4] += m_matrix[7] * v.x;
//     m_matrix[8] += m_matrix[11] * v.x;
//     m_matrix[12] += m_matrix[15] * v.x;
//     m_matrix[1] += m_matrix[3] * v.y;
//     m_matrix[5] += m_matrix[7] * v.y;
//     m_matrix[9] += m_matrix[11] * v.y;
//     m_matrix[13] += m_matrix[15] * v.y;
//     m_matrix[2] += m_matrix[3] * v.z;
//     m_matrix[6] += m_matrix[7] * v.z;
//     m_matrix[10] += m_matrix[11] * v.z;
//     m_matrix[14] += m_matrix[15] * v.z;

//     return *this;
// }

// ///////////////////////////////////////////////////////////////////////////////
// // uniform scale
// ///////////////////////////////////////////////////////////////////////////////
// Matrix4 & Matrix4::Scale(float s)
// {
//     return Scale(s, s, s);
// }

// Matrix4 & Matrix4::Scale(float x, float y, float z)
// {
//     m_matrix[0] *= x;
//     m_matrix[4] *= x;
//     m_matrix[8] *= x;
//     m_matrix[12] *= x;
//     m_matrix[1] *= y;
//     m_matrix[5] *= y;
//     m_matrix[9] *= y;
//     m_matrix[13] *= y;
//     m_matrix[2] *= z;
//     m_matrix[6] *= z;
//     m_matrix[10] *= z;
//     m_matrix[14] *= z;

//     return *this;
// }

// ///////////////////////////////////////////////////////////////////////////////
// // build a rotation matrix with given angle(degree) and rotation axis, then
// // multiply it with this object
// ///////////////////////////////////////////////////////////////////////////////
// Matrix4 & Matrix4::Rotate(float angle, const Vector3 & axis)
// {
//     return Rotate(angle, axis.x, axis.y, axis.z);
// }

// Matrix4 & Matrix4::Rotate(float angle, float x, float y, float z)
// {
//     float c  = cosf(to_radians(angle)); // cosine
//     float s  = sinf(to_radians(angle)); // sine
//     float c1 = 1.0f - c;                // 1 - c
//     float m0 = m_matrix[0], m4 = m_matrix[4], m8 = m_matrix[8], m12 = m_matrix[12], m1 = m_matrix[1], m5 =
//     m_matrix[5],
//           m9 = m_matrix[9], m13 = m_matrix[13], m2 = m_matrix[2], m6 = m_matrix[6], m10 = m_matrix[10],
//           m14 = m_matrix[14];

//     // build rotation matrix
//     float r0  = x * x * c1 + c;
//     float r1  = x * y * c1 + z * s;
//     float r2  = x * z * c1 - y * s;
//     float r4  = x * y * c1 - z * s;
//     float r5  = y * y * c1 + c;
//     float r6  = y * z * c1 + x * s;
//     float r8  = x * z * c1 + y * s;
//     float r9  = y * z * c1 - x * s;
//     float r10 = z * z * c1 + c;

//     // multiply rotation matrix
//     m_matrix[0]  = r0 * m0 + r4 * m1 + r8 * m2;
//     m_matrix[1]  = r1 * m0 + r5 * m1 + r9 * m2;
//     m_matrix[2]  = r2 * m0 + r6 * m1 + r10 * m2;
//     m_matrix[4]  = r0 * m4 + r4 * m5 + r8 * m6;
//     m_matrix[5]  = r1 * m4 + r5 * m5 + r9 * m6;
//     m_matrix[6]  = r2 * m4 + r6 * m5 + r10 * m6;
//     m_matrix[8]  = r0 * m8 + r4 * m9 + r8 * m10;
//     m_matrix[9]  = r1 * m8 + r5 * m9 + r9 * m10;
//     m_matrix[10] = r2 * m8 + r6 * m9 + r10 * m10;
//     m_matrix[12] = r0 * m12 + r4 * m13 + r8 * m14;
//     m_matrix[13] = r1 * m12 + r5 * m13 + r9 * m14;
//     m_matrix[14] = r2 * m12 + r6 * m13 + r10 * m14;

//     return *this;
// }

// Matrix4 & Matrix4::RotateX(float angle)
// {
//     float c  = cosf(to_radians(angle));
//     float s  = sinf(to_radians(angle));
//     float m1 = m_matrix[1], m2 = m_matrix[2], m5 = m_matrix[5], m6 = m_matrix[6], m9 = m_matrix[9], m10 =
//     m_matrix[10],
//           m13 = m_matrix[13], m14 = m_matrix[14];

//     m_matrix[1]  = m1 * c + m2 * -s;
//     m_matrix[2]  = m1 * s + m2 * c;
//     m_matrix[5]  = m5 * c + m6 * -s;
//     m_matrix[6]  = m5 * s + m6 * c;
//     m_matrix[9]  = m9 * c + m10 * -s;
//     m_matrix[10] = m9 * s + m10 * c;
//     m_matrix[13] = m13 * c + m14 * -s;
//     m_matrix[14] = m13 * s + m14 * c;

//     return *this;
// }

// Matrix4 & Matrix4::RotateY(float angle)
// {
//     float c  = cosf(to_radians(angle));
//     float s  = sinf(to_radians(angle));
//     float m0 = m_matrix[0], m2 = m_matrix[2], m4 = m_matrix[4], m6 = m_matrix[6], m8 = m_matrix[8], m10 =
//     m_matrix[10],
//           m12 = m_matrix[12], m14 = m_matrix[14];

//     m_matrix[0]  = m0 * c + m2 * s;
//     m_matrix[2]  = m0 * -s + m2 * c;
//     m_matrix[4]  = m4 * c + m6 * s;
//     m_matrix[6]  = m4 * -s + m6 * c;
//     m_matrix[8]  = m8 * c + m10 * s;
//     m_matrix[10] = m8 * -s + m10 * c;
//     m_matrix[12] = m12 * c + m14 * s;
//     m_matrix[14] = m12 * -s + m14 * c;

//     return *this;
// }

// Matrix4 & Matrix4::RotateZ(float angle)
// {
//     float c  = cosf(to_radians(angle));
//     float s  = sinf(to_radians(angle));
//     float m0 = m_matrix[0], m1 = m_matrix[1], m4 = m_matrix[4], m5 = m_matrix[5], m8 = m_matrix[8], m9 =
//     m_matrix[9],
//           m12 = m_matrix[12], m13 = m_matrix[13];

//     m_matrix[0]  = m0 * c + m1 * -s;
//     m_matrix[1]  = m0 * s + m1 * c;
//     m_matrix[4]  = m4 * c + m5 * -s;
//     m_matrix[5]  = m4 * s + m5 * c;
//     m_matrix[8]  = m8 * c + m9 * -s;
//     m_matrix[9]  = m8 * s + m9 * c;
//     m_matrix[12] = m12 * c + m13 * -s;
//     m_matrix[13] = m12 * s + m13 * c;

//     return *this;
// }

// ///////////////////////////////////////////////////////////////////////////////
// // rotate matrix to face along the target direction
// // NOTE: This function will clear the previous rotation and scale info and
// // rebuild the matrix with the target vector. But it will keep the previous
// // translation values.
// // NOTE: It is for rotating object to look at the target, NOT for camera
// ///////////////////////////////////////////////////////////////////////////////
// Matrix4 & Matrix4::LookAt(const Vector3 & target)
// {
//     Vector3 position = Vector3(m_matrix[12], m_matrix[13], m_matrix[14]);
//     Vector3 up;   // up vector of object
//     Vector3 left; // left vector of object

//     // compute forward vector and normalize
//     Vector3 forward = target - position;
//     forward.Normalize();

//     // compute temporal up vector
//     // if forward vector is near Y-axis, use up vector (0,0,-1) or (0,0,1)
//     if (fabs(forward.x) < EPSILON_FLOAT && fabs(forward.z) < EPSILON_FLOAT)
//     {
//         // forward vector is pointing +Y axis
//         if (forward.y > 0)
//             up.Set(0, 0, -1);
//         // forward vector is pointing -Y axis
//         else
//             up.Set(0, 0, 1);
//     }
//     else
//     {
//         // assume up vector is +Y axis
//         up.Set(0, 1, 0);
//     }

//     // compute left vector
//     left = Vector3::Cross(up, forward);
//     left.Normalize();

//     // re-compute up vector
//     up = Vector3::Cross(forward, left);
//     // up.normalize();

//     // NOTE: overwrite rotation and scale info of the current matrix
//     this->SetColumn(0, left);
//     this->SetColumn(1, up);
//     this->SetColumn(2, forward);

//     return *this;
// }

// Matrix4 & Matrix4::LookAt(const Vector3 & target, const Vector3 & upVec)
// {
//     Vector3 position = Vector3(m_matrix[12], m_matrix[13], m_matrix[14]);

//     // compute forward vector
//     Vector3 forward = target - position;
//     forward.Normalize();

//     // compute left vector
//     Vector3 left = Vector3::Cross(upVec, forward);
//     left.Normalize();

//     // compute orthonormal up vector
//     Vector3 up = Vector3::Cross(forward, left);
//     up.Normalize();

//     // NOTE: overwrite rotation and scale info of the current matrix
//     this->SetColumn(0, left);
//     this->SetColumn(1, up);
//     this->SetColumn(2, forward);

//     return *this;
// }

/////////////////////////////////////////////////
/////////////////////////////////////////////////