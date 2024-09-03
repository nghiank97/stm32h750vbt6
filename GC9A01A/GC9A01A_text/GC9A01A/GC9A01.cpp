#include "main.h"
#include "GC9A01.h"

#define ORIENTATION 2   // Set the display orientation 0,1,2,3

GC9A01::GC9A01(
	SPI_HandleTypeDef _spi,
	GPIO_TypeDef* _cs_port, u16 _cs_pin,
	GPIO_TypeDef* _dc_port, u16 _dc_pin,
	GPIO_TypeDef* _rs_port, u16 _rs_pin)
{
	spi = _spi;

	cs_port = _cs_port;
	dc_port = _dc_port;
	rs_port = _rs_port;

	cs_pin = _cs_pin;
	dc_pin = _dc_pin;
	rs_pin = _rs_pin;
}

inline void GC9A01::reset(void) {
    HAL_GPIO_WritePin(rs_port, rs_pin, GPIO_PIN_RESET);
    delay_ms(5);
    HAL_GPIO_WritePin(rs_port, rs_pin, GPIO_PIN_SET);
    delay_ms(120);
}

inline void GC9A01::choose_data(void) {
    HAL_GPIO_WritePin(dc_port, dc_pin, GPIO_PIN_SET);
}

inline void GC9A01::choose_cmd(void) {
    HAL_GPIO_WritePin(dc_port, dc_pin, GPIO_PIN_RESET);
}

inline void GC9A01::chip_select(void) {
	HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_RESET);
}

inline void GC9A01::chip_unselect(void) {
	HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_SET);
}

inline void GC9A01::spi_tx(u08 *data, size_t len) {
	HAL_SPI_Transmit(&spi, data, len, 1000);
}

void GC9A01::write_cmd(u08 cmd) {
	choose_cmd();
	chip_select();
	spi_tx(&cmd, 1);
    chip_unselect();
}

void GC9A01::write_data(u08 val) {
	choose_data();
	chip_select();
	spi_tx(&val, 1);
    chip_unselect();
}

void GC9A01::write_datas(u08 *data, size_t len) {
	choose_data();
	chip_select();
	spi_tx(data, len);
    chip_unselect();
}

void GC9A01::init(void) {

	chip_select();
    delay_ms(5);
    reset();
    /* Initial Sequence */

    write_cmd(0xEF);
    write_cmd(0xEB);
    write_data(0x14);
    write_cmd(0xFE);
    write_cmd(0xEF);

    write_cmd(0xEB);
    write_cmd(0x14);

    write_cmd(0x84);
    write_data(0x40);

    write_cmd(0x85);
    write_data(0xFF);

    write_cmd(0x86);
    write_data(0xFF);

    write_cmd(0x87);
    write_data(0xFF);

    write_cmd(0x88);
    write_data(0x0A);

    write_cmd(0x89);
    write_data(0x21);

    write_cmd(0x8A);
    write_data(0x00);

    write_cmd(0x8B);
    write_data(0x80);

    write_cmd(0x8C);
    write_data(0x01);

    write_cmd(0x8D);
    write_data(0x01);

    write_cmd(0x8E);
    write_data(0xFF);

    write_cmd(0x8F);
    write_data(0xFF);


    write_cmd(0xB6);
    write_data(0x00);
    write_data(0x00);

    write_cmd(0x36);

#if ORIENTATION == 0
    write_data(0x18);
#elif ORIENTATION == 1
    write_data(0x28);
#elif ORIENTATION == 2
    write_data(0x48);
#else
    write_data(0x88);
#endif

    write_cmd(COLOR_MODE);
    write_data(COLOR_MODE__18_BIT);

    write_cmd(0x90);
    write_data(0x08);
    write_data(0x08);
    write_data(0x08);
    write_data(0x08);

    write_cmd(0xBD);
    write_data(0x06);

    write_cmd(0xBC);
    write_data(0x00);

    write_cmd(0xFF);
    write_data(0x60);
    write_data(0x01);
    write_data(0x04);

    write_cmd(0xC3);
    write_data(0x13);
    write_cmd(0xC4);
    write_data(0x13);

    write_cmd(0xC9);
    write_data(0x22);

    write_cmd(0xBE);
    write_data(0x11);

    write_cmd(0xE1);
    write_data(0x10);
    write_data(0x0E);

    write_cmd(0xDF);
    write_data(0x21);
    write_data(0x0c);
    write_data(0x02);

    write_cmd(0xF0);
    write_data(0x45);
    write_data(0x09);
    write_data(0x08);
    write_data(0x08);
    write_data(0x26);
    write_data(0x2A);

    write_cmd(0xF1);
    write_data(0x43);
    write_data(0x70);
    write_data(0x72);
    write_data(0x36);
    write_data(0x37);
    write_data(0x6F);

    write_cmd(0xF2);
    write_data(0x45);
    write_data(0x09);
    write_data(0x08);
    write_data(0x08);
    write_data(0x26);
    write_data(0x2A);

    write_cmd(0xF3);
    write_data(0x43);
    write_data(0x70);
    write_data(0x72);
    write_data(0x36);
    write_data(0x37);
    write_data(0x6F);

    write_cmd(0xED);
    write_data(0x1B);
    write_data(0x0B);

    write_cmd(0xAE);
    write_data(0x77);

    write_cmd(0xCD);
    write_data(0x63);

    write_cmd(0x70);
    write_data(0x07);
    write_data(0x07);
    write_data(0x04);
    write_data(0x0E);
    write_data(0x0F);
    write_data(0x09);
    write_data(0x07);
    write_data(0x08);
    write_data(0x03);

    write_cmd(0xE8);
    write_data(0x34);

    write_cmd(0x62);
    write_data(0x18);
    write_data(0x0D);
    write_data(0x71);
    write_data(0xED);
    write_data(0x70);
    write_data(0x70);
    write_data(0x18);
    write_data(0x0F);
    write_data(0x71);
    write_data(0xEF);
    write_data(0x70);
    write_data(0x70);

    write_cmd(0x63);
    write_data(0x18);
    write_data(0x11);
    write_data(0x71);
    write_data(0xF1);
    write_data(0x70);
    write_data(0x70);
    write_data(0x18);
    write_data(0x13);
    write_data(0x71);
    write_data(0xF3);
    write_data(0x70);
    write_data(0x70);

    write_cmd(0x64);
    write_data(0x28);
    write_data(0x29);
    write_data(0xF1);
    write_data(0x01);
    write_data(0xF1);
    write_data(0x00);
    write_data(0x07);

    write_cmd(0x66);
    write_data(0x3C);
    write_data(0x00);
    write_data(0xCD);
    write_data(0x67);
    write_data(0x45);
    write_data(0x45);
    write_data(0x10);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);

    write_cmd(0x67);
    write_data(0x00);
    write_data(0x3C);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x01);
    write_data(0x54);
    write_data(0x10);
    write_data(0x32);
    write_data(0x98);

    write_cmd(0x74);
    write_data(0x10);
    write_data(0x85);
    write_data(0x80);
    write_data(0x00);
    write_data(0x00);
    write_data(0x4E);
    write_data(0x00);

    write_cmd(0x98);
    write_data(0x3e);
    write_data(0x07);

    write_cmd(0x35);
    write_cmd(0x21);

    write_cmd(0x11);
    delay_ms(120);
    write_cmd(0x29);
    delay_ms(20);
}

void GC9A01::set_frame(struct GC9A01_frame frame) {
    u08 data[4];
    write_cmd(COL_ADDR_SET);
    data[0] = (frame.start.X >> 8) & 0xFF;
    data[1] = frame.start.X & 0xFF;
    data[2] = (frame.end.X >> 8) & 0xFF;
    data[3] = frame.end.X & 0xFF;
    write_datas(data, sizeof(data));

    write_cmd(ROW_ADDR_SET);
    data[0] = (frame.start.Y >> 8) & 0xFF;
    data[1] = frame.start.Y & 0xFF;
    data[2] = (frame.end.Y >> 8) & 0xFF;
    data[3] = frame.end.Y & 0xFF;
    write_datas(data, sizeof(data));
}
