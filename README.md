# Tsela
## de NacioSystems:

Versión 1.3
Fecha: 31/10/2019

Este proyecto es un vehículo autónomo llamado **Tsela** (Tesela), que es capaz de conducir sin piloto por una pista de *siguelineas*. Realizado por NacioSystems (O Milladoiro):

Es un proyecto que tenía pensado desde hace un par de años, al ver las competiciones de siguelienas en la **Oshwdem Coruña**, y ver que todos los vehículos giran sobre dos o cuatro ruedas, pero forzando la velocidad de un lado respecto del otro, cuando en la práctica, salvo los vehículos con cadenas, todos los vehículos se mueven girando uno de los ejes, normalmente el delantero, haciendo coincidir la direccion de las ruedas delanteras con la secante de la curva.

Realmente al ver el resultado final, y las aprariencias del modelo, se me ocurrió llamarle Nisan Patrol, pero ese nombre ya estaba pillado. Me acordé también de Nicola Tesla, un pionero de los generadores eléctricos, pero el nombre tambien estaba pillado. Entonces recordé que las teselas, esos elementos geométricos que forman parte de la naturaleza, que fueron uno de los retos de la Oshwdem hace un par de años, podrían ser la clave. Así que me pareció muy apropiado el nombre de Tesela. Para abreviar, _**Tsela, Modelo 3, con Autopilot**_. :-)


- - -

### Introducción:

El chasis del vehículo está construido básicamente en madera, utilizando sobrante de madera de una caja de vino. Como motores utiliza dos micrometal que encontré perdidos y de los que desconozco su relación de reducción, aunque puedo decir que son muy potentes y poco veloces. Para controlar la velocidad de los motores utilizo un *driver* puente en H tipo **L298N**, que me permite regular la velocidad y el sentido de los dos motores. Por otra parte para leer la posición del vehículo respecto de la línea (negra) que debe seguir, utilizo una batería de cuatro sensores **CNY70**, puestos de modo transversal a la línea. Todo el conjunto está controlado por un **Arduino Nano** montado sobre una placa de expansión. La gracia del vehículo respecto de otros siguelíneas tradicionales, a parte de su bonito diseño totalmente artesano, es que gira gracias a un eje directriz delantero movido por un microservo **SG90**. Se alimenta todo e conjunto a través de do baterías **LiPo 18650** puestas en serie, con 8V de tensión nominal.

El vehículo se enciendo por un interruptor que da tensión al *driver* de los motores y a la placa Arduino. La marcha se inicia pulsando un botón que pone el vehículo en estado *Autopilot*, iniciando el movimiento hacia adelante y leyendo lo sensores infrarrojos. En función de la señal que reciba de los sensores, en caso de no estar centrado sobre la línea, manda una señal al microservo de la dirección para corregir la posición y centrarse en la línea.

A través del puerto serie permite la **conexión remota por _Bluetooth_** y la gestión del vehículo, desactivando el *Autopilot* previamente. En caso de estar activado el _Autopilot_ no seguirá las instrucciones del piloto, salvo que no encuentre una línea a seguir, en ese caso, si encuentra una línea a seguir, tendrá prefrencia el seguimiento de la línea.

Si se toma el control por Bluetooth (9600,N,1), el Autopilot se activa enviando el caracter 'P'. Es recomendable poner la aplicacion Bluetooth en modo repetitivo, con lo que se consigue girar progresivamente o acelerar mientras se pulsa botón correspondiente de la app. (ejemplo Bluetooth spp pro). Otras funciones implementadas para el contros serie son:
* 'A' Avanza más rápido, acelera
* 'R' Reduce la velocidad, decelera
* 'D' Mueve la dirección hacia la derecha, muy poco respecto de la posicióin actual
* 'I' Mueve la dirección hacia la izquierda, muy poco respecto de la posición actual
* 'P' Cada pulsación cambia entre modo _Autopilot_ o modo manual
* '0' Para los motores y pone la dirección recta
* 'C' Toca el claxon

![Imagen Tesla](https://github.com/NacioSystems/Tsela/blob/master/Imagenes/IMG_20191029_220630_952.jpg "Tesla en construcción")

Los sensores infrarrojos están montados sobre una placa improvisada, utilizando una tarjeta comercial tipo, numerados de izquierda a derecha del 1 al 4. Cuando el vehículo está centrado los sensores centrales 2 y 3 estarían sobre la línea negra, devolviendo muy poca señal al sensor, mientras que el resto de los sensores, 1 y 4 estarían sobre el blanco de la pista, devolviendo mucha señal al sensor. El sensor sobre la pista puede estar en 8 posiciones distintas:
* 1)- Sensor 1 en negro y resto en blanco. Vehículo muy desviado a la izquierda
* 2)- Sensor 1 y 2 en negro y resto en blanco. Vehículo desviado a la izquierda
* 3)- Sensor 2 en negro y resto en blanco. Vehículo ligeramente desplazado hacia la izquierda
* 4)- Sensores 2 y 3 en negro y 1 y 4 en blanco. Vehículo centrado, posición ideal
* 5)- Sensor 3 en negro y resto en blanco. Vehículo ligeramente desviado a la derecha
* 6)- Sensor 3 y 4 en negro y resto en blanco. Vehículo desviado a la derecha
* 7)- Sensor 4 en negro y resto en blanco. Vehículo muy desviado a la derecha.
* 8)- Todos los sensores sobre blanco, fuera de pista

![Placa receptores infrarrojos](https://github.com/NacioSystems/Tsela/blob/master/Imagenes/IMG_20191010_172056_005.jpg "Batería de sensores infrarrojos")

![Esquema conexionado sensores infrarrojos](https://github.com/NacioSystems/Tsela/blob/master/Imagenes/Esquema Conexion CNU70.JPG "Esquema de conexionado")

Conociendo la ubicación del vehículo sobre la pista, el sistema de control puede actuar sobre los motores y la dirección para corregir la posición, si es necesario, siendo los giros más cerrados cuanto más desviado está de la posición ideal, que sería cuando el vehículo está centrado.

Si el vehículo está centrado avanza recto a la máxima velocidad, pero cuando llega a una curva, detecta que es un giro por la posición de los sensores y decide reducir la velocidad y girar el eje delantero para corregir la posición.

Si la curva es muy cerrada y va muy rápido, detectará el cambio de dirección pero es posible que pierda la señal de la línea negra, lo que sería una situación fuera de pista, entonces mantendrá una velocidad más reducida y la dirección girada totalmente hasta que recupere la línea y pueda seguir el camino.


### Materiales y materiales reciclados:
El vehículo utiliza los siguientes materiales reciclados, que se pueden visualizar en las fotos:
* Chasis y bastidor totalmente de madera, de una vieja caja de vino
* La placa que soporta los sensores es una tarjeta comercial tipo tarjeta de crédito.
* Los ejes de la dirección son metálicos de un viejo camión de bomberos de juguete
* Las ruedas son de un _quad_ Lego en desuso
* Parte del cableado está basado en líneas de pares telefónicos reutilizados y cable bililar de audio
* Las baterías Lipo 18650 son recuperadas de un viejo portátil que iba al desguace
* Parte de la tornillería es de una vieja impresora HP Lajerjet que tambien se envió al desguace

![Foto Maderas cortadas](https://github.com/NacioSystems/Tsela/blob/master/Imagenes/IMG_20191029_194325_094.jpg "Preparando la carrocería")

Otros materiales:

También se han utilizado piezas impresas en 3D, para hacer la dirección, puesto que no servía ninguna dirección adecuada para este vehículo. La dirección es diseñada totalmente por mi, para integrar el Servo SG90, los ejes de dirección metálicos disponibles y las ruedas de Lego. Otras piezas impresas son la caja soporte de las baterías, también diseñada por mi y las piezas soporte de los motores al chasis. Para las piezas impresas he utilizado nueva tornillería de métrica M3.

![Diseño sistema dirección](https://github.com/NacioSystems/Tsela/blob/master/Imagenes/Modelo%20Eje%20Delantero.JPG "Eje delantero")


![Foto Tsela sin carcasa](https://github.com/NacioSystems/Tsela/blob/master/Imagenes/IMG_20191012_210451_012.jpg "Prototipo 2")

Materiales electrónicos:

* Arduino Nano
* Extension Board Arduino Nano
* Puente H L298N
* 2 Micrometal Gear. Micromotores 6V
* Microservo SG90
* 4 Sensores infrarrojos CNY70
* 2 Lipo 18650 de 3,7V
* 2 pulsadores y un micorinterruptor
* Buzzer
* Algunas resistencias para la polarización de los CNY70 y la medición del estado de las baterías (sin implementar por A0)
* Otro pequeño material como bornas para la conexion de la batería y PCB prototipo para el montaje de interruptor y botones.


### Pista:
La pista del circuito a recorrer está montada en un tablero de 2x2m2, de color blanco, en el que se traza una línea negra de 1,9cm de ancho, que será la que marque el circuito a recorrer.

El recorrido del circuito es cerrado, los puntos de salida y llegada son el mismo. Tendrá una longitud aproximada de 4 metros e incluye rectas y curvas de diferentes radios. La curva de menor radio no será inferior a los 125 mm, y la distancia mínima entre dos partes próximas del recorrido no será inferior a los 250 mm. Las medidas y recorrido del circuito no se darán a conocer hasta el comienzo de la prueba.

Los vehículos (robots) deberán completar un recorrido completo en el menor tiempo posible.

![Foto Pista](https://github.com/NacioSystems/Tsela/blob/master/Imagenes/PistaTipo.jpg "Modelo Pista")


### Condiciones iniciales:
En el inicio de la competición el vehículo se sitúa centrado sobre la línea del circuito, en la dirección a recorrer. El interruptor de encendido debe estar en **ON** y en el momento de salida habrá que iniciar el camino pulsando el botón de *Autopilot*. Deberá realizar el recorrido en el menor tiempo posible sin salirse del circuito y recorriéndolo completamente. Una vez terminado el recorrido se puede desactivar el modo _Autopilot_ pulsando nuevamente en el botón correspondiente, o a través de Bluetooth de ser el caso.


### Desplazamientos y giros:
Una vez puesto en marcha el vehículo inicia su movimiento a la máxima velocidad, manteniendo la dirección si está centrado. En el momento que detecta que no está centrado, inicia un giro del eje delantero, a través del Microservo SG90 para corregir su posición. Una vez se encuentra centrado de nuevo, el robot devuelve la dirección del eje delantero para continuar en línea recta.


### Programa:
El programa está realizado con el IDE Arduino, para su programación directa a través de cable USB. En la carpeta software se puede ver el programa comentado. El programa cuenta con una pestaña de _"configuracion.h"_, en donde está el _pineado_ para las conexiones con el Arduino (sensores, microservo, botones, buzzer) para ajustar los valores por defecto, que dependerán de los motores y sensores utilizados en cada caso, si son diferentes a los de esta construcción. El programa está estructurado y comentado con lo que resulta fácil su comprensión, mantenimiento y modificación.


### Construcción:
El resultado final es la progresión de varias experiencias sobre el modelo inicial trabajando únicamente sobre un bastidor de madera, al que fui añadiendo modificaciones según iban apareciendo las complicaciones o para simplificar problemas. El primer vehículo llevaba motores chinos sobre una plataforma de madera más larga, en la que fui acoplando ejes delanteros de giro de varios coches de juguete, accionados por un microservo y palancas de reenvío. 

Ante el fracaso continuo con el sistema de dirección, especialmente por las holguras y el corto ángulo de giro,  me propuse aprovechar parte de uno de los ejes de un juguete que había usado para construir un nuevo sistema delantero de dirección, utilizando _FreeCad_. El resultado espectacular. Un único inconveniente, el vehículo resulta muy largo y limita el ángulo de giro. Las primeras pruebas las hago sin sensores, moviendo el vehículo a través de un control por Bluetooth y comprobando su comportamiento con control manual. Primer objetivo reducir la longitud del bastidor para mejorar el ángulo de giro, para llegar a los 12,5cm de radio de giro de la Oshwdem.

A esta segunda versión ya le incorporo todos los elementos electrónicos, incluyendo el sensor de líneas. Este sensor iba situado muy avanzado delante de eje de dirección, para anticiparse a las curvas. Después de muchos ajustes, placa controladora, baterías, dirección, driver de motores, vemos que queda espacio para reducir más la longitud del bastidor. Aparece un nuevo problema, en curvas cerradas, el sistema de dirección gira bien, pero la velocidad es muy alta y los motores no tienen la calidad suficiente para mantener el empuje con valores pequeños de PWM. En curvas cerradas el vehículo se queda por falta de empuje o sale disparado fuera de la pista por mucha potencia en los motores. Decisión, cambiar motores.

En una nueva versión ya incorporo un soporte para las baterías impreso en 3D y diseñado en _FreeCad_ **(Gracias por tus microtutoriales Obijúan)**

![Foto portabaterías LiPo](https://github.com/NacioSystems/Tsela/blob/master/Imagenes/Soporte%20Baterias%20Lipo.png "Portabaerías")

El cambio de motores supone también la necesidad de un sistema de acople a la carrocería. Se resuelve con un diseño en _Freecad_ de nuevas piezas que abrazan lon motores al bastidor de madera y permiten la incorporación de amortiguadores, listas para imprimir en 3D. En esta versión también se comprueba la viabilidad de acercar el sensor para ponerlo debajo del tren delantero. El resultado es prometedor, el vehículo recorre perfectamente circuitos muy complejos sin salirse de la pista. 

![Nuevo Tesela](https://github.com/NacioSystems/Tsela/blob/master/Imagenes/IMG_20191029_172438_377.jpg "Nuevo Tsela")

A partir de aquí empiezo a construir la carrocería, dibujando directamente las medidas que tomo en el chasis sobre la madera y cortando con una sierra de calar. Unimos las piezas con cola blanca para madera, lo lijo y lo pinto de color rojo con spray.

![Foto chasis en construcción](https://github.com/NacioSystems/Tsela/blob/master/Imagenes/IMG_20191029_220701_045.jpg "Piezas madera cortada")

Se incluyen en los archivos _FreeCad_ el diseño de la carrocería en 3D, por si alguien quiere ver las dimensiones de las piezas o imprimirla en material plástico en vez de recortar madera.
![Diseño carrocería](https://github.com/NacioSystems/Tsela/blob/master/Imagenes/Captura%20de%20pantalla%202019-10-30%2022.52.08.png "Carrocería")


### Piezas impresas:
* Caja baterías
* Dirección eje delantero
* Soporte motores traseros

### Pendiente:
En este momento tengo pendiente de incorporar dos funcionalidades:
* Medir el estado de las baterías LiPo 18650, para visar del cambio cuando la tensión baja de 3.7V
* Incorporar un Buzzer para hacer de claxon, a través de Bluetooth o por pulsación del segundo botón
* Incorporar luces *LED* de posición delanteras (blancas) y traseras (rojas), así como de dirección (intermitencias amarillas)


### Referencias:
* *[Página Web **OSHWDEM**][9]*

* *[Tutorial para construir un robot siguelineas con material reciclado][1]*

* *[Arduino Nano][2]*

* *[Extension Shield Arduino Nano en Amazon][3]*

* *[Driver motores, puente H L298N en Amazon][4]*

* *[Micrometal Gear Motor en BricoGeek][5]*

* *[Microservo SG90 en PC Componentes][6]*

* *[Sensor infrarrojos CNY70 en Amazon][7]*

* *[Baterías Lipo 18650 en Alibaba][8]*


### Autor:

**Ignacio Otero**


### Licencia:

Todos estos productos están liberados mediante Creative Commons Attribution-ShareAlike 4.0 International License.

[1]: https://todohacker.com/tutoriales/tutorial-robot-siguelineas
[2]: https://store.arduino.cc/arduino-nano
[3]: https://www.amazon.es/Ociodual-ATmega328P-Extension-Compatible-Arduino/dp/B07FN2Z5K7/ref=sr_1_7?keywords=Arduino+Nano+Shield&qid=1572508808&sr=8-7
[4]: https://www.amazon.es/HarmonyHappy-L298N-Motor-Drive-Modulo/dp/B07V7DHC2F/ref=sr_1_2_sspa?adgrpid=58915550391&gclid=Cj0KCQjwjOrtBRCcARIsAEq4rW7nMH2KA9twb-7bBBSOtDHfWDAwWROMDDYi8UgLknAD3hGYtXTghWIaAq14EALw_wcB&hvadid=275375934640&hvdev=c&hvlocphy=20272&hvnetw=g&hvpos=1t1&hvqmt=e&hvrand=14673444293332309264&hvtargid=kwd-305755956612&hydadcr=11860_1753010&keywords=puente+h+l298n&qid=1572508864&sr=8-2-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExVEVMWUpaOVRWUzBFJmVuY3J5cHRlZElkPUEwMTEwMDg4MVVBUE4xQTlZNzEwSCZlbmNyeXB0ZWRBZElkPUEwNjY4NzcxMjhLTjJRNVNNWVg3RiZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=
[5]: https://tienda.bricogeek.com/motores/113-motor-micro-metal-lp-con-reductora-10-1.html?gclid=Cj0KCQjwjOrtBRCcARIsAEq4rW414ujdRvTcawPlYSsHrevqkNvZurT0J92hZpU_B8HwZAMc4b-R4zYaAlZHEALw_wcB
[6]: https://www.pccomponentes.com/servo-sg90-micro-servo-9g-compatible-con-arduino?gclid=Cj0KCQjwjOrtBRCcARIsAEq4rW79ytf_hkwBZFFgm8VT65IvFSeHm6rW3BJJC8ZQcVMIFY1y7Rm7s58aAhJQEALw_wcB
[7]: https://www.amazon.es/s?k=cny70&adgrpid=59837770927&gclid=Cj0KCQjwjOrtBRCcARIsAEq4rW7nGRUqLJyFEBINF4V5HhXnWCjw_Tyta8sMNxcH3XCZ3p53EwSo-q8aAtb9EALw_wcB&hvadid=275348760401&hvdev=c&hvlocphy=20272&hvnetw=g&hvpos=1t1&hvqmt=e&hvrand=12513185469951307096&hvtargid=kwd-332007787404&hydadcr=10283_1779472&tag=hydes-21&ref=pd_sl_54ma8e90ll_e
[8]: https://www.alibaba.com/product-detail/Best-Quality-Of-ISR-Lithium-Rechargeable_60779827115.html?spm=a2700.7735675.normalList.5.773d241cja7gLd&s=p
[9]: https://oshwdem.org/




