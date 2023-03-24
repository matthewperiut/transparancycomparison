#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLuint WIDTH = 1280, HEIGHT = 720;

const std::string vertexShaderSource = R"glsl(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec2 texCoords;

    out vec2 TexCoords;

    void main()
    {
        gl_Position = vec4(position, 1.0f);
        TexCoords = texCoords;
    }
)glsl";

const std::string fragmentShaderSource = R"glsl(
#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D tex256;
uniform sampler2D tex1280;

void main()
{
    vec2 scaledCoords = floor(TexCoords * 1280.0 / 5.0) / (1280.0 / 5.0);

    vec4 smallTexColor = texture(tex256, scaledCoords);
    vec4 largeTexColor = texture(tex1280, TexCoords);
    if (largeTexColor.a > smallTexColor.a)
    {
        color = vec4(largeTexColor.rgb, 1.0f);
    }
    else
    {
        color = vec4(smallTexColor.rgb, 1.0f);
    }
}
)glsl";

GLFWwindow* initWindow();
GLuint compileShader(const char* shaderSource, GLenum shaderType);
GLuint createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
GLuint generateQuadVAO();
GLuint loadTexture(const char* imagePath);

int main()
{
    GLFWwindow* window = initWindow();
    if (!window)
    {
        return -1;
    }

    GLuint shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    GLuint quadVAO = generateQuadVAO();
    GLuint tex256 = loadTexture("imgs/256.png");
    GLuint tex1280 = loadTexture("imgs/1280.png");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(quadVAO);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex256);
                glUniform1i(glGetUniformLocation(shaderProgram, "tex256"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex1280);
        glUniform1i(glGetUniformLocation(shaderProgram, "tex1280"), 1);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}