# Files and Directories #

[![Developed by @santiago-b9826](https://img.shields.io/badge/developed%20by-%40SantiagoBedoya-blue.svg  "Santiago Bedoya")](https://github.com/santiago-b9826)   [![Developed by @linamariaum](https://img.shields.io/badge/developed%20by-%40linamariaum-ff69b4.svg  "Lina María Uribe")](https://github.com/linamariaum)

En esta tarea, nos familiarizaremos con el API descrito en el capítulo del libro. Para hacer esto, usted solo debe escribir unos cuantos programas, la mayoria basada en varias utilidades UNIX.

## Preguntas ##

1. **Stat**: Escriba su propia versión del comando ```stat```, la cual simplemente invoca la llamada del sistema ```stat()``` en un archivo o directorio. Imprima el tamaño del archivo, el número de bloques asignado, reference (link) count, etc. ¿Qué es el link count de un directorio, ¿cómo el numero de entradas en el directorio cambia? Interfaces Útiles: ```stat()```, naturalmente.

    > Un ```hard link``` es una nueva forma de hacer una entrada en el árbol del sistema de archivos, a través de una llamada al sistema conocida como ***link()***. La llamada al sistema link() toma dos argumentos, el antiguo nombre de ruta y uno nuevo; cuando "vincula" un nuevo nombre de archivo a uno antiguo, esencialmente crea otra forma de referirse al mismo archivo, es decir, crea otro nombre para el archivo y lo remite al mismo número de inodo del archivo original; el archivo no se copia, más bien, ahora tiene dos nombres que ambos se refieren al mismo archivo. El comando ```ln``` se usa para hacer esto, es decir, crear el ```hard link```. Ahora, el ***link count*** de un directorio (llamado también recuento de referencias), es el número de links o enlaces, permite que el sistema de archivos rastree cuántos nombres de archivos diferentes se han vinculado a un inodo particular. El ```link count``` de un archivo se puede ver usando la llamada al sistema ***stat()***.

    > Un directorio tiene un ```link count``` que comienza en 2, uno es el normal que proviene de la entrada en el directorio principal, mientras que el segundo proviene del "." entrada (el directorio se vincula a sí mismo). Cada subdirectorio agregado aumenta el ```link count``` en uno, debido a la entrada en cada subdirectorio.

    > El programa **Stat** se encuentra en este repositorio como: ```myStat.c```. Importante, antes de ejecutar este programa, es necesario compilarlo.

    > Para compilar: ```gcc myStat.c -o myStat.out -Wall```

2. **List Files**: Escriba un programa que liste los archivos en un directorio dado. Cuando sea llamado sin argumentos, el programa deberá solo imprimir los nombres del archivo. Cuando se invoque con la flag ```-l```, el programa deberá imprimir la información de cada archivo tal como, owner, group, permissions y otra información obtenida de la llamada de sistema ```stat()```. El programa deberá tomar un argumento adicional el cual es el directorio a leer, por ejemplo, ```myls -l directory```.  Si ningún directorio es dado, el programa solo deberá usar el directorio de trabajo actual. Interfaces Útiles: ```stat()```, ```opendir()```, ```readdir()```, ```getcwd()```.

    > El programa **List Files** se encuentra en este repositorio como: ```myls.c```. Importante, antes de ejecutar este programa, es necesario compilarlo, igualmente compilar el programa ```myStat.c``` para el correcto funcionamiento de **List Files**.

    > Para compilar: ```gcc myls.c -o myls.out -Wall```

3. **Recursive Search**: Escriba un programa que imprima los nombres de cada archivo y directorio del arbol del sistema de archivos (file system tree), empezando en un punto dado del sistema de archivos en el arbol. Por ejemplo, cuando ejecute sin argumentos, el programa deberá empezar con el directorio de trabajo actual e imprimir su contenido, asi como con los contenidos de cualquier subdirectorio en este, etc., hasta que el arbol entero, root en el CWD sea impreso. Si se da un unico argumento (de un nombre de un directorio), use este como root en vez de el del sistema. Refine su busqueda recursiva con mas opciones de busqueda divertidas, similar a la poderosa herramienta por linea de comandos ```find```.


## Referencias de utilidad ##

1. [Conceptos basicos claves resumidos](https://docs.google.com/document/d/1-336S7oKYwzSSSH-vzks8lGJ0R5VJoZu3PGBsz3vP2w/edit?usp=sharing)
2. [Aspectos basicos de C](https://github.com/repos-SO-UdeA/lab3)
3. [Manejo dinamico de memoria en C](https://github.com/repos-SO-UdeA/lab5)
4. [Manejo de archivos en C](https://github.com/repos-SO-UdeA/lab6)

