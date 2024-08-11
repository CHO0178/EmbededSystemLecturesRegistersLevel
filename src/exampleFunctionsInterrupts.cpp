/*

// přerušení strana 35 
// bit přerušení z GPIO
#define INTERRUPT_GPIO_SOURCE 22
// registr s flagy přerušení
#define DPORT_PRO_INTR_STATUS_REG_0_REG REG(0x3FF000EC)
// registr s nastavením úrovně přerušení
#define DPORT_PRO_GPIO_INTERRUPT_MAP_REG REG(0x3FF0015C)
// registr s adresou obsluhy přerušení
#define PIDCTRL_INTERRUPT_ADDR_3_REG REG(0x3FF1F00C)
// povolení generování přerušení pro úroveň
#define PIDCTRL_INTERRUPT_ENABLE_REG REG(0x3FF1F000)

#define GPIO_INTERRUPT_PRO 
#define BUTTON_MUX_REG REG(IO_MUX_GPIO19_REG)

void interruptHandler(){
    // CZ: vymazání příznaku přerušení
    // EN: clear the interrupt flag    
    
    // CZ: zde můžete zpracovat přerušení
    // EN: you can process the interrupt here



    //PIDCTRL_INTERRUPT_ADDR_1_REG = 1;
}



*/