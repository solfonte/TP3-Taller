# TP3-Taller

**Descripcion general del trabajo practico**  
Para el trabajo practico se implementaron las clases de Cliente y Servidor para encapsular los comportamientos de cada uno. El servidor se encarga de correr el hilo aceptador, y luego el hilo aceptador corre cada cliente. Cada hilo cliente se encarga de recibir y responder los mensajes del cliente con el cual tiene una conexion a traves de cada socket.   


**Comentarios adicionales**  
-Para sobrecargar al operador () se implemento que este llamara al metodo start() de los threads. Tanto al metodo start y el metodo run se los definio con visibilidad privada.  
-Para aplicar polimorfismo sobre la resolucion de las respuestas del servidor, se realizo una clase Metodo de la cual heredan las distintas opciones. Si bien se implementaron las clases de los metodos, definiendo en los nombres si tienen recurso o no, se implemento de esta manera para que cada clase concreta de cada metodo sepa como implementar su respuesta.  

**Diagrama de clases**  
![Alt Text](clasestp2.png)
