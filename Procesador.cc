#include "Procesador.hh"

// ! Private

map<int, Proceso>::iterator Procesador::finalizar_proceso(map<int, int>::iterator& it){
    // Datos necesarios para realizar correctamente el procedimiento.
    int pos_inicial = it->second; // Posición inicial del proceso a eliminar
    map<int, Proceso>::iterator it1 = procesos_ejecucion.find(pos_inicial);
    int mem_req = it1->second.consultar_memoria_requerida();
    int pos_final = pos_inicial + mem_req - 1;   // Posición final del proceso a eliminar
    
    // Liberar la memoria del procesador
    memoria_libre += mem_req;

    // Actualiza los huecos de la memoria
    int pos = 0;        // Posición inicial de hueco originado al eliminar el proceso.
    int hueco_total = 0;

    // ! Huecos al inicio de la memoria (Primer proceso)
    // Si hay espacio entre el inicio de la memoria del procesador y el proceso a eliminar es el primero de todos.
    if (it1 == procesos_ejecucion.begin()){
        int hueco_ini = it1->first;          // Hueco entre el inicio de la memoria y el proceso a eliminar
        if (hueco_ini > 0){
            hueco_total += hueco_ini;
            // Eliminar hueco inicial si existía
            // Si solo tenia una posición inicial en dónde habia un hueco de ese tamaño
            if (memoria_procesador[hueco_ini].size() == 1) memoria_procesador.erase(hueco_ini);
            else memoria_procesador[hueco_ini].erase(0);
        }
    }
    // ! Huecos antes y después del proceso (Proceso entre procesos)
    map<int, Proceso>::iterator it_hueco = it1;     // Iterador auxiliar para mirar los costados del proceso
    if (it_hueco != procesos_ejecucion.begin()) {
        --it_hueco;      // Se mira el 'anterior' proceso
        
        // Si existe el 'anterior' proceso, calcula el tamaño del hueco 'anterior'
        int prev_pos = it_hueco->first + it_hueco->second.consultar_memoria_requerida() - 1;  // Posición final del proceso 'anterior'
        int prev_hueco = pos_inicial - prev_pos - 1;
        // Modificamos a la posición correspondiente al nuevo hueco que se origina al eliminar el proceso
        pos = prev_pos + 1;
        // Si existia un hueco entre el proceso 'anterior' y el proceso a eliminar
        if (prev_hueco > 0) {
            hueco_total += prev_hueco;
            // Eliminar el hueco 'anterior' si existía:
            // Si solo tenia una posición inicial en dónde habia un hueco de ese tamaño
            if (memoria_procesador[prev_hueco].size() == 1) memoria_procesador.erase(prev_hueco);
            else memoria_procesador[prev_hueco].erase(prev_pos + 1);
        }
        ++it_hueco;     // Se 'restaura' el iterador hacia al proceso a eliminar
    }
    ++it_hueco;         // Se mira el siguiente proceso
    // Si existe el siguiente proceso, calcula el tamaño del 'siguiente' hueco
    if (it_hueco != procesos_ejecucion.end()){
        int sig_pos = it_hueco->first;          // Posición inicial del proceso 'siguiente'
        int sig_hueco = sig_pos - pos_final - 1;
        if (sig_hueco > 0) {
            hueco_total += sig_hueco;
            // Eliminar el siguiente hueco si existía
            // Si solo tenia una posición inicial en dónde habia un hueco de ese tamaño
            if (memoria_procesador[sig_hueco].size() == 1) memoria_procesador.erase(sig_hueco);
            else memoria_procesador[sig_hueco].erase(pos_final + 1);
        }
    }
    // ! Huecos al final de la memoria (Último proceso)
    // Si hay espacio entre el proceso a eliminar y el final de la memoria.
    if (it_hueco == procesos_ejecucion.end()){
        int hueco_fin = tamano_memoria - pos_final - 1;
        
        if (hueco_fin > 0){
            hueco_total += hueco_fin;
            // Eliminar el hueco final si existía
            // Si solo tenia una posición inicial en dónde habia un hueco de ese tamaño
            if (memoria_procesador[hueco_fin].size() == 1) memoria_procesador.erase(hueco_fin);
            else memoria_procesador[hueco_fin].erase(pos_final + 1);
        }
    }
    // Registra el nuevo hueco que se origina al eliminar el proceso de la memoria
    hueco_total += mem_req;
    memoria_procesador[hueco_total].insert(pos);

    // Eliminar el proceso del procesador
    posiciones_procesos.erase(it);
    return procesos_ejecucion.erase(it1);
}

// -----------------------------------------------------------------------------------------------------------------------------------------

// ! Constructoras: 

Procesador::Procesador() {}

Procesador::Procesador(int tm_memoria) {
    memoria_libre = tm_memoria;
    tamano_memoria = tm_memoria;
    // Si no hay procesos en ejecución, se considera todo el espacio como hueco
    memoria_procesador[tamano_memoria].insert(0);
}

// -----------------------------------------------------------------------------------------------------------------------------------------

// ! Modificadoras (Setters):

int Procesador::anadir_proceso(const Proceso& p, const int& hueco) {
    // Datos necesarios para realizar correctamente el procedimiento.
    int pos = -1, idn = p.consultar_identificador_proceso(), mem_req = p.consultar_memoria_requerida();

    map<int,int>::const_iterator it = posiciones_procesos.find(idn);
    // Si ya existe el proceso, indica que se ha de imprimir el error 'caso 2'
    if (it != posiciones_procesos.end()) return 2;

    // Si no se ha encontrado ningún hueco, indica que se ha de imprimir el error 'caso 3'
    if (hueco == -1) return 3;
    
    // Si existe el proceso se busca el hueco más ajustado para encajar el proceso, con 'lower_bound'.
    map<int, set<int>>::iterator it_hueco = memoria_procesador.find(hueco);
    // Si se ha encontrado un hueco que se ajusta al tamaño del proceso
    if (it_hueco != memoria_procesador.end()){
        pos = *it_hueco->second.begin();    // Posición inicial más pequeña del hueco
        
        // Si el hueco en dónde se ha insertado era de un tamaño más grande del que requeria el proceso.
        if (it_hueco->first > mem_req) memoria_procesador[it_hueco->first - mem_req].insert(pos + mem_req);  
        
        // Si solo hay una posicion en memoria que contenga ese hueco, elimina directamente el registro del hueco.
        if (memoria_procesador[it_hueco->first].size() == 1) memoria_procesador.erase(it_hueco);
        // Si hay más posiciones en memoria que contengan ese tamaño de hueco, elimina la posición inicial que será ocupada.
        else it_hueco->second.erase(pos);
        
        // Actualizar la memoria libre del procesador
        memoria_libre -= mem_req;
    }
    // Añande el proceso en el procesador.
    posiciones_procesos[idn] = pos;
    procesos_ejecucion[pos] = p;

    return -1;
}

int Procesador::finalizar_proceso_procesador(const int& idn) {
    // Encuentra el proceso a finalizar
    map<int, int>::iterator it = posiciones_procesos.find(idn);
    // Si no existe el proceso en memoria del procesador
    if (it == posiciones_procesos.end()) return 2;
    // Si existe, finaliza el proceso, actualizando información en memoria.
    finalizar_proceso(it);
    
    return -1;
}

void Procesador::gestionar_tiempo_procesador(const int& tmp) {
    // Si el map de procesos en ejecución no es vacío
    map<int, Proceso>::iterator it = procesos_ejecucion.begin();

    while (it != procesos_ejecucion.end()) {        
        // Avanza el tiempo restante de ejecución del proceso.
        if (it->second.modificar_tiempo_ejecucion(tmp)) {
            // El proceso ha terminado, se elimina de la memoria del procesador.
            map<int,int>::iterator it1 = posiciones_procesos.find(it->second.consultar_identificador_proceso());
            it = finalizar_proceso(it1);
        }
        // Avanza el tiempo al siguiente proceso.
        else ++it;
    }
}

void Procesador::compactar_memoria() {
    // Si la memoria del procesador contiene procesos pendientes.
    if (not procesos_ejecucion.empty()){
        map<int, Proceso>::iterator it = procesos_ejecucion.begin();
        int pos = 0; // Posición en dónde compactar el proceso.
        
        // Obten el hueco entre el espacio que hay entre el inicio de la memoria y el primer proceso de la memoria.
        // Aprovechamos que será el mismo valor que la posición inicial del primer proceso del procesador.
        // Con esta variable se actualizará el hueco que hay entre la posición en dónde se debe de colocar el proceso.
        int hueco_comp = it->first; 

        // Compacta todos los procesos en ejecución de la memoria del procesador
        while (it != procesos_ejecucion.end()){
            
            // Obtenemos el proceso a compactar
            Proceso comp = it->second;
            // Datos necesarios para realizar correctamente el procedimiento.
            int idn = comp.consultar_identificador_proceso(), mem_req = comp.consultar_memoria_requerida();
            
            // Actualiza la variable de la posición final
            int pos_final_previo = it->first + it->second.consultar_memoria_requerida() - 1;

            // Si la posición actual del proceso no coincide con la posición 'compactada', se necesita compactar el proceso
            if (it->first != pos){
                // Extrae el proceso a compactar de la memoria del procesador
                map<int,int>::iterator it_find = posiciones_procesos.find(idn);
                it = finalizar_proceso(it_find);    // Apunta al siguiente proceso

                // Restaura la memoria libre que se añade al aprovechar la función 'finalizar_proceso'
                memoria_libre -= mem_req;
                
                // Actualiza el hueco arrastrado al compactar el proceso, eliminando el hueco previo antes de compactar el proceso
                if (it != procesos_ejecucion.end()) hueco_comp += (it->first - pos_final_previo - 1);
                else hueco_comp += (tamano_memoria - pos_final_previo - 1);
  
                map<int, set<int>>::iterator it_hueco = memoria_procesador.find(hueco_comp + mem_req);
                // Si solo hay una posicion en memoria que contenga ese hueco, elimina directamente el registro del hueco.
                if (memoria_procesador[it_hueco->first].size() == 1) memoria_procesador.erase(it_hueco);
                // Si hay más posiciones en memoria que contengan ese tamaño de hueco, elimina la posicion inicial que será ocupada.     
                else it_hueco->second.erase(pos);

                // Compacta el proceso 
                posiciones_procesos[idn] = pos;
                procesos_ejecucion[pos] = comp;
                
                // Registra el hueco originado al compactar el proceso.
                memoria_procesador[hueco_comp].insert(pos + mem_req);
            }
            // Apunta al siguiente proceso en el mapa de procesos en ejecución y actualiza el hueco que se origina al compactar el siguiente proceso 
            else{
                ++it;
                if (it != procesos_ejecucion.end()) hueco_comp = it->first - pos_final_previo - 1;
            }
            // Incrementa la posición correspondiente para encajar el siguiente proceso 
            pos += mem_req;
        }  
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------

// ! Consultoras (Getters):

int Procesador::consultar_memoria_libre() const{
    return memoria_libre;
}

bool Procesador::consultar_procesos_pendientes() const{
    return procesos_ejecucion.empty();
}

int Procesador::consultar_hueco_ajustado(const int& mem_req) const{
    // Busca el hueco más ajustado en la memoria del procesador con el método 'lower_bound'.
    map<int, set<int>>:: const_iterator it = memoria_procesador.lower_bound(mem_req);
    if (it != memoria_procesador.end()) return it->first;
    return -1;
}  

bool Procesador::consultar_proceso_procesador(const int& idn) const{
    return posiciones_procesos.find(idn) != posiciones_procesos.end();
}

// -----------------------------------------------------------------------------------------------------------------------------------------
 
// ! Escritura del procesador:

void Procesador::imprimir_procesador_cluster() const{
    // Si el map de procesos en ejecución no es vacío
    map<int, Proceso>::const_iterator it = procesos_ejecucion.begin();
    // Imprime todos los procesos en ejecución de la memoria del procesador.
    while (it != procesos_ejecucion.end()){
        cout << it->first << ' ';
        it->second.imprimir_proceso();
        ++it;
    }
}

