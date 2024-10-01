#pragma once

#define MAX_LAYER_TYPES 0xffffffff

// enum class LAYER_TYPE ������ | �� ������ ���
using LAYER_TYPES = UINT;

// ���̾� Ÿ�� (value : ������ ����)
// TODO : 2�� ����� �ø� ��
enum LAYER_TYPE : UINT
{
	CAMERA = 0,

	// LAYER_TYPES(int) �� ���� ������ ���̾��
	DEFAULT = 1,
	GROUND = DEFAULT << 1,
	MONSTER = GROUND << 1,
	PLAYER = MONSTER << 1,
	SKILL = PLAYER << 1,
	DEBUG = 0x80000000 // MAX
};