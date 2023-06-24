[[block]]
struct Data {
    world: mat4x4<f32>;
    view: mat4x4<f32>;
    proj: mat4x4<f32>;
};

struct Texel {
    [[builtin(position)]] vpos: vec4<f32>;
    [[location(0)]] pos: vec4<f32>;
    [[location(1)]] uv: vec3<f32>;
    [[location(2)]] normal: vec3<f32>;
    [[location(3)]] color: vec3<f32>;
};

[[block]]
struct Material {
    color: vec4<f32>;
    specular: vec4<f32>;
};

[[group(0), binding(0)]]
var<uniform> uniforms: Data;

[[group(1), binding(0)]]
var<uniform> material: Material;
[[group(1), binding(1)]]
var t_diffuse: texture_2d<f32>;
[[group(1), binding(2)]]
var s_diffuse: sampler;

[[stage(fragment)]]
fn main(tx: Texel) -> [[location(0)]] vec4<f32> {
    let color = vec3<f32>(1., 1., 1.);

    let color = textureSample(t_diffuse, s_diffuse, tx.pos.xy).xyz;
//    let light: vec3<f32> = vec3<f32>(0.5, 1.0, 2.0);
//    let color: vec3<f32> = normal.xyz * 0.5 + 0.5;0
//    let color: vec3<f32> = uv.xyz;
//    let color: vec3<f32> = vec3<f32>(1.0);
//    let brightness: f32 = dot(tx.normal, normalize(tx.vpos.xyz) * 1.0);
//    let dark_color: vec3<f32> = vec3<f32>(0.1) * clamp(color, vec3<f32>(0.), vec3<f32>(1.));
//    let out_color = vec4<f32>(mix(vec3<f32>(0.), clamp(color, vec3<f32>(0.), vec3<f32>(1.)), vec3<f32>(brightness)), 1.0);
//    return out_color;
//    return vec4<f32>(tx.normal.xyz, 1.);
    let darken_amount = 0.2;
    let dark1: i32 = i32((tx.pos.x)) % 2 - 1;
    let dark2: i32 = i32((tx.pos.y)) % 2 - 1;
    let dark3 = darken_amount * f32(abs(dark1 - dark2)) + 1.0 - darken_amount;
    let color = vec4<f32>((tx.normal.z * 0.5 + 0.5) * dark3 * color, 1.0);
    return color;
}
