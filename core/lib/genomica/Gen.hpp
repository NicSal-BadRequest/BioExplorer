/*
    Biblioteca para definir una clase Gen que maneje la informacion, 
    metadatos de BBDD, secuencia, asociaciones de elementos subgeneticos,
    e interacciones genicas.
*/

#include <string>
#include <map>
#include <vector>


// Tipos abstractos estrictos para Pattern Matching

enum class TipoSubGenetico {
    Promotor,
    UTR_5,
    ORF,
    UTR_3,
    Terminador,
    Exon,
    Intron,
    Enhancer,
    Caja,
    RBS,
    Kozak,
    Sitio_Regulacion_Epi,
    Sitio_Regulacion_RNAi,
    Sitio_FT
};

enum class NivelRegulatorio{
    Genico,
    Epigenico,
    Transcripcional,
    Post_Transcripcional,
    Traduccional,
    Post_Traduccional,
    Proteico,
    Metabolico
};

enum class TipoInteraccion {
    Activacion,
    Inhibicion,
    Fosforilacion,
    Desfosforilacion,
    Metilacion,
    Acetilacion,
    Ubiquitinacion,
    Binding,
    Catalisis
};

// Definido segun tipo de transcrito y la funcion del mismo
enum class TipoGen {
    Proteico, //ARNm
    ARN_Ribosomal, //ARNr
    ARN_Transferencia, //ARNt
    MicroARN, //microARN
    LncARN, //lncARN
    ARN_Nuclear, // ARNpn
    ARN_Nucleolar, //ARNpno
    ARN_Piwi, // ARNpiwi
    ARN_Enhancer, //ARNe
    Pseudogen
};

class SubGenetico {
private:
    TipoSubGenetico tipo;
    std::string nombre;
    Secuencia secuencia;

    // Map interno para elementos que tienen "subcosas"
    // Ej: Promotor -> {"Caja_TATA": secuencia, "Caja_CAAT": secuencia}
    // Ej: ORF -> {"exon1": secuencia, "intron1": secuencia}
    std::map<std::string, std::puntero_comun<SubGenetico>> subelementos;

public:
    SubGenetico(TipoSubGenetico t, 
                const std::string& n, 
                const std::string& ruta_seq,
                size_t lon);
    TipoSubGenetico genTipo() const;
    const std::string& getNombre() const;
    const Secuencia& getSecuencia() const;

    void agregarSubElemento(const std::string& clave,
                            std::shared_ptr<SubGenetico> elem);

    std::shared_ptr<SubGenetico> obtenerSubElemento(const std::string& clave) const;

    const std::map<std::string, std::shared_ptr<SubGenetico>>& getSubElementos() const;
};


class Gen{
protected:
    std::string ID; //Cambiar por un Serialize interno
    std::string nombre;
    std::string numAccesoNCBI;
    std::string numAccesoUniprot;
    std::string simbolo;
    std::string version;
    std::string organismo;
    std::string coordenadasGenomicas;
    std::<string> tipoRegulacion; // Mas que string que sea un Array de Tipo abstracto definido estricto.
    std::string tipoGen; // Idem , cambiar a un tipo estricto como el anterior que permita pattern matchin o similar.


    /*
    - Una estructura que contenga la secuencia completa o acceso parcial si se lo requiere
    - Un Map que tenga los elementos subgeneticos . Por ejemplo, por clave promotor y por valor un diccionario 
    que contenga por clave el nombre de la caja reguladora y por valor su secuencia; lo mismo para 5'UTR con sus propios subelementos, etc
    - Una estructura tipo grafo de interacciones proteicas 
    - Una estructura tipo grafo de interacciones genica (por ejemplo la proteina reguladora del operon Lac 
    tendria conexion o una flecha en un sentido con todos los genes que tengan en el Map de los elementos subgeneticos un
    oLac para ser regulados por dicha proteina).
    - tipoRegulacion podria ser un Array con un Map y un grafo que para cada nivel de posible regulacion
    ya sea genica, epigenica, transcrita, proteica, etc, guarda un booleano e indica al menos el numero de acceso
    del gen o molecula que lo regula.
    */ 

}