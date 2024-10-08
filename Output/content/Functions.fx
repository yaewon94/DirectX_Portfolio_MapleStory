#ifndef _FUNCTIONS
#define _FUNCTIONS
#include "Values.fx"

float4 GetDebugColor(float2 _uv, int _level)
{
    float2 texPos = _uv * _level;
    int col = floor(texPos.x);
    int row = floor(texPos.y);
    
    if ((col + row) % 2) 
        return float4(1.f, 0.f, 1.f, 1.f);
    else
        return float4(0.f, 0.f, 0.f, 1.f);

}

// ����ó��
void CalcLight2D(int lightIdx, float2 objPos, inout float3 lightColor)
{
    float DistanceRatio = 1.f;
    
    // ���籤��
    if (g_light2dInfo[lightIdx].type == DIRECTION_LIGHT)
    {
        lightColor += g_light2dInfo[lightIdx].color;
    }
    // �� ����
    else if (g_light2dInfo[lightIdx].type == POINT_LIGHT)
    {
        float Distance = distance(objPos, g_light2dInfo[lightIdx].worldPos);
        
        if (Distance <= g_light2dInfo[lightIdx].radius)
        {
            DistanceRatio = saturate(1.f - (Distance / g_light2dInfo[lightIdx].radius));
            lightColor += (g_light2dInfo[lightIdx].color * DistanceRatio);
        }
    }
    // ����Ʈ����Ʈ
    else if (g_light2dInfo[lightIdx].type == SPOT_LIGHT)
    {
        // ���� üũ (LEFT, RIGHT, UP, DOWN)
        //float3 vecMinus = worldPos - g_light2dInfo[lightIdx].worldPos;
        float2 vecMinus = objPos - g_light2dInfo[lightIdx].worldPos;

        // ������Ʈ �ȼ��� ���� ���⿡ �ִ��� Ȯ��
        // (��ȣ�� ���� �� ���ڳ��� ���ϸ� ����� �Ǵ� ���� �̿�)
        // 2���� ���� ������ x�� �Ǵ� y�� ��������
        if (g_light2dInfo[lightIdx].dir.x * vecMinus.x > 0
            || g_light2dInfo[lightIdx].dir.y * vecMinus.y > 0)
        // 3���� ���� ������ x,y,z,xy,xz,yz�� �߿� �Ǻ��ؾ� ��
        //if ((g_light2dInfo[0].dir.x == 0.f || (g_light2dInfo[0].dir.x != 0.f && g_light2dInfo[0].dir.x * vecMinus.x > 0))
        //    && (g_light2dInfo[0].dir.y == 0.f || (g_light2dInfo[0].dir.y != 0.f && g_light2dInfo[0].dir.y * vecMinus.y > 0))
        //    && (g_light2dInfo[0].dir.z == 0.f || (g_light2dInfo[0].dir.z != 0.f && g_light2dInfo[0].dir.z * vecMinus.z > 0)))
        {
            // ����(O)����
            // ���� ����������� �������� ���� ������ ������Ʈ �ȼ��� �����ϴ� ���� ������ ����(V)
            // ������ �Ÿ�
            // (g_light2dInfo[0].dir �� Light2DŬ�������� �������ͷ� �Էµ�)
            //float OVdis = distance(worldPos * g_light2dInfo[lightIdx].dir
            //                        , g_light2dInfo[lightIdx].worldPos * g_light2dInfo[lightIdx].dir);
            float OVdis = distance(objPos * g_light2dInfo[lightIdx].dir
                                    , g_light2dInfo[lightIdx].worldPos * g_light2dInfo[lightIdx].dir);
            
            
            // ���� ���ߴ� ����, �������� V��ǥ������ �Ÿ��� �������
            // ������Ʈ�� �����Ǵ� Light�� ������ ���ϱ�
            // cos(g_light2dInfo[0].angle) == OVdis / sqrt(OVdis^2 + Radius^2)
            // sin(g_light2dInfo[0].angle) == Radius / sqrt(OVdis^2 + Radius^2)
            // => Radius == OVdis / cos(g_light2dInfo[0].angle) * sqrt(1-cos(g_light2dInfo[0].angle)^2)
            // => sin(angle)^2 + cos(angle)^2 = 1 �̹Ƿ�
            float Radius = OVdis * sin(g_light2dInfo[lightIdx].angle) / cos(g_light2dInfo[lightIdx].angle);
            
            // ������Ʈ �ȼ�(P)�� Light ���� �ȿ� �ִ��� üũ
            //float3 unitVec = (1.f, 1.f, 1.f);
            float2 unitVec = (1.f, 1.f);
            if (g_light2dInfo[lightIdx].dir.x != 0.f)
                unitVec.x = 0.f;
            if (g_light2dInfo[lightIdx].dir.y != 0.f)
                unitVec.y = 0.f;
            
            //float VPdis = distance(worldPos * unitVec, g_light2dInfo[lightIdx].worldPos * unitVec);
            float VPdis = distance(objPos * unitVec, g_light2dInfo[lightIdx].worldPos * unitVec);

            if (VPdis < Radius)
            {
                DistanceRatio = saturate(1.f - (VPdis / Radius));
                lightColor += (g_light2dInfo[lightIdx].color * DistanceRatio);
            }
        }
    }
}
#endif