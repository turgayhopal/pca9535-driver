// Header: PCA9535 Cpp Driver Soruce File
// File Name: pca9535.cpp
// Author: Turgay Hopal
// Date: 28.12.2023

#include "../inc/pca9535.hpp"

PCA9535::PCA9535(pca9535_config_t config)
{
    this->config.i2c_device_path = config.i2c_device_path;
    this->config.polarity = config.polarity;
    this->config.slave_addr = config.slave_addr;
}

int PCA9535::chip_available(void)
{
    uint8_t data;
    this->read_i2c(0x00, &data);
    if (data == 0xFF)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void PCA9535::configure_port(uint8_t port_direction, uint8_t port_number)
{
    if (port_number == PCA9535_PORT_0)
    {
        this->set_port_config_0(port_direction);
        this->set_port_polarity_0(config.polarity);
    }
    else if (port_number == PCA9535_PORT_1)
    {
        this->set_port_config_1(port_direction);
        this->set_port_polarity_1(config.polarity);
        this->set_port_polarity_1(config.polarity);
    }
    else if (port_number == PCA9535_PORT_BOTH)
    {
        this->set_port_config_0(port_direction);
        this->set_port_config_1(port_direction);
        this->set_port_polarity_0(config.polarity);
        this->set_port_polarity_1(config.polarity);
    }
}
void PCA9535::set_port_value(uint8_t port_number)
{
    if (port_number == PCA9535_PORT_0)
    {
        this->set_port_output_0(port.port_0_value);
    }
    else if (port_number == PCA9535_PORT_1)
    {
        this->set_port_output_1(port.port_1_value);
    }
    else if (port_number == PCA9535_PORT_BOTH)
    {
        this->set_port_output_0(port.port_0_value);
        this->set_port_output_1(port.port_1_value);
    }
}
void PCA9535::get_port_value(uint8_t port_number)
{
    if (port_number == PCA9535_PORT_0)
    {
        this->get_port_input_0(&this->port.port_0_value);
    }
    else if (port_number == PCA9535_PORT_1)
    {
        this->get_port_input_1(&this->port.port_1_value);
    }
    else if (port_number == PCA9535_PORT_BOTH)
    {
        this->get_port_input_0(&this->port.port_0_value);
        this->get_port_input_1(&this->port.port_1_value);
    }
}
void PCA9535::get_port_input_0(uint8_t *port_value)
{
    this->read_i2c(CR_INPUT_PORT_0, port_value);
}
void PCA9535::get_port_input_1(uint8_t *port_value)
{
    this->read_i2c(CR_INPUT_PORT_1, port_value);
}
void PCA9535::set_port_output_0(uint8_t port_value)
{
    this->write_i2c(CR_OUTPUT_PORT_0, port_value);
}
void PCA9535::set_port_output_1(uint8_t port_value)
{
    this->write_i2c(CR_OUTPUT_PORT_1, port_value);
}
void PCA9535::get_port_output_0(uint8_t *port_value)
{
    this->read_i2c(CR_OUTPUT_PORT_0, port_value);
}
void PCA9535::get_port_output_1(uint8_t *port_value)
{
    this->read_i2c(CR_OUTPUT_PORT_1, port_value);
}
void PCA9535::get_port_polarity_0(uint8_t *port_polarity)
{
    this->read_i2c(CR_POLARITY_INV_PORT_0, port_polarity);
}
void PCA9535::get_port_polarity_1(uint8_t *port_polarity)
{
    this->read_i2c(CR_POLARITY_INV_PORT_1, port_polarity);
}
void PCA9535::set_port_polarity_0(uint8_t port_polarity)
{
    this->write_i2c(CR_POLARITY_INV_PORT_0, port_polarity);
}
void PCA9535::set_port_polarity_1(uint8_t port_polarity)
{
    this->write_i2c(CR_POLARITY_INV_PORT_1, port_polarity);
}
void PCA9535::get_port_config_0(uint8_t *port_direction)
{
    this->read_i2c(CR_CONFIGURATION_PORT_0, port_direction);
}
void PCA9535::get_port_config_1(uint8_t *port_direction)
{
    this->read_i2c(CR_CONFIGURATION_PORT_1, port_direction);
}
void PCA9535::set_port_config_0(uint8_t port_direction)
{
    this->write_i2c(CR_CONFIGURATION_PORT_0, port_direction);
}
void PCA9535::set_port_config_1(uint8_t port_direction)
{
    this->write_i2c(CR_CONFIGURATION_PORT_1, port_direction);
}

void PCA9535::write_i2c(uint8_t register_addr, uint8_t data)
{
    int file;

    if ((file = open(this->config.i2c_device_path, O_RDWR)) < 0)
    {
    }
    else
    {
        if (ioctl(file, I2C_SLAVE, this->config.slave_addr) < 0)
        {
        }
        else
        {
            char buffer[2];
            buffer[0] = register_addr;
            buffer[1] = data;
            if (write(file, buffer, sizeof(buffer)) == sizeof(buffer))
            {
            }
        }
    }

    close(file);
}
void PCA9535::read_i2c(uint8_t register_addr, uint8_t *data)
{
    int file;

    if ((file = open(this->config.i2c_device_path, O_RDWR)) < 0)
    {
        *data = 0;
    }
    else
    {
        if (ioctl(file, I2C_SLAVE, this->config.slave_addr) < 0)
        {
            *data = 0;
        }
        else
        {
            if (write(file, &register_addr, 1) != 1)
            {
                *data = 0;
            }
            else
            {
                if (read(file, data, 1) != 1)
                {
                    *data = 0;
                }
            }
        }
    }

    close(file);
}
