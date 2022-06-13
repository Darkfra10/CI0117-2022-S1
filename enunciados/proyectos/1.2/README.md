# Proyecto01: [tetris_player]. Entrega #2

Entregar a más tardar el Sábado 2 de Julio a las 23:59. Las entregas tardías se tratarán como se estipula en la carta al estudiante.

## Repositorio y archivos

Los cambios en el código para esta segunda entrega se deben realizar sobre la misma carpeta del avance 01 del repositorio de control de versiones. Si una corrección de la entrega 1 interfiere con un requerimiento de la entrega 2, se deben aplicar los cambios correspondientes para lograr esta segunda entrega.

Los lineamientos sobre el trabajo en el repositorio y entrega de archivos estipulados en el avance 1, se aplican para esta entrega. Esto incluye igual participación de los miembros del equipo, políticas de commits y branches, estructura de archivos y carpetas, documentación, modularización, y estilo de código (cpplint).

## Análisis

En el [avance 1](https://github.com/jocan3/CI0117-2022-S1/tree/main/enunciados/proyectos/1.1) se construyó un jugador virtual del juego Tetris que determina jugadas, dado un **estado inicial**, utilizando un método de fuerza bruta y búsqueda en profundidad para encontrar la solución óptima. Esta solución llega a ser muy costosa cuando al jugador se le solicita una jugada que tome en cuenta muchas figuras de tetris (valor de profundidad alto).

En esta segunda entrega se creará una solución que haga mejor uso de los recursos de la máquina, al hacer concurrente la aplicación del jugador de Tetris. La aplicación deberá crear tantos **Solucionadores de Tetris** como CPUs hay disponibles en el sistema. Si el equipo de trabajo lo quiere, puede ofrecer un argumento de línea de comandos que controle esta cantidad de solucionadores, pero no es obligatorio.

Dado el estado inicial de Tetris, el programa deberá separar el problema en unidades de trabajo más pequeñas y los solucionadores deberán ir resolviendo cada unidad de trabajo y continuar con otra unidad conforme vayan termimando (mapeo dinámico). El número de unidades de trabajo estará determinado por la cantidad de columnas del tablero de juego multiplicado por la cantidad de posibles rotaciones de la figura del nivel 0. Por ejemplo, si el tablero tiene 30 columnas y la figura 0  es una L entonces su programa deberá crear 30 x 4 = 120 unidades de trabajo.  

El mapeo dinámico será implementado mediante el patrón Productor-Consumidor, el cual se detalla en las siguientes secciones de este enunciado.

## Diseño

En esta segunda entrega, se debe paralelizar su programa para que haga un uso equilibrado de los recursos de la máquina. Esta modificación consiste en hacer la aplicación concurrente utilizando el patrón Productor-Consumidor, de modo que un productor coloca unidades de trabajo (estados de Tetris) en una cola y cada consumidor utiliza un Solucionador de Tetris. Un consumidor toma una unidad de trabajo, inicia el solucionador y, una vez resuelto, vuelve a buscar otra unidad de trabajo en la cola, con el fin de equilibrar mejor la carga de trabajo entre los hilos de ejecución. El equipo de trabajo debe actualizar su diseño para que cumpla con estos requerimientos.

El siguiente diagrama muestra un ejemplo de diseño a muy alto nivel de la entrega #1 junto a los nuevos cambios requeridos para la entrega #2. Su diagrama debe contener más detalles y mostrar componentes específicos de la implementación realizada por su grupo de trabajo.

![figures](http://jocan3.com/misc_images/tetris_prod_cons_diagram.png)

El diseño debe contemplar cómo se comunican los hilos entre sí.

El hilo principal debe continuar ejecutando la lógica del *File watcher*, extrayendo los valores del estado inicial de Tetris.

Cada vez que se obtiene un estado inicial de Tetris, el programa separa dicho estado en unidades de trabajo. Cada unidad de trabajo representa un nuevo estado de Tetris generado luego de colocar la primera figura en una columna y rotación diferente. Por ejemplo, en la siguiente figura se muestra una representación de cuáles serían las 20 unidades de trabajo (estados de Tetris) diferentes generados a partir de un estado inicial en un tablero de 10 columnas y cuya primera figura (nivel 0) es una I.

![figures](http://jocan3.com/misc_images/tetris_work_units.png)

El solucionador de Tetris (*Tetris solver*) se mantendrá igual que en la entrega 1, siendo una clase que resuelve de manera serial, utilizando fuerza bruta y búsqueda en profundidad, un estado de Tetris.

Un hilo *productor* recibe las unidades de trabajo y las coloca en una cola de trabajo.

Varios hilos *consumidores* obtienen unidades de trabajo y las resuelven utilizando un solucionador de Tetris.

El diseño debe reflejar el recorrido de los datos a lo largo de la ejecución. Ustedes deciden la manera en la que manejan y combinan los resultados obtenidos en cada unidad de trabajo. Por ejemplo, una buena solución podría incluir un hilo adicional que se encargue recopilar los resultados de los demás, hacer las comparaciones y mandar a escribir los archivos de salida, de forma que el hilo principal (File watcher) no tenga que esperar a que la solución esté lista para leer otro archivo.

El diseño concurrente consta del flujo de datos, diagramas de clase UML, y pseudocódigo. El pseudocódigo sirve para detallar las acciones que se realizan en la creación, producción, y consumo a lo largo de la cadena de producción.

## Implementación

Se debe aplicar el diseño del programa concurrente aplicando los patrones sugeridos (productor-consumidor) al código solución en C++. La implementación de la solución debe apegarse al diseño elaborado por el equipo en la sección anterior. Se verificará que haya una correspondencia entre los elementos del diseño y los elementos de la implementación durante la revisión.

Su solución debe resolver cada estado inicial de Tetris correctamente. Es decir, debe generar los mismos archivos de salida que generaría la versión serial de la entrega 1. Además, debe validar entradas: Números o valores mal formados, o entradas mal intencionadas son reportados con mensajes de error, en lugar de caerse o producir resultados incorrectos.

Debe implementar algún mecanismo para finalizar el programa sin tener que hacerlo con Ctrl-C o con el comando kill. Haga que el programa termine cuando el *File watcher* lea un archivo con el nombre *tetris_end.txt*. Al recibir un archivo con este nombre, el programa debe terminar la ejecución. En cado de que haya hilos ejecutándose al recibir el archivo de terminación, el programa debe terminarlos correctamente.

Utilice el código */prodcons* y el archivo *Makefile* incluidos en este enunciado para facilitar la implementación de esta entrega. Noten que estas interfaces implementan una clase *Thread* que internamente hace uso de la biblioteca *std::thread* de C++. Por lo tanto, cualquier instancia de las clases *Producer* y *Consumer* puede ser ejecutada como un hilo. 

En el folder */prodcons* también se incluye una implementación de una clase *Queue* que representa una cola, la cual es *thread-safe* al utilizar internamente un mecanismo de control de concurrencia definido en la clase *Semaphore*. Por lo tanto, su equipo de trabajo no debe preocuparse por problemas de concurencia mientras haga los llamados a los métodos públicos de estas interfaces.

Se incluyen además otras interfaces, como el *Assembler* y el *Dispatcher*, que pueden ser utilizadas para mejorar la implementación pero no es requerido utilizarlas. Por ejemplos, los hilos consumidores pueden implementarse como ensambladores (*assemblers*) que leen unidades de trabajo de una cola, resuelven el problema, y colocan los resultados en otra cola, donde finalmente un hilo consumidor se encarga únicamentre de leer resultados, compararlos y escribir resultados.

Es responsabilidad de su equipo de trabajo el analizar y entender dicho código para adarparlo a su solución. Durante las clases también se proveerán ejemplos sobre cómo utilizar las principales interfaces.

## Pruebas

Refiérase a la sección *Pruebas* del enunciado de la [entrega #1](https://github.com/jocan3/CI0117-2022-S1/tree/main/enunciados/proyectos/1.1). Los mismos criterios aplican para esta entrega, incluyendo el uso de la interfaz gráfica para asegurarse de que su jugador de Tetris funciona correctamente.

## Evaluación

[5%] Buen uso y aporte equilibrado del repositorio (commits, ignores) y directorios.

[25%] Diseño concurrente: documento de diseño, flujo de datos, clases en UML, pseudocódigo.

[25%] Implementación del patrón Productor-Consumidor en su programa C++ de la primera entrega. Comunicación entre los hilos.

[20%] Implementa tantos consumidores como CPUs hay disponibles en el sistema. Descomposición en unidades de trabajo. Trazabilidad de las soluciones de Tetris.

[10%] Finalización correcta del programa. Buen uso de la memoria y de la concurrencia (Sanitizers y Valgrind).

[5%] Pruebas y documento de análisis (readme.ext).

[5%] Modularización en subrutinas y archivos (.hpp, .cpp). Apego a una convención de estilos (cpplint).

[5%] Documentación de interfaces e implementaciones (algoritmos).

Recuerde que en todos los rubros se evalúan las buenas prácticas de programación.
