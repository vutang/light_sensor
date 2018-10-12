/*
* Read_Temperature.c
*
*  Created on: Jul 23, 2014
*      Author: mabeecha
*/


/*#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xiicps.h"
#include "xstatus.h"

#define SlaveAddr 0x40
#define FsclHz 100000

//function prototypes
//void printf(char *str);
//int XIicPs_MasterSendPolled(XIicPs *InstancePtr, u8 *MsgPtr, int ByteCount, u16 SlaveAddr);
//int XIicPs_MasterRecvPolled(XIicPs *InstancePtr, u8 *MsgPtr, int ByteCount, u16 SlaveAddr);
//XIicPs_Config *XIicPs_LookupConfig(u16 DeviceId);
//int XIicPs_CfgInitialize(XIicPs *InstancePtr, XIicPs_Config *ConfigPtr, u32 EffectiveAddr);
//int XIicPs_SetSClk(XIicPs *InstancePtr, u32 FsclHz);



//globals
XIicPs IicInstance;
int config_reg;
u8 config_data[2];
u8 rxdata[1];
u8 read_reg_cmnd[1];



int status;



int main()
{
                init_platform();
                printf("start1\n\r");

                //initializations
                XIicPs_Config *ConfigPtr;
                printf("start2\n\r");

                ConfigPtr = XIicPs_LookupConfig(XPAR_PS7_I2C_0_DEVICE_ID);
                printf("start3\n\r");

                if (ConfigPtr == NULL) {
                                return XST_FAILURE;
                                printf("failure\n\r");
                }

                status = XIicPs_CfgInitialize(&IicInstance, ConfigPtr, ConfigPtr->BaseAddress);

                if (status != XST_SUCCESS) {
                                return XST_FAILURE;
                                printf("failure2\n\r");
                }

                printf("start4\n\r");

                XIicPs_SetSClk(&IicInstance, FsclHz);



                //read the user register before a write
                /*u8 read_reg_cmnd[1];
                read_reg_cmnd[0] = 0xE7;
                /*XIicPs_MasterSendPolled(&IicInstance, &read_reg_cmnd[0], 1, SlaveAddr);
                XIicPs_MasterRecvPolled(&IicInstance, &rxdata, 1, SlaveAddr);
                printf("user reg before = %d\n\r", rxdata[0]);*/

//write the user register with some data
/*u8 user_reg_heater_on[2];
                user_reg_heater_on[0] = 0xE6;
                user_reg_heater_on[1] = 0x04;
                XIicPs_MasterSendPolled(&IicInstance, &user_reg_heater_on, 2, SlaveAddr);

                //read back the user register to see if it changed
                read_reg_cmnd[0] = 0xE7;
                XIicPs_MasterSendPolled(&IicInstance, &read_reg_cmnd[0], 1, SlaveAddr);
                XIicPs_MasterRecvPolled(&IicInstance, &rxdata[0], 1, SlaveAddr);
                config_reg = rxdata[0];

                printf("user reg = %d\n\r", config_reg);*/



/*while(1){

                                //read humidity
                                u8 txdata_measure_humid[1];
                                u8 rxdata_humid[2];
                                u16 humid_code;
                                int humidity;

                                txdata_measure_humid[0] = 0xE5;
                                XIicPs_MasterSendPolled(&IicInstance, &txdata_measure_humid[0], 1, SlaveAddr);
                                //printf("sent command successfully\n\r");

                                XIicPs_MasterRecvPolled(&IicInstance, &rxdata_humid[0], 2, SlaveAddr);
                                //printf("recieved data successfully\n\r");

                                humid_code = rxdata_humid[0] << 8;
                                humid_code |= rxdata_humid[1];
                                humidity = ((125.00 * humid_code) / 65536.00) - 6.00;
                                printf("humidity=%d\n\r", humidity);
                                //printf("finished conversion\n\r");

                                //read temperature
                                /*u8 txdata_measure_temp[1];
                                u8 rxdata_temp[2];
                                u16 temp_code;
                                int temp;

                                txdata_measure_temp[0] = 0xE3;
                                //txdata_measure_temp[0] = 0xE0;

                                XIicPs_MasterSendPolled(&IicInstance, &txdata_measure_temp[0], 1, SlaveAddr);
                                //printf("sent command successfully\n\r");

                                XIicPs_MasterRecvPolled(&IicInstance, &rxdata_temp[0], 2, SlaveAddr);
                                //printf("recieved data successfully\n\r");

                                temp_code = rxdata_temp[0] << 8;
                                temp_code |= rxdata_temp[1];
                                temp = ((175.72 * temp_code) / 65536.00) - 46.85;
                                //temp = ((9 / 5) * temp) + 32
                                temp = temp*9.00/5.00;
                                temp = temp + 32.00;
                                printf("temp=%d\n\r", temp);
                                //printf("finished conversion\n\r");*/
/*
                }
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "xparameters.h"
#include "xiicps.h"


#define SI1145ADDR 0x60
#define SI7021ADDR 0x40
#define SI7013ADDR 0x40


void delay(int StopValue);

int main()
{

                int g_ActivePeripheralAddressI2C            = XPAR_PS7_I2C_0_BASEADDR;


                XIicPs IicInstance;
                int * pointer;
                uint32_t Temp; //hold the temp value
                uint32_t Temp_F;
                u16 temp_bits;
                uint32_t Humidity;
                int PS1_Data;
                int PS2_Data;
                int PS3_Data;
                int ALS_Data;
                int UV_Data;

                int Light; //hold the Ambient light value
                int UVindex; //hold UV light value
                u8 Object; //boolean of weather or not there is an object

                init_platform();

                Temp = 1000;

                //printf("temp = %d", Temp);

                int Status;
                //void XIicPs_MasterRecv(XIicPs *InstancePtr, u8 *MsgPtr, int ByteCount, u16 SlaveAddr)
                //u8 TxBuffer[1];
                u8 send_buffer[2];
                u8 CHLIST_ENABLES[3];
                u8 PROX1_DATA_HIGH[1];
                u8 PROX1_DATA_LOW[1];
                u8 PROX2_DATA_HIGH[1];
                u8 PROX2_DATA_LOW[1];
                u8 PROX3_DATA_HIGH[1];
                u8 PROX3_DATA_LOW[1];
                u8 ALS_DATA_HIGH[1];
                u8 ALS_DATA_LOW[1];
                u8 UV_DATA_HIGH[1];
                u8 UV_DATA_LOW[1];

                u8 prox_buffer[2];
                u8 light_buffer[2];
                u8 config_buffer[2];
                int user_reg;
                u8 RxBuffer_Rate[1];
                u8 RxBuffer_PS1data[2];
                u8 RxBuffer_PS2data[2];
                u8 RxBuffer_PS3data[2];
                u8 RxBuffer_ALSdata[2];
                u8 RxBuffer_UVdata[2];
                u8 RxBuffer_hum[2];
                u8 RxBuffer_temp[2];
                u8 Rx_buffer_user[2];

                u16 hum_bits;

                printf("START\n\n");

                XIicPs_Config *ConfigPtr;             /* Pointer to configuration data */

                ConfigPtr = XIicPs_LookupConfig(XPAR_PS7_I2C_0_DEVICE_ID);
                if (ConfigPtr == NULL) {
                                return XST_FAILURE;
                }

                Status = XIicPs_CfgInitialize(&IicInstance, ConfigPtr,
                                                ConfigPtr->BaseAddress);
                if (Status != XST_SUCCESS) {
                                return XST_FAILURE;
                }

                XIicPs_SetSClk(&IicInstance, 100000);


                //send hardware key
                send_buffer[0] = 0x07;
                send_buffer[1] = 0x17;
                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&send_buffer, 2, SI1145ADDR);

                //initialize led current
                send_buffer[0] = 0x0F;
                send_buffer[1] = 0xFF;
                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&send_buffer, 2, SI1145ADDR);

                send_buffer[0] = 0x10;
                send_buffer[1] = 0x0F;
                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&send_buffer, 2, SI1145ADDR);


                //set CHLIST parameter enables
                CHLIST_ENABLES[0] = 0x17;
                CHLIST_ENABLES[1] = 0xFF;
                CHLIST_ENABLES[2] = 0xA1;
                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&CHLIST_ENABLES, 3, SI1145ADDR);



                while(1)
                {


                                //FORCE PROX AND ALS MEASUREMENTS/////////////////////////////////////////////////////////////////////////////
                                //------------------------------------------------------------------------------------------------------------
                                send_buffer[0] = 0x18;
                                send_buffer[1] = 0x05;
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&send_buffer, 2, SI1145ADDR);
                                //------------------------------------------------------------------------------------------------------------


                               /* send_buffer[0] = 0x18;
                                send_buffer[1] = 0x0F;//command to put it into auto mode
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&send_buffer, 2, SI1145ADDR);


                                send_buffer[0] = 0x08;
                                send_buffer[1] = 0x00; //meas rate to slow
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&send_buffer, 2, SI1145ADDR);


                                send_buffer[0] = 0x09;
                                send_buffer[1] = 0xFF;
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&send_buffer, 2, SI1145ADDR);
*/


                                delay(1000);





                                //READ PROX DATA//////////////////////////////////////////////////////////////////////////////////////////////
                                //read LSB of PS1 Data
                                //------------------------------------------------------------------------------------------------------------
                                PROX1_DATA_LOW[0] = 0x26;
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&PROX1_DATA_LOW, 1, SI1145ADDR);
                                XIicPs_MasterRecvPolled(&IicInstance, (u8 *)&RxBuffer_PS1data[0], 1, SI1145ADDR);
                                //------------------------------------------------------------------------------------------------------------

                                //read MSB of PS1 Data
                                //------------------------------------------------------------------------------------------------------------
                                PROX1_DATA_HIGH[0] = 0x27;
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&PROX1_DATA_HIGH, 1, SI1145ADDR);
                                XIicPs_MasterRecvPolled(&IicInstance, (u8 *)&RxBuffer_PS1data[1], 1, SI1145ADDR);
                                //------------------------------------------------------------------------------------------------------------

/*
                                //read LSB of PS2 Data
                                //------------------------------------------------------------------------------------------------------------
                                prox_buffer[0] = 0x26;
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&prox_buffer, 1, SI1145ADDR);
                                XIicPs_MasterRecvPolled(&IicInstance, (u8 *)&RxBuffer_PS2data[0], 1, SI1145ADDR);
                                //------------------------------------------------------------------------------------------------------------

                                //read MSB of PS2 Data
                                //------------------------------------------------------------------------------------------------------------
                                prox_buffer[0] = 0x27;
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&prox_buffer, 1, SI1145ADDR);
                                XIicPs_MasterRecvPolled(&IicInstance, (u8 *)&RxBuffer_PS2data[1], 1, SI1145ADDR);
                                //------------------------------------------------------------------------------------------------------------


                                //read LSB of PS3 Data
                                //------------------------------------------------------------------------------------------------------------
                                prox_buffer[0] = 0x26;
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&prox_buffer, 1, SI1145ADDR);
                                XIicPs_MasterRecvPolled(&IicInstance, (u8 *)&RxBuffer_PS3data[0], 1, SI1145ADDR);
                                //------------------------------------------------------------------------------------------------------------

                                //read MSB of PS3 Data
                                //------------------------------------------------------------------------------------------------------------
                                prox_buffer[0] = 0x27;
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&prox_buffer, 1, SI1145ADDR);
                                XIicPs_MasterRecvPolled(&IicInstance, (u8 *)&RxBuffer_PS3data[1], 1, SI1145ADDR);
                                //------------------------------------------------------------------------------------------------------------
*/

                                //READ ALS DATA///////////////////////////////////////////////////////////////////////////////////////////////
                                send_buffer[0] = 0x18;
                                send_buffer[1] = 0x0E; //AUTO for ALS
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&send_buffer, 2, SI1145ADDR);
                                delay(10000000);

                				//force an ALS read
                                send_buffer[0] = 0x18;
                                send_buffer[1] = 0x06;
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&send_buffer, 2, SI1145ADDR);

                               delay(10000000);

                                //read LSB of ALS Data
								//------------------------------------------------------------------------------------------------------------
                                ALS_DATA_LOW[0] = 0x22;
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&ALS_DATA_LOW, 1, SI1145ADDR);
                                XIicPs_MasterRecvPolled(&IicInstance, (u8 *)&RxBuffer_ALSdata[0], 1, SI1145ADDR);
                                //------------------------------------------------------------------------------------------------------------

                                //read MSB of ALS Data
                                //------------------------------------------------------------------------------------------------------------
                                ALS_DATA_HIGH[0] = 0x23;
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&ALS_DATA_HIGH, 1, SI1145ADDR);
                                XIicPs_MasterRecvPolled(&IicInstance, (u8 *)&RxBuffer_ALSdata[1], 1, SI1145ADDR);
                                //------------------------------------------------------------------------------------------------------------



                                //read the user register
                                send_buffer[0] = 0xE7;
                                XIicPs_MasterSendPolled(&IicInstance, &send_buffer, 1, SI7013ADDR);
                                XIicPs_MasterRecvPolled(&IicInstance, (u8 *)&Rx_buffer_user[0], 1, SI7013ADDR);
                                //printf("user reg = 0x%x\n\r", Rx_buffer_user[0]);

                                send_buffer[1] = Rx_buffer_user[0] && 0x7a;  //set high resolution and turn heater off
                                delay(100000);

                                send_buffer[0] = 0xE6;
                               // send_buffer[1] = 0xFF;
                                XIicPs_MasterSendPolled(&IicInstance, &send_buffer, 2, SI7013ADDR);



                                //READ UV DATA////////////////////////////////////////////////////////////////////////////////////////////////
                                //read LSB of UV Data
                                //------------------------------------------------------------------------------------------------------------
                                UV_DATA_LOW[0] = 0x2C;
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&UV_DATA_LOW, 1, SI1145ADDR);
                                XIicPs_MasterRecvPolled(&IicInstance, (u8 *)&RxBuffer_UVdata[0], 1, SI1145ADDR);
                                //------------------------------------------------------------------------------------------------------------


                                //read MSB of UV Data
                                //------------------------------------------------------------------------------------------------------------
                                UV_DATA_HIGH[0] = 0x2D;
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&UV_DATA_HIGH, 1, SI1145ADDR);
                                XIicPs_MasterRecvPolled(&IicInstance, (u8 *)&RxBuffer_UVdata[1], 1, SI1145ADDR);



                                //read Temperature
                                //------------------------------------------------------------------------------------------------------------
                                send_buffer[0] = 0xE3;
                                delay(50000000);
                               // XIicPs_MasterSendPolled(&IicInstance, &send_buffer, 1, SI7013ADDR);
                                //send_buffer[0] = 0xE3;//command to take temp measurement
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&send_buffer, 1, SI7013ADDR); //send command
                                XIicPs_MasterRecvPolled(&IicInstance, (u8 *)&RxBuffer_temp[0], 2, SI7013ADDR);//read back 16 bit temp
                                //------------------------------------------------------------------------------------------------------------

                                //make RH measurement command
                                //------------------------------------------------------------------------------------------------------------
                                send_buffer[0] = 0xE5; // measure hum command
                                delay(1000000);
                                XIicPs_MasterSendPolled(&IicInstance, (u8 *)&send_buffer, 1, SI7013ADDR); //send the command to the 7021
                                XIicPs_MasterRecvPolled(&IicInstance, (u8 *)&RxBuffer_hum, 2, SI7013ADDR); //read the 16 bit value back
                                //------------------------------------------------------------------------------------------------------------


                                //FORMAT DATA/////////////////////////////////////////////////////////////////////////////////////////////////
                                //format PS1 reading into 16 bit number
                                //------------------------------------------------------------------------------------------------------------
                                PS1_Data = RxBuffer_PS1data[1] << 8;
                                PS1_Data |= RxBuffer_PS1data[0];
                                //------------------------------------------------------------------------------------------------------------

                                //format PS2 reading into 16 bit number
                                //------------------------------------------------------------------------------------------------------------
                                PS2_Data = RxBuffer_PS2data[1] << 8;
                                PS2_Data |= RxBuffer_PS2data[0];
                                //------------------------------------------------------------------------------------------------------------

                                //format PS3 reading into 16 bit number
                                //------------------------------------------------------------------------------------------------------------
                                PS3_Data = RxBuffer_PS3data[1] << 8;
                                PS3_Data |= RxBuffer_PS3data[0];
                                //------------------------------------------------------------------------------------------------------------

                                //format ALS reading into 16 bit number
                                //------------------------------------------------------------------------------------------------------------
                                ALS_Data = RxBuffer_ALSdata[1] << 8;
                                ALS_Data |= RxBuffer_ALSdata[0];
                                //------------------------------------------------------------------------------------------------------------

                                //format UV reading into 16 bit number
                                //------------------------------------------------------------------------------------------------------------
                                UV_Data = RxBuffer_UVdata[1] << 8;
                                UV_Data |= RxBuffer_UVdata[0];
                                UV_Data = UV_Data + 50;
                                UV_Data /= 10000;
                                //------------------------------------------------------------------------------------------------------------

                                //Convert temp to F
                                //------------------------------------------------------------------------------------------------------------
                               // temp_bits = (RxBuffer_temp[0] << 8) + (RxBuffer_temp[1] & 0xfc);
                                temp_bits = (RxBuffer_temp[0] << 8) + (RxBuffer_temp[1]);
                               // Temp = ((175.72 * temp_bits)/ 65536.0) - 46.85; // Temp is in celcius
                               // Temp_F = Temp * (9.0/5.0) + 32;
                                //------------------------------------------------------------------------------------------------------------

                                Temp = 175.72 * temp_bits;
                                		Temp = Temp/65536.0;
                                		Temp = Temp - 46.85;
                                		Temp_F = Temp * 9.0;
                                		Temp_F = Temp_F / 5.0;
                                		Temp_F = Temp_F + 32.0;




                                //Convert Hum to percent
                                //------------------------------------------------------------------------------------------------------------
                                hum_bits = RxBuffer_hum[0] <<8;
                                hum_bits |= RxBuffer_hum[1];
                                Humidity = ((125.0 * hum_bits)/ 65536.0) - 6.0;
                                //------------------------------------------------------------------------------------------------------------

                             //  system("cls");
                                //PRINT DATA///////////////////////////////////////////////////////////////////////////////////////////////////
                                printf("humidity = %d%%\n\r", Humidity);
                                printf("temp(C) = %d\n\rtemp(F) = %d\n", Temp, Temp_F);
                                Temp = Temp_F = 0;
                                printf("PS1_Data = %d\n\r", PS1_Data);
                                //OBJECT PRESENT?///////////////////////////////////////////////////////////////////////////////////////////////
                                if(PS1_Data < 22000){
                                	printf("Object Far\n\r");
                                }
                                else if(PS1_Data < 24000)
                                {
                                	printf("Object in Vicinity\n\r");
                                }
                                else if (PS1_Data < 30000)
                                {
                                	printf("Object Near\n\r");
                                }

                                else printf("Very Near\n\r");
                                // printf("PS2_Data = %d\n\r", PS2_Data);
                                // printf("PS3_Data = %d\n\r", PS3_Data);
                                printf("ALS_Data = %d\n\r", ALS_Data);
                                printf("UV_Data = %d\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r", UV_Data);





                                delay(1000000);

                }


                return 0;
}


void delay(int StopValue)
{
                int i=0;
                int a=0;

                for(i=0;i<StopValue;i++)
                {
                                a=i;
                }
}
