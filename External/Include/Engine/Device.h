#pragma once
#include "ConstBuffer.h"

#define VERTEX_SHADER_VER "vs_5_0"
#define PIXEL_SHADER_VER "ps_5_0"

#define CONTEXT Device::GetInstance()->GetContext()
#define DEVICE Device::GetInstance()->GetDevice()

// GPU ���� Ŭ����
class Device final : public Singleton<Device>
{
	SINGLETON(Device);

private:
	HWND hwnd;

	ComPtr<ID3D11Device> device;			// GPU ����, GPU �޸𸮿� ������ ����
	ComPtr<ID3D11DeviceContext> context;	// GPU ���� ���, ������, GPGPU

	ComPtr<IDXGISwapChain> swapChain;		// ����� ����, ���� ������ ����
	
	ComPtr<ID3D11Texture2D> rtTex;			// �����
	ComPtr<ID3D11RenderTargetView> rtView;	// ����� �߰� ������
	
	ComPtr<ID3D11Texture2D> dsTex;			// Depth, Stencil, Texture
	ComPtr<ID3D11DepthStencilView> dsView;

	D3D11_VIEWPORT viewPort;

	Ptr<ConstBuffer> cbArr[(UINT)CB_TYPE::COUNT_END];	// Ÿ�Ժ� �������

	/*ID3D11RasterizerState* rsState;
	ID3D11DepthStencilState* dsState;
	ID3D11BlendState* bsState;
	ID3D11SamplerState* samplerState;*/

public:
	ComPtr<ID3D11Device> GetDevice() { return device; }
	ComPtr<ID3D11DeviceContext> GetContext() { return context; }
	Ptr<ConstBuffer> GetConstBuffer(CB_TYPE type) { return cbArr[(UINT)type]; }

public:
	int Init(HWND hwnd);
	
public:
	void Clear();
	void Present();

private:
	int CreateSwapChain();
	int CreateView();
	int CreateConstBuffer();
};