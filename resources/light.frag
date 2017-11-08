#ifdef GL_ES
#define LOWP lowp
precision mediump float;
#else
#define LOWP
#endif

//varying LOWP vec4 vColor;
//varying vec2 vTexCoord;
 
//texture samplers
uniform sampler2D u_texture; //diffuse map
uniform sampler2D u_lightmap;   //light map
//uniform vec4 color;
uniform float intensity;
 
//additional parameters for the shader
uniform vec2 resolution; //resolution of screen
//uniform LOWP vec4 ambientColor; //ambient RGB, alpha channel is intensity 
 
void main() {
    vec2 lighCoord = (gl_FragCoord.xy / resolution.xy);
   // vec4 diffuseColor = texture2D(u_texture, gl_TexCoord[0].xy);
    vec4 light = texture2D(u_lightmap, lighCoord);
    //float intensity = 15.0;
    light = light * vec4(intensity,intensity,intensity,1.0);
    light = light + vec4(1.0,1.0,1.0,1.0);
 
    //vec3 ambient = ambientColor.rgb * ambientColor.a;
    //vec3 intensity = ambient + light.rgb;
    //vec3 finalColor = diffuseColor.rgb * intensity;
 
    //gl_FragColor = gl_Color * vec4(finalColor, diffuseColor.a);
    gl_FragColor = (gl_Color * texture2D(u_texture, gl_TexCoord[0].xy) + vec4(0.02,0.02,0.02,0)) * light;
    //gl_FragColor = (gl_Color * texture2D(u_texture, gl_TexCoord[0].xy)) * light;
}
