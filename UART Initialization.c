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
