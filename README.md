# GpioExpansionBoard使用文档

`GpioExpansionBoard`是一个GPIO扩展板主类，它提供了多种功能，包括设置GPIO模式、设置GPIO输出电平、获取GPIO输出电平、获取GPIO ADC电平值、设置GPIO开发板PWM频率、设置PWM占空比和驱动舵机转动到指定角度等。

## API使用文档

### 枚举定义

#### 扩展板默认I2C地址：0x24

| GpioExpansionBoard::kDeviceI2cAddressDefault | 扩展板默认I2C地址：0x24 |
| --- | --- |

#### GPIO可配置模式

| GpioExpansionBoard::GpioMode | 描述 |
| --- | --- |
| GpioExpansionBoard::GpioMode::kNone | 无效模式，请勿直接使用，程序内部自用 |
| GpioExpansionBoard::GpioMode::kInputPullUp | 输入模式，默认拉高电平 |
| GpioExpansionBoard::GpioMode::kInputPullDown | 输入模式，默认拉低电平 |
| GpioExpansionBoard::GpioMode::kInputFloating | 浮空输入模式 |
| GpioExpansionBoard::GpioMode::kOutput | 输出模式 |
| GpioExpansionBoard::GpioMode::kAdc | ADC模式 |
| GpioExpansionBoard::GpioMode::kPwm | PWM输出模式（**只支持引脚E1 ~ E2**） |

#### GPIO引脚

| GpioExpansionBoard::GpioPin | 描述 |
| --- | --- |
| GpioExpansionBoard::GpioPin::kGpioPinE0 | 引脚E0 |
| GpioExpansionBoard::GpioPin::kGpioPinE1 | 引脚E1 |
| GpioExpansionBoard::GpioPin::kGpioPinE2 | 引脚E2 |
| GpioExpansionBoard::GpioPin::kGpioPinE3 | 引脚E3 |
| GpioExpansionBoard::GpioPin::kGpioPinE4 | 引脚E4 |
| GpioExpansionBoard::GpioPin::kGpioPinE5 | 引脚E5 |
| GpioExpansionBoard::GpioPin::kGpioPinE6 | 引脚E6 |
| GpioExpansionBoard::GpioPin::kGpioPinE7 | 引脚E7 |

### 构造函数

#### `GpioExpansionBoard(uint8_t device_i2c_address = kDeviceI2cAddressDefault)`

- 描述：构造函数。
- 参数：
  - `device_i2c_address`：扩展板I2C地址，默认值为0x24。
- 返回值：无。

### GPIO模式相关函数

#### `bool SetGpioMode(GpioPin gpio_pin, GpioMode mode)`

- 描述：设置GPIO模式。
- 参数：
  - `gpio_pin`：GPIO引脚。枚举类型，取值范围参考：[GPIO引脚](#GPIO引脚)
  - `mode`：GPIO模式。枚举类型，取值范围参考：[GPIO可配置模式](#GPIO可配置模式)
- 返回值：成功返回true，失败返回false。

#### `bool SetGpioLevel(GpioPin gpio_pin, uint8_t level)`

- 描述：设置GPIO输出电平。
- 参数：
  - `gpio_pin`：GPIO引脚。枚举类型，取值范围参考：[GPIO引脚](#GPIO引脚)
  - `level`：电平值，0为低电平，1为高电平。
- 返回值：成功返回true，失败返回false。

#### `uint8_t GetGpioLevel(GpioPin gpio_pin)`

- 描述：获取GPIO输出电平。
- 参数：
  - `gpio_pin`：GPIO引脚。枚举类型，取值范围参考：[GPIO引脚](#GPIO引脚)
- 返回值：电平值，0为低电平，1为高电平。

### ADC相关函数

#### `uint16_t GetGpioAdcValue(GpioPin gpio_pin)`

- 描述：获取GPIO ADC电平值。
- 参数：
  - `gpio_pin`：GPIO引脚。枚举类型，取值范围参考：[GPIO引脚](#GPIO引脚)
- 返回值：ADC电平值。范围0 ~ 1023

### PWM相关函数

#### `bool SetPwmFrequency(uint32_t frequency)`

- 描述：设置GPIO开发板PWM频率。
- 参数：
  - `frequency`：PWM频率，单位：HZ。
- 返回值：成功返回true，失败返回false。

#### `bool SetPwmDuty(GpioPin gpio_pin, uint8_t duty)`

- 描述：设置PWM的占空比，使用前需要将引脚的模式设置为pwm模式(kPwm)。
- 参数：
  - `gpio_pin`：GPIO引脚。枚举类型，取值范围参考：[GPIO引脚](#GPIO引脚)
  - `duty`：占空比，范围: 0 ~ 100, 单位%，代表占空比 0% ~ 100%。
- 返回值：成功返回true，失败返回false。

### 舵机相关函数

#### `bool SetServoAngle(GpioPin gpio_pin, float angle)`

- 描述：驱动舵机转动到指定角度，**只支持E1 ~ E2**。
- 参数：
  - `gpio_pin`：GPIO引脚。枚举类型，取值范围参考：[GPIO引脚](#GPIO引脚)
  - `angle`：角度值，范围0 ~ 180。
- 返回值：成功返回true，失败返回false。

## 示例程序

### ADC输入

```c++
#include <Arduino.h>

#include "gpio_expansion_board.h"

// 创建 GpioExpansionBoard 实例
GpioExpansionBoard gpio_expansion_board;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  Serial.println("setup");

  // 配置E0为ADC模式
  gpio_expansion_board.SetGpioMode(GpioExpansionBoard::kGpioPinE0, GpioExpansionBoard::kAdc);
}

void loop() {
  Serial.print("adc value:");
  // 读取E0的ADC值并打印
  Serial.println(gpio_expansion_board.GetGpioAdcValue(GpioExpansionBoard::kGpioPinE0));
  delay(100);
}

```

### 数字高低电平输入

```c++
#include <Arduino.h>

#include "gpio_expansion_board.h"

// 创建 GpioExpansionBoard 实例
GpioExpansionBoard gpio_expansion_board;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  Serial.println("setup");

  // 配置E0为输入模式，默认拉高电平
  gpio_expansion_board.SetGpioMode(GpioExpansionBoard::kGpioPinE0, GpioExpansionBoard::kInputPullDown);
}

void loop() {
  Serial.print("digital value:");
  // 读取E0的数字值并打印
  Serial.println(gpio_expansion_board.GetGpioLevel(GpioExpansionBoard::kGpioPinE0));
  delay(100);
}
```

### 数字高低电平输出

```c++

#include <Arduino.h>

#include "gpio_expansion_board.h"

// 创建 GpioExpansionBoard 实例
GpioExpansionBoard gpio_expansion_board;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  Serial.println("setup");

  // 配置E0为输出模式
  gpio_expansion_board.SetGpioMode(GpioExpansionBoard::kGpioPinE0, GpioExpansionBoard::kOutput);
}

void loop() {
  // 设置E0的输出高电平
  gpio_expansion_board.SetGpioLevel(GpioExpansionBoard::kGpioPinE0, 1);
  delay(100);
  // 设置E0的输出低电平
  gpio_expansion_board.SetGpioLevel(GpioExpansionBoard::kGpioPinE0, 0);
  delay(100);
}
```

### 舵机控制(只支持E1 ~ E2)

```c++
#include <Arduino.h>

#include "gpio_expansion_board.h"

// 创建 GpioExpansionBoard 实例
GpioExpansionBoard gpio_expansion_board;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  Serial.println("setup");

  // 使用舵机需要把gpio口设置为pwm模式，这里将E1口设置为pwm模式
  gpio_expansion_board.SetGpioMode(GpioExpansionBoard::kGpioPinE1, GpioExpansionBoard::kPwm);

  // 使用舵机需要把gpio口设置为pwm模式，这里将E2口设置为pwm模式
  gpio_expansion_board.SetGpioMode(GpioExpansionBoard::kGpioPinE2, GpioExpansionBoard::kPwm);
}

// 注意，舵机控制只支持E1 ~ E2
void loop() {
  // 设置E1舵机转动到0度位置
  gpio_expansion_board.SetServoAngle(GpioExpansionBoard::kGpioPinE1, 0);
  delay(500);

  // 设置E2舵机转动到0度位置
  gpio_expansion_board.SetServoAngle(GpioExpansionBoard::kGpioPinE2, 0);
  delay(500);

  // 设置E1舵机转动到90度位置
  gpio_expansion_board.SetServoAngle(GpioExpansionBoard::kGpioPinE1, 90);
  delay(500);

  // 设置E2舵机转动到90度位置
  gpio_expansion_board.SetServoAngle(GpioExpansionBoard::kGpioPinE2, 90);
  delay(500);

  // 设置E1舵机转动到180度位置
  gpio_expansion_board.SetServoAngle(GpioExpansionBoard::kGpioPinE1, 180);
  delay(500);

  // 设置E2舵机转动到180度位置
  gpio_expansion_board.SetServoAngle(GpioExpansionBoard::kGpioPinE2, 180);
  delay(500);
}
```

### PWM输出

```c++
#include <Arduino.h>

#include "gpio_expansion_board.h"

// 创建 GpioExpansionBoard 实例
GpioExpansionBoard gpio_expansion_board;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  Serial.println("setup");

  // 配置扩展板pwm频率为50hz
  gpio_expansion_board.SetPwmFrequency(50);

  // 配置E1为pwm输出模式
  gpio_expansion_board.SetGpioMode(GpioExpansionBoard::kGpioPinE1, GpioExpansionBoard::kPwm);
}

void loop() {
  // 设置E1的pwm输出占空比为30
  gpio_expansion_board.SetPwmDuty(GpioExpansionBoard::kGpioPinE1, 30);
  delay(1000);

  // 设置E1的pwm输出占空比为70
  gpio_expansion_board.SetPwmDuty(GpioExpansionBoard::kGpioPinE1, 70);
  delay(1000);
}
```
