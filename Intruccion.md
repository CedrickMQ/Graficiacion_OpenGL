<!-- 

Si quieres que esto se Vea bonito y con formato 
DESCARGA EL PLUGIN:

    "Markdown Preview Enhanced" 
        De Yiyi Wang 

Y presiona las teclas:

    CTRL + SHIFT + V

ESTAS AVISADO !!!


-->

# Como funciona esto?

Este es proyecto el cual usa lo que es **OpenGL** para el manejo de graficos, sinembargo las herremientas que se estan usando son las de **GLFW** estas son las que de verdad permiten el uso de los graficos, en conjunto de lo que es **CMake** este es un generador de codigo.
Los distintos documentos y elementos que encontraran dentro de este son extraidos de forma del GitHub de [GLFW](https://github.com/glfw/glfw), por mi parte añadi otra carpeta en la cual trabajare los graficos la cual es *proyectGra* 

---

## Herramientas que usa

para poder ejecutar el proyecto es necesario lo siguiente:

>- #### GLFW 
>    Esta ya esta descargada, puesto que es practicamente todo el proyecto que se subio.
>
>- #### CMake
>    Este es necesario descargar *( Segun tutu y un pdf )* se descarga en el siguiente [link](https://cmake.org/download/), yo descarge "Windows x64 Installer".

para lo que es visual le coloque varios plugins que me ayudaron a ejecutar el codigo, los cuales fueron:

>- #### C/C++
>    De Microsoft
>
>- #### C/C++ Themes
>    De Microsoft
>
>- #### C/C++ Extension pack
>    De Microsoft
>
>- #### CMake 
>    De twxs
>
>- #### CMake Tools
>    De Microsoft

---

## Estructura de carpetas

> - #### glfw-3.3.9
>   - __CMake__
        Estas son una serie el Scripts para el funcionamineto en distintos dispositivos (alchile no se pero no le muevan)
>   - __deps__
        Este pose las librerias a las cuales se debe hacer referencia para poder trabajar con los graficos (GLUT)
>   - __docs__
        Es un Html raro que lleva a la documentacion del la libreria (no es la documentacion, es un link a la documentacion)
>   - __examples__
        Tiene el nombre de ejemplos pero estos no se pueden ejecutar (o yo no pude), solo para "ver como funciona".
>   - __include__
        Este pose otra serie de elementos que se deben referenciar para ejecutar los graficos (El __GLFW__).
>   - __ProyectGra__
        Esta contiene el material para el proyecto de graficacion. (no funciona)
>   - __src__
        Ni idea no le muevan.
>   - __tests__
        Estos son ejemplos de lo que se pueden ejecutar con la libreria y se pueden ejecutar.
>   - _Otros_
        En general es documentacion.


> Detalles
        El codigo para la recta esta en  Test > Z_Linea 

---

## Como correr los programas 

Para esto hacemos uso de lo que es uso de lo que es el simbolo de play que aparece en la parte inferior azul, la primera vez les saldra un menu que le permitira seleccionar entre vario elementos (yo escogi el ultimo, el que dice Windows), estos son los proyectos que podemos encontrar en el apartado *"examples"*, cuando ejecuten un Script les abrira una terminal con la cual podran ejecutar los distintos codigos de la carpeta.

Debo aclarar que los codigos ejecutables estan fuera de la carpeta "glfw-3.3.9", estan el **build** entre un mar de codigo asi que si modifican algo y quieren ver si funciona o falla, se debera hacer otro compilado (cosa que aun no se hacer ... ).


--- 

**Nota**:
Apenas le estoy entendiendo a esta madre asi que si encuentran algo o me equivoque en algo porfabor corijan :v 