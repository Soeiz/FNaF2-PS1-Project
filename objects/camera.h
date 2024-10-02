//This function take in charge the cameras.
//Why ? It's Simple, because the game.c was LONG ASF. Longer than my life savings I'd say. (10 rubies) 
//(and also because it was harder to look for a specific thing and having to scroll like 100000 times to pass by the thing we want. Here, you know you are at the cam func.)
// *copy-paste old comment and change three-four words* "Yeah, That'll work"
// *change euros to rubies* "Yeah, I'm original"
// *copy-paste old comment about changing euros to rubies* "I've done what's called a programmer move"

void cameraloc(void) {
    //Gosh, This is gonna be long
    if (curcam[0] == '0' && curcam[1] == '1') { //6
        MovVectorpolycamgreyogreen.vx = -66;
        MovVectorpolycamgreyogreen.vy = 24;  
        sprintf(curcamname, "Party Room 1");
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            sprintf(curcam, "02");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            sprintf(curcam, "03");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            sprintf(curcam, "05");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '2') {         //5
        MovVectorpolycamgreyogreen.vx = -5;
        MovVectorpolycamgreyogreen.vy = 24;  
        sprintf(curcamname, "Party Room 2");
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            sprintf(curcam, "04");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            sprintf(curcam, "01");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            sprintf(curcam, "06");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            sprintf(curcam, "10");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '3') {   
        MovVectorpolycamgreyogreen.vx = -66;
        MovVectorpolycamgreyogreen.vy = -18;  
        sprintf(curcamname, "Party Room 3");
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            sprintf(curcam, "04");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) {  
            sprintf(curcam, "01");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) {  
            sprintf(curcam, "08");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '4') {     //2B      
        MovVectorpolycamgreyogreen.vx = -5;
        MovVectorpolycamgreyogreen.vy = -18;  
        sprintf(curcamname, "Party Room 4");
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            sprintf(curcam, "07");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            sprintf(curcam, "03");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            sprintf(curcam, "02");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            sprintf(curcam, "10");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '5') {     //4B
        MovVectorpolycamgreyogreen.vx = -62;
        MovVectorpolycamgreyogreen.vy = 72;  
        sprintf(curcamname, "L. VENT");
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            sprintf(curcam, "06");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            sprintf(curcam, "01");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '6') {    
        MovVectorpolycamgreyogreen.vx = -9;
        MovVectorpolycamgreyogreen.vy = 71;  
        sprintf(curcamname, "R. VENT");
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            sprintf(curcam, "05");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) {
            sprintf(curcam, "02"); 
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '7') {     
        MovVectorpolycamgreyogreen.vx = 14;
        MovVectorpolycamgreyogreen.vy = -60;  
        sprintf(curcamname, "Main Hall");
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            sprintf(curcam, "04"); 
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            sprintf(curcam, "09"); 
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            sprintf(curcam, "08"); 
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '8') {   
        MovVectorpolycamgreyogreen.vx = -66;
        MovVectorpolycamgreyogreen.vy = -70;  
        sprintf(curcamname, "Part & Service");
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            sprintf(curcam, "07"); 
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            sprintf(curcam, "03"); 
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '9') {      
        MovVectorpolycamgreyogreen.vx = 105;
        MovVectorpolycamgreyogreen.vy = -87;  
        sprintf(curcamname, "Show Stage");
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            sprintf(curcam, "11"); 
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            sprintf(curcam, "07"); 
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
    }

    if (curcam[0] == '1' && curcam[1] == '0') {    
        MovVectorpolycamgreyogreen.vx = 65;
        MovVectorpolycamgreyogreen.vy = -6;  
        sprintf(curcamname, "Game Area");
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            sprintf(curcam, "11");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            sprintf(curcam, "12");
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            sprintf(curcam, "04"); 
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            sprintf(curcam, "12"); 
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
    }

    if (curcam[0] == '1' && curcam[1] == '1') {   
        MovVectorpolycamgreyogreen.vx = 117;
        MovVectorpolycamgreyogreen.vy = -38;  
        sprintf(curcamname, "Prize Corner");
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) {
            sprintf(curcam, "09"); 
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            sprintf(curcam, "10"); 
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            sprintf(curcam, "07"); 
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
        if (pad & PADRleft || pad >> 16 & PADRleft && twoplayermode == 1) { 
            if (windingframessound == 0) {
                SpuSetKey(SPU_ON, SPU_14CH);
                windingframessound = 30;
            }   
            if (musicboxtimer < 2000) {
                musicboxtimer = musicboxtimer + 7;
            } else {
                musicboxtimer = 2000;
            }
        }
    }

    if (curcam[0] == '1' && curcam[1] == '2') {  
        MovVectorpolycamgreyogreen.vx = 114;
        MovVectorpolycamgreyogreen.vy = 17;  
        sprintf(curcamname, "Kid's Cove");
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            sprintf(curcam, "10"); 
            curcam[0] = '1';
            curcam[1] = '0';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            sprintf(curcam, "07"); 
            curcam[0] = '0';
            curcam[1] = '7';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            sprintf(curcam, "02"); 
            curcam[0] = '0';
            curcam[1] = '2';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
    }

    if(pad & PADR1 || pad >> 16 & PADR1 && twoplayermode == 1) { //R1
        if (camlimiter == 1) {return;}
        camera = 0;
        SpuSetKey(SPU_OFF, SPU_01CH);
        SpuSetKey(SPU_ON, SPU_07CH);
    }
    if(!(pad & PADR1 || pad >> 16 & PADR1 && twoplayermode == 1)) {camlimiter = 0;}

    if (!(pad & PADLdown || pad >> 16 & PADLdown) && limitercameraD == 1) {limitercameraD = 0;}
    if (!(pad & PADLup || pad >> 16 & PADLup) && limitercameraU == 1) {limitercameraU = 0;}
    if (!(pad & PADLright || pad >> 16 & PADLright) && limitercameraR == 1) {limitercameraR = 0;}
    if (!(pad & PADLleft || pad >> 16 & PADLleft) && limitercameraL == 1) {limitercameraL = 0;}
} //old 467