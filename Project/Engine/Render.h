#pragma once


// ����
#define COLOR_GREEN Vec4(0.f, 1.f, 0.f, 1.f);

// �ؽ�ó Ÿ�� (value : �������� ��ȣ)
enum TEXTURE_PARAM
{
	NULL_PARAM = -1,	// �������� �Ҵ� ���� ��
	TEX_0, TEX_1, TEX_2, TEX_3, TEX_4, TEX_5,
	TEXARR_0, TEXARR_1, TEXARR_2, TEXARR_3,
	CUBE_0, CUBE_1,
	COUNT_END
};

// Blend State
enum class BLEND_TYPE : UINT
{
	DEFAULT,				// �������
	ALPHABLEND,				// ���İ� ����
	ALPHABLEND_COVERAGE,	// ���ĺ��� + AlphaToCoverage
	ONE_ONE,				// 1:1 ����
	COUNT_END
};

// ��� ���� Ÿ��
enum class CB_TYPE : UINT
{
	TRANSFORM, MATERIAL, COUNT_END
};

// ���� �������
struct CB_Material
{
	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matrixArr[2];
	int bTex[TEXTURE_PARAM::COUNT_END];	// ���̳ʸ� �ؽ�ó
};

// ������Ʈ�� ��ġ,ũ��,ȸ���� �������
struct CB_Transform
{
	//Vec4 pos;
	//Vec4 scale;
	Matrix worldMatrix;
	Matrix viewMatrix;
	Matrix projMatrix;

	Matrix wv;	// world * view
	Matrix wvp;	// world * view * projection
};

// ����� ��� shape
enum class DEBUG_SHAPE
{
	RECT, CIRCLE, CROSS, LINE
};

// �����Ͷ����� Ÿ��
enum class RASTERIZE_TYPE : UINT
{
	// culling : ������Ʈ���� �ʿ���� �κ��� ������ ���� �ʰ� �ϴ� ��� 
	CULL_BACK,	// �޸� �ø� (DEFAULT)
	CULL_FRONT,	// �ո� �ø�
	CULL_NONE,
	WIRE_FRAME,	// ���̾� ������
	COUNT_END
};

// ���ø� Ÿ��
enum class SAMPLER_TYPE : UINT
{
	AF,							// �̹漺 ���͸�
	MIN_MAG_POINT_MIP_LINEAR,	// Minification, Magnification Mipmap ���� ���͸�
	COUNT_END
};

// �Ķ���� Ÿ��
enum SCALAR_PARAM
{
	INT_0, INT_1, INT_2, INT_3,
	FLOAT_0, FLOAT_1, FLOAT_2, FLOAT_3,
	VEC2_0, VEC2_1, VEC2_2, VEC2_3,
	VEC4_0, VEC4_1, VEC4_2, VEC4_3,
	MATRIX_0, MATRIX_1
};

// ���̴� ���� �з�
enum class SHADER_DOMAIN
{
	DOMAIN_OPAQUE,			// ������
	DOMAIN_MASK,			// ������ or ����
	DOMAIN_TRANSPARENT,		// ������ + ����
	DOMAIN_POSTPROCESS		// ��ó��
};

// ==============================
// �ܺκ���
// ==============================
extern CB_Transform g_transform;