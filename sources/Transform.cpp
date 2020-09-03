#include "VDEngine/Core/Transform.h"
#include "VDEngine/Core/GameObject.h"

using namespace VDEngine;

Transform::Transform()
{
    position = Vector3::VecZero();
    scale    = Vector3::VecOne();
    rotation = Quaternion();
}

Transform::~Transform()
{
}

// -------------------------------------

Matrix4 Transform::GetModelMatrix(Space space) const
{
    Matrix4 model_matrix;

    switch (space)
    {
        case LOCAL:
            model_matrix = Matrix4::ComposeTRS(position, rotation, scale);
            break;
        case GLOBAL:
            model_matrix = GetGlobalModelMatrix();
            break;
        default:
            std::cout << "[Warning] [Transform::GetModelMatrix] unknown space. identity matrix will be returned."
                      << std::endl;
            break;
    }

    return model_matrix;
}

Matrix4 Transform::GetGlobalModelMatrix() const
{
    if (m_game_object->GetParent() != nullptr)
    {
        Matrix4 parent_matrix = m_game_object->GetParent()->GetTransform()->GetGlobalModelMatrix();
        return (parent_matrix * GetModelMatrix());
    }

    return GetModelMatrix();
}

Matrix4 Transform::GetNormalMatrix(Space space) const
{
    return GetModelMatrix(space).GetInverted().GetTransposed();
}

// -------------------------------------

Vector3 Transform::GetForwardDir() const
{
    return (rotation.GetZAxis());
}
Vector3 Transform::GetUpDir() const
{
    return (rotation.GetYAxis());
}
Vector3 Transform::GetRightDir() const
{
    return (-rotation.GetXAxis());
}

// -------------------------------------

void Transform::Translate(const Vector3 & translation)
{
    position += translation;
}

void Transform::Translate(float x, float y, float z)
{
    Translate(Vector3(x, y, z));
}

void Transform::Rotate(const Vector3 & eulers)
{
    rotation *= Quaternion::CreateFromEuler(eulers);
}
void Transform::Rotate(float x, float y, float z)
{
    Rotate(Vector3(x, y, z));
}

void Transform::Rotate(float angle, const Vector3 & rotation_axis)
{
    rotation *= Quaternion::CreateFromAxisAngle(rotation_axis, angle);
}

void Transform::LookAt(const Vector3 & target, const Vector3 & up)
{
    Vector3 look_direction = target - position;

    rotation = Quaternion::LookRotation(look_direction, up);
}