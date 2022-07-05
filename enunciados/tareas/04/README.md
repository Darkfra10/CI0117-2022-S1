# Tarea04: [tetris_solver_mpi]

Tarea estrictamente individual. Fecha límite de entrega: Martes 26 de Julio a las 23:59. Se entrega en su repositorio personal.

En las tareas anteriores usted escribió programas que determinan la jugada óptima de un estado de juego de Tetris de forma serial (tarea01), concurrente con Pthreads (tarea02) y con OpenMP (tarea03), además de realizar comparaciones de rendimiento. Estas soluciones aprovechan los recursos concurrentes de una máquina, pero no escalan, ni aprovechan varias computadoras disponibles o un clúster de computadoras.

En esta tarea su objetivo es distribuir el trabajo del solucionador entre varias máquinas usando la tecnología MPI. Su programa recibirá las entradas en el mismo formato, y deberá producir los mismos resultados que en las tareas anteriores.

## Correcciones a la tarea03

Luego de haber recibido observaciones durante la revisión de la tarea03, corrija su solución en la carpeta *tareas/tetris_solver_omp/*. Se sugiere utilizar *issues* de su sistema de control de versiones de la siguiente forma:

1. Por cada observación que reciba durante la revisión, cree un issue en el sistema de alojamiento de control de versiones (github). Inicie el título del issue con el número de la tarea, por ejemplo "Tarea03: cambiar arreglo estático por dinámico". Describa en el issue el problema identificado puntualmente. Note que cada issue recibe un número que lo identifica.

2. Corrija un issue a la vez en su repositorio. Para cada corrección cree un commit y en el mensaje refiera el número del issue.

Una vez que haya corregido la tarea03, pase a la versión distribuida con MPI (tarea04).

## Descripción del problema (tarea04)

En su repositorio personal cree un folder *tareas/tetris_solver_mpi*. Para hacer su solución escalable y aprovechar un clúster de computadoras, distribuya el trabajo del solucionador de Tetris utilizando la tecnología MPI. Tome en cuenta que su programa toma los valores de entrada de archivos de texto, por lo tanto es válido que todos los procesos lean el mismo archivo para que cada uno pueda tener su copia del estado inicial de Tetris (no debería haber problema dado que sólamente están leyendo el archivo y no escribiendo en él). Sin embargo, asegúrese de que sea un único proceso el que genere los archivos salida.

Descomponga las unidades de trabajo a distribuir y se recomienda continuar utilizando la tecnología OpenMP, de forma que el trabajo se divida entre varios procesos y éstos a su vez puedan dividir su trabajo entre varios hilos.

Para repartir el trabajo entre diferenes procesos, implemente cualquiera de los mecanismos de mapeo vistos en clase (bloque, cíclico o dinámico), de tal forma que los recursos del clúster se aprovechen lo más equitativamente posible. Agregue al README.md de la tarea una breve explicación refiriéndose al tipo de mapeo utilizado y cómo se da la comunicación entre los procesos (puede agregar algún diagrama de componentes o de flujo de datos).

Un enfoque que podría seguirse es, por ejemplo, distribuir el nivel de profundidad 0 entre varios procesos. Cada proceso, a su vez, divide el trabajo en el nivel 1 de profundidad que le corresponde entre varios hilos. Ustedes deciden el comportamiento y la implementación con respecto al mapeo y para el caso en el que la profundidad solicitada sea igual a 0.

Asegúrese de que su solución distribuida con MPI mantenga la misma funcionalidad de las tareas anteriores utilizando distintas cantidades de procesos e hilos. Además su implementación no debe generar diagnósticos del linter.

## Pruebas

Asegúrese de verificar el funcionamiento de su programa con diferentes casos de prueba. Se recomienda enfáticamente crear varios casos de prueba dentro del folder *test* de su solución. Además se debe probar el buen uso de memoria (asan, msan, ubsan, memcheck) y el un buen uso de la concurrencia (tsan). Dado que valgrind y los sanitizers pueden generar falsos positivos al utilizar algunas tecnologías y bibliotecas externas, agregue una sección al README.md de la tarea indicando los errores encontrados y justificando por qué son falsos positivos.

## Documento de reporte

Cree una carpeta *tareas/tetris_solver_mpi/report/* y dentro un archivo Readme.md. A este archivo se le referirá como documento de reporte. Conviene crear un enlace desde *tareas/tetris_solver_mpi/README.md* a su documento de reporte para que facilite la navegación.

Compare el rendimiento de su solución distribuida con el caso de prueba que usó en la tarea03. En este caso, es necesario usar un ambiente distribuido, para el cual utilizaremos el Clúster Kabre (Solicite al profesor una cuenta de acceso y refiérase al [manual de usuario del clúster](https://kabre.cenat.ac.cr/guia-usuario/) para más información, además de las explicaciones dadas en clase sobre cómo usarlo). Se adjunta un ejemplo del archivo .slurm para enviar solicitudes de trabajo en el clúster utilizando MPI. Utilice al menos 4 nodos del Cluster y puede probar con diferentes cantidades de hilos (se recomienda utilizar entre 8 y 16).

Mida la duración de la versión distribuida, calcule el incremento de velocidad y la eficiencia respecto a la versión OpenMP (Debe volver a calcular la duración de la tarea03 en un nodo del clúster para garantizar las mismas condiciones). Agregue los resultados a una hoja de cálclo y genere gráfico, de tal forma que en el eje-x se pueda comparar la versión distribuida de MPI con las versión con OpenMP. Agregue estas mediciones a su documento de reporte y una breve discusión o análisis sobre los resultados obtenidos.

## Evaluación

[40%] Distribución y concurrencia declarativa: Implementación y corrección. Pasar los casos de prueba y obtener incremento de desempeño respecto de la versión no distribuida.

[15%] Mapeo: Implementación de la división de carga de trabajo usando paso de mensajes y la respectiva documentación en el README de la tarea.

[25%] Comparación OpenMP-MPI: Hoja de cálculo con las mediciones, incrementos de velocidad, eficiencia, y gráfico combinado. Coherencia de la discusión de resultados y el correspondiene gráfico en el documento de reporte.

[10%] Documentación de interfaces (doxygen) e implementaciones (algoritmos).

[10%] Apego a una convención de estilos (cpplint). Modularización en subrutinas y archivos (.h, .c). Buen uso del repositorio (commits, ignores, tags) y directorios, como se ha indicado en tareas anteriores.

Recuerde que en todos los rubros se evalúan las buenas prácticas de programación. En todos los rubros que generan documentación se evalúa el buen uso de la comunicación escrita, tal como lo estipula la carta al estudiante.
