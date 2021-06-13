void UART0_Init(void) {
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;

    UART0_CTL_R &= ~UART_CTL_UARTEN;
    UART0_IBRD_R = 104;
    UART0_FBRD_R = 11;
    UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
    UART0_CTL_R |= (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE);

    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & ~0xFF) | (GPIO_PCTL_PA0_U0RX | GPIO_PCTL_PA1_U0TX);
    GPIO_PORTA_DEN_R |= 0x03;
}

char UART0_read(void) {
    while ((UART0_FR_R & 0x10) == 0x10);
    return UART0_DR_R & 0xFF;
}

void UART0_write(char c) {
    while ((UART0_FR_R & UART_FR_TXFF) != 0);
    UART0_DR_R = c;
}

void UART1_Init(void) {
    SYSCTL_RCGCUART_R |= 0x02;
    while ((SYSCTL_PRUART_R & 0x02) == 0);
    SYSCTL_RCGCGPIO_R |= 0x04;
    while ((SYSCTL_PRGPIO_R & 0x04) == 0);

    GPIO_PORTC_CR_R |= 0x30;
    GPIO_PORTC_AMSEL_R &= ~0x30;
    GPIO_PORTC_AFSEL_R |= 0x30;
    GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0xFF00FFFF) + 0x00220000;

    GPIO_PORTC_DEN_R |= 0x30;
    GPIO_PORTC_DIR_R &= ~0x10;
    GPIO_PORTC_DIR_R |= 0x20;
    UART1_CTL_R &= ~0x01;
    UART1_IBRD_R = 104;
    UART1_FBRD_R = 11;
    UART1_LCRH_R = 0x70;
    UART1_CTL_R |= 0x301;

}

char UART1_read(void) {
    while ((UART1_FR_R & 0x10) == 0x10);
    return UART1_DR_R & 0xFF;
}
