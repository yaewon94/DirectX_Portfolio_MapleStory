#pragma once

// enum class LAYER_TYPE ������ | �� ������ ���
using LAYER_TYPES = UINT;

// ���̾� Ÿ��
// TODO : 2�� ����� �ø� ��(+���鸸), MAX(0x40000000)
enum class LAYER_TYPE
{
	CAMERA = -2,
	NONE = -1,

	// LAYER_TYPES �� ���� ������ ���̾��
	PLAYER = 0,
};