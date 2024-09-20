#version 330 core

uniform vec2 buttonCenter;    // Center of the button in screen coordinates
uniform float buttonRadius;   // Radius of the button
uniform vec2 screenSize;      // Size of the screen (width, height)

void main() {
    // Get the current pixel position in window space
    vec2 pixelPos = gl_FragCoord.xy;

    // Calculate the distance between the pixel and the button center
    float distance = length(pixelPos - buttonCenter);

    // Set the maximum distance that will be dimmed
    float maxDimDistance = length(screenSize / 2.0);  // Maximum possible distance on screen

    // Compute the dimming factor based on the distance from the button
    float dimFactor = smoothstep(buttonRadius, maxDimDistance, distance);

    // Get the current pixel color (you might want to sample a texture instead here)
    vec4 pixelColor = gl_FragColor;

    // Apply dimming to the pixel color based on the dimFactor
    vec4 dimmedColor = mix(pixelColor, vec4(0.0, 0.0, 0.0, 1.0), dimFactor);  // Dim to black gradually

    gl_FragColor = dimmedColor;
}