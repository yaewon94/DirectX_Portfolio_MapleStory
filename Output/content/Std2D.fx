// ���� ��Ŭ�� > HLSL �����Ϸ� > ���̴� ���� /fx ����

#ifndef _STD2D // ���ϸ�
#define _STD2D

#include "Values.fx"
#include "Functions.fx"

// Vertex Shader
struct VS_IN
{
    float3 pos : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

VS_OUT VS_Std2D(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // ======================== ��ǥ ============================
    // �����ǥ => ������ǥ
    //float3 pos = (input.pos * objScale.xyz) + objPos.xyz;
    //output.pos = float4(pos, 1.f);
    //float4 worldPos = mul(float4(input.pos, 1.f), g_worldMatrix);
    // ������ǥ => view ����
    //float4 viewPos = mul(worldPos, g_viewMatrix);
    // view ���� => ��������
    //output.pos = mul(viewPos, g_projMatrix);
    output.pos = mul(float4(input.pos, 1.f), g_wvp);
    
    // ======================== ���� ============================
    output.color = input.color;
    
    // ======================== UV ��ǥ =========================
    output.uv = input.uv;
    
    return output;
}

// Pixel Shader
float4 PS_Std2D(VS_OUT input) : SV_Target
{
    // texture�� ���ε� �Ǿ����� ������ ����� ���� ���
    // ��� 1. Shader �󿡼� �ذ�
    // ������ : ��� �ȼ��� �˻��ϱ� ������ ���� �ſ� ������
    int width = 0;
    int height = 0;
    g_tex_0.GetDimensions(width, height);
    
    if (!width || !height)
        return GetDebugColor(input.uv, 10);
    else
        return g_tex_0.Sample(g_sampler0, input.uv);
    
    ////// �ߵ����
    ////clip(-1);
    ////discard;
    //float4 color = g_tex_0.Sample(g_sampler0, input.uv);
    
    ////// ���� ǥ�� �뵵
    ////if (color.r == 1.f && color.g == 0.f && color.b == 1.f)
    ////    discard;
    
    //if (g_int_0 == 10) return float4(0.f, 0.f, 1.f, 1.f);
    //else return color;
}

#endif
