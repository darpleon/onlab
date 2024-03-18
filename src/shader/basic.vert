#version 460 core
    layout (location = 0) in vec2 pos;
    uniform mat4 camera;
    void main()
    {
       mat3 m = mat3(-1.0);
       gl_Position = camera * vec4(pos.x, pos.y, 1.0, 1.0);
       // vec3 flipped = m * vec3(pos, 1.0);
       // gl_Position = vec4(flipped, 1.0);
       // gl_Position = vec4(pos, 1.0, 1.0);
    }
