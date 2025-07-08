# 📏 Medição de Distância com Raspberry Pi Pico e VL53L0X

Este projeto utiliza o microcontrolador **Raspberry Pi Pico** e o sensor de distância **VL53L0X** para realizar medições em milímetros (mm), centímetros (cm) e metros (m), exibindo os resultados no console serial.

---

## 🛠️ Funcionalidades

✅ Inicializa o sensor **VL53L0X** via comunicação I2C.
✅ Realiza medições de distância a cada 500 ms.
✅ Converte automaticamente os valores de **milímetros** para **centímetros** e **metros**.
✅ Indica quando o objeto está **fora do alcance** do sensor (acima de \~2 metros).

---

## ⚙️ Requisitos

* [Raspberry Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/)
* Sensor **VL53L0X** (Time-of-Flight da STMicroelectronics)
* Cabo micro-USB para programação
* [Pico SDK](https://github.com/raspberrypi/pico-sdk) configurado no seu ambiente
* Ferramentas de build:

  * `cmake`
  * `arm-none-eabi-gcc`
  * `ninja` (opcional)

---

## 📦 Conexões

| VL53L0X Pin | Raspberry Pi Pico Pin |
| ----------- | --------------------- |
| SDA         | GP0 (I2C0 SDA)        |
| SCL         | GP1 (I2C0 SCL)        |
| VIN         | 3V3 (OUT)             |
| GND         | GND                   |

> 📝 *Certifique-se de usar resistores pull-up de 4.7kΩ nos pinos SDA e SCL caso o módulo não os tenha embutidos.*

---

## 🧑‍💻 Como Compilar e Executar

1. Clone este repositório:

   ```bash
   git clone https://github.com/seu-usuario/projeto-vl53l0x-pico.git
   cd projeto-vl53l0x-pico
   ```
