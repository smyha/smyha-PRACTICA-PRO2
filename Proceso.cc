#include "Proceso.hh"

// ! Constructoras:

Proceso::Proceso(){}

Proceso::Proceso(int idn_proceso, int mem_req, int tmp_ejc){
    this->identificador_proceso = idn_proceso;
    this->memoria_requerida = mem_req;
    this->tiempo_ejecucion = tmp_ejc;
}

// -----------------------------------------------------------------------------------------------------------------------------------------

 // ! Modificadoras (Setters):

bool Proceso::modificar_tiempo_ejecucion(int tmp){
    // Decrementamos el tiempo de ejecución al proceso.
    tiempo_ejecucion -= tmp;
    // Si el tiempo es menor o igual a cero, implica que se ha terminado.
    if (tiempo_ejecucion <= 0) return true;
    return false;
}

// -----------------------------------------------------------------------------------------------------------------------------------------

// ! Consultoras (Getters):   

int Proceso::consultar_identificador_proceso() const{
    return identificador_proceso;
}

int Proceso::consultar_memoria_requerida() const{
    return memoria_requerida;
}

// -----------------------------------------------------------------------------------------------------------------------------------------

// ! Lectura del proceso:

void Proceso::lectura_proceso(){
    cin >> identificador_proceso >> memoria_requerida >> tiempo_ejecucion;
}

// -----------------------------------------------------------------------------------------------------------------------------------------

// ! Escritura del proceso:

void Proceso::imprimir_proceso() const{
    cout << identificador_proceso << ' ' << memoria_requerida << ' ' <<  tiempo_ejecucion << endl;
}