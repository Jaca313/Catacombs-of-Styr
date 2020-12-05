uniform sampler2D obraz;


void main( out vec4 fragColor)
{
	vec2 uv = vec2(gl_TexCoord[0].x,gl_TexCoord[0].y);	
	uv.y = 1.0 - uv.y;

	vec3 tex = texture2D(obraz,uv);

	fragColor = vec4(tex,1.0);
}