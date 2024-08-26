#pragma once
#include "Component.h"

class Mesh;
class GraphicShader;

// �޽�, �׷��ȼ��̴� ������ ��� ������Ʈ
class MeshRender final : public Component
{
	NO_COPY_ASSIGN(MeshRender);

private:
	Ptr<Mesh> mesh;
	Ptr<GraphicShader> shader;

public:
	MeshRender(const Ptr<GameObject>& owner);
	MeshRender(const MeshRender& origin, const Ptr<GameObject>& owner);
	~MeshRender();

public:
	void SetMesh(const Ptr<Mesh>& mesh);
	void SetShader(const Ptr<GraphicShader>& shader);

public:
	virtual void FinalTick() final {}
	void Render();
};