#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Inclui as bibliotecas do VL53L0X
#include "vl53l0x_api.h"

// Configuração do I2C
#define I2C_PORT i2c0
#define SDA_PIN 0  // GPIO0 (SDA - I2C0)
#define SCL_PIN 1  // GPIO1 (SCL - I2C0)

// Endereço padrão do VL53L0X
#define VL53L0X_DEFAULT_ADDRESS 0x29

VL53L0X_Dev_t dev;           // Estrutura do dispositivo VL53L0X
VL53L0X_DEV dev_ptr = &dev;  // Ponteiro para a estrutura

void i2c_init_vl53l0x() {
    i2c_init(I2C_PORT, 400 * 1000); // Inicializa I2C a 400kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

int main() {
    stdio_init_all();
    sleep_ms(2000); // Aguarda inicialização USB serial

    printf("Iniciando VL53L0X...\n");

    // Inicializa o I2C
    i2c_init_vl53l0x();

    // Configuração do dispositivo
    dev_ptr->I2cDevAddr = VL53L0X_DEFAULT_ADDRESS;
    dev_ptr->comms_type = 1; // Tipo de comunicação: I2C
    dev_ptr->comms_speed_khz = 400;

    // Inicialização do sensor
    int status = VL53L0X_DataInit(dev_ptr);
    if (status) {
        printf("Erro na inicialização do VL53L0X: %d\n", status);
        return -1;
    }

    printf("VL53L0X inicializado com sucesso!\n");

    // Configura modo de medição contínua
    status = VL53L0X_StartMeasurement(dev_ptr);
    if (status) {
        printf("Erro ao iniciar medição: %d\n", status);
        return -1;
    }

    while (true) {
    VL53L0X_RangingMeasurementData_t measurement;
    status = VL53L0X_PerformSingleRangingMeasurement(dev_ptr, &measurement);
    if (status == 0) {
        uint16_t mm = measurement.RangeMilliMeter;

        if (mm >= 8190) {
            printf("Distância: Fora de alcance\n");
        } else {
            float cm = mm / 10.0f;
            float m = mm / 1000.0f;
            printf("Distância: %5d mm | %5.1f cm | %4.2f m\n", mm, cm, m);
        }
    } else {
        printf("Erro ao medir distância: %d\n", status);
    }
    sleep_ms(500);
}



}
