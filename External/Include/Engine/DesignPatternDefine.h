#pragma once

// ����Ʈ ���� ������, �̵� ���� ������, ���� ������, �̵� ���� ������ ����
#define NO_COPY_ASSIGN(type) type(const type&) = delete;\
							 type(type&&) = delete;\
							 type& operator=(const type&) = delete;\
							 type& operator=(type&&) = delete;