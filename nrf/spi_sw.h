#ifndef SPI_SW_H_
#define SPI_SW_H_

#include "hw.h"
#include "ch.h"
#include "hal.h"

// Functions
void spi_sw_init(void);
void spi_sw_stop(void);
void spi_sw_change_pins(
		stm32_gpio_t *port_csn, int pin_csn,
		stm32_gpio_t *port_sck, int pin_sck,
		stm32_gpio_t *port_mosi, int pin_mosi,
		stm32_gpio_t *port_miso, int pin_miso);
void spi_sw_transfer(char *in_buf, const char *out_buf, int length);
void spi_sw_begin(void);
void spi_sw_end(void);

#endif /* SPI_SW_H_ */
