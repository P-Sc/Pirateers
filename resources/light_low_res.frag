#version 130

uniform sampler2D u_texture;
uniform sampler2D u_lightmap;
uniform float intensity;
uniform vec2 resolution;
uniform vec2 uShift;

const int gaussRadius = 11;
const float gaussFilter[gaussRadius] = float[gaussRadius](
	0.0402,0.0623,0.0877,0.1120,0.1297,0.1362,0.1297,0.1120,0.0877,0.0623,0.0402
);

void main() {
    vec2 lightCoord = (gl_FragCoord.xy / resolution.xy);
    vec2 texCoord = lightCoord - float(int(gaussRadius/2)) * uShift;
    
    vec4 light = vec4(0.0, 0.0, 0.0, 0.0);
    for (int i=0; i<gaussRadius; ++i) { 
		light += gaussFilter[i] * texture2D(u_lightmap, texCoord);
		texCoord += uShift;
	}
    
    // Multiply
    light = light * vec4(intensity,intensity,intensity,1.0);
    float gr = 3;
    //light = light * vec4(gr,gr,gr,0);
    light = light + vec4(1.0,1.0,1.0,1.0);
    
    // Apply 
    gl_FragColor = (gl_Color * texture2D(u_texture, gl_TexCoord[0].xy) + vec4(0.02,0.02,0.02,0)) * light;
}
