#ifndef _TILEMAP
#define _TILEMAP

#include "Values.fx"
#include "Functions.fx"

#define AtlasTex g_tex_0
#define TileCount g_vec2_0

struct TileInfo
{
    float2 tileLeftTopUV;
    float2 tileSliceUV;
};

StructuredBuffer<TileInfo> g_buffer : register(t16);

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float3 worldPos : POSITION;
    float2 uv : TEXCOORD;
};

VS_OUT VS_TileMap(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.pos = mul(float4(input.pos, 1.f), g_wvp);
    output.worldPos = mul(float4(input.pos, 1.f), g_worldMatrix);
    output.uv = input.uv * TileCount;
    
    return output;
}

float4 PS_TileMap(VS_OUT input) : SV_Target
{
    float4 color = (float4) 0.f;
    
    // Ÿ�� ������
    if (g_bTex_0)
    {
        int2 colRow = floor(input.uv);
        int index = colRow.y * TileCount.x + colRow.y;
        
        float2 atlasUV = g_buffer[index].tileLeftTopUV + (frac(input.uv) * g_buffer[index].tileSliceUV);
        color = AtlasTex.Sample(g_sampler1, atlasUV);
    }
    else
    {
        color = GetDebugColor(input.uv, 10);
    }
    
    // ========================================
    // ���� ó��
    // ========================================
    float3 lightColor = float3(0.f, 0.f, 0.f);
    float DistanceRatio = 1.f;
    
    // ���籤��
    if (g_light2dInfo[0].type == DIRECTION_LIGHT)
    {
        lightColor += g_light2dInfo[0].color;
    }
    // �� ����
    else if (g_light2dInfo[0].type == POINT_LIGHT)
    {
        float Distance = distance(input.worldPos, g_light2dInfo[0].worldPos);
        if (Distance <= g_light2dInfo[0].radius)
        {
            lightColor += g_light2dInfo[0].color;
            DistanceRatio = saturate(1.f - (Distance / g_light2dInfo[0].radius));
        }

    }
    // ���� : ����Ʈ����Ʈ ����
    else if (g_light2dInfo[0].type == SPOT_LIGHT)
    {
        // ���� üũ (LEFT, RIGHT, UP, DOWN)
        float3 vecMinus = input.worldPos - g_light2dInfo[0].worldPos;

        // ������Ʈ �ȼ��� ���� ���⿡ �ִ��� Ȯ��
        // (��ȣ�� ���� �� ���ڳ��� ���ϸ� ����� �Ǵ� ���� �̿�)
        // 2���� ���� ������ x�� �Ǵ� y�� ��������
        if (g_light2dInfo[0].dir.x * vecMinus.x > 0 
            || g_light2dInfo[0].dir.y * vecMinus.y > 0)
        // 3���� ���� ������ x,y,z,xy,xz,yz�� �߿� �Ǻ��ؾ� ��
        //if ((g_light2dInfo[0].dir.x == 0.f || (g_light2dInfo[0].dir.x != 0.f && g_light2dInfo[0].dir.x * vecMinus.x > 0))
        //    && (g_light2dInfo[0].dir.y == 0.f || (g_light2dInfo[0].dir.y != 0.f && g_light2dInfo[0].dir.y * vecMinus.y > 0))
        //    && (g_light2dInfo[0].dir.z == 0.f || (g_light2dInfo[0].dir.z != 0.f && g_light2dInfo[0].dir.z * vecMinus.z > 0)))
        {
            // ����(O)����
            // ���� ����������� �������� ���� ������ ������Ʈ �ȼ��� �����ϴ� ���� ������ ����(V)
            // ������ �Ÿ�
            // (g_light2dInfo[0].dir �� Light2DŬ�������� �������ͷ� �Էµ�)
            float OVdis = distance(input.worldPos * g_light2dInfo[0].dir
                                    , g_light2dInfo[0].worldPos * g_light2dInfo[0].dir);
            
            // ���� ���ߴ� ����, �������� V��ǥ������ �Ÿ��� �������
            // ������Ʈ�� �����Ǵ� Light�� ������ ���ϱ�
            // cos(g_light2dInfo[0].angle) == OVdis / sqrt(OVdis^2 + Radius^2)
            // sin(g_light2dInfo[0].angle) == Radius / sqrt(OVdis^2 + Radius^2)
            // => Radius == OVdis / cos(g_light2dInfo[0].angle) * sqrt(1-cos(g_light2dInfo[0].angle)^2)
            // => sin(angle)^2 + cos(angle)^2 = 1 �̹Ƿ�
            float Radius = OVdis * sin(g_light2dInfo[0].angle) / cos(g_light2dInfo[0].angle);
            
            // ������Ʈ �ȼ�(P)�� Light ���� �ȿ� �ִ��� üũ
            float3 unitVec = (1.f, 1.f, 1.f);
            if (g_light2dInfo[0].dir.x != 0.f)
                unitVec.x = 0.f;
            if (g_light2dInfo[0].dir.y != 0.f)
                unitVec.y = 0.f;
            
            float VPdis = distance(input.worldPos * unitVec, g_light2dInfo[0].worldPos * unitVec);
            if (VPdis < Radius)
            {
                lightColor += g_light2dInfo[0].color;
                DistanceRatio = saturate(1.f - (VPdis / Radius));
            }
            else
            {
                discard;
            }
        }
        else
        {
            discard;
        }
    }
    
    color.rgb *= lightColor * DistanceRatio;
    return color;
}
#endif