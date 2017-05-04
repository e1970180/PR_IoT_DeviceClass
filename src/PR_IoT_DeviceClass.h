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
            void	        setupHW() {};		                       //hardware setup
	        void            announce();                                //send parametrs list to general topic  
    		void	        begin(uint16_t updatePeriod);
    		void	        end();
    		void	        loop();
			virtual	void	loopHW() 			{};				
    		void	        invoke();
            virtual	void	update()=0;
			virtual void	inMsgCallback()=0;
			
    		const	String	deviceName;
    	protected:
    		int 	   		 _updatePeriod;		//[s] how often to do update "0" means each loop, "negative" mean no period update, inly by invoke()
    		IoTtime_t	    _lastUpdateTime;
    		bool		    _isBegin = false;	//flag if begin or stopped
    
            bool            postMsg(const String subTopic, const String payload);            
    };

#endif
