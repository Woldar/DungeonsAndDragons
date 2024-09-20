uniform vec2 buttonCenter;    // Center of the button in screen coordinates
uniform float buttonRadius;   // Radius of the button
uniform vec2 screenSize;      // Size of the screen (width, height)

void main() {
    // Get the current pixel position
    vec2 pixelPos = gl_FragCoord.xy;
    
    // Calculate the distance between the pixel and the button center
    float distance = length(pixelPos - buttonCenter);

    // Normalize the distance based on the screen size
    float maxDistance = length(screenSize / 2.0); // Max possible distance on screen

    // Calculate alpha based on the distance from the button
    float alpha = clamp(distance / maxDistance, 0.0, 1.0);

    // Darken the screen based on alpha (further means more dimming)
    gl_FragColor = vec4(0.0, 0.0, 0.0, alpha);  // Black color with variable transparency
}