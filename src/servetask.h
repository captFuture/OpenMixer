void pumpitUp(){

    DEBUG_INFORMATION_SERIAL.println(atoi(config.liquid1));
    DEBUG_INFORMATION_SERIAL.println(atoi(config.liquid2));
    DEBUG_INFORMATION_SERIAL.println(atoi(config.liquid3));
    DEBUG_INFORMATION_SERIAL.println(complete);
    DEBUG_INFORMATION_SERIAL.println(factor);

    for (int i=0; i <= atoi(config.liquid1); i++){
        showBar(i,0,0,factor);
        delay(100);
    }  
    for (int i=0; i <= atoi(config.liquid2); i++){
        showBar(atoi(config.liquid1),i,0,factor);
        delay(100);
    }  
    for (int i=0; i <= atoi(config.liquid3); i++){
        showBar(atoi(config.liquid1),atoi(config.liquid2),i, factor);
        delay(100);
    }
}

void showServeStats(){
    DEBUG_INFORMATION_SERIAL.print("servestatus: "); DEBUG_INFORMATION_SERIAL.print(serving.servestatus);
    DEBUG_INFORMATION_SERIAL.print(" | display: "); DEBUG_INFORMATION_SERIAL.print(serving.displaypage);
    DEBUG_INFORMATION_SERIAL.print(" | olddisplay: "); DEBUG_INFORMATION_SERIAL.print(olddisplay);
    DEBUG_INFORMATION_SERIAL.print(" | pump0: "); DEBUG_INFORMATION_SERIAL.print(serving.pump0);
    DEBUG_INFORMATION_SERIAL.print(" | pump1: "); DEBUG_INFORMATION_SERIAL.print(serving.pump1);
    DEBUG_INFORMATION_SERIAL.print(" | pump2: "); DEBUG_INFORMATION_SERIAL.print(serving.pump2);
    DEBUG_INFORMATION_SERIAL.print(" | pump3: "); DEBUG_INFORMATION_SERIAL.print(serving.pump3);
    DEBUG_INFORMATION_SERIAL.print(" | weight: "); DEBUG_INFORMATION_SERIAL.print(serving.weight);
    DEBUG_INFORMATION_SERIAL.print(" | led1: "); DEBUG_INFORMATION_SERIAL.print(serving.led1);
    DEBUG_INFORMATION_SERIAL.print(" | led2: "); DEBUG_INFORMATION_SERIAL.print(serving.led2);
    DEBUG_INFORMATION_SERIAL.print(" | liquid0: "); DEBUG_INFORMATION_SERIAL.print(atoi(config.liquid0));
    DEBUG_INFORMATION_SERIAL.print(" | liquid1: "); DEBUG_INFORMATION_SERIAL.print(atoi(config.liquid1));
    DEBUG_INFORMATION_SERIAL.print(" | liquid2: "); DEBUG_INFORMATION_SERIAL.print(atoi(config.liquid2));
    DEBUG_INFORMATION_SERIAL.print(" | liquid3: "); DEBUG_INFORMATION_SERIAL.println(atoi(config.liquid3));
}

void sendServeStats(){
    DEBUG_INFORMATION_SERIAL.print("-- sending: "); DEBUG_INFORMATION_SERIAL.print(serving.servestatus);
    sprintf(msg, servingFormat, serving.pump0, serving.pump1, serving.pump2, serving.pump3, serving.weight);
    if (client.publish(servingTopic, msg))
    {
    }
}

void switchPump(int pump, int status, int amount){
    if(status == 0){
        relay.relayWrite(pump, 0);
    }else{
        //relay.relayWrite(pump, 1);
        DEBUG_INFORMATION_SERIAL.print("Pump on: ");  DEBUG_INFORMATION_SERIAL.println(pump);
        while(serving.weight < amount){
            relay.relayWrite(pump, 1);
            showServeStats();
            if(config.NETworkmode){
                sendServeStats();
            }
        }
        if(pump == 0){
            DEBUG_INFORMATION_SERIAL.println("Pump is 0");
            serving.pump0 = 0;
            serving.pump1 = 1;
            serving.pump2 = 0;
            serving.pump3 = 0;
            relay.relayWrite(pump, 0);
            return;
        }else if(pump == 1){
            DEBUG_INFORMATION_SERIAL.println("Pump is 1");
            serving.pump0 = 0;
            serving.pump1 = 0;
            serving.pump2 = 1;
            serving.pump3 = 0;
            relay.relayWrite(pump, 0);
            return;
        }else if(pump == 2){
            DEBUG_INFORMATION_SERIAL.println("Pump is 2");
            serving.pump0 = 0;
            serving.pump1 = 0;
            serving.pump2 = 0;
            serving.pump3 = 1;
            relay.relayWrite(pump, 0);
            return;
        }else if(pump == 3){
            DEBUG_INFORMATION_SERIAL.println("Pump is 3");
            serving.pump0 = 0;
            serving.pump1 = 0;
            serving.pump2 = 0;
            serving.pump3 = 0;
            relay.relayWrite(pump, 0);
            serving.led1 = 0;
            serving.led2 = 0;
            serving.servestatus = 0;
            LoadCell.tare();
            DEBUG_INFORMATION_SERIAL.println("DRINK DONE");
            serving.displaypage = 1;
            return;
        }else{

        }
    }

}



void servetaskCode(void* pvParameters) {
    while (1) {
        //DEBUG_INFORMATION_SERIAL.print("servetask Uptime (ms): ");
        //DEBUG_INFORMATION_SERIAL.println(millis());
        //DEBUG_INFORMATION_SERIAL.print("servetask running on core ");
        //DEBUG_INFORMATION_SERIAL.println(xPortGetCoreID());
        //showServeStats();
        //if(serving.led1 == 1){switchLed(LED1, 1);}else{switchLed(LED1, 0);};
        //if(serving.led2 == 1){switchLed(LED2, 1);}else{switchLed(LED2, 0);};

        if(serving.servestatus == 1){
            showServeStats();

            if(serving.pump0 == 1){switchPump(0, 1, atoi(config.liquid0));}else{switchPump(0, 0, 0);};
            if(serving.pump1 == 1){switchPump(1, 1, atoi(config.liquid0)+atoi(config.liquid1));}else{switchPump(1, 0, 0);};
            if(serving.pump2 == 1){switchPump(2, 1, atoi(config.liquid0)+atoi(config.liquid1)+atoi(config.liquid2));}else{switchPump(2, 0, 0);};
            if(serving.pump3 == 1){switchPump(3, 1, atoi(config.liquid0)+atoi(config.liquid1)+atoi(config.liquid2)+atoi(config.liquid3));}else{switchPump(3, 0, 0);};

        }else{
            serving.led1 = 0;
            serving.led2 = 0;
            serving.pump0 = 0;
            serving.pump1 = 0;
            serving.pump2 = 0;
            serving.pump3 = 0;
        }
        delay(200);
        
    }
}

