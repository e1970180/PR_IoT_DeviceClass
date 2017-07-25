#ifndef PR_IoT_DeviceClass_h
#define PR_IoT_DeviceClass_h

    #include <arduino.h>         
    
	//#include <PR_IoT_TimeClass.h>

	#include <PR_IoT.h>
  
    class PR_IoT_DeviceClass {
    	public:
    			PR_IoT_DeviceClass(String name) 
    				:	deviceName(name), _lastUpdateTime(0)
    				{}
    		void	        begin(int16_t updatePeriod);
    		void	        end();
    		void	        loop();
    		void	        invoke();									//ToDo add invoke(IoT_Msg &Msg) , it requres inMsgCallback(IoT_Msg &Msg)

	        virtual void    announce();                                // 
            virtual void	setupHW() 			{};		               //hardware setup			
			virtual	void	loopHW() 			{};				
            virtual	void	update()			=0;
			virtual void	inMsgCallback()		=0;
			
    		const	String	deviceName;
    	protected:
    		int16_t	   		_updatePeriod;		//[s] how often to do update "0" means in each loop, "negative" mean no update, only by invoke()
    		IoTtime_t	    _lastUpdateTime;
    		bool		    _isBegin = false;	//flag if begin or stopped
    
            bool            postMsg(const String subTopic, const String payload);            
    };

#endif
