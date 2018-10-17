#include "app_data.h"

static sFrame RecFrame,SedFrame;

static u8 JudgeFrame(const u8* indata,u16 len);
static void FrameStructure(u8* indata, u16 inlen,u8* outdata, u8* outlen);
static u8 JudgementFixationFrame(u8* indata,u16 inlen);

void AppDataDeal(const u8* data,u16 len)
{
	u8 i,ret = 0xff;
	u8 rec_ret; //接收回复，0：无需回复，1：需要回复
	u8 ret_data[50];
	
	//*******接收部分*******//
	if(data[0] == FRAME_HEX_HEADER)
	{
		//首帧为0x68
		ret = JudgeFrame(data,len);
	}
	else
	{
		//首帧和第一个字节对应不上，例编数组找首帧
		for(i=0;i<len;i++)
		{
			if(data[i] == FRAME_HEX_HEADER)
			{
				//找到首帧
				
				ret=JudgeFrame(&data[i],len-i,ret_data);
				break;
			}
		}
	}
	if(ret == 0xff)
	{
		//历遍完毕没有找到帧头
	}
	else if(ret == 0)
	{
		//接收成功
	}
	else
	{
		//接收错误 
		if(ret == 1)
		{
			//帧不完整
		}
		else if(ret == 2)
		{
			//帧长度小于4
		}
		else
		{
			//例外 程序不受控
		}
	}
	//********发送部分*********//
	if(rec_ret)
	{
		rec_ret = 0;
		if(RecFrame.type == HANDSHAKE_FRAMETYPE)
		{	//回复心跳
			
		}
	}
	
}
/* 	帧判断函数 检测到帧头执行，并把帧对应存入结构体中 
	返回：0 正确接收， 1 帧不完整 2 帧长度小于4
输入 indata: 要处理的帧地址，len:要处理帧的长度 ， data:  */
static u8 JudgeFrame(const u8* indata,u16 len)	//len 限制长度 数组的最大长度 
{
	u16 tem_len,tem_hard;
	u8 i,ret=0;
	
	RecFrame.header = indata[0];
	
	tem_len |= indata[1]<<8;
	tem_len |= indata[2];
	RecFrame.len = tem_len;
	
	RecFrame.type = indata[3];
	
	RecFrame.version = indata[4];
	
	tem_hard |= indata[5]<<8;
	tem_hard |= indata[6];
	RecFrame.hard = tem_hard;
	
	//先验证帧完整性，查看帧尾是否正确
	if(indata[tem_hard+3] == FRAME_HEX_TAIL) //3 = 1 + 2 帧头 一个字节 长度 三个字节
	{
		if(tem_hard<4)
		{
			RecFrame.FrameData.len = tem_hard - 4;//数据长度等与 总长度减4 2个字节的硬件号 1个字节版本号 和1个粽子节帧类型
			//正确,接收帧数据
			if(RecFrame.FrameData.len == 0) 
			{	//无数据位 可能为 握手等协议
				
			}
			else
			{
				for(i=0;i<RecFrame.FrameData.len;i++)
				{
					RecFrame.FrameData.data[i] = indata[i+7];
				}
			}
			//帧正确 ret = 0
		}
		else
		{
			ret = 2; //tem_hard < 4 暂时没有协议帧长度小于4
		}
	}
	else
	{
		ret = 1;	//帧不完整
	}
	return ret;
}
//包装函数 将发送的协议包装
static void FrameStructure(u8* indata, u16 inlen,u8* outdata, u8* outlen)
{
	u16 len = FIXATION_LEN+inlen;
	
	outdata[0] = FRAME_HEX_HEADER;
	outdata[1] = (u8)(len>>8);
	outdata[2] = (u8)len;
	outdata[3] = 
	outdata[inlen+FIXATION_LEN] = FRAME_HEX_TAIL;
	
}
//判断帧的固定帧 返回 1:成功 0:软件版本对应不上 2:硬件版本对应不上
//ps:需要先将输入的数据通过帧完整性判断
static u8 JudgementFixationFrame(u8* indata,u16 inlen)
{
	u8 ret;
	u8 version;
	u16 hard;
	
	version = indata[4];
	hard |= ((u16)indata[5])<<8;
	hard |= (u16)indata[6];
	
	if(version == SOFTWARE_VERSION)
	{
		//软件版本能对应上
		if(hard == LGJType)	
		{
			//硬件版本能对应上	ps:暂时不支持直接协议修改硬件版本，之后可以添加 设计为硬件类型为变量
			ret = 1;
		}
		else
		{
			ret = 2;
		}
	}
	else
	{
		ret = 0;
	}
	return ret;
}
