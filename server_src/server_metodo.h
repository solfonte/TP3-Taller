#ifndef __METODO_H__
#define __METODO_H__
#include <string>

class Metodo{
  public:
    virtual std::string obtener_respuesta() = 0;
    Metodo() {}
    virtual ~Metodo() {}
};

class GetSinRecurso: public Metodo{
  private:
    std::string archivo;
  public:
    explicit GetSinRecurso(const std::string& archivo):
    archivo(archivo)
    {}
     std::string obtener_respuesta() override;
};

class GetConRecurso: public Metodo{
  private:
    bool recurso_existe;
    std::string contenido_recurso;
  public:
    GetConRecurso(bool recurso_existe,const std::string& contenido):
      recurso_existe(recurso_existe),
      contenido_recurso(contenido)
      {}
     std::string obtener_respuesta() override;
};

class PostSinRecurso: public Metodo{
  public:
    PostSinRecurso();
    std::string obtener_respuesta() override;
};

class PostConRecurso: public Metodo{
  public:
    PostConRecurso();
     std::string obtener_respuesta() override;
};

class MetodoInvalido: public Metodo{
  public:
    MetodoInvalido();
    std::string obtener_respuesta() override;
};

#endif
