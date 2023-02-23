int vfbIn=A1;       // connected to A1
int potIn=A0;       // addjust potentiometer to A0
int pwmOut=6;

void setup() { 
  TCCR0A = 0b10000011;    // Fast PWM (mode 3), Autoamatic clear  on compare match
  TCCR0B = 0b00000001;    // no prescaler fc = 16MHz/256 = 62.5kHz
  OCR0A=84;               // init  33% duty cycle
  pinMode(pwmOut,OUTPUT);  //
}

void loop() {
  int voltageReff;
  int voltageFeedBack;

  OCR0A = constrain(OCR0A,84,168);            // limit PWM Duty Cycle 33% < Duty Cycle < 63%

  voltageReff=map(analogRead(potIn),0,1023,84,168);      // map 0V to 84 (33% Duty Cycle or 0.33*255), 5V(1023) to 168 (66% Duty Cycle)                                                      
  voltageFeedBack=map(analogRead(vfbIn),491,737,84,168); // map for 12V and 18V

  if (voltageFeedBack>voltageReff) OCR0A--;   // Decrease Duty Cycle
  if (voltageFeedBack<voltageReff) OCR0A++;   // Increase Duty Cycle
  delay(100);
}
