#include "pch.h"
#include "Transform.h"
#include "GameObject.h"
#include "Device.h"
#include "ConstBuffer.h"

Transform::Transform(const Ptr<GameObject>& owner)
	: Component(owner)
	, localScale(Vec3(100.f, 100.f, 1.f))
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

	// ���⺤�� �ʱ�ȭ
	localDirVec[(UINT)DIRECTION_VEC::RIGHT] = Vec3(1.f, 0.f, 0.f);
	localDirVec[(UINT)DIRECTION_VEC::UP] = Vec3(0.f, 1.f, 0.f);
	localDirVec[(UINT)DIRECTION_VEC::FRONT] = Vec3(0.f, 0.f, 1.f);

	for (int i = 0; i < localDirVec.size(); ++i)
	{
		//XMVector3TransformCoord(localDirVec[i], matRotation);
		localDirVec[i] = XMVector3TransformNormal(localDirVec[i], matRotation);
	}

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

	//CB_Transform tr = {};
	//tr.worldMatrix = worldMatrix;
	//cb->SetData(&tr);

	g_transform.worldMatrix = worldMatrix;
	cb->SetData(&g_transform);
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
	// ȸ����� �缳��
	matRotation = XMMatrixRotationX(localRotation.x)
		* XMMatrixRotationY(localRotation.y)
		* XMMatrixRotationZ(localRotation.z);

	// ���⺤�� �缳��
	for (int i = 0; i < localDirVec.size(); ++i)
	{
		//XMVector3TransformCoord(localDirVec[i], matRotation);
		localDirVec[i] = XMVector3TransformNormal(localDirVec[i], matRotation);
	}

	OnChangeMatrix();
}

void Transform::OnChangeMatrix()
{
	worldMatrix = matScale * matRotation * matTrans;
	BindOnGpu();
}
