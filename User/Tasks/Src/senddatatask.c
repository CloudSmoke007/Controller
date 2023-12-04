#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "CRC8_CRC16.h"
#include "senddatatask.h"
#include "string.h"

/***********函数定义区******************/

static void Data_Concatenation(uint8_t *data, uint16_t data_lenth);

/*************全局变量区*****************/

Controller_t tx_data; // 自定义控制器发送的数据

void StartSendDataTask(void const *argument)
{
    // uint8_t index = 0;
    uint32_t wait_time = xTaskGetTickCount();
    for (;;)
    {
        uint8_t data[DATA_LENGTH] = {0x40, 0x50, 0x60, 0x70};
        Data_Concatenation(data, DATA_LENGTH);
        HAL_UART_Transmit(&huart1, (uint8_t *)(&tx_data), sizeof(tx_data), 50);
        osDelayUntil(&wait_time, 500);
    }
}

/**
 * @brief 数据拼接函数，将帧头、命令码、数据段、帧尾头拼接成一个数组
 * @param data 数据段的数组指针
 * @param data_lenth 数据段长度
 */
static void Data_Concatenation(uint8_t *data, uint16_t data_lenth)
{
    static uint8_t seq = 0;
    /// 帧头数据
    tx_data.frame_header.sof = 0xA5;                              // 数据帧起始字节，固定值为 0xA5
    tx_data.frame_header.data_length = data_lenth;                // 数据帧中数据段的长度
    tx_data.frame_header.seq = seq++;                             // 包序号
    append_CRC8_check_sum((uint8_t *)(&tx_data.frame_header), 5); // 添加帧头 CRC8 校验位
    /// 命令码ID
    tx_data.cmd_id = CONTROLLER_CMD_ID;
    /// 数据段
    memcpy(tx_data.data, data, data_lenth);
    /// 帧尾CRC16，整包校验
    append_CRC16_check_sum((uint8_t *)(&tx_data), DATA_FRAME_LENGTH);
}
