#pragma pack_matrix( row_major )

// Shader Resources
cbuffer CameraData : register(b0)
{
    matrix projectionMatrix;
    matrix viewMatrix;
}
cbuffer ModelData : register(b1)
{
	matrix worldMatrix;
}
cbuffer ColorData : register(b2)
{
	float4 color;
}

// Parameter Structs
struct VertexShaderInput 
{
	float3 position : POSITION;
};
struct VertexShaderOutput
{
	float4 color : COLOR;
	float4 position : SV_POSITION;
};

// Vertex Shader
VertexShaderOutput Color_Main(VertexShaderInput input)
{
	VertexShaderOutput output;

	// Matrix for tranforming the position into 3D space. World * View * Proj.
	matrix Mat = mul(mul(worldMatrix, viewMatrix), projectionMatrix);
	
	output.position = mul(float4(input.position, 1.0f), Mat);
	output.color = float4(color.xyz, 1.0f);

	return output;
}
