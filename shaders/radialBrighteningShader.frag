uniform sampler2D texture;      // Background texture
uniform vec2 buttonCenter;      // Center of the hovered button
uniform float buttonRadius;     // Radius of maximum brightening around the button
uniform vec2 screenSize;        // Size of the screen
uniform float maxBrightFactor;  // Maximum brightening factor

void main() {
    // Get the fragment's current position on the screen
    vec2 fragPos = gl_FragCoord.xy;

    // Clamp the fragment position to ensure it's within the screen's boundaries
    vec2 clampedFragPos = clamp(fragPos, vec2(0.0, 0.0), screenSize);

    // Sample the texture at the current fragment position
    vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);

    // Calculate the distance from the current fragment to the button center
    float dist = distance(clampedFragPos, buttonCenter);

    // Calculate brightening factor based on the distance
    float brightFactor = clamp((buttonRadius - dist) / (screenSize.x / 2.0), 0.0, maxBrightFactor);

    // Brighten the texture color based on the brightening factor (mix with white)
    vec3 finalColor = mix(texColor.rgb, vec3(1.0), brightFactor);

    // Set the final fragment color
    gl_FragColor = vec4(finalColor, texColor.a);
}