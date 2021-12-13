layout (location = 0) in vec3 iPos;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec3 iColor;
layout (location = 3) in vec2 iTexCoord;

out vec3 TexCoords;

layout (std140) uniform PV {
    mat4 p;
    mat4 v;
    mat4 pv;
};

void main() {
    TexCoords = iPos;
    vec4 pos = p * mat4(mat3(v)) * vec4(iPos, 1.0);
    gl_Position = pos.xyww;
}
