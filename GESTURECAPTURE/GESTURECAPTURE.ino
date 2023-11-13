#include <Arduino_LSM9DS1.h>

#define RED 22
#define BLUE 24
#define GREEN 23

void setup() {
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
   while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in g's");
  Serial.println("X\tY\tZ");
}

void loop() {
  float x, y, z;






  if (IMU.gyroscopeAvailable()) {
    IMU.readAcceleration(x, y, z);
    Serial.println(x);
  // Serial.print("\t");
    //Serial.print(y);
    //Serial.print("\t");
    //Serial.println(z);
    
    if (y > 0.5) {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, HIGH);
      Serial.println("D");

    }

    else if (y <=-0.5 ) {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, HIGH);
      Serial.println("UP");

    }

    else if (x <= -0.5) {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
      Serial.println("R");

    }

    else if (x >= 0.5) {
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      Serial.println("L");
    }


    else {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, HIGH);
      Serial.println("N");
    }
    
  }

  delay(50);
}

