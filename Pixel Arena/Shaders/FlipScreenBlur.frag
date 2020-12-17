uniform sampler2D obraz;
uniform vec2 iResolution;

void main( out vec4 fragColor)
{
    float Pi = 6.28318530718; // Pi*2
    
    // GAUSSIAN BLUR SETTINGS {{{
    float Directions = 16.0; // BLUR DIRECTIONS (Default 16.0 - More is better but slower)
    float Quality = 8.0; // BLUR QUALITY (Default 4.0 - More is better but slower)
    float Size = 12.0; // BLUR SIZE (Radius) Default - 8.0

	// GAUSSIAN BLUR SETTINGS }}}   
    vec2 Radius = Size/iResolution.xy;

	// Normalized pixel coordinates (from 0 to 1)
	vec2 uv = vec2(gl_TexCoord[0].x,gl_TexCoord[0].y);	
	uv.y = 1.0 - uv.y;
	// Pixel colour
	fragColor = texture2D(obraz,uv);

	// Blur calculations
    for( float d=0.0; d<Pi; d+=Pi/Directions)
    {
		for(float i=1.0/Quality; i<=1.0; i+=1.0/Quality)
        {
			fragColor += texture2D( obraz, uv+vec2(cos(d),sin(d))*Radius*i);		
        }
    }
    
    // Output to screen
    fragColor /= Quality * Directions - 15.0;
}