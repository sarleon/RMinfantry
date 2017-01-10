
#define __DMP_GLOBALS

#include "mpu9250dmp.h"
#include "sim_IIC.h"

#include <math.h>
#include <string.h>

#define i2c_write   IIC_SendBuffer
#define i2c_read    IIC_ReadBuffer
#define delay_ms    mpu_delay_ms
#define get_ms      mpu_get_ms


static struct hal_s hal = {0};

//static signed char gyro_orientation[9] = {-1, 0, 0,
//                                           0,-1, 0,
//                                           0, 0, 1};

//����ʵ�ʽǶȵ���ת����
static signed char gyro_orientation[9] = {0, -1, 0,
                                           -1,0, 0,
                                           0, 0, -1};

                                           
/**
  * @brief  mpu9250dmp��ʼ��
  * @param  0��ʵ������ϵΪ��׼      1�Ե�ǰλ��Ϊ��׼
  * @note   Ĭ�����������̡�2g  ���ٶȼ����̡�2000��        
            Ҫ�޸Ľ�mpu_init�����ģ�ͬʱ��MPU9250_GetGyro��MPU9250_GetAccel����
  * @retval 0�ɹ�     ����ʧ��
  */
uint8_t MPU9250DMP_InitConfig(uint8_t mode)
{
    uint8_t result;
    
    result = mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS);
    if(result)return 1;
    result = mpu_init();
    if(result)return 2;
    result = mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS);
    if(result)return 3;
    result = mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS);
    if(result)return 4;
    result = mpu_set_sample_rate(DEFAULT_MPU_HZ);
    if(result)return 5;
    mpu_accel_lpfset();
    memset(&hal, 0, sizeof(hal));
//    hal.sensors = ACCEL_ON | GYRO_ON | QUAT_ON;
    
    result = dmp_load_motion_driver_firmware();
    result = dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation));
    
//    hal.dmp_features = DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
//        DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
//        DMP_FEATURE_GYRO_CAL;
    
    hal.dmp_features = DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP;

    result = dmp_enable_feature(hal.dmp_features);
    if(result)return 6;
    result = dmp_set_fifo_rate(DEFAULT_MPU_HZ);
    if(result)return 7;
    result = MPU9250DMPU_Selftest(mode);
//    if(result)return 8;
    result = mpu_set_dmp_state(1);
    if(result)return 9;
    hal.dmp_on = 1;
    
    return 0;
}


/**
  * @brief  ��ȡdmp�����ŷ��������
  * @param  pitchָ��
  * @param  rollָ��
  * @param  yawָ��
  * @retval 0�ɹ�     1ʧ��
  */
#define q30  1073741824.0f
uint8_t MPU9250DMP_GetEuler(float *Pitch, float *Roll, float *Yaw)
{
    float q0 = 0, q1 = 0, q2 = 0, q3 = 0;
	unsigned long sensor_timestamp;
	short gyro[3], accel[3], sensors;
	unsigned char more;
	long quat[4]; 
    
	if(dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more))
    {
        return 1;
    }
	if(sensors&INV_WXYZ_QUAT) 
	{
		q0 = quat[0] / q30;	//q30��ʽת��Ϊ������
		q1 = quat[1] / q30;
		q2 = quat[2] / q30;
		q3 = quat[3] / q30; 
		//����õ�������/�����/�����
        *Pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3;	// pitch
        *Roll  = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3;	// roll
        *Yaw   = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;	//yaw
	}
    else 
    {
        return 2;
	}
    return 0;
}


/**
  * @brief  ��ȡmpu9250���ٶ�
  * @param  X����ٶȴ洢��ַ
  * @param  Y����ٶȴ洢��ַ
  * @param  Z����ٶȴ洢��ַ
  * @note   Ĭ�����̡�2000��
  * @retval 0��ȡ�ɹ�       1��ȡʧ��
  */
uint8_t MPU9250_GetGyro(float *X, float *Y, float *Z)
{
    unsigned long timestamp;
    short tmp[3];
    
    if(mpu_get_gyro_reg(tmp, &timestamp))
    {
        return 1;
    }
    else
    {
        *X = 0.0610352F * tmp[0];
        *Y = 0.0610352F * tmp[1];
        *Z = 0.0610352F * tmp[2];
        
        return 0;
    }
}


/**
  * @brief  ��ȡmpu9250�������ٶ�
  * @param  X���������ٶȴ洢��ַ
  * @param  Y���������ٶȴ洢��ַ
  * @param  Z���������ٶȴ洢��ַ
  * @note   Ĭ�����̡�2g��
  * @retval 0��ȡ�ɹ�       1��ȡʧ��
  */
uint8_t MPU9250_GetAccel(float *X, float *Y, float *Z)
{
    unsigned long timestamp;
    short tmp[3];
    
    if(mpu_get_accel_reg(tmp, &timestamp))
    {
        return 1;
    }
    else
    {
        *X = 2 * Acceleration_Of_Gravity * tmp[0] / 32768;
        *Y = 2 * Acceleration_Of_Gravity * tmp[1] / 32768;
        *Z = 2 * Acceleration_Of_Gravity * tmp[2] / 32768;
        
        return 0;
    }
}


/**
  * @brief  �Լ�
  * @param  0��ʵ������ϵΪ��׼      1�Ե�ǰλ��Ϊ��׼
  * @retval 0�ɹ�     1ʧ��
  */
static uint8_t MPU9250DMPU_Selftest(uint8_t mode)
{
    int result;
    long gyro[3], accel[3];

    result = mpu_run_self_test(gyro, accel);
    
    if (result == 0x07) 
    {
        if(mode)
        {
            float sens;
            unsigned short accel_sens;
            mpu_get_gyro_sens(&sens);
            gyro[0] = (long)(gyro[0] * sens);
            gyro[1] = (long)(gyro[1] * sens);
            gyro[2] = (long)(gyro[2] * sens);
            dmp_set_gyro_bias(gyro);
            mpu_get_accel_sens(&accel_sens);
            accel[0] *= accel_sens;
            accel[1] *= accel_sens;
            accel[2] *= accel_sens;
            dmp_set_accel_bias(accel);
        }
        
        return 0;
    }
    return 1;
}



static inline unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{
    unsigned short scalar;

    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}


/* These next two functions converts the orientation matrix (see
 * gyro_orientation) to a scalar representation for use by the DMP.
 * NOTE: These functions are borrowed from Invensense's MPL.
 */
static inline unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}


/**
  * @brief  mpu6050���
  * @param  void
  * @retval 0 ����		1 ������
  */
uint8_t mpu6050_Check(void)
{
	uint8_t res;
	
	//���6050�Ƿ�����
	if(IIC_SingleRead(0x68, 0x75, &res))
	{
		return 1;
	}
	
	if(res != 0x71)//����ID����ȷ
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/**
  * @brief  ���ٶȼƵ�ͨ�˲�����
  * @param  void
  * @retval void
  */
void mpu_accel_lpfset(void)
{
    uint8_t data = 3;
    IIC_SendBuffer(0x68, 0x1D, 1, &data);
}
    
    
    
                                           
/**
  * @brief  ��ʱ��dmpר��
  * @param  unused
  * @retval void
  */
__weak void mpu_delay_ms(int x)
{
    x *= 20000;
    while(x--);
}


/**
  * @brief  ��ȡʱ�䣬dmpר�á���ʵûʵ�����ã����Ϊ��
  * @param  unused
  * @retval void
  */
__weak void mpu_get_ms(unsigned long *p)
{
    ;
}













