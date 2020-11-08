#ifndef __RECURSOS_PROTEGIDOS_H__
#define __RECURSOS_PROTEGIDOS_H__

#include <map>
#include <string>

class Recursos_protegidos{
  private:
    std::string root_file;
    std::map<std::string,std::string> recursos;
  public:
    Recursos_protegidos(const std::string& root_file):
      root_file(root_file)
      {}
    std::string get_contenido_recurso(const std::string& recurso) const;
    void guardar_recurso(std::string& recurso,std::string& contenido);
    std::string get_archivo_root();
};

#endif
