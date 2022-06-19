# Tarea03: [tetris_solver_omp]

Tarea estrictamente individual. Fecha límite de entrega: Lunes 4 de Julio a las 23:59. Se entrega en su repositorio personal.

En las tareas anteriores usted escribió programas que determinan la jugada óptima de un estado de juego de Tetris de forma serial (tarea01) y concurrente con Pthreads (tarea02). En esta tarea su objetivo es evaluar una tecnología declarativa: OpenMP. Su programa recibirá las entradas en el mismo formato, y deberá producir los mismos resultados que en las tareas anteriores.

## Aspectos generales

Esta tarea es una secuencia de la [tarea01](https://github.com/jocan3/CI0117-2022-S1/tree/main/enunciados/tareas/01) y de la [tarea02](https://github.com/jocan3/CI0117-2022-S1/tree/main/enunciados/tareas/02) y debe apegarse a las reglas de dichas entregas, a excepción de los cambios solicitados en este enunciado. También se mantienen los lineamientos de las siguientes secciones de la [tarea01](https://github.com/jocan3/CI0117-2022-S1/tree/main/enunciados/tareas/01):

* Descripción del problema

* Entregables

* Análisis

* Documentación

## Correcciones a la tarea02

Luego de haber recibido observaciones durante la revisión de la tarea02, corrija su solución en la carpeta *tareas/tetris_solver_pthreads/*. Se sugiere utilizar *issues* de su sistema de control de versiones de la siguiente forma:

1. Por cada observación que reciba durante la revisión, cree un issue en el sistema de alojamiento de control de versiones (github). Inicie el título del issue con el número de la tarea, por ejemplo "Tarea02: cambiar arreglo estático por dinámico". Describa en el issue el problema identificado puntualmente. Note que cada issue recibe un número que lo identifica.

2. Corrija un issue a la vez en su repositorio. Para cada corrección cree un commit y en el mensaje refiera el número del issue.

Una vez que haya corregido la tarea02, pase a la versión de concurrencia con OpenMP (tarea03).

## Descripción del problema (tarea03)

En su repositorio personal cree un folder *tareas/tetris_solver_omp*. La solución a esta tarea debe ser trabajada en dicho folder y puede implementarlo en lenguage C (tomando como base el código de sus tareas anteriores) o en C++ (tomando como base el código realizado por su equipo de trabajo en el proyecto 1).

El programa recibirá el mismo formato de archivo de entrada y deberá genrar los archivos de salida de la misma forma que la versión con pthreads lo hace. Es decir, para un archivo de entrada dado, su programa de la tarea03 debe generar exactamente las mismas salidas que la tarea02. Sin embargo, para esta tarea se debe Utilizar la tecnología de paralelismo de datos OpenMP para paralelizar el trabajo de resolver el estado de un juego de Tetris.

Si toma como base el código de la tarea02, debe eliminar por completo las referencias a Pthreads, ya que en esta tarea se utilizará OpenMP únicamente. Puede hacer uso de cualquier directiva, constructo y función definida en el [manual de referencia de esta biblioteca](https://www.openmp.org/specifications/). Usted decide cuál tipo de *schedule* utilizar para su solución. 

Al igual que en la tarea02, haga que los hilos trabajen de forma lo más paralela posible, y por consiguiente, evitar control de concurrencia innecesario. Se recomienda evitar la serialización de los hilos.

Su programa debe permitir al usuario invocarlo con un número provisto como argumento de línea de comandos, el cual indica la cantidad de hilos de ejecución que se repartirán el trabajo. Si este número no se provee, se debe asumir la cantidad de núcleos (CPUs) disponibles en la máquina.

## Pruebas

Asegúrese de verificar el funcionamiento de su programa con diferentes casos de prueba. Se recomienda enfáticamente crear varios casos de prueba dentro del folder *test* de su solución. Además se debe probar el buen uso de memoria (asan, msan, ubsan, memcheck) y el un buen uso de la concurrencia (tsan). Dado que valgrind y los sanitizers pueden generar falsos positivos al utilizar OpenMP, agregue una sección al README.md de la tarea indicando los errores encontrados y justificando por qué son falsos positivos.

Recuerde que para generar un ejecutable con un sanitizer hay que (re)compilar todos los fuentes con el sanitizer. Si ya se tiene un ejecutable construido sin sanitizer o un sanitizer diferente, es mejor borrar (make clean) todos los archivos objeto viejos (.o) y recompilar de nuevo.

## Documento de reporte

Cree una carpeta tareas/tetris_solver_omp/report/ y dentro un archivo Readme.md. A este archivo se le referirá como documento de reporte. Conviene crear un enlace desde tareas/tetris_solver_omp/README.md a su documento de reporte para que facilite la navegación.

### Mediciones de tiempo de ejecución

Para todas las mediciones de rendimiento utilice el mismo archivo de entrada. Esta entrada debe ser lo suficientemente grande para que su programa tarde varios minutos (preferiblemente no más de 30 minutos). Usted debe crear este archivo de entrada, asegurándose de que sea válido y utilizando el número de columnas y valor de profundidad necesarios.

Debe ejecutar las pruebas en una máquina con al menos 4 núcleos. Si no dispone de un equipo con estas características, puede realizar las pruebas en un nodo del clúster Kabré (Solicite al profesor una cuenta de acceso y refiérase al [manual de usuario del clúster](https://kabre.cenat.ac.cr/guia-usuario/) para más información, además de las explicaciones dadas en clase sobre cómo usarlo).

Para medir el tiempo, modifique el código a utilizar para que registre e imprima en la salida estándar el tiempo de *CPU wall time* que tarda en ejecutarse un caso de prueba. Para medir el tiempo de las soluciones de la tarea01 y tarea02, refiérase a la subrutina *clock_gettime* utilizada en ejemplos durante la clase. Para la tarea03 puede hacer uso de la función *omp_get_wtime* de la biblioteca OpenMP.

### Comparación de optimizaciones

Una vez que tenga lista la solución a la tarea03 y que haya modificado el código de las tareas 01 y 02 para que registren el tiempo de ejecución como se mencionó en la sección anterior, realice comparaciones entre ellas con respecto al incremento de desempeño. Todas las mediciones deben realizarse en la misma máquina y con el mismo caso de prueba *grande*. Para cada solución realice 3 corridas y tome el valor de la corrida con menor duración.

Todas las mediciones deben realizarse con mínimo 4 hilos y máximo 8 (no exceder la cantidad de núcleos disponibles en la máquina), a excepción de la versión serial. Para todas las mediciones calcule el incremento de velocidad (*speedup*) con respecto a la versión serial, y la eficiencia. Refiérase a las explicaciones y ejemplos vistos en clase sobre estas métricas.

Lleve el control de estos valores en una hoja de cálculo y cree gráficos que muestren las duraciones y el incremento de velocidad en cada comparación. Incluya imágenes de estos gráficos en el documento de reporte, además de una breve discusión en la que explique los resultados obtenidos. Además suba esta hoja de cálculo a su repositorio.

### Comparación de grado de concurrencia

Realice otra comparación de sus programa utilizando diferentes grados de concurrencia (número de hilos). Para esta comparación utilice únicamente la solución de la tarea03. Al igual que la anterior, todas las mediciones deben realizarse en la misma máquina y con el mismo caso de prueba *grande*. Para cada una de las siguientes mediciones realice 3 corridas y tome el valor de la corrida con menor duración (serían 15 corridas):

* A. Usando un solo hilo (versión serial)
* B. Usando un número de hilos igual al número de CPUs en la máquina que ejecuta el programa (máximo 16 hilos)
* C. Usando un número de hilos igual a la mitad del número de CPUs en la máquina que ejecuta el programa (máximo 8 hilos)
* D. Usando dos hilos por cada CPU en la máquina que ejecuta el programa (máximo 32 hilos)
* E. Usando un número de hilos igual a la cantidad de columnas del tablero de juego multiplicado por el número de rotaciones de la primera figura basándose en el archivo de entrada.

Una vez que tenga todas las mediciones calcule el incremento de velocidad (*speedup*) de cada medición respecto a la versión con un solo hilo. Calcule también la eficiencia de cada medición.

De igual manera, lleve el control de estos valores en una hoja de cálculo y cree gráficos que muestren las duraciones y el incremento de velocidad en cada comparación. Incluya imágenes de estos gráficos en el documento de reporte, además de una breve discusión en la que explique los resultados obtenidos. Además suba esta hoja de cálculo a su repositorio.

## Evaluación

[40%] Implementación de la concurrencia declarativa (OpenMP): Implementación y corrección. Pasar los casos de prueba y obtiene incremento de desempeño respecto de su versión serial.

[10%] Documentación en el reporte que incluye: diseño de las soluciones (tarea01, tarea02 y tarea03) y valores de speedup/eficiencia.

[15%] Comparación de optimizaciones: Hoja de cálculo con las mediciones, incrementos de velocidad, eficiencia, y gráficos combinados. Discusión de resultados y gráficos en el documento de reporte.

[15%] Comparación de grado de concurrencia: Hoja de cálculo con las mediciones, incrementos de velocidad, eficiencia, y gráficos combinados. Discusión de resultados y gráficos en el documento de reporte.

[10%] Buen uso de la memoria (memcheck, asan, msan, ubsan) y la concurrencia (tsan).

[5%] Documentación de interfaces e implementaciones (algoritmos).

[5%] Apego a una convención de estilos (cpplint). Modularización en subrutinas y archivos. Buen uso del repositorio (commits, ignores, tags) y directorios, como se ha indicado en tareas anteriores.

Recuerde que en todos los rubros se evalúan las buenas prácticas de programación. En todos los rubros que generan documentación se evalúa el buen uso de la comunicación escrita, tal como lo estipula la carta al estudiante.
