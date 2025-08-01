// Parameter Structs
struct VertexShaderOutput
{
	float4 color : COLOR;
	float4 position : SV_POSITION;
};

// Pixel Shader
float4 Color_Main(VertexShaderOutput input) : SV_TARGET
{
	return input.color;
}
