#pragma once
#include <string>

#ifdef  DLL_EXPORTS	// ������Ʈ�� �ش� �̸��� ��ó���Ⱑ ���ǵǾ� �ִٴ� ��
#define MYDLL  __declspec(dllexport)
#else
#define MYDLL __declspec(dllimport)
#endif

extern"C" MYDLL std::string GetLibraryNameDll();