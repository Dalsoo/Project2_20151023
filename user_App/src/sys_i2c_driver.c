#include "sys_main.h"
#include "nrf_delay.h"


u8 sys_i2c_busy_flag=0;
u8 sys_i2c2_busy_flag=0;

void GPIO_I2C_port_initial(void)
{
   	nrf_gpio_cfg_output(I2C_SCL1_Port);
	nrf_gpio_cfg_output(I2C_SDA1_Port);
	nrf_gpio_cfg_output(I2C_SCL2_Port);
	nrf_gpio_cfg_output(I2C_SDA2_Port);
	
	I2C_SCL1_High();
	I2C_SDA1_High();
	I2C_SCL2_High();
	I2C_SDA2_High();
	
}





/********   i2c channel 1  **********/


void  i2c1_send_NACK(void)
{
//	I2C_SDA1_OUTPUT();
	I2C_SCL1_Low();
	I2C_SDA1_High(); 
	delay_time(CLK_TIME);
	I2C_SCL1_High();
	

}

void  i2c1_send_ACK(void)
{
//	I2C_SDA1_OUTPUT();
	I2C_SCL1_Low();
	I2C_SDA1_Low(); 
	delay_time(CLK_TIME);
	I2C_SCL1_High();
	

}

//----------------------------------------
void i2c1_start_condition(void)
{
	
     I2C_SCL1_High();
    I2C_SDA1_High() ;
    delay_time(CLK_TIME);

    I2C_SDA1_Low(); 
    delay_time(CLK_TIME);
    I2C_SCL1_Low();
    delay_time(CLK_TIME);

}

////--------------------------------------

void i2c1_stop_condition(void)
{

    I2C_SDA1_Low(); 
    I2C_SCL1_Low();

    delay_time(CLK_TIME);

    I2C_SCL1_High();
    delay_time(CLK_TIME);
    I2C_SDA1_High();
    delay_time(CLK_TIME);
  //  I2C_SCL1_Low();
 
}





void i2c1_nack(void)
{

    I2C_SDA1_High();
    delay_time(CLK_TIME);
    I2C_SCL1_Low();
    delay_time(CLK_TIME);
    I2C_SCL1_High();
    delay_time(CLK_TIME);
    I2C_SCL1_Low();
    delay_time(CLK_TIME);
}
void i2c1_ack(void)
{

    I2C_SDA1_INPUT();
  //  I2C_SDA1_Low();
    delay_time(CLK_TIME);
    I2C_SCL1_Low();
    delay_time(CLK_TIME);
    I2C_SCL1_High();
    delay_time(CLK_TIME);
    I2C_SCL1_Low();
  
	I2C_SDA1_OUTPUT();
}
unsigned char  i2c1_read_byte(char ack_en)
{
      
	int i;
	unsigned char temp=0;
	
       I2C_SDA1_INPUT(); 

	
	
	for(i=0;i<8;i++)
	{
		temp=temp<<1;

		I2C_SCL1_Low() ;
		delay_time(CLK_TIME);
		I2C_SCL1_High();
		delay_time(CLK_TIME);
		if(I2C_SDA1_READ())  
			temp|=1;  

		//delay_time(CLK_TIME);
	
	}
		  I2C_SDA1_OUTPUT();
          if(ack_en)
        {

          // i2c1_ack();
		i2c1_send_ACK();
        }else
        {
		i2c1_send_NACK();
        }
        I2C_SCL1_Low();
	
    
	return temp;
}
void  i2c1_write_byte(unsigned char write_data, char ack_en)
{
   
	int i;
  

	for(i=0;i<8;i++)
	{

                 I2C_SCL1_Low();
                
		delay_time(CLK_TIME);
		if((write_data & (0x80>>i)))
                  I2C_SDA1_High();
		else
                  I2C_SDA1_Low();
		
               delay_time(CLK_TIME);
                    I2C_SCL1_High();
		delay_time(CLK_TIME);
                   I2C_SCL1_Low();
	
	}
        
        if(ack_en)
        {
           i2c1_ack();
            
        }else
        {
            i2c1_nack();
        }
                  

}

void I2C1_CommandWrite(char SlaveAddr, char Command)
{
sys_i2c_busy_flag= 1;
     i2c1_start_condition();
     i2c1_write_byte(SlaveAddr,1);
     i2c1_write_byte(Command,1);
     i2c1_stop_condition();
   sys_i2c_busy_flag= 0;
    
}




/*******************************************************************************
* Function Name  : I2C_BufferWrite
* Description    : Writes more than one byte to the device with a single WRITE
*                  cycle. The number of byte can't exceed the device buffer size.
* Input          : - pBuffer : pointer to the buffer containing the data to be 
*                    written to the device.
*                  - WriteAddr : device's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the device.
* Output         : None
* Return         : None
*******************************************************************************/
char I2C1_BufferWrite(char SlaveAddr, char WriteAddr, char* pBuffer,char NumByteToWrite)
{
   //     INT8U err;
   // OSSemPend(sys_I2C_SemLock, 0 ,&err); 
	sys_i2c_busy_flag= 1;
     i2c1_start_condition();
     i2c1_write_byte(SlaveAddr,1);
     i2c1_write_byte(WriteAddr,1);
      while(NumByteToWrite--)  
    {
    /* Send the current byte */
    i2c1_write_byte(*pBuffer,1); 
    //    i2c_write_byte(0xff,1); 
      /* Point to the next byte to be written */
    pBuffer++; 
    }
     i2c1_stop_condition();
 sys_i2c_busy_flag= 0;
    return 0x00;
}

/********   i2c channel 2  **********/
void  i2c2_send_ACK(void)
{
//	I2C_SDA1_OUTPUT();
	I2C_SCL2_Low();
	I2C_SDA2_Low(); 
	delay_time(CLK_TIME);
	I2C_SCL2_High();
	

}
void  i2c2_send_NACK(void)
{
//	I2C_SDA1_OUTPUT();
	I2C_SCL2_Low();
	I2C_SDA2_High(); 
	delay_time(CLK_TIME);
	I2C_SCL2_High();
	

}

//----------------------------------------
void i2c2_start_condition(void)
{
     I2C_SCL2_High();
    I2C_SDA2_High() ;
    delay_time(CLK_TIME);

    I2C_SDA2_Low(); 
    delay_time(CLK_TIME);
    I2C_SCL2_Low();
    delay_time(CLK_TIME);

}

////--------------------------------------

void i2c2_stop_condition(void)
{

    I2C_SDA2_Low(); 
    I2C_SCL2_Low();

    delay_time(CLK_TIME);

    I2C_SCL2_High();
    delay_time(CLK_TIME);
    I2C_SDA2_High();
    delay_time(CLK_TIME);
    I2C_SCL2_Low();
 
}





void i2c2_nack(void)
{

    I2C_SDA2_High();
    delay_time(CLK_TIME);
    I2C_SCL2_Low();
    delay_time(CLK_TIME);
    I2C_SCL2_High();
    delay_time(CLK_TIME);
    I2C_SCL2_Low();
    delay_time(CLK_TIME);
}
void i2c2_ack(void)
{

    I2C_SDA2_INPUT();
    I2C_SDA2_Low();
    delay_time(CLK_TIME);
    I2C_SCL2_Low();
    delay_time(CLK_TIME);
    I2C_SCL2_High();
    delay_time(CLK_TIME);
    I2C_SCL2_Low();
  
	I2C_SDA2_OUTPUT();
}
unsigned char  i2c2_read_byte(char ack_en)
{
      
	int i;
	unsigned char temp=0;
	
       I2C_SDA2_INPUT(); 
	
	for(i=0;i<8;i++)
	{
		temp=temp<<1;

		I2C_SCL2_Low() ;
		delay_time(CLK_TIME);
		I2C_SCL2_High();
		delay_time(CLK_TIME);
		if(I2C_SDA2_READ())  
			temp|=1;  

		//delay_time(CLK_TIME);
	
	}
	I2C_SDA2_OUTPUT();
          if(ack_en)
        {
       //    i2c2_ack();
            i2c2_send_ACK();
        }else
        {
		i2c2_send_NACK();
        }
        I2C_SCL2_Low();

    
	return temp;
}
void  i2c2_write_byte(unsigned char write_data, char ack_en)
{
   
	int i;
  

	for(i=0;i<8;i++)
	{

                 I2C_SCL2_Low();
                
		delay_time(CLK_TIME);
		if((write_data & (0x80>>i)))
                  I2C_SDA2_High();
		else
                  I2C_SDA2_Low();
		
               delay_time(CLK_TIME);
                    I2C_SCL2_High();
		delay_time(CLK_TIME);
                   I2C_SCL2_Low();
	
	}
        
        if(ack_en)
        {
           i2c2_ack();
            
        }else
        {
            i2c2_nack();
        }
                  

}
void I2C2_CommandWrite(char SlaveAddr, char Command)
{
     sys_i2c_busy_flag = 1;
     i2c2_start_condition();
     i2c2_write_byte(SlaveAddr,1);
     i2c2_write_byte(Command,1);
     i2c2_stop_condition();
   sys_i2c_busy_flag = 0;
    
}

/*******************************************************************************
* Function Name  : I2C_BufferWrite
* Description    : Writes more than one byte to the device with a single WRITE
*                  cycle. The number of byte can't exceed the device buffer size.
* Input          : - pBuffer : pointer to the buffer containing the data to be 
*                    written to the device.
*                  - WriteAddr : device's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the device.
* Output         : None
* Return         : None
*******************************************************************************/
char I2C2_BufferWrite(char SlaveAddr, char WriteAddr, char* pBuffer,char NumByteToWrite)
{
   //     INT8U err;
   // OSSemPend(sys_I2C_SemLock, 0 ,&err); 
	sys_i2c_busy_flag = 1;
     i2c2_start_condition();
     i2c2_write_byte(SlaveAddr,1);
     i2c2_write_byte(WriteAddr,1);
      while(NumByteToWrite--)  
    {
    /* Send the current byte */
    i2c2_write_byte(*pBuffer,1); 
    //    i2c_write_byte(0xff,1); 
      /* Point to the next byte to be written */
    pBuffer++; 
    }
     i2c2_stop_condition();
 sys_i2c_busy_flag = 0;
    return 0x00;
}
/*******************************************************************************
* Function Name  : I2C_BufferRead
* Description    : Reads a block of data from the I2C device.
* Input          : - pBuffer : pointer to the buffer that receives the data read 
*                    from the I2C device.
*                  - ReadAddr : I2C device internal address to read from.
*                  - NumByteToRead : number of bytes to read from the I2C device.
* Output         : None
* Return         : None
*******************************************************************************/
char I2C2_BufferRead(char SlaveAddr, char ReadAddr, char* pBuffer, int NumByteToRead)
{
	sys_i2c_busy_flag = 1;
      i2c2_start_condition();
     i2c2_write_byte(SlaveAddr,1);
     i2c2_write_byte(ReadAddr+1,1);
      while(NumByteToRead--)  
    {
    /* Send the current byte */
    i2c2_write_byte(*pBuffer,1); 
      /* Point to the next byte to be written */
    pBuffer++; 
    }
     i2c2_stop_condition();
    sys_i2c_busy_flag = 0;
       return 1;
}


/***************   i2c  driver ****************/
static bool twi_master_clear_bus(void)
{
    uint32_t twi_state;
    bool bus_clear;
    uint32_t clk_pin_config;
    uint32_t data_pin_config;
        
    // Save and disable TWI hardware so software can take control over the pins
    twi_state        = NRF_TWI1->ENABLE;
    NRF_TWI1->ENABLE = TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos;
    
    clk_pin_config                                        =  \
            NRF_GPIO->PIN_CNF[TWI_MASTER_CONFIG_CLOCK_PIN_NUMBER];    
    NRF_GPIO->PIN_CNF[TWI_MASTER_CONFIG_CLOCK_PIN_NUMBER] =   \
            (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
          | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
          | (GPIO_PIN_CNF_PULL_Pullup    << GPIO_PIN_CNF_PULL_Pos)  \
          | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
          | (GPIO_PIN_CNF_DIR_Output     << GPIO_PIN_CNF_DIR_Pos);    

    data_pin_config                                      = \
        NRF_GPIO->PIN_CNF[TWI_MASTER_CONFIG_DATA_PIN_NUMBER];
    NRF_GPIO->PIN_CNF[TWI_MASTER_CONFIG_DATA_PIN_NUMBER] = \
        (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
      | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
      | (GPIO_PIN_CNF_PULL_Pullup    << GPIO_PIN_CNF_PULL_Pos)  \
      | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
      | (GPIO_PIN_CNF_DIR_Output     << GPIO_PIN_CNF_DIR_Pos);    
      
    TWI_SDA_HIGH();
    TWI_SCL_HIGH();
    TWI_DELAY();

    if ((TWI_SDA_READ() == 1) && (TWI_SCL_READ() == 1))
    {
        bus_clear = true;
    }
    else
    {
        uint_fast8_t i;
        bus_clear = false;

        // Clock max 18 pulses worst case scenario(9 for master to send the rest of command and 9 for slave to respond) to SCL line and wait for SDA come high
        for (i=18; i--;)
        {
            TWI_SCL_LOW();
            TWI_DELAY();
            TWI_SCL_HIGH();
            TWI_DELAY();

            if (TWI_SDA_READ() == 1)
            {
                bus_clear = true;
                break;
            }
        }
    }
    
    NRF_GPIO->PIN_CNF[TWI_MASTER_CONFIG_CLOCK_PIN_NUMBER] = clk_pin_config;
    NRF_GPIO->PIN_CNF[TWI_MASTER_CONFIG_DATA_PIN_NUMBER]  = data_pin_config;

    NRF_TWI1->ENABLE = twi_state;

    return bus_clear;
}


bool twi_master_init(void)
{
    /* To secure correct signal levels on the pins used by the TWI
       master when the system is in OFF mode, and when the TWI master is 
       disabled, these pins must be configured in the GPIO peripheral.
    */
    NRF_GPIO->PIN_CNF[TWI_MASTER_CONFIG_CLOCK_PIN_NUMBER] =     \
        (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
      | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
      | (GPIO_PIN_CNF_PULL_Pullup    << GPIO_PIN_CNF_PULL_Pos)  \
      | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
      | (GPIO_PIN_CNF_DIR_Input      << GPIO_PIN_CNF_DIR_Pos);   

    NRF_GPIO->PIN_CNF[TWI_MASTER_CONFIG_DATA_PIN_NUMBER] =      \
        (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
      | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
      | (GPIO_PIN_CNF_PULL_Pullup    << GPIO_PIN_CNF_PULL_Pos)  \
      | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
      | (GPIO_PIN_CNF_DIR_Input      << GPIO_PIN_CNF_DIR_Pos);    

    NRF_TWI1->EVENTS_RXDREADY = 0;
    NRF_TWI1->EVENTS_TXDSENT  = 0;
    NRF_TWI1->PSELSCL         = TWI_MASTER_CONFIG_CLOCK_PIN_NUMBER;
    NRF_TWI1->PSELSDA         = TWI_MASTER_CONFIG_DATA_PIN_NUMBER;
    NRF_TWI1->FREQUENCY       = TWI_FREQUENCY_FREQUENCY_K100 << TWI_FREQUENCY_FREQUENCY_Pos;
   // NRF_PPI->CH[0].EEP        = (uint32_t)&NRF_TWI1->EVENTS_BB;
   // NRF_PPI->CH[0].TEP        = (uint32_t)&NRF_TWI1->TASKS_SUSPEND;
   // NRF_PPI->CHENCLR          = PPI_CHENCLR_CH0_Msk;
    NRF_TWI1->ENABLE          = TWI_ENABLE_ENABLE_Enabled << TWI_ENABLE_ENABLE_Pos;

    return twi_master_clear_bus();
}

#define MAX_TIMEOUT_LOOPS             (20000UL)        /**< MAX while loops to wait for RXD/TXD event */


static bool twi_master_write(uint8_t *data, uint8_t data_length, bool issue_stop_condition)
{
    uint32_t timeout = MAX_TIMEOUT_LOOPS;   /* max loops to wait for EVENTS_TXDSENT event*/

    if (data_length == 0)
    {
        /* Return false for requesting data of size 0 */
        return false;
    }

    NRF_TWI1->TXD           = *data++;
    NRF_TWI1->TASKS_STARTTX = 1;

    while (true)
    {
        while(NRF_TWI1->EVENTS_TXDSENT == 0 && (--timeout))
        {
            // Do nothing.
        }

        if (timeout == 0)
        {
            NRF_TWI1->EVENTS_STOPPED = 0; 
            NRF_TWI1->TASKS_STOP     = 1; 
            
            /* Wait until stop sequence is sent */
            while(NRF_TWI1->EVENTS_STOPPED == 0) 
            { 
                // Do nothing.
            }
            
            /* Timeout before receiving event*/
            return false;
        }

        NRF_TWI1->EVENTS_TXDSENT = 0;
        if (--data_length == 0)
        {
            break;
        }

        NRF_TWI1->TXD = *data++;
    }
    
    if (issue_stop_condition) 
    { 
        NRF_TWI1->EVENTS_STOPPED = 0; 
        NRF_TWI1->TASKS_STOP     = 1; 
        /* Wait until stop sequence is sent */ 
        while(NRF_TWI1->EVENTS_STOPPED == 0) 
        { 
            // Do nothing.
        } 
    }
    return true;
}


static bool twi_master_read(uint8_t *data, uint8_t data_length, bool issue_stop_condition)
{
    uint32_t timeout = MAX_TIMEOUT_LOOPS;   /* max loops to wait for RXDREADY event*/

    if (data_length == 0)
    {
        /* Return false for requesting data of size 0 */
        return false;
    }
    NRF_TWI1->EVENTS_RXDREADY = 0;
    NRF_TWI1->TASKS_STARTRX   = 1;
    
    while (true)
    {
        while((NRF_TWI1->EVENTS_RXDREADY == 0) && (--timeout))
        {    
            // Do nothing.
        }
        NRF_TWI1->EVENTS_RXDREADY = 0;

        if (timeout == 0)
        {
            /* Wait until stop sequence is sent */ 
            NRF_TWI1->EVENTS_STOPPED = 0; 
            NRF_TWI1->TASKS_STOP     = 1; 
            while(NRF_TWI1->EVENTS_STOPPED == 0) 
            { 
                // Do nothing.
            }
            return false;
        }

        *data++ = NRF_TWI1->RXD;

        /* Configure PPI to stop TWI master before we get last BB event */
        if (--data_length == 0)
        {
            NRF_TWI1->EVENTS_STOPPED = 0;
            NRF_TWI1->TASKS_STOP = 1;
            break;
        }
    }

    /* Wait until stop sequence is sent */
    while(NRF_TWI1->EVENTS_STOPPED == 0)
    {
        // Do nothing.
    }
    return true;
}

bool twi_master_transfer(uint8_t address, uint8_t *data, uint8_t data_length, bool issue_stop_condition)
{
    bool transfer_succeeded = false;
    if (data_length > 0 && twi_master_clear_bus())
    {
        NRF_TWI1->ADDRESS = (address >> 1);

        if ((address & TWI_READ_BIT))
        {
            transfer_succeeded = twi_master_read(data, data_length, issue_stop_condition);
        }
        else
        {
            transfer_succeeded = twi_master_write(data, data_length, issue_stop_condition);
        }
    }
    return transfer_succeeded;
}


/* add by ll */

char IIC_write(uint8_t device_addr, uint8_t register_addr, uint8_t *register_data, uint8_t write_length)
{
    uint8_t send[10], i;
    if( (write_length > 9) || (write_length < 1) )
    {
        sys_printf("write length error.\r\n");
        return false;
    }
    else
    {
        device_addr = (device_addr << 1) & 0xFE;
        send[0] = register_addr;
        
        for(i = 1; i <= write_length; i++)
        {
            send[i] = register_data[i-1];
        }
        
        twi_master_transfer(device_addr, send, write_length + 1, TWI_ISSUE_STOP); 
        return true;
    }
}


char IIC_read(uint8_t device_addr, uint8_t register_addr, uint8_t *register_data, uint8_t read_length)
{
    if(read_length < 1)
    {
       sys_printf("read length error.\r\n");
        return false;
    }
    else
    {
        device_addr = (device_addr << 1) & 0xFE;
        twi_master_transfer(device_addr, &register_addr, 1, TWI_DONT_ISSUE_STOP); // write
        
        device_addr = device_addr | 0x01;
        twi_master_transfer(device_addr, register_data, read_length, TWI_ISSUE_STOP); // read
        return true;
    }
}



