#pragma once

// �ð� ���� ó�� Ŭ����
class TimeManager final : public Singleton<TimeManager>
{
	SINGLETON(TimeManager)

private:
	LARGE_INTEGER frequency;	// �ʴ� ī���� ���� ��
	LARGE_INTEGER curCount;		// ���� ī��Ʈ ��
	LARGE_INTEGER prevCount;	// ���� ������ ī��Ʈ ��

	double deltaTime;	// ������ �� �ð�
	double totalTime;	// ���� �ð�

	UINT fps;	// �ʴ� ������ Ƚ��

public:
	double GetDeltaTime() { return deltaTime; }

public:
	void Init();
	void Tick();
};