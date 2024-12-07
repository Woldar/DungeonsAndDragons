uniform sampler2D texture;
uniform vec2 resolution;
uniform float radius; // The blur radius

void main() {
    vec2 texCoord = gl_TexCoord[0].xy;
    vec4 color = vec4(0.0);
    float total = 0.0;

    // Gaussian weights and offsets
    for (float x = -radius; x <= radius; x++) {
        for (float y = -radius; y <= radius; y++) {
            vec2 offset = vec2(x, y) / resolution;
            float weight = exp(-(x * x + y * y) / (2.0 * radius * radius));
            color += texture2D(texture, texCoord + offset) * weight;
            total += weight;
        }
    }

    gl_FragColor = color / total;
}