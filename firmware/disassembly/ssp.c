void main(void) { //0x3800: System_init:
    B = 0xA5;
    EA = 0; // disable all interrupts
    CLRWDT = 0x55;
    if (MODE_FG & POF) {// if (ACC_1 == 1) then jumps (forward): 0x386F // Label_008
        //0x386F: Label_008 moved here
        load_akira_to_0x20(); //Calls (backward) this: 0x384E (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x004E)

        for (uint8_t i = 0x14; i != 0; --i) { // i in ACC and loop at //0x3873: Label_009
            if (P4_5 == 1) goto Label_004; // then jumps (backward): 0x3829
            if (P4_6 == 0) goto Label_004; // then jumps (backward): 0x3829
        } //while (ACC != 0); // then jumps (backward): 0x3873 // Label_009

        P4CON = 0;
        R0 = 0;
        for (uint8_t i = 0x14; i != 0; --i) { // i in ACC and loop at //0x3881: Label_010
            P4 = 0xDF;
            while (--R0 != 0) { //0x3884: Label_011:
            } //then jumps: 0x3884 (waiting loop) // Label_011

            if (P4_6 == 0) goto Label_004; // then jumps (backward): 0x3829

            P4 = 0xBF;

            while (--R0 != 0) { //0x388C: Label_012:
            } //then jumps: 0x388C (waiting loop) // Label_012

            if (P4_5 == 1) goto Label_004; // then jumps (backward): 0x3829

            P4 = 0xFF;

            while (--R0 != 0) { //0x3894: Label_013:
            } //then jumps: 0x3894 (waiting loop) // Label_013

            if (P4_5 == 0) goto Label_004; // then jumps (backward): 0x3829

            if (i == 0x0A) { //if (ACC != 0x0A {'\n'}) then jumps (forward): 0x389E // Label_014
                R5_3 = 0x0A;
            } // 0x389E: Label_014:

            if (i == 0x11) { //if (ACC != 0x11) then jumps (forward): 0x38A4 // Label_015
                R6_3 = 0x09; // {'\t'}
            } //0x38A4: Label_015:

            if (i == 0x06) { //if (ACC != 0x06) then jumps (forward): 0x38A9 // Label_016
                R7_3 = 0x06;
            } //0x38A9: Label_016:

            CLRWDT = 0x55;
        } //while (--ACC != 0); //then jumps (backward): 0x3881 // Label_010

        while (--R0 != 0) { //0x38AF: Label_017:
        } //then jumps: 0x38AF (waiting loop) // Label_017

        if (!P4_5 || !P4_6) {
            //if (P4_5 == 1) then jumps (forward): 0x38B9 // Label_018
            //if (P4_6 == 1) then jumps (forward): 0x38B9 // Label_018
            //Jumps (forward): 0x39A6 (PC += 2, PC(10-0) = 0x01A6) // Label_042
            //0x39A6: Label_042 moved here
            P4_6 = 0;
            PREWDT = 0x03;
            SP = 0x27;
            //Calls (forward) this: 0x3A30 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x0230)
            R2<#2> = 0x05;

            while (true) { //0x39B3: Label_043:
                P4 = 0xFF;

                do { //0x39B6: Label_044:
                    CLRWDT = 0x55;
                } while (P4_5); //then jumps (backward): 0x39B6 // Label_044

                if (P4_6) {//if (P4_6 == 0) then jumps (forward): 0x39C6 // Label_046
                    P4_6 = 0;

                    while (!P4_5) { //0x39C1: Label_045:
                    } //Jumps (backward): 0x39C1 (PC += 2, PC(10-0) = 0x01C1) // Label_045
                    continue;// then jumps (backward): 0x39B3 // Label_043
                }// 0x39C6: Label_046:

                ACC = 0x02;
                //Calls (forward) this: 0x3A22 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x0222)
                if (ACC == 0x33) { //if (ACC != 0x33) then jumps (forward): 0x39DD // Label_047
                    //Calls (forward) this: 0x3A1D (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x021D)
                    R4 = ACC;
                    //Calls (forward) this: 0x3A1D (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x021D)
                    R5 = ACC;
                    if (R5 != 0x5A) continue; // then jumps (backward): 0x39B3 // Label_043
                    if (R4 != 0) continue; // then jumps (backward): 0x39B3 // Label_043

                    //Calls (forward) this: 0x3F1B (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x071B)
                    continue; //Jumps (backward): 0x39B3 (PC += 2, PC(10-0) = 0x01B3) // Label_043
                } //0x39DD: Label_047:

                if (ACC == 0x55) { //if (ACC != 0x55) then jumps (forward): 0x39F6 // Label_050
                    R1 = 0x08;
                    R2 = 0x08;

                    do { //0x39E4: Label_048:
                        //Calls (forward) this: 0x3A1D (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x021D)
                        *R1 = ACC;
                        ++R1;
                    } while (--R2 != 0); // then jumps (backward): 0x39E4 // Label_048

                    R1 = 0x08;
                    R2 = 0x08;

                    do { //0x39EE: Label_049:
                        ACC = *R1;
                        //Calls (forward) this: 0x3DC4 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x05C4)
                        ++R1;
                    } while (--R2 != 0); // then jumps (backward): 0x39EE // Label_049

                    continue; //Jumps (backward): 0x39B3 (PC += 2, PC(10-0) = 0x01B3) // Label_043
                }

                while (ACC != 0x66) {// 0x39F6: Label_050:
                } //then jumps: 0x39F6 // Label_050

                //Calls (forward) this: 0x3C37 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x0437)

                while (ACC != 0) {//0x39FB: Label_051:
                }//then jumps: 0x39FB // Label_051

                R2 = 0x08;

                do { //0x39FF: Label_052:
                    //Calls (forward) this: 0x3E8D (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x068D)
                    CLRWDT = 0x55;
                    CY = 1;
                    P4 = 0xFF;

                    do { //0x3A08: Label_053:
                        if (!P4_5) continue; //then jumps: 0x3A08 (waiting loop) // Label_053
                        while (P4_5) { //0x3A0B: Label_054:
                        } //then jumps: 0x3A0B (waiting loop) // Label_054

                        ACC[76543210] = ACC[6543210C];
                        CY = ACC[7];
                        P4_6 = CY;
                        CY = 0;
                    } while (ACC); // then jumps (backward): 0x3A08 // Label_053

                    while (!P4_5) { //0x3A14: Label_055:
                    } //then jumps: 0x3A14 (waiting loop) // Label_055

                    P4_6 = 0;
                } while (--R2 != 0);// then jumps (backward): 0x39FF // Label_052

            } // Jumps (backward): 0x39B3 (PC += 2, PC(10-0) = 0x01B3) // Label_043
        } //0x38B9: Label_018:

        SP = 0x27;
        P4 = 0x9F;
        R2_2 = 0x05;
        R5 = 0x37;
        R4 = 0xFE;
        ACC = 0x5A;
        //Calls (forward) this: 0x3DBE (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x05BE)

        do { //0x38CA: Label_019:
            P4_5 = 0;
            //Calls (forward) this: 0x3EC5 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x06C5)
            P4_5 = 1;
            //Calls (forward) this: 0x3EC5 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x06C5)
        } while (P4_5 == 0); //then jumps (backward): 0x38CA // Label_019

    } else if (MODE_FG & USBRST ||
        *r20 != 'A' || *r21 != 'K' || *r22 != 'I' || *r23 != 'R' ||
        *r24 != *r20 /*'A'*/) {
        goto Label_005;
    }

    //0x3827: Label_003: 
    goto Label_020; //Jumps (forward): 0x38D5 (PC += 2, PC(10-0) = 0x00D5) // Label_020

 Label_004: //0x3829:
    P4CON = 0x60;
    P4 = 0x7F;
    if (ROM[0x37FE] ^ 0x5A) { // if (ACC == 0) then jumps (backward): 0x3827 // Label_003 -> Label_020

    Label_005: //0x3838: //ajmp from 0x3BCC
        if (ROM[0x37FB] == 0x02) {
            ACC = 0;
            B = 0;
            DPTR = 0x0000;
            SP = 0x07;
            PSW = 0;
            goto Label_000; // Jumps (backward): 0x37FB
        }
    }
    goto Label_020; //then jumps (backward): 0x3827 // Label_003 -> Label_020

 Label_020: //0x38D5: 
    CLRWDT = 0x55;
    SP = 0x27;
    PSW = 0;
    P4CON = 0x60;
    P4 = 0x7F;

    if (MODE_FG & 0x0A) {//if (ACC == 0) then jumps (forward): 0x38F4 // Label_022
        //Label_021: //0x38EA:  //ajmp from 0x3F19

        DFC = 0x01;
        load_akira_to_0x20(); //Calls (backward) this: 0x384E (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x004E)
        //Calls (forward) this: 0x3ECF (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x06CF)
        DFC = 0xC2;
    } //0x38F4: Label_022:
    
    //Calls (forward) this: 0x3A30 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x0230)
    DFC = 0xCA;
    PREWDT = 0x03;

    while (true) {// 0x38FC: Label_023
        ACC = *r20;
        while (ACC != 0x41) { //0x38FE: Label_024:
        } // then jumps: 0x38FE // Label_024

        ACC |= *r24;
        while (ACC != 0) { //0x3903: Label_025:
        } //then jumps: 0x3903 // Label_025

        while (EA) { //0x3905: Label_026:
        } //then jumps: 0x3905 (waiting loop) // Label_026

        CLRWDT = 0x55;
        ACC = IF2;
        if (ACC_0) { //if (IF2 & STUP) //if (ACC_0 == 0) then jumps (forward): 0x394B // Label_031
            IF2 &= 0xFE;
            // from 0x3913: Label_027 to 0x394B: Label_031 cut out and put in common if ACC_0 || ACC_1
        }// 0x394B: Label_031:

        if (ACC_1) { //if (ACC_1 == 0) then jumps (forward): 0x3953 // Label_032
            IF2 &= 0xFD;
            //Jumps (backward): 0x3913 (PC += 2, PC(10-0) = 0x0113) // Label_027
        } //0x3953: Label_032:

        if (ACC_0 || ACC_1) { //0x3913: Label_027
            if (!(RXFLG0 & 0x18)) {//if (ACC != 0) then jumps (forward): 0x3935 // Label_028
                //Calls (forward) this: 0x3B53 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x0353)
                if (R3 == 0x08) { // if (R3 != 0x08 {'\b'}) then jumps (forward): 0x393E // Label_029
                    RXFLG0 |= 0x04;
                    RXFLG0 &= 0xFE;
                    if (!(RXFLG0 & R0_OW)) {//if (ACC_4 == 1) then jumps (forward): 0x393E // Label_029
                        //Calls (forward) this: 0x3BE5 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x03E5)
                        //Calls (forward) this: 0x3A64 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x0264)
                        if (!(*r33)) {//if ([0x33] == 1) then jumps (forward): 0x393E // Label_029
                            RXFLG0 &= 0xFB;
                            continue; //Jumps (backward): 0x38FC (PC += 2, PC(10-0) = 0x00FC) // Label_023
                        }
                    }
                }
            } //0x3935: Label_028:
            else if (ACC_4) { // if (ACC_4 == 1) then jumps (forward): 0x3946 // Label_030
                //0x3946: Label_030 copied here
                RXFLG0 &= 0xFB;
                continue; //Jumps (backward): 0x38FC (PC += 2, PC(10-0) = 0x00FC) // Label_023
            } else { // allow all the above if's to jump to 0x393E // Label_029
                RXFLG0 |= 0x04;
                RXFLG0 &= 0xFE;
            }
            //0x393E: Label_029
            TXFLG0 |= 0x02;
            RXFLG0 |= 0x02;
            //Calls (forward) this: 0x3BF1 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x03F1)
            //0x3946: Label_030
            RXFLG0 &= 0xFB;
            continue; //Jumps (backward): 0x38FC (PC += 2, PC(10-0) = 0x00FC) // Label_023
        }

        if (ACC_3) {//if (ACC_3 == 0) then jumps (forward): 0x3975 // Label_036
            IF2 &= 0xF7;
            RXFLG0 &= 0xFB;
            if (!*0x30) {//if ([0x30] == 1) then jumps (forward): 0x3963 // Label_033
                //Calls (forward) this: 0x3B61 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x0361)
                //Jumps (forward): 0x3970 (PC += 2, PC(10-0) = 0x0170) // Label_035
            } else { //0x3963: Label_033:
                if (R0_2 == 0x01) {//if (ACC != 0x01) then jumps (forward): 0x396E // Label_034
                    DADDR = R2_1;
                    //ACC = R2_1 so if (ACC == 0) then jumps (forward): 0x396E // Label_034 (no op???)
                } //0x396E: Label_034:
                //Calls (forward) this: 0x3BF1 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x03F1)
            } //0x3970: Label_035:

            RXFLG0 &= 0xFB;
            continue; //Jumps (backward): 0x38FC (PC += 2, PC(10-0) = 0x00FC) // Label_023
        } //0x3975: Label_036:

        if (ACC_4) { //if (ACC_4 == 0) then jumps (forward): 0x39A4 // Label_041
            IF2 &= 0xEF;
            if (RXFLG0 & R0_OW) { //if (ACC_4 == 1) then jumps (forward): 0x3994 // Label_039
                //0x3994: Label_039 moved here
                *r33 = 1;
                // Jumps (backward): 0x393E (PC += 2, PC(10-0) = 0x013E) // Label_029
                //0x393E: Label_029 copied here

                TXFLG0 |= 0x02;
                RXFLG0 |= 0x02;
                //Calls (forward) this: 0x3BF1 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x03F1)

                RXFLG0 &= 0xFB;
                continue; //Jumps (backward): 0x38FC (PC += 2, PC(10-0) = 0x00FC) // Label_023
            } 

            RXFLG0 |= 0x04;
            if (!*r31) { //if ([0x31] == 1) then jumps (forward): 0x398A // Label_037
                if (RXCNT0 != 0) { //if (ACC != 0) then jumps (forward): 0x3998 // Label_040
                    //0x3998: Label_040 moved here
                    //Calls (forward) this: 0x3B53 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x0353)
                    RXFLG0 |= 0x04;
                    RXFLG0 &= 0xFE;
                    //Calls (forward) this: 0x3BAD (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x03AD)
                } //Jumps (backward): 0x398F (PC += 2, PC(10-0) = 0x018F) // Label_038
            } else { //0x398A: Label_037 (as else allows above to jump to 0x398F: Label_038)
                RXFLG0 &= 0xFE;
                //Calls (forward) this: 0x3BF1 (PC += 2, [++SP] = PCL, [++SP] = PCH, PC(10-0) = 0x03F1)
            } //0x398F: Label_038:
            RXFLG0 &= 0xFB;
            //continue; //unnecessary here//Jumps (backward): 0x38FC (PC += 2, PC(10-0) = 0x00FC) // Label_023
        } //0x39A4: Label_041:
    } // Jumps (backward): 0x38FC (PC += 2, PC(10-0) = 0x00FC) // Label_023
} // end main


void load_akira_to_0x20(void) { //0x384E
    ACC = B;

    while (ACC != 0xA5) { //0x3857: Label_006:
    } //then jumps: 0x3857 // Label_006

    R0 = 0x20;
    DPTR = 0x3FBA;
    for (uint8_t i = 6; i != 0; --i) { // i in R1 and loop at 0x385A
        *R0 = ROM[DPTR];
        ++R0;
        ++DPTR;
    }
    load_0x37FF_to_0x27(); // control falls thorugh to func_001 for ret
}

void load_0x37FF_to_0x27(void) { //0x3861
    R5_3 = 0;
    R6_3 = 0;
    R7_3 = 0;
    *r27 = ROM[0x37FF];
    return; //ret //PCH = [SP--], PCL = [SP--]
}
