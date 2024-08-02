#include "pch.h"
#include "RenderTest.h"
#include "Device.h"
#include "TimeManager.h"
#include "Mesh.h"
#include "GraphicShader.h"

#define SQUARE_VERTEX_COUNT 4
#define SQUARE_INDEX_COUNT 6
#define LAYOUT_FIELD_COUNT 3

// ������Ʈ ��ġ
Vec3 g_objPos = Vec3(0.f, 0.f, 0.f);

ComPtr<ID3D11Buffer> g_constBuff;	// ��� ����

Mesh* g_mesh = nullptr;
GraphicShader* g_shader = nullptr;

int InitTest()
{
	// ���� ��ġ ���� (viewport ��ǥ)
	// �� �ȼ� ������ �÷����� �����Ǽ� ����
	int index = 0;

	Vertex vertexArr[SQUARE_VERTEX_COUNT] = {};
	vertexArr[index].pos = Vec3(-0.5f, 0.5f, 0.f);
	vertexArr[index++].color = Vec4(1.f, 0.f, 0.f, 1.f);

	vertexArr[index].pos = Vec3(0.5f, 0.5f, 0.f);
	vertexArr[index++].color = Vec4(0.f, 0.f, 1.f, 1.f);

	vertexArr[index].pos = Vec3(0.5f, -0.5f, 0.f);
	vertexArr[index++].color = Vec4(0.f, 1.f, 0.f, 1.f);

	vertexArr[index].pos = Vec3(-0.5f, -0.5f, 0.f);
	vertexArr[index++].color = Vec4(1.f, 0.f, 1.f, 1.f);

	// �ε��� �� ����
	UINT indexArr[SQUARE_INDEX_COUNT] = { 0, 1, 2, 0, 2, 3 };
	
	// �޽� ���� ����
	g_mesh = new Mesh(L"MeshTest", L"");
	if (FAILED(g_mesh->Create(vertexArr, SQUARE_VERTEX_COUNT, indexArr, SQUARE_INDEX_COUNT)))
	{
		return E_FAIL;
	}

	// ��� ���� ����
	D3D11_BUFFER_DESC cbDesc = {};

	cbDesc.ByteWidth = sizeof(CB_Transform);
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// ���� ����
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(DEVICE->CreateBuffer(&cbDesc, nullptr, g_constBuff.GetAddressOf())))
	{
		return E_FAIL;
	}

	// ���̴� ���� ����
	g_shader = new GraphicShader(L"ShaderTest", L"Shader.fx");
	if (FAILED(g_shader->Create("VS_Test", "PS_Test")))
	{
		return E_FAIL;
	}

	return S_OK;
}

void TickTest()
{
}

void RenderTest()
{
	// ���� ������ RenderTarget, DepthStencil Ŭ����
	Device::GetInstance()->Clear();

	// �� ����, ������
	Device::GetInstance()->GetContext()->VSSetConstantBuffers(0, 1, g_constBuff.GetAddressOf());
	g_shader->Bind();
	g_mesh->Render();

	// �����쿡 RenderTarget�� �׷��� �� ���
	Device::GetInstance()->Present();
}

void ReleaseTest()
{
	if (g_mesh != nullptr)
	{
		delete g_mesh;
		g_mesh = nullptr;
	}

	if (g_shader != nullptr)
	{
		delete g_shader;
		g_shader = nullptr;
	}
}

void MoveTest(KEY_CODE key)
{
	float DT = TimeManager::GetInstance()->GetDeltaTime();
	float dir = 0.f;

	// ���⿡ �°� ������Ʈ �̵�
	if (key == KEY_CODE::LEFT) dir = -1.f;
	else if (key == KEY_CODE::RIGHT) dir = 1.f;

	g_objPos.x += dir * DT;

	// ��� ���� �� ����
	CB_Transform tr;
	tr.pos = g_objPos;

	D3D11_MAPPED_SUBRESOURCE sub = {};
	Device::GetInstance()->GetContext()->Map(g_constBuff.Get()
		, 0
		, D3D11_MAP_WRITE_DISCARD
		, 0
		, &sub);
	memcpy(sub.pData, &tr, sizeof(CB_Transform));
	Device::GetInstance()->GetContext()->Unmap(g_constBuff.Get(), 0);
}