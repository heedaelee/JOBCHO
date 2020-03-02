// 2/3 여기에서 write 기능하고 checkSum 달아서 processing하고 연동 시켜야 구현됨!!

//놀라운 코드
int col_en[2] = {47, 45};
int col_s[4] = {2, 3, 4, 5};

int pulse = 11;
int row_en[4] = {49, 51, 53, 43};
int row_s[4] = {6, 7, 8, 9};

boolean print = true; //print test하려면 true, 프로세싱 통신 하려면 false
boolean calib = false;
boolean test = false;
boolean col_test = true;


//incoming serial byte
int inByte = 0; 

int rowNum = 64;
int colNum = 32;

int data = 0;               //variable for sending bytes to processing
int calibra[64][32];         //row* col 맞게 calibration 배열 생성
int initMaximum = 0;        //Variable for starting the min array



void setup() {
  // put your setup code here, to run once:
  for (int i = 2; i < 12; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  for (int i = 40; i < 54; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  Serial.begin(115200);

if (calib) {
  Serial.println("\n\Calibrating...\n");

  // Full of 0's of initial matrix
  for (byte j = 0; j < rowNum; j ++) {
    RowSelect(rowNum);
    for (byte i = 0; i < colNum; i++) {
      calibra[j][i] = 0; //초기값 0 주입
    }
  }
  
    // Calibration
    for (byte k = 0; k < 50; k++) { //50번 돌림
      for (byte j = 0; j < rowNum; j ++) {
        RowSelect(j);
        for (byte i = 0; i < colNum; i ++) {
          ColSelect(i);
          digitalWrite(pulse, HIGH);
          calibra[j][i] = calibra[j][i] + analogRead(A0); // 0 + col 기본값

        }
      }
    }

    //Print averages
    for (byte j = 0; j < rowNum; j ++) {
      RowSelect(j); //초기 test, row
      for (byte i = 0; i < colNum; i ++) {
        calibra[j][i] = calibra[j][i] / 50; //calibra 후 기본값/50 해서 대입 -> 평균을 만듦
        if (calibra[j][i] > initMaximum)
          initMaximum = calibra[j][i]; //초기 최대값
        Serial.print(calibra[j][i]);
        Serial.print("\t");
      }
      Serial.println();
    }

    Serial.println();
    Serial.print("initMaximum Value: ");
    Serial.println(initMaximum); //초기 최대값
    Serial.println();
  }
}


void loop() {
  if (Serial.available() > 0) {
//    inByte = Serial.read();//처음 start letter
//    if (inByte == 'C') { //1. 프로세싱에서 connect 버튼 누르면 'C'받음
//      Serial.write('A');   // 2.'A'를 프로세싱에 보냄
//      delay(300);
//    }
//    if (inByte == 'A') {//3.프로세싱에서 port.clear 후 'A' 전송해주면 데이터 전송 시작
      for (int i = 0; i < 64; i++) {
        if(test==true){
        //if(true){
          //if((i % 8)== 0){
          if((i % 8)== 0){
            Serial.println(' ');
          }
        }
        if(i==0){
          Serial.print('a');
          Serial.print(' ');
        } 
        else if (i<63){
          Serial.print('b');
          Serial.print(' ');
        }
        if(i==63){
          Serial.print('c');
          Serial.print(' ');
        }
        RowSelect(i);
        for (int j = 0; j < 32 ; j++) {
          ColSelect(j);

          digitalWrite(pulse, HIGH);
          data = analogRead(A0);
          if(test){
            if(!col_test){
            delay(3000); //for test
            }
          }

          digitalWrite(pulse, LOW);

          int maximum = 1024;
          if (calib) {
            data = map(data, initMaximum, maximum, 0, 100);//data 조절
          } else {
            data = map(data, 0, maximum, 0, 100);//data 조절
          }
          if (data < 0)
            data = 0; //값의 최소 최대 조절
          if (data > 100) //0~100
            data = 100;

          if (!print) {
            Serial.write(data);
          }

          if (print) {
            Serial.print(data);
            Serial.print(' ');
          }
        }
        if (print) {
          Serial.println(' ');
        }
        if (test){
        delay(3000); //for test
        }
      }
      if (print) {
        Serial.println(' ');
        Serial.println(' ');
        Serial.println(' ');
//        Serial.println(' ');
      }

}

void ColSelect(int ch_num) {
  if (ch_num < 16) {
    digitalWrite(col_en[0], HIGH);
    digitalWrite(col_en[1], LOW);
  }
  if (ch_num > 15) {
    digitalWrite(col_en[0], LOW);
    digitalWrite(col_en[1], HIGH);
  }


  for (int i = 0; i < 4; i++) {
    digitalWrite(col_s[i], bitRead(ch_num, i));
  }
}

void RowSelect(int ch_num) {
  if (ch_num < 16) {
    digitalWrite(row_en[0], LOW);
    digitalWrite(row_en[1], HIGH);
    digitalWrite(row_en[2], HIGH);
    digitalWrite(row_en[3], HIGH);
  }
  if (ch_num > 15 && ch_num < 32) {
    digitalWrite(row_en[0], HIGH);
    digitalWrite(row_en[1], LOW);
    digitalWrite(row_en[2], HIGH);
    digitalWrite(row_en[3], HIGH);
  }
  if (ch_num > 31 && ch_num < 48) {
    digitalWrite(row_en[0], HIGH);
    digitalWrite(row_en[1], HIGH);
    digitalWrite(row_en[2], LOW);
    digitalWrite(row_en[3], HIGH);
  }
  if (ch_num > 47 && ch_num < 64) {
    digitalWrite(row_en[0], HIGH);
    digitalWrite(row_en[1], HIGH);
    digitalWrite(row_en[2], HIGH);
    digitalWrite(row_en[3], LOW);
  }

  for (int i = 0; i < 4; i++) {
    digitalWrite(row_s[i], bitRead(ch_num, i));
  }
}
