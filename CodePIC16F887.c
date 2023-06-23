#include<tv_16f887_setup.c>

unsigned int8 mp, mode, tt_hien_thi;
int1 tt_cai, vitri_ht_vol, tt_hien_thi_cai_vol;
unsigned int8 phut; unsigned int16 gio;
unsigned int8 mp_lcd_rate[3]={0,0,0}, mp_lcd_vol[4]={0,0,0,0};
signed int8 i;
signed int16 rate, vol;
unsigned int16 count_drop_run_mode;
float  pumped_vol;
int1 tt_start_stop, mode_bonus;



unsigned int16 bdn_tg_dd=0, bdn_motor=0, motor_delay, tg_giot_ht=0, tg_giot_chay=0, ks_tg_dd=0;
unsigned int8 bdn_tg_cua=0, solan_buzzer_keu=0;


int1 mode_select=0, mode_th=0, mode_nhogiot=1;

void SET_RATE_VOL();
void giaima_hienthi_rate();
void giaima_hienthi_vol();
void hien_thi_giao_dien_ban_dau();
void hien_thi_giao_dien_khi_bom();
void hien_thi_giao_dien_bonus();
void hien_thi_thong_so_da_bom();

#int_timer0
void interrupt_timer0()
{ 
   if(mode==1)
   {
       bdn_motor++;
   }   
   set_timer0(131); // 0.2ms
}

#int_timer1
void interrupt_timer1()
{ 
   if(mode==1)
   {
      bdn_tg_dd++;
      bdn_tg_cua++;
   }
   set_timer1(3036); //100ms
}

#int_ext
void interrupt_ext()
{
   if(input(laser_output)==0)
   {
      count_drop_run_mode++;
      tg_giot_ht=bdn_tg_dd; // ms
      bdn_tg_dd=0;
   }
}

void interrupts_button()
{
   mp=key_4x4();
   if((mp>=0)&&(mp<=9)&&(mode!=100)) //Nhan phim tu 0-9
   {
      SET_RATE_VOL();
      output_high(led_set);
   }
   else if(mp==10) //phim CLEAR
   {
      hien_thi_giao_dien_ban_dau();
      output_low(led_set);
   }
   else if(mp==11) //Phim OK
   {
      if(tt_cai==0) //RATE
      {
         rate=100*(int16)mp_lcd_rate[2]+10*(int16)mp_lcd_rate[1]+(int16)mp_lcd_rate[0];
         if (rate>=200)    rate=200;
         for(i=0;i<3;i++)
         {
            mp_lcd_rate[i]=0;
         }
         tt_hien_thi_cai_vol=1;
      }
      else if(tt_cai==1) //VOL
      {
         vol=1000*(int16)mp_lcd_vol[3]+100*(int16)mp_lcd_vol[2]+10*(int16)mp_lcd_vol[1]+(int16)mp_lcd_vol[0];   
         for(i=0;i<4;i++)
         {
            mp_lcd_vol[i]=0;
         }
         if((mode_bonus==1)||(mode==1))
         {  
            output_high(led_set);
         }
         else
            output_low(led_set);
         if((vol!=0)&&(rate!=0)&&((mode_bonus==1)||(mode==1)))
         {      
            lcd_gotoxy(21,2);
            lcd_putc("Time left:");
         } 
      }
      tt_cai=~tt_cai;
   }
   else if(mp==12) //Phim START
   {
      mode_bonus=0;
      output_low(led_set);
      tt_cai=0; vitri_ht_vol=1;
      
      
      if((rate==0)&&(mode_th==1))
      {
         lcd_gotoxy(1,2);
         lcd_putc("                    ");
         lcd_gotoxy(1,1);
         lcd_putc("  Please set rate!  ");
         lcd_gotoxy(21,1);
         lcd_putc("   Please press C   ");
         lcd_gotoxy(21,2);
         lcd_putc("     to continue    ");
         mode=100; // tranh TH nhan phim 0-9 ngay, phai nhan C truoc
      }
      else
      {
         enable_interrupts(int_timer0);
         enable_interrupts(int_timer1);
         if(mode_nhogiot==1)
         {
            enable_interrupts(int_ext_H2L);
         }else disable_interrupts(int_ext_H2L);
         hien_thi_giao_dien_khi_bom();
         mode=1; //DONG CO QUAY
         output_low(enable_motor); // cho phep dong co
//!            motor_delay=;
         bdn_tg_dd=0;
         ks_tg_dd=(float)2*(float)1800/(float)rate;
         
         if(rate>=90)
         {
            output_low(m0);
            output_low(m1);
         }

         if (rate>=200)
         {
            motor_delay=20;
         }
         else if((rate>=150)&&(rate<200))
         {
            motor_delay=(((float)-1/(float)5)*(float)rate)+(float)60;
         }
         else if((rate>=115)&&(rate<150))
         {
            motor_delay=(((float)-2/(float)7)*(float)rate)+((float)510/(float)7);
         }
         else if((rate>=100)&&(rate<115))
         {
            motor_delay=(((float)-2/(float)3)*(float)rate)+((float)350/(float)3);
         }
         else if((rate>=90)&&(rate<100))
         {
            motor_delay=(-(float)rate)+(float)150;
            motor_delay=motor_delay-4;
//!            motor_delay=motor_delay+3;
         }
         else if((rate>=66)&&(rate<90))
         {
            motor_delay=(((float)-5/(float)12)*(float)rate)+67.5;
            motor_delay=motor_delay+3;
            output_high(m0);
            output_low(m1);
         }
         else if((rate>=42)&&(rate<66))
         {
            motor_delay=(((float)-5/(float)6)*(float)rate)+(float)(95);
//!            motor_delay=motor_delay;
            output_high(m0);
            output_low(m1);
         }
         else if((rate>=24)&&(rate<42))
         {
            motor_delay=(((float)-10/(float)9)*(float)rate)+((float)230/(float)3);
            motor_delay=motor_delay-1;
            output_low(m0);
            output_high(m1);
         }
         else if((rate>=18)&&(rate<24))
         {
            motor_delay=(((float)-5/(float)3)*(float)rate)+(float)(90);
            output_low(m0);
            output_high(m1);
         }
         else if((rate>=12)&&(rate<18))
         {
            motor_delay=(((float)-5/(float)3)*(float)rate)+(float)(60);
            output_high(m0);
            output_high(m1);
         }
         else if((rate>=9)&&(rate<12))
         {
            motor_delay=(((float)-10/(float)3)*(float)rate)+(float)(80);
            output_high(m0);
            output_high(m1);
         }
         else if(rate<9)
         {
            motor_delay=60;
            output_high(m0);
            output_high(m1);
         }
      }
   }
   else if(mp==13) //Phim STOP
   {
      lcd_gotoxy(8,1);
      lcd_putc("STOPPING... ");
      mode=0; //stop
      output_high(enable_motor); // ngung cho phep dong co
      output_low(led_set);
      output_low(buzzer);
      disable_interrupts(int_timer0);
      disable_interrupts(int_timer1);
      disable_interrupts(int_ext_H2L);
   }
   else if(mp==14) //Phim BONUS
   {
      if(mode_th==1)
      {
         hien_thi_giao_dien_bonus();
         mode_bonus=1;
         output_low(enable_motor); // cho phep dong co
   //!      setup_timer_1(T1_EXTERNAL);
         enable_interrupts(int_timer0);
         enable_interrupts(int_timer1);
         if(mode_nhogiot==1)
         {
            enable_interrupts(int_ext_H2L);
         }else disable_interrupts(int_ext_H2L);
         mode=1; //DONG CO QUAY
   //!      motor_delay=;
   
///////
         motor_delay=1;
         output_low(m0);
         output_low(m1);
///////
      }
   }
   
   else if(mp==15) //Phim SELECT
   {
//!      button_function=15;
      if((mode==0)||(mode==88))
      {
//!         mode_select=~mode_select;
         mode_select=1;
         if(mode_select==1)
         {
            lcd_gotoxy(1,1);
            lcd_putc("       SELECT       ");
            lcd_gotoxy(1,2);
            lcd_putc("1. Adjust           ");
            lcd_gotoxy(21,1);
            lcd_putc("2. Auto             ");
            lcd_gotoxy(21,2);
            lcd_putc("3. Drip Sensor: ");
            lcd_gotoxy(37,2);
            if(mode_nhogiot==1)
            {              
               lcd_putc("ON ");
            }else lcd_putc("OFF");
         }
//!         else hien_thi_giao_dien_ban_dau();
      }
      else mode_select=0;
   }
}

void main()
{
   set_tris_a(0b11000000);
   set_tris_b(0b11110101);
   port_b_pullups(0b11110100);
   set_tris_c(0b00000001);
   lcd_init();
   lcd_gotoxy(4,1);
   lcd_putc("MAY TRUYEN DICH");
   lcd_gotoxy(4,2);
   lcd_putc("INFUSION PUMPS");
   lcd_gotoxy(26,1);
   lcd_putc("Checking...");
   delay_ms(1000);
   lcd_putc(12);
   
   hien_thi_giao_dien_ban_dau();
      
   while(true)
   {   
      if(mode==88)
      {
         output_toggle(led_liquid);
         delay_ms(200);
      }
      if(mode_select==1)
      {
         mp=key_4x4();
         if(mp==1)
         {
            mode_th=0; // thu cong
            lcd_gotoxy(1,1);
            lcd_putc("(Adj)  ");
            mode_select=0;
            hien_thi_giao_dien_ban_dau();
         }
         else if(mp==2)
         {
            mode_th=1; // tu dong
            lcd_gotoxy(1,1);
            lcd_putc("(Auto) ");
            mode_select=0;
            hien_thi_giao_dien_ban_dau();
         }
         else if(mp==3)
         {
            mode_nhogiot=~mode_nhogiot;
            if(mode_nhogiot==1)
            {
               output_high(laser_signal);
            }else output_low(laser_signal);
            hien_thi_giao_dien_ban_dau();
         }
         else if(mp==15)
         {
            hien_thi_giao_dien_ban_dau();
            mode_select=0;
         }
      }
      
      else interrupts_button();

      if((input(door)==0)&&(mode!=1)) //cua mo khi ko quay dong co
      {
         output_high(led_door);
      }else 
      {
         output_low(led_door);
      }
      
      if ((bdn_tg_dd<ks_tg_dd)&&(mode==1)&&(mode_nhogiot==1)) // khong bi loi dung dich khi chay
      {
         output_low(led_liquid);
      }


         
      if(tt_hien_thi_cai_vol==1)
      {
         tt_hien_thi_cai_vol=0;
         lcd_gotoxy(26,1);
         lcd_putc("....");
      }
      
      if((mode==1)&&(mode_th==0)) //Start, ko dong co - che do adj
      {
         output_high(enable_motor); // ngung cho phep dong co
         tg_giot_chay=tg_giot_ht;
         rate=1800/tg_giot_chay;
         pumped_vol=(float)count_drop_run_mode/(float)20; //1ml = 20drops
         lcd_gotoxy(7,2);
         printf(lcd_putc,"%3lu",rate);
         lcd_gotoxy(21,2);
         lcd_putc("Time left:");
         hien_thi_thong_so_da_bom();
      }
      
      else if((mode==1)&&(mode_th==1)) //Start, chay dong co, che do auto
      {
         
         if((input(door)==0)||((bdn_tg_dd>=ks_tg_dd)&&(mode_nhogiot==1)))//cua mo, giot khong chay
         {            
            if(bdn_tg_cua>5)
            {
               bdn_tg_cua=0;
               if (solan_buzzer_keu<5) // keu 3 lan, moi lan cach 1s
               {
                  output_toggle(buzzer);
                  solan_buzzer_keu++;
               } 
               else
               {  
                  solan_buzzer_keu=0;
                  output_low(buzzer);
                  lcd_gotoxy(8,1);
                  lcd_putc("STOPPING... ");
                  mode=0; //stop
                  bdn_tg_dd=0;
                  output_high(enable_motor);
                  disable_interrupts(int_timer0);
                  disable_interrupts(int_timer1);
                  disable_interrupts(int_ext_H2L);
               }
            }
            if(input(door)==0)
            {
               output_high(led_door);
            }else if ((bdn_tg_dd>=ks_tg_dd)&&(mode_nhogiot==1))
            {
               output_high(led_liquid);
            }
         }
         else
         {
            output_low(buzzer);
            output_low(led_door);
         }
         
         if(bdn_motor>=motor_delay)
         {  
            bdn_motor=bdn_motor-motor_delay;  //!            bdn_motor=0;
            output_toggle(step);
         }

         if((pumped_vol>=vol)&&(vol!=0))
         {
            mode=88; //done
            lcd_gotoxy(8,1);
            lcd_putc(" DONE        ");

            disable_interrupts(int_timer0);
            disable_interrupts(int_timer1);
            disable_interrupts(int_ext_H2L);
            output_high(enable_motor); // ngung cho phep dong co
            rate=0; vol=0; pumped_vol=0; count_drop_run_mode=0;
         }
         else
         {
            pumped_vol=(float)count_drop_run_mode/(float)20; //1ml = 20drops
            hien_thi_thong_so_da_bom();
         }
      }
         
   }
}

/////////////////// CHUONG TRINH CON //////////////////////
void SET_RATE_VOL()
{
   if(tt_cai==0) //cai RATE
   {
      //HIEN THI LEN LCD CAI RATE
      giaima_hienthi_rate();               
   }

   else if (tt_cai==1) //Cai VOL
   {
      //HIEN THI LEN LCD CAI VOL
      giaima_hienthi_vol();
   }
}

void SELECT_BTN_C()
{
   rate=0;
   vol=0;
}

//PHAM GIAI MA HIEN THI LCD
void giaima_hienthi_rate()
{
   for(i=2;i>0;i--)
   {
      mp_lcd_rate[i]=mp_lcd_rate[i-1];
   }
   if(mp<10)   mp_lcd_rate[0]=mp;
   else;

   lcd_gotoxy(7,2);
   for(i=2;i>-1;i--)
   {
      lcd_putc(mp_lcd_rate[i]+0x30);
   }
}

void giaima_hienthi_vol()
{
   for(i=3;i>0;i--)
   {
      mp_lcd_vol[i]=mp_lcd_vol[i-1];
   }
   if(mp<10)   mp_lcd_vol[0]=mp;
   else;
   
   if(vitri_ht_vol==0)  lcd_gotoxy(26,1);  
   else lcd_gotoxy(33,1);
   for(i=3;i>-1;i--)
   {
      lcd_putc(mp_lcd_vol[i]+0x30);
   }
}

void hien_thi_giao_dien_ban_dau()
{
   
   for(i=0;i<3;i++)
   {
      mp_lcd_rate[i]=0;
   }   
   for(i=0;i<4;i++)
   {
      mp_lcd_vol[i]=0;
   }
   pumped_vol=0;
   count_drop_run_mode=0;
   mode=0;
   tt_hien_thi=0;
   tt_cai=0;
   vitri_ht_vol=0; tt_hien_thi_cai_vol=0;
   i=0;
   tt_start_stop=0;
   mode_bonus=0;
   mode_select=0;

   tg_giot_chay=0;
   bdn_tg_dd=0;
   ks_tg_dd=0;
   
   if(mode_nhogiot==1)
   {
      output_high(laser_signal);
   }else output_low(laser_signal);
   
   lcd_gotoxy(8,1);
   lcd_putc("SETTING...   ");
   if(mode_th==0)
   {
      lcd_gotoxy(1,1);
      lcd_putc("(Adj)  ");
      lcd_gotoxy(1,2);
      lcd_putc("Rate: ___ ml/h      ");
      lcd_gotoxy(21,1);
      lcd_putc("Vol: .... ml        ");
      tt_cai=1; //chi cai VOL, con Rate thu cong
   }
   else
   {
      lcd_gotoxy(1,1);
      lcd_putc("(Auto) ");
      lcd_gotoxy(1,2);
      lcd_putc("Rate: ... ml/h      ");
      lcd_gotoxy(21,1);
      lcd_putc("Vol:      ml        ");
   }
   lcd_gotoxy(21,2);
   lcd_putc("                    ");
   vol=0;   rate=0;
   
   
   //
   output_low(buzzer);
   output_low(led_liquid);
   output_low(led_door);
   output_low(led_set);

   
   
   //dong co
   output_high(enable_motor);
   output_high(dir);
   //
   
   setup_timer_0(RTCC_DIV_8|RTCC_INTERNAL);
   set_timer0(131); 
   
   setup_timer_1(t1_internal|t1_div_by_8); 
   set_timer1(3036); 
   
   
   enable_interrupts(global);
   disable_interrupts(int_timer0);
   disable_interrupts(int_timer1);
   disable_interrupts(int_ext_H2L);
}

void hien_thi_giao_dien_khi_bom()
{
   lcd_gotoxy(8,1);
   lcd_putc("RUNNING...   ");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"Rate: %3lu ml/h      ", rate);
   lcd_gotoxy(21,1);
   printf(lcd_putc,"Vol:       /%4lu ml ",vol);
   
   if((vol!=0)&&(rate!=0)&&(mode_bonus==0))
   {      
      lcd_gotoxy(21,2);
      lcd_putc("Time left:          ");
   } 
   else
   {
      lcd_gotoxy(21,2);
      lcd_putc("                    ");
   }
}


void hien_thi_giao_dien_bonus()
{
   lcd_gotoxy(8,1);
   lcd_putc("BONUS.....   ");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"Rate: ___ ml/h      ");
   lcd_gotoxy(21,1);
   printf(lcd_putc,"Vol:       /%4lu ml ",vol);
   lcd_gotoxy(21,2);
   lcd_putc("                    ");
}

void hien_thi_thong_so_da_bom()
{
   lcd_gotoxy(26,1);
   printf(lcd_putc,"%4.1f",pumped_vol);
   if((vol!=0)&&(rate!=0)&&(mode_bonus==0))
   {
      unsigned int16 vol_left=abs(vol-(unsigned int16)pumped_vol);
      float tg_trans=(float)vol_left/(float)rate;
      gio=vol_left/rate;
      phut=(tg_trans-gio)*60;
      lcd_gotoxy(31,2);
      printf(lcd_putc,"%4luh %02um",gio,phut);
   }
}

