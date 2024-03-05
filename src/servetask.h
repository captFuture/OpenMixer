

void pumpitUp(){

    DEBUG_INFORMATION_SERIAL.println(atoi(config.liquid1));
    DEBUG_INFORMATION_SERIAL.println(atoi(config.liquid2));
    DEBUG_INFORMATION_SERIAL.println(atoi(config.liquid3));
    DEBUG_INFORMATION_SERIAL.println(atoi(config.liquid4));
    DEBUG_INFORMATION_SERIAL.println(atoi(config.liquid5));
    DEBUG_INFORMATION_SERIAL.println(atoi(config.liquid6));
    DEBUG_INFORMATION_SERIAL.println(atoi(config.liquid7));
    DEBUG_INFORMATION_SERIAL.println(complete);
    DEBUG_INFORMATION_SERIAL.println(factor);

    for (int i=0; i <= atoi(config.liquid1); i++){
        showBar(i,0,0,factor);
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
    DEBUG_INFORMATION_SERIAL.print(" | pump4: "); DEBUG_INFORMATION_SERIAL.print(serving.pump4);
    DEBUG_INFORMATION_SERIAL.print(" | pump5: "); DEBUG_INFORMATION_SERIAL.print(serving.pump5);
    DEBUG_INFORMATION_SERIAL.print(" | pump6: "); DEBUG_INFORMATION_SERIAL.print(serving.pump6);
    DEBUG_INFORMATION_SERIAL.print(" | pump7: "); DEBUG_INFORMATION_SERIAL.print(serving.pump7);
    DEBUG_INFORMATION_SERIAL.print(" | weight: "); DEBUG_INFORMATION_SERIAL.print(serving.weight);
    DEBUG_INFORMATION_SERIAL.print(" | led1: "); DEBUG_INFORMATION_SERIAL.print(serving.led1);
    DEBUG_INFORMATION_SERIAL.print(" | led2: "); DEBUG_INFORMATION_SERIAL.print(serving.led2);
    DEBUG_INFORMATION_SERIAL.print(" | liquid0: "); DEBUG_INFORMATION_SERIAL.print(atoi(config.liquid0));
    DEBUG_INFORMATION_SERIAL.print(" | liquid1: "); DEBUG_INFORMATION_SERIAL.print(atoi(config.liquid1));
    DEBUG_INFORMATION_SERIAL.print(" | liquid2: "); DEBUG_INFORMATION_SERIAL.print(atoi(config.liquid2));
    DEBUG_INFORMATION_SERIAL.print(" | liquid3: "); DEBUG_INFORMATION_SERIAL.print(atoi(config.liquid3));
    DEBUG_INFORMATION_SERIAL.print(" | liquid4: "); DEBUG_INFORMATION_SERIAL.print(atoi(config.liquid4));
    DEBUG_INFORMATION_SERIAL.print(" | liquid5: "); DEBUG_INFORMATION_SERIAL.print(atoi(config.liquid5));
    DEBUG_INFORMATION_SERIAL.print(" | liquid6: "); DEBUG_INFORMATION_SERIAL.print(atoi(config.liquid6));
    DEBUG_INFORMATION_SERIAL.print(" | liquid7: "); DEBUG_INFORMATION_SERIAL.print(atoi(config.liquid7));
}

void switchPump(int pump, int status, int amount){
    if(status == 0){
        relay.relayWrite(pump, 0);
    }else{
        //relay.relayWrite(pump, 1);
        DEBUG_INFORMATION_SERIAL.print("Pump on: ");  DEBUG_INFORMATION_SERIAL.println(pump);
        while(serving.weight < amount){
            relay.relayWrite(pump, 1);

            //showServeStats();
        }
        if(pump == 0){
            DEBUG_INFORMATION_SERIAL.println("Current Pump is 0 Next Pump is 1");
            serving.pump0 = 0;
            serving.pump1 = 1;
            serving.pump2 = 0;
            serving.pump3 = 0;
            serving.pump4 = 0;
            serving.pump5 = 0;
            serving.pump6 = 0;
            serving.pump7 = 0;
            relay.relayWrite(pump, 0);
            return;
        }else if(pump == 1){
            DEBUG_INFORMATION_SERIAL.println("Current Pump is 1 Next Pump is 2");
            serving.pump0 = 0;
            serving.pump1 = 0;
            serving.pump2 = 1;
            serving.pump3 = 0;
            serving.pump4 = 0;
            serving.pump5 = 0;
            serving.pump6 = 0;
            serving.pump7 = 0;
            relay.relayWrite(pump, 0);
            return;
        }else if(pump == 2){
            DEBUG_INFORMATION_SERIAL.println("Current Pump is 2 Next Pump is 3");
            serving.pump0 = 0;
            serving.pump1 = 0;
            serving.pump2 = 0;
            serving.pump3 = 1;
            serving.pump4 = 0;
            serving.pump5 = 0;
            serving.pump6 = 0;
            serving.pump7 = 0;
            relay.relayWrite(pump, 0);
            return;
        }else if(pump == 3){
            DEBUG_INFORMATION_SERIAL.println("Current Pump is 3 Next Pump is 4");
            serving.pump0 = 0;
            serving.pump1 = 0;
            serving.pump2 = 0;
            serving.pump3 = 0;
            serving.pump4 = 1;
            serving.pump5 = 0;
            serving.pump6 = 0;
            serving.pump7 = 0;
            relay.relayWrite(pump, 0);
            return;
         }else if(pump == 4){
            DEBUG_INFORMATION_SERIAL.println("Current Pump is 4 Next Pump is 5");
            serving.pump0 = 0;
            serving.pump1 = 0;
            serving.pump2 = 0;
            serving.pump3 = 0;
            serving.pump4 = 0;
            serving.pump5 = 1;
            serving.pump6 = 0;
            serving.pump7 = 0;
            relay.relayWrite(pump, 0);
            return;
         }else if(pump == 5){
            DEBUG_INFORMATION_SERIAL.println("Current Pump is 5 Next Pump is 6");
            serving.pump0 = 0;
            serving.pump1 = 0;
            serving.pump2 = 0;
            serving.pump3 = 0;
            serving.pump4 = 0;
            serving.pump5 = 0;
            serving.pump6 = 1;
            serving.pump7 = 0;
            relay.relayWrite(pump, 0);
            return;
         }else if(pump == 6){
            DEBUG_INFORMATION_SERIAL.println("Current Pump is 6 Next Pump is 7");
            serving.pump0 = 0;
            serving.pump1 = 0;
            serving.pump2 = 0;
            serving.pump3 = 0;
            serving.pump4 = 0;
            serving.pump5 = 0;
            serving.pump6 = 0;
            serving.pump7 = 1;
            relay.relayWrite(pump, 0);
            //finishing drink
            serving.led1 = 0;
            serving.led2 = 0;
            serving.servestatus = 0;
            #ifdef USE_M5MINISCALES
                scales.setOffset();
            #else
                LoadCell.tare();
            #endif
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
        //
        if(serving.servestatus == 1){
            
            showServeStats();
            DEBUG_INFORMATION_SERIAL.print("servetaskCode servestatus: "); DEBUG_INFORMATION_SERIAL.println(serving.servestatus);
            if(serving.pump0 == 1){switchPump(0, 1, atoi(config.liquid0));}else{switchPump(0, 0, 0);};
            if(serving.pump1 == 1){switchPump(1, 1, atoi(config.liquid0)+atoi(config.liquid1));}else{switchPump(1, 0, 0);};
            if(serving.pump2 == 1){switchPump(2, 1, atoi(config.liquid0)+atoi(config.liquid1)+atoi(config.liquid2));}else{switchPump(2, 0, 0);};
            if(serving.pump3 == 1){switchPump(3, 1, atoi(config.liquid0)+atoi(config.liquid1)+atoi(config.liquid2)+atoi(config.liquid3));}else{switchPump(3, 0, 0);};
            if(serving.pump4 == 1){switchPump(4, 1, atoi(config.liquid0)+atoi(config.liquid1)+atoi(config.liquid2)+atoi(config.liquid3)+atoi(config.liquid3));}else{switchPump(4, 0, 0);};
            if(serving.pump5 == 1){switchPump(5, 1, atoi(config.liquid0)+atoi(config.liquid1)+atoi(config.liquid2)+atoi(config.liquid3)+atoi(config.liquid4)+atoi(config.liquid5));}else{switchPump(5, 0, 0);};
            if(serving.pump6 == 1){switchPump(6, 1, atoi(config.liquid0)+atoi(config.liquid1)+atoi(config.liquid2)+atoi(config.liquid3)+atoi(config.liquid4)+atoi(config.liquid5)+atoi(config.liquid6));}else{switchPump(6, 0, 0);};
            if(serving.pump7 == 1){switchPump(7, 1, atoi(config.liquid0)+atoi(config.liquid1)+atoi(config.liquid2)+atoi(config.liquid3)+atoi(config.liquid4)+atoi(config.liquid5)+atoi(config.liquid6)+atoi(config.liquid7));}else{switchPump(7, 0, 0);};

        }else{
            serving.led1 = 0;
            serving.led2 = 0;
            serving.pump0 = 0;
            serving.pump1 = 0;
            serving.pump2 = 0;
            serving.pump3 = 0;
            serving.pump4 = 0;
            serving.pump5 = 0;
            serving.pump6 = 0;
            serving.pump7 = 0;
        }
        delay(200);
    }
}

