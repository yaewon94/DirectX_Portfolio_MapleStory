#include "pch.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "GraphicShader.h"
#include "Material.h"

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
	if (FAILED(CreateDefaultMaterial())) return E_FAIL;

	return S_OK;
}

int AssetManager::CreateDefaultMesh()
{
	Ptr<Mesh> mesh;

	// =============================
	// �簢��
	// =============================
	{
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
		mesh = AddAsset<Mesh>(L"RectMesh", L"RectMesh");
		if (FAILED(mesh->CreateOnGpu(vertexArr, SQUARE_VERTEX_COUNT, indexArr, SQUARE_INDEX_COUNT)))
		{
			MessageBox(nullptr, L"�簢�� Mesh ���� ����", L"���� ���� ����", MB_OK);
			return E_FAIL;
		}

		// =============================
		// ����� ��� �簢��
		// =============================
		{
			const int DBG_RECT_IDX_COUNT = 5;
			UINT DbgRectIdx[DBG_RECT_IDX_COUNT] = { 0, 1, 2, 3, 0 };
			mesh = AddAsset<Mesh>(L"RectMesh_D", L"RectMesh_D");
			if (FAILED(mesh->CreateOnGpu(vertexArr, SQUARE_VERTEX_COUNT, DbgRectIdx, DBG_RECT_IDX_COUNT)))
			{
				MessageBox(nullptr, L"������ �簢�� Mesh ���� ����", L"���� ���� ����", MB_OK);
				return E_FAIL;
			}
		}
	}

	// =============================
	// ��
	// =============================
	{
		const int SLICE = 40;
		const float RADIUS = 0.5f;

		vector<Vertex> vertexVec(SLICE + 2);
		vector<UINT> indexVec(SLICE * 3);
		Vertex vertex;
		float theta = 0.f;	// ���� ���� �ﰢ���� �߽ɰ�

		// �߽���
		vertex.pos = Vec3(0.f, 0.f, 0.f);
		vertex.uv = Vec2(0.5f, 0.5f);
		vertexVec[0] = vertex;

		// ������ ��ǥ �ʱ�ȭ
		for (int i = 1; i < SLICE + 2; ++i)
		{
			// cos(theta) : x ��ǥ / RADIUS
			// sin(theta) : y ��ǥ / RADIUS
			vertex.pos = Vec3(RADIUS * cosf(theta), RADIUS * sinf(theta), 0.f);
			vertex.uv = Vec2(vertex.pos.x + 0.5f, 1.f - (vertex.pos.y + 0.5f));
			vertexVec[i] = vertex;

			theta += (XM_PI * 2.f) / SLICE;
		}

		// �ε���(���� �̷�� ������ ��ȣ) �ʱ�ȭ
		int index = -1;
		for (int i = 0; i < SLICE; ++i)
		{
			indexVec[++index] = 0;
			indexVec[++index] = i + 1;
			indexVec[++index] = i + 2;
		}

		// �޽� ����
		mesh = AddAsset<Mesh>(L"CircleMesh", L"CircleMesh");
		if (FAILED(mesh->CreateOnGpu(vertexVec.data(), vertexVec.size(), indexVec.data(), indexVec.size())))
		{
			MessageBox(nullptr, L"�� Mesh ���� ����", L"���� ���� ����", MB_OK);
			return E_FAIL;
		}

		// =============================
		// ����� ��� ��
		// =============================
		{
			indexVec.resize(vertexVec.size() - 1);
			for (int i = 0; i < indexVec.size(); ++i)
			{
				indexVec[i] = i + 1;
			}

			mesh = AddAsset<Mesh>(L"CircleMesh_D", L"CircleMesh_D");
			if (FAILED(mesh->CreateOnGpu(vertexVec.data(), vertexVec.size(), indexVec.data(), indexVec.size())))
			{
				MessageBox(nullptr, L"������ �� Mesh ���� ����", L"���� ���� ����", MB_OK);
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

int AssetManager::CreateDefaultShader()
{
	Ptr<GraphicShader> shader;

	// ==========================
	// �⺻ 2D ���̴�
	// ==========================
	{
		shader = AddAsset<GraphicShader>(L"Std2D_Shader", L"Std2D.fx");
		shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
		shader->SetBlendType(BLEND_TYPE::DEFAULT);
		shader->SetDomain(SHADER_DOMAIN::DOMAIN_MASK);
		if (FAILED(shader->CreateOnGpu("VS_Std2D", "PS_Std2D")))
		{
			MessageBox(nullptr, L"�⺻ 2D ���̴� ���� ����", L"���� ���� ����", MB_OK);
			return E_FAIL;
		}
	}

	// ==========================
	// �⺻ ���ĺ��� 2D ���̴�
	// ==========================
	{
		shader = AddAsset<GraphicShader>(L"Std2D_AlphaBlend_Shader", L"Std2D.fx");
		shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
		shader->SetBlendType(BLEND_TYPE::ALPHABLEND);
		shader->SetDepthStencilType(DEPTH_STENCIL_TYPE::NO_TEST);
		shader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);
		if (FAILED(shader->CreateOnGpu("VS_Std2D", "PS_Std2D_AlphaBlend")))
		{
			MessageBox(nullptr, L"�⺻ ���ĺ��� 2D ���̴� ���� ����", L"���� ���� ����", MB_OK);
			return E_FAIL;
		}
	}

	// ==========================
	// PaperBurn ���̴�
	// ==========================
	{
		shader = AddAsset<GraphicShader>(L"PaperBurn_Shader", L"Std2D.fx");
		shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
		shader->SetBlendType(BLEND_TYPE::DEFAULT);
		shader->SetDomain(SHADER_DOMAIN::DOMAIN_MASK);
		if (FAILED(shader->CreateOnGpu("VS_Std2D", "PS_PaperBurn")))
		{
			MessageBox(nullptr, L"PaperBurn ���̴� ���� ����", L"���� ���� ����", MB_OK);
			return E_FAIL;
		}
	}

	// ============================
	// ����� ��� ���̴�
	// ============================
	{
		shader = AddAsset<GraphicShader>(L"Debug_Shader", L"Debug.fx");
		shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
		shader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		if (FAILED(shader->CreateOnGpu("VS_Debug", "PS_Debug")))
		{
			MessageBox(nullptr, L"����� ��� ���̴� ���� ����", L"���� ���� ����", MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}

int AssetManager::CreateDefaultMaterial()
{
	Ptr<Material> material;

	// ==========================
	// �⺻ 2D ����
	// ==========================
	material = AddAsset<Material>(L"Std2D_Material", L"Std2D_Material");
	material->SetShader(FindAsset<GraphicShader>(L"Std2D_Shader"));

	// ==========================
	// �⺻ ���ĺ��� 2D ����
	// ==========================
	material = AddAsset<Material>(L"Std2D_AlphaBlend_Material", L"Std2D_AlphaBlend_Material");
	material->SetShader(FindAsset<GraphicShader>(L"Std2D_AlphaBlend_Shader"));

	// ==========================
	// PaperBurn ����
	// ==========================
	material = AddAsset<Material>(L"PaperBurn_Material", L"PaperBurn_Material");
	material->SetShader(FindAsset<GraphicShader>(L"PaperBurn_Shader"));

	// ==========================
	// ����� ��� ����
	// ==========================
	material = AddAsset<Material>(L"Debug_Material", L"Debug Material");
	material->SetShader(FindAsset<GraphicShader>(L"Debug_Shader"));

	return S_OK;
}
