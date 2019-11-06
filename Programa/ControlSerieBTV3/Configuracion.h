

// Pines Botón de inicio / parada y claxon
#define CLAXON 9  // Pulsador para el claxon, puesto a pullup
#define BOTON  8  // Pulsador de inicio parada, puesto a pullup
                  // La lectura da siempre positivo, salvo que se pulse el botón
#define BUZZER 10  // Reservado para poner el altavoz del claxon
#define CONTROLir 12// Futuro control de los sensores por este pin

// Definición pines motores PWM
#define MDA 3  // Negro
#define MDB 5  // Blanco
#define MIA 11 // Violeta
#define MIB 6  // Negro

// Definición pines controles manuales y servo
// Pines sensores infrarrojos
#define SIRD2 A1
#define SIRD1 A2
#define SIRI1 A3
#define SIRI2 A4

#define BATERIA  A0  // Pin analógico para medición de batería. Divisor con dos resistencias de 10K
#define PinServo  4  // Salida control servo
#define central  85  // Es la configuraion del servo en posición central
#define margen   35  // Apertura lateral desde la posición central. Límite
#define retardo  20  // Posible retardo en los bucles

// Lecturas de línea
#define NEGRO 100    // Por debajo de 100 es color negro
#define BLANCO 500   // Mas de 500 (999) es blanco

#define V_MAX 250  // Va muy bien con 250 / 150 / 100
#define V_MED 200  // Tambien con 250 / 170 /150
#define V_MIN 150

// Otros parámetros de configuracion
#define NumLecturas 10 // Serán las lecturas para hacer la media
