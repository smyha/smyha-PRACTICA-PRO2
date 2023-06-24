Para usar el generador de inputs seguir las siguientes instrucciones.

1. Compilar efCode2023.cc con la siguiente instrucción:
    g++ -O2 -o exe efCode2023.cc
2. Ejecutar exe con el siguiente comando:
    ./exe > nombre_input_generado.txt
3. A continuación introducir 4 ints representado el número de procesadores, procesos, prioridades e instrucciones respectivamente.
   Se os habrá generado un fichero nombre_input_generado.txt con el input generado.
4. Para ejecutar el programa haced el siguiente comando, que os leerá el input desde un .txt y os generará el output en otro txt:
   ./vuestro_ejecutable < nombre_input.txt > nombre_output.txt
5. Para comparar vuestra solución con la de alguien más usad la siguiente instrucción:
   diff vuestro_output.txt solucion_output.txt

EXTRA. Si algún ejecutable no os funciona probad a ejecutar la siguiente instrucción y volved a probar a ejecutar:
    chmod 777 nombre_ejecutable
