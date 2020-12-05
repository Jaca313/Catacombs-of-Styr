uniform sampler2D obraz;
uniform sampler2D Z_Buffer;
uniform float distEntity;
void main()
{
	float maximum;
	vec2 uv = vec2(gl_TexCoord[0].x,gl_TexCoord[0].y);	
	vec4 tex = texture2D(obraz,uv.xy);
	vec4 buf = texture2D(Z_Buffer,vec2(uv.x,0.0));

	int distanceFromBuffer = (buf.r*256*256*256+buf.g*256*256+buf.b*256+buf.a);
	//if(distEntity < 1.0)tex.r = 1.0;
	//tex.r = distEntity/256.0;
	//tex.r = buf.r*4*64*64;
	//distanceFromBuffer = distanceFromBuffer;
	gl_FragColor = tex;//vec4(distanceFromBuffer,distanceFromBuffer,distanceFromBuffer,1.0);
}

//dont know what that striping is find out!!!!