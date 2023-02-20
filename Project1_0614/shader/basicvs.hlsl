#include	"psvscommon.hlsl"

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main( float4 Pos : POSITION,
			    float4 Color : COLOR,
				float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	// �X�N���[�����W�v�Z�p
	float4 ScreenPos;

	// ���W�ϊ�
	Pos.w = 1.0f;
	ScreenPos = mul(Pos, World);			// ���W�ϊ�

	// �X�N���[�����W�ɕϊ�
	output.Pos = ScreenPos;
	output.Pos.x = (ScreenPos.x / ViewportWidth.x) * 2 - 1.0f;
	output.Pos.y = 1.0f - (ScreenPos.y / ViewportHeight.x) * 2;

	output.Pos.z = Pos.z;				
	output.Pos.w = 1.0f;

	// �J���[�l�Z�b�g
	output.Color = Color;
	// �e�N�X�`�����W�Z�b�g
	output.Tex = Tex;
	return output;
}
