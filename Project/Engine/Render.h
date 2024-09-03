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

// �����Ͷ����� Ÿ��
// ���� �׷��� ���� => ������ �̹���(bit) ��ȯ
enum class RASTERIZE_TYPE : UINT
{
	// culling : ������Ʈ���� �ʿ���� �κ��� ������ ���� �ʰ� �ϴ� ��� 
	CULL_BACK,	// �޸� �ø� (DEFAULT)
	CULL_FRONT,	// �ո� �ø�
	CULL_NONE,
	WIRE_FRAME,	// ���̾� ������
	COUNT_END
};

// ==============================
// �ܺκ���
// ==============================
extern CB_Transform g_transform;