uniform sampler2D obraz;
uniform sampler2D Z_Buffer;
uniform float distEntity;
uniform vec2 screenresolution;

void main()
{
	vec2 uv = vec2(gl_TexCoord[0].x,gl_TexCoord[0].y);	
	vec4 tex = texture2D(obraz,uv.xy);
	vec4 buf = texture2D(Z_Buffer,gl_FragCoord.xy/screenresolution.xy);

	float distanceFromBuffer = (buf.r*256.0*256.0*256.0*256.0+buf.g*256.0*256.0*256.0+buf.b*256.0*256.0+buf.a*256.0);
	if(distEntity > distanceFromBuffer)tex.a = 0.0;

	gl_FragColor = tex;
}
