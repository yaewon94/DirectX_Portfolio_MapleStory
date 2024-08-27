#include "pch.h"
#include "RenderTest.h"
#include "Device.h"
#include "AssetManager.h"
#include "MeshRender.h"
#include "Mesh.h"
#include "GraphicShader.h"
#include "Player.h"

#define SQUARE_VERTEX_COUNT 4
#define SQUARE_INDEX_COUNT 6

int InitTest()
{
	// ���ӿ�����Ʈ ����
	g_player = Ptr<GameObject>();
	g_player->AddComponent<MeshRender>();
	g_player->AddComponent<Player>();

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
	Ptr<Mesh> mesh = AssetManager::GetInstance()->FindAsset<Mesh>(L"MeshTest", L"MeshTest");
	if (FAILED(mesh->CreateOnGpu(vertexArr, SQUARE_VERTEX_COUNT, indexArr, SQUARE_INDEX_COUNT)))
	{
		return E_FAIL;
	}
	g_player->GetComponent<MeshRender>()->SetMesh(mesh);

	// ���̴� ���� ����
	Ptr<GraphicShader> shader = AssetManager::GetInstance()->FindAsset<GraphicShader>(L"ShaderTest", L"Shader.fx");
	if (FAILED(shader->CreateOnGpu("VS_Test", "PS_Test")))
	{
		return E_FAIL;
	}
	g_player->GetComponent<MeshRender>()->SetShader(shader);
	g_player->Init();

	return S_OK;
}

void TickTest()
{
	g_player->Tick();
	g_player->FinalTick();
}

void RenderTest()
{
	// ���� ������ RenderTarget, DepthStencil Ŭ����
	Device::GetInstance()->Clear();

	// ���ӿ�����Ʈ ������
	g_player->Render();

	// �����쿡 RenderTarget�� �׷��� �� ���
	Device::GetInstance()->Present();
}