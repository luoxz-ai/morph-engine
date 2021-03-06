

struct PSInput {
  float4 position : SV_POSITION;
  float4 color : COLOR;
  float2 uv: UV;
};

struct PSOutput {
	float4 color: SV_TARGET0;
};

cbuffer cCamera : register(b1) {
  float4x4 projection;
  float4x4 view;
	float4x4 prev_projection;
  float4x4 prev_view;
};

PSInput vmain(
	float3 position: POSITION,
	float4 color:    COLOR,
	float2 uv:       UV) {

	PSInput input;

	input.position = mul(projection, mul(view, float4(position, 1.f)));
	input.color = color;
	input.uv = uv;

	return input;
}

PSOutput pmain(PSInput input) {
	PSOutput output;

	output.color = input.color; 

	return output;
}