#include "PR_IoT_DeviceClass.h"

void	PR_IoT_DeviceClass::begin(uint16_t updatePeriod) {
	_updatePeriod = updatePeriod;
	_isBegin = true;    
}

void	PR_IoT_DeviceClass::end() {
	_isBegin = false;
	//release resources here
}

void	PR_IoT_DeviceClass::loop() {
	IoTtime_t	currentTime;
    
    if (_isBegin) {
		
		loopHW();			//do hardware specific 
		
		if (NodeMQTT.isOnline() && (_updatePeriod >=0) ) {	//do not update if _updatePeriod is negative
			currentTime = IoTtime.now();
            
			if ( ((currentTime - _lastUpdateTime) > _updatePeriod) || !_updatePeriod ) {	// time to update, if _updatePeriod=0 update every time
				_lastUpdateTime = currentTime;
				update();
			}
		}
   //*******  parcing the incoming message
        if ( inMsg.newMsgFlag ) {    
            if ( inMsg.deviceName == deviceName ) {     //we proceed the msg
                 inMsg.newMsgFlag = false;            
     
                 PR_DBGT("Msg parced to ") PR_DBGVLN(deviceName)

                 inMsgCallback();
            }            
        }   
	} //if (_isBegin) 
}//loop()

void	PR_IoT_DeviceClass::invoke() {
	if (_isBegin && NodeMQTT.isOnline() ) {
		_lastUpdateTime = IoTtime.now() - random(0, _updatePeriod/2);               //distributing update() events
		//if ( _lastUpdateTime > IoTtime.now() )  _lastUpdateTime = IoTtime.now();        //ToDO - remove if _lastUpdateTime is signed?
		update();
	}
}

bool    PR_IoT_DeviceClass::postMsg(const String subTopic, const String payload) {
    //use MQTTclient om ESP or SerialMsgClient on AVR 

	NodeMQTT.postMsg(deviceName + "/" + subTopic, payload);
	    
    PR_DBGV(deviceName); PR_DBGTLN(" post a msg");
}


	

	
	
	
