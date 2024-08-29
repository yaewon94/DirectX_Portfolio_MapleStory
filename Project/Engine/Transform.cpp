#include "pch.h"
#include "Transform.h"
#include "GameObject.h"
#include "Device.h"
#include "ConstBuffer.h"

Transform::Transform(const Ptr<GameObject>& owner)
	: Component(owner), localScale(Vec3(1.f, 1.f, 1.f))
{
}

Transform::Transform(const Ptr<Component>& origin, const Ptr<GameObject>& owner)
	: Component(origin, owner)
{
	auto tr = origin.ptr_dynamic_cast<Transform>();
	localPos = tr->localPos;
	localScale = tr->localScale;
	localRotation = tr->localRotation;
}

Transform::~Transform()
{
}

void Transform::SetPosX(float x)
{
	localPos.x = x;
	//worldMatrix._41 = localPos.x;
	OnChangePos();
}

void Transform::SetPosY(float y)
{
	localPos.y = y;
	//worldMatrix._42 = localPos.y;
	OnChangePos();
}

void Transform::SetPosZ(float z)
{
	localPos.z = z;
	//worldMatrix._43 = localPos.z;
	OnChangePos();
}

void Transform::SetScaleX(float x)
{
	localScale.x = x;
	//worldMatrix._11 = localScale.x;
	OnChangeScale();
}

void Transform::SetScaleY(float y)
{
	localScale.y = y;
	//worldMatrix._22 = localScale.y;
	OnChangeScale();
}

void Transform::SetScaleZ(float z)
{
	localScale.z = z;
	//worldMatrix._33 = localScale.z;
	OnChangeScale();
}

void Transform::SetRotationX(float x)
{
	localRotation.x = x;
	OnChangeRotation();
}

void Transform::SetRotationY(float y)
{
	localRotation.y = y;
	OnChangeRotation();
}

void Transform::SetRotationZ(float z)
{
	localRotation.z = z;
	OnChangeRotation();
}

void Transform::Init()
{
	// ��İ� �ʱ�ȭ
	worldMatrix = XMMatrixIdentity();

	matTrans = XMMatrixTranslation(localPos.x, localPos.y, localPos.z);
	matScale = XMMatrixScaling(localScale.x, localScale.y, localScale.z);
	matRotation = XMMatrixRotationX(localRotation.x)
		* XMMatrixRotationY(localRotation.y)
		* XMMatrixRotationZ(localRotation.z);

	worldMatrix = matScale * matRotation * matTrans;	// ��� �����̹Ƿ� ���� �߿�

	// Bind
	BindOnGpu();
}

void Transform::FinalTick()
{
	/*worldMatrix = XMMatrixIdentity();

	worldMatrix._41 = localPos.x;
	worldMatrix._42 = localPos.y;
	worldMatrix._43 = localPos.z;

	worldMatrix._11 = localScale.x;
	worldMatrix._22 = localScale.y;
	worldMatrix._33 = localScale.z;*/
}

void Transform::BindOnGpu()
{
	Ptr<ConstBuffer> cb = Device::GetInstance()->GetConstBuffer(CB_TYPE::TRANSFORM);

	CB_Transform tr = {};
	tr.worldMatrix = worldMatrix;

	cb->SetData(&tr);
	cb->BindOnGpu();
}

void Transform::OnChangePos()
{
	matTrans = XMMatrixTranslation(localPos.x, localPos.y, localPos.z);
	OnChangeMatrix();
}

void Transform::OnChangeScale()
{
	matScale = XMMatrixScaling(localScale.x, localScale.y, localScale.z);
	OnChangeMatrix();
}

void Transform::OnChangeRotation()
{
	matRotation = XMMatrixRotationX(localRotation.x)
		* XMMatrixRotationY(localRotation.y)
		* XMMatrixRotationZ(localRotation.z);
	OnChangeMatrix();
}

void Transform::OnChangeMatrix()
{
	worldMatrix = matScale * matRotation * matTrans;
	BindOnGpu();
}
