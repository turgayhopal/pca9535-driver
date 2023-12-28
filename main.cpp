#include <iostream>
#include "lib/inc/pca9535.hpp"

using namespace std;

int main()
{

    pca9535_config_t config_t;

    config_t.i2c_device_path = "/dev/i2c-1";
    config_t.polarity = PCA9535_POLARITY_NORMAL;
    config_t.slave_addr = 0x20;

    PCA9535 pca9535{config_t};

    if (pca9535.chip_available() == 1)
    {
        pca9535.configure_port(PCA9535_PORT_DR_OUT, PCA9535_PORT_1);

        while (1) {
            pca9535.port.port_1_value |= (1 << 0);
            pca9535.set_port_value(PCA9535_PORT_1);
            usleep(500000); // 500 ms
            cout << "Out Off " << endl;
            pca9535.port.port_1_value &= ~(1 << 0);
            pca9535.set_port_value(PCA9535_PORT_1);
            usleep(500000); // 500 ms
            cout << "Out On " << endl;
        }
    }

    return 0;
}
