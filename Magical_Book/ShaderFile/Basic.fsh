
precision highp float;
// precision mediump float;
// precision lowp float;

uniform float alpha;
uniform sampler2D texture;
varying vec2 vary_uv;

void main( void)
{
	vec4 color = texture2D( texture, vary_uv);
	color.a = alpha / 255.0f;
	gl_FragColor = color;
}
