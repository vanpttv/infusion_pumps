UNSIGNED INT8  MPT1=0,MPT2=0;
UNSIGNED INT KEY_NHAN()
{     
   SIGNED INT8 MAPHIM;
   MAPHIM=0XFF;  
   
//!   //BAN PHIM MEM
//!   output_low(pin_a0); output_high(pin_a1); output_high(pin_a2); output_high(pin_a3);
//!   IF         (INPUT(PIN_B7)==0)      {MAPHIM=1;}
//!   ELSE    IF (INPUT(PIN_B6)==0)      {MAPHIM=4;}
//!   ELSE    IF (INPUT(PIN_B5)==0)      {MAPHIM=7;}
//!   ELSE    IF (INPUT(PIN_B4)==0)      {MAPHIM=10;}
//!   
//!   output_high(pin_a0); output_low(pin_a1); output_high(pin_a2); output_high(pin_a3);
//!   IF         (INPUT(PIN_B7)==0)      {MAPHIM=2;}
//!   ELSE    IF (INPUT(PIN_B6)==0)      {MAPHIM=5;}
//!   ELSE    IF (INPUT(PIN_B5)==0)      {MAPHIM=8;}
//!   ELSE    IF (INPUT(PIN_B4)==0)      {MAPHIM=0;}
//!   
//!   output_high(pin_a0); output_high(pin_a1); output_low(pin_a2); output_high(pin_a3);
//!   IF         (INPUT(PIN_B7)==0)      {MAPHIM=3;}
//!   ELSE    IF (INPUT(PIN_B6)==0)      {MAPHIM=6;}
//!   ELSE    IF (INPUT(PIN_B5)==0)      {MAPHIM=9;}
//!   ELSE    IF (INPUT(PIN_B4)==0)      {MAPHIM=11;}
//!   
//!   output_high(pin_a0); output_high(pin_a1); output_high(pin_a2); output_low(pin_a3);
//!   IF         (INPUT(PIN_B7)==0)      {MAPHIM=12;}
//!   ELSE    IF (INPUT(PIN_B6)==0)      {MAPHIM=13;}
//!   ELSE    IF (INPUT(PIN_B5)==0)      {MAPHIM=14;}
//!   ELSE    IF (INPUT(PIN_B4)==0)      {MAPHIM=15;}
   
   
   //BAN PHIM CUNG
   output_low(pin_a0); output_high(pin_a1); output_high(pin_a2); output_high(pin_a3);
   IF         (INPUT(PIN_B7)==0)      {MAPHIM=1;}
   ELSE    IF (INPUT(PIN_B6)==0)      {MAPHIM=2;}
   ELSE    IF (INPUT(PIN_B5)==0)      {MAPHIM=3;}
   ELSE    IF (INPUT(PIN_B4)==0)      {MAPHIM=12;}
   
   output_high(pin_a0); output_low(pin_a1); output_high(pin_a2); output_high(pin_a3);
   IF         (INPUT(PIN_B7)==0)      {MAPHIM=4;}
   ELSE    IF (INPUT(PIN_B6)==0)      {MAPHIM=5;}
   ELSE    IF (INPUT(PIN_B5)==0)      {MAPHIM=6;}
   ELSE    IF (INPUT(PIN_B4)==0)      {MAPHIM=13;}
   
   output_high(pin_a0); output_high(pin_a1); output_low(pin_a2); output_high(pin_a3);
   IF         (INPUT(PIN_B7)==0)      {MAPHIM=7;}
   ELSE    IF (INPUT(PIN_B6)==0)      {MAPHIM=8;}
   ELSE    IF (INPUT(PIN_B5)==0)      {MAPHIM=9;}
   ELSE    IF (INPUT(PIN_B4)==0)      {MAPHIM=14;}
   
   output_high(pin_a0); output_high(pin_a1); output_high(pin_a2); output_low(pin_a3);
   IF         (INPUT(PIN_B7)==0)      {MAPHIM=10;}
   ELSE    IF (INPUT(PIN_B6)==0)      {MAPHIM=0;}
   ELSE    IF (INPUT(PIN_B5)==0)      {MAPHIM=11;}
   ELSE    IF (INPUT(PIN_B4)==0)      {MAPHIM=15;}
   
   RETURN(MAPHIM);
}

UNSIGNED INT KEY_4X4()
{     
      MPT1=KEY_NHAN();       
      IF (MPT1!=0XFF)   
      {  
         DELAY_MS(1);
         MPT1=KEY_NHAN();
         DO
         {
            MPT2=KEY_NHAN(); 
            DELAY_MS(10);
         }
         WHILE (MPT2==MPT1);
      }             
      RETURN(MPT1);
}

