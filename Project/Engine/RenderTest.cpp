#include "pch.h"
#include "RenderTest.h"
#include "Device.h"
#include "PathManager.h"
#include "TimeManager.h"

#define SQUARE_VERTEX_COUNT 6
#define SQUARE_INDEX_COUNT 4
#define LAYOUT_FIELD_COUNT 3

// ����
Vertex g_vertexArr[SQUARE_INDEX_COUNT] = {};
ComPtr<ID3D11Buffer> g_vertexBuff;
ComPtr<ID3D11Buffer> g_indexBuff;	// �ε��� ����

// ���̴�
ComPtr<ID3DBlob> g_vertexShaderBlob;
ComPtr<ID3DBlob> g_pixelShaderBlob;
ComPtr<ID3DBlob> g_errorBlob;

ComPtr<ID3D11VertexShader> g_vertexShader;
ComPtr<ID3D11PixelShader> g_pixelShader;

// Input Layout
ComPtr<ID3D11InputLayout> g_layout;

int InitTest()
{
	// ���� ��ġ ���� (viewport ��ǥ)
	// �� �ȼ� ������ �÷����� �����Ǽ� ����
	int index = 0;

	g_vertexArr[index].pos = Vec3(-0.5f, 0.5f, 0.f);
	g_vertexArr[index++].color = Vec4(1.f, 0.f, 0.f, 1.f);

	g_vertexArr[index].pos = Vec3(0.5f, 0.5f, 0.f);
	g_vertexArr[index++].color = Vec4(0.f, 0.f, 1.f, 1.f);

	g_vertexArr[index].pos = Vec3(0.5f, -0.5f, 0.f);
	g_vertexArr[index++].color = Vec4(0.f, 1.f, 0.f, 1.f);

	g_vertexArr[index].pos = Vec3(-0.5f, -0.5f, 0.f);
	g_vertexArr[index++].color = Vec4(1.f, 0.f, 1.f, 1.f);

	// ���� ������ �ý��� �޸� => GPU�� ����
	D3D11_BUFFER_DESC vbDesc = {};

	vbDesc.ByteWidth = sizeof(Vertex) * SQUARE_INDEX_COUNT;
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	vbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// ���� ����
	vbDesc.Usage = D3D11_USAGE_DYNAMIC;

	// ������ų ������ �ʱⵥ����
	D3D11_SUBRESOURCE_DATA sub = {};
	sub.pSysMem = g_vertexArr;

	// ���� ���� ��ü ����
	if (FAILED(Device::GetInstance()->GetDevice()->CreateBuffer(&vbDesc, &sub, g_vertexBuff.GetAddressOf())))
	{
		return E_FAIL;
	}

	// �ε��� ���� ����
	UINT indexArr[SQUARE_VERTEX_COUNT] = { 0, 1, 2, 0, 2, 3 };
	D3D11_BUFFER_DESC ibDesc = {};

	ibDesc.ByteWidth = sizeof(UINT) * SQUARE_VERTEX_COUNT;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;	// ���� �Ұ�
	ibDesc.Usage = D3D11_USAGE_DEFAULT;

	sub.pSysMem = indexArr;

	if (FAILED(Device::GetInstance()->GetDevice()->CreateBuffer(&ibDesc, &sub, g_indexBuff.GetAddressOf())))
	{
		return E_FAIL;
	}

	// ���� ���̴� ���� ������
	wstring contentPath = PathManager::GetInstance()->GetContentPath();
	UINT flag = D3DCOMPILE_DEBUG;
	HRESULT result = S_OK;

	result = D3DCompileFromFile(wstring(contentPath + L"Shader\\Shader.fx").c_str()
		, nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "VS_Test"
		, SHADER_MODEL_VER
		, flag
		, 0
		, g_vertexShaderBlob.GetAddressOf()
		, g_errorBlob.GetAddressOf());

	if (FAILED(result))
	{
		errno_t errNum = GetLastError();

		if (errNum == 2 || errNum == 3)
		{
			MessageBoxA(nullptr, "���̴� ������ �������� ����", "���� ���̴� ������ ����", MB_OK);
		}
		else
		{
			char* errMsg = (char*)g_errorBlob->GetBufferPointer();
			MessageBoxA(nullptr, errMsg, "���� ���̴� ������ ����", MB_OK);
		}
		
		return E_FAIL;
	}

	// ���� ���̴� ����
	Device::GetInstance()->GetDevice()->CreateVertexShader(g_vertexShaderBlob->GetBufferPointer()
		, g_vertexShaderBlob->GetBufferSize()
		, nullptr
		, g_vertexShader.GetAddressOf());

	// �ȼ� ���̴� ���� ������
	result = D3DCompileFromFile(wstring(contentPath + L"Shader\\Shader.fx").c_str()
		, nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "PS_Test"
		, SHADER_MODEL_VER
		, flag
		, 0
		, g_pixelShaderBlob.GetAddressOf()
		, g_errorBlob.GetAddressOf());

	if (FAILED(result))
	{
		errno_t errNum = GetLastError();

		if (errNum == 2 || errNum == 3)
		{
			MessageBoxA(nullptr, "���̴� ������ �������� �ʽ��ϴ�.", "�ȼ� ���̴� ������ ����", MB_OK);
		}

		else
		{
			char* pErrMsg = (char*)g_errorBlob->GetBufferPointer();
			MessageBoxA(nullptr, pErrMsg, "�ȼ� ���̴� ������ ����", MB_OK);
		}

		return E_FAIL;
	}

	// �ȼ� ���̴� ����
	Device::GetInstance()->GetDevice()->CreatePixelShader(g_pixelShaderBlob->GetBufferPointer()
		, g_pixelShaderBlob->GetBufferSize()
		, nullptr
		, g_pixelShader.GetAddressOf());

	// Input Layout ����
	D3D11_INPUT_ELEMENT_DESC layoutDesc[LAYOUT_FIELD_COUNT] = {};
	layoutDesc[0].AlignedByteOffset = 0;
	layoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	layoutDesc[0].InputSlot = 0;
	layoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[0].InstanceDataStepRate = 0;
	layoutDesc[0].SemanticName = "POSITION";
	layoutDesc[0].SemanticIndex = 0;

	layoutDesc[1].AlignedByteOffset = 12;
	layoutDesc[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	layoutDesc[1].InputSlot = 0;
	layoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[1].InstanceDataStepRate = 0;
	layoutDesc[1].SemanticName = "TEXCOORD";
	layoutDesc[1].SemanticIndex = 0;

	layoutDesc[2].AlignedByteOffset = 20;
	layoutDesc[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	layoutDesc[2].InputSlot = 0;
	layoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[2].InstanceDataStepRate = 0;
	layoutDesc[2].SemanticName = "COLOR";
	layoutDesc[2].SemanticIndex = 0;

	if (FAILED(Device::GetInstance()->GetDevice()->CreateInputLayout(layoutDesc
		, LAYOUT_FIELD_COUNT
		, g_vertexShaderBlob->GetBufferPointer()
		, g_vertexShaderBlob->GetBufferSize()
		, g_layout.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void TickTest()
{
}

void RenderTest()
{
	// ���� ������ RenderTarget, DepthStencil Ŭ����
	Device::GetInstance()->Clear();

	// Input Assembler Stage : ������ ���� ����
	UINT Stride = sizeof(Vertex);
	UINT Offset = 0;
	Device::GetInstance()->GetContext()->IASetVertexBuffers(0, 1, g_vertexBuff.GetAddressOf(), &Stride, &Offset);
	Device::GetInstance()->GetContext()->IASetIndexBuffer(g_indexBuff.Get(), DXGI_FORMAT_R32_UINT, 0);
	Device::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Device::GetInstance()->GetContext()->IASetInputLayout(g_layout.Get());

	// Vertex Shader Stage
	Device::GetInstance()->GetContext()->VSSetShader(g_vertexShader.Get(), nullptr, 0);

	// Rasterizer Stage

	// Pixel Shader Stage
	Device::GetInstance()->GetContext()->PSSetShader(g_pixelShader.Get(), nullptr, 0);

	// Output Merge Stage
	// Depth Stencil Stage
	// Blend Stage

	// ������
	Device::GetInstance()->GetContext()->DrawIndexed(SQUARE_VERTEX_COUNT, 0, 0);

	// �����쿡 RenderTarget�� �׷��� �� ���
	Device::GetInstance()->Present();
}

void ReleaseTest()
{
}

void MoveTest(KEY_CODE key)
{
	float DT = TimeManager::GetInstance()->GetDeltaTime();
	float dir = 0.f;

	if (key == KEY_CODE::LEFT) dir = -1.f;
	else if (key == KEY_CODE::RIGHT) dir = 1.f;

	for (int i=0; i<SQUARE_INDEX_COUNT; ++i)
	{
		g_vertexArr[i].pos.x += dir * DT;
	}

	D3D11_MAPPED_SUBRESOURCE sub = {};
	Device::GetInstance()->GetContext()->Map(g_vertexBuff.Get()
		, 0
		, D3D11_MAP_WRITE_DISCARD
		, 0
		, &sub);
	memcpy(sub.pData, g_vertexArr, sizeof(Vertex) * SQUARE_INDEX_COUNT);
	Device::GetInstance()->GetContext()->Unmap(g_vertexBuff.Get(), 0);

}