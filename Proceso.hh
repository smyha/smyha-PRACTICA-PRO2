/** @file Proceso.hh
 *  @brief Especificacion de la clase Proceso
*/

#ifndef PROCESO_HH 
#define PROCESO_HH

#ifndef NO_DIAGRAM
#include<iostream>
#endif

using namespace std;

/** @class Proceso
 *      @brief Representa un proceso (obj. 'Proceso')
 *  
 *      La clase Proceso representa un proceso, con la cúal se facilita su gestión. 
 *      Permite almacenar información relativa a un proceso, como su identificador,
 *      la cantidad de memoria estimada que va a necesitar para ejecutarse y el tiempo
 *      estimado de ejecución. 
*/


class Proceso {
    public:
    // ! Constructoras:

    /** @brief Creadora por defecto. Constructora de un proceso vacío. Se ejecuta automáticamente al declarar un proceso.
     *  \pre <em>cierto</em>
     *  \post El resultado es una proceso el cual sus atributos no han sido inicializados.
    */
    Proceso();
    
    /** @brief Constructor de un proceso. 
     *  \pre <em>idn_proceso >= 0</em> (identificador) , <em>mem_req >= 0</em> (memoria requerida), <em>tmp_ejc >= 0</em> (tiempo de ejecución).  
     *  \post El resultado es un proceso el cual sus atributos han sido inicializados.
    */
    Proceso(int idn_proceso, int mem_req, int tmp_ejc);

    // -----------------------------------------------------------------------------------------------------------------------------------------

    // ! Modificadoras (Setters):

    /** @brief Modificadora que se encarga de modificar el tiempo de ejecución del proceso.
     *  \pre <em>tmp</em> es la cantidad de tiempo que se va a sumar al tiempo de ejecución actual del proceso.
     *       Se asume que el proceso esta en ejecución en el procesador.
     *  \post El tiempo de ejecución del proceso se ha decrementado en <em>tmp</em>. Devuelve <em>false</em> si el tiempo todavia
     *        no se ha agotado, y en caso contrario, devuelve <em>true</em>.
    */
    bool modificar_tiempo_ejecucion(int tmp);

    // -----------------------------------------------------------------------------------------------------------------------------------------

    // ! Consultoras (Getters):     

    /** @brief Consultora (Getter) que devuelve el identificador del proceso.
        \pre <em>cierto</em>
        \post Devuelve el identificador del proceso consultado.
    */
    int consultar_identificador_proceso() const;

    /** @brief Consultora (Getter) que devuelve la cantidad de memoria estimada que va a necesitar para ejecutarse.
        \pre <em>cierto</em>
        \post Devuelve la cantidad de memoria estimada que va a necesitar para ejecutarse.
    */
    int consultar_memoria_requerida() const;    

    // -----------------------------------------------------------------------------------------------------------------------------------------

    // ! Lectura del proceso:
    
    /** @brief Método que se encarga de inicializar los atributos del proceso, dados unos datos por el canal standard de entrada.
     *  \pre Están disponibles por el canal estandard de entrada tres enteros no negativos.
     *  \post El parámetro implícito tiene los atributos leídos del canal estandard d'entrada.
    */
    void lectura_proceso();

    // -----------------------------------------------------------------------------------------------------------------------------------------

    // ! Escritura del proceso:

    /** @brief Método que imprime por pantalla la información del proceso.  
        \pre <em>cierto</em> El objeto Proceso ha sido creado correctamente.
        \post Se muestra por el canal standard de salida la información del proceso, que incluye su
    *         identificador, la cantidad de memoria estimada que va a necesitar
    *         para ejecutarse y el tiempo estimado de ejecución.
    */
    void imprimir_proceso() const;

        // -----------------------------------------------------------------------------------------------------------------------------------------

    private:

    // Conjunto información proceso
    int identificador_proceso;                                  // ? < Identificador del proceso 
    int memoria_requerida;                                      // ? < Cantidad de memoria requerida en un procesador
    int tiempo_ejecucion;                                       // ? < Tiempo estimado de ejecución en un procesador     

    /** @invariant Invariantes de la representación:
     * Inv: identificador_proceso > 0
     * Inv: memoria_requerida > 0
     * Inv: tiempo_ejecucion > 0
    */

};
#endif
