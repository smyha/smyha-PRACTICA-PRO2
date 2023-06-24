# Se declaran los 'warning' de compilación del compilador g++, para evitar problemas de ejecución del programa.
OPCIONES = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++11

program.exe: program.o Proceso.o Procesador.o  Cluster.o Area_Espera.o
	g++ -o program.exe *.o $(OPCIONES)

Proceso.o: Proceso.cc Proceso.hh
	g++ -c Proceso.cc $(OPCIONES)

Procesador.o: Procesador.cc Procesador.hh Proceso.hh
	g++ -c Procesador.cc $(OPCIONES)

Cluster.o: Cluster.cc Cluster.hh Procesador.hh BinTree.hh
	g++ -c Cluster.cc $(OPCIONES)

Area_Espera.o : Area_Espera.cc Area_Espera.hh Cluster.hh Proceso.hh
	g++ -c Area_Espera.cc $(OPCIONES)

program.o: program.cc Cluster.hh Area_Espera.hh
	g++ -c program.cc $(OPCIONES)

practica.tar: *.hh *.cc Makefile
	tar -cvf practica.tar *.hh *.cc *.zip Makefile

# Elimina todos los ficheros .o y .exe con el comando 'make clean'.
clean:
	rm *.o
	rm *.exe
	rm *.tar

# Realiza una prueba al programa con el sample.inp, se ejecuta con 'make test'.
test:
	./program.exe <sample.inp> sample.out
	kompare sample.out sample.cor