#include "transformComponent.h"

void TransformComponent::Create(const Vector2D& m_position, float m_rotation, const Vector2D m_scale )
{
	this->position = m_position;
	this->rotation = m_rotation;
	this->scale = m_scale;
}

void TransformComponent::Destroy()
{
	//
}

void TransformComponent::Update()
{
	Matrix33 mxs; mxs.Scale(scale);
	Matrix33 mxr; mxr.Rotate(rotation * Math::DegreesToRadians);
	Matrix33 mxt; mxt.Translate(position);

	matrix = mxs * mxr * mxt;
}
