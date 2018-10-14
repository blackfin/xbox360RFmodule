#define button_pin 2 //power button repurposed for sync button (pin 5 on the module)
#define data_pin 3 //data line (pin 6 on the module)
#define clk_pin 4 //clock line (pin 7 on module) 


int led_amber[10] = {0,0,1,1,1,0,0,0,0,0};

int BOOTANIM[10] = {0,0,1,0,0,0,0,1,0,1}; //Same as LED_INIT + Displays the XBOX 360 boot LED sequence (appears to only work once) 
int LED_INIT[10] =  {0,0,1,0,0,0,0,1,0,0}; //Initializes the LEDs (needed before any other commands) and turns on the power LED
int LED_INIT_BLPWR[10]= {0,0,1,0,0,0,1,1,0,0}; //Initializes the LEDs (needed before any other commands) and blinks the power LED 

int SYNC[10] = {0,0,0,0,0,0,0,1,0,0}; //Displays the XBOX 360 controller sync LED sequence (not sure if it really syncs)
volatile boolean isSyncEnable = false;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only   
  }
  pinMode(button_pin, INPUT);
  digitalWrite(button_pin, HIGH);
  pinMode(data_pin, INPUT);
  pinMode(clk_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(button_pin), sync, LOW);
  delayMicroseconds(4000);
  initRFModule();
}

void sync(){
  //detachInterrupt (digitalPinToInterrupt (button_pin));
  sendDataToXbox(SYNC);
  isSyncEnable = true;
}

void initRFModule(){
  sendDataToXbox(BOOTANIM);
}

/**
 * Send 10 bit data to xbox controller
 * The control bus appears to use 10bit commands where the first two bits are always 0
 * these commands are sent in big-endian (MSB first) bit-order.
 */
void sendDataToXbox(int cmd[]) {
  pinMode(data_pin, OUTPUT);
  digitalWrite(data_pin, LOW); //pulls DATA low to start communication 
  int prev = 1;
  for(int i = 0; i < 10; i++) {
    while (prev == digitalRead(clk_pin)){} //waits for CLOCK to go low
    prev = digitalRead(clk_pin);  //should be after downward edge of clock, so send bit of data now
    digitalWrite(data_pin, cmd[i]);//sets DATA to the current bit's value
    while (prev == digitalRead(clk_pin)){} //waits for CLOCK to go high
    prev = digitalRead(clk_pin);
  }
  //release DATA
  digitalWrite(data_pin, HIGH);
  pinMode(data_pin, INPUT);
}

void loop() {
  if (isSyncEnable) {
    isSyncEnable = false;
    Serial.println("Start syncing gamepad...");
  }
}
