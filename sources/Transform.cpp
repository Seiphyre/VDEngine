#include "VDEngine/Core/Transform.h"

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

Matrix4 Transform::GetMatrix() const
{
    return Matrix4::ComposeTRS(position, rotation, scale);
}

Matrix4 Transform::GetLocalMatrix() const
{
    if (m_game_object->GetParent() != nullptr)
    {
        Matrix4 parent_matrix = m_game_object->GetParent()->GetTransform()->GetLocalMatrix();
        return (parent_matrix * GetMatrix());
    }

    return GetMatrix();
}

Matrix4 Transform::GetNormalMatrix() const
{
    return GetMatrix().GetInverted().GetTransposed();
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