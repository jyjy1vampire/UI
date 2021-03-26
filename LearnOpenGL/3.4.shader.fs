/*#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D texture;
uniform sampler2D texture1;

void main()
{
    //FragColor = texture(ourTexture, TexCoord);
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
	FragColor = mix(texture(texture, TexCoord), texture(texture1, TexCoord), 0.2);
}*/
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0); // set alle 4 vector values to 1.0
}