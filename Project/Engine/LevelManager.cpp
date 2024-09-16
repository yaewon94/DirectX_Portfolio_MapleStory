#include "pch.h"
#include "LevelManager.h"
#include "Level.h"
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"

LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::Init()
{
	curLevel = Ptr<Level>();

	// ===================== �ʼ� ������Ʈ �߰� =======================
	// ����ī�޶� �߰�
	Ptr<GameObject> camera = Ptr<GameObject>();
	camera->GetTransform()->SetLocalPos(Vec3(0.f, 0.f, -100.f));
	camera->AddComponent<Camera>();
	camera->SetLayer(LAYER_TYPE::CAMERA);

	// ���緹�� Init()
	curLevel->Init();
}

void LevelManager::Tick()
{
	curLevel->Tick();
	curLevel->FinalTick();
}

void LevelManager::Render(LAYER_TYPES layers)
{
	curLevel->Render(layers);
}

Ptr<GameObject> LevelManager::AddObject(const Ptr<GameObject>& obj)
{
	return curLevel->AddObject(obj);
}

void LevelManager::DeleteObject(const Ptr<GameObject>& obj)
{
	curLevel->DeleteObject(obj);
}

Ptr<GameObject> LevelManager::GetGameObject(LAYER_TYPE layer)
{
	return curLevel->GetGameObject(layer);
}