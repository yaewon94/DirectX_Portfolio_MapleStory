#pragma once
#include "Render.h"

#define VERTEX_SHADER_VER "vs_5_0"
#define PIXEL_SHADER_VER "ps_5_0"

#define CONTEXT Device::GetInstance()->GetContext()
#define DEVICE Device::GetInstance()->GetDevice()

class ConstBuffer;

// GPU ���� Ŭ����
class Device final : public Singleton<Device>
{
	SINGLETON(Device);

private:
	HWND m_hwnd;

	ComPtr<ID3D11Device> m_device;			// GPU ����, GPU �޸𸮿� ������ ����
	ComPtr<ID3D11DeviceContext> m_context;	// GPU ���� ���, ������, GPGPU

	ComPtr<IDXGISwapChain> m_swapChain;		// ����� ����, ���� ������ ����

	Ptr<ConstBuffer> m_cbArr[(UINT)CB_TYPE::COUNT_END];	// Ÿ�Ժ� �������

	ComPtr<ID3D11RasterizerState> m_rsState[(UINT)RASTERIZE_TYPE::COUNT_END];
	ComPtr<ID3D11SamplerState> m_spState[(UINT)SAMPLER_TYPE::COUNT_END];
	ComPtr<ID3D11BlendState> m_bsState[(UINT)BLEND_TYPE::COUNT_END];
	ComPtr<ID3D11DepthStencilState> m_dsState[(UINT)DEPTH_STENCIL_TYPE::COUNT_END];

public:
	ComPtr<ID3D11Device> GetDevice() { return m_device; }
	ComPtr<ID3D11DeviceContext> GetContext() { return m_context; }
	Ptr<ConstBuffer> GetConstBuffer(CB_TYPE type);
	ComPtr<ID3D11RasterizerState> GetRasterizerState(RASTERIZE_TYPE type) { return m_rsState[(UINT)type]; }
	ComPtr<ID3D11BlendState> GetBlendState(BLEND_TYPE type) { return m_bsState[(UINT)type]; }
	ComPtr<ID3D11DepthStencilState> GetDepthStencilState(DEPTH_STENCIL_TYPE type) { return m_dsState[(UINT)type]; }

public:
	int Init(HWND hwnd);
	
public:
	// RenderTargetView => ������ ���
	void Present();

private:
	int CreateSwapChain();
	int CreateView();
	int CreateConstBuffer();
	int CreateRasterizerState();
	int CreateBlendState();
	int CreateDepthStencilState();
	int CreateSamplerState();
};