#ifndef __METODO_H__
#define __METODO_H__
#include <string>

class Metodo{
  public:
    virtual std::string obtener_respuesta() = 0;
    Metodo();//deberia borrarlo
    virtual ~Metodo() {} 
};

class GetSinRecurso: public Metodo{
  private:
    std::string archivo;
  public:
    GetSinRecurso(std::string archivo):
    archivo(archivo)
    {}
     std::string obtener_respuesta() override;
};

class GetConRecurso: public Metodo{
  public:
    GetConRecurso();
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
