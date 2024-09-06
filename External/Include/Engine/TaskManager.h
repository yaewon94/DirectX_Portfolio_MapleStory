#pragma once
#include "Singleton.h"

// �۾��� ��Ƽ� ���� �����ӿ� ó���� �� �ְ� ��
class TaskManager : public Singleton<TaskManager>
{
	SINGLETON(TaskManager);

private:
	vector<TaskInfo> taskVec;

public:
	void AddTesk(const TaskInfo& task) { taskVec.push_back(task); }

public:
	void Tick();
};