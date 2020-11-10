# TP3-Taller

**Descripcion general del trabajo practico**  
Para el trabajo practico se implementaron las clases de Cliente y Servidor para encapsular los comportamientos de cada uno. El servidor se encarga de correr el hilo aceptador, y luego el hilo aceptador corre cada cliente. Cada hilo cliente se encarga de recibir y responder los mensajes del cliente con el cual tiene una conexion a traves de cada socket.   

**Clase Recursos_protegidos**  
Esta clase fue implementada con el fin de encapsular todos los datos accedidos en una clase protegida. Encapsula tanto el mapa de recursos, al cual podria acceder cualquiera de los hilos clientes, ademas de encapsular la apertura del archivo root ingresado al ejecutar el servidor, ya que multiples hilos tambien podrian necesitar obtener su contenido e intentarian abrir este archivo en cualquier momento.  

**Comentarios adicionales**  
-Para sobrecargar al operador () se implemento que este llamara al metodo start() de los threads. Tanto al metodo start y el metodo run se los definio con visibilidad privada.  
-Para aplicar polimorfismo sobre la resolucion de las respuestas del servidor, se realizo una clase Metodo de la cual heredan las distintas opciones. Si bien se implementaron las clases de los metodos, definiendo en los nombres si tienen recurso o no, se implemento de esta manera para que cada clase concreta de cada metodo sepa como implementar su respuesta.  
-Cuando se recibe un GET/ sin recurso, si el archivo root no puede ser abierto por el programa, se muestra un mensaje de error para no cortar el flujo del programa.  

**Diagrama de clases**  
![Alt Text](clasestp3.png)  
