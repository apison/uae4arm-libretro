 /* 
  * UAE - The Un*x Amiga Emulator
  * 
  * Joystick emulation for Linux and BSD. They share too much code to
  * split this file.
  * 
  * Copyright 1997 Bernd Schmidt
  * Copyright 1998 Krister Walfridsson
  */

#include "sysconfig.h"
#include "sysdeps.h"

#include "config.h"
#include "uae.h"
#include "options.h"
#include "memory.h"
#include "custom.h"
#include "joystick.h"
#include "inputdevice.h"

extern unsigned char MXjoy[2];

#include "core-log.h"

static int delayjoy1=0;
static int delayjoy2=0;

void read_joystick(int nr, unsigned int *dir, int *button)
{
	//Autofire implementato su entrambi i  solo sui joystick 

	int    up  = (MXjoy[nr]>>0)&1;
	int  down  = (MXjoy[nr]>>1)&1;
	int  left  = (MXjoy[nr]>>2)&1;   
	int  right = (MXjoy[nr]>>3)&1;
	int b1	   = (MXjoy[nr]>>4)&1;
	int b2	   = (MXjoy[nr]>>5)&1;

	*dir = 0;
	*button = 0;

	  // normal joystick movement
	  if (left)
		up = !up;
		if (right)
		  down = !down;
	//  *dir = down | (right << 1) | (up << 8) | (left << 9);

	unsigned int dir2 = down | (right << 1) | (up << 8) | (left << 9);
	int but2= b1| b2<< 1;


	/**dir = dir2;
	*button =but2;*/
	
	//write_log("second_joystick_enable: %d  currprefs.input_autofire_framecnt: %d currprefs.input_autofire_framecnt_joy2: %d \n",second_joystick_enable,currprefs.input_autofire_framecnt,currprefs.input_autofire_framecnt_joy2);
	//write_log("num. joy: %d    delayjoy1: %d  delayjoy2: %d \n",nr,delayjoy1,delayjoy2);
	*dir = dir2;
	if (nr==0)
	{
		if (second_joystick_enable &&  currprefs.input_autofire_framecnt!=0 && delayjoy1 > currprefs.input_autofire_framecnt && but2)
		{
			//if(!but2)	*button=1;
			delayjoy1=0;
			*button |= (but2 & 1) << 1;

		}
		else
		{
			//*dir = dir2;
			*button =but2;
			
			
		}
		delayjoy1++;
		//metto  delayjoy2 a input_autofire_framecnt_joy2 se non ho premuto tasti alla prossima pressione scatterà
		if (delayjoy1>currprefs.input_autofire_framecnt) delayjoy1=currprefs.input_autofire_framecnt+1;
	}
	else
	{
		//Se joystick 2 verifico anche che non si sia appena abilitato l'evento autofire per il joy 0 
		//se cosi' è evito l'abilitazione, sembra che l'emulazione gestisca solo un evento di input alla volta
		//if (second_joystick_enable &&  currprefs.input_autofire_framecnt_joy2!=0 && delayjoy2 > currprefs.input_autofire_framecnt_joy2 && but2 && delayjoy1!=0)
		if (second_joystick_enable &&  currprefs.input_autofire_framecnt_joy2!=0 && delayjoy2 > currprefs.input_autofire_framecnt_joy2 && but2 )
		{
				//write_log("Entrato autofire joy2 \n");
	
			//if(!but2)	*button=1;
			delayjoy2=0;
			*button |= (but2 & 1) << 1;

		}
		else
		{
			//*dir = dir2;
			*button =but2;
			
		}
		delayjoy2++;
		//metto  delayjoy2 a input_autofire_framecnt_joy2 se non ho premuto tasti alla prossima pressione scatterà
		if (delayjoy2>currprefs.input_autofire_framecnt_joy2) delayjoy2=currprefs.input_autofire_framecnt_joy2+1;
		
	}
	//write_log("button: %d  but2: %d  b1: %d   b2: %d \n",*button,but2,b1,b2);
	
}

void handle_joymouse(void)
{
/*
	if (currprefs.pandora_custom_dpad == 1)
	{
    int mouseScale = currprefs.input_joymouse_multiplier / 2;

		if (buttonY) // slow mouse active
			mouseScale = currprefs.input_joymouse_multiplier / 10;

		if (dpadLeft)
		{
			lastmx -= mouseScale;
			newmousecounters=1;
		}
		if (dpadRight)
		{
			lastmx += mouseScale;
			newmousecounters=1;
		}
		if (dpadUp)
		{    
			lastmy -= mouseScale;
			newmousecounters=1;
		}
		if (dpadDown)
		{
			lastmy += mouseScale;
			newmousecounters=1;
		}
	}
*/
}

void init_joystick(void)
{
   
}

void close_joystick(void)
{

}
