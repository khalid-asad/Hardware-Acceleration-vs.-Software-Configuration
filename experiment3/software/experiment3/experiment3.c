// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

// This is the embedded software for the
// LCD / Camera design

#include <stdio.h>
#include "io.h"
#include "system.h"
#include "sys/alt_irq.h"
#include "sys/alt_stdio.h"
#include "priv/alt_busy_sleep.h"




void TouchPanel_int(void) {
    static int exposure = 0x0400, run = 1;
    static int config = 0;
    static int set = -1;
	static int new_config = 4;
    int TP_val, x_val, y_val, key = 6;

    TP_val = IORD(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 0);
    x_val = (TP_val >> 20) & 0xFF; y_val = (TP_val >> 4) & 0xFF;

    if (((TP_val >> 31) & 0x1) && (x_val >= 0xC9) && (x_val <= 0xF1)) {
        if ((y_val >= 0x17) && (y_val <= 0x33)) { // Key 0
            key = 0;
            IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x1);
        }
        if ((y_val >= 0x3D) && (y_val <= 0x58)) { // Key 1
            key = 1;
            IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x2);
        }
        if ((y_val >= 0x62) && (y_val <= 0x7E)) { // Key 2
            key = 2;
            IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x4);
        }
        if ((y_val >= 0x88) && (y_val <= 0xA4)) { // Key 3
            key = 3;
            IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x8);
        }
        if ((y_val >= 0xAE) && (y_val <= 0xC9)) { // Key 4
            key = 4;
            IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x10);
        }
        if ((y_val >= 0xD3) && (y_val <= 0xEF)) { // Key 5
            key = 5;
            IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x20);
        }
    } else IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x0);
    
    if (IORD(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 2) & 0x2) { // posedge
    	switch (key) {
        	case 0 :
        		if (run == 1) {
                    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x8);
                    run = 0;
                }else {
                    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x4);
                    run = 1;
                }
                break;
            case 1 : 
                config++; if (config == 4) config = 0;
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 4, config);
                break;
            case 2 : 
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 4, 4);
                break;
            case 3 :
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 4, 5);
                set++;
                if (set == 6){
                	set = 0;
                }
                if (set==0){
                	IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 5, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 6, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 7, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 8, 0.5);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 9, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 10, 0.5);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 11, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 12, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 13, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 14, 3);
                }else if (set==1){
                	IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 5, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 6, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 7, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 8, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 9, 8);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 10, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 11, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 12, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 13, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 14, 4);
                }else if (set==2){
                	IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 5, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 6, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 7, 2);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 8, 2);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 9, 4);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 10, 2);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 11, 2);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 12, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 13, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 14, 4);
                }else if (set==3){
                	IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 5, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 6, -2);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 7, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 8, -2);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 9, 5);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 10, -2);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 11, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 12, -2);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 13, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 14, 0);
                }else if (set==4){
                	IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 5, -1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 6, -1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 7, -1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 8, -1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 9, 9);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 10, -1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 11, -1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 12, -1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 13, -1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 14, 0);
                }else if (set==5){
                	IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 5, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 6, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 7, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 8, 0.5);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 9, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 10, 0.5);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 11, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 12, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 13, 1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 14, 3);
                }else if (set==6){
                	IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 5, 0);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 6, -1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 7, 0);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 8, -1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 9, 5);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 10, -1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 11, 0);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 12, -1);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 13, 0);
					IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 14, 0);
                }
                break;
            case 4 :
                if (exposure <= 0xFEFF) exposure += 0x0100;
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 0, exposure);
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x2);
                break;                              
            case 5 : 
                if (exposure >= 0x0100) exposure -= 0x0100;
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 0, exposure);
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x2);
                break;
        }
    }
    
    TP_val = IORD(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 2);
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 2, TP_val & 0x30);
}

int main() 
{
    alt_irq_register(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_IRQ, NULL, (void *)TouchPanel_int);

    printf("Experiment 3!\n");

    // initialize the touch panel
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 2, 0x0);
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 1, 0x400000);

    // initialize the camera
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 0, 0x0400);
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x2);
    while ((IORD(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1) & 0x1) == 0);
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x4);

    // initialize the buttons
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 1, 0x0);
    
    // initialize the filter pipe
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 4, 0);

    while (1);
    
    return 0;
}
