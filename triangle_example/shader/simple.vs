#version 330 core
layout (location = 0) in vec3 aPos; 
// location0번은 vao의 0번째 attribute대로 참고
void main(){
    gl_Position = vec4(aPos, 1.0);
}