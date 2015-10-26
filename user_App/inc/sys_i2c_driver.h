
#ifndef  __SYS_I2C_DRIVER_H__
#define __SYS_I2C_DRIVER_H__


#define I2C_Speed 100000
#define I2C2_SLAVE_ADDRESS7     0x30
#define I2C2_DELAY_TIME       2

#define CLK_TIME  20

#define I2C_SCL1_Port    30
#define I2C_SDA1_Port    7

#define I2C_SCL2_Port    15
#define I2C_SDA2_Port    14



#define I2C_SCL1_High() 	nrf_gpio_pin_set(I2C_SCL1_Port)
#define I2C_SCL1_Low() 	 nrf_gpio_pin_clear(I2C_SCL1_Port)

#define I2C_SDA1_High()	nrf_gpio_pin_set(I2C_SDA1_Port)
#define I2C_SDA1_Low()	 nrf_gpio_pin_clear(I2C_SDA1_Port)

#define I2C_SCL2_High()	nrf_gpio_pin_set(I2C_SCL2_Port)
#define I2C_SCL2_Low()	 nrf_gpio_pin_clear(I2C_SCL2_Port)

#define I2C_SDA2_High()	nrf_gpio_pin_set(I2C_SDA2_Port)
#define I2C_SDA2_Low()	 nrf_gpio_pin_clear(I2C_SDA2_Port)

#define I2C_SDA1_INPUT() nrf_gpio_cfg_input(I2C_SDA1_Port,NRF_GPIO_PIN_NOPULL)
#define I2C_SDA2_INPUT() nrf_gpio_cfg_input(I2C_SDA2_Port,NRF_GPIO_PIN_NOPULL)

#define I2C_SDA1_OUTPUT() nrf_gpio_cfg_output(I2C_SDA1_Port)
#define I2C_SDA2_OUTPUT() nrf_gpio_cfg_output(I2C_SDA2_Port)

#define I2C_SDA1_READ()  nrf_gpio_pin_read(I2C_SDA1_Port)
#define I2C_SDA2_READ()  nrf_gpio_pin_read(I2C_SDA2_Port)


/****************   i2c driver **************************/

#define TWI_READ_BIT                 (0x01)        //!< If this bit is set in the address field, transfer direction is from slave to master.

#define TWI_ISSUE_STOP               ((bool)true)  //!< Parameter for @ref twi_master_transfer
#define TWI_DONT_ISSUE_STOP          ((bool)false) //!< Parameter for @ref twi_master_transfer
	
#define TWI_MASTER_CONFIG_CLOCK_PIN_NUMBER  (30U) // (21U)
#define TWI_MASTER_CONFIG_DATA_PIN_NUMBER   (7U) // (22U)

#define TWI_SCL_HIGH()   do { NRF_GPIO->OUTSET = (1UL << TWI_MASTER_CONFIG_CLOCK_PIN_NUMBER); } while(0)   /*!< Pulls SCL line high */
#define TWI_SCL_LOW()    do { NRF_GPIO->OUTCLR = (1UL << TWI_MASTER_CONFIG_CLOCK_PIN_NUMBER); } while(0)   /*!< Pulls SCL line low  */
#define TWI_SDA_HIGH()   do { NRF_GPIO->OUTSET = (1UL << TWI_MASTER_CONFIG_DATA_PIN_NUMBER);  } while(0)   /*!< Pulls SDA line high */
#define TWI_SDA_LOW()    do { NRF_GPIO->OUTCLR = (1UL << TWI_MASTER_CONFIG_DATA_PIN_NUMBER);  } while(0)   /*!< Pulls SDA line low  */
#define TWI_SDA_INPUT()  do { NRF_GPIO->DIRCLR = (1UL << TWI_MASTER_CONFIG_DATA_PIN_NUMBER);  } while(0)   /*!< Configures SDA pin as input  */
#define TWI_SDA_OUTPUT() do { NRF_GPIO->DIRSET = (1UL << TWI_MASTER_CONFIG_DATA_PIN_NUMBER);  } while(0)   /*!< Configures SDA pin as output */
#define TWI_SCL_OUTPUT() do { NRF_GPIO->DIRSET = (1UL << TWI_MASTER_CONFIG_CLOCK_PIN_NUMBER); } while(0)   /*!< Configures SCL pin as output */
/*lint -restore */

#define TWI_SDA_READ() ((NRF_GPIO->IN >> TWI_MASTER_CONFIG_DATA_PIN_NUMBER) & 0x1UL)                     /*!< Reads current state of SDA */
#define TWI_SCL_READ() ((NRF_GPIO->IN >> TWI_MASTER_CONFIG_CLOCK_PIN_NUMBER) & 0x1UL)                    /*!< Reads current state of SCL */

#define TWI_DELAY() nrf_delay_us(4) /*!< Time to wait when pin states are changed. For fast-mode the delay can be zero and for standard-mode 4 us delay is sufficient. */


/*********************************************************/
extern u8 sys_i2c_busy_flag;
extern u8 sys_i2c2_busy_flag;



void GPIO_I2C_port_initial(void);


void i2c1_start_condition(void);
void i2c1_stop_condition(void);
void i2c1_nack(void);
void i2c1_ack(void);
unsigned char  i2c1_read_byte(char ack_en);
void  i2c1_write_byte(unsigned char write_data, char ack_en);
void I2C1_CommandWrite(char SlaveAddr, char Command);
char I2C1_BufferWrite(char SlaveAddr, char WriteAddr, char* pBuffer,char NumByteToWrite);
char I2C1_BufferRead(char SlaveAddr, char ReadAddr, char* pBuffer, int NumByteToRead);


void i2c2_start_condition(void);
void i2c2_stop_condition(void);
void i2c2_nack(void);
void i2c2_ack(void);
unsigned char  i2c2_read_byte(char ack_en);
void  i2c2_write_byte(unsigned char write_data, char ack_en);
void I2C2_CommandWrite(char SlaveAddr, char Command);
char I2C2_BufferWrite(char SlaveAddr, char WriteAddr, char* pBuffer,char NumByteToWrite);
char I2C2_BufferRead(char SlaveAddr, char ReadAddr, char* pBuffer, int NumByteToRead);



/**************  i2c driver ********/
bool twi_master_init(void);
bool twi_master_transfer(uint8_t address, uint8_t *data, uint8_t data_length, bool issue_stop_condition);
char IIC_write(uint8_t device_addr, uint8_t register_addr, uint8_t *register_data, uint8_t write_length);
char IIC_read(uint8_t device_addr, uint8_t register_addr, uint8_t *register_data, uint8_t read_length);


#endif

