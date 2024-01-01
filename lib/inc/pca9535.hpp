// Header: PCA9535 Cpp Driver Header File
// File Name: pca9535.hpp
// Author: Turgay Hopal
// Date: 28.12.2023

#include <iostream>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

constexpr uint8_t CR_INPUT_PORT_0 = 0x00;
constexpr uint8_t CR_INPUT_PORT_1 = 0x01;
constexpr uint8_t CR_OUTPUT_PORT_0 = 0x02;
constexpr uint8_t CR_OUTPUT_PORT_1 = 0x03;
constexpr uint8_t CR_POLARITY_INV_PORT_0 = 0x04;
constexpr uint8_t CR_POLARITY_INV_PORT_1 = 0x05;
constexpr uint8_t CR_CONFIGURATION_PORT_0 = 0x06;
constexpr uint8_t CR_CONFIGURATION_PORT_1 = 0x07;

typedef struct
{
    const char *i2c_device_path;
    uint8_t slave_addr;
    uint8_t polarity;
} pca9535_config_t;

typedef struct
{
    uint8_t port_0_value;
    uint8_t port_1_value;
} pca9535_port_t;

enum
{
    PCA9535_PORT_0 = 0,
    PCA9535_PORT_1 = 1,
    PCA9535_PORT_BOTH = 2
};

enum
{
    PCA9535_PORT_DR_IN = 0xFF,
    PCA9535_PORT_DR_OUT = 0x00
};

enum
{
    PCA9535_POLARITY_NORMAL = 0x00,
    PCA9535_POLARITY_INVERTED = 0xFF
};

class PCA9535
{
private:
    pca9535_config_t config;
    void get_port_input_0(uint8_t *port_value);
    void get_port_input_1(uint8_t *port_value);
    void set_port_output_0(uint8_t port_value);
    void set_port_output_1(uint8_t port_value);
    void get_port_output_0(uint8_t *port_value);
    void get_port_output_1(uint8_t *port_value);
    void get_port_polarity_0(uint8_t *port_polarity);
    void get_port_polarity_1(uint8_t *port_polarity);
    void set_port_polarity_0(uint8_t port_polarity);
    void set_port_polarity_1(uint8_t port_polarity);
    void get_port_config_0(uint8_t *port_direction);
    void get_port_config_1(uint8_t *port_direction);
    void set_port_config_0(uint8_t port_direction);
    void set_port_config_1(uint8_t port_direction);
    void write_i2c(uint8_t register_addr, uint8_t data);
    void read_i2c(uint8_t register_addr, uint8_t *data);

public:
    pca9535_port_t port;

    PCA9535(pca9535_config_t config);
    int chip_available(void);
    void configure_port(uint8_t port_direction, uint8_t port_number);
    void set_port_value(uint8_t port_number);
    void get_port_value(uint8_t port_number);
};
