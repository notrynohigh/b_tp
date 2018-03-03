b_tp
====
功能说明
----
    1、支持通信数据传输的分包以及组包
    2、通用协议格式，同时支持协议头自定义配置
    3、接口简单，使用方便
    4、数据校验方式可选CRC32, CRC16等
协议格式说明
----
【协议头】【数据】【校验】
协议头格式：
```
typedef struct
{
  B_TP_HEAD_TYPE          head;
  B_TP_FRAME_NUMBER_TYPE  f_num;
  b_TPU8                  number;         /**< 自定义一项 */
  B_TP_TOTAL_LEN_TYPE     total_len;
}b_tp_head_t;
```
不是自定义的项变量名不能改变，分别是，头标志 分帧标志 数据长度
    头标志：    数据类型可以配置
    分帧标志：  是否分帧传输
    数据长度：  数据的长度，不包括协议头以及校验
    校验：      校验方式可选，对协议头以及数据部分进行校验
    
使用接口说明
----
    1、根据需求完成b_tp_config.h文件的配置
    2、如果在协议头加入了自定义项，实现一下两个函数来操作自定义的部分：
```
b_tp_err_code_t _b_tp_rec_check_head(b_tp_head_t *);
void _b_tp_send_set_head(b_tp_head_t *);
```
    3、完成b_tp_port.c里发送函数
    4、收到数据后将收到的数据通过b_tp_receive_data函数提交给b_tp进行解析
    5、解析完成后调用回调，所以通过b_tp_reg_callback注册回调

如有建议或者疑问： email： notrynohigh@outlook.com
