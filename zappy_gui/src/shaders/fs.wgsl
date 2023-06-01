[[stage(fragment)]]
fn main([[location(0)]] normal: vec3<f32>, [[builtin(position)]] position: vec4<f32>) -> [[location(0)]] vec4<f32> {
    let light: vec3<f32> = vec3<f32>(0.5, 1.0, 2.0);
//    let color: vec3<f32> = normal.xyz * 0.5 + 0.5;
    let color: vec3<f32> = vec3<f32>(1.0);
    let brightness: f32 = dot(normalize(normal), normalize(light));
    let dark_color: vec3<f32> = vec3<f32>(0.1) * color;
    let out_color = vec4<f32>(mix(dark_color, color, vec3<f32>(brightness)), 1.0);
    return out_color;
//    return vec4<f32>(color, 1.0);
}