void pathfunc() {
    if (freddylocation == 0) { //Part and Service
        MovVectorfreddy.vx = -34; 
        MovVectorfreddy.vy = -42;
        if (curcam[0] == '0' && curcam[1] == '8') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[0] = 2;
          } else {
            animatronicscamera[0] = 1;
          }
        } else {
            animatronicscamera[0] = 0;
        }
    }
    if (freddylocation == 1) { // Main hall
        MovVectorfreddy.vx = -10; 
        MovVectorfreddy.vy = -35;
        if (curcam[0] == '0' && curcam[1] == '7') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[0] = 2;
          } else {
            animatronicscamera[0] = 1;
          }
        } else {
            animatronicscamera[0] = 0;
        }
    }
    if (freddylocation == 2) { // Party Room 3
        MovVectorfreddy.vx = -38; 
        MovVectorfreddy.vy = -15;
        if (curcam[0] == '0' && curcam[1] == '3') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[0] = 2;
          } else {
            animatronicscamera[0] = 1;
          }
        } else {
            animatronicscamera[0] = 0;
        }
    }
    if (freddylocation == 3) { // Hallway
        animatronicscamera[0] = 0;
    }
    if (freddylocation == 4) { // Office
        animatronicscamera[0] = 0;
    }
    if (bonnielocation == 0) { //Part and Service
        MovVectorbonnie.vx = -43; 
        MovVectorbonnie.vy = -41;
        if (curcam[0] == '0' && curcam[1] == '8') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[1] = 2;
          } else {
            animatronicscamera[1] = 1;
          }
        } else {
            animatronicscamera[1] = 0;
        }
    }
    if (bonnielocation == 1) { // Main hall
        MovVectorbonnie.vx = -20; 
        MovVectorbonnie.vy = -35;
        if (curcam[0] == '0' && curcam[1] == '7') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[1] = 2;
          } else {
            animatronicscamera[1] = 1;
          }
        } else {
            animatronicscamera[1] = 0;
        }
    }
    if (bonnielocation == 2) { // Hallway
        animatronicscamera[1] = 0;
    }
    if (bonnielocation == 3) { // Party room 1
        MovVectorbonnie.vx = 50;
        MovVectorbonnie.vy = -49;
        if (curcam[0] == '0' && curcam[1] == '9') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[1] = 2;
          } else {
            animatronicscamera[1] = 1;
          }
        } else {
            animatronicscamera[1] = 0;     
        }
    }
    if (bonnielocation == 4) { // L. Vent
        MovVectorbonnie.vx = -46;
        MovVectorbonnie.vy = 33;
        if (curcam[0] == '0' && curcam[1] == '5') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[1] = 2;
          } else {
            animatronicscamera[1] = 1;
          }
        } else {
            animatronicscamera[1] = 0;
        }
    }
    if (bonnielocation == 5) { // Office
        animatronicscamera[1] = 0;
    }
    if (chicalocation == 0) { // Part and Service

        MovVectorchica.vx = -41; 
        MovVectorchica.vy = -36;
        if (curcam[0] == '0' && curcam[1] == '8') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[2] = 2;
          } else {
            animatronicscamera[2] = 1;
          }
        } else {
            animatronicscamera[2] = 0;
        }
    }
    if (chicalocation == 1) { // Party Room 4
        MovVectorchica.vx = 10;
        MovVectorchica.vy = -13;
        if (curcam[0] == '0' && curcam[1] == '4') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[2] = 2;
          } else {
            animatronicscamera[2] = 1;
          }
        } else {
            animatronicscamera[2] = 0;
        }
    }
    if (chicalocation == 2) { // Party Room 2
        MovVectorchica.vx = 5;
        MovVectorchica.vy = 12;
        if (curcam[0] == '0' && curcam[1] == '2') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[2] = 2;
          } else {
            animatronicscamera[2] = 1;
          }
        } else {
            animatronicscamera[2] = 0;
        }

    }
    if (chicalocation == 3) { // R.Vent
        MovVectorchica.vx = 10;
        MovVectorchica.vy = 33;
        if (curcam[0] == '0' && curcam[1] == '6') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[2] = 2;
          } else {
            animatronicscamera[2] = 1;
          }
        } else {
            animatronicscamera[2] = 0;
        }

    }
    if (chicalocation == 4) { // Office
        animatronicscamera[2] = 0;
    }

    //foxy's not here

    if (toyfreddylocation == 0) { //Stage
            MovVectortoyfreddy.vx = 41; 
            MovVectortoyfreddy.vy = -45;
        if (curcam[0] == '0' && curcam[1] == '9') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[4] = 2;
          } else {
            animatronicscamera[4] = 1;
          }
        } else {
            animatronicscamera[4] = 0;
        }
    }
    if (toyfreddylocation == 1) { //Game area
        MovVectortoyfreddy.vx = 28;
        MovVectortoyfreddy.vy = -30;
        if (curcam[0] == '1' && curcam[1] == '0') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[4] = 2;
          } else {
            animatronicscamera[4] = 1;
          }
        } else {
            animatronicscamera[4] = 0;
        }
    }
    if (toyfreddylocation > 1) { //Hallway (far) 2, hallway (closer) 3, in your office 4
        animatronicscamera[4] = 0;
    }
    if (toybonnielocation == 0) { //Stage
        MovVectortoybonnie.vx = 32;
        MovVectortoybonnie.vy = -49;
        if (curcam[0] == '0' && curcam[1] == '9') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[5] = 2;
          } else {
            animatronicscamera[5] = 1;
          }
        } else {
            animatronicscamera[5] = 0;
        }
    }
    if (toybonnielocation == 1) { //Party room 3
        MovVectortoybonnie.vx = -43;
        MovVectortoybonnie.vy = -15;
        if (curcam[0] == '0' && curcam[1] == '3') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[5] = 2;
          } else {
            animatronicscamera[5] = 1;
          }
        } else {
            animatronicscamera[5] = 0;
        }
    }
    if (toybonnielocation == 2) { //Party room 4
        MovVectortoybonnie.vx = 5;
        MovVectortoybonnie.vy = -11;
        if (curcam[0] == '0' && curcam[1] == '4') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[5] = 2;
          } else {
            animatronicscamera[5] = 1;
          }
        } else {
            animatronicscamera[5] = 0;
        }
    }
    if (toybonnielocation == 3) { //Party room 2
        MovVectortoybonnie.vx = 10;
        MovVectortoybonnie.vy = 12;
        if (curcam[0] == '0' && curcam[1] == '2') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[5] = 2;
          } else {
            animatronicscamera[5] = 1;
          }
        } else {
            animatronicscamera[5] = 0;
        }
    }
    if (toybonnielocation == 4) { //R. Vent (in)
        MovVectortoybonnie.vx = 10;
        MovVectortoybonnie.vy = 33;
        if (curcam[0] == '0' && curcam[1] == '6') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[5] = 2;
          } else {
            animatronicscamera[5] = 1;
          }
        } else {
            animatronicscamera[5] = 0;
        }
    }
    if (toybonnielocation == 5) { //R. Vent (out)
        animatronicscamera[5] = 0;
    }
    if (toybonnielocation == 6) { //Office
        animatronicscamera[5] = 0;
    }

    if (toychicalocation == 0) { //Stage
        MovVectortoychica.vx = 50;
        MovVectortoychica.vy = -49;
        if (curcam[0] == '0' && curcam[1] == '9') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[6] = 2;
          } else {
            animatronicscamera[6] = 1;
          }
        } else {
            animatronicscamera[6] = 0;     
        }
    }
    if (toychicalocation == 1) { //Main hall
        MovVectortoychica.vx = -5;
        MovVectortoychica.vy = -33;
        if (curcam[0] == '0' && curcam[1] == '7') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[6] = 2;
          } else {
            animatronicscamera[6] = 1;
          }
        } else {
            animatronicscamera[6] = 0;           
        }
    }
    if (toychicalocation == 2) { //hallway outside
        animatronicscamera[6] = 0;   
    }
    if (toychicalocation == 3) { //Party room 1
        MovVectortoychica.vx = -46;
        MovVectortoychica.vy = 12;
        if (curcam[0] == '0' && curcam[1] == '1') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[6] = 2;
          } else {
            animatronicscamera[6] = 1;
          }
        } else {
            animatronicscamera[6] = 0;           
        }
    }
    if (toychicalocation == 4) { //L.Vent (in)
        MovVectortoychica.vx = -46;
        MovVectortoychica.vy = 33;
        if (curcam[0] == '0' && curcam[1] == '5') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[6] = 2;
          } else {
            animatronicscamera[6] = 1;
          }
        } else {
            animatronicscamera[6] = 0;
        }
    }
    if (toychicalocation == 5){ //L.Vent (out)
        animatronicscamera[6] = 0;
    }

    //BB is not here either

    if (manglelocation == 0) { //Kids cove
        MovVectormangle.vx = 38;
        MovVectormangle.vy = 21;

        if (curcam[0] == '1' && curcam[1] == '2') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[7] = 2;
          } else {
            animatronicscamera[7] = 1;
          }
        } else {
            animatronicscamera[7] = 0;
        }
    }
    if (manglelocation == 1) { //Prize corner
        MovVectormangle.vx = 58;
        MovVectormangle.vy = -5;
        if (curcam[0] == '1' && curcam[1] == '1') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[7] = 2;
          } else {
            animatronicscamera[7] = 1;
          }
        } else {
            animatronicscamera[7] = 0;    
        }
    }
    if (manglelocation == 2) { //Game area
        MovVectormangle.vx = 25;
        MovVectormangle.vy = -10;
        if (curcam[0] == '1' && curcam[1] == '0') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[7] = 2;
          } else {
            animatronicscamera[7] = 1;
          }
        } else {
            animatronicscamera[7] = 0;    
        }
    }
    if (manglelocation == 3) { //Main Hall
        MovVectormangle.vx = 0;
        MovVectormangle.vy = -36;
        if (curcam[0] == '0' && curcam[1] == '7') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[7] = 2;
          } else {
            animatronicscamera[7] = 1;
          }
        } else {
            animatronicscamera[7] = 0;
        }
    }
    //apparently mangle can be seen on cam 01
    if (manglelocation == 4) { //Hallway
        animatronicscamera[7] = 0;
    }
    //apparently mangle can be seen on cam 01
    if (manglelocation == 5) { //Party Room 2
        MovVectormangle.vx = 0;
        MovVectormangle.vy = 6;
        if (curcam[0] == '0' && curcam[1] == '2') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[7] = 2;
          } else {
            animatronicscamera[7] = 1;
          }
        } else {
            animatronicscamera[7] = 0;
        }
    }
    if (manglelocation == 6) { //R. Vent (in)
        MovVectormangle.vx = 10;
        MovVectormangle.vy = 33;
        if (curcam[0] == '0' && curcam[1] == '6') {
          if (blinkicon > 30 || radar == 1) {
            animatronicscamera[7] = 2;
          } else {
            animatronicscamera[7] = 1;
          }
        } else {
            animatronicscamera[7] = 0;
        }
    }
    if (manglelocation == 7 || manglelocation == 8) { //R. Vent (out)
        animatronicscamera[7] = 0;
    }
    //Might do another route she can pick (hallway)
}