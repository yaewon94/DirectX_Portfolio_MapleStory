#pragma once

// �ð� ���� ó�� Ŭ����
class TimeManager final : public Singleton<TimeManager>
{
	SINGLETON(TimeManager)

private:
	LARGE_INTEGER m_frequency;	// �ʴ� ī���� ���� ��
	LARGE_INTEGER m_curCount;	// ���� ī��Ʈ ��
	LARGE_INTEGER m_prevCount;	// ���� ������ ī��Ʈ ��

	float m_deltaTime;	// ������ �� �ð�
	float m_totalTime;	// ���� �ð�

	UINT m_fps;	// �ʴ� ������ Ƚ��

public:
	float GetDeltaTime() { return m_deltaTime; }

public:
	void Init();
	void Tick();
};