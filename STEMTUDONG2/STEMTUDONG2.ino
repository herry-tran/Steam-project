int s1 = 2; 
int s2 = 3;
int s3 = 4;
int s4 = 5;
int s5 = 6; 
int s6 = 13; 
#define ENA 9
#define thuan1 7
#define nguoc1 8
#define ENB 11
#define thuan2 10
#define nguoc2 12
bool stop = false;
int giatri1, giatri2, giatri3, giatri4, giatri5, giatri6;
int State, State1;

void setup() {
  Serial.begin(9600);

  pinMode(s1, INPUT);  
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(s6, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(thuan1, OUTPUT);
  pinMode(nguoc1, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(thuan2, OUTPUT);
  pinMode(nguoc2, OUTPUT);
}

void loop() {
  giatri1 = digitalRead(s1);  
  giatri2 = digitalRead(s2);
  giatri3 = digitalRead(s3);
  giatri4 = digitalRead(s4);
  giatri5 = digitalRead(s5);
  giatri6 = digitalRead(s6);

if (giatri6 == 0) {
  // Serial.println("doline");
  doline();
} else if (giatri6 == 1) {
  Serial.println("dung");
  dung();
  }
  while (stop && giatri6 == 0) {
    dung();
  }
 }





void tien() {
  digitalWrite(thuan1, LOW);
  digitalWrite(nguoc1, HIGH);
  analogWrite(ENA, 120);
  digitalWrite(thuan2, HIGH);
  digitalWrite(nguoc2, LOW);
  analogWrite(ENB, 120);
}
void lui() {
  digitalWrite(thuan1, LOW);
  digitalWrite(nguoc1, HIGH);
  analogWrite(ENA, 100);
  digitalWrite(thuan2, LOW);
  digitalWrite(nguoc2, HIGH);
  analogWrite(ENB, 100);
}
void phai() {
  digitalWrite(thuan1, HIGH);
  digitalWrite(nguoc1, LOW);
  analogWrite(ENA, 120);
  digitalWrite(thuan2, HIGH);
  digitalWrite(nguoc2, LOW);
  analogWrite(ENB, 120);
}
void trai() {
  digitalWrite(thuan1, LOW);
  digitalWrite(nguoc1, HIGH);
  analogWrite(ENA, 120);
  digitalWrite(thuan2, LOW);
  digitalWrite(nguoc2, HIGH);
  analogWrite(ENB, 120);
}
void chinhphai() {
  digitalWrite(thuan1, HIGH);
  digitalWrite(nguoc1, LOW);
  analogWrite(ENA, 120);
  digitalWrite(thuan2, HIGH);
  digitalWrite(nguoc2, LOW);
  analogWrite(ENB, 0);
}
void chinhtrai() {
  digitalWrite(thuan1, LOW);
  digitalWrite(nguoc1, HIGH);
  analogWrite(ENA, 0);
  digitalWrite(thuan2, LOW);
  digitalWrite(nguoc2, HIGH);
  analogWrite(ENB, 120);
}
void dung() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
void doline() {
  if (giatri1 == 1 && giatri2 == 1 && giatri3 == 0 && giatri4 == 1 && giatri5 == 1) {
    Serial.println("tien");
    tien();
    State = 0;
  } 
  else if ((giatri1 == 1 && giatri2 == 1 && giatri3 == 1 && giatri4 == 0 && giatri5 == 1) || (giatri1 == 1 && giatri2 == 1 && giatri3 == 0 && giatri4 == 0 && giatri5 == 1) || (giatri1 == 1 && giatri2 == 1 && giatri3 == 1 && giatri4 == 0 && giatri5 == 1)) {
    Serial.println("chinhphai");
    chinhphai();
    State = 1;
  } 
  else if ((giatri1 == 1 && giatri2 == 0 && giatri3 == 1 && giatri4 == 1 && giatri5 == 1) || (giatri1 == 1 && giatri2 == 0 && giatri3 == 0 && giatri4 == 1 && giatri5 == 1) || (giatri1 == 1 && giatri2 == 0 && giatri3 == 1 && giatri4 == 1 && giatri5 == 1)) {
    Serial.println("chinhtrai");
    chinhtrai();
    State = -1; 
  } 
  else if ((giatri1 == 1 && giatri2 == 1 && giatri3 == 1 && giatri4 == 0 && giatri5 == 0) || (giatri1 == 1 && giatri2 == 1 && giatri3 == 1 && giatri4 == 1 && giatri5 == 0) || (giatri1 == 1 && giatri2 == 1 && giatri3 == 0 && giatri4 == 0 && giatri5 == 0)) {
    Serial.println("phai");
    phai();
    State = 1;
  } 
  else if ((giatri1 == 0 && giatri2 == 1 && giatri3 == 1 && giatri4 == 1 && giatri5 == 1) || (giatri1 == 0 && giatri2 == 0 && giatri3 == 1 && giatri4 == 1 && giatri5 == 1) || (giatri1 == 0 && giatri2 == 0 && giatri3 == 0 && giatri4 == 1 && giatri5 == 1))   {
    Serial.println("trai");
    trai();
    State = -1;
  } 
  else if (giatri1 == 1 && giatri2 == 1 && giatri3 == 1 && giatri4 == 1 && giatri5 == 1) {
    if (State == 0) {
      Serial.println("tien");
      tien();
    }
    
     else if (State == -1) {
      Serial.println("trai");
      trai();
    } else if (State == 1) {
      Serial.println("phai");
      phai();
    }
  } else if ((giatri1 == 0 && giatri2 == 0 && giatri3 == 0 && giatri4 == 0 && giatri5 == 0) || (giatri1 == 1 && giatri2 == 0 && giatri3 == 0 && giatri4 == 0 && giatri5 == 0 ) || (giatri1 == 0 && giatri2 == 0 && giatri3 == 0 && giatri4 == 0 && giatri5 == 1)) {
    stop = true;
    Serial.println("doline stopped");
    dung();
  }
  }






