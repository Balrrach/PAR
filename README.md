# Description
Solution to the problem of clustering with constrains using different metaheuristics.

# CMAKE
Para facilitar la portabilidad a otros sistemas operativos se entrega junto a la practica un fichero CMakeLists.txt con el que 
se puede elaborar un archivo tipo makefile válido para el sistema operativo deseado. A modo de prueba se ha creado en un archivo 
tipo minGW Makefile válido para Windows. Para poder crear este fichero o ejecutarlo hay que tener instaladas las herramientas 
de compilación que ofrece GNU para Windows, en concreto basta con tener instalado el paquete mingw32-gcc-g++ y el programa mingw32-make. 
Estas herramientas se pueden obterner de forma sencilla a través del programa MinGW Instaler que se puede descargar desde su página web. 
Una vez se cuente con estas herramientas hay que descargar e instalar la aplicación cmake desde su página web y ejecutar la aplicación 
especificando las opciones deseadas.

Es muy importante que el programa se ejecute desde el directorio /bin y que no se modifique la estructura de directorios proporcionada 
de lo contrario la lectura de los datos o la salida producida al ejecutar el benchmark podrían fallar.


# Parameters
El programa diseñado para soportar dos casos de uso:
    1. Algoritmo y dataset específicos: En el caso de querer ejecutar un algoritmo concreto con un dataset bajo un conjunto de 
    restricciones concretas hay que pasar exactamente los siguientes argumentos:
    (a) Dataset:
        zoo: Para el dataset zoo.csv
        glass: Para el dataset glass.csv
        bupa: Para el dataset bupa.csv
    (b) Restricciones:
        10: Para tener un 10% de restricciones
        20: Para tener un 20% de restricciones
    (c) Algoritmo:
        GREEDY: Para ejecutar greedy
        BL: Para ejecutar búsqueda local
        BMB: Para ejecutar el algoritmo de Búsqueda Multiarranque Básica
        ES: Para ejecutar el algoritmo de Enfriamiento Simulado
        ILS: Para ejecutar el algoritmo de Búsqueda Local Reiterada clásico
        ILS-ES: Para ejecutar el algoritmo de Búsqueda Local Reiterada con Enfriamiento Simulado

    2. Benchmark: En caso de querer ejecutar los casos de uso de los que se han extraído los resultados expuestos en las tablas 
    más adelante hay que pasar como primer argumento la letra: 'B' y como segundo argumento el número de la práctica asociada con dichos algoritmos.

En caso la semilla se puede especificar como último parámetro y en el caso del benchmark las ejecuciones se realizaran utilizando dicha semila y las cuatro posteoriores.


# Output
Si el programa se ejecuta en modo benchmark entonces, al terminar la ejecución, se generarán un conjunto de archivos en el directorio 
/results en formato CSV en los que se muestran todos los resultados en forma de tabla. Incido, para que la generación de los archivos 
se realice de forma correcta es necesario que se mantenga la estructura de directorios tal y como ha sido proporcionada.

Note: To correctly use clang as language server one has to execute the line in the .task file project_init function to get the compile_commands.json and the correct directory structure
