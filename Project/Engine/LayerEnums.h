#pragma once

#define MAX_LAYER_TYPES 0xffffffff

// enum class LAYER_TYPE ������ | �� ������ ���
using LAYER_TYPES = UINT;

// ���̾� Ÿ��
// TODO : 2�� ����� �ø� ��(+���鸸), MAX(0x40000000)
enum LAYER_TYPE
{
	NONE = -1,
	CAMERA = 0,

	// LAYER_TYPES(UINT) �� ���� ������ ���̾��
	PLAYER = 1,
};