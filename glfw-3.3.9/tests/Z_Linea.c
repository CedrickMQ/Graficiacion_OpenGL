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

    x2 = 0;
    y2 = 0;

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
    height = 880;

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
    
    char coord_string[50];
    
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();

        nk_glfw3_new_frame();

        if (nk_begin(nk, "", nk_rect(0, 50, 200, 900), 0))
        {
            nk_layout_row_dynamic(nk, 30, 1);
            nk_label(nk, "Cordenandas", NK_TEXT_CENTERED);
        }

        float step = 0.01f; // Paso para incrementar x e y
        float current_x = x1;
        float current_y = y1;
        // Bucle para dibujar la línea y mostrar las coordenadas
        while ((current_x <= x2) && (current_y <= y2))
        {
            // glVertex2f(current_x, current_y); // Dibuja el punto
            char coord_string[50]; // Cadena para almacenar las coordenadas
            sprintf(coord_string, "(%.2f, %.2f)", current_x, current_y);
            nk_label(nk, coord_string, NK_TEXT_CENTERED); 
            if ((x2 - current_x) >= (y2 - current_y)) {
                // Si la distancia horizontal es mayor o igual que la vertical
                current_x += (x2 >= current_x) ? step : -step;
                current_y += (y2 >= current_y) ? (step * (y2 - y1) / (x2 - x1)) : -(step * (y2 - y1) / (x2 - x1));
            } else {
                // Si la distancia vertical es mayor que la horizontal
                current_y += (y2 >= current_y) ? step : -step;
                current_x += (x2 >= current_x) ? (step * (x2 - x1) / (y2 - y1)) : -(step * (x2 - x1) / (y2 - y1));
            }
        } 

        nk_end(nk);

        // glEnd();

        //drawLine(x1, y1, x2, y2); // Llamar a la función para dibujar la línea 
        drawPixelLine(x1, y1, x2, y2);

        nk_glfw3_render(NK_ANTI_ALIASING_ON);
        glfwSwapBuffers(window);
    }

    nk_glfw3_shutdown();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
