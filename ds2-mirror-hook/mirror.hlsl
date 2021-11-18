Texture2D shaderTexture: register(t0);
SamplerState sampleType: register(s0);

struct vs_in
{
    float3 pos : POS;
    float2 tex : TEX;
};

struct vs_out
{
    float4 pos : SV_POSITION;
    float2 tex : TEX;
};

vs_out vs_main(vs_in input)
{
    vs_out output;
    output.pos = float4(input.pos, 1);
    output.tex.y = input.tex.y;
    output.tex.x = 1 - input.tex.x;
    return output;
}

float4 ps_main(vs_out input) : SV_TARGET
{
    return shaderTexture.Sample(sampleType, input.tex);
}