#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define NK_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_STANDARD_VARARGS
#include <nuklear.h>

#define NK_GLFW_GL2_IMPLEMENTATION
#include <nuklear_glfw_gl2.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, 1);
            break;
    }
}

int main(int argc, char** argv)
{
    int ch, width, height;
    GLFWwindow* window;
    struct nk_context* nk;
    struct nk_font_atlas* atlas;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    width = 640;
    height = 480;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    window = glfwCreateWindow(width, height, "AAAAA", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    nk = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
    nk_glfw3_font_stash_begin(&atlas);
    nk_glfw3_font_stash_end();

    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        nk_glfw3_new_frame();

        if (nk_begin(nk, "", nk_rect(50, 50, 200, 100), 0))
        {
            nk_layout_row_dynamic(nk, 30, 1);
            nk_label(nk, "Hello World! SIUUU", NK_TEXT_CENTERED);
        }
        nk_end(nk);

        nk_glfw3_render(NK_ANTI_ALIASING_ON);
        glfwSwapBuffers(window);
    }

    nk_glfw3_shutdown();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
