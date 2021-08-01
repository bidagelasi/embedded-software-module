
#include "sim_uart.h"


/*
移植说明：
1、把sim_uart.h 文件中#include"stm8s.h"换成你自己的MCU头文件
2、把SIM_UART_IO_H、SIM_UART_IO_L表示的是你准备用来做串口TX的IO口
   SIM_UART_IO_H 表示把MCU的管脚拉高
   SIM_UART_IO_L 表示把MCU的管脚拉低
*/

/*
定时器的定时间隔又波特率决定，比如常用的适合仿真串口的
波特率是9600bps，这意味着串口传输一位的时间是104us(1000000/9600)，
因此定时器的定时中断是104us
*/
void timer_interrupt(void )
{
    app_sim_uart_transmit();
}

//9600bps，104us的硬件定时器
void timer_init(void )
{
    
}

main()
{
    //硬件定时器初始化
    timer_init();
    //仿真串口初始化
    app_sim_uart_init();
    while(1)
    {
        //检查串口缓冲区是否为空，如果为空，发送下一个字节   
        if(app_sim_uart_get_tx_state() == 0)
        {
            //发送0xaa
            app_sim_uart_tx_set_data(0xaa);
        }
    }
}

