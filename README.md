# PRÁCTICA DE PRO2 FIB: Simulación del rendimiento de procesadores interconectados

### Lista de comandos

- `configurar_cluster`: lee los procesadores del clúster, sus conexiones y la memoria de cada uno de ellos. Si ya existía un clúster anterior, este deja de existir. Se garantiza que los identificadores de los procesadores no están repetidos. El comando admite la forma abreviada cc.
  
  Esta funcionalidad se ha de aprovechar para la inicialización del primer clúster.

- `modificar_cluster`: lee un identificador p de un procesador del clúster y un
   nuevo clúster. Si p no existe, o tiene procesos en ejecución, o tiene procesadores auxiliares, se imprime un mensaje de error. En caso contrario, el nuevo cluster se
   coloca en el lugar de p, haciendo crecer así el cluster original (si p era auxiliar de otro procesador, la raíz del nuevo cluster pasa a ser el correspondiente auxiliar de dicho procesador). Se garantiza que no habrá repetición de identificadores en el
   cluster modificado resultante. El comando admite la forma abreviada `mc`.

- `alta_prioridad`: lee un identificador de prioridad. Si ya existe en el área de espera una prioridad con el mismo identificador, se imprime un mensaje de error. En
   caso contrario se añade esta prioridad al área de espera, sin procesos pendientes.
   El comando admite la forma abreviada `ap`.

- `baja_prioridad`: lee un identificador de prioridad. Si no existe en el área de
   espera una prioridad con el mismo identificador o si tiene procesos pendientes, se
   imprime un mensaje de error. En caso contrario se elimina esta prioridad del área
   de espera. El comando admite la forma abreviada `bp`.

- `alta_proceso_espera`: lee los datos de un proceso y un identificador de prioridad. Si no existe la prioridad en el área de espera o si ya había un proceso con ese identificador y esa prioridad, se imprime un mensaje de error. En caso contrario el proceso pasa al área de espera con dicha prioridad. El comando admite la forma abreviada `ape`.
  
- `alta_proceso_procesador`: lee el identificador de un procesador y los datos
   de un proceso. Si no existe el procesador en el clúster o ya contiene un proceso
   con el mismo identificador o el proceso no se puede colocar en el procesador, se
   imprime un mensaje de error. En caso contrario, el proceso pasa a ejecutarse en
   dicho procesador y la memoria que usa pasa a estar ocupada. El proceso se coloca
   en la posición más pequeña que deje el hueco más ajustado, tal como se explica
   más arriba. El comando admite la forma abreviada `app`.

- `baja_proceso_procesador`: lee el identificador de un procesador y de un proceso. Si no existe el procesador o el proceso no está en el procesador, se imprime
   un mensaje de error. En caso contrario se elimina el proceso del procesador. El
   comando admite la forma abreviada `bpp`.
   
- `enviar_procesos_cluster`: lee un entero no negativo n y se intentan enviar al
   clúster n procesos pendientes. El comando admite la forma abreviada epc.
   Los procesos se intentan colocar en el clúster por orden de prioridad. Dentro de
   una misma prioridad, se intentan colocar primero los procesos más antiguos. Los
   intentos continúan hasta haber colocado n procesos en el clúster o hasta que no
   queden procesos pendientes o hasta que todos los que queden pendientes se hayan
   intentado colocar sin éxito.

    a) Si un proceso no se ha podido colocar, no tiene sentido volver a intentar enviarlo al clúster en la misma operación porque, dado que en ella no se libera memoria, seguirá sin caber en ningún procesador. Entonces se considera que ha sido rechazado por el clúster. Los procesos rechazados por el clúster vuelven al área de espera como si fueran nuevos, con la misma prioridad.

    b) Si un proceso se puede colocar en más de un procesador, se elige el que disponga de un hueco más ajustado respecto a tal proceso. En caso de empate entre varios procesadores, se designa el que quede con más memoria libre. Si persiste el empate, se escoge el más cercano a la raíz del árbol de procesadores y si todavía es necesario desempatar, el de más a la izquierda.

- `avanzar_tiempo`: lee un entero positivo t que indica las unidades de tiempo que
   han transcurrido desde la última vez que se avanzó el tiempo (o desde el momento
   inicial, si es la primera vez que se aplica). Se eliminan todos los procesos activos que hayan acabado en ese intervalo de tiempo. La ejecución de todos los procesos de todos los procesadores han progresado t unidades de tiempo. El comando
   admite la forma abreviada `at`.

- `imprimir_prioridad`: lee un identificador de prioridad. Si no existe una prioridad con el mismo identificador en el área de espera se imprime un mensaje de error. En caso contrario, se escriben los procesos pendientes de dicha prioridad por orden decreciente de antigüedad, desde su última alta. Además, escribe el número de procesos de la prioridad colocados en el clúster por la operación ``enviar_procesos_a_cluster`` y el número de rechazos (un mismo proceso cuenta tantas veces como rechazos haya sufrido). El comando admite la forma abreviada `ipri`.

- `imprimir_area_espera`: Escribe los procesos pendientes de todas la prioridades del área de espera por orden creciente de prioridad. Para cada prioridad se escribe lo mismo que en la funcionalidad anterior. El comando admite la forma
   abreviada iae.

- `imprimir_procesador`: lee el identificador de un procesador. Si no existe un
   procesador con el mismo identificador en el clúster se imprime un mensaje de
   error. En caso contrario, se escriben los procesos de dicho procesador por orden
   creciente de primera posición de memoria, incluyendo dicha posición y el resto de
   datos de cada proceso. El tiempo que se escribe es el tiempo que falta para que
   el proceso acabe, no el tiempo inicial de ejecución. El comando admite la forma
   abreviada `ipro`.

- `imprimir_procesadores_cluster`. Escribe todos los procesadores del clúster
   por orden creciente de identificador. Para cada procesador se escribe lo mismo que
   en la funcionalidad anterior. El comando admite la forma abreviada `ipc`.

- `imprimir_estructura_cluster`. Escribe la estructura de procesadores del clúster. El comando admite la forma abreviada `iec`.
  
- `compactar_memoria_procesador`: lee el identificador de un procesador. Si no
   existe un procesador con el mismo identificador en el clúster se imprime un mensaje de error. En caso contrario, se mueven todos los procesos hacia el principio de la memoria del procesador, sin dejar huecos, sin solaparse y respetando el orden inicial. El comando admite la forma abreviada `cmp`.

- `compactar_memoria_cluster`: en cada procesador, se mueven todos los procesos hacia el principio de la memoria, sin dejar huecos, sin solaparse y respetando el orden inicial. El comando admite la forma abreviada `cmc`.
  
- `fin`

La única operación que modifica el tiempo es `avanzar_tiempo`. Se considera que
cada una de las restantes operaciones se ejecuta en el instante de tiempo definido por la ejecución más reciente de `avanzar_tiempo` (o en el instante 0, si aún no se ha ejecutado ninguna vez).
