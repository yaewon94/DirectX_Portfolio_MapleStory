#pragma once

// ��� ���� Ÿ��
enum class CB_TYPE : UINT
{
	TRANSFORM, COUNT_END
};

// ������Ʈ�� ��ġ,ũ��,ȸ���� �������
struct CB_Transform
{
	//Vec4 pos;
	//Vec4 scale;
	Matrix worldMatrix;
	Matrix viewMatrix;
	Matrix projMatrix;
};

// ==============================
// �ܺκ���
// ==============================
extern CB_Transform g_transform;