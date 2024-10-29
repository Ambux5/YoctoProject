#ifndef DRIVER_INA219_BASIC_H
#define DRIVER_INA219_BASIC_H

#include "ina219_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ina219_example_driver ina219 example driver function
 * @brief    ina219 example driver modules
 * @ingroup  ina219_driver
 * @{
 */

/**
 * @brief ina219 basic example default definition
 */
#define INA219_BASIC_DEFAULT_BUS_VOLTAGE_RANGE            INA219_BUS_VOLTAGE_RANGE_32V             /**< set bus voltage range 32V */
#define INA219_BASIC_DEFAULT_BUS_VOLTAGE_ADC_MODE         INA219_ADC_MODE_12_BIT_1_SAMPLES         /**< set bus voltage adc mode 12 bit 1 sample */
#define INA219_BASIC_DEFAULT_SHUNT_VOLTAGE_ADC_MODE       INA219_ADC_MODE_12_BIT_1_SAMPLES         /**< set shunt voltage adc mode 12 bit 1 sample */
#define INA219_BASIC_DEFAULT_PGA                          INA219_PGA_320_MV                        /**< set pga 320 mV */

/**
 * @brief     basic example init
 * @param[in] addr_pin is the iic address pin
 * @param[in] r is the reference resistor value
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t ina219_basic_init(ina219_address_t addr_pin, double r);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ina219_basic_deinit(void);

/**
 * @brief      basic example read
 * @param[out] *mV points to a mV buffer
 * @param[out] *mA points to a mA buffer
 * @param[out] *mW points to a mW buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t ina219_basic_read(float *mV, float *mA, float *mW);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif