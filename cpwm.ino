// Centere aligned PWM with teensy4.1 board in ARDUINO IDE
#include <imxrt.h>
#define period 354 // Period in clock cycles
void setup() {

// Setup Multiplexer to FlexPWM
IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_04 = 0b000000000000000000000000000000001;
IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_05 = 0b000000000000000000000000000000001;
IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_10 = 0b000000000000000000000000000000001;
IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_11 = 0b000000000000000000000000000000001;
IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_38 = 0b000000000000000000000000000000001;
IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_39 = 0b000000000000000000000000000000001;

FLEXPWM4_SM2CTRL2 = 0b1100000010001000; // debug enabled | wait enabled | complementary A B enabled | initial 0| local sync |force initialize enable |Force currently zero bit 6 | local reload | IPBus clock selected
 
FLEXPWM4_SM2CTRL  = 0b1001010001110000; // load freq once 10 pwm cycles | half cycle reload disable | prescaled fclk/128 | Split disabled | double switching disabled(for now not sure)|
FLEXPWM4_SM2TCTRL = 0b000000000000000000;
FLEXPWM4_MCTRL |=(1<<4)|(1<<5)|(1<<6)| (1<<7) ;//sets clear load bits 4,5,6,7 to high so that load ok bit is cleared
FLEXPWM2_MCTRL |=(1<<4)|(1<<5)|(1<<6)| (1<<7);//sets clear load bits 4,5,6,7 to high so that load ok bit is cleared
FLEXPWM1_MCTRL |=(1<<4)|(1<<5)|(1<<6)| (1<<7);//sets clear load bits 4,5,6,7 to high so that load ok bit is cleared

FLEXPWM4_MCTRL |=(1<<0)|(1<<1)|(1<<2)|(1<<3);//sets load ok bits 0,1,2,3 to high so that buffered value registers are used for update
FLEXPWM2_MCTRL |=(1<<0)|(1<<1)|(1<<2)|(1<<3);//sets load ok bits 0,1,2,3 to high so that buffered value registers are used for update
FLEXPWM1_MCTRL |=(1<<0)|(1<<1)|(1<<2)|(1<<3);//sets load ok bits 0,1,2,3 to high so that buffered value registers are used for update

FLEXPWM4_SM2INIT = -period/2; //-ve Half value of total period clock pulses
FLEXPWM4_SM2VAL0 =    0; // Centre point if reload pushed
FLEXPWM4_SM2VAL1 =  period/2; // Total clock cycles of period
FLEXPWM4_SM2VAL2 =    0; // PWM23 pos edge
FLEXPWM4_SM2VAL3 =    0; // PWM23 neg edge
FLEXPWM4_SM2VAL4 =    0; // PWM45 pos edge
FLEXPWM4_SM2VAL5 =    0;// PWM 45 neg edge

FLEXPWM2_SM2INIT = -period/2; //-ve Half value of total period clock pulses
FLEXPWM2_SM2VAL0 =    0; // Centre point if reload pushed
FLEXPWM2_SM2VAL1 =  period/2; // Total clock cycles of period
FLEXPWM2_SM2VAL2 =    0; // PWM23 pos edge
FLEXPWM2_SM2VAL3 =    0; // PWM23 neg edge
FLEXPWM2_SM2VAL4 =    0; // PWM45 pos edge
FLEXPWM2_SM2VAL5 =    0;// PWM 45 neg edge

FLEXPWM1_SM3INIT = -period/2; //-ve Half value of total period clock pulses
FLEXPWM1_SM3VAL0 =    0; // Centre point if reload pushed
FLEXPWM1_SM3VAL1 =  period/2; // Total clock cycles of period
FLEXPWM1_SM3VAL2 =    0; // PWM23 pos edge
FLEXPWM1_SM3VAL3 =    0; // PWM23 neg edge
FLEXPWM1_SM3VAL4 =    0; // PWM45 pos edge
FLEXPWM1_SM3VAL5 =    0;// PWM 45 neg edge

delay(1000);
start_gate();
 
}

void loop() {
  // put your main code here, to run repeatedly:

//duty(50);//example
}
void start_gate() {
  FLEXPWM4_OUTEN = 0b0000000100010000;//Enable PWM channels A and B of submodules 3-0 of Module4
  FLEXPWM2_OUTEN = 0b0000000100010000;//Enable PWM channels A and B of submodules 3-0 of Module2
  FLEXPWM1_OUTEN = 0b0000000100010000;//Enable PWM channels A and B of submodules 3-0 of Module1

  FLEXPWM4_MCTRL = 0b0000000100010001;//Enable 
  FLEXPWM2_MCTRL = 0b0000000100010001;//Enable
  FLEXPWM1_MCTRL = 0b0000000100000001;//Enable 

  
}

void stop_car(){
  FLEXPWM4_MCTRL = 0b0000000000000001;//Enable PWM channels A and B of submodules 3-0 of Module4
  FLEXPWM2_MCTRL = 0b0000000000000001;//Enable PWM channels A and B of submodules 3-0 of Module2
  FLEXPWM1_MCTRL = 0b0000000000000001;//Enable PWM channels A and B of submodules 3-0 of Module1
  
  FLEXPWM4_OUTEN = 0b0000000000000000;//Disable PWM channels A and B of submodules 3-0 of Module4
  FLEXPWM2_OUTEN = 0b0000000000000000;//Disable PWM channels A and B of submodules 3-0 of Module2
  FLEXPWM1_OUTEN = 0b0000000000000000;//Disable PWM channels A and B of submodules 3-0 of Module1
  
}

void duty_update (int perA,int perB,int perC ){

//----//----// 
FLEXPWM4_SM2VAL2 = -177*perA/100; // PWM23 pos edge
FLEXPWM4_SM2VAL3 = 177*perA/100; // PWM23 neg edge                  
//----//----//
FLEXPWM2_SM2VAL2 = -177*perB/100; // PWM23 pos edge
FLEXPWM2_SM2VAL3 = 177*perB/100; // PWM23 neg edge                  
//----//----//
FLEXPWM1_SM3VAL2 = -177*perC/100; // PWM23 pos edge
FLEXPWM1_SM3VAL3 = 177*perC/100; // PWM23 neg edge
                   
// set the LDFQ bit so no need to clear the load ok bit and trigger it
  
}
