
#include "use.h"
#include "GC9A01.h"

GC9A01 circle_lcd = GC9A01{
	hspi1,
	GC9A01_CS_GPIO_Port, GC9A01_CS_Pin,
	GC9A01_DC_GPIO_Port, GC9A01_DC_Pin,
	GC9A01_RES_GPIO_Port, GC9A01_RES_Pin
};

struct GC9A01_frame frame = {{0,0},{239,239}};

extern void setup(void){
	circle_lcd.init();
	circle_lcd.set_frame(frame);
}

extern void loop(void){
    u08 color[3];

    /* Triangle */
    delay_ms(1000);
    color[0] = 0xFF;
    color[1] = 0xFF;
    for (int x = 0; x < 240; x++) {
        for (int y = 0; y < 240; y++) {
            if (x < y) {
                color[2] = 0xFF;
            } else {
                color[2] = 0x00;
            }
            if (x == 0 && y == 0) {
            	circle_lcd.write_datas(color, sizeof(color));
            } else {
            	circle_lcd.write_datas(color, sizeof(color));
            }
        }
    }

    /* Rainbow */
    delay_ms(1000);
    float frequency = 0.026;
    for (int x = 0; x < 240; x++) {
        color[0] = sin(frequency*x + 0) * 127 + 128;
        color[1] = sin(frequency*x + 2) * 127 + 128;
        color[2] = sin(frequency*x + 4) * 127 + 128;
        for (int y = 0; y < 240; y++) {
            if (x == 0 && y == 0) {
            	circle_lcd.write_datas(color, sizeof(color));
            } else {
            	circle_lcd.write_datas(color, sizeof(color));
            }
        }
    }

    /* Checkerboard */
    delay_ms(1000);
    for (int x = 0; x < 240; x++) {
        for (int y = 0; y < 240; y++) {
            if ((x / 10) % 2 ==  (y / 10) % 2) {
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
            } else {
                color[0] = 0x00;
                color[1] = 0x00;
                color[2] = 0x00;
            }
            if (x == 0 && y == 0) {
            	circle_lcd.write_datas(color, sizeof(color));
            } else {
            	circle_lcd.write_datas(color, sizeof(color));
            }
        }
    }

    /* Swiss flag */
    delay_ms(1000);
    color[0] = 0xFF;
    for (int x = 0; x < 240; x++) {
        for (int y = 0; y < 240; y++) {
            if ((x >= 1*48 && x < 4*48 && y >= 2*48 && y < 3*48) ||
                (x >= 2*48 && x < 3*48 && y >= 1*48 && y < 4*48)) {
                color[1] = 0xFF;
                color[2] = 0xFF;
            } else {
                color[1] = 0x00;
                color[2] = 0x00;
            }
            if (x == 0 && y == 0) {
            	circle_lcd.write_datas(color, sizeof(color));
            } else {
            	circle_lcd.write_datas(color, sizeof(color));
            }
        }
    }
}

