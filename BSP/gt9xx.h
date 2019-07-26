/* drivers/input/touchscreen/gt9xx.h
 * 
 * 2010 - 2013 Goodix Technology.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be a reference 
 * to you, when you are integrating the GOODiX's CTP IC into your system, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 */

#ifndef _GOODIX_GT9XX_H
#define _GOODIX_GT9XX_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f4xx_hal.h"

#ifndef NULL
  #define NULL        0
#endif

/**
 * struct i2c_msg - an I2C transaction segment beginning with START
 * @addr: Slave address, either seven or ten bits.  When this is a ten
 *	bit address, I2C_M_TEN must be set in @flags and the adapter
 *	must support I2C_FUNC_10BIT_ADDR.
 * @flags: I2C_M_RD is handled by all adapters.  No other flags may be
 *	provided unless the adapter exported the relevant I2C_FUNC_*
 *	flags through i2c_check_functionality().
 * @len: Number of data bytes in @buf being read from or written to the
 *	I2C slave address.  For read transactions where I2C_M_RECV_LEN
 *	is set, the caller guarantees that this buffer can hold up to
 *	32 bytes in addition to the initial length byte sent by the
 *	slave (plus, if used, the SMBus PEC); and this value will be
 *	incremented by the number of block data bytes received.
 * @buf: The buffer into which data is read, or from which it's written.
 *
 * An i2c_msg is the low level representation of one segment of an I2C
 * transaction.  It is visible to drivers in the @i2c_transfer() procedure,
 * to userspace from i2c-dev, and to I2C adapter drivers through the
 * @i2c_adapter.@master_xfer() method.
 *
 * Except when I2C "protocol mangling" is used, all I2C adapters implement
 * the standard rules for I2C transactions.  Each transaction begins with a
 * START.  That is followed by the slave address, and a bit encoding read
 * versus write.  Then follow all the data bytes, possibly including a byte
 * with SMBus PEC.  The transfer terminates with a NAK, or when all those
 * bytes have been transferred and ACKed.  If this is the last message in a
 * group, it is followed by a STOP.  Otherwise it is followed by the next
 * @i2c_msg transaction segment, beginning with a (repeated) START.
 *
 * Alternatively, when the adapter supports I2C_FUNC_PROTOCOL_MANGLING then
 * passing certain @flags may have changed those standard protocol behaviors.
 * Those flags are only for use with broken/nonconforming slaves, and with
 * adapters which are known to support the specific mangling options they
 * need (one or more of IGNORE_NAK, NO_RD_ACK, NOSTART, and REV_DIR_ADDR).
 */
struct i2c_msg {
	uint8_t addr;	/* slave address			*/
	uint16_t flags;
#define I2C_M_TEN		0x0010	/* this is a ten bit chip address */
#define I2C_M_RD		0x0001	/* read data, from slave to master */
#define I2C_M_NOSTART		0x4000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_REV_DIR_ADDR	0x2000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_IGNORE_NAK	0x1000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NO_RD_ACK		0x0800	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_RECV_LEN		0x0400	/* length will be first received byte */
	uint16_t len;		/* msg length				*/
	uint8_t *buf;		/* pointer to msg data			*/
};


typedef enum 
{
	GT9157=0,
	GT911=1,
}TOUCH_IC;

//***************************PART1:ON/OFF define*******************************

#define GTP_DEBUG_ON                    0
#define GTP_DEBUG_ARRAY_ON              0
#define GTP_DEBUG_FUNC_ON               0

//*************************** PART2:TODO define **********************************


//以下配置已改成数组，在c文件中
//*************************** PART2:TODO define **********************************

// TODO: define your own default or for Sensor_ID == 0 config here. 
// The predefined one is just a sample config, which is not suitable for your tp in most cases.
// 5寸屏GT9157驱动配置
//#define CTP_CFG_GT9157 {\
//0x00,0x20,0x03,0xE0,0x01,0x05,0x3C,0x00,0x01,0x08,\
//0x28,0x0C,0x50,0x32,0x03,0x05,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x17,0x19,0x1E,0x14,0x8B,0x2B,0x0D,\
//0x33,0x35,0x0C,0x08,0x00,0x00,0x00,0x9A,0x03,0x11,\
//0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x32,0x00,0x00,\
//0x00,0x20,0x58,0x94,0xC5,0x02,0x00,0x00,0x00,0x04,\
//0xB0,0x23,0x00,0x93,0x2B,0x00,0x7B,0x35,0x00,0x69,\
//0x41,0x00,0x5B,0x4F,0x00,0x5B,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E,0x10,\
//0x12,0x14,0x16,0x18,0x1A,0xFF,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0F,\
//0x10,0x12,0x13,0x16,0x18,0x1C,0x1D,0x1E,0x1F,0x20,\
//0x21,0x22,0x24,0x26,0xFF,0xFF,0xFF,0xFF,0x00,0x00,\
//0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,\
//0xFF,0xFF,0xFF,0xFF,0x48,0x01\
//}

// 7寸屏GT911驱动配置
//#define CTP_CFG_GT911 {\
//0x00,0x20,0x03,0xE0,0x01,0x05,0x3D,0x00,0x01,0x48,\
//0x28,0x08,0x6E,0x5A,0x03,0x05,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x18,0x1A,0x1E,0x14,0x87,0x28,0x0A,\
//0x46,0x48,0x31,0x0D,0x00,0x00,0x02,0x18,0x03,0x1D,\
//0x00,0x01,0x00,0x00,0x00,0x03,0x64,0x32,0x00,0x00,\
//0x00,0x0F,0x4B,0x94,0x45,0x02,0x07,0x00,0x00,0x04,\
//0x9B,0x11,0x00,0x72,0x18,0x00,0x57,0x21,0x00,0x43,\
//0x2E,0x00,0x36,0x40,0x00,0x36,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x14,0x12,0x10,0x0E,0x0C,0x0A,0x08,0x06,\
//0x04,0x02,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x26,0x24,0x22,0x21,0x20,0x1F,0x1E,0x1D,\
//0x0C,0x0A,0x08,0x06,0x04,0x02,0x00,0xFF,0xFF,0xFF,\
//0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,\
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x00,0xCD,0x01	\
//}



// STEP_3(optional): Specify your special config info if needed
#define GTP_MAX_HEIGHT                  480
#define GTP_MAX_WIDTH                   800
#define GTP_INT_TRIGGER                 0
#define GTP_MAX_TOUCH                   1


//***************************PART3:OTHER define*********************************
#define GTP_DRIVER_VERSION              "V2.2<2014/01/14>"
#define GTP_I2C_NAME                    "Goodix-TS"
#define GT91XX_CONFIG_PROC_FILE         "gt9xx_config"
#define GTP_POLL_TIME                   10    
#define GTP_ADDR_LENGTH                 2
#define GTP_CONFIG_MIN_LENGTH           186
#define GTP_CONFIG_MAX_LENGTH           240
#define FAIL                            0
#define SUCCESS                         1
#define SWITCH_OFF                      0
#define SWITCH_ON                       1

//******************** For GT9XXF Start **********************//
#define GTP_REG_BAK_REF                 0x99D0
#define GTP_REG_MAIN_CLK                0x8020
#define GTP_REG_CHIP_TYPE               0x8000
#define GTP_REG_HAVE_KEY                0x804E
#define GTP_REG_MATRIX_DRVNUM           0x8069     
#define GTP_REG_MATRIX_SENNUM           0x806A
#define GTP_REG_COMMAND				          0x8040

#define GTP_COMMAND_READSTATUS	        0
#define GTP_COMMAND_DIFFERENCE	        1
#define GTP_COMMAND_SOFTRESET		        2
#define GTP_COMMAND_UPDATE	    		    3
#define GTP_COMMAND_CALCULATE	          4
#define GTP_COMMAND_TURNOFF	    	      5




#define GTP_FL_FW_BURN                  0x00
#define GTP_FL_ESD_RECOVERY             0x01
#define GTP_FL_READ_REPAIR              0x02

#define GTP_BAK_REF_SEND                0
#define GTP_BAK_REF_STORE               1
#define CFG_LOC_DRVA_NUM                29
#define CFG_LOC_DRVB_NUM                30
#define CFG_LOC_SENS_NUM                31

#define GTP_CHK_FW_MAX                  40
#define GTP_CHK_FS_MNT_MAX              300
#define GTP_BAK_REF_PATH                "/data/gtp_ref.bin"
#define GTP_MAIN_CLK_PATH               "/data/gtp_clk.bin"
#define GTP_RQST_CONFIG                 0x01
#define GTP_RQST_BAK_REF                0x02
#define GTP_RQST_RESET                  0x03
#define GTP_RQST_MAIN_CLOCK             0x04
#define GTP_RQST_RESPONDED              0x00
#define GTP_RQST_IDLE                   0xFF

//******************** For GT9XXF End **********************//
// Registers define
#define GTP_READ_COOR_ADDR              0x814E
#define GTP_REG_SLEEP                   0x8040
#define GTP_REG_SENSOR_ID               0x814A
#define GTP_REG_CONFIG_DATA             0x8047
#define GTP_REG_VERSION                 0x8140

#define RESOLUTION_LOC                  3
#define TRIGGER_LOC                     8

#define CFG_GROUP_LEN(p_cfg_grp)        (sizeof(p_cfg_grp) / sizeof(p_cfg_grp[0]))
	

// Log define
#define GTP_INFO(fmt,arg...)            printf("<<-GTP-INFO->> "fmt"\n",##arg)
#define GTP_ERROR(fmt,arg...)           printf("<<-GTP-ERROR->> "fmt"\n",##arg)
#define GTP_DEBUG(fmt,arg...)           do{\
                                           if(GTP_DEBUG_ON)\
                                           printf("<<-GTP-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)
#define GTP_DEBUG_ARRAY(array, num)     do{\
                                           int32_t i;\
                                           uint8_t* a = array;\
                                           if(GTP_DEBUG_ARRAY_ON)\
                                           {\
                                            printf("<<-GTP-DEBUG-ARRAY->>\n");\
                                            for (i = 0; i < (num); i++)\
                                            {\
                                                printf("%02x   ", (a)[i]);\
                                                if ((i + 1 ) %10 == 0)\
                                                {\
                                                    printf("\n");\
                                                }\
                                            }\
                                            printf("\n");\
                                           }\
                                        }while(0)
#define GTP_DEBUG_FUNC()                do{\
                                           if(GTP_DEBUG_FUNC_ON)\
                                           printf("<<-GTP-FUNC->> Func:%s@Line:%d\n",__func__,__LINE__);\
                                        }while(0)
#define GTP_SWAP(x, y)                  do{\
                                           typeof(x) z = x;\
                                           x = y;\
                                           y = z;\
                                        }while (0)

//*****************************End of Part III********************************
int8_t GTP_Reset_Guitar(void);
int32_t GTP_Read_Version(void);
int32_t GTP_Init_Panel(void);
int8_t GTP_Send_Command(uint8_t command);

void GT9xx_GetOnePiont(void);
#ifdef __cplusplus
}
#endif
#endif /* _GOODIX_GT9XX_H_ */
