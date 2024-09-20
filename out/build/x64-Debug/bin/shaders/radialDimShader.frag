uniform sampler2D texture;      // Background texture
uniform vec2 buttonCenter;      // Center of the hovered button
uniform float buttonRadius;     // Radius of no dimming around the button
uniform vec2 screenSize;        // Size of the screen
uniform float maxDimFactor;     // Maximum dimming factor

void main() {
    // Get the fragment's current position on the screen
    vec2 fragPos = gl_FragCoord.xy;

    // Clamp the fragment position to ensure it's within the screen's boundaries
    vec2 clampedFragPos = clamp(fragPos, vec2(0.0, 0.0), screenSize);

    // Sample the texture at the current fragment position
    vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);

    // Calculate the distance from the current fragment to the button center
    float dist = distance(clampedFragPos, buttonCenter);

    // Calculate dimming factor based on the distance
    float dimFactor = clamp((dist - buttonRadius) / (screenSize.x / 2.0), 0.0, maxDimFactor);

    // Dim the texture based on the distance factor (mixing with black)
    vec3 finalColor = mix(texColor.rgb, vec3(0.0), dimFactor);

    // Set the final fragment color
    gl_FragColor = vec4(finalColor, texColor.a);
}