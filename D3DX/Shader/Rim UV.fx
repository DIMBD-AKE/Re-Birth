//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// Rim UV
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Rim_UV_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Teapot.3ds";

float4x4 gWorldViewProjectionMatrix : WorldViewProjection;
float4x4 gWorldMatrix : World;
float4 gWorldLightDirection
<
   string UIName = "gWorldLightDirection";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 1.00, -1.00, 1.00, 1.00 );

struct VS_INPUT 
{
   float4 Position : POSITION0;
   float3 Normal : NORMAL;
   float3 Tangent : TANGENT;
   float3 Binormal : BINORMAL;
   float2 UV : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 UV : TEXCOORD0;
   float3 LightDir : TEXCOORD1;
   float3 T : TEXCOORD2;
   float3 B :TEXCOORD3;
   float3 N : TEXCOORD4;
   float3 WorldPosition : TEXCOORD5;
};

VS_OUTPUT Rim_UV_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position = mul( Input.Position, gWorldViewProjectionMatrix );
   Output.WorldPosition = mul( Input.Position, gWorldMatrix );
   Output.UV = Input.UV;
   
   Output.N = normalize(mul(Input.Normal, (float3x3)gWorldMatrix));
   Output.T = normalize(mul(Input.Tangent, (float3x3)gWorldMatrix));
   Output.B = normalize(mul(Input.Binormal, (float3x3)gWorldMatrix));
   
   Output.LightDir = normalize(gWorldLightDirection);
   
   return( Output );
   
}




texture DiffuseMap_Tex
<
   string ResourceName = "..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Fieldstone.tga";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};
texture NormalMap_Tex
<
   string ResourceName = "..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\FieldstoneBumpDOT3.tga";
>;
sampler2D NormalSampler = sampler_state
{
   Texture = (NormalMap_Tex);
};

float4 gCamPos : ViewPosition;
float3 gLightColor
<
   string UIName = "gLightColor";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float3( 1.00, 1.00, 1.00 );
float3 gRimColor
<
   string UIName = "gRimColor";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float3( 1.00, 0.00, 0.00 );
float gOffset
<
   string UIName = "gOffset";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 0.00 );
float gAlpha
<
   string UIName = "gAlpha";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 0.20 );
float gRimPower
<
   string UIName = "gRimPower";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 1.00 );

struct PS_INPUT
{
   float2 UV : TEXCOORD0;
   float3 LightDir : TEXCOORD1;
   float3 T : TEXCOORD2;
   float3 B :TEXCOORD3;
   float3 N : TEXCOORD4;
   float3 WorldPosition : TEXCOORD5;
};

float4 Rim_UV_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{   
   // NormalMap
   float3 tangentNormal = tex2D(NormalSampler, Input.UV).xyz;
   tangentNormal = normalize(tangentNormal * 2 - 1);
   
   float3x3 TBN = float3x3(normalize(Input.T), normalize(Input.B), normalize(Input.N));
   TBN = transpose(TBN);
   float3 worldNormal = mul(TBN, tangentNormal);
   
   float4 albedo = tex2D(DiffuseSampler, Input.UV);
   float3 lightDir = normalize(Input.LightDir);
   float3 diffuse = saturate(dot(worldNormal, -lightDir));
   diffuse = gLightColor * albedo * diffuse;
   float3 ambient = float3(0.3f, 0.3f, 0.3f) * albedo;
   float3 offset = float3(gOffset, gOffset, gOffset);
   
   float3 viewDir = normalize(gCamPos - Input.WorldPosition);
   float3 rim = smoothstep(0.5f, 1.0f, 1 - dot(worldNormal, viewDir)) * gRimPower * gRimColor;

   return( float4( ambient + diffuse + offset + rim, gAlpha ) );
   
}
//--------------------------------------------------------------//
// Pass 1
//--------------------------------------------------------------//
string Rim_UV_Pass_1_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Teapot.3ds";

float4x4 Rim_UV_Pass_1_Vertex_Shader_gWorldMatrix : World;
float4x4 Rim_UV_Pass_1_Vertex_Shader_gWorldViewProjectionMatrix : WorldViewProjection;

struct Rim_UV_Pass_1_Vertex_Shader_VS_INPUT 
{
   float4 Position : POSITION0;
   float3 Normal : NORMAL;
};

struct Rim_UV_Pass_1_Vertex_Shader_VS_OUTPUT 
{
   float4 Position : POSITION0;
   float3 Normal : TEXCOORD0;
   float3 WorldPosition : TEXCOORD1;
};

Rim_UV_Pass_1_Vertex_Shader_VS_OUTPUT Rim_UV_Pass_1_Vertex_Shader_vs_main( Rim_UV_Pass_1_Vertex_Shader_VS_INPUT Input )
{
   Rim_UV_Pass_1_Vertex_Shader_VS_OUTPUT Output;

   Output.Position = mul (Input.Position, Rim_UV_Pass_1_Vertex_Shader_gWorldViewProjectionMatrix);
   Output.Normal = mul (Input.Normal, Rim_UV_Pass_1_Vertex_Shader_gWorldMatrix);
   Output.WorldPosition = mul( Input.Position, Rim_UV_Pass_1_Vertex_Shader_gWorldMatrix );
   
   return( Output );
   
}




float4 Rim_UV_Pass_1_Pixel_Shader_gCamPos : ViewPosition;
float Rim_UV_Pass_1_Pixel_Shader_gRimPower
<
   string UIName = "Rim_UV_Pass_1_Pixel_Shader_gRimPower";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 1.00 );
float3 Rim_UV_Pass_1_Pixel_Shader_gRimColor
<
   string UIName = "Rim_UV_Pass_1_Pixel_Shader_gRimColor";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float3( 1.00, 0.00, 0.00 );

struct Rim_UV_Pass_1_Pixel_Shader_PS_INPUT
{
   float3 Normal : TEXCOORD0;
   float3 WorldPosition : TEXCOORD1;
};

float4 Rim_UV_Pass_1_Pixel_Shader_ps_main(Rim_UV_Pass_1_Pixel_Shader_PS_INPUT Input) : COLOR0
{   
   float3 viewDir = normalize(Rim_UV_Pass_1_Pixel_Shader_gCamPos - Input.WorldPosition);
   float3 N = normalize(Input.Normal);
   float smooth = smoothstep(0.5f, 1.0f, 1 - dot(N, viewDir));
   float3 rim = smooth * Rim_UV_Pass_1_Pixel_Shader_gRimPower * Rim_UV_Pass_1_Pixel_Shader_gRimColor;

   float alpha = 1.0f;
   if (smooth < 0.5f || smooth > 1.0f)
      alpha = 0.0f;

   return( float4( rim, alpha ) );
}




//--------------------------------------------------------------//
// Technique Section for Rim UV
//--------------------------------------------------------------//
technique Rim_UV
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 Rim_UV_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Rim_UV_Pass_0_Pixel_Shader_ps_main();
   }

   pass Pass_1
   {
      VertexShader = compile vs_2_0 Rim_UV_Pass_1_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Rim_UV_Pass_1_Pixel_Shader_ps_main();
   }

}

