const char* vertexScreenShaderSource = R"(
    #version 330 core 
    layout (location = 0) in vec2 Pos;
    layout (location = 1) in vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 Proj;

    out vec2 Tex;

    void main()
    {
        gl_Position  = Proj * model * vec4(Pos,0.0f,1.0f);
        Tex = TexCoord;
    }

)";

const char* fragmentScreenShaderSource = R"(
    #version 330 core
    out vec4 Color;
    
    in vec2 Tex;
    uniform vec3 ObjColor;
    uniform sampler2D ourTexture;
   
    void main()
    {   
       Color = texture(ourTexture,Tex); 
    };
)";