# Tsela
## de NacioSystems:

Versión 1.0
Fecha: 29/10/2019

Este proyecto es un vehículo autónomo llamado Tesela, que es capaz de conducir sin piloto por una pista de _siguelineas_. Realizado por NacioSystems (O Milladoiro):

Es un proyecto que tenía pensado desde hace un par de años, al ver las competiciones de siguelienas en la Oshwdem Coruña, y ver que todos los vehículos giran sobre dos o cuatro ruedas, pero forzando la velocidad de un lado respecto del otro, cuando en la práctica, salvo los vehiculos con cadenas, todos los vehículos se mueven girando uno de los ejes, normalmente el delantero.

Realmente al ver el resultado se me ocurrió llamarle Nisan Patrol, pero ese nombre ya estaba pillado. Me acordé también de Nícola Tesla para ponerle el nombre y entonces se me ocurrió que la teselas fueron uno de los objetivos de la Oshwdem, así que me pareció muy apropiado el nombre de Tesela, Modelo 3, con Autopilot. :-)

- - -

###Introducción:
El chasis del vehículo está construido básicamente en madera, utilizando sobrante de madera de una caja de vino. Como motores utiliza dos micrometal que encontré perdidos y de los que desconozco su relación de reducción, aunque puedo decir que son muy potentes y poco veloces. Para controlar la velocidad de los motores utilizo un punte en H tipo L298N, que me permite regular la velocidad y el sentido de los dos motores. Por otra parte para leer la posición del vehículo respecto de la línea (negra) que debe seguir, utilizo una batería de cuatro sensores CNY70, puestos de modo transverlal a la línea. Todo el conjunto está controlado por un Arduino Nano montado sobre una placa de expansión. La gracia del vehículo, respecto de otros siguelíneas tradicionales, es que gira gracias a un eje directriz delantero movido por un microservo SG90. Se alimenta todo e conjunto a través de do baterías LiPo 18650 puestas en serie,con 8V de tensión nominal.

El vehículo se enciendo por un interruptor que da tensión a los motores y a la placa Arduino, iniciando el movimiento hacia adelante y leyendo lo sensores infrarrojos. En función de la señal que reciba de los sensores, en caso de no estar centrado sobre la línea, manda una señal al microservo de la dirección para corregir la posición y centrarse en la línea.

* _Foto Tsela_

Los sensores infrarrojos están montados sobre una placa improvisada, utlizando una tarjeta comercial tipo, numerados de izquierda a derecha del 1 al 4. Cuando el vehiculo está centrado los sensores centrales 2 y 3 estarían sobre la línea negra, devolviendo muy poca señal al sensor, mientras que el resto de los sensores, 1 y 4 estarían sobre el blanco de la pista, devolviendo mucha señal al sensor. El sensor sobre la pista puede estar en 8 posiciones distintas:
* 1 Sensor 1 en negro y resto en blanco. Vehículo muy desviado a la izquierda
* 2 Sensor 1 y 2 en negro y resto en blanco. Vehículo desviado a la izquierda
* 3 Sensor 2 en negro y resto en blanco. Vehículo ligeramente desplazado hacia la izquierda
* 4 Sensores 2 y 3 en negro y 1 y 2 en blanco. Vehículo centrado, posición ideal
* 5 Sensor 3 en negro y resto en blanco. Vehículo ligeramente desviado a la derecha
* 6 Sensor 3 y 4 en negro y resto en blanco. Vehículo desviado a la derecha
* 7 Sensor 4 en negro y resto en blanco. Vehículo muy desviado a la derecha.
* 8 Todos los sensores sobre blanco, fuera de pista

* _Foto Sensor en placa RV_

Conociendo la ubicación del vehículo sobre la pista, el sistema de control puede actuar sobre los motores y la dirección para corregir la posición, si es necesario, siendo los giros más cerrados cuanto más desviado está de la posición ideal cuando el vehículo está centrado.

Si el vehículo está centrado avanza recto a la máxima velocidad, pero cuando llega a una curva, detecta que es un giro por la posión de los sensores y decide reducir la velocidad y girar el eje delantero para corregir la posición.

Si la curva es muy cerrada y va muy rápido, detactará el cambio de dirección pero es posible que pierda la señal de la línea negra, situación fuera de pista, entonces mantendrá una velociad más reducida y la dirección girada totalmente hasta que recupere la linea y pueda seguir el camino.


###Materiales y materiales reciclados:
El vehículo utiliza los siguientes materiales reciclados, que se pueden visualizar en las fotos:
* Chasis totalmente de madera, de una vieja caja de vino
* La placa que soporta los sensores es una tarjeta comercial tipo tarjeta de crédito.
* Los ejes de la dirección son metálicos de un viejo camión de bomberos de juguete
* Las ruedas son de un viejo juguete Lego
* Parte del cableado está basado en líneas de pares telefónicos reutilizados
* Las baterías Lipo 18650 son recuperadas de un viejo portátil que iba al desguace
* Parte de la tornillería es de una vieja impresora HP Lajerjet que tambien se envió al desguace

* _Foto Maderas cortadas_

Otros materiales:

También se han utilizado piezas impresas en 3D, para hacer la dirección, puesto que no servía ninguna dirección adecuada para este vehículo. La dirección es diseñada totalmente por mi, para integrar el Servo SG90, los ejes de dirección metálicos disponibles y las ruedas de Lego. Otras piezas impresas son la caja soporte de las baterías, tambien diseñada por mi y las piezas soporte de los motores al chasis. Para las piezas impresas he utilizado nueva tornillería de métrica M3.

* _Toto Tsela sin carcasa

Materiales electrónicos:

* Arduino Nano
* Extension Board Arduino Nano
* Puente H L298N
* Microservo SG90
* 4 Sensores infrarrojos CNY70
* 2 Lipo 18650 de 3,7V


###Pista:
La pista está montada en un tablero de 2x2m2, de color blanco, en el que se traza una línea negra de 1,9cm de ancho, que será la que marque el circuito a recorrer.

El recorrido del circuito es cerrado, los puntos de salida y llegada son el mismo. Tendrá una longitud aproximada de 4 metros e incluye rectas y curvas de diferentes radios. La curva de menor radio no será inferior a los 125 mm, y la distancia mínima entre dos partes próximas del recorrido no será inferior a los 250 mm. Las medidas y recorrido del circuito no se darán a conocer hasta el comienzo de la prueba.

Los vehículos (robots) deberán completar un recorrido completo en el menor tiempo posible.

* _Foto Pista_


###Condiciones iniciales:
En el inicio de la competición el vehículo se sitúa centrado sobre la línea del circuito, en la dirección a recorrer. En el momento de saída deberá iniciar el recorrido en el menor tiempo posible sin salirse del circuito y recorriendolo completamente.


###Desplazamientos y giros:
Una vez puesto en marcha el vehículo inicia su movimiento a la máxima velocidad, manteniendo la dirección si está centrado. En el momento que detecta que no está centrado, inicia un giro del eje delantero, a través del Microservo SG90 para corregir su posición. Una vez se encuentra centrado de nuevo, el robot devuelve la dirección del eje delantero para continuar en línea recta.


###Programa:
El programa está realizado con el IDE Arduino, para su programación directa a través de cable USB. En la carpeta software se puede ver el programa comentado. El programa cuenta con una pestaña de "configuración.h", para ajustar los valores por defecto, que dependerán de los motores y sensores utilizados en cada caso, si son diferentes a los de esta construcción.


###Construcción:
El resultado final es la progresión de varias experiencias sobre el modelo inicial tabajando únicamente sobre un bastidor de madera, al que fui añadiendo modificaciones según iban apareciendo las compliaciones o para simplificar problemas. El primer vehiculo llevaba motores chinos sobre una plataforma de madera más larga, en la que fui acoplando ejes delanteros de giro de varios coches de juguete, accionados por un microservo y palancas de reenvío. 

Ante el fracaso continuo con el sistema de dirección, especialmente por las holguras y el corto ángulo de giro,  me propuse aprovechar parte de uno de los ejes que habia usado y construir un sistema delantero de direccion, utilizando FreeCad. El resultado espectacular. Un único inconveniente, el vehículo resuta muy largo y limita el ángulo de giro. Las primeras pruebas las hago sin sensores, moviendo el vehículo a través de un control por Bluetooth y comprobando su comportamiento con control manual. Primer objetivo reducir la longitud para mejorar el ángulo de giro, para llegar a los 12,5cm de radio de giro de la Oshwdem.

A esta segunda versión ya le incorpor todos los elementos electrónicos, incluyendo el sensor de lineas. Este sensor iba avanzado delante de eje de dirección, para anticiparse a las curvas. Despues de muchos ajustes, placa controladora, baterías, dirección, driver de motores, vemos que queda espacio para reducir más la longitud. Aparece un nuevo problema, en curvas cerradas, el sistema de dirección gira bien, pero la velocidad es muy alta y los motores no tienen la calidad suficiente para tener empuje con valores pequeños de PWM. En curvas cerradas el vehiculo se queda por falta de empuje o sale disparado fuera de la pista por mucha potencia en los motores. Decisión, cambiar motores.

En una nueva versión ya incorporo un soporte para las baterias impreso en 3D y diseñado en FreeCad (Gracias por tus microtutoriales Obijúan)

El cambio de motores supone tambien la necesidad de un sistema de acople a la carrocería. Se resuelve con un diseño en Freecad de nuevas piezas para imprimir en 3D. En esta versión tambien se comprueba la viabilidad de acercar el sensor para ponerlo debajo del tren delantero. El resultado es prometedor, el vehículo recorre perfectamente circuitos muy complejos sin salirse de la pista. 

A partir de aquí empiezo a construir la carrocería, dibujando directamente las medidas que tomo en el chasis sobre la madera y cortando con una sierra de calar. Encolo todo con pegamento para madera, lo lijo y lo pinto de color rojo con spray.


###Piezas impresas:
* Caja baterías
* Dirección eje delantero
* Soporte motores traseros


###Referencias:

### Autor:

**Ignacio Otero**



### Licencia:

Todos estos productos están liberados mediante Creative Commons Attribution-ShareAlike 4.0 International License.


