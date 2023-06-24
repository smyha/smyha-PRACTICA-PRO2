/** @mainpage Diseño modular: Simulación del rendimiento de procesadores interconectados - Sergio Shmyhelskyy Yaskevych
 * 
 *  En esta práctica se diseña un programa modular que ofrece un menú de comandos para simular un el funcionamiento de una arquitectura multiprocesador.
 *  De acuerdo con la información proporcionada por el enunciado, se ha presentado la implementación de exactamente 4 clases:
 *  <ul>
 *      <li>Cluster.hh</li>
 *      <li>Area_Espera.hh</li>
 *      <li>Procesador.hh</li>
 *      <li>Proceso.hh</li>
 *  </ul>
 *  El programa principal se encuentra en el módulo <em>program.cc</em>.
*/

/** @file program.cc
 *  @brief Programa principal para la práctica de PRO2: <em>Simulación del rendimiento de procesadores interconectados</em>.
 * 
 *  El enunciado de la práctica da a entender que los datos a leer son sintácticamente correctos, por tanto no se realizarán comprobaciones al respecto.
 *  No obstante, algunas funcionalidades tendrán restricciones en relación a los datos, con la finalidad de simplificar la ejecución.
 *  Para el acceder a los controles del programa, usaremos los comandos previamente especificados por el postulado de la praxis.
*/

#include "Cluster.hh"
#include "Area_Espera.hh"

#ifndef NO_DIAGRAM  // No aparece en el diagrama
#include <iostream>
using namespace std;
#endif

int main(){

    Cluster clu;
    Area_Espera esp;

    clu.configurar_cluster();
    esp.configurar_area_espera();

    string cm;
	cin >> cm;
	while (cm != "fin") {
        string p;
        string prior;        
        cout << '#' << cm;
        // 1
		if (cm == "configurar_cluster" or cm == "cc") {
            cout << endl;
            clu.configurar_cluster();
		}
        // 2
		else if (cm == "modificar_cluster" or cm == "mc") {
            cin >> p;
            cout << ' ' << p << endl;

            // Lee el nuevo clúster a acoplar al clúster principal.
            Cluster clu_comp;
            clu_comp.configurar_cluster();

            int caso = clu.modificar_cluster(p, clu_comp);
            // Si el procesador no existe en el clúster principal, imprime mensaje de error
            if (caso == 1) cout << "error: no existe procesador" << endl;
            // Si el procesador tiene procesos pendientes de acabar en memoria, imprime mensaje de error
            if (caso == 2) cout << "error: procesador con procesos" << endl;
            // Si el procesador tiene procesadores auxiliares, imprime mensaje de error
            if (caso == 3) cout << "error: procesador con auxiliares" << endl;

        }
        // 3
		else if (cm == "alta_prioridad" or cm == "ap"){
            cin >> prior;
            cout << ' ' << prior << endl;

            int caso1 = esp.alta_prioridad(prior);
            // Si ya existe en el área de espera una prioridad con el mismo identificador,imprime mensaje de error
            if (caso1 == 1) cout << "error: ya existe prioridad" << endl;                   
        }
        // 4
		else if (cm == "baja_prioridad" or cm == "bp"){  
            cin >> prior;
            cout << ' ' << prior << endl;
            
            int caso2 = esp.baja_prioridad(prior);
            // Si no existe la prioridad en el área de espera., imprime mensaje de error
            if (caso2 == 1) cout << "error: no existe prioridad" << endl;
            // Si ya había un proceso/s con ese identificador en esa prioridad, imprime mensaje de error
            if (caso2 == 2) cout << "error: prioridad con procesos" << endl;
        }
        // 5
        else if (cm == "alta_proceso_espera" or cm == "ape") {
            cin >> prior;

            Proceso proceso;
            proceso.lectura_proceso();

            cout << ' ' << prior << ' ' << proceso.consultar_identificador_proceso() << endl;
            
            int caso3 = esp.alta_proceso_espera(proceso, prior);
            // Si la prioridad no existe, imprimir mensaje de error
            if (caso3 == 1) cout << "error: no existe prioridad" << endl;
            // Si el proceso ya existe, imprimir mensaje de error
            if (caso3 == 2) cout << "error: ya existe proceso" << endl;
        }
        // 6
 		else if (cm == "alta_proceso_procesador" or cm == "app") {
            cin >> p;
            // Lee el proceso a dar de alta en el procesador indicado por 'p'
            Proceso proceso;
            proceso.lectura_proceso();

            cout << ' ' << p << ' ' << proceso.consultar_identificador_proceso() << endl;
            
            int caso1 = clu.alta_proceso_procesador(proceso, p); 
            // Si no existe el procesador en el clúster, imprime mensaje de error
            if (caso1 == 1) cout << "error: no existe procesador" << endl;
            // Si no existe un proceso con el mismo identificador, imprime mensaje de error
            if (caso1 == 2) cout << "error: ya existe proceso" << endl;
            // Si no cabe el proceso en el procesador, imprime mensaje de error
            if (caso1 == 3) cout << "error: no cabe proceso" << endl;

        }
        // 7
		else if (cm == "baja_proceso_procesador" or cm == "bpp") {
            cin >> p;
            int idn_proceso;
            cin >> idn_proceso;

            cout << ' ' << p << ' ' << idn_proceso << endl;
            
            int caso2 = clu.baja_proceso_procesador(p, idn_proceso);
            // Si no existe el procesador en el clúster, imprime mensaje de error
            if (caso2 == 1) cout << "error: no existe procesador" << endl;
            // Si no existe un proceso con el mismo identificador, imprime mensaje de error
            if (caso2 == 2) cout << "error: no existe proceso" << endl;
        }
        // 8
		else if (cm == "enviar_procesos_cluster" or cm == "epc") {
            int n;      
            cin >> n;

            cout << ' ' << n << endl;
            // Se envian n procesos, por orden de las prioridades del área de espera
            esp.enviar_procesos_cluster(clu, n); 
        }
        // 9
		else if (cm == "avanzar_tiempo" or cm == "at") {
            int t;      // t > 0
            cin >> t;

            cout << ' ' << t << endl;
            // Recorre todos los procesadores y restaura aquellos que han acabado su proceso
            clu.avanzar_tiempo(t);                                  
        }
        // 10
		else if (cm == "imprimir_prioridad" or cm == "ipri"){
            cin >> prior;

            cout << ' ' << prior << endl;
            // Si la prioridad no existe en el área de espera, imprime mensaje de error
            if (not esp.imprimir_prioridad(prior)) cout << "error: no existe prioridad" << endl;
            
        }
        // 11
		else if (cm == "imprimir_area_espera" or cm == "iae") {
            cout << endl;
            esp.imprimir_area_espera();
        }
        // 12
		else if (cm == "imprimir_procesador" or cm == "ipro") {
            cin >> p;
            cout << ' ' << p << endl;
            // Si no existe el procesador en el clúster, imprime mensaje de error
            if (not clu.imprimir_procesador(p)) cout << "error: no existe procesador" << endl;
        }
        // 13
		else if (cm == "imprimir_procesadores_cluster" or cm == "ipc"){
            cout << endl;
            clu.imprimir_procesadores_cluster();
        }
        // 14
		else if (cm == "imprimir_estructura_cluster" or cm == "iec"){
            cout << endl;
            clu.imprimir_estructura_cluster();
        }
        // 15
		else if (cm == "compactar_memoria_procesador" or cm == "cmp") {
            cin >> p;
            
            cout << ' ' << p << endl;
            // Si no existe el procesador en el clúster, imprime mensaje de error
            if (not clu.compactar_memoria_procesador(p)) cout << "error: no existe procesador" << endl;
        }
        // 16
		else if (cm == "compactar_memoria_cluster" or cm == "cmc"){
            cout << endl;
            clu.compactar_memoria_cluster();
        }    
		cin >> cm;
    }
}