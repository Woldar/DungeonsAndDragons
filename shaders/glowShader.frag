uniform float time;          // Current time for animation
uniform vec4 glowColor;      // The glow color (RGBA)
uniform vec2 resolution;     // Resolution of the glow shape

void main() {
    vec2 uv = gl_FragCoord.xy / resolution;

    // Calculate distance from the center
    float dist = length(uv - vec2(0.5, 0.5));

    // Create a radial glow effect
    float intensity = 0.5 + 0.5 * sin(time * 3.0); // Pulsating effect
    float glow = smoothstep(0.5, 0.0, dist) * intensity;

    // Apply glow color
    gl_FragColor = glowColor * glow;
}