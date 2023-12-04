#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "CRC8_CRC16.h"
#include "senddatatask.h"
#include "string.h"

/***********����������******************/

static void Data_Concatenation(uint8_t *data, uint16_t data_lenth);

/*************ȫ�ֱ�����*****************/

Controller_t tx_data; // �Զ�����������͵�����

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
 * @brief ����ƴ�Ӻ�������֡ͷ�������롢���ݶΡ�֡βͷƴ�ӳ�һ������
 * @param data ���ݶε�����ָ��
 * @param data_lenth ���ݶγ���
 */
static void Data_Concatenation(uint8_t *data, uint16_t data_lenth)
{
    static uint8_t seq = 0;
    /// ֡ͷ����
    tx_data.frame_header.sof = 0xA5;                              // ����֡��ʼ�ֽڣ��̶�ֵΪ 0xA5
    tx_data.frame_header.data_length = data_lenth;                // ����֡�����ݶεĳ���
    tx_data.frame_header.seq = seq++;                             // �����
    append_CRC8_check_sum((uint8_t *)(&tx_data.frame_header), 5); // ���֡ͷ CRC8 У��λ
    /// ������ID
    tx_data.cmd_id = CONTROLLER_CMD_ID;
    /// ���ݶ�
    memcpy(tx_data.data, data, data_lenth);
    /// ֡βCRC16������У��
    append_CRC16_check_sum((uint8_t *)(&tx_data), DATA_FRAME_LENGTH);
}
