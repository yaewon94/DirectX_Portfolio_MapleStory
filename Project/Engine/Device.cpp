#include "pch.h"
#include "Device.h"
#include "Engine.h"

Device::Device() 
	: hwnd(nullptr), viewPort{}
	/*, rsState(nullptr), dsState(nullptr), bsState(nullptr), samplerState(nullptr)*/
{
}

Device::~Device()
{
	//// delete �� ���� ���� ����, DirectX �� ���� (���� �ٸ� crt.dll �� ����ϰ� ���� �� �����Ƿ�)
	//if(rsState != nullptr) rsState->Release();
	//if(dsState != nullptr) dsState->Release();
	//if(bsState != nullptr) bsState->Release();
	//if(samplerState != nullptr) samplerState->Release();
}

int Device::Init(HWND hwnd)
{
	this->hwnd = hwnd;

	// ============================================================
	// Device, Context ����
	// ============================================================
	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
		, nullptr, iFlag
		, nullptr, 0, D3D11_SDK_VERSION
		, device.GetAddressOf()
		, &level
		, context.GetAddressOf())))
	{
		return E_FAIL;
	}

	// =========================================
	// SwapChain ����
	// =========================================
	if (FAILED(CreateSwapChain())) return E_FAIL;

	// =====================================
	// View ����
	// =====================================
	if (FAILED(CreateView())) return E_FAIL;

	// ====================================================
	// ViewPort ����
	// ����Ʈ ������ ������ ũ�⸦ �������� 0~1 ����ȭ�� ��
	// ====================================================
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = Engine::GetInstance()->GetResolution().x;
	viewPort.Height = Engine::GetInstance()->GetResolution().y;

	viewPort.MinDepth = 0.f;
	viewPort.MaxDepth = 1.f;

	context->RSSetViewports(1, &viewPort);

	// Rendering �������� ����
	context->OMSetRenderTargets(1, rtView.GetAddressOf(), dsView.Get());

	Vec4 vClearColor = Vec4(0.f, 0.f, 0.f, 1.f);
	context->ClearRenderTargetView(rtView.Get(), vClearColor);

	// ������ �� RenderTarget �� �׷��� �̹����� ��½�Ų��.
	swapChain->Present(0, 0);

	return S_OK;
}

int Device::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc = {};

	desc.BufferCount = 1;	// ����� ����
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// ����� �뵵 ����

	desc.BufferDesc.Width = (UINT)Engine::GetInstance()->GetResolution().x;	// �ػ�
	desc.BufferDesc.Height = (UINT)Engine::GetInstance()->GetResolution().y;

	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// �ȼ� ����

	desc.BufferDesc.RefreshRate.Denominator = 1;	// ȭ�� ���� ����
	desc.BufferDesc.RefreshRate.Numerator = 60;

	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	desc.OutputWindow = hwnd;	// ����ۿ� �׷��� �̹����� ��½�ų ������
	desc.Windowed = true;	// â���(true) or ��üȭ��(false) ���
	
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;	// ���� ������ ������ ����
	desc.Flags = 0;

	// ==============================
	// SwapChain ��ü ����
	// ==============================
	ComPtr<IDXGIDevice> giDevice;
	ComPtr<IDXGIAdapter> adapter;
	ComPtr<IDXGIFactory> factory;

	// GUID(Global Unique ID, 128 ��Ʈ) 
	device->QueryInterface(__uuidof(IDXGIDevice), (void**)giDevice.GetAddressOf());
	giDevice->GetAdapter(adapter.GetAddressOf());
	adapter->GetParent(__uuidof(IDXGIFactory), (void**)factory.GetAddressOf());
	if(FAILED(factory->CreateSwapChain(device.Get(), &desc, swapChain.GetAddressOf()))) return E_FAIL;

	return S_OK;
}

int Device::CreateView()
{
	// ==============================================
	// Render Target Texture
	// SwapChain�� ������ �� ������� �ؽ�ó�� ����Ŵ
	// ==============================================
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)rtTex.GetAddressOf());

	// Render Target View ����
	if (FAILED(device->CreateRenderTargetView(rtTex.Get(), nullptr, rtView.GetAddressOf())))
	{
		return E_FAIL;
	}

	// ==============================================
	// Depth Stencil Texture
	// ==============================================
	D3D11_TEXTURE2D_DESC desc = {};

	desc.Width = (UINT)Engine::GetInstance()->GetResolution().x;
	desc.Height = (UINT)Engine::GetInstance()->GetResolution().y;

	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	// ���� ���� CPU���� ������ �������� �ɼ�
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;

	// �Ӹ� ������ 1 ==> ������ ������ 
	desc.MipLevels = 1;

	desc.MiscFlags = 0;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	// Depth Stencil Texture ����
	if (FAILED(device->CreateTexture2D(&desc, nullptr, dsTex.GetAddressOf())))
	{
		return E_FAIL;
	}

	// Depth Stencil View ����
	if (FAILED(device->CreateDepthStencilView(dsTex.Get(), nullptr, dsView.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}
