
#include "sim_uart.h"



//��ʱ���Ķ�ʱ����ֲ����ʾ��������糣�õ��ʺϷ��洮�ڵ�
//��������9600bps������ζ�Ŵ��ڴ���һλ��ʱ����104us(1000000/9600)��
//��˶�ʱ���Ķ�ʱ�ж���104us
void timer_interrupt(void )
{
    app_sim_uart_transmit();
}

//9600bps��104us��Ӳ����ʱ��
void timer_init(void )
{
    
}

main()
{
    //Ӳ����ʱ����ʼ��
    timer_init();
    //���洮�ڳ�ʼ��
    app_sim_uart_init();
    while(1)
    {
        //��鴮�ڻ������Ƿ�Ϊ�գ����Ϊ�գ�������һ���ֽ�   
        if(app_sim_uart_get_tx_state() == 0)
        {
            //����0xaa
            app_sim_uart_tx_set_data(0xaa);
        }
    }
}

