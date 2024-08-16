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

float x1, x2, y1, y2;

void drawPixelLine(float x1, float y1, float x2, float y2){
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);

    float XDiag, YDiag, XRecta, YRecta;

    float dy = (y2 - y1);
    float dx = (x2 - x1);

    float Dis = 0.001f;

    if (dy >= 0)
    {
        YDiag = Dis;
    } else {
        dy = -dy;
        YDiag = -Dis;
    }

    if (dx >= 0)
    {
        XDiag = Dis;
    } else {
        dx = -dx;
        XDiag = -Dis;
    }

    if (dx >= dy)
    {
        YRecta = 0;
        XRecta = XDiag;
    } else {
        XRecta = 0;
        YRecta = YDiag;
    }

    float x = x1;
    float y = y1;

    float avR = 2 * dy;
    float av = avR - dx;
    float avI = av - dx;

    for(;((x <= x2) && (y <= y2));)
    {
        glVertex2f(x,y);
 
        if (av >= 0)
        {
            x = x + XDiag;
            y = y + YDiag;
            av = av + avI;
        } else {
            x = x + XRecta;
            y = y + YRecta;
            av = av + avR;
        }
    }

    glEnd();

}

void drawLine(float x1, float y1, float x2, float y2) {
    // Establecer el color de la línea (en este caso, rojo)
    glColor3f(1.0f, 0.0f, 0.0f);

    // Dibujar la línea utilizando glBegin y glEnd
    glBegin(GL_LINES);
    glVertex2f(x1, y1); // Punto inicial de la línea
    glVertex2f(x2, y2);   // Punto final de la línea
    glEnd();
}

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

    x1 = -0.5;
    y1 = -0.5;

    x2 = 0.5;
    y2 = 0.5;

    if (x1 < -1.0)
    {
        float XDistancia = x1 - x2;
        if (XDistancia < 0)
        {
            XDistancia = XDistancia * -1;
        }

        float YDistancia = y1 - x2;
        if (YDistancia < 0)
        {
            YDistancia = YDistancia * -1;
        }
        
        float Name ;
        if (XDistancia > YDistancia) {
            Name = XDistancia / YDistancia; 
        } else {
            Name = YDistancia / XDistancia;
        }
    }

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
        glFlush();


        nk_glfw3_new_frame();

        if (nk_begin(nk, "", nk_rect(50, 50, 200, 50), 0))
        {
            nk_layout_row_dynamic(nk, 30, 1);
            nk_label(nk, "Hello World!!", NK_TEXT_CENTERED);
            nk_label(nk, "SIUUU", NK_TEXT_CENTERED);
        }
        nk_end(nk);

        // drawLine(x1, y1, x2, y2); // Llamar a la función para dibujar la línea 
        // drawPixelLine(x1, y1, x2, y2);

        nk_glfw3_render(NK_ANTI_ALIASING_ON);
        glfwSwapBuffers(window);
    }

    nk_glfw3_shutdown();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
