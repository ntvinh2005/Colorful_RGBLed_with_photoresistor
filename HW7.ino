// C++ code
//declare constants for pin, analog pin
const int red_digital = 7;
const int blue_digital = 6;
const int green_digital = 5;
const int ledPin = 13;
const int motorPin = 12;

//declare other variables and constants
int analog_value;
float lux = 0.00, Rsensor;
float percent = 0.00;
bool open = false, close = true;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  pinMode(red_digital, OUTPUT);
  pinMode(blue_digital, OUTPUT);
  pinMode(green_digital, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
}

void setColor(float percent) 
{
  float red = sin(percent * TWO_PI) * 127 + 128;
  float green = sin((percent + 1.0 / 3.0) * TWO_PI) * 127 + 128;
  float blue = sin((percent + 2.0 / 3.0) * TWO_PI) * 127 + 128;
  
  analogWrite(red_digital, int(red));
  analogWrite(green_digital, int(green));
  analogWrite(blue_digital, int(blue));
}

bool runMotor(){
  digitalWrite(motorPin, HIGH);
  delay(5000);
  digitalWrite(motorPin, LOW);
  return true;
}

void loop()
{
  analog_value = analogRead(A0);
  Serial.println(analog_value);
  float percent = mapFloat(analog_value, 0, 1023, 1, -1);
    
  setColor(percent);
  
  if (analog_value < 300) {
    digitalWrite(ledPin, HIGH);
    if (open == false) {
      open = runMotor();
      close = false;
    }
  }
  else if (analog_value >= 300 && analog_value <= 400) {
    digitalWrite(ledPin, LOW);
  }
  else {
    digitalWrite(ledPin, LOW);
    Serial.println("Yeak!");
    if (close == false) {
      close = runMotor();
      open = false;
    }
  }
  
  delay(100);
}

float mapFloat(float x, float input_min, float input_max, float output_min, float output_max) {
  return (x - input_min) * (output_max - output_min) / (input_max - input_min) + output_min;
}
