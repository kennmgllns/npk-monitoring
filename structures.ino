struct WaterSense{
  float temp = ; 
  float level = ;
  float temp_threshold_min = ;
  float temp_threshold_max = ;
  float level_threshold_min = ;
  float level_threshold_max = ;
  float readTemp(){
    temp = ;//
    return temp;
  }
  float readLevel(){
    level = ;
    return level;
  }
  void activateHeater(){
    /*
     * activate heater while water temperature is below minimum temperature threshold
     * later on call thresholdBreach(1,false); function when temperature is back to normal
     */
  }
  void activateAerator(){
    /*
     * activate aerator while water temperature is beyond maximum temperature threshold
     * later on call thresholdBreach(1,false); function when temperature is back to normal
     */
  }
  void pump(bool add = true){ //assuming water level control mechanism is pump-like and capable to add and reduce water
    if(add){
      /*
       * add watter while water level is below minimum level threshold
       * later on call thresholdBreach(0,false); function when level is back to normal
       */
    }
    else{
      /*
       * decrease water while water level is higher than maximum level threshold
       * later on call thresholdBreach(0,false); function when level is back to normal
       */
    }
  }
}
struct AirSense{
  float temp;
  float hum;
  float readTemp(){
    temp = ;//
    return temp;
  }
  float readHumidity(){
    hum =;
    return hum;
  }
}
struct NPK{
  float nitrogen;
  float phosphorous;
  float potassium; 
  float nitrogenLowThreshold;
  float phosphorousLowThreshold;
  float potassiumLowThreshold;
  void getNPK(){
    nitrogen = ;
    phosphorous = ;
    potassium = ;
  }
  /* functions to  pump nutrients solution delivery to normalize nutrient levels  */
  void addNitrogen(){
    /* add nitrogen solution while current level is below normal
     * later on call thresholdBreach(3,false); function when level is back to normal
     */
  }
  void addPhosphorous(){
     /* add phosphorous solution while level is below normal
     * later on call thresholdBreach(4,false); function when level is back to normal
     */
  }
  void addPotassium(){
     /* add nitrogen solution while level is below normal
     * later on call thresholdBreach(5,false); function when level is back to normal
     */
  }
}

struct PH{
  float level;
  float lowThreshold;
  float getPHLevel(){
    level = ;
    return level;
  }
  /*   pump solution delivery  while ph level is not normal   */
  void addPH(){
     /* increase PH level while current level is below normal
     * later on call thresholdBreach(2,false); function when level is back to normal
     */
  }
}

struct FishFeeder{
  float level;
  float lowThreshold = ;
  float getLevel(){
    level = ;
    return level;
  }
  void feedFish(){
    /*
     *  servo functions to activate feeding mechanisms
    */
  }
}
