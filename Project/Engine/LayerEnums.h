#pragma once

#define MAX_LAYER_TYPES 0x7fffffff

// enum class LAYER_TYPE ������ | �� ������ ���
using LAYER_TYPES = int;

// ���̾� Ÿ�� (value : ������ ����)
// TODO : 2�� ����� �ø� ��
enum LAYER_TYPE : int
{
	NONE = -100,
	LIGHT = -1,
	CAMERA = 0,

	// LAYER_TYPES(int) �� ���� ������ ���̾��
	DEFAULT = 1,
	GROUND = DEFAULT << 1,
	MONSTER = GROUND << 1,
	PLAYER = MONSTER << 1,
	SKILL = PLAYER << 1,
	DEBUG = SKILL << 1,
	// 0x40000000 // MAX
};