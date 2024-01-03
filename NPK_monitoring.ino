#include <EEPROM.h> 
#define SERIAL_BAUDRATE 115200
#define ssid "********"  // wifi ssid and password
#define password "********"
#define updateInterval 15000 //15 seconds
#define NORMAL 1
#define ALERT 0

AirSense air;
WaterSense water;
NPK npk;
PH ph;
FishFeeder feeder;
float tds;

unsigned long feedTime = ; //feeding time schedule (can be multiple, by hour count, etc)
float thresholds[]={}; //array to store sensors threshold
unsigned long prevMillis = 0; //variable to store previous milliseconds count
bool alerts[8] = {}; // array to store threshold breaches alert flag from sensors [waterlevel,watertemp, ph, nitrogen,phosphorous,potassium, fishfeedlevel]

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  startWiFIAP();  // start wifi accesspoint
  startWiFIWebServer(); //start web server to enable tab section view 
  wifi.connect(ssid,password); 
  if(wifi.is_Connected()){
    Serial.println("connected to wifi");
  }
  else{
    Serial.println("can\'t connect to wifi, please check ssid/password");
    delay(10000);
  }
  setThresholds({},false);  //set thresholds from eeprom data
}

void loop() {
  water.readLevel();
  water.readTemp();
  Serial.println("W A T E R");
  Serial.print("level: "+String(water.level));
  Serial.println("\ttemperature: "+String(water.temp));

  air.readHum();
  air.readTemp();
  Serial.println("A I R");
  Serial.print("humidity: "+String(air.hum));
  Serial.println("\ttemperature: "+String(air.temp));

  npk.getNPK();
  Serial.println("N P K");
  Serial.print("nitrogen: "+String(npk.nitrogen));
  Serial.print("\tphosphorous: "+String(npk.phosphorous));
  Serial.print("\tpotassium: "+String(npk.potassium));

  ph.getPHLevel();
  Serial.println("P H");
  Serial.println("level: "+String(ph.level));

  getTDS();
  Serial.println("T D S");
  Serial.println("total: "+String(tds));

  feeder.getLevel();
  Serial.println("Fish Feed");
  Serial.println("level: "+String(feeder.level));

  monitorLevels();
  checkFeedingTime();
  
  bool onAlert = false;
  for(int i = 0; i<sizeof(alerts); i++){ //check sensors threshold breach status
    if(alerts[i] == true){  //threshold breached (any of the sensors)
      onAlert = true;
      break;
    }
  }
  if(!onAlert){  //no sensors threshold breach alert is flagged
     lights(NORMAL); //set lights  to normal (green)
  }

  if(millis() - prevMillis >= updateInterval){
     if(wifi.is_Connected()){
        sendToCLoud(); //send sensors data to http server
     }
    prevMillis = millis();
  }
  
}
