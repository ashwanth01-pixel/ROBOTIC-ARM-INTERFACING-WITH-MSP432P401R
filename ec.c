#include "msp.h"
#include <string.h>

void UART0_init(void);
void delayMs(int n);
void pinconfig(void);
void off(void);


int main(){
	int i;
	unsigned char c;
  char message[] = "q.UART,w.SWITCH,r.AUTOMATIC\n";
	char automatic[] = "automatic mode\n";
	char uart[] = "UART mode\n";
	char button[] = "switch mode\n";
	char forward[]= "elbow forward\n";
	char backward[]= "elbow backward\n";
	char right[]= "elbow right\n";
	char left[] = "elbow left\n";
	char pick[]= "pick\n";
	char place[]="place\n";
	pinconfig();   
  UART0_init();  // Call UART Transmission Function
	off();
    for (i = 0; i < strlen(message); i++)
    {
        while (!(EUSCI_A0->IFG & 0x02))
        {
        }                       // Wait until transmitter buffer is empty
        EUSCI_A0->TXBUF = message[i];  // Send a character
    }
   // Infinite Loop (An embedded program does not stop):
	while (1)
	{
		while (!(EUSCI_A0-> IFG & 0x01)) { } // Wait until transmitter buffer is empty
		c = EUSCI_A0 -> RXBUF; // Receive a character
		
		if (c == 'q')//UART mode
		{
			 for (i = 0; i < strlen(uart); i++)
      {
         while (!(EUSCI_A0->IFG & 0x02)){}                       // Wait until transmitter buffer is empty
         EUSCI_A0->TXBUF = uart[i];  // Send a character
      }
			
			P2->OUT |= 1; // Turn ON P2.0 RED LED
			while(1){
				 while (!(EUSCI_A0-> IFG & 0x01)) { } // Wait until transmitter buffer is empty
		     c = EUSCI_A0 -> RXBUF;				 // Receive a character
				 EUSCI_A0->TXBUF = c;
		     if (c == 'A' || c == 'a') 
		     {
			     P2->OUT |= 0x80; 
		     }
		     else if (c == 'B' || c == 'b') 
		     {
			     P2->OUT |= 0x40;
		     }
         else if (c == 'C' || c ==	'c')
		     {
			     P2->OUT |= 0x20;
		     }
		     else if (c == 'D' || c ==	'd')
		     {
			     P2->OUT |= 0x10;
		     }
		     else if (c == 'E' || c ==	'e')
		     {
			     P4->OUT |= 0x01;
		     }
		     else if (c == 'F' || c ==	'f')
		     {
			     P4->OUT |= 0x02;
		     }
		     else if (c == 'G' || c ==	'g')
		     {
			     P4->OUT |= 0x04;
		     }
		     else if (c == 'H' || c ==	'h')
		     {
			     P4->OUT |= 0x08;
				 }
				 else if (c == 'M' || c ==	'm')
				 {
					 break;
				 }
				 else if ( c== 'I' || c == 'i') //off
		     {
					 P2->OUT &= ~0x80;
					 P2->OUT &= ~0x40;
					 P2->OUT &= ~0x20;
					 P2->OUT &= ~0x10;
					 P4->OUT &= ~0x01;
					 P4->OUT &= ~0x02;
					 P4->OUT &= ~0x04;
					 P4->OUT &= ~0x08;
					 
				 }
				 
			 }
			 break;
		}
		else if (c == 'w')//button mode
		{
			 for (i = 0; i < strlen(button); i++)
      {
         while (!(EUSCI_A0->IFG & 0x02)){}                       // Wait until transmitter buffer is empty
         EUSCI_A0->TXBUF = button[i];  // Send a character
      }
			P2->OUT |= 2; // Turn ON P2.1 Green LED
			while(1){
				 while (!(EUSCI_A0-> IFG & 0x01)) { } // Wait until transmitter buffer is empty
		     c = EUSCI_A0 -> RXBUF;		// Receive a character
		     if (!(P1->IN & 0x40))
		     {
			     P2->OUT |= 0x80; 
		     }
		     else if(!(P1->IN & 0x80))
		     {
			     P2->OUT |= 0x40;
		     }
         else if(!(P3->IN & 0x01))
		     {
			     P2->OUT |= 0x20;
		     }
		     else if(!(P3->IN & 0x02))
		     {
			     P2->OUT |= 0x10;
		     }
				 else if (!(P3->IN & 0x04))
		     {
			     P4->OUT |= 0x01;
		     }
		     else if (!(P3->IN & 0x08))
		     {
			     P4->OUT |= 0x02;
		     }
		     else if (!(P3->IN & 0x10))
		     {
			     P4->OUT |= 0x04;
		     }
		     else if (!(P3->IN & 0x20))
		     {
			     P4->OUT |= 0x08;
				 }
				 else if(c == 'm' || c == 'M')
				 {
					 break;
					}
				 else  //off
		     {
					 P2->OUT &= ~0x80;
					 P2->OUT &= ~0x40;
					 P2->OUT &= ~0x20;
					 P2->OUT &= ~0x10;
					 P4->OUT &= ~0x01;
					 P4->OUT &= ~0x02;
					 P4->OUT &= ~0x04;
					 P4->OUT &= ~0x08;
					 
				 }
		     
			} break; }
		else if (c == 'r')//automatic mode
		{
			 for (i = 0; i < strlen(automatic); i++)
      {
         while (!(EUSCI_A0->IFG & 0x02)){}                       // Wait until transmitter buffer is empty
         EUSCI_A0->TXBUF = automatic[i];  // Send a character
      }
			P2->OUT |= 4; // Turn OFF P2.2 BLUE LED
			while(1){
				while (!(EUSCI_A0-> IFG & 0x01)) { } // Wait until transmitter buffer is empty
		     
				 P2->OUT |= 0x80;                               
					 delayMs(2000);
					  for (i = 0; i < strlen(right); i++)
      {
         while (!(EUSCI_A0->IFG & 0x02)){}                       // Wait until transmitter buffer is empty
         EUSCI_A0->TXBUF = right[i];  // Send a character
      }
					 P2->OUT &= ~0x80;                               
					 delayMs(2000);
					 P2->OUT |= 0x20;
					 delayMs(2000);
			 for (i = 0; i < strlen(forward); i++)
      {
         while (!(EUSCI_A0->IFG & 0x02)){}                       // Wait until transmitter buffer is empty
         EUSCI_A0->TXBUF = forward[i];  // Send a character
      }
					 P2->OUT &= ~0x20;
					 delayMs(2000);
					 P4->OUT |= 0x01;
					 delayMs(2000);
			 for (i = 0; i < strlen(pick); i++)
      {
         while (!(EUSCI_A0->IFG & 0x02)){}                       // Wait until transmitter buffer is empty
         EUSCI_A0->TXBUF = pick[i];  // Send a character
      }
					 P4->OUT &= ~0x01;
					 delayMs(2000);
					 P4->OUT |= 0x04;
					 delayMs (2000);
			 for (i = 0; i < strlen(backward); i++)
      {
         while (!(EUSCI_A0->IFG & 0x02)){}                       // Wait until transmitter buffer is empty
         EUSCI_A0->TXBUF = backward[i];  // Send a character
      }
					 P4->OUT &= ~0x04;
					 delayMs (2000);
					 P2->OUT |= 0x40;
					 delayMs(2000);
			 for (i = 0; i < strlen(left); i++)
      {
         while (!(EUSCI_A0->IFG & 0x02)){}                       // Wait until transmitter buffer is empty
         EUSCI_A0->TXBUF = left[i];  // Send a character
      }
					 P2->OUT &= ~0x40;
					 delayMs(2000);
					 P2->OUT |= 0x10;
					 delayMs(2000);
			 for (i = 0; i < strlen(place); i++)
      {
         while (!(EUSCI_A0->IFG & 0x02)){}                       // Wait until transmitter buffer is empty
         EUSCI_A0->TXBUF = place[i];  // Send a character
      }
					 P2->OUT &= ~0x10;
					 delayMs(2000);
					 P4->OUT |= 0x02;
					 delayMs(2000);
			 for (i = 0; i < strlen(backward); i++)
      {
         while (!(EUSCI_A0->IFG & 0x02)){}                       // Wait until transmitter buffer is empty
         EUSCI_A0->TXBUF = backward[i];  // Send a character
      }
					 P4->OUT &= ~0x02;
					 delayMs(2000);
					 P4->OUT |= 0x08;
					 delayMs(2000);
			 for (i = 0; i < strlen(right); i++)
      {
         while (!(EUSCI_A0->IFG & 0x02)){}                       // Wait until transmitter buffer is empty
         EUSCI_A0->TXBUF = right[i];  // Send a character
      }
					 P4->OUT &= ~0x08;
					 delayMs(2000);
					 
					
				}
   		
		
	}  break;	
}
}


//PIN CONFIGURATION 
void off (void){
	P2->OUT &= ~0x80;
	P2->OUT &= ~0x40;
	P2->OUT &= ~0x20;
	P2->OUT &= ~0x10;
  P4->OUT &= ~0x01;
	P4->OUT &= ~0x02;
	P4->OUT &= ~0x04;
	P4->OUT &= ~0x08;
	P2->OUT &= ~1;
	P2->OUT &= ~2;
	P2->OUT &= ~4;
}
void pinconfig(void){
P2->SEL0 &= ~1;
P2->SEL1 &= ~1;
P2->DIR |= 1;
	
P2->SEL0 &= ~2;
P2->SEL1 &= ~2;
P2->DIR |= 2;
	
P2->SEL0 &= ~4;
P2->SEL1 &= ~4;
P2->DIR |= 4;
	
P2->SEL0 &= ~0x80;
P2->SEL1 &= ~0x80;
P2->DIR |= 0x80;
	
P2->SEL0 &= ~0x40;
P2->SEL1 &= ~0x40;
P2->DIR |= 0x40;
	
P2->SEL0 &= ~0x20;
P2->SEL1 &= ~0x20;
P2->DIR |= 0x20;

P2->SEL0 &= ~0x10;
P2->SEL1 &= ~0x10;
P2->DIR |= 0x10;

P4->SEL0 &= ~0x01;
P4->SEL1 &= ~0x01;
P4->DIR |= 0x01;

P4->SEL0 &= ~0x02;
P4->SEL1 &= ~0x02;
P4->DIR |= 0x02;

P4->SEL0 &= ~0x04;
P4->SEL1 &= ~0x04;
P4->DIR |= 0x04;

P4->SEL0 &= ~0x08;
P4->SEL1 &= ~0x08;
P4->DIR |= 0x08;

P1->SEL1 &= ~0x40; 
P1->SEL0 &= ~0x40;	
P1->DIR &= ~0x40; 
P1->REN |= 0x40; 
P1->OUT |= 0x40;

P1->SEL1 &= ~0x80; 
P1->SEL0 &= ~0x80;	
P1->DIR &= ~0x80; 
P1->REN |= 0x80; 
P1->OUT |= 0x80;

P3->SEL1 &= ~0x01; 
P3->SEL0 &= ~0x01;	
P3->DIR &= ~0x01; 
P3->REN |= 0x01; 
P3->OUT |= 0x01;

P3->SEL1 &= ~0x02; 
P3->SEL0 &= ~0x02;	
P3->DIR &= ~0x02; 
P3->REN |= 0x02; 
P3->OUT |= 0x02;

P3->SEL1 &= ~0x04; 
P3->SEL0 &= ~0x04;	
P3->DIR &= ~0x04; 
P3->REN |= 0x04; 
P3->OUT |= 0x04;

P3->SEL1 &= ~0x08; 
P3->SEL0 &= ~0x08;	
P3->DIR &= ~0x08; 
P3->REN |= 0x80; 
P3->OUT |= 0x08;

P3->SEL1 &= ~0x10; 
P3->SEL0 &= ~0x10;	
P3->DIR &= ~0x10; 
P3->REN |= 0x10; 
P3->OUT |= 0x10;

P3->SEL1 &= ~0x20; 
P3->SEL0 &= ~0x20;	
P3->DIR &= ~0x20; 
P3->REN |= 0x20; 
P3->OUT |= 0x20;

}
// Function for UART Transmission:
void UART0_init(void)
{
    EUSCI_A0->CTLW0 |= 1;        // Put in reset mode to configure UART
    EUSCI_A0->MCTLW = 0;         // Disable oversampling
    EUSCI_A0->CTLW0 = 0x0081;    // 00 - 1 stop bit, No Parity, 8-bits data, Asynchronous Mode, First LSB Then MSB, SMCLK
                                 // 81 -  Enabled EUSCI_A0 logic is held in reset state
    EUSCI_A0->BRW = 26;          // 3000000/115200 = 26
    P1->SEL0 |= 0x0C;            // Configure functionality of P1.2, P1.3 as UART Pins
    P1->SEL1 &= ~0x0C;
    EUSCI_A0->CTLW0 &= ~1;       // Take UART out of reset mode
}

// Delay milliseconds when system clock is at 3 MHz for Rev C MCU:
void delayMs(int n)
{
    int i, j;
    for (j = 0; j < n; j++)
        for (i = 750; i > 0; i--)
            ; // Delay of 1 ms
}


