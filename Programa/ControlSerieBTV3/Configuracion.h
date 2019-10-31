

// Botón de inicio / parada
#define BOTON 8 // Pulsador de inicio parada, puesto a pullup
                // La lectura da siempre positivo, salvo que se pulse el botón

// Definición pine motores
#define MDA 3  // Negro
#define MDB 5  // Blanco
#define MIA 11 // Violeta
#define MIB 6  // Negro

// Definición pines controles manuales y servo
#define PinDir   A0  // Entrada analógica del control de velocidad
#define PinVel   A1  // Entrada analógica del control de velocidad
#define PinServo  4  // Salida control servo
#define central  85  // Es la configuraion del servo en posición central
#define margen   35  // Apertura lateral desde la posición central. Límite
#define retardo  20  // Posible retardo en los buclesÇ

// Lecturas de línea
#define NEGRO 100    // Por debajo de 100 es color negro
#define BLANCO 500   // Mas de 500 (999) es blanco

#define V_MAX 250  // Va muy bien con 250 / 150 / 100
#define V_MED 200  // Tambien con 250 / 170 /150
#define V_MIN 150

// Otros parámetros de configuracion
#define NumLecturas 10 // Serán las lecturas para hacer la media
