
 precision highp float;
// precision mediump float;
// precision lowp float;

attribute vec2 attr_uv;
attribute vec4 attr_pos;

varying vec2 vary_uv;

void main(void)
{
	vary_uv = attr_uv;
	gl_Position = attr_pos;
}
