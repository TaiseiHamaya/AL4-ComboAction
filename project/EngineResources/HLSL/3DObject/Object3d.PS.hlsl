#include "Object3d.hlsli"

struct Material {
	float3 color;
	int lightingType;
	float shininess;
	float4x4 uvTransform;
};

struct PixelShaderOutput {
	float4 color : SV_Target0;
};

struct DirectionalLight {
	float3 color; // 色
	float intensity; // 輝度
	float3 directon; // 向き
};

struct CameraInfoPS {
	float3 position;
};

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);
ConstantBuffer<CameraInfoPS> gCameraInfoPS : register(b2);
Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

PixelShaderOutput main(VertexShaderOutput input) {
	PixelShaderOutput output;
	float4 transformedUV = mul(float4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
	float4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
	
	float3 toCamera = normalize(gCameraInfoPS.position - input.world);
	//float3 reflectLight = reflect(gDirectionalLight.directon, normalize(input.normal));
	//float dotReflect = dot(reflectLight, toCamera);
	//float specularPow = pow(saturate(dotReflect), gMaterial.shininess);
	//specularPow = isnan(specularPow) ? 0 : specularPow * 2.0f;
	float3 halfVector = normalize(-gDirectionalLight.directon + toCamera);
	float dotNormal = dot(normalize(input.normal), halfVector);
	float specularPow = pow(saturate(dotNormal), gMaterial.shininess);
	if (isnan(specularPow)) {
		specularPow = 0;
	}
	else {
		specularPow *= 2.0f;
	}
	float3 specular = gDirectionalLight.color * gDirectionalLight.intensity * specularPow * gMaterial.color * textureColor.rgb;

		// ライティングなし
	if (gMaterial.lightingType == 0) {
		output.color = float4(gMaterial.color, 1.0f) * textureColor;
	}
	// Lambert
	else if (gMaterial.lightingType == 1) {
		float NdotL = dot(normalize(input.normal), -gDirectionalLight.directon);
		float cos = saturate(NdotL);
		float3 baseColor = gMaterial.color * textureColor.rgb * gDirectionalLight.color;
		output.color.rgb = baseColor * cos * gDirectionalLight.intensity;
		output.color.rgb += specular;
		output.color.a = textureColor.a;
	}
	// Half Lambert
	else if (gMaterial.lightingType == 2) {
		float NdotL = dot(normalize(input.normal), -gDirectionalLight.directon);
		float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
		float3 baseColor = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb;
		output.color.rgb = baseColor * cos * gDirectionalLight.intensity;
		output.color.rgb += specular;
		output.color.a = textureColor.a;
	}
	// それ以外は異常値なので、白を出力
	else {
		output.color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	// 透明の場合は出力せず終了
	// サンプリングによっては0にならない場合があるためバッファを取る
	if (output.color.a <= 0.05f) {
		discard;
	}
	return output;
}