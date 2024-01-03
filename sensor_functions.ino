void thresholdBreach(int index,bool breached){   // function to update sensors alerts flags
  alerts[index] = breached;
}

void  saveToEEPROM(int arr[]){
  for(int i = 0; i <sizeof(arr); i++){
    thresholds[i] = arr[i];
    EEPROM.write(i,arr[i])    // save data to eeprom
  }
}
void setThresholds(float tempThresholds[],bool fromWeb){
  if(fromWeb){ 
    saveToEEPROM(tempThresholds);   //overwrite eeprom thresholds data from collected user data
  }
  water.temp_threshold_min = EEPROM.read(0);
  water.temp_threshold_max = EEPROM.read(1);
  water.level_threshold_min = EEPROM.read(2);
  water.level_threshold_max = EEPROM.read(3);
  ph.low_threshold = EEPROM.read(4);
  npk.nitrogenLowThreshold = EEPROM.read(5);
  npk.phosphorousLowThreshold = EEPROM.read(6);
  npk.nitrogenLowThreshold = EEPROM.read(7);
}

void getTDS(){
  tds = ;   // get tds sensor data
}

void monitorLevels(){  // function to monitor sensors data and if they breached their high/low threshold
  for(int i = 0; i<sizeof(alerts); i++){   //initialy set all sensors alert flags to true, will be set false later when each sensor readings are normal
    alerts[i] = true;
  }
  
  if(water.level() <= water.level_threshold_min){
    /*
     *   water is low, adding water
     */
     lights(ALERT); // activate red lights
     water.pump(true);  //activate water pump to incease water
  }
  else if(water.level() >= water.level_threshold_max){ //this depends on the water level control mechanism (if can decrease/increase water)
    /*
     *   water overflow, decreasing water
     */
     lights(ALERT);
     water.pump(false);  //activate water pump to dicrease water
  }
  else{
     /*
     *   water levels back to normal 
     */
     thresholdBreach(0,false);  // set sensor alert flag to false
  }
  if(water.temp() <= water.temp_threshold_min){
    /*
     *   water too cold (heater on)
     */
     lights(ALERT);
     water.activateHeater();
  }
  else if(water.temp() >= water.temp_threshold_max){
     /*
     *   water too hot (aerator on)
     */
     lights(ALERT);
     water.activateAerator();
  }
  else{
     /*
     *   water temperature normal
     */
     thresholdBreach(1,false)
  }

  if(ph.level <= ph.lowThreshold){
    lights(ALERT);
    ph.addPH();
  }
  else{
    thresholdBreach(2,false);
  }

  if(npk.nitrogen <= npk.nitrogenLowThreshold){
    lights(ALERT);
    npk.addNitrogen();
  }
  else{
    thresholdBreach(3,false);
  }
  if(npk.phosphorous <= npk.phosphorousLowThreshold){
    lights(ALERT);
    npk.addPhosphorous();
  }
  else{
    thresholdBreach(4,false);
  }
  if(npk.potassium <= npk.potassiumLowThreshold){
    lights(ALERT);
    npk.addPotassium();
  }
  else{
    thresholdBreach(5,false);
  }
}

void checkFeedingTime(){
  timeNow = ;
  /*
   * get time
   */
  if(feedTime == timeNow){
   feeder.feedFish();  // call feed fish function
   if(feeder.level <= feeder.lowThreshold){ // check if fish feed level is low
      lights(ALERT);
   }
   else{
    thresholdBreach(6,false);
   }
  }
}

void lights(int normal){  // function to set light modes, activate green led for normal, red for any sensors threshold breach
  if(normal){
     /*turn on green led pin , turn off red led pin*/
  }
  else
  {
    /*turn on red led pin , turn off green led pin*/
  }
}
