// https://github.com/Hapaxia/Lens

#version 130

uniform sampler2D texture;
uniform float amount = 0.4;
uniform float thickness = 1.0;
uniform float spacing = 1.0;

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy) * gl_Color;
	if (mod(gl_FragCoord.y, round(thickness + spacing)) < round(spacing))
		pixel = vec4(pixel.rgb * (1.0 - amount), pixel.a);
	gl_FragColor = pixel;
}
