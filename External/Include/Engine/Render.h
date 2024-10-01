#pragma once

// ����
#define COLOR_RED Vec4(1.f, 0.f, 0.f, 1.f)
#define COLOR_GREEN Vec4(0.f, 1.f, 0.f, 1.f)

// �������
#define BUFFER_SIZE_UNIT 16 // �������,����ȭ���� �ּ� ���� (����Ʈ)

// ======================
// Texture
// ======================
// �ؽ�ó Ÿ�� (value : �������� ��ȣ)
enum TEXTURE_PARAM
{
	NULL_PARAM = -1,	// �������� �Ҵ� ���� ��
	TEX_0, TEX_1, TEX_2, TEX_3, TEX_4, TEX_5,
	TEXARR_0, TEXARR_1, TEXARR_2, TEXARR_3,
	CUBE_0, CUBE_1,
	//SPRITE_TEX,
	COUNT_END,
	SPRITE_TEX = 12	// ���� : �� COUNT_END == 13�̸� ���ܶ�?
};


// =======================
// Const Buffer
// =======================
// ��� ���� Ÿ�� (value : �������� ��ȣ)
enum class CB_TYPE : UINT
{
	TRANSFORM, MATERIAL, SPRITE, COUNT_END
};

// ���� ������� (�� �ʵ带 ������ �������Ϳ� ���ε�)
struct CB_Material
{
	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matrixArr[2];
	int bTex[TEXTURE_PARAM::COUNT_END];
};

// ��������Ʈ �̹��� �������
struct CB_Sprite
{
	Vec2 leftTopUV;
	Vec2 sliceUV;
	Vec2 backgroundUV;
	Vec2 offsetUV;
	int isUsed;
	int padding[3];
};

// �Ķ���� Ÿ�� (Material ���� ���)
enum SCALAR_PARAM
{
	INT_0, INT_1, INT_2, INT_3,
	FLOAT_0, FLOAT_1, FLOAT_2, FLOAT_3,
	VEC2_0, VEC2_1, VEC2_2, VEC2_3,
	VEC4_0, VEC4_1, VEC4_2, VEC4_3,
	MATRIX_0, MATRIX_1
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

// ======================
// Shader
// ======================
// ���̴� ���� �з� (value : ������ ����)
enum class SHADER_DOMAIN : UINT
{
	DOMAIN_OPAQUE,			// ������
	DOMAIN_MASK,			// ������ or ����
	DOMAIN_TRANSPARENT,		// ������ + ����
	DOMAIN_POSTPROCESS,		// ��ó��
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

// �������� Ÿ��
enum class DEPTH_STENCIL_TYPE : UINT
{
	LESS,
	LESS_EQUAL,
	GREATER,		// �����ִ� ����
	NO_TEST,		// �������� X
	NO_WRITE,		// �������� LESS, ��� X
	NO_TEST_WRITE,	// �������� X, ��� X
	COUNT_END
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

#ifdef _DEBUG
// ======================
// Debug
// ======================
// ����� ��� shape
enum class DEBUG_SHAPE
{
	RECT, CIRCLE, CROSS, LINE
};

// ����� ��� ����
struct DebugShapeInfo
{
	DEBUG_SHAPE shape;
	Vec3 pos, scale, rotation;
	Vec4 color;

	//const float Duration;
	//float curTime = 0.f;

	bool hasDepthTest = false;	// �������� ���� ����
};
#endif	// _DEBUG

// ==============================
// �ܺκ���
// ==============================
extern CB_Transform g_transform;