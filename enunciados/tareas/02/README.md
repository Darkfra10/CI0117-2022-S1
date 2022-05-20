# Tarea02: [tetris_solver_pthreads]

Tarea estrictamente individual. Fecha límite de entrega: sábado 28 de mayo a las 23:59. Se entrega en su repositorio personal.

Esta tarea es una secuencia de la tarea01 y debe apegarse a las reglas de entrega de la tarea01, a excepción de los cambios solicitados en este enunciado. En particular, se mantienen las siguientes secciones de la tarea01:

* Descripción del problema
* Entregables
* Análisis
* Documentación

Para esta tarea paralelice su programa en C usando Pthreads para que la búsqueda del mejor puntaje dado un estado de Tetris se haga de forma concurrente.

## Correcciones a la tarea01

Luego de haber recibido observaciones durante la revisión de la tarea01, corrija su solución en la carpeta *tareas/tetris_solver_serial/* , de manera que no se propaguen las deficiencias identificadas de la tarea01 en la tarea02. Se sugiere utilizar *issues* de su sistema de control de versiones de la siguiente forma:

1. Por cada observación que reciba durante la revisión, cree un issue en el sistema de alojamiento de control de versiones (github). Inicie el título del issue con el número de la tarea, por ejemplo "Tarea01: cambiar arreglo estático por dinámico". Describa en el issue el problema identificado puntualmente. Note que cada issue recibe un número que lo identifica.

2. Corrija un issue a la vez en su repositorio. Para cada corrección cree un commit y en el mensaje refiera el número del issue.

Una vez que haya corregido la tarea01, pase a la versión concurrente (tarea02).

## Descripción del problema (tarea02)
En su repositorio personal copie la carpeta tareas/tetris_solver_serial/ y su contenido como tareas/tetris_solver_pthreads. Haga un commit con este cambio.

El programa concurrente recibirá el mismo formato de archivo de entrada y deberá genrar los archivos de salida de la misma forma que la versión serial lo hace. Es decir, para un archivo de entrada dado, su programa concurrente debe generar exactamente las mismas salidas que la versión serial. La diferencia con la versión serial, es que la solución a esta tarea debe realizar la búsqueda del mejor puntaje de manera concurrente utilizando hilos que se reparten el trabajo, y por lo tanto, debe tener un incremento en el desempeño corroborable.

Su programa concurrente debe permitir al usuario invocarlo con un número provisto como argumento de línea de comandos, el cual indica la cantidad de hilos de ejecución que se repartirán el trabajo. Si este número no se provee, se debe asumir la cantidad de núcleos (CPUs) disponibles en la máquina. Recuerde actualizar su README.md para indicar que su solución usa hilos, y que el usuario puede proveer este parámetro opcional.

## Diseño concurrente
Al disponer de varios hilos de ejecución, debe repartir el trabajo lo más equitativamente posible entre ellos. Haga que los hilos se repartan el trabajo utilizando **mapeo por bloque o mapeo cíclico únicamente**. No utilice mapeo dinámico para esta tarea.

Su solución debe tener un buen diseño concurrente expresado en diagramas y pseudocódigo:

* Resalte en su diagrama las estrucuas de datos y cómo se hace la repartición del trabajo a cada hilo de ejecución.
* El diseño en pseudocódigo debe centrarse en la lógica concurrente (lo nuevo en esta tarea) y no los detalles del algorítmo de la tarea01. Debe usar la misma notación de pseudocódigo que se ha usado en las lecciones del curso para representar creación de hilos y subrutinas. Su pseudocódigo debe considerar la creación de estructuras de datos, lectura de la entrada, creación de hilos y escritura de salidas. 

## Implementación concurrente
Implemente su diseño concurrente en el lenguaje de programación C con la tecnología Pthreads. Recuerde aplicar buenas prácticas de programación, estilo de código (linter), y documentar las subrutinas.

En esta versión NO haga optimizaciones al código de la tarea01. La versión concurrente debe implementar el mismo algoritmo que la versión serial. Simplemente debe repartir el trabajo lo más equitativamente posible entre los hilos de ejecución utilizando **mapeo por bloque o mapeo cíclico**.

La versión concurrente debe registrar un incremento de velocidad. Es decir, la duración de la versión concurrente cuando la profundidad de entrada es grande, debe ser menor o igual que la duración de la versión serial.

## Pruebas
Asegúrese de verificar el funcionamiento de su programa con diferentes casos de prueba. Se recomienda enfáticamente crear más casos de prueba que prueben diferentes estados y valores de profundidad altos (profundidades mayores a 6).

Además de probar el buen uso de memoria (asan, msan, ubsan, memcheck), asegúrese de hacer un buen uso de la concurrencia (tsan). 

## Evaluación
[5%] Buen uso del repositorio (commits, ignores, tags) y directorios.

[5%] Análisis: agregar concurrencia al README.md.

[15%] Diseño de la solución concurrente: diagrama de memoria y pseudocódigo.

[5%] Documentación de implementaciones (algoritmos).

[30%] Implementación y funcionalidad de la concurrencia (obtener mismos resultados que su versión serial).

[10%] Buen uso de la memoria (memcheck, asan, msan, ubsan).

[10%] Buen uso de la concurrencia (tsan).

[10%] Incremento del desempeño con los casos de prueba para valores de profundidad grandes.

[10%] Modularización en subrutinas y archivos (.h, .c). Apego a una convención de estilos (cpplint).

Recuerde que en todos los rubros se evalúan las buenas prácticas de programación.
