#include "pch.h"
#include "Transform.h"
#include "GameObject.h"
#include "Device.h"
#include "ConstBuffer.h"

// ����ȭ�� ���⺤�� �����
static const array<const Vec3, (UINT)DIRECTION_VEC::COUNT_END> NormDirVec
	= { Vec3(1.f, 0.f, 0.f), 
		Vec3(0.f, 1.f, 0.f), 
		Vec3(0.f, 0.f, 1.f) };

Transform::Transform(const Ptr<GameObject>& owner)
	: Component(owner)
	, m_localScale(Vec3(100.f, 100.f, 1.f))
{
}

Transform::Transform(const Ptr<Component>& origin, const Ptr<GameObject>& owner)
	: Component(origin, owner)
{
	auto tr = origin.ptr_dynamic_cast<Transform>();
	m_localPos = tr->m_localPos;
	m_localScale = tr->m_localScale;
	m_localRotation = tr->m_localRotation;
}

Transform::~Transform()
{
}

Vec3 Transform::GetWorldScale()
{
	Vec3 scale = m_localScale;
	Ptr<GameObject> parent = GetOwner()->GetParent();

	if (parent != nullptr)
	{
		scale *= parent->GetTransform()->GetWorldScale();
	}

	return scale;
}

void Transform::Init()
{
	m_worldMatrix = XMMatrixIdentity();
	OnChangePos();
	OnChangeScale();
	OnChangeRotation();
	OnChangeMatrix();
}

void Transform::FinalTick()
{
	OnChangeMatrix();
}

void Transform::BindOnGpu()
{
	Ptr<ConstBuffer> cb = Device::GetInstance()->GetConstBuffer(CB_TYPE::TRANSFORM);
	
	g_transform.worldMatrix = m_worldMatrix;
	g_transform.wv = g_transform.worldMatrix * g_transform.viewMatrix;
	g_transform.wvp = g_transform.wv * g_transform.projMatrix;

	cb->SetData(&g_transform);
	cb->BindOnGpu();
}

void Transform::OnChangePos()
{

	m_matTrans = XMMatrixTranslation(m_localPos.x, m_localPos.y, m_localPos.z);

}

void Transform::OnChangeScale()
{
	m_matScale = XMMatrixScaling(m_localScale.x, m_localScale.y, m_localScale.z);
}

void Transform::OnChangeRotation()
{
	m_matRot = XMMatrixRotationX(m_localRotation.x) * XMMatrixRotationY(m_localRotation.y) * XMMatrixRotationZ(m_localRotation.z);
	
	// ���� ���⺤�� ����
	for (UINT i = 0; i < m_localDirVec.size(); ++i)
	{
		m_worldDirVec[i] = m_localDirVec[i] = XMVector3TransformNormal(NormDirVec[i], m_matRot);
	}
}

void Transform::OnChangeMatrix()
{
	m_worldMatrix = m_matScale * m_matRot * m_matTrans;	// ��� �����̹Ƿ� ���� �߿�

	// �θ� ������Ʈ�� �ִ� ���
	Ptr<GameObject> parent = GetOwner()->GetParent();
	if (parent != nullptr)
	{
		const auto& matParentWorld = parent->GetTransform()->GetWorldMatrix();

		//// localScale�� ��� ���� ���� ������ ũ���� ���ε��ϴ� ���
		//Vec3 parentScale = parent->GetTransform()->GetWorldScale();
		//Matrix matParentScale = XMMatrixScaling(parentScale.x, parentScale.y, parentScale.z);
		//Matrix matParentScaleInv = XMMatrixInverse(nullptr, matParentScale);
		//m_worldMatrix *= (matParentScaleInv * matParentWorld);

		// �θ� Scale�� ����� ���ũ��� ���ε�
		m_worldMatrix *= matParentWorld;

		// ���� ���⺤�� ����
		for (UINT i = 0; i < m_worldDirVec.size(); ++i)
		{
			m_worldDirVec[i] = XMVector3TransformNormal(NormDirVec[i], m_worldMatrix);
			m_worldDirVec[i].Normalize();
		}
	}
}