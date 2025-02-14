#define CH1 9
#define CH2 10
#define CH3 11
//#define CH4 9
//#define CH5 10
//#define CH6 11

#define enA 2
#define in1 3
#define in2 4

#define enB 7
#define in3 5
#define in4 6
 
// Integers to represent values from sticks and pots
int ch1v;
int ch2v;
int ch3v;
//int ch4v; 
//int ch5v;
 
// Boolean to represent switch value
//bool ch6Value;
 
// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
 
void setup(){
  // Set up serial monitor
  Serial.begin(115200);
  
  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
//  pinMode(CH4, INPUT);
//  pinMode(CH5, INPUT);
//  pinMode(CH6, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);

  
}
 
 
void loop() {
  
  // Get values for each channel
  ch1v = readChannel(CH1, -100, 100, 0);
  ch2v = readChannel(CH2, -100, 100, 0);
  ch3v = readChannel(CH3, -100, 100, -100);
//  ch4v = readChannel(CH4, -100, 100, 0);
//  ch5v = readChannel(CH5, -100, 100, 0);
//  ch6Value = readSwitch(CH6, false);
  
  // Print to Serial Monitor
  Serial.print("Ch1: ");
  Serial.print(ch1v);
  Serial.print(" | Ch2: ");
  Serial.print(ch2v);
  Serial.print(" | Ch3: ");
  Serial.println(ch3v);
//  Serial.print(" | Ch4: ");
//  Serial.print(ch4v);
//  Serial.print(" | Ch5: ");
//  Serial.println(ch5v);
//  Serial.print(" | Ch6: ");
//  Serial.println(ch6Value);       
//  
//  delay(500);

  if(ch2v > 3)
  {
    forward();
  }
  else if(ch2v <-3)
  {
    reverse();
  }
  else
  {
    standing();
  }
  

}

void forward()
{
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    for(int i=0; i<=ch2v; i++)
    {
      analogWrite(enA, i);
      analogWrite(enB, i);
    }
}

void reverse()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  for(int i=0; i<=-(ch2v); i++)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
  } 
}

void standing()

{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  for(int i=0; i<=0; i++)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
  } 
}
