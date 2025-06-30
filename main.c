#include<lpc21xx.h>
#include<stdio.h>
#include"uart.h"
#include"lcd.h"
#include"spii.h"
#include"types.h"
#include"spi.h"
#include"types.h"
#include"rtr.h"
#include"mcp3208.h"

 #define cs 1<<7



int main()
{
	u8 sec = 0,min = 2,hours = 5,day = 5,date=5,month=6,year=25;
	char temp2[10];
   float s;
   int temp;
  
   lcd_config();
   init_i2c();
   Init_SPI0();
   lcd_string("data project");
   delay_ms(2000);
   lcd_cmd(0x01);
    uart0_init() ;

   rtc_write(sec,min,hours,day,date,month,year);
   
   while(1)
   {
	 s=Read_ADC_MCP3208(0);
	  temp=s*100;
	  rtc_read(&sec,&min,&hours,&day,&date,&month,&year);
		lcd_cmd(0x80);
		lcd_string("Time:");
		lcd_time_display(hours);
		sprintf(temp2, "%d",hours);
		uart0_str(temp2);
		uart0_tx(',');
		lcd_data(':');
		lcd_time_display(min);
		sprintf(temp2, "%d",min);
		uart0_str(temp2);
		 uart0_tx(',');
		lcd_data(':');
		lcd_time_display(sec);
		sprintf(temp2, "%d",sec);
		uart0_str(temp2);
		 uart0_tx(',');
		lcd_cmd(0xc0);
		lcd_string("temp:");
		lcd_time_display(temp);
		sprintf(temp2, "%d",temp);
		uart0_str(temp2);
		 uart0_tx('\n');
		lcd_data(' ');
	    lcd_data('C');
		delay_ms(5000);
		
	 
   }	
	 
}
									      