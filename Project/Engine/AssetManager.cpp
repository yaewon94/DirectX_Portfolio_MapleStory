#include "pch.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "GraphicShader.h"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	for (auto& map : assetMapArr)
	{
		map.clear();
	}
}

int AssetManager::Init()
{
	// TODO : ���Ϸ� ��ȯ�ϱ�
	if (FAILED(CreateDefaultMesh())) return E_FAIL;
	if (FAILED(CreateDefaultShader())) return E_FAIL;

	return S_OK;
}

int AssetManager::CreateDefaultMesh()
{
	{
		// =============================
		// �簢��
		// =============================
		// ���� ��ġ ���� (viewport ��ǥ)
		// �� �ȼ� ������ �÷����� �����Ǽ� ����
		const int SQUARE_VERTEX_COUNT = 4;
		const int SQUARE_INDEX_COUNT = 6;
		int index = 0;

		Vertex vertexArr[SQUARE_VERTEX_COUNT] = {};
		vertexArr[index].pos = Vec3(-0.5f, 0.5f, 0.f);
		vertexArr[index].uv = Vec2(0.f, 0.f);
		vertexArr[index++].color = Vec4(1.f, 0.f, 0.f, 1.f);

		vertexArr[index].pos = Vec3(0.5f, 0.5f, 0.f);
		vertexArr[index].uv = Vec2(1.f, 0.f);
		vertexArr[index++].color = Vec4(0.f, 0.f, 1.f, 1.f);

		vertexArr[index].pos = Vec3(0.5f, -0.5f, 0.f);
		vertexArr[index].uv = Vec2(1.f, 1.f);
		vertexArr[index++].color = Vec4(0.f, 1.f, 0.f, 1.f);

		vertexArr[index].pos = Vec3(-0.5f, -0.5f, 0.f);
		vertexArr[index].uv = Vec2(0.f, 1.f);
		vertexArr[index++].color = Vec4(1.f, 0.f, 1.f, 1.f);

		// �ε��� �� ����
		UINT indexArr[SQUARE_INDEX_COUNT] = { 0, 1, 2, 0, 2, 3 };

		// �޽� ���� ����
		Ptr<Mesh> rectMesh = AddAsset<Mesh>(L"RectMesh", L"RectMesh");
		if (FAILED(rectMesh->CreateOnGpu(vertexArr, SQUARE_VERTEX_COUNT, indexArr, SQUARE_INDEX_COUNT)))
		{
			MessageBox(nullptr, L"�簢�� Mesh ���� ����", L"���� ���� ����", MB_OK);
			return E_FAIL;
		}
	}

	{
		// =============================
		// ��
		// =============================
		const int SLICE = 40;
		const float RADIUS = 0.5f;

		vector<Vertex> vertexVec;
		vector<UINT> indexVec;
		Vertex vertex;
		float theta = 0.f;	// ���� ���� �ﰢ���� �߽ɰ�

		// �߽���
		vertex.pos = Vec3(0.f, 0.f, 0.f);
		vertex.uv = Vec2(0.5f, 0.5f);
		vertexVec.push_back(vertex);

		// ������ ��ǥ �ʱ�ȭ
		for (int i = 0; i < SLICE + 1; ++i)
		{
			// cos(theta) : x ��ǥ / RADIUS
			// sin(theta) : y ��ǥ / RADIUS
			vertex.pos = Vec3(RADIUS * cosf(theta), RADIUS * sinf(theta), 0.f);
			vertex.uv = Vec2(vertex.pos.x + 0.5f, 1.f - (vertex.pos.y + 0.5f));
			vertexVec.push_back(vertex);

			theta += (XM_PI * 2.f) / SLICE;
		}

		// �ε���(���� �̷�� ������ ��ȣ) �ʱ�ȭ
		for (int i = 0; i < SLICE; ++i)
		{
			indexVec.push_back(0);
			indexVec.push_back(i + 1);
			indexVec.push_back(i + 2);
		}

		// �޽� ����
		Ptr<Mesh> circleMesh = AddAsset<Mesh>(L"CircleMesh", L"CircleMesh");
		if (FAILED(circleMesh->CreateOnGpu(vertexVec.data(), vertexVec.size(), indexVec.data(), indexVec.size())))
		{
			MessageBox(nullptr, L"�� Mesh ���� ����", L"���� ���� ����", MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}

int AssetManager::CreateDefaultShader()
{
	// ==========================
	// �⺻ 2D ���̴�
	// ==========================
	Ptr<GraphicShader> shader = AddAsset<GraphicShader>(L"Std2D_Shader", L"Std2D.fx");
	shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
	if (FAILED(shader->CreateOnGpu("VS_Std2D", "PS_Std2D")))
	{
		MessageBox(nullptr, L"�⺻ 2D ���̴� ���� ����", L"���� ���� ����", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}