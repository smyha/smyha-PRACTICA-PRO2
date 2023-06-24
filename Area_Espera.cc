#include "Area_Espera.hh"

// ! Private:
// -----------------------------------------------------------------------------------------------------------------------------------------

// ! Constructoras

Area_Espera:: Area_Espera(){}

// -----------------------------------------------------------------------------------------------------------------------------------------

// ! Modificadoras (Setters):

int Area_Espera::alta_prioridad(const string& idn) {
    map<string, Prioridad>::iterator it = prioridades.find(idn);

    // Si ya existe en el área de espera una prioridad con el mismo identificador
    if (it != prioridades.end()) return 1;
    
    // Si no existe en el área de espera, añade la prioridad.
    Prioridad prioridad;        // Prioridad vacía
    // Inicializa la información sobre la transferencia de procesos al clúster
    prioridad.procesos_aceptados = 0;
    prioridad.procesos_rechazados = 0;
    prioridades.insert(it, make_pair(idn, prioridad));
    
    return 0;
}

int Area_Espera::baja_prioridad(const string& prior) {
    map<string, Prioridad>::iterator it = prioridades.find(prior);

    // Si no existe la prioridad en el área de espera.
    if (it == prioridades.end()) return 1;
    
    // Si hay proceso/s en la prioridad.
    if (not it->second.cjt_procesos.empty()) return 2;
    
    // Elimina la prioridad del área de espera
    prioridades.erase(it);
    
    return 0;
}

int Area_Espera::alta_proceso_espera(const Proceso& proc, const string& prior){
    // Verificar si la prioridad existe en el área de espera
    map<string, Prioridad>::iterator it = prioridades.find(prior);

    // Si la prioridad no existe en el área de espera
    if (it == prioridades.end()) return 1;
    
    // Si el proceso ya existe en la prioridad
    if (it->second.procesos.find(proc.consultar_identificador_proceso()) != it->second.procesos.end()) return 2;
    
    // Agregar el proceso a la prioridad    
    it->second.cjt_procesos.push_back(proc);
    it->second.procesos.insert(proc.consultar_identificador_proceso());
     
    return 0;
}

void Area_Espera::enviar_procesos_cluster(Cluster& clu, int& num_prior) {
    // Itera para cada prioridad de el área de espera hasta enviar todos los procesos determinados.
    map<string, Prioridad>:: iterator it = prioridades.begin();

    while (it != prioridades.end() and num_prior > 0){
        list<Proceso>::iterator it2 = it->second.cjt_procesos.begin();
        int tamano_prioridad = it->second.cjt_procesos.size();
        
        // Itera para todos los procesos de la prioridad hasta enviar todos los procesos determinados.
        for (int i = 0; i < tamano_prioridad and num_prior > 0; ++i){        
            // Si el clúster admite procesos a llevar a cabo en sus procesadores.
            if (clu.anadir_proceso_cluster(*it2)){
                // Esborramos el proceso del registro de la prioridad.
                it->second.procesos.erase(it2->consultar_identificador_proceso());
                // Incrementa el número de procesos aceptados.
                ++it->second.procesos_aceptados;
                // Decrementa el número de procesos a enviar.
                --num_prior;
            }
            // Si no, recibe los procesos a enviar como nuevos, terminando el proceso de envío.
            else {
                // Recibe de nuevo el proceso rechazado.
                it->second.cjt_procesos.push_back(*it2);
                // Incrementa el número de procesos rechazados.
                ++it->second.procesos_rechazados;
            }
            // Elimina definitivamente el proceso y apunta al siguiente.
            it2 = it->second.cjt_procesos.erase(it2);  
        }
        // Pasa a enviar procesos de la siguiente prioridad.
        ++it;
    }    
} 

// -----------------------------------------------------------------------------------------------------------------------------------------

// ! Consultoras (Getters):

// -----------------------------------------------------------------------------------------------------------------------------------------

// ! Lectura del Área de Espera:

void Area_Espera::configurar_area_espera() {
    int nprior;
    cin >> nprior;

    // Inicializar el iterador con el inicio de prioridades
    map<string, Prioridad>::iterator it = prioridades.begin();  

    // Lee todas las prioridades a insertar en el área de espera.
    for (int i = 0; i < nprior; ++i) {
        string prior;
        cin >> prior;
        Prioridad prioridad;    // Prioridad vacia
        // Inicializa la información sobre la transferencia de procesos al clúster
        prioridad.procesos_aceptados = 0, prioridad.procesos_rechazados = 0;

        it = prioridades.insert(it, make_pair(prior, prioridad));
        ++it;
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------

// ! Escritura del Área de Espera:

void Area_Espera::imprimir_area_espera() const {
    map<string, Prioridad>::const_iterator it = prioridades.begin();
    
    while (it != prioridades.end()) {
        // Imprime el identificador de la prioridad.
        cout << it->first << endl;
        // Imprime el conjutno de procesos de la prioridad.
        list<Proceso>::const_iterator it1 = it->second.cjt_procesos.begin();
        while (it1 != it->second.cjt_procesos.end()){
            it1->imprimir_proceso();
            ++it1;
        }
        // Imprime la información sobre los procesos aceptados y rechazados de la prioridad al clúster.
        cout << it->second.procesos_aceptados << ' ' << it->second.procesos_rechazados << endl;
        
        // Imprime la siguiente prioridad.
        ++it;
    }
}

bool Area_Espera::imprimir_prioridad(const string& idn_prior) const {
    map<string, Prioridad>::const_iterator it = prioridades.find(idn_prior);
    
    // Si la prioridad no existe en el área de espera
    if (it == prioridades.end()) return false;
    
    // Imprime el conjutno de procesos de la prioridad
    list<Proceso>::const_iterator it1 = it->second.cjt_procesos.begin();
    while (it1 != it->second.cjt_procesos.end()){
        it1->imprimir_proceso();
        ++it1;
    }
    // Imprime la información sobre los procesos aceptados y rechazados de la prioridad al clúster
    cout << it->second.procesos_aceptados << ' ' << it->second.procesos_rechazados << endl;
    
    return true;
}
