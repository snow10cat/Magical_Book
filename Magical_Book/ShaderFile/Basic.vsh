
 precision highp float;
// precision mediump float;
// precision lowp float;

attribute vec2 attr_uv;
attribute vec4 attr_pos;

uniform mat4 unif_translate;
uniform mat4 unif_rotate;
uniform mat4 unif_scale;

varying vec2 vary_uv;

void main( void)
{
	vary_uv = attr_uv;
	gl_Position = unif_translate * attr_pos;
}
