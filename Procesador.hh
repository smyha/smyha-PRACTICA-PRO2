/** @file Procesador.hh
 *  @brief Especificacion de la clase Procesador
*/

#ifndef PROCESADOR_HH
#define PROCESADOR_HH

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include<map>
#include <set>
#include<utility>
#endif

using namespace std;

/* 1 : Caso de procesos contiguos:
    
    +--------------------------------------------------------+          En este caso, los procesos están colocados de forma contigua en la memoria del 
    | Proceso 1 | Proceso 2 | Proceso 3 |      Hueco         |          procesador, sin huecos libres entre ellos. Esto significa que no hay memoria disponible para 
    +--------------------------------------------------------+          asignar nuevos procesos sin realizar cambios en la estructura de la memoria.

    2: Caso de memoria con huecos al principio:
    
    +--------------------------------------------------------+          Hay un hueco al principio de la memoria del procesador. Esto podría permitir la 
    |      Hueco      | Proceso 1 | Proceso 2 | Proceso 3    |          inserción de nuevos procesos al comienzo de la memoria sin afectar a los procesos existentes.
    +--------------------------------------------------------+


    3: Caso de memoria con huecos en el medio:
    
    +--------------------------------------------------------+          Hay hueco/s en medio de la memoria del procesador. 
    | Proceso 1 |    Hueco    | Proceso 2 | Proceso 3 |  -   |          Esto podría permitir la inserción de nuevos procesos entre los procesos existentes sin afectar a su ubicación.
    +--------------------------------------------------------+


    4: Caso de memoria con huecos al final:
    
    +--------------------------------------------------------+          En este caso, hay un hueco al final de la memoria del procesador.
    | Proceso 1 | Proceso 2 | Proceso 3 |    Hueco    |   -  |          Esto podría permitir la inserción de nuevos procesos al final de la memoria sin afectar a los procesos existentes.
    +--------------------------------------------------------+

*/

/** @class Procesador
 *  @brief Representa un procesador operativo del clúster obj. ('Procesador').
 * 
 *  La clase Procesador representa un procesador operativo de un clúster, y dispone de atributos y métodos que lo definen como tal. 
 *  Entre sus atributos se encuentran los procesos en 'ejecución', así como su respectiva información sobre sus identificadores y posiciones en memoria,
 *  los huecos disponibles en memoria, y la cantidad de memoria total libre. En resumen, almacena la información de los procesos en memoria y facilita su gestión.
*/
class Procesador {
    public:
    // ! Constructoras:   

    /** @brief Creadora por defecto. Constructora de un procesador vacío. Se ejecuta automáticamente al declarar un procesador.
     *  \pre <em>cierto</em>
     *  \post El resultado es un procesador el cual sus atributos no han sido inicializados.
    */
    Procesador();

    /** @brief Creadora de procesador inicializado. Constructora de un procesador con identificación y tamaño de memoria establecido.
     *  \pre <em>cierto</em>
     *  \post El resultado es un procesador el cual sus atributos (identificador, tamaño memoria) han sido inicializados.
    */
    Procesador(int tm_memoria);

    // -----------------------------------------------------------------------------------------------------------------------------------------
    
    // ! Modificadoras (Setters):

    /** @brief Modificadora que se encarga de anadir proceso/s al procesador, gestionando la memoria.
     *  \pre  El parámetro implícito <em>p</em> es el proceso a añadir.
     *        Se cumple que <em> 0 <= pos <= memoria_procesador.size() - 1 </em>.
     *  \post Por un lado, devuelve un <em>2</em> en caso que ya exista un proceso en la memoria del procesador.
     *        Por otro lado, devuelve un <em>3</em> en caso de que no se pueda encajar el proceso en la memoria del procesador
     *        (se incluyen los casos: Si la memoria requerida por el proceso es más grande que la memoria del procesador o
     *        toda la memoria del procesador ya esta reservada por proceso/s o simplemente no se ha encontrado ningún hueco ajustado).
     *        Por último, además de devolver <em>-1</em>, se ha añadido el proceso en memoria, actualizando la información sobre los huecos.
    */
    int anadir_proceso(const Proceso& p, const int& hueco);                                        

    /** @brief Modificadora que se encarga de finalizar proceso/s del procesador, gestionando la memoria.
     *  \pre  El parámetro implícito <em>idn_proceso >= 0</em> es el identificador del proceso a finalizar.
     *  \post Devuelve un <em>2</em> en caso que no exista el proceso, y en caso contrario, además de devolver <em>-1</em>
     *        finaliza el proceso en la memoria del procesador, actualizando la información de los huecos.
    */
    int finalizar_proceso_procesador(const int& idn_proceso);   // ? Emplea 'finalizar_proceso'.

    /** @brief Modificadora que se encarga de avanzar el reloj del procesador, gestionando así la terminación de los procesos.
     *  \pre  <em>tmp > 0</em> es la cantidad de tiempo que debe de avanzar el reloj del procesador.
     *  \post Se han finalizado todos los procesos activos que hayan acabado en ese intervalo de tiempo 
     *        de la lista de procesos de ejecución (liberando cierto espacio en la memoria del procesador).
    */
    void gestionar_tiempo_procesador(const int& tmp);

    /** @brief Modificadora que se encarga de compactar los proceso/s del procesador, gestionando la memoria.
     *  \pre  <em>cierto</em>
     *  \post El conjunto de procesos ha sido compactado, eliminando los huecos entre procesos, actualizando
     *        la información de estos mismos en los atributos del parámetro implícito.
    */
    void compactar_memoria();

    // -----------------------------------------------------------------------------------------------------------------------------------------

    // ! Consultoras (Getters):

    /** @brief Consultora (Getter) que devuelve la cantidad de memoria libre del parámetro implícito (procesador).
     *  \pre  <em>cierto</em>
     *  \post Se devuelve la cantidad de memoria libre del parámetro implícito (procesador).
    */
    int consultar_memoria_libre() const;

    /** @brief  Consultora (Getter) que determina si el parámetro implícito (procesador) tiene procesos pendientes.
     *  \pre  <em>cierto</em>
     *  \post Se devuelve <em>false</em> si la memoria del parámetro implícito contiene procesos en memoria, 
     *        y en caso contrario, devuelve <em>true</em>.
    */
    bool consultar_procesos_pendientes() const;

    /** @brief Consultora (Getter) que devuelve el tamaño del hueco más ajustado para un determinado proceso.
     *  \pre  <em>mem_req</em> es la memoria que requiere el proceso.
     *  \post  Se devuelve el tamaño del hueco que se ajusta más al proceso. Si no se ha encontrado hueco, se devuelve -1.
    */
    int consultar_hueco_ajustado(const int& mem_req) const;

    /** @brief Consultora (Getter) que determina si el parámetro implícito (procesador) tiene un proceso en concreto.
     *  \pre   <em>idn</em> es el identificador de un proceso a consultar.
     *  \post  Devuelve <em>true</em> en caso que ya exista el proceso en el procesador, en caso contrario, devuelve <em>false</em>.
    */
    bool consultar_proceso_procesador(const int& idn) const;

    // -----------------------------------------------------------------------------------------------------------------------------------------

    // ! Lectura del procesador:

    // -----------------------------------------------------------------------------------------------------------------------------------------

    // ! Escritura del procesador:
    
    /** @brief Método que imprime por pantalla la información del procesador.  
     *  \pre <em>cierto</em> El objeto ''Procesador'' ha sido creado correctamente.
     *  \post Se muestra por el canal standard de salida la información del procesador, que incluye sus
     *  atributos y los procesos en ejecución que contiene en su memoria.
    */
    void imprimir_procesador_cluster() const;

    // -----------------------------------------------------------------------------------------------------------------------------------------

    private:      

    // Conjunto memoria procesador
    map<int, Proceso> procesos_ejecucion;               // ? Map que contiene los procesos que estan en ejecución, ordenados (clave) según su posicion inicial.
    map<int, int> posiciones_procesos;                  // ? Map que contiene las posiciones iniciales de los procesos, ordenados (clave) según su identificador.
    map<int, set<int>> memoria_procesador;              // ? Map que contiene las posciones iniciales de los huecos, que se encuentran ordenados (clave) según su tamaño.
    // Conjunto información memoria
    int tamano_memoria;                                 // ? < Numero de posiciones de memoria que contiene el procesador.
    int memoria_libre;                                  // ? < Numero de posiciones libres en memoria del propio procesador.

    /** @invariant Invariantes de la representación: 
     *  Inv: memoria_reservada >= 0
     *  Inv: tamano_memoria >= 0
    */

    /** @brief Modificadora que finaliza un proceso en el procesador y devuelve el iterador al siguiente proceso.
     *  \pre <em>it</em> es un identificador del proceso a eliminar.
     *  \post Además de eliminar el proceso de la memoria y actualizar los huecos, devuelve el iterador al siguiente proceso.
     * 
     *  @note Analísis del coste de la implementación de los métodos y atributos de la clase 'Procesador'. 
     * 
     *  En general, al utilizar un map, es posible acceder a los procesos de una procesador de manera eficiente, 
     *  ya que la búsqueda por clave en un map es de <em>coste logarítmico</em> O(log(n)). 
     *  El coste de consultar cualquier infomación de la memoria del procesador (identificadores, posiciones y huecos), 
     *  sin contar la própia información de los procesos, es de coste logarítmico .
     * 
     *  Para la escritura del procesador, la implementación tiene un coste lineal O(n), sea n el número de procesos en memoria, 
     *  ya que simplemente se trata de recorrer el map 'procesos_ejecución'.
    */
    map<int, Proceso>::iterator finalizar_proceso(map<int, int>::iterator& it);

};
#endif

