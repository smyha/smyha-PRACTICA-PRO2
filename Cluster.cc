#include "Cluster.hh"
 
// ! Private:

void Cluster::inicializar_cluster(BinTree<string>& procesadores_arbol) {
    // Par formado por el identificador del procesador(string) y su memoria(int).
    pair<string,int> lectura_procesador;    
    cin >> lectura_procesador.first;
 
    if (lectura_procesador.first != "*" ){
        cin >> lectura_procesador.second;
        // Declaramos arboles auxiliares para leer los subárboles del nodo actual.
        BinTree<string> izq, der;
        // Leemos el subárbol izquierdo y el subárbol derecho.
        inicializar_cluster(izq);
        inicializar_cluster(der);
        // Crea el árbol de identificadores de los procesadores y pásalos al atributo del parámetro implícito.
        procesadores_arbol = BinTree<string> (lectura_procesador.first, izq, der);
        // Agregar el procesador al map de procesadores.
        procesadores[lectura_procesador.first] = Procesador(lectura_procesador.second);
    }
}
    
void Cluster::imprimir_cluster(const BinTree<string>& procesadores_arbol) const {
    // Si el árbol de procesadores no es vacio.
    if (not procesadores_arbol.empty()){
        cout << '(';
        cout << procesadores_arbol.value();
        // Imprime el subárbol izquierdo y el subárbol derecho.
        imprimir_cluster(procesadores_arbol.left()); 
        imprimir_cluster(procesadores_arbol.right());
        cout << ')';
    }
    // Indica que el subárbol de procesadores es vacio.
    else cout << ' ';
}

void Cluster::modificar_arbol(BinTree<string>& arbol1, const Cluster& clu_comp, const string& idn, int& caso){
    // Si el nodo no es vacío.
    if (not arbol1.empty()) {
        // Si el nodo a consultar es igual al identificador
        if (arbol1.value() == idn){
            // Si el procesador tiene procesos pendientes de acabar en memoria
            if (not procesadores[idn].consultar_procesos_pendientes()) caso = 2;
            // Determina si el procesador tiene procesadores auxiliares.
            else if (not arbol1.left().empty() or not arbol1.right().empty()) caso = 3;
            // Añadir el contenido del subárbol en el árbol del clúster principal.
            else {
                caso = -1;
                arbol1 = clu_comp.procesadores_arbol;   // Modifica el árbol
                procesadores.erase(idn);
                procesadores.insert(clu_comp.procesadores.begin(), clu_comp.procesadores.end());    // Añade el cambio al map
            }
        }
        else {
            // Construimos el nuevo árbol a partir de los subárbol izquierdo y del derecho.
            BinTree<string> l = arbol1.left();
            BinTree<string> r = arbol1.right();

            // Llamada recursiva para determinar los siguientes nodos del subárbol izquierdo
            modificar_arbol(l, clu_comp, idn, caso);    
            // Si todavía no se ha encontrado, llamada recursiva para determinar los siguientes nodos del subárbol derecho.               
            if (caso == 1) modificar_arbol(r, clu_comp, idn, caso);     

            // Formamos el nuevo árbol definitivo del clúster principal.
            arbol1 = BinTree<string>(arbol1.value(), l, r);
        } 
    } 
}

void Cluster::recorrido_anchura(const BinTree<string>& procesadores_arbol, list <string>& l){
    // Si el árbol no es vacío, añade los subárboles a la cola
    if(not procesadores_arbol.empty()){
        queue <BinTree<string> > c;
        c.push(procesadores_arbol);
        // Mientras que la cola no este vacía, mueve los procesadores de la cola a la lista.
        while(not c.empty()){
            BinTree<string> aux(c.front());
            l.insert(l.end(),aux.value());
            // Consulta el subárbol izquierdo y el subárbol derecho.
            if (not aux.left().empty()) c.push(aux.left());
            if (not aux.right().empty()) c.push(aux.right());
            // Extrae el último nodo de la cola
            c.pop();
        }
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------
 
// ! Constructoras
 
Cluster::Cluster(){}
 
// -----------------------------------------------------------------------------------------------------------------------------------------
 
// ! Modificadoras (Setters):

int Cluster::modificar_cluster(const string& idn, Cluster& clu_comp){
    int caso = 1;
    // Se determina cúal es el caso que se corresponde al intentar modificar el clúster.
    modificar_arbol(this->procesadores_arbol, clu_comp, idn, caso);
    return caso;
}

void Cluster::compactar_memoria_cluster() {
    procesadores_it it = procesadores.begin();
    // Compacta la memoria de cada procesador en el cluster
    while (it != procesadores.end()) {
        it->second.compactar_memoria();
        ++it;
    }
}

bool Cluster::compactar_memoria_procesador(const string& idn) {
    // Buscamos el procesador con el identificador dado.
    procesadores_it it1 = procesadores.find(idn);
    // Si no existe el procesador en el clúster
    if (it1 == procesadores.end()) return false;
    // Si existe, compactamos la memoria del procesador
    it1->second.compactar_memoria();
    return true;
}

int Cluster::alta_proceso_procesador(Proceso& prc, const string& idn_proc){
    procesadores_it it1 = procesadores.find(idn_proc);
    // Si no existe el procesador en el clúster.
    if (it1 == procesadores.end()) return 1;
    // Determina el caso según la función anadir_proceso
    int hueco = it1->second.consultar_hueco_ajustado(prc.consultar_memoria_requerida());
    return it1->second.anadir_proceso(prc, hueco);
}

int Cluster::baja_proceso_procesador(const string& idn_prc, const int& idn_proc){
    procesadores_it it1 = procesadores.find(idn_prc);
    // Si no existe el procesador en el clúster.
    if (it1 == procesadores.end()) return 1;
    // Determina el caso según la función finalizar_proceso_procesador
    return it1->second.finalizar_proceso_procesador(idn_proc);
}

void Cluster::avanzar_tiempo(const int& tmp){
    procesadores_it it = procesadores.begin();
    // Avanza el tiempo en cada procesador y gestiona su finalización
    while(it != procesadores.end()) {
        it->second.gestionar_tiempo_procesador(tmp);
        ++it;
    }
}

bool Cluster::anadir_proceso_cluster(const Proceso& p) {
    // Declaramos la lista para tener el orden de nivel del árbol de procesadores
    list<string> lista_bfs;
    recorrido_anchura(procesadores_arbol, lista_bfs);

    // Determinamos qué procesador es más cercano a la raíz, mirando por niveles.
    list<string>::const_iterator it_list = lista_bfs.begin();
    
    // Variables para almacenar los datos mejor procesador encontrado hasta el momento.
    string mejor_procesador = "";
    int mejor_hueco = -1;
    int mejor_memoria_libre = -1;

    while (it_list != lista_bfs.end()) {        
        // Iterador para recorrer los procesadores en el clúster.
        map<string, Procesador>::iterator it = procesadores.find(*it_list);
        // Si el procesador no contiene ningún proceso con el mismo identificador que 'p'.
        if (it != procesadores.end() and not it->second.consultar_proceso_procesador(p.consultar_identificador_proceso())){
            // Determinamos si se puede encajar el proceso en el procesador apuntado por 'it'
            int hueco = it->second.consultar_hueco_ajustado(p.consultar_memoria_requerida());
            // Si existe un hueco en el procesador apuntado por 'it'
            if (hueco != -1) {
                // Si no hay un mejor procesador seleccionado aún, lo establecemos como el actual
                int memoria_libre_actual = it->second.consultar_memoria_libre();
                if (mejor_procesador.empty() ) {
                    mejor_procesador = it->first;
                    mejor_hueco = hueco;
                    mejor_memoria_libre = memoria_libre_actual;
                } 
                // Discutimos los posibles casos de empate que surgen al escoger el procesador.
                else {
                    // Si el nuevo procesador tiene un hueco más ajustado respecto a 'p'
                    if (hueco < mejor_hueco) {
                        mejor_procesador = it->first;
                        mejor_hueco = hueco;
                        mejor_memoria_libre = memoria_libre_actual;
                    } 
                    // Si hay empate en el hueco más ajustado, se selecciona el que tiene más memoria libre
                    else if (hueco == mejor_hueco and memoria_libre_actual > mejor_memoria_libre) {
                        mejor_procesador = it->first;
                        mejor_hueco = hueco;
                        mejor_memoria_libre = memoria_libre_actual;    
                        // Si persiste el empate en la memoria libre, se mantiene el procesador más cercano a la raíz.   
                    }
                }
            }
        }
        // Buscamos en el siguiente procesador de la lista por niveles.
        ++it_list;
    }
    // Ningún procesador puede llevar a cabo el proceso 'p'
    if (mejor_procesador.empty()) return false;
    // Se agrega el proceso 'p' al mejor procesador seleccionado
    procesadores[mejor_procesador].anadir_proceso(p, mejor_hueco);
    return true;
}     

// -----------------------------------------------------------------------------------------------------------------------------------------
 
// ! Consultoras (Getters):
 
// -----------------------------------------------------------------------------------------------------------------------------------------
 
// ! Lectura del Clúster:
 
void Cluster::configurar_cluster(){
    procesadores.clear();
    inicializar_cluster(procesadores_arbol);
}
 
// -----------------------------------------------------------------------------------------------------------------------------------------
 
// ! Escritura del Clúster:
 
void Cluster::imprimir_estructura_cluster() {
    imprimir_cluster(procesadores_arbol);
    cout << endl;
}
 
void Cluster::imprimir_procesadores_cluster() const{
    map<string, Procesador>::const_iterator it = procesadores.begin();
    while (it != procesadores.end()) {
        cout << it->first << endl;
        it->second.imprimir_procesador_cluster();
        ++it;
    }
}
 
bool Cluster::imprimir_procesador(const string& idn) const{
    map<string, Procesador>::const_iterator it = procesadores.find(idn);
    // Si el procesador no se encuentra en el clúster
    if (it == procesadores.end()) return false;
    // Si el procesador se encuentra en el clúster
    it->second.imprimir_procesador_cluster();
    return true;
}
