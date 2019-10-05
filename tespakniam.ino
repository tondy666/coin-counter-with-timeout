#define sensPT A0
#define L 100
#define alpha 0.3

float v[100], vin, s, v_ma, v_sm;
int i;


void setup() {
  Serial.begin(9600);
  pinMode(sensPT, INPUT);

  for(i = 0; i<L; i++)
  {
    v[i] = 0;
  }

}

void loop() {

  vin = analogRead(sensPT);
  vin = vin * 5/1023.0;
  if (vin < 1)
    vin = 1;
  vin = vin - 1.0;
  vin = vin * 100.0;

  for( i = L-1; i > 0; i--)
  {
    v[i] = v[i-1];
  }
  v[0] = vin;
  s = 0;
  for(i=0; i<L; i++)
  {
    s += v[i];
  }
  v_ma = s/L;

   
  v_sm = alpha * vin + (1 - alpha) * v_sm;

  Serial.print("@#");Serial.print(vin);Serial.print("#");Serial.print(v_ma);Serial.print("#");Serial.println(v_sm);
  delay(50);
    
}
