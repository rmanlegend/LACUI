String incomingCommand;
String initialCommand;
String params;
String unitResponse;
void setup() {
  Serial.begin(9600); // set the baud rate
}
void loop() {
  while(Serial.available()) {
    incomingCommand = Serial.readString();// read the incoming data as string
    initialCommand = incomingCommand.substring(0,2);
    params = incomingCommand.substring(3);
    if (initialCommand == "R0") 
      unitResponse = "000";
    else if (initialCommand == "R1")
      // R1 can have passed 0 or 1 and the response back will depend on that
      if (params == "0")
        unitResponse = "34.56";
      else
        unitResponse = "1 24.56";
    else if (initialCommand == "R2")
      // R2 can have passed 0 or 1 and the response back will depend on that
      if (params == "0")
        unitResponse = "5";  // Hex value for 0101 (Drive cabinet fault and Tracking fault) *** ALL FAULTS ***        
      else
        unitResponse = "1";  // Hex value for 0001 (Drive cabinet fault) *** New fault since last R2 request        
    else if (initialCommand == "R3")
      // R3 can have passed "h" (as returned from R3) - returns eight (8) ASCII encoded hex
      // as we are not writing the full "system" just return an arbitary response
        unitResponse = "00000002 00100010";  // Hex value for 0001 (Drive cabinet fault) *** New fault since last R2 request                
    else
      unitResponse = "Unknown command";  
    
    Serial.println(unitResponse);
    }
  delay(100); // delay for 1/10 of a second
}
