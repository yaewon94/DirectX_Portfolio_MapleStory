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
	DEFAULT = 0b1,
	MONSTER = 0b10,
	PLAYER = 0b100,
	SKILL = 0b1000,
	DEBUG = 0x80000000 // MAX
};