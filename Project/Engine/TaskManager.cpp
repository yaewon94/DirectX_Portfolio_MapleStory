#include "pch.h"
#include "TaskManager.h"
#include "LevelManager.h"
#include "GameObject.h"

TaskManager::TaskManager()
{
}

TaskManager::~TaskManager()
{
}

void TaskManager::Tick()
{
	for (auto& task : taskVec)
	{
		if (task.Type == TASK_TYPE::CREATE_OBJECT)
		{
			Ptr<GameObject> obj = Ptr<GameObject>(task.param0);
			obj->SetLayer((LAYER_TYPE)task.param1);
			obj->Init();
		}
		else if (task.Type == TASK_TYPE::DELETE_OBJECT)
		{
		}
		else if (task.Type == TASK_TYPE::CHANGE_LEVEL)
		{
		}
		else
		{
			throw std::logic_error("���ǵ��� ���� Task Ÿ���Դϴ�");
		}
	}
}