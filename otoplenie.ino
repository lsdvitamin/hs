#include  <LiquidCrystal.h> //подключаем библиотеку экрана.

#define B 3950 // B-коэффициент
#define SERIAL_R 95000 // сопротивление последовательного резистора, 102 кОм
#define THERMISTOR_R 100000 // номинальное сопротивления термистора, 100 кОм
#define NOMINAL_T 25 // номинальная температура (при которой TR = 100 кОм)

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int button;  //вводим числовые значения для кнопок
const int BUTTON_NONE   = 0; //присваиваем постоянное значение для BUTTON_NONE 
const int BUTTON_RIGHT  = 1; //присваиваем постоянное значение для BUTTON_RIGHT
const int BUTTON_UP     = 2; //присваиваем постоянное значение для BUTTON_UP
const int BUTTON_DOWN   = 3; //присваиваем постоянное значение для BUTTON_DOWN 
const int BUTTON_LEFT   = 4; //присваиваем постоянное значение для BUTTON_LEFT
const int BUTTON_SELECT = 5; //присваиваем постоянное значение для BUTTON_SELECT
const byte tempHWSPin = A1;
const byte tempHSPin = A2;

void setup() {
    Serial.begin( 9600 );
    pinMode( tempHWSPin, INPUT);
    pinMode( tempHSPin, INPUT);
    lcd.begin(16, 2); //Инициализируем дисплей: 2 строки по 16 символов     
}

void loop() {
    float l_tempHWS = readTemp(1);
    float l_tempHS = readTemp(2);
    //Serial.print("HWS=");
    //Serial.print(l_tempHWS);
    lcd.setCursor(0, 0);
    lcd.print("HWS/HS ");
    lcd.setCursor(7, 0);
    lcd.print(l_tempHWS);
    lcd.setCursor(11, 0);
    lcd.print("/");
    lcd.setCursor(12, 0);
    lcd.print(l_tempHS);
    switch3Way(l_tempHWS, l_tempHS);
    delay(1000);
}


int switch3Way(float p_HWS, float p_HS){
    int l_relay1;  
    int l_relay2;
    Serial.print("SwitchHWS");
    lcd.setCursor(0, 1);
    lcd.print("SwitchHWS");
    //if (l_tempHWS < 51) 
    //else if (l_tempHWS >= 51) 
}


float readTemp(int x){
    int t;
    float tr;
    if (x == 1)
        t = analogRead(tempHWSPin);
    else if  (x == 2) 
        t = analogRead(tempHSPin);
        //Serial.println(t);
    tr = 1023.0 / t - 1;
    tr = SERIAL_R / tr;
    float steinhart;
    steinhart = tr / THERMISTOR_R; // (R/Ro)
    steinhart = log(steinhart); // ln(R/Ro)
    steinhart /= B; // 1/B * ln(R/Ro)
    steinhart += 1.0 / (NOMINAL_T + 273.15); // + (1/To)
    steinhart = 1.0 / steinhart; // Invert
    steinhart -= 273.15; 
    return steinhart;
}

