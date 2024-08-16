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
int window_width = 400;
int window_height = 400;

void drawLine(float x1, float y1, float x2, float y2) {
    // Establecer el color de la línea (en este caso, rojo)
    glColor3f(1.0f, 0.0f, 0.0f);

    // Dibujar la línea utilizando glBegin y glEnd
    glBegin(GL_LINES);
    glVertex2f(x1, y1); // Punto inicial de la línea
    glVertex2f(x2, y2);   // Punto final de la línea
    // glVertex2f(1.5f,1.2f);
    glEnd();
}

void drawPixelLine(float x1, float y1, float x2, float y2){
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);

    float XDiag, YDiag, XRecta, YRecta;

    float dy = (y2 - y1);
    float dx = (x2 - x1);
    float AB_dx, AB_dy;

    float Dis = 0.001f;

    if (dy <= 0) {
        AB_dy = -dy;
    } else {
        AB_dy = dy;
    }

    if (dx <= 0) {
        AB_dx = -dx;
    } else {
        AB_dx = dx;
    }

    if (AB_dx >= AB_dy) {
        XDiag = (dx >= 0) ? 0.001f : -0.001f;
        YDiag = (dy / dx) * XDiag;
    } else {
        YDiag = (dy >= 0) ? 0.001f : -0.001f;
        XDiag = (dx / dy) * YDiag;
    }

    // if (dy >= 0)
    // {
    //     YDiag = Dis;
    // } else {
    //     // dy = -dy;
    //     YDiag = -Dis;
    // }

    // if (dx >= 0)
    // {
    //     XDiag = Dis;
    // } else {
    //     // dx = -dx;
    //     XDiag = -Dis;
    // }

    // if (dx >= dy)
    // {
    //     YRecta = 0;
    //     XRecta = XDiag;
    // } else {
    //     XRecta = 0;
    //     YRecta = YDiag;
    // }

    float x = x1;
    float y = y1;

    float avR = 2 * AB_dy;
    float av = avR - AB_dx;
    float avI = av - AB_dx;

    for(;((x <= x2) && (y <= y2));)
    {
        glVertex2f(x,y);
 
        if (av >= 0)
        {
            x = x + XDiag;
            y = y + YDiag;
            av = av + avI;
        } else {
            // x = x + XRecta;
            // y = y + YRecta;
            x += (dx >= 0) ? 0.001f : -0.001f;
            y += (dy >= 0) ? 0.001f : -0.001f;
            av = av + avR;
        }
    }

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    window_width = width;
    window_height = height;
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

    float M;

    float XDistancia = x2 - x1;
    float YDistancia = y2 - y1;

    M = YDistancia / XDistancia;

    char m_string[50];
    sprintf(m_string, "valor de M = %.2f", M);

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    window_width = mode->width * 0.8; // Por ejemplo, el 80% del ancho del monitor
    window_height = mode->height * 0.8;

    window = glfwCreateWindow(window_width, window_height, "AAAAA", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    nk = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
    nk_glfw3_font_stash_begin(&atlas);
    nk_glfw3_font_stash_end();    
    
    char coord_string[50];
    
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
// No Mover esta mierda ===============
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0 * (float)window_width / window_height, 1.0 * (float)window_width / window_height, -1.0, 1.0, -1.0, 1.0); // Configurar proyección ortográfica
        glMatrixMode(GL_MODELVIEW);
// ====================================
        glFlush();

        // drawLine(x1, y1, x2, y2);
        drawPixelLine(x1, y1, x2, y2);

        nk_glfw3_new_frame();

        if (nk_begin(nk, "", nk_rect(0, 0, 200, 500), 0))
        {
            nk_layout_row_dynamic(nk, 30, 1);
            nk_label(nk, m_string, NK_TEXT_CENTERED);
            nk_label(nk, "Cordenandas", NK_TEXT_CENTERED);
        }

        float step = 0.01f; 
        float current_x = x1;
        float current_y = y1;
        
        while ((current_x <= x2) && (current_y <= y2))
        { 
            char coord_string[50];  
            sprintf(coord_string, "(%.2f, %.2f)", current_x, current_y);
            nk_label(nk, coord_string, NK_TEXT_CENTERED); 
            if ((x2 - current_x) >= (y2 - current_y)) {
                current_x += (x2 >= current_x) ? step : -step;
                current_y += (y2 >= current_y) ? (step * (y2 - y1) / (x2 - x1)) : -(step * (y2 - y1) / (x2 - x1));
            } else {
                current_y += (y2 >= current_y) ? step : -step;
                current_x += (x2 >= current_x) ? (step * (x2 - x1) / (y2 - y1)) : -(step * (x2 - x1) / (y2 - y1));
            }
        } 
        nk_end(nk);
 
        nk_glfw3_render(NK_ANTI_ALIASING_ON);
        glfwSwapBuffers(window);
    }

    nk_glfw3_shutdown();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
