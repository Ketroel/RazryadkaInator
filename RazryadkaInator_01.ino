// Создатель и программист - Созаев Заурбек aka Ketroel. Скетч создан в конце 2019 года

#include <QuadDisplay2.h> //инициализация дисплея от Амперки с сегментными индикаторами
QuadDisplay qd(3, 10, 12);   //контакт CS модуля дисплея соединяется с 3 пином на ардуино меге, можно поменять
//модуль дисплеянадо соединять так: DI - 10, значок ШИМа - 12, там сидит интерфейс SPI. Не забывайте про питание 5 Вольт

#define K1 9    //реле для подключения резистора 10 Ом №1 rare please(((
#define K2 8    //реле для подключения резистора 10 Ом №2
#define K3 4    //реле для подключения резистора 47 Ом №1
#define K4 5    //реле для подключения резистора 47 Ом №2
#define K5 6    //реле для подключения резистора 180 Ом №1
#define K6 7    //реле для подключения резистора 180 Ом №2

void setup() {
  qd.begin();
  pinMode(A0, INPUT);
  pinMode(K1, OUTPUT);
  pinMode(K2, OUTPUT);
  pinMode(K3, OUTPUT);
  pinMode(K4, OUTPUT);
  pinMode(K5, OUTPUT);
  pinMode(K6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float voltage = analogRead(A0) * 27.0 / 1024.00 + 0.7; // Переводим напряжение, пришедшее на ардуину через делитель напряжения в +- реальное значение напряжения.
  if (voltage <= 1.5)
  {
    voltage = voltage - 0.1; // Коэффицент смещения напряжения, который выявлен экспериментально, т.к. ардуино не может в точные вольтметры на всём диапазоне напряжений.
    }
  if(voltage <= 0.66)
  {
    voltage = 0.00; // В схеме стоит диод, на который открывается выше 0,6 Вольт. А напряжение ниже 0,6 - нас не интересует.
    }
  Serial.println(voltage); // Если понадобиться дебажить ардуинку, где и будет лежать этот скетч
  qd.displayInt(8888); // Чтобы проверить, все ли сегменты сегментных индикаторов дисплея светятся. Да он 4-х значный.
  qd.displayFloat(voltage, 2); //Вывод напряжения на дисплей


  // Далее будут включаться и выключаться определённые реле с резисторами, чтобы выставить оптимальный, по моему мнению, ток разряда на всём диапазоне рабочих напряжений стенда (0 - 26,2 Вольт)
  
  if ((25.0 >= voltage)&&(15.1 <= voltage))
  {
    digitalWrite(K1, LOW);
    digitalWrite(K2, LOW);
    digitalWrite(K3, LOW);
    digitalWrite(K4, LOW);
    digitalWrite(K5, HIGH);
    digitalWrite(K6, HIGH);
  }
  if((14.9 >= voltage)&&(10.1 <= voltage))
  {
    digitalWrite(K1, LOW);
    digitalWrite(K2, LOW);
    digitalWrite(K3, HIGH);
    digitalWrite(K4, LOW);
    digitalWrite(K5, LOW);
    digitalWrite(K6, LOW);
  }
  if((9.9 >= voltage)&&(5.1 <= voltage))
  {
    digitalWrite(K1, LOW);
    digitalWrite(K2, LOW);
    digitalWrite(K3, HIGH);
    digitalWrite(K4, HIGH);
    digitalWrite(K5, LOW);
    digitalWrite(K6, LOW);
  }
  if((4.9 >= voltage)&&(2.1 <= voltage))
  {
    digitalWrite(K1, LOW);
    digitalWrite(K2, LOW);
    digitalWrite(K3, HIGH);
    digitalWrite(K4, HIGH);
    digitalWrite(K5, HIGH);
    digitalWrite(K6, HIGH);
  }
  if((1.9 >= voltage)&&(1.1 <= voltage))
  {
    digitalWrite(K1, LOW);
    digitalWrite(K2, HIGH);
    digitalWrite(K3, LOW);
    digitalWrite(K4, LOW);
    digitalWrite(K5, LOW);
    digitalWrite(K6, LOW);
  }
  if((0.9 >= voltage)&&(0 <= voltage))
  {
    digitalWrite(K1, HIGH);
    digitalWrite(K2, HIGH);
    digitalWrite(K3, LOW);
    digitalWrite(K4, LOW);
    digitalWrite(K5, LOW);
    digitalWrite(K6, LOW);
  }
  delay(400); // Чтобы спокойно читать показания с экрана и не офигеть с частоты включения/выключения релюшек
}
