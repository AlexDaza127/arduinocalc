#include <Keypad.h>

const byte FILAS = 4;
const byte COLUMNAS = 4;
char keys[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'D'},
  {'4', '5', '6', 'C'},
  {'7', '8', '9', 'B'},
  {'*', '0', '#', 'A'}
};

byte pinesFilas[FILAS] = {2, 3, 4, 5};
byte pinesColumnas[COLUMNAS] = {6, 7, 12, 13};

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);
char TECLA, action;
long Num1, Num2, Number;
boolean result = false;

byte CERO[] = { 0x18, 0x24, 0x24, 0x24, 0x24, 0x18};
byte UNO[] = { 0x08, 0x18, 0x28, 0x08, 0x08, 0x3C};
byte DOS[] = { 0x18, 0x24, 0x24, 0x08, 0x10, 0x3C};
byte TRES[] = {0x18, 0x24, 0x08, 0x04, 0x24, 0x18};
byte CUATRO[] = {0x24, 0x24, 0x3C, 0x04, 0x04, 0x04};
byte CINCO[] = {0x3C, 0x20, 0x38, 0x04, 0x04, 0x38};
byte SEIS[] = {0x18, 0x24, 0x20, 0x38, 0x24, 0x18};
byte SIETE[] = {0x3C, 0x24, 0x04, 0x04, 0x04, 0x04};
byte OCHO[] = {0x18, 0x24, 0x18, 0x24, 0x24, 0x18};
byte NUEVE[] = { 0x18, 0x24, 0x1C, 0x04, 0x04, 0x18};
byte SUMA[] = { 0x00, 0x18, 0x3C, 0x3C, 0x18, 0x00};
byte RESTA[] = {0x00, 0x00, 0x3C, 0x3C, 0x00, 0x00};
byte DIVISION[] = { 0x00, 0x04, 0x08, 0x10, 0x20, 0x00};
byte MULTIPLICACION[] = {0x00, 0x24, 0x18, 0x18, 0x24, 0x00};
byte RESULTADO[] = {0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00};


void setup() {

  for (int j = 0; j < 6; j++)    ///Definimos todos los pines del arduino como salida
    pinMode(j, OUTPUT);

  for (int j = 20; j < 22; j++)    ///Definimos todos los pines del arduino como salida
    pinMode(j, OUTPUT);
  // put your setup code here, to run once:
  for (int j = 6; j < 20; j++)    ///Definimos todos los pines del arduino como salida
    pinMode(j, OUTPUT);

  Serial.begin(9600);

}
void SetChar(char p)
{
  int cantFill = 14;
  int cantCol = 12;
  Clear();
  for (int filas = 0; filas < 6; filas++)
  {
    digitalWrite( filas + cantFill , LOW) ; // Activamos la filasa para el barrido
    //byte F = N[filas] ;
    byte F = Selecciona( p, filas);

    for (int columnas = 7; columnas >= 0; columnas--)
    {
      digitalWrite(cantCol - columnas, LOW);   //Bajamos la columnasumna
      bool b = GetBit(F, columnas)  ;

      if (b) {
        digitalWrite( (cantCol + 1) - columnas, HIGH); //Levantamos la columnasumna, con su pin

      } else
        digitalWrite( (cantCol + 1) - columnas  , LOW); // Si 0, apagamos

    }                                    // Solo si b es 1
    digitalWrite( filas + cantFill , HIGH) ;          // Apagamos filasa antes de salir

  }
}
int next = -5;
bool GetBit( byte N, int posicion)
{ // posicion = 7 6 5 4 3 2 1 0
  int b;
  b = N >> posicion;//+next;// Shift bits
  b = b & 1 ;// coger solo el ultimo bit

  return b ;
}

void Clear()
{
  for (int j = 4; j < 15; j++) // Valores de los pines de columnasumna
    digitalWrite(j, LOW); // Todos apagados

  for (int k = 16 ; k < 22 ; k++)
    digitalWrite(k, HIGH);  // Todas las filasas cortadas
}

byte Selecciona( char c, byte filas) {
  if (c == '0')           return (CERO[filas]) ;
  if (c == '1')           return (UNO[filas]) ;
  if (c == '2')           return (DOS[filas]) ;
  if (c == '3')           return (TRES[filas]) ;
  if (c == '4')           return (CUATRO[filas]) ;
  if (c == '5')           return (CINCO[filas]) ;
  if (c == '6')           return (SEIS[filas]) ;
  if (c == '7')           return (SIETE[filas]) ;
  if (c == '8')           return (OCHO[filas]) ;
  if (c == '9')           return (NUEVE[filas]) ;
  if (c == 'S')           return (SUMA[filas]) ;
  if (c == 'R')           return (RESTA[filas]) ;
  if (c == 'D')           return (DIVISION[filas]) ;
  if (c == 'M')           return (MULTIPLICACION[filas]) ;
  if (c == 'T')           return (RESULTADO[filas]) ;

}


String s;
long cant, cantU, cantD;
bool resultado, turno;
void loop() {

  // put your main code here, to run repeatedly:
  TECLA = teclado.getKey();
  if (TECLA != NO_KEY)
    detectarBotones();

  if (result == true)
    calcularResul();

  impresionResultados();
}

void detectarBotones()
{

  if (TECLA == '*') //If cancel Button is pressed
  { resultado = true;
    Number = Num1 = Num2 = 0;
    s = "";
    result = false;

  }

  if (TECLA == '1') //If Button 1 is pressed
  { resultado = true;
    if (Number == 0) {
      Number = 1;
      s = (String)Number;
    }
    else {
      Number = (Number * 10) + 1; //Pressed twice
      resultado = false;
      s = (String)Number;
    }
  }

  if (TECLA == '4') //If Button 4 is pressed
  { resultado = true;
    if (Number == 0) {
      Number = 4;
      s = (String)Number;
    } else {
      Number = (Number * 10) + 4; //Pressed twice
      resultado = false;
      s = (String)Number;
    }
  }

  if (TECLA == '7') //If Button 7 is pressed
  { resultado = true;
    if (Number == 0) {
      Number = 7;
      s = (String)Number;
    }
    else {
      Number = (Number * 10) + 7; //Pressed twice
      resultado = false;
      s = (String)Number;
    }
  }


  if (TECLA == '0')
  { resultado = true;
    if (Number == 0) {
      Number = 0;
      s = (String)Number;
    }
    else {
      Number = (Number * 10) + 0; //Pressed twice
      resultado = false;
      s = (String)Number;
    }
  }

  if (TECLA == '2') //Button 2 is Pressed
  { resultado = true;
    if (Number == 0) {
      Number = 2;
      s = (String)Number;
    }
    else {
      Number = (Number * 10) + 2; //Pressed twice
      resultado = false;
      s = (String)Number;
    }
  }

  if (TECLA == '5')
  { resultado = true;
    if (Number == 0) {
      Number = 5;
      s = (String)Number;
    }
    else {
      Number = (Number * 10) + 5; //Pressed twice
      resultado = false;
      s = (String)Number;
    }
  }

  if (TECLA == '8')
  { resultado = true;
    if (Number == 0) {
      Number = 8;
      s = (String)Number;
    }
    else {
      Number = (Number * 10) + 8; //Pressed twice
      resultado = false;
      s = (String)Number;
    }
  }


  if (TECLA == '#')
  { resultado = false;
    Num2 = Number;
    result = true;
  }

  if (TECLA == '3')
  { resultado = true;
    if (Number == 0) {
      Number = 3;
      s = (String)Number;
    }
    else {
      Number = (Number * 10) + 3; //Pressed twice
      resultado = false;
      s = (String)Number;
    }
  }

  if (TECLA == '6')
  { resultado = true;
    if (Number == 0) {
      Number = 6;
      s = (String)Number;
    }
    else {
      Number = (Number * 10) + 6; //Pressed twice
      resultado = false;
      s = (String)Number;
    }
  }

  if (TECLA == '9')
  { resultado = true;
    if (Number == 0) {
      Number = 9;
      s = (String)Number;
    }
    else {
      Number = (Number * 10) + 9; //Pressed twice
      resultado = false;
      s = (String)Number;
    }
  }

  if (TECLA == 'A' || TECLA == 'B' || TECLA == 'C' || TECLA == 'D') //Detecting Buttons on Column 4
  {
    Num1 = Number;
    Number = 0;
    if (TECLA == 'A')
    {
      s = "S";
      action = '+';
    }
    if (TECLA == 'B')
    {
      s = "R";
      action = '-';
    }
    if (TECLA == 'C')
    {
      s = "M";
      action = '*';
    }
    if (TECLA == 'D')
    {
      s = "D";
      action = '/';
    }

    delay(100);
  }

}

void calcularResul()
{
  if (action == '+') {
    Number = Num1 + Num2;
    s = "T"+(String)Number;
  }

  if (action == '-') {
    Number = Num1 - Num2;
    s = "T"+(String)Number;
  }

  if (action == '*') {
    Number = Num1 * Num2;
    s = "T"+(String)Number;
  }

  if (action == '/') {
    Number = Num1 / Num2;
    s = "T"+(String)Number;
  }
}


void impresionResultados() {
  //String s = "0123456789SRDM" ; /////////////////////////////AQUI SE ESCRIBE EL TEXTO A MOSTRAR
  //String s = "0";
  //String s = "T";
  //String s = "M";
  int l = s.length();      // Calcula la longitus de s
  for ( int n = 0; n < l; n++ )
  {
    long t = millis();
    char c = s[n];

    if (resultado == true) {
      while ( millis() < t + 10) { ///Se difine el tiempo de cambio de letra.
        SetChar(c);

      }
    }
    if (resultado == false) {
      while ( millis() < t + 500) { ///Se difine el tiempo de cambio de letra.
        SetChar(c);
      }
    }

  }
}
