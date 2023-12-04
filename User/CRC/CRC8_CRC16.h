/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       crc8_crc16.c/h
  * @brief      crc8 and crc16 calculate function, verify function, append function.
  *             crc8和crc16计算函数,校验函数,添加函数
  * @note
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Nov-11-2019     RM              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */
#ifndef CRC8_CRC16_H
#define CRC8_CRC16_H

#include "main.h"

/**
 * @brief          计算CRC8
 * @param[in]      pch_message: 数据
 * @param[in]      dw_length: 数据和校验的长度
 * @param[in]      ucCRC8:初始CRC8
 * @retval         计算完的CRC8
 */
extern uint8_t get_CRC8_check_sum(unsigned char *pchMessage, unsigned int dwLength, unsigned char ucCRC8);

/**
 * @brief          CRC8校验函数
 * @param[in]      pch_message: 数据
 * @param[in]      dw_length: 数据和校验的长度
 * @retval         真或者假
 */
extern uint32_t verify_CRC8_check_sum(unsigned char *pchMessage, unsigned int dwLength);

/**
 * @brief          添加CRC8到数据的结尾
 * @param[in]      pch_message: 数据
 * @param[in]      dw_length: 数据和校验的长度
 * @retval         none
 */
extern void append_CRC8_check_sum(unsigned char *pchMessage, unsigned int dwLength);

/**
 * @brief          计算CRC16
 * @param[in]      pch_message: 数据
 * @param[in]      dw_length: 数据和校验的长度
 * @param[in]      wCRC:初始CRC16
 * @retval         计算完的CRC16
 */
extern uint16_t get_CRC16_check_sum(uint8_t *pchMessage, uint32_t dwLength, uint16_t wCRC);

/**
 * @brief          CRC16校验函数
 * @param[in]      pch_message: 数据
 * @param[in]      dw_length: 数据和校验的长度
 * @retval         真或者假
 */
extern uint32_t verify_CRC16_check_sum(uint8_t *pchMessage, uint32_t dwLength);

/**
 * @brief          添加CRC16到数据的结尾
 * @param[in]      pch_message: 数据
 * @param[in]      dw_length: 数据和校验的长度
 * @retval         none
 */
extern void append_CRC16_check_sum(uint8_t *pchMessage, uint32_t dwLength);
#endif
