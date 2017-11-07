/**--------------------------------------------------------|
 * ------------------------- i2c --------------------------|
 * --------------------------------------------------------|
 * -----------| реализация функций интерфейса |------------|
 * -----------| и функция для работы с LIS331 |------------|
 * --------------------------------------------------------|
 * --------------------------------------------------------|
 * */

#include "lis.h"
#include <stdio.h>
#include "driver/i2c.h"
#include "esp_log.h"
#include <stdbool.h>

#define DATA_LENGTH          512  /*!<Data buffer length for test buffer*/
#define RW_TEST_LENGTH       129  /*!<Data length for r/w test, any value from 0-DATA_LENGTH*/
#define DELAY_TIME_BETWEEN_ITEMS_MS   1234 /*!< delay time between different test items */

#define LIS_I2C_ADDRESS   0x19
#define SCL_PIN    22
#define SDA_PIN    21
#define I2C_EXAMPLE_MASTER_NUM I2C_NUM_0
#define I2C_EXAMPLE_MASTER_FREQ_HZ    400000     /*!< I2C master clock frequency */


static void i2c_master_init()
{
    i2c_config_t i2c_config = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = SDA_PIN,
            .scl_io_num = SCL_PIN,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = I2C_EXAMPLE_MASTER_FREQ_HZ
    };
    i2c_param_config(I2C_NUM_0, &i2c_config );
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER,0 ,0 ,0);
}


//--------------------------------- Байты.   Уроверь 01. -------------------------------------------
bool write_byte(char data){

    esp_err_t espRc;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, ( LIS_I2C_ADDRESS << 1 ) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, data , true);
    i2c_master_stop(cmd);
    espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 30/portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    if (espRc == ESP_OK) {
        ESP_LOGD("i2c", "Command \"Write byte\"  success");
        return true;
    } else {
        ESP_LOGE("i2c", "Command \"Write byte\" failed. code: 0x%.2X", espRc);
        return false;
    }
}

uint8_t read_byte(){
    uint8_t read_data = 0;  // данные
    esp_err_t espRc;        // статус операции


    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, ( LIS_I2C_ADDRESS << 1 ) | I2C_MASTER_READ, true);
    i2c_master_read_byte(cmd, &read_data, true);
    i2c_master_stop(cmd);
    espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 30/portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    if (espRc == ESP_OK) {
        ESP_LOGD("i2c", "Command \"Read byte\" success");
    } else {
        ESP_LOGE("i2c", "Command \"Read byte\" failed. code: 0x%.2X", espRc);
    }
    return read_data;

}

//--------------------------------- Регистры. Уровень 02. -------------------------------------------
void readReg(uint8_t address, uint8_t *value){
    write_byte(address);
    *value = read_byte();
}

void writeReg(uint8_t address, uint8_t value){      //device address + register address + register value
    esp_err_t espRc;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, ( LIS_I2C_ADDRESS << 1 ) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, address , true);
    i2c_master_write_byte(cmd, value , true);
    i2c_master_stop(cmd);
    espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 30/portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    if (espRc == ESP_OK) {
        ESP_LOGI("i2c", "Command \"Write byte\"  success");
    } else {
        ESP_LOGE("i2c", "Command \"Write byte\" failed. code: 0x%.2X", espRc);
    }
}

//--------------------------------- Аккселерометр. Уровень 03. -----------------------------------------
void setPowerStatus(uint8_t power){
    uint8_t setting;
    readReg(LR_CTRL_REG1, &setting);
    // drop the power bits by leftshifting by 3
    setting=setting<<3;
    // move the rest of the settings back to normal
    setting=setting>>3;
    setting=setting|power;
    writeReg(LR_CTRL_REG1,setting);
}

void setScale(uint8_t state){
    uint8_t setting;
    readReg(LR_CTRL_REG4, &setting);
    setting &= ~(1<<FS0);
    setting &= ~(1<<FS1);
    if (state == LR_4G){
        setting |= 1<<FS0;
    }
    if (state == LR_8G){
        setting |= 1<<FS0;
        setting |= 1<<FS1;
    }
    writeReg(LR_CTRL_REG4,setting);
}

uint8_t getPowerStatus(){
    uint8_t state;
    readReg(LR_CTRL_REG1, &state);
    state=state>>5;
    state=state<<5;
    return state;
}

void setDataRate(uint8_t rate){
    uint8_t  setting;
    uint8_t  power;
    readReg(LR_CTRL_REG1, &setting);
    setting=setting<<6;
    setting=setting>>6;
    setting=setting|rate;
    power=getPowerStatus();
    setting=setting|power;
    writeReg(LR_CTRL_REG1,setting);
}


void setXEnable(bool state){
    uint8_t setting;
    readReg(LR_CTRL_REG1, &setting);
    setting &= ~    (1<<0);
    if (state) setting |= 1<<0;
    writeReg(LR_CTRL_REG1,setting);
}

int16_t getXValue(){
    uint8_t high;
    uint8_t low;
    readReg(LR_OUT_X_L, &low);
    readReg(LR_OUT_X_H, &high);
    return (low|(high << 8));
}


