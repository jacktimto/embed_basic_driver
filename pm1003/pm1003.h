#ifndef _PM1003_H_
#define _PM1003_H_

#include "stdint.h"
#include "stddef.h"

/*PM1003错误定义*/
typedef enum PM1003Error
{
    PM1003_NO_ERROR = 0x00,       // 无错误
    PM1003_CHECKSUM_ERROR = 0x01, // 校验错误
    PM1003_TIMEOUT_ERROR = 0x02,  // 超时错误
    PM1003_INIT_ERROR = 0x03,     // PM1003对象初始化错误
    PM1003_PARAM_ERROR = 0x04,    // 传入的参数错误
    PM1003_FRAM_ERROR = 0x01,     // 帧头错误错误
} PM1003Error_Type;

/*PM1003模式:1.uart测量 2.脉冲宽度测量*/
typedef enum PM1003Mode
{
    Mode_uart,
    Mode_pwm,
} PM1003Mode_Type;

/*定义PM1003对象*/
typedef struct PM1003_Object
{
    uint16_t PM2d5;                                                                          // pm2.5
    uint16_t (*Send_Recive_Cmd)(struct PM1003_Object *pm1003, uint8_t *cmd, uint8_t txsize); // 发送接收pm2.5数据,必须是 struct PM1003_Object *pm1003

} PM1003_Object_Type;

typedef uint16_t (*PM1003Send_Recive_Cmd)(PM1003_Object_Type *pm1003, uint8_t *cmd, uint8_t txsize); // 其实是在给uint16_t(*)(int)取别名

/*PM1003初始化*/
PM1003Error_Type PM1003init(PM1003_Object_Type *pm1003, PM1003Send_Recive_Cmd pm1003send_recive_cmd);

/*PM1003测量命令*/
void PM1003ReadResult(PM1003_Object_Type *pm1003);

/*pm1003校验*/
PM1003Error_Type PM1003checksum(uint8_t *rxdata, uint8_t size);

#endif