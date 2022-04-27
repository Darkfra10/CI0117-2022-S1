# Tarea01: [tetris_solver_serial]

Tarea estrictamente individual. Fecha límite de entrega: Domingo 08 de Mayo a las 23:59. Se entrega en su repositorio personal.

## Descripción del problema

Tetris es un video juego tradicional en el cual se tiene un área de juego que cosiste en una cuadrícula de tamaño NxM (comúnmente se utiliza 20x10). Hay siete figuras geométricas diferentes, conocidas como *tetriminós* que están compuestas por cuatro bloques cuadrados unidos entre sí. Durante una partida de tetris, se van generando figuras de forma aleatoria, una por una, desde la parte superior del área de juego y éstas van cayendo hacia la parte inferior. La siguiente figura no se genera hasta que la actual figura no haya caido completamente.

Cada uno de los tetriminós se representa con una letra en mayúscula y posee cierta cantidad de rotaciones posibles:

![figures](http://jocan3.com/misc_images/tetris_figures.png)

Los jugadores pueden decidir la rotación de la pieza (0°, 90°, 180°, 270°) y en qué lugar debe caer. Cuando una línea horizontal se completa, esa línea desaparece y todas las piezas que están por encima descienden una posición, liberando espacio de juego y por tanto facilitando la tarea de situar nuevas piezas. Cada línea completa le da cierta cantidad de puntos al jugador, dependiendo del nivel y cuántas líneas se completaron en *combo*. El jugador también puede ver cuáles serán las siguientes K figuras (comúnmente seis figuras) y planear la posición basándose en las mismas.

Cuando las piezas se amontonan y colisionan con la parte superior del tablero, el juego se termina. Puede [jugarlo online](https://tetris.com/play-tetris) o ver un [gamepley](https://www.youtube.com/watch?v=QQ5U-rN7Veg) para entender mejor la dinámica.

En esta tarea se creará un solucionador de tetris utilizando el lenguage de programación C que determinará la mejor posición y la rotación de una figura de tetris en un momento dado. El programa recibe un estado de juego de tetris en un archivo con el siguiente formato:

- La línea 1 contiene un número que representa un identificador del estado del juego.
- La línea 2 contiene un número entero que representa la **profundidad** a calcular (explicación más adelante).
- La línea 3 contiene un número entero N que representa la cantidad de filas del área de juego.
- La línea 4 contiene un número entero M que representa la cantidad de columnas del área de juego.
- Las siguientes N líneas contienen cadenas de M caracteres que representan el área de juego. En el área de juego, un '0' significa un cuadro vacío, mientras que cualquier otro dígito representa un bloque ocupado.
- La siguiente línea contiene un número entero K que representa la cantidad de figuras "siguientes".
- Las últimas K líneas contienen un caracter representando alguno de las siete figuras diferentes. El primer caracter corresponde a la figura que cayendo en ese momento y a la cual se debe calcular la posición.

Ejemplo de entrada:

```
1650259796944
1
20
10
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0001111000
0000040000
0004440000
0000700000
0007770000
0002200000
0020220000
0220066000
0777742240
7
I
Z
I
J
S
L
S
```

Con respecto a la **profundidad**, ésta determina la cantidad de piezas a considerar para la jugada. Por ejemplo, si la profundidad es 0 entonces solo se toma en cuenta la primera figura. Si la profundidad es 1, entonces se toman en cuenta la primera y segunda figura, y así sucesivamente.

El cálculo de la jugada se realiza mediante *fuerza bruta* como ya se mencionó y se recomienda seguir un algoritmo de [búsqueda en profundidad](https://es.wikipedia.org/wiki/B%C3%BAsqueda_en_profundidad) (aunque se puede seguir cualquier otro método de fuerza bruta). Dependiendo del nivel, para cada rotación y posición de una figura, se calcularán también todas las combinaciones posibles de la siguiente. Por ejemplo, para la entrada mostrada anteriormente, dado que el nivel es 1 se consideran las primeras 2 figuras de la siguiente manera:

![play](http://jocan3.com/misc_images/tetris_solve_tree.png)
\
\
**Observaciones:** No debe implementar jugadas "inteligentes" donde una figura se gira a último momento para que quepa en un determinado espacio, sino que se asume que la figura se rota desde el inicio. Tampoco  es necesario calcular ni *limpiar* las líneas que se completan. El objetivo de esta tarea es principalmente colocar las figuras.

Cada vez que se coloque una pieza, se debe calcular un puntaje que nos diga "qué tan bueno" es el estado del juego en ese momento. Dada la complejidad del juego, no existe una fórmula perfecta, sin embargo en la Web se pueden encontrar diferentes soluciones y literatura al respecto (Por ejemplo: [Tetris: A Heuristic Study](http://kth.diva-portal.org/smash/get/diva2:815662/FULLTEXT01.pdf) o [Heuristic AI for playing tetris](https://github.com/takado8/Tetris)). El estudiante es libre de implementar la fórmula o estrategia que considere mejor para dicho cálculo. El puntaje se debe calcular siempre en los niveles más bajos (hojas del árbol).

Una vez que su solución haya recorrido todas las combinaciones posibles y calculado un puntaje para cada una, se debe guardar la mejor posición y rotación para cada figura.

Por cada nivel de profundidad, se espera que el programa genere un archivo "tetris_play_{nivel}.txt" que contenga:
- En la primera linea el identificador del estado del juego (el mismo recibido en el archivo de entrada).
- En la segunda línea la letra que representa la figura colocada en dicho nível.
- En la tercera línea el número que representa la rotación aplicada (0, 1, 2, ó 3)
- En la cuarta línea, el número de filas N del área de juego
- En la quinta línea, el número de columnas M del área de juego
- Y en las siguientes N líneas, hileras de M caracteres representando cada una de las filas del área de juego del estado original más las figuras del nivel actual y los anteriores colocadas en la mejor posición encontrada.

Ejemplo de salida esperada (tetris_play_0.txt):

```
1650259796944
I
1
20
10
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0001111000
0000040000
0004440000
0000700000
0007770000
1002200000
1020220000
1220066000
1777742240
```
Ejemplo de salida esperada (tetris_play_1.txt):
```
1650259796944
Z
0
20
10
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0001111000
0000040000
0004440000
0000700000
0007770000
1002200000
1020220220
1220066022
1777742240
```
Observe cómo en el archivo "tetris_play_0.txt", la matriz del área del juego tiene ahora la figura **I** en la columna 0 y en rotación 1 (vertical). Mientras que en el archivo "tetris_play_1.txt" la matriz agrega, además de la figura I, la figura **Z** en la columna 7 y en rotación 0. 

Si para un estado dado, el programa no puede encontrar del todo una posición valida para colocar la figura correspondiente al nivel, entonces **no** se debe generar ningún archivo de salida para dicho nivel ni para los siguientes. Los archivos de salida deben contener únicamente estados válidos.

## Entregables
En su repositorio personal cree una carpeta *tareas/tetris_solver_serial/* para esta tarea. Debe mantenerse la estructura de archivos y directorios característica de un proyecto de Unix:

- *bin/* folder con los ejecutables.
- *design/* folder con el diseño de la solución (Por ej. UML, pseudocódigo u otro).
- *src/* folder con el Código fuente (.h y .c).
- *test/* folder con archivos de casos de prueba.
- *Makefile* que compila y prueba con las diferente herramientas vistas en clase.
- *README.md* que describe el problema resuelto y el manual de usuario
- *.gitignore* debe ignorar los recursos que NO deben estar en control de versiones (por ej. archivos ejecutables, código binario, carpeta *build*, archivos del IDE, etc.)

Haga buen uso del repositorio de control de versiones. Cada commit debe tener un cambio con un mensaje significativo.

Si reutiliza código de alguna fuente, dé el respectivo crédito. Por ejemplo, basta un comentario en el código fuente que diga: // Adaptado de <URL>. No es necesario dar crédito a los ejemplos y materiales provistos por el profesor en este curso.

## Análisis
En un archivo README.md en notación Markdown (Si no conoce el formato Markdown, asegúrese de seguir un manual o buscar un tutorial, ya que la buena calidad del código también será evaluada). Su documento de análisis debe incluir:

- Una descripción del problema a resolver. Puede adaptar partes de este enunciado pero hacerlo más orientado a un usuario final.

- Un manual de uso, que indica cómo construir (compilar) la solución, y cómo correrla. Conviene proveer ejemplos de cómo correr el programa, sea de forma interactiva, o en lote redireccionando la entrada estándar.

- Una sección de créditos, donde indica su nombre e información de contacto (correo institucional). Si utiliza recursos de terceros, como imágenes o archivos de código fuente, dé el respectivo crédito.

## Diseño
Elabore un diagrama de la estructura de datos (por ej. tipos definidos y cómo interactúan entre ellos) utilizando UML o cualquier notación que usted conozca o haya utilizado en otros cursos. 
Exporte sus diagramas a archivos .svg o .png y almacénelos en la carpeta design/. En esta misma carpeta cree un archivo design/README.md. En este archivo incruste las imágenes de diseño. Además provea una descripción que ayude a una persona ajena al proyecto a comprender su diseño general. Se recomienda también agregar algún pseudocódigo del algoritmo principal utilizado para resolver el problema.

## Documentación
Las declaraciones de subrutinas y tipos de datos (e.j struct) públicos deben estar en archivos .h, y deben estar documentados. Puede utilizar el formato de ejemplo siguiente:

```c
/**
 @brief Read @a value_count double from stdin and store them in @a values array
 @param value_count Number of elements to be read from stdin
 @param values Array of elements. It must not be NULL
 @return An error code:
   0 for success.
   1 if EOF is found before @a value_count values are read
   2 if a valid double value cannot be read from stdin
*/
int read_values(const size_t value_count, double values[]);
```

## Implementación
Implemente su diseño (diagramas UML y pseudocódigo) en el lenguaje de programación C. Recuerde aplicar buenas prácticas de programación. Por ejemplo, las variables globales están prohibidas en esta y todas las evaluaciones del curso. Corra el linter con frecuencia.
  
Para el manejo de las figuras y las rotaciones utilice el código dado por el profesor: [tetris_figure_factory.c](https://github.com/jocan3/CI0117-2022-S1/blob/master/enunciados/tareas/01/tetris_figure_factory.c) y [tetris_figure_factory.h](https://github.com/jocan3/CI0117-2022-S1/blob/master/enunciados/tareas/01/tetris_figure_factory.h). Esto le ahorrará tiempo implementando la manipulación de las figuras.
  
Los siguientes son algunos detalles técnicos que debe tomar en cuenta:

### Validación de entrada
Aplique la buena práctica de programación defensiva. Su programa debe defenderse de entradas inválidas o mal intencionadas, como números incorrectos o caracteres no válidos.

### Estructuras de datos
La biblioteca estándar de C no tiene contenedores genéricos, por lo tanto se deben implementar de forma *manual* o reutilizar código de terceros.

### Optimización
Para esta tarea **no** es necesario optimizar la solución. Por el contrario, el enfoque debe ser resolver el problema utilizando fuerza bruta y no importa qué tan eficiente sea la solución mientras sea correcta (Por ej. Si para colocar una figura de tetris se recorre todo el área de juego varias veces hasta encontrar un espacio, sigue siendo una solución válida para esta tarea).

### Pruebas
Asegúrese de verificar el funcionamiento de su programa con el caso de prueba del enunciado y cree otros casos de prueba propios, utilizando diferentes tamaños y niveles de profundidad.

Su programa debe hacer buen uso de los recursos. Por ejemplo, no debe generar fugas de memoria, ni accesos inválidos, ni usar memoria no inicializada. Estas pruebas puede realizarlas con herramientas de análisis dinámico de código como Valgrind y Google Sanitizers.

## Evaluación
[10%] Buen uso de los commits, estructura de archivos y directorios, ignorar archivos generados.

[10%] Análisis (README.md): descripción del problema, el manual de usuario, créditos.

[15%] Diseño de la solución: diagrama de UML, pseudocódigo.

[10%] Documentación de subrutinas y registros y algoritmos en los cuerpos de subrutinas.

[35%] Implementación y corrección de los algoritmos y estructuras de datos (Que las salidas generadas tengan sentido y muestren correctitud).

[10%] Buen uso de la memoria (memcheck, asan, msan). 

[10%] Modularización en subrutinas y archivos (.h, .c). Apego a una convención de estilos (cpplint).
