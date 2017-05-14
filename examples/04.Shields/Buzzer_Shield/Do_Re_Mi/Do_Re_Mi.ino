
int buzzer=D5; //Buzzer control port, default D5

int freq[]={1047,1175,1319,1397,1568,1760,1976,2093};//Note name: C6 D6 E6 F6 G6 A6 B6 C7   http://newt.phys.unsw.edu.au/jw/notes.html
String note[]={"C6", "D6", "E6", "F6", "G6", "A6", "B6", "C7"};

void setup() {
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  Serial.begin(115200);
  Serial.println("Buzzer Test...");
}

void loop() {
  for(int i=0; i<8; i++){
    analogWriteRange(freq[i]);
    Serial.print("Note name: ");
    Serial.print(note[i]);
    Serial.print(", Freq: ");
    Serial.print(freq[i]);
    Serial.println("Hz");
    
    analogWrite(buzzer, 512);
    delay(1000);
    analogWrite(buzzer, 0);
    pinMode(buzzer, OUTPUT);
    digitalWrite(buzzer, LOW);
    delay(1000);
  }
  Serial.println("STOP");
  delay(5000);

}