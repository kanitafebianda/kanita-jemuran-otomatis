
#include <Stepper.h> //Library Stepper Motor https://drive.google.com/file/d/1yaPMGvbOj1XMqMPOfGdn0PVZwmX8Qxc7/view?usp=drive_link

const int stepsPerRevolution = 200;  //Sesuaikan step

//Inisialisasi Pin in1 = 8, in2 = 9, in3 = 10, in4 = 11.
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

#define button1 digitalRead(3)==0
#define button2 digitalRead(4)==0

const int hujanPin = A0;  // Pin analog tempat sensor hujan terhubung
int hujan = 0;
int cerah = 1;
int aman = 2;
int kondisi = hujan;


void setup() {
  Serial.begin(9600); //memulai serial monitor

  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  pinMode(hujanPin, INPUT);

  myStepper.setSpeed(100); //mengatur kecepatan atau speed dari motor stepper
}

void loop() {

  int hujanValue = analogRead(hujanPin);
  Serial.print("Nilai Hujan: ");
  Serial.println(hujanValue);

  if (hujanValue <= 500 && kondisi == hujan) {
    Serial.println("Hari Hujan");
    Serial.println("Menarik Jemuran");
    myStepper.step(5120);// memutar 360 derajat untuk 2048 dan 180 derajat untuk 1024
    delay(1000);
    kondisi = cerah;
  } else if (hujanValue >= 700 && kondisi == cerah) {
    Serial.println("Hari Cerah");
    Serial.println("Menjemur pakaian");
    myStepper.step(-5120); // memutar -360 derajat untuk -2048 dan -180 derajat untuk -1024
    delay(1000);
    kondisi = hujan;
  }

  if (button1) {
    while (button1) {
      //Serial.println("Menarik pakaian");
      myStepper.step(1);
      kondisi = aman;
    }
  }

  if (button2) {
    while (button2) {
      //Serial.println("Menjemur pakaian");
      myStepper.step(-1);
      kondisi = hujan;
    }
  }

  Serial.println("stand by");
  delay(100);
}
