// ���� ��Ŭ�� > HLSL �����Ϸ� > ���̴� ���� /fx ����

#ifndef _SHADER // ���ϸ�
#define _SHADER

// ��� ����
cbuffer Transform : register(b0) // �������� ��ȣ
{
    //float4 objPos;
    //float4 objScale;
    row_major matrix g_worldMatrix;   // �� �켱 ���
    row_major matrix g_viewMatrix;
    row_major matrix g_projMatrix;
};

// Vertex Shader
struct VS_IN
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
};

VS_OUT VS_Test(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // ======================== ��ǥ ============================
    // �����ǥ => ������ǥ
    //float3 pos = (input.pos * objScale.xyz) + objPos.xyz;
    //output.pos = float4(pos, 1.f);
    float4 worldPos = mul(float4(input.pos, 1.f), g_worldMatrix);
    // ������ǥ => view ����
    float4 viewPos = mul(worldPos, g_viewMatrix);
    // view ���� => ��������
    output.pos = mul(viewPos, g_projMatrix);
    
    // ======================== ���� ============================
    output.color = input.color;
    
    return output;
}

// Pixel Shader
float4 PS_Test(VS_OUT input) : SV_Target
{
    return input.color;
}

#endif
