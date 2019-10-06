/*******************************************************************************
 * Copyright:		BUPT
 * File Name:		nrf24l01.c
 * Description:		NRF Driver.Ref benjiming
 * Author:			ZeroVoid
 * Version:			0.1
 * Data:			2019/10/02 Wed 16:28
 *******************************************************************************/
#include "nrf24l01.h"

/*******************************************************************************
 * NRF Private Macro
 *******************************************************************************/
#define NRF_PAYLOAD_SIZE					32 // NRF Payload Register Size(Bytes)

/*******************************************************************************
 * NRF Private Macro Functions
 *******************************************************************************/
#define NRF_SPI_TransmitReceive(pTxData, pRxData, len)   HAL_SPI_TransmitReceive(&NRF_SPI_Handle, pTxData, pRxData, len, 50)
#define NRF_SPI_Read(pRxData, len) HAL_SPI_Receive(&NRF_SPI_Handle, pRxData, len, 50)
#define NRF_SPI_Write(pTxData, len) HAL_SPI_Transmit(&NRF_SPI_Handle, pTxData, len, 50)

/*******************************************************************************
 * NRF Private Function Declaration
 *******************************************************************************/
/* NRF Register Write & Read -----------------------------------------------------*/
static void nrf_write_reg(uint8_t reg, const uint8_t *data, uint8_t len);
static void nrf_write_reg_byte(uint8_t reg, uint8_t value);
static void nrf_read_reg(uint8_t reg, uint8_t *data, uint8_t len);
static void nrf_read_reg_byte(uint8_t reg, uint8_t *data);

/* NRF SPI Communication Utils -----------------------------------------------------*/
static void nrf_spi_start(void);
static void nrf_spi_end(void);
static void nrf_spi_dealy(void);

/*******************************************************************************
 * NRF Private Val
 *******************************************************************************/
//static uint8_t nrf_spi_rx;
static uint8_t nrf_rx_data[32];
static uint8_t nrf_tx_data[32];

/*******************************************************************************
 * NRF Functions
 *******************************************************************************/
void nrf_init(void);
void nrf_stop(void);

void nrf_set_speed(NRF_SPEED speed) {
    char reg_old;
    nrf_read_reg_byte(NRF_REG_RF_SETUP, &reg_old);
	char reg_new = reg_old;

	reg_new &= ~(NRF_RF_SETUP_RF_DR_LOW | NRF_RF_SETUP_RF_DR_HIGH);

	switch (speed) {
	case NRF_SPEED_250K:
		reg_new |= NRF_RF_SETUP_RF_DR_LOW;
		break;

	case NRF_SPEED_1M:
		break;

	case NRF_SPEED_2M:
		reg_new |= NRF_RF_SETUP_RF_DR_HIGH;
		break;

	default:
		break;
	}

	if (reg_old != reg_new) {
		nrf_write_reg_byte(NRF_REG_RF_SETUP, reg_new);	// Update if we need
	}
}

void nrf_set_power(NRF_POWER power) {
    
}
void nrf_set_address_width(NRF_AW aw);
void nrf_set_crc_type(NRF_CRC crc_type);
void nrf_set_retr_retries(int retries);
void nrf_set_retr_delay(NRF_RETR_DELAY delay);
void nrf_set_rx_addr(int pipe, const char *address, int addr_len);
void nrf_set_tx_addr(const char *address, int addr_len);
void nrf_write_tx_payload(const char *data, int length);
void nrf_write_tx_payload_no_ack(const char *data, int length);
void nrf_write_ack_payload(int pipe, const char *data, int length);
void nrf_read_rx_payload(char *data, int length);
void nrf_set_frequency(int freq);
int nrf_get_frequency(void);
int nrf_get_address_width(void);
void nrf_power_up(void);
void nrf_power_down(void);
void nrf_mode_tx(void);
void nrf_mode_rx(void);
void nrf_enable_pipe_autoack(int pipes);
void nrf_enable_pipe_address(int pipes);
void nrf_enable_pipe_dlp(int pipes);
void nrf_enable_features(int features);


/*******************************************************************************
 * Private Function Definition
 *******************************************************************************/
/* NRF Register Write & Read -----------------------------------------------------*/
static void nrf_write_reg(uint8_t reg, const uint8_t *data, uint8_t len) {
    uint8_t cmd = NRF_CMD_WRITE_REGISTER | reg;

    nrf_spi_start();
    NRF_SPI_TransmitReceive(&cmd, 0, 1);
    NRF_SPI_Write(data, len);
    nrf_spi_end();
}

static void nrf_write_reg_byte(uint8_t reg, const uint8_t data) {
    nrf_write_reg(reg, &data, 1);
}

static void nrf_read_reg(uint8_t reg, uint8_t *data, uint8_t len) {
    uint8_t cmd = NRF_CMD_READ_REGISTER | reg;

    nrf_spi_start();
    NRF_SPI_TransmitReceive(&cmd, 0, 1);
    NRF_SPI_Read(data, len);
    nrf_spi_end();
    
}

static void nrf_read_reg_byte(uint8_t reg, uint8_t *data) {
    nrf_read_reg(reg, data, 1);
}
/* NRF SPI Communication Utils -----------------------------------------------------*/
static void nrf_spi_start(void) {
    HAL_GPIO_WritePin(NRF_SPI_CSN_GPIO_PORT, NRF_SPI_CSN_PIN, 0);
    NRF_SPI_Delay();
}

void nrf_spi_end(void) {
    NRF_SPI_Delay();
    HAL_GPIO_WritePin(NRF_SPI_CSN_GPIO_PORT, NRF_SPI_CSN_PIN, 1);
}

void nrf_spi_delay(void) {
    for (volatile int i = 0; i<5; i++) {
        UNUSED(i);
    }
}
