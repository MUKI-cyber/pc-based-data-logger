 void uart0_init() {
    PINSEL0 &= ~0x0F;   // Clear P0.0 and P0.1
    PINSEL0 |= 0x05;    // Enable UART0 RXD/TXD

    U0LCR = 0x83;       // Enable DLAB
    U0DLL = 97;         // For 9600 baud with PCLK = 15MHz
    U0DLM = 0;
    U0LCR = 0x03;       // 8-bit, no parity, 1 stop bit
    //U0FCR = 0x07;       // Enable and reset FIFO
}


void uart0_tx(unsigned char d)
 {
 U0THR=d;
 while(((U0LSR>>5)&1)==0);
 }
char uart0_rx() {
    while ((U0LSR & 1)==0);  // Wait until data is received
    return U0RBR;
}

void uart0_str(const char *str) {
    while (*str) {
        uart0_tx(*str++);
    }
}
