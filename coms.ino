
void startWiFIAP(){  //function to enable wifi accesspoint (hotspot) that users should connect to to go to the plant selection interface 
  
}
void handleRequests(){  // function to handle GET/POST requests from user
  request = ;
  if(request == POST ) // user set active plant from web interface
  { 
    tempThresholds = ; //get thresholds from form submitted by user assuming it is in array format
    setThresholds(thresholds,true);   //set thresholds got from client
  }
  else if (request == GET){
    // serve web view to client
  }
}

void startWiFiWebServer(){
   enableServer();    //start web view of plant selection interface
   handleRequest(); 
}

void sendToCloud(){
  /*
   * send data to http server
   */
}
