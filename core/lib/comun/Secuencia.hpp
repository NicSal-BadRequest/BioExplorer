// Clase Secuencia para Lazy Loading de secuencias geneticas o genomicas

#include <string>
#include <memory>
#include <optional>
#include <fstream>

class Secuencia {
private:
    std::string ruta_archivo;
    mutable std::optional<std::string> secuencia_cache;
    size_t longitud;

public:
    Secuencia(const std::string& ruta, size_t longitud);

    // Para Carga completa (lazy)
    const std::string& obtener() const;

    // Para acceso parcial sin cargar todo
    std::string obtenerSubSecuencia(size_t inicio, size_t fin) const;

    size_t getLongitud() const;

private:
    void cargarDesdeArchivo() const;   
}