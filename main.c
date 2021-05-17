#include <msp430.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//volatile int moi[50];
void readMoisture();


char Moisturety[] = "Moisturety is: ";
char hundred[]   = "100%";
char ninety[] = "90%";
char eighty[] = "80%";
char seventy[] = "70%";
char sixty[] = "60%";
char fifty[] = "50%";
char forty[] = "40%";
char thirty[] = "30%";
char twenty[] = "20%";
char ten[] = "10%";
char zero[] = "0%";




int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  P2DIR &= ~BIT1;
  P2IFG &= ~BIT1;
  P2IE |= BIT1;
  P2IES |= BIT1;
  P2DIR |= BIT2;
  P2OUT |= BIT2;
  ADC10CTL0 = ADC10SHT_2 + ADC10ON;
  ADC10CTL1 = INCH_7;
  ADC10AE0 |= 0x80;
  P1DIR |= 0x3F;


     BCSCTL1 = CALBC1_1MHZ;
     DCOCTL = CALDCO_1MHZ;

     P1SEL = BIT1|BIT2;
     P1SEL2 = BIT1|BIT2;

     UCA0CTL1 |= UCSWRST+UCSSEL_2;
     UCA0BR0 = 52;  //settings for 19200 baud
     UCA0BR1 = 0;
     UCA0MCTL = UCBRS_0;
     UCA0CTL1 &= ~UCSWRST;

 void ser_output(char *str);

 for (;;)
  {
    ADC10CTL0 |= ENC + ADC10SC;

    //gotoxy(1,1);
    //sendString(" MOISTURE VALUE");
//    gotoxy(1,2);
//    sendString("      PERCENT");
    readMoisture();

    if( ( P2IN & BIT0  ) == 0 ){
        P2OUT &= ~BIT2;
        _bis_SR_register( LPM4_bits | GIE );
    }

    _delay_cycles(500000);
  }
}

void readMoisture(){
    while(1){

        if (ADC10MEM <= 0x01B8)
        {
//            gotoxy(2,2);
//            sendString(" 100");
            ser_output(zero);
        }
        else if (0x01B9 <=ADC10MEM && ADC10MEM <= 0x01D7)
        {
//            gotoxy(2,2);
//            sendString("  90") ;
            ser_output(ninety);
        }
        else if (0x01D8 <=ADC10MEM && ADC10MEM <= 0x01F6)
        {
//            gotoxy(2,2);
//            sendString("  85") ;
            ser_output(eighty);
        }
        else if (0x01F7 <=ADC10MEM && ADC10MEM <= 0x0215)
        {
//            gotoxy(2,2);
//            sendString("  80") ;
            ser_output(eighty);
        }
        else if (0x0216 <=ADC10MEM && ADC10MEM <= 0x0234)
        {
//            gotoxy(2,2);
//            sendString("  75") ;
            ser_output(seventy);
        }
        else if (0x0235 <=ADC10MEM && ADC10MEM <= 0x0253)
        {
//            gotoxy(2,2);
//            sendString("  70") ;
            ser_output(seventy);
        }
        else if (0x0254 <=ADC10MEM && ADC10MEM <= 0x0272)
        {
//            gotoxy(2,2);
//            sendString("  65") ;
            ser_output(sixty);
        }
        else if (0x0273 <=ADC10MEM && ADC10MEM <= 0x0291)
        {
//            gotoxy(2,2);
//            sendString("  60") ;
            ser_output(sixty);
        }
        else if (0x0292 <=ADC10MEM && ADC10MEM <= 0x02B0)
        {
//            gotoxy(2,2);
//            sendString("  55") ;
            ser_output(fifty);
        }
        else if (0x02B1 <=ADC10MEM && ADC10MEM <= 0x02CF)
        {
//            gotoxy(2,2);
//            sendString("  50") ;
            ser_output(fifty);
        }
        else if (0x02D0 <=ADC10MEM && ADC10MEM <= 0x02EE)
        {
//            gotoxy(2,2);
//            sendString("  45") ;
            ser_output(forty);
        }
        else if (0x02EF <=ADC10MEM && ADC10MEM <= 0x030D)
        {
//            gotoxy(2,2);
//            sendString("  40") ;
            ser_output(forty);
        }
        else if (0x030E <=ADC10MEM && ADC10MEM <= 0x032C)
        {
//            gotoxy(2,2);
//            sendString("  35") ;
            ser_output(thirty);
        }
        else if (0x032D <=ADC10MEM && ADC10MEM <= 0x034B)
        {
//            gotoxy(2,2);
//            sendString("  30") ;
            ser_output(thirty);
        }
        else if (0x034C <=ADC10MEM && ADC10MEM <= 0x036A)
        {
//            gotoxy(2,2);
//            sendString("  25") ;
            ser_output(twenty);
        }
        else if (0x036B <=ADC10MEM && ADC10MEM <= 0x0389)
        {
//            gotoxy(2,2);
//            sendString("  20") ;
            ser_output(twenty);
        }
        else if (0x038A <=ADC10MEM && ADC10MEM <= 0x03A8)
        {
//            gotoxy(2,2);
//            sendString("  15") ;
            ser_output(ten);
        }
        else if (0x03A9 <=ADC10MEM && ADC10MEM <= 0x03C7)
        {
//            gotoxy(2,2);
//            sendString("  10") ;
            ser_output(ten);
        }
        else if (0x03C8 <=ADC10MEM && ADC10MEM <= 0x03E6)
        {
//            gotoxy(2,2);
//            sendString("  05") ;
            ser_output(zero);
        }
        else if (0x03E7 <= ADC10MEM)
        {
//            gotoxy(2,2);
//            sendString("  00") ;
            ser_output(zero);
        }

        __delay_cycles(1000000);

    }
}

#pragma vector = PORT2_VECTOR
__interrupt void port2( void ){
    _bic_SR_register_on_exit( LPM4_bits | GIE );
    P2IFG &= ~BIT1;
    P2OUT |= BIT2;
}

void ser_output(char *str){
    while(*str != 0){
        while (!(IFG2&UCA0TXIFG));
        UCA0TXBUF = *str++;
    }
}

