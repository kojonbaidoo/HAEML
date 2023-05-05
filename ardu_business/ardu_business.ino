const int MD0 = 13; //lsb
const int MD1 = 12;
const int MD2 = 11;
const int MD3 = 10;
const int MD4 = 9;
const int MD5 = 8;
const int MD6 = 7;
const int MD7 = 6; //msb

const int MS0 = 0; //mcu_signal
const int MS1 = 1; //mcu_ready

const int FD0 = 5; //LSB
const int FD1 = 4; //MSB

const int FS0 = 3; //fpga_signal
const int FS1 = 2; //fpga_ready

const int MD[8] = {13,12,11,10,9,8,7,6};
const int MS[2] = {0,1};
const int FD[2] = {5,4};
const int FS[2] = {3,2};

// Code commands
int start_time;
int end_time;
int reset_counter = 0;
volatile int processing = 0;
volatile int waiting = 1;
volatile int pos = 0;
void setup() {
  Serial.begin(9600);
  
  for(int i = 0;i < 8;i++){
    pinMode(MD[i], OUTPUT);
  }
  for(int i = 0;i < 8;i++){
    pinMode(MS[i], OUTPUT);
    pinMode(FD[i], INPUT);
    pinMode(FS[i], INPUT);
  }

  attachInterrupt(0, fpga_ready_isr,RISING);
  attachInterrupt(1, fpga_signal_isr,RISING);
  digitalWrite(MD[0], HIGH);
  for(int i = 1;i < 8;i++){
    digitalWrite(MD[i], LOW);
  }
  fpga_reset();
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
            
       switch(processing){
          case 0: // Check if FPGA is performing inference
            processing = 1;
            start_time = micros();
            fpga_write(0x0201);
            fpga_write(0x0403);
            fpga_write(0x0605); 
            break;
    
          case 2: // Check if FPGA is done performing inference
            end_time = micros();
            processing = 0;
            Serial.print("Time: ");
            Serial.println(end_time - start_time);
            fpga_reset();// Reset the communication module of the FPGA
            break;
    
          default:
//            Serial.println("Stuck");
            reset_counter++;
            if(reset_counter == 5){
              fpga_reset();
              processing = 0;
              reset_counter = 0;
            }
            break;
        }
}

void fpga_reset(){
  digitalWrite(A1, LOW);
  delay(20);
  digitalWrite(A1, HIGH);
}

void fpga_write_byte(int value){
  waiting = 1;
  digitalWrite(A0,LOW);
  for(int i = 0;i < 8;i++){
    if(((value&(1 << i)) >> i)){
      digitalWrite(MD[i],HIGH);    
    }
    else{
      digitalWrite(MD[i], LOW);
    }
  }
  digitalWrite(A0,HIGH);
//  while(waiting == 1);
}

void fpga_write(int value){
  fpga_write_byte((value << 8) >> 8);
  delayMicroseconds(1);
  fpga_write_byte(value >> 8);
  delayMicroseconds(1);
}

void fpga_signal_isr(){
  //Interrupt vector 1
  waiting = 0;
//  pos = 1;
}

void fpga_ready_isr(){
  //Interrupt vector 0
  processing = 2;
  pos = 1;
}
