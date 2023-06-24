#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <map>
#include <set>

using namespace std;




/* PROCESADOR
 * - identificador: string
 * - memoria
 * - [procesos]
*/

/*
 * PROCESO
 * - identificador: int > 0
 * - tiempo
 * - memoria
*/

/*
 * PRIORIDAD
 * - identificador: string
 * - procesadores
*/

void escribir_bintree(const vector<string>& v, vector<string>& procesadores) {
  int x = rand() % 500 + 3;

  set<string> s;
  int max_mem_size = 20;
  if (x%8 == 0) {
    while (s.size() < 5) s.insert(v[rand() % v.size()]);
    set<string>::iterator it = s.begin();
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
  }
  else if (x%8 == 1) {
    while (s.size() < 3) s.insert(v[rand() % v.size()]);
    set<string>::iterator it = s.begin();
    cout << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
  }
  else if (x%8 == 2) {
    while (s.size() < 6) s.insert(v[rand() % v.size()]);
    set<string>::iterator it = s.begin();
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
  }
  else if (x%8 == 3) {
    while (s.size() < 8) s.insert(v[rand() % v.size()]);
    set<string>::iterator it = s.begin();
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << '*' << endl;
  }
  else if (x%8 == 4) {
    while (s.size() < 4) s.insert(v[rand() % v.size()]);
    set<string>::iterator it = s.begin();
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << '*' << endl;
  }
  else if (x%8 == 5) {
    while (s.size() < 5) s.insert(v[rand() % v.size()]);
    set<string>::iterator it = s.begin();
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << '*' << endl;
  }
  else if (x%8 == 6) {
    while (s.size() < 4) s.insert(v[rand() % v.size()]);
    set<string>::iterator it = s.begin();
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
  }
  else if (x%8 == 7) {
    while (s.size() < 8) s.insert(v[rand() % v.size()]);
    set<string>::iterator it = s.begin();
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
    cout << *it << endl << int(rand() % max_mem_size + 1) << endl; ++it;
    cout << '*' << endl;
    cout << '*' << endl;
  }
}


int main() {
    int n_procesadores; cin >> n_procesadores;
    int n_procesos; cin >> n_procesos;
    int n_prioridades; cin >> n_prioridades;
    map<string, vector<int>> map_prioridades; // id_prioridad, vector con los ids de los procesos

    // PROCESADORES
    vector<string> procesadores_no_ini(n_procesadores);
    vector<string> procesadores;
    for (int i = 0; i < (int)procesadores_no_ini.size(); ++i) procesadores_no_ini[i] = "procesador" + to_string(i+1);

    // PROCESOS
    vector<int> procesos_no_ini(n_procesos);
    vector<int> procesos;
    for (int i = 0; i < (int)procesos_no_ini.size(); ++i) procesos_no_ini[i] = i+1;

    // PRIORIDADES
    vector<string> prioridades_no_ini(n_prioridades);
    vector<string> prioridades;
    for (int i = 0; i < (int)prioridades_no_ini.size(); ++i) prioridades_no_ini[i] = "prioridad" + to_string(i+1);

    // Definimos una semilla aleatoria para cada ejecución
    srand(time(NULL));

    int MAX; cin >> MAX; // Nombre total de instrucciones

    // INICIALIZACIÓN CLÚSTER
    escribir_bintree(procesadores_no_ini, procesadores);

    // INICIALIZACIÓN ÁREA DE ESPERA
    int n_area_espera = rand() % n_procesos;
    cout << n_area_espera << endl;
    for (int i = 0; i < n_area_espera; ++i) {
      int id_proceso = rand() % procesos_no_ini.size();
      cout << procesos_no_ini[id_proceso] << endl;

      procesos.push_back(procesos_no_ini[id_proceso]);
      int size_aux = procesos_no_ini.size();
      int proceso_last = procesos_no_ini[size_aux - 1];
      procesos_no_ini[id_proceso] = proceso_last;
      procesos_no_ini.pop_back();
    }

    // Primera escritura para ver si todo se ha configurado bien
    cout << "imprimir_estructura_cluster" << endl;
    cout << "imprimir_area_espera" << endl;
    cout << "imprimir_procesadores_cluster" << endl;

    for (int INSTRUCCIONES = 1; INSTRUCCIONES <= MAX; ++INSTRUCCIONES) {
        int x = rand() % 25;

        if (x == 1) { // configurar_cluster
            cout << "cc" << endl;
            escribir_bintree(procesadores_no_ini, procesadores);
        }

        else if (x == 2) { // modificar_cluster !

        }

        else if (x == 3) { // alta_prioridad (F)
          int aux = rand() % 4;
          if (aux == 0) { // Da de alta una prioridad ya existente
            if (!prioridades.empty()) {
              int index = rand() % prioridades.size();
              cout << "ap " << prioridades[index] << endl;
            }
          }
            else { // Da de alta una nueva prioridad
              if (!prioridades_no_ini.empty()) {
                int index = rand() % prioridades_no_ini.size();
                cout << "ap " << prioridades_no_ini[index] << endl;

                // Pasamos la prioridad a existente y la borramos de no_inicializadas
                prioridades.push_back(prioridades_no_ini[index]);
                int size_aux = prioridades_no_ini.size();
                string prioridad_last = prioridades_no_ini[size_aux - 1];
                prioridades_no_ini[index] = prioridad_last;
                prioridades_no_ini.pop_back();
            }
          }
        }

        else if (x == 4) { // baja_prioridad (F)
            int aux = rand() % 4;

            if (aux == 0) { // Da de baja una prioridad que no existe
              if (!prioridades_no_ini.empty()) {
                int index = rand() % prioridades_no_ini.size();
                cout << "bp " << prioridades_no_ini[index] << endl;
              }
            }
            else { // Da de baja una prioridad que existe
              if (!prioridades.empty()) {
                int index = rand() % prioridades.size();
                cout << "bp " << prioridades[index] << endl;

                /*
                // Pasamos la prioridad a no_inicializadas y la borramos de existentes
                prioridades_no_ini.push_back(prioridades[index]);
                int size_aux = prioridades.size();
                string prioridad_last = prioridades[size_aux - 1];
                prioridades[index] = prioridad_last;
                prioridades.pop_back();
                */
              }
            }
        }

        else if (x == 5 or x == 23 or x == 24) { // alta_proceso_espera
            int aux = rand() % 5;
            int proceso_id;
            int proceso_memoria = rand() % 20 + 1;
            int proceso_temps   = rand() % 20 + 1;
            string prioridad_id;

            if (aux == 0) { // Da de alta un proceso de espera en una prioridad no existente
              if (!procesos.empty() and !prioridades_no_ini.empty()) {
                int proceso_indice = rand() % procesos.size();
                proceso_id = procesos[proceso_indice];

                int prioridad_indice = rand() % prioridades_no_ini.size();
                prioridad_id = prioridades_no_ini[prioridad_indice];

                cout << "ape " << prioridad_id << " " << proceso_id << " " << proceso_memoria << " " << proceso_temps << endl;
              }
            }

            /*
            else if (aux == 2) { // Da de alta un proceso de espera que ya existe en la prioridad
              int prioridad_indice = rand() % prioridades.size();
              prioridad_id = prioridades[prioridad_indice];

              vector<int> v = map_prioridades.find(prioridad_id)->second;
              int indice_aux = rand() % v.size();
              proceso_id = v[indice_aux];
            }*/

            else {
              if (!prioridades.empty() and !procesos_no_ini.empty()) {
                int prioridad_indice = rand() % prioridades.size();
                prioridad_id = prioridades[prioridad_indice];

                int proceso_indice = rand() % procesos_no_ini.size();
                proceso_id = procesos_no_ini[proceso_indice];

                cout << "ape " << prioridad_id << " " << proceso_id << " " << proceso_memoria << " " << proceso_temps << endl;
              }
            }
        }

        else if (x == 6) { // alta_proceso_procesador (F)
            // lee el identificador de un procesador
            if (!procesadores.empty()) {
              int aux = rand() % procesadores.size();
              string procesador_id = procesadores[aux];

              // lee los datos de un proceso
              int proceso_id = rand() % procesos_no_ini.size();
              proceso_id = procesos_no_ini[proceso_id];
              int proceso_memoria = rand() % 50 + 1;
              int proceso_temps = rand() % 50 + 1;

              // Output
              cout << "app " << procesador_id << " " << proceso_id << " " << proceso_memoria << " " << proceso_temps << endl;
            }
        }

        else if (x == 7) { // baja_proceso_procesador (F)
            // lee el identificador de un procesador
            if (!procesadores.empty() and !procesos.empty()) {
              int procesador_index = rand() % procesadores.size();

              int proceso_index = rand() % procesos.size();

              // Output
              cout << "bpp " << procesadores[procesador_index] << " " << procesos[proceso_index] << endl;
            }
        }

        else if (x == 8) { // enviar_procesos_cluster !

        }

        else if (x == 9 or x == 17) { // avanzar_tiempo (F)
          int tiempo = rand() % 15 + 1;
          cout << "at " << tiempo << endl;
        }

        else if (x == 10 or x == 18) { // imprimir_prioridad (F)
            int aux = rand() % 4;

            if (aux == 0) { // Imprime una prioridad no inicializada
              if (!prioridades_no_ini.empty()) {
                int prioridad_indice = rand() % prioridades_no_ini.size();
                cout << "ipri " << prioridades_no_ini[prioridad_indice] << endl;
              }
            }
            else { // Imprime una prioridad inicializada
              if (!prioridades.empty()) {
                int prioridad_indice = rand() % prioridades.size();
                cout << "ipri " << prioridades[prioridad_indice] << endl;
              }
            }
        }

        else if (x == 11 or x == 19) { // imprimir_area_espera (F)
            cout << "iae" << endl;
        }

        else if (x == 12 or x == 20) { // imprimir_procesador (F)
            int aux = rand() % 4;

            if (aux == 0) { // Imprime un procesador no inicializado
              if (!procesadores_no_ini.empty()) {
                int indice = rand() % procesadores_no_ini.size();
                cout << "ipro " << procesadores_no_ini[indice] << endl;
              }
            }

            else { // Imprime un procesador inicializado
              if (!procesadores.empty()) {
                int indice = rand() % procesadores.size();
                cout << "ipro " << procesadores[indice] << endl;
              }
            }
        }

        else if (x == 13 or x == 21) { // imprimir_procesadores_cluster (F)
            cout << "ipc" << endl;
        }

        else if (x == 14) { // imprimir_estructura_cluster (F)
            cout << "iec" << endl;
        }

        else if (x == 15) { // compactar_memoria_procesador !

        }

        else if (x == 16) { // compactar_memoria_cluster !

        }
    }

    // Queremos comprobar que todo vaya bien cuando acabe
    cout << "imprimir_estructura_cluster" << endl;
    cout << "imprimir_area_espera" << endl;
    cout << "imprimir_procesadores_cluster" << endl;


    // fer el fin
    cout << "fin" << endl;
}
