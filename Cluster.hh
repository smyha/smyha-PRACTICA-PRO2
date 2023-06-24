/** @file Cluster.hh
 *  @brief Especificación de la clase Cluster 
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH

#include "Procesador.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include<queue>
#include<list>
#endif

using namespace std;

/*
    Ejemplo de la estructura del árbol de procesadores  -------->   Lista del recorrido por anchura:
 
                       CPU 1 Root (Main)                            +----+------------+------------+------------+-------------+-------------+-------------+-------------+-------------+
                    /                   \                           | #  | Procesador |  IDN_1     |   IDN_11   |   IDN_12    |   IDN_111   |   IDN_112   |   IDN_121   |   IDN 122   |    
                CPU 11                  CPU 12                      +----+------------+------------+------------+-------------+-------------+-------------+-------------+-------------+
                /    \                /       \
            CPU 111     CPU 112    CPU 121  CPU 122

    Ejemplo de la representación del map de procesadores

    +------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+
    | Procesador | IDN_1 (Root) | IDN_11       | IDN_111       | IDN_111     | IDN_112      | IDN_12       | IDN_121      | IDN_122      |
    +------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+
    | Contenido  | Main         | CPU 11       | CPU 111       | CPU 111     | CPU 112      | CPU 12       | CPU 121      | CPU_122      |
    +------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+
*/

/** @typedef procesadores_it 
 *  Alias (Typedef para el iterador de un mapa de procesadores) para el iterador de la estructura 
 *  de datos map que almacena objetos 'Procesador' indexados por un string (identificador).
 *  Se usa para facilitar la sintaxis a su vez que se utiliza para iterar sobre los elementos de la misma.
*/
typedef map<string, Procesador>::iterator procesadores_it;

/** @class Cluster
 *  @brief Representa un clúster operativo. 
 * 
 *  La clase Cluster representa un conjunto de procesadores variable, distribuidos en forma de árbol binario,
 *  con identificadores únicos. Cada procesador puede tener dos, uno o cero procesadores sucesores, también llamados
 *  auxiliares. Todo clúster ha de tener como mínimo un procesador. Todo procesador tiene los mismos atributos, pero
 *  de diferente magnitud (almenos con un identificador y procesos diferentes). En resumen, facilita la gestión 
 *  de un conjunto de procesadores.
 * 
 *  @note El número máximo de procesadores permitidos en un clúster es ilimitado.
*/
class Cluster{
    public:
    // ! Constructoras:

    /** @brief Creadora por defecto. Constructora de un Cluster vacío. Se ejecuta automáticamente al declarar un Cluster.
     *  \pre <em>cierto</em>
     *  \post El resultado es un clúster con su árbol binario de procesadores no definido.
    */
    Cluster();

    // -----------------------------------------------------------------------------------------------------------------------------------------
    
    // ! Modificadoras:

    /** @brief Modificadora única del clúster que añade procesadores.
     *  \pre  <em>idn</em> indica el lugar en donde se añadiran los procesadores al Clúster.
     *        <em>clu_comp</em> es el clúster a colocar en el lugar del procesador referenciado
     *        por <em>idn</em> en el clúster principal.
     *  \post Devuelve <em>1</em> si el procesador no existe en el clúster principal, <em>2</em> en caso que tenga procesos en ejecución
     *        y <em>3</em> en caso que no sea el procesador raíz. Si no es ninguno de los casos anteriores, además de devolver <em>0</em> , 
     *        el nuevo cluster se coloca en el lugar de p, haciendo crecer así el clúster original.
    */
    int modificar_cluster(const string& idn, Cluster& clu_comp);                            

    /** @brief Modificadora que se encarga de compactar la memoria del clúster.
     *  \pre  <em>cierto</em>
     *  \post El conjunto de memorias de los procesadores del clúster ha sido compactado, eliminando un numero de posiciones consecutivas 
     *        en las memorias de los procesadores, las cúales anteriormente eran vacías entre procesos.
    */
    void compactar_memoria_cluster();

    /** @brief Modificadora que se encarga de compactar la memoria de un procesador del clúster.
     *  \pre <em>idn</em> es el identificador de un procesador (no tiene porque ser del clúster) que contiene solo letras y digitos
     *       al cúal se se le debe compactar la memoria
     *  \post Se devuelve <em>false</em> en caso de que no exista un procesador con identificador <em>idn</em>, y en caso contrario, además de devolver <em>true</em>
     *        se ha compactado la memoria del procesador <em>idn</em>, en dónde se mueven todos los procesos hacia el principio de la memoria del procesador, 
     *        sin dejar huecos, sin solaparse y respetando el orden inicial.
    */
    bool compactar_memoria_procesador(const string& idn);

    /** @brief Modificadora que da de alta a un proceso en un procesador del clúster que admita el proceso en su memoria.
     *  \pre <em>p</em> es el proceso a dar de alta en el clúster.
     *  \post   Se devuelve <em>false</em> en caso de que ningún procesador del clúster pueda llevar a cabo el proceso <em>p</em>, 
     *          y en caso contrario, además de devolver <em>true</em> el número total de memoria_reservada y el tamaño previsto 
     *          se ha incrementado según las características del proceso, y el proceso <em>p</em> se ha añadido a un procesador.
    */
    bool anadir_proceso_cluster(const Proceso& p);

    /** @brief Modificadora que da de alta a un proceso en un procesador del clúster, en caso de que éste no exista en él previamente.
     *  \pre <em>idn</em> es un identificador de un procesador (no tiene porque ser del clúster) y <em>prc</em> es el proceso a dar de alta.
     *  \post Se devuelve <em>1</em> en caso de que no exista un procesador con identificador <em>idn</em>, y en caso contrario, además de devolver <em>true</em>
     *        ,el número total de memoria_reservada y el tamaño previsto se ha incrementado según las características del proceso, y el proceso 
     *        <em>proc</em> se ha añadido al procesador. En el caso en el que la memoria del procesador no admita el proceso, se devuelve <em>3</em>.
    */
    int alta_proceso_procesador(Proceso& prc, const string& idn);

    /** @brief Modificadora que da de baja a un proceso en un procesador del clúster, en caso de que éste exista en él.
     *  \pre <em>idn_prc</em> es un identificador de un procesador (no tiene porque ser del clúster) y <em>idn_proc</em> es el proceso a dar de baja.
     *  \post Se devuelve <em>1</em> en caso de que no exista un procesador con identificador <em>idn</em>, y en caso contrario, además de devolver <em>-1</em>
     *        ,el número total de memoria_reservada y el tamaño previsto se ha decrementado según las características del proceso, y el proceso 
     *        <em>proc</em> se ha eliminado del procesador. En el caso en el que el proceso no exista en el procesador, se devuelve <em>2</em>.
    */
    int baja_proceso_procesador(const string& idn_prc, const int& idn_proc);
    
    /** @brief Modificadora que se encarga de gestionar el tiempo transcurrido desde la ejecución y implementación de procesos del clúster.
     *  \pre <em>tmp</em> indica el tiempo que ha pasado desde la ejecución. 
     *  \post Se han modificado todos los tiempos de los procesadores del clúster.
    */
    void avanzar_tiempo(const int& tmp);

    // -----------------------------------------------------------------------------------------------------------------------------------------

    // ! Consultoras:

    // -----------------------------------------------------------------------------------------------------------------------------------------

    // ! Lectura del Cluster:

    /** @brief Método que se encarga de inicializar los procesadores del cluster, sus conexiones y la memoria de cada uno de ellos.
     *  \pre Está disponible por el canal standard de entrada la información de los procesadores, en forma de árbol binario, particularmente en preorden.
     *       Primero hay un número de procesadores p >= 0 seguido de cada uno de sus identificadores, conexiones auxiliares y memoria de cada uno de ellos.
     *  \post El parametro implícito ha sido modificado de forma que se han almacenado todos los procesadores con la información correspondiente.
    */
    void configurar_cluster();                                      // ? Emplea 'inicializar_cluster'

    // -----------------------------------------------------------------------------------------------------------------------------------------

    // ! Escritura del Cluster:

    /** @brief Método que se encarga de imprimir la estructura (árbol binario de procesadores) del clúster.
     *  \pre <em>cierto</em>
     *  \post Se ha muestra por el canal standard de salida la estructura del clúster en "preorden ", es decir, 
              comenzando por el nodo actual (raíz), luego visitando sus hijos izquierdos  
              y finalmente visitando sus hijos derechos .
    */
    void imprimir_estructura_cluster();

    /** @brief Método que se encarga de imprimir los procesadores del clúster, en orden creciente del identificador.
     *  \pre <em>cierto</em>
     *  \post Se ha impreso los procesadores del clúster por orden creciente por el canal de salida estándar.
    */
    void imprimir_procesadores_cluster() const;

    /** @brief Operación de escritura 
     *  \pre <em>idn</em> es un identificador del procesador a consultar.
     *  \post Devuelve <em>false</em> en caso de que no exista un procesador con identificador <em>idn</em>, y en caso contrario, 
     *        se devuelve <em>true</em> y se imprime por el canal standard de salida los procesos del parámetro implícito 
     *        por orden creciente de primera posición de memoria. Además, se escribe el tiempo para que acabe el proceso.
    */
    bool imprimir_procesador(const string& idn) const;

    // -----------------------------------------------------------------------------------------------------------------------------------------

    private:
    
    // ! Atributos

    /** @brief Árbol binario que representa la jerarquía de procesadores en el clúster. */
    BinTree<string> procesadores_arbol;                             // ? Árbol binario que representa la jerarquía de procesadores en el clúster
    map<string, Procesador> procesadores;                           // ? Map que contiene los procesadores, ordenados según el grado de su identificador.

    // ! Métodos

    /** @brief Método que se encarga de imprimir los procesadores del clúster, en orden creciente del identificador.
     *  \pre <em>procesadores_arbol</em> es el parámetro a inicializar.
     *  \post Se ha impreso los procesadores del clúster (para) por orden creciente por el canal de salida estándar.
     *  
     *  @note Analísis del coste de la implementación de los métodos y atributos de la clase 'Cluster':
     * 
     *        El coste de esta función depende del número de nodos en el árbol que se está creando. 
     *        En cada llamada recursiva, se realiza una lectura y se crea un nuevo subárbol izquierdo y derecho. 
     *        Si asumimos que el árbol tiene N nodos, el coste será O(N), ya que cada nodo se procesa una vez.
    */
    void inicializar_cluster(BinTree<string>& procesadores_arbol);   // ? Inicializador de Clúster   

    /** @brief Método que se encarga de imprimir los procesadores del clúster, en orden creciente del identificador.
     *  \pre <em>procesadores_arbol</em> es el parámetro a imprimir.
     *  \post Se ha impreso los procesadores del clúster por orden creciente por el canal de salida estándar. 
     *  
     *  @note Analísis del coste de la implementación de los métodos y atributos de la clase 'Cluster':
     *        
     *        El coste de esta función también depende del número de nodos en el árbol. 
     *        En cada llamada recursiva, se imprime el valor de un nodo y se realiza una llamada recursiva para el subárbol izquierdo y derecho. 
     *        Si asumimos que el árbol tiene N nodos, el coste será O(N), ya que cada nodo se imprime una vez.
    */
    void imprimir_cluster(const BinTree<string>& procesadores_arbol) const;

    /** @brief Método que se encarga de determinar que caso corresponde devolver de la función modificar_clúster.
     * \pre <em>cierto</em>
     * \post Si se ha encontrado el nodo determinado por <em>idn</em> y este no tiene procesadores auxiliares, se le añade el subárbol
     *       al árbol del clúster principal, es decir, la raíz del nuevo cluster pasa a ser el correspondiente auxiliar de dicho procesador.
     * 
     * @note Analísis del coste de la implementación de los métodos y atributos de la clase 'Cluster':
     * 
     *       El coste de esta función también depende del número de nodos en el árbol. 
     *       En el peor caso, si el nodo a modificar está en el último nivel del árbol, se realizarán llamadas recursivas hasta llegar a ese nodo. 
     *       Si asumimos que el árbol tiene N nodos, hasta llegar al nodo a modificar, el coste será O(N), ya que cada nodo se procesa una vez.
    */
    void modificar_arbol(BinTree<string>& arbol1, const Cluster& clu_comp, const string& id, int& caso);
    
    /** @brief Método que se encarga de "escribir" en una lista: primero se escribe la raíz del árbol (es decir, el nodo 
     *         de nivel 0), después todos los nodos que están al nivel 1, de izquierda a derecha, después todos los nodos
     *         que están a nivel 2, también de izquierda a derecha, etc.
     * 
     *  \pre   <em>l</em> es una lista vacía.
     *  \post  <em>l</em> contiene los nodos de <em>procesadores_arbol</em> en orden creciente respecto al nivel donde se encuentran, 
     *          y los de cada nivel en orden de izquierda a derecha
     * 
     *  @note Analísis del coste de la implementación de los métodos y atributos de la clase 'Cluster':
     * 
     *        El coste de esta función también depende del número de nodos en el árbol. 
     *        En el peor caso, si el árbol tiene una estructura de árbol completo, es decir, todos los niveles excepto posiblemente el último nivel 
     *        están completamente llenos, se recorrerán todos los nodos. Si asumimos que el árbol tiene N nodos, el coste será O(N).
    */
    void recorrido_anchura(const BinTree<string>& procesadores_arbol, list <string>& l);
    
    /** @note Analísis del coste de la implementación de los métodos y atributos de la clase 'Cluster':
     *  
     *  <b>Implementación de los métodos privados:</b>
     *  <ul>
     *      <li>inicializar_cluster: El coste de esta función depende del número de nodos en el árbol que se está creando. 
     *      En cada llamada recursiva, se realiza una lectura y se crea un nuevo subárbol izquierdo y derecho. 
     *      Si asumimos que el árbol tiene N nodos, el coste será O(N), ya que cada nodo se procesa una vez.</li>
     *      
     *      <li>imprimir_cluster: El coste de esta función también depende del número de nodos en el árbol. 
     *      En cada llamada recursiva, se imprime el valor de un nodo y se realiza una llamada recursiva para el subárbol izquierdo y derecho. 
     *      Si asumimos que el árbol tiene N nodos, el coste será O(N), ya que cada nodo se imprime una vez.</li>
     *      
     *      <li>modificar_arbol:  El coste de esta función también depende del número de nodos en el árbol. 
     *      En el peor caso, si el nodo a modificar está en el último nivel del árbol, se realizarán llamadas recursivas hasta llegar a ese nodo. 
     *      Si asumimos que el árbol tiene N nodos, hasta llegar al nodo a modificar, el coste será O(N), ya que cada nodo se procesa una vez.</li>
     *   
     *      <li>recorrido_anchura:  El coste de esta función también depende del número de nodos en el árbol. 
     *      En el peor caso, si el árbol tiene una estructura de árbol completo, es decir, todos los niveles excepto posiblemente el último nivel 
     *      están completamente llenos, se recorrerán todos los nodos. Si asumimos que el árbol tiene N nodos, el coste será O(N).</li>
     *  </ul>
     * 
     *  En resumen, el coste de los métodos privados es lineal, respecto a el número de nodos de 'procesadores_arbol'.
    */
};
#endif