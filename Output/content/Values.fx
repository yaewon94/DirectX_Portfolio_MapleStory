#ifndef _VALUES
#define _VALUES

// ��� ����
cbuffer Transform : register(b0) // �������� ��ȣ
{
    //float4 objPos;
    //float4 objScale;
    // * row major : �� �켱 ���
    row_major matrix g_worldMatrix; // ������ǥ
    row_major matrix g_viewMatrix;  // view ����
    row_major matrix g_projMatrix;  // ���� ����
    
    row_major matrix g_wv;  // world * view
    row_major matrix g_wvp; // world * view * proj
};

// �ؽ�ó
Texture2D g_tex : register(t0);

// Sampler State
SamplerState g_sampler0 : register(s0); // �̹漺 ���͸�
SamplerState g_sampler1 : register(s1); // MIN_MAG_POINT ���͸�

#endif