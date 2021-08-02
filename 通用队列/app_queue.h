#ifndef _APP_QUEUE_
#define _APP_QUEUE_

#include "stdint.h"

typedef enum
{
  	Q_NONE,
  	Q_NON_NONE,
  	Q_S_NONE,
  	Q_S_OK,
	Q_S_ERR,
}Q_status_t;

typedef uint16_t q_size_t;

typedef struct
{
	q_size_t head;
	q_size_t end;
	q_size_t q_len;
	q_size_t size;
}pos_t;

//��ʼ������
//a_size: ������һ��Ԫ��ռ�õ��ֽ�����
//q_max : ���г���
//p_q   : ָ����л���
void app_queue_init(void *p_q, q_size_t q_max,q_size_t a_size);

//enqueue
void app_enqueue(void *p_q, void *p_src);

//dequeue
void app_dequeue(void *p_q, void *p_des);

//judge queue enpty
//if queue none ,return Q_NONE
uint8_t app_queue_none(void *p_q);

//search queue 
//if find, return Q_S_OK
uint8_t app_queue_search(void *p_q, void *p_src);

//clear queue all data
void app_queue_clr(void *p_q);

//��ö���Ԫ�ظ���
uint16_t app_queue_get_len(void *queue);

//��ö���ʣ��ռ�
uint16_t app_queue_get_remain_len(void *queue);

//����idxָ���Ķ���Ԫ��
//ע��idx = 0��ʾ�����е�һ��Ԫ��
//    idx = 1��ʾ�����еڶ���Ԫ��
//    idx = n��ʾ�����е�n��Ԫ�أ�n���ܳ�������������Ԫ�صĳ���
//����ҵ�idx��Ӧ��Ԫ�أ�Ԫ�����ݻᱻ������p_desָ��Ŀռ�
//���û���ҵ�idxָ����Ԫ��,����Q_S_ERR������Q_S_OK
Q_status_t app_queue_traverse(void *queue, void *p_des, q_size_t idx);

//��������λ������idx��Ԫ���滻Ϊp_replace
//����ɹ��滻������Q_S_ERR������Q_S_OK
Q_status_t app_queue_modify_speci_element(void *queue, q_size_t idx, void *p_replace);


//����:
/*
#define NB_Q_MAX 10

typedef struct
{
	uint8_t tx_interval;
	uint8_t tx_try_cnt;
	uint16_t rx_timeout;
}nb_opt_t;

typedef struct
{
	pos_t  pos;  //������,��������pos_t
	nb_opt_t opt[NB_Q_MAX]; 
}nb_q_t;

nb_q_t nb_Q;

nb_opt_t test;

1����ʼ������
app_queue_init(&nb_Q, NB_Q_MAX, sizeof(nb_opt_t));

2�����
app_enqueue(&nb_Q, &test);

3������
app_dequeue(&nb_Q, &p_des);

4���ж϶��п�
if(app_queue_none(&nb_Q) != Q_NONE)
{
}

5����������
if(app_queue_search(&nb_Q,&test) == Q_S_OK)
{
	����������ͬ����
}

6���������
app_queue_clr(&nb_Q);

7���ҵ�������λ�ڶ�������0λ�õ�Ԫ��,������浽temp��
nb_opt_t temp;

app_queue_traverse(&nb_Q, &temp, 0);

8���ҵ�������λ�ڶ�������0λ�õ�Ԫ��,����Ԫ���滻Ϊtemp
nb_opt_t temp

temp.tx_interval = 0x01;
temp.tx_try_cnt = 0xff;

app_queue_modify_speci_element(&nb_Q, 0, &temp);

*/

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

typedef struct
{
	uint16_t head;
	uint16_t end;
	uint16_t buf_size;
	uint16_t buf_pos;
	uint8_t size;
	void *data;
}batch_q_t;

/*
�������ܣ���ö��е�ʣ�೤��
*/
uint16_t app_batch_queue_remain_len(batch_q_t *bq);

/*
�������ܣ���ö��г���
*/
uint16_t app_batch_queue_get_data_len(batch_q_t *bq);

/*
�������ܣ����
*/
int32_t app_batch_data_enqueue(batch_q_t *bq, void *p, uint16_t len);

/*
�������ܣ�����
*/
int32_t app_batch_data_dequeue(batch_q_t *bq, void *p, uint16_t len);

/*
�������ܣ��ж϶����Ƿ�Ϊ��
	      ��������0����ʾ����Ϊ��
		  ��������1����ʾ���зǿ�
*/
int16_t app_batch_queue_none(batch_q_t *bq);

/*
��������: 	�������ݶ��г�ʼ��
			bq - ����
			p - ָ��Ӧ�ò�Ķ��л��棬������ÿ�����ݴ�Сֻ����1�ֽڡ�2�ֽڡ�4�ֽ�
			size - ����Ԫ����ÿ�����ݴ�С(ֻ����1��2��4�е�һ��)����λΪ�ֽ�
			len -  ���г��ȣ�Ҫע�⻺�������ȱ�����2����
*/
void app_batch_queue_init(batch_q_t *bq, void *p,uint8_t size, uint16_t len);


/*
���ӣ�
batch_q_t bq_test;

uint8_t buf[1024]; //buf���ȱ�����2�ı���
uint8_t test[10] = {0x01,0x02,0x03,0x04,0x05};
uint8_t test_buf[200];

1����ʼ��
app_batch_queue_init(&bq_test,buf, 1,1024); //buf���ȱ�����2�ı���

������л��涨��Ϊ��
uint32_t buf[1024];

app_batch_queue_init(&bq_test,buf, 4,1024);

2�����
db_ble_data_enqueue(&bq_test, test, 5);

3������,�м��ַ�ʽ�����������ֻ��5�����ݣ�

a�����ӵ���������5����ֻ���������ݵ�test_buf
app_batch_data_dequeue(&bq_test,test_buf, 2);

b������������5��ֻ��5������

4���ж϶����ڻ�ʣ�¶��ٿռ�
uin16_t len;

len = app_batch_queue_remain_len(&bq_test);

5���ж϶����Ƿ�Ϊ��
//������зǿ�
if(app_batch_queue_none(&bq_test) != 0)
{
  .......
}

6���������ж�������
app_batch_queue_get_data_len()

*/

#endif










