#include "pm1003.h"

/*对成员初始化,对传入的参数判断*/
PM1003Error_Type PM1003init(PM1003_Object_Type *pm1003, PM1003Send_Recive_Cmd pm1003send_recive_cmd)
{
    if ((pm1003 == NULL) || (pm1003send_recive_cmd == NULL))
    {
        return PM1003_PARAM_ERROR;
    }
    pm1003->PM2d5 = 0;
    pm1003->Send_Recive_Cmd = pm1003send_recive_cmd;

    return PM1003_NO_ERROR;
}

/*pm1003校验*/
PM1003Error_Type PM1003checksum(uint8_t *rxdata, uint8_t size)
{
    uint8_t temp = 0;
    if (rxdata[0] != 0x16)
    {
        return PM1003_FRAM_ERROR;
    }
    for (int i = 0; i < (size - 1); i++)
    {
        temp = temp + rxdata[i];
    }
    if (rxdata[size - 1] != (0xFF - temp)) // 注意temp的类型转换
    {
        return PM1003_CHECKSUM_ERROR;
    }
    return PM1003_NO_ERROR;
}

/*PM1003读取结果*/
void PM1003ReadResult(PM1003_Object_Type *pm1003)
{
    uint8_t cmd[] = {0x11, 0x02, 0x0B, 0x01, 0xE1};
    pm1003->PM2d5 = pm1003->Send_Recive_Cmd(pm1003, cmd, sizeof cmd);
}