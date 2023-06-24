/** @file Area_Espera.hh
 *  @brief Especificacion de la clase Area_Espera
*/

#ifndef AREA_ESPERA_HH
#define AREA_ESPERA_HH

#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include<list>
#include<set>
#include<map>
#include<utility>  
#endif

using namespace std;

/*
    Ejemplo de la representación del Área de Espera:
 
    +-----------------------------------------------------+
    | Prioridad |    Procesos    | Aceptados | Rechazados |
    +-----------------------------------------------------+
    |    P1     |   11-111-123   |     x1    |     y1     | 
    +-----------------------------------------------------+
    |    P2     |   122-121-13   |     x2    |     y2     |
    +-----------------------------------------------------+
    |    P3     |   12-124       |     x3    |     y3     |
    +-----------------------------------------------------+
    |    P4     |   123-125-156  |     x4    |     y4     |
    +-----------------------------------------------------+

*/

/** @class Area_Espera
 *  @brief Representa un conjutno de procesos pendientes a enviar. (obj. 'Proceso')
 * 
 *  La clase tiene el proposito de gestionar un conjuto de procesos en espera de ser ejecutados.
 *  Ésta permite añadir nuevos procesos en espera (indicando su prioridad), listarlos según el orden 
 *  lexicográfico de las prioridades y enviar procesos al clúster, en orden de la prioridad y según el orden de entrada (FIFO).
 * 
 *  Las prioridades del área de espera están formadas por un campo (struct) que contiene una lista que simula una 
 *  colas de procesos y un conjunto 'set' que permite ordenar los procesos para consultar eficientemente.  
*/
class Area_Espera {

    public:
    // ! Constructoras:

    /** @brief Creadora por defecto. Constructora de un conjunto de prioridades y procesos vacío. Se ejecuta automáticamente al declarar un conjutno de prioridades y procesos.
     *  \pre <em>cierto</em>
     *  \post El resultado es un conjunto de prioridades y procesos el cual sus atributos no han sido inicializados.
    */
    Area_Espera();

    // -----------------------------------------------------------------------------------------------------------------------------------------
    
    // ! Modificadoras (Setters):

    /** @brief Modificadora que añade una prioridad a el área de espera, en caso que no exista previamente.
     *  \pre <em>prior</em> es un identificador ('string') de una prioridad que contiene solo letras y números.
     *  \post Devuelve <em>1</em> en caso que ya exista una prioridad con identificador <em>prior</em>, y en caso
     *        contrario, además de devolver <em>0</em>, la prioridad <em>prior</em> se ha añadido al área de espera, sin procesos pendientes.
    */
    int alta_prioridad(const string& prior);

    /** @brief Modificadora que elimina una prioridad del área de espera, en caso que exista.
     *  \pre <em>prior</em> es un identificador ('string') de una prioridad que contiene solo letras y números.
     *  \post Devuelve un <em>1</em> en caso que no exista una prioridad con identificador <em>prior</em>. Luego,
     *        en caso que en la prioridad había proceso/s, devuelve <em>2</em>. Si no es ninguno de los dos anteriores casos,
     *        la prioridad <em>prior</em>se ha eliminado al área de espera, las demás prioridades se han ajustado en el map, 
     *        según su grado de "prioridad" correspondiente. 
    */
    int baja_prioridad(const string& prior);

    /** @brief Modificadora que añade un proceso a el área de espera, en caso que no exista previamente.
     *  \pre <em>prior</em> es un identificador ('string') de una prioridad que contiene solo letras y números,
     *       y <em>Proc</em> es el proceso a añadir a la prioridad del área de espera.
     *  \post Devuelve un <em>1</em> en caso que no exista una prioridad con identificador <em>prior</em>. 
     *        Luego, en caso que en la prioridad ya existía el proceso/s, devuelve <em>2</em>.
     *        En caso que no exista, además de devolver <em>0</em> se ha añadido el proceso área de espera, 
     *        ajustandose en la prioridad indicada por el identificador. 
    */
    int alta_proceso_espera(const Proceso& proc, const string& prior); 

    /** @brief Modificadora que se encarga de actualizar el área de espera enviando, según su grado de prioridad, un conjunto de procesos al clúster, 
     *  \pre   <em>num_prior > 0</em> es el numero de procesos a enviar al clúster <em>clu</em>, por orden de prioridad.
     *  \post  Por un lado, se han terminado aquellos procesos que han sido enviados al clúster de sus correspondientes prioridades.
     *         Por otro lado, se han añadido aquellos procesos rechazados por el clúster, tratadas como nuevas, con el misma prioridad.
     *         Además, según el criterio anterior, se ha incrementado el contador de los procesos aceptados y rechazados en las prioridades.
    */
    void enviar_procesos_cluster(Cluster& clu, int& num_prior);

    // -----------------------------------------------------------------------------------------------------------------------------------------

    // ! Consultoras (Getters):

    // -----------------------------------------------------------------------------------------------------------------------------------------

    // ! Lectura del Área de Espera:

    /** @brief Método que se encarga de inicializar los atributos del conjunto, dados unos datos por el canal standard de la entrada.
     *  \pre Están disponibles por el canal standard de entrada un número entero 'nprior >= 0' que indica el tamaño del conjunto de el área de espera
     *       seguido de una secuencia de idn 'strings' y p 'colas' que identifican a las prioridades (sin repeticiones). 
     *  \post El parámetro implícito pasa a tener todos los atributos leídos del canal standard de entrada, de manera ordenada para facilitar su dirección.
     *        Los contadores de prioridades aceptadas y rechazadas son inicializadas a cero.
    */
    void configurar_area_espera();                      // ? Inicializador de Area_Espera             

    // -----------------------------------------------------------------------------------------------------------------------------------------

    // ! Escritura del Área de Espera:

    /** @brief Operación de escritura: Método que se encarga de imprimir las prioridades y procesos pendientes del área de espera.
     *  \pre   <em>cierto</em>
     *  \post  Se han escrito las prioridades y procesos pendientes del parámetro implícito al canal standard de salida.
    */
    void imprimir_area_espera() const ;

    /** @brief Operación de escritura: Método que se encarga de imprimir una prioridad específica del área de espera.
     *  \pre <em>idn_prior</em> es un identificador de la prioridad a consultar.
     *  \post Devuelve <em>false</em> en caso de que no exista una prioridad con identificador <em>idn_prior</em>, y en caso contrario, se devuelve <em>true</em>
     *        y se imprime por el canal standard el nombre y los procesos pendientes.
    */
    bool imprimir_prioridad(const string& idn_prior) const; 

    // -----------------------------------------------------------------------------------------------------------------------------------------

    private:

    /** @struct Prioridad
     *  @brief Struct que representa una prioridad operativa del área de espera.
     *  
     *  Permite almacenar información relativa a un Prioridad, como sus procesos, que por un lado
     *  se guardan sus identificadores ordenados en un conjunto 'set' y por otro lado se guardan 
     *  por orden de llegada en una lista (que simula una cola), además de recopilar la información
     *  sobre los procesos aceptados y rechazados por el clúster.
    */
    struct Prioridad{
        set<int> procesos;                              // ? < Set que contiene los identificadores y las posiciones del conjunto de procesos, ordenados según el grado del identificador.
        list<Proceso> cjt_procesos;                     // ? < Lista que contiene toda la información de los procesos, ordenados según el orden de entrada, simulando una cola de procesos.

        int procesos_aceptados;                         // ? < Número de procesos aceptados por el cluster, desde el inicio de la ejecución.     
        int procesos_rechazados;                        // ? < Número de procesos rechazados por el clúster, desde el inicio de la ejecución.  

        /** @invariant Invariante de la representación:
         *  procesos_aceptados >= 0
         *  procesos_rechazados >= 0
        */  
    };   

    /** @brief Map que contiene a los procesos del circuito según el orden de inserción de prioriades.
     * 
     *   @note Analísis del coste de la implementación de los métodos y atributos de la clase 'Area_Espera'.
     * 
     *   Por un lado, al utilizar un map, es posible acceder a los procesos de una prioridad de manera eficiente, 
     *   ya que la búsqueda por clave en un map es de <em>coste logarítmico</em> O(log(n)). 
     *   Además, se garantiza que los procesos se almacenen en el orden de inserción de las prioridades.
     * 
     *   Por otro lado, al utilizar una lista para contener procesos, el coste de imprimir los procesos de una prioridad (
     *   sin tener en cuenta el coste de busqueda, mencionado anteriormente), tiene un coste lineal correspondiente al número de procesos. 
     *   Además, se usa una lista para facilitar su gestión a la hora de añadir o eliminar procesos, 
     *   sin modificar el tamaño de la lista ni su contenido ajeno al proceso a tratar.
    */
    map<string, Prioridad> prioridades;                 // ? < Map que contiene a los procesos del circuito según el orden de inserción de prioriades.  

};
#endif