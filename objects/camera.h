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
        curcamname[0] = 'P';
        curcamname[1] = 'a';
        curcamname[2] = 'r';
        curcamname[3] = 't';
        curcamname[4] = 'y';
        curcamname[5] = ' ';
        curcamname[6] = 'R';
        curcamname[7] = 'o';
        curcamname[8] = 'o';
        curcamname[9] = 'm';
        curcamname[10] = ' ';
        curcamname[11] = '1';
        curcamname[12] = ' ';
        curcamname[13] = ' '; 
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '2';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '3';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '5';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '2') {         //5
        MovVectorpolycamgreyogreen.vx = -5;
        MovVectorpolycamgreyogreen.vy = 24;  
        curcamname[0] = 'P';
        curcamname[1] = 'a';
        curcamname[2] = 'r';
        curcamname[3] = 't';
        curcamname[4] = 'y';
        curcamname[5] = ' ';
        curcamname[6] = 'R';
        curcamname[7] = 'o';
        curcamname[8] = 'o';
        curcamname[9] = 'm';
        curcamname[10] = ' ';
        curcamname[11] = '2';
        curcamname[12] = ' ';
        curcamname[13] = ' '; 
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '4';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '1';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '6';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = '0';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '3') {   
        MovVectorpolycamgreyogreen.vx = -66;
        MovVectorpolycamgreyogreen.vy = -18;  
        curcamname[0] = 'P';
        curcamname[1] = 'a';
        curcamname[2] = 'r';
        curcamname[3] = 't';
        curcamname[4] = 'y';
        curcamname[5] = ' ';
        curcamname[6] = 'R';
        curcamname[7] = 'o';
        curcamname[8] = 'o';
        curcamname[9] = 'm';
        curcamname[10] = ' ';
        curcamname[11] = '3';
        curcamname[12] = ' ';
        curcamname[13] = ' '; 
        curcamname[14] = ' '; 
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '4';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '1';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '8';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '4') {     //2B      
        MovVectorpolycamgreyogreen.vx = -5;
        MovVectorpolycamgreyogreen.vy = -18;  
        curcamname[0] = 'P';
        curcamname[1] = 'a';
        curcamname[2] = 'r';
        curcamname[3] = 't';
        curcamname[4] = 'y';
        curcamname[5] = ' ';
        curcamname[6] = 'R';
        curcamname[7] = 'o';
        curcamname[8] = 'o';
        curcamname[9] = 'm';
        curcamname[10] = ' ';
        curcamname[11] = '4';
        curcamname[12] = ' ';
        curcamname[13] = ' '; 
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '7';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '3';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '2';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = '0';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '5') {     //4B
        MovVectorpolycamgreyogreen.vx = -62;
        MovVectorpolycamgreyogreen.vy = 72;  
        curcamname[0] = 'L';
        curcamname[1] = '.';
        curcamname[2] = ' ';
        curcamname[3] = 'V';
        curcamname[4] = 'e';
        curcamname[5] = 'n';
        curcamname[6] = 't';
        curcamname[7] = ' ';
        curcamname[8] = ' ';
        curcamname[9] = ' ';
        curcamname[10] = ' ';
        curcamname[11] = ' ';
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '6';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '1';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '6') {    
        MovVectorpolycamgreyogreen.vx = -9;
        MovVectorpolycamgreyogreen.vy = 71;  
        curcamname[0] = 'R';
        curcamname[1] = '.';
        curcamname[2] = ' ';
        curcamname[3] = 'V';
        curcamname[4] = 'e';
        curcamname[5] = 'n';
        curcamname[6] = 't';
        curcamname[7] = ' ';
        curcamname[8] = ' ';
        curcamname[9] = ' ';
        curcamname[10] = ' ';
        curcamname[11] = ' ';
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '5';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '2';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '7') {     
        MovVectorpolycamgreyogreen.vx = 14;
        MovVectorpolycamgreyogreen.vy = -60;  
        curcamname[0] = 'M';
        curcamname[1] = 'a';
        curcamname[2] = 'i';
        curcamname[3] = 'n';
        curcamname[4] = ' ';
        curcamname[5] = 'H';
        curcamname[6] = 'a';
        curcamname[7] = 'l';
        curcamname[8] = 'l';
        curcamname[9] = ' ';
        curcamname[10] = ' ';
        curcamname[11] = ' ';
        curcamname[12] = ' ';
        curcamname[13] = ' ';
        curcamname[14] = ' '; 
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '4';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '9';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '8';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '8') {   
        MovVectorpolycamgreyogreen.vx = -66;
        MovVectorpolycamgreyogreen.vy = -70;  
        curcamname[0] = 'P';
        curcamname[1] = 'a';
        curcamname[2] = 'r';
        curcamname[3] = 't';
        curcamname[4] = ' ';
        curcamname[5] = '&';
        curcamname[6] = ' ';
        curcamname[7] = 's';
        curcamname[8] = 'e';
        curcamname[9] = 'r';
        curcamname[10] = 'v';
        curcamname[11] = 'i';
        curcamname[12] = 'c';
        curcamname[13] = 'e';
        curcamname[14] = ' '; 
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '7';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '3';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
    }

    if (curcam[0] == '0' && curcam[1] == '9') {      
        MovVectorpolycamgreyogreen.vx = 105;
        MovVectorpolycamgreyogreen.vy = -87;  
        curcamname[0] = 'S';
        curcamname[1] = 'h';
        curcamname[2] = 'o';
        curcamname[3] = 'w';
        curcamname[4] = ' ';
        curcamname[5] = 'S';
        curcamname[6] = 't';
        curcamname[7] = 'a';
        curcamname[8] = 'g';
        curcamname[9] = 'e';
        curcamname[10] = ' '; //Need to put little spaces like that in case the old name is longer
        curcamname[11] = ' ';
        curcamname[12] = ' ';
        curcamname[13] = ' ';
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = '1';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '7';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
    }

    if (curcam[0] == '1' && curcam[1] == '0') {    
        MovVectorpolycamgreyogreen.vx = 65;
        MovVectorpolycamgreyogreen.vy = -6;  
        curcamname[0] = 'G';
        curcamname[1] = 'a';
        curcamname[2] = 'm';
        curcamname[3] = 'e';
        curcamname[4] = ' ';
        curcamname[5] = 'a';
        curcamname[6] = 'r';
        curcamname[7] = 'e';
        curcamname[8] = 'a';
        curcamname[9] = ' ';
        curcamname[10] = ' ';
        curcamname[11] = ' ';
        curcamname[12] = ' ';
        curcamname[13] = ' ';

        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = '1';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = '2';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '4';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraL = 1;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = '2';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraR = 1;
        }
    }

    if (curcam[0] == '1' && curcam[1] == '1') {   
        MovVectorpolycamgreyogreen.vx = 117;
        MovVectorpolycamgreyogreen.vy = -38;  
        curcamname[0] = 'P';
        curcamname[1] = 'r';
        curcamname[2] = 'i';
        curcamname[3] = 'z';
        curcamname[4] = 'e';
        curcamname[5] = ' ';
        curcamname[6] = 'c';
        curcamname[7] = 'o';
        curcamname[8] = 'r';
        curcamname[9] = 'n';
        curcamname[10] = 'e';
        curcamname[11] = 'r';
        curcamname[12] = ' ';
        curcamname[13] = ' ';
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) {
            curcam[0] = '0';
            curcam[1] = '9';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = '0';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '7';
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
        curcamname[0] = 'K';
        curcamname[1] = 'i';
        curcamname[2] = 'd';
        curcamname[3] = 's';
        curcamname[4] = ' ';
        curcamname[5] = 'C';
        curcamname[6] = 'o';
        curcamname[7] = 'v';
        curcamname[8] = 'e';
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = '0';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraU = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '0';
            curcam[1] = '7';
            SpuSetKey(SPU_ON, SPU_03CH);
            limitercameraD = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
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
}