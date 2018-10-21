#include "app_data.h"

static sFrame RecFrame,SedFrame;

static u8 JudgeFrame(const u8* indata,u16 len);
static void FrameStructure(u8* indata, u16 inlen,u8* outdata, u8* outlen);
static u8 JudgementFixationFrame(u8* indata,u16 inlen);

void AppDataDeal(const u8* data,u16 len)
{
	u8 i,ret = 0xff;
	u8 rec_ret; //���ջظ���0������ظ���1����Ҫ�ظ�
	u8 ret_data[50];//�������жϺ�Ĵ���������
	u16 ret_len;//���������ݵ�֡����
	
	//*******���ղ���*******//
	//*******|___�����������ж�
	if(data[0] == FRAME_HEX_HEADER)
	{
		//��֡Ϊ0x68
		ret = JudgeFrame(data,len,ret_data,&ret_len);//10-18�����������ж� Ҫ�����ж�����������������ݳ���
	}
	else
	{
		//��֡�͵�һ���ֽڶ�Ӧ���ϣ�������������֡
		for(i=0;i<len;i++)
		{
			if(data[i] == FRAME_HEX_HEADER)
			{
				//�ҵ���֡
				
				ret=JudgeFrame(&data[i],len-i,ret_data,&ret_len);//10-18�����������ж� Ҫ�����ж�����������������ݳ���
				break;
			}
		}
	}
	//*******|___���ݴ���
	if(ret == 0xff)
	{
		//�������û���ҵ�֡ͷ
	}
	else if(ret == 0)
	{
		//���ճɹ�
		if (JudgementFixationFrame(ret_data, ret_len)==1u)//���ж�֡�Ĺ̶������Ƿ���ȷ
		{//������ȷ
			if (FrameDealDataToStruct(ret_data, &ret_len, &RecFrame) == 1u)
			{
				if ((RecFrame.type == HANDSHAKE_FRAMETYPE) || (RecFrame.type == HEARTBEAT_FRAMETYPE)\
					|| (RecFrame.type == DETECTION_FRAMETYPE) || (RecFrame.type == MEASURING_FRAMETYPE)\
					|| (RecFrame.type == END_FRAMETYPE))
				{
					rec_ret = 1u;
				}
			}
		}

	}
	else
	{
		//���մ��� 
		if(ret == 1)
		{
			//֡������
		}
		else if(ret == 2)
		{
			//֡����С��4
		}
		else
		{
			//���� �����ܿ�
		}
	}
	//********���Ͳ���*********//
	if(rec_ret == 1u)
	{//��Ҫ�ظ�
		rec_ret = 0;
		if(RecFrame.type == HANDSHAKE_FRAMETYPE)
		{	//�ظ�����
			
		}
	}
	
}
/* 	֡�жϺ��� ��⵽֡ͷִ�У�����֡��Ӧ����ṹ���� 
	���أ�0 ��ȷ���գ� 1 ֡������ 2 ֡����С��4
���� indata: Ҫ�����֡��ַ��len:Ҫ����֡�ĳ��� �� data:  */
static u8 JudgeFrame(const u8* indata,u16 len)	//len ���Ƴ��� �������󳤶� 
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
	
	//����֤֡�����ԣ��鿴֡β�Ƿ���ȷ
	if(indata[tem_hard+3] == FRAME_HEX_TAIL) //3 = 1 + 2 ֡ͷ һ���ֽ� ���� �����ֽ�
	{
		if(tem_hard<4)
		{
			RecFrame.FrameData.len = tem_hard - 4;//���ݳ��ȵ��� �ܳ��ȼ�4 2���ֽڵ�Ӳ���� 1���ֽڰ汾�� ��1�����ӽ�֡����
			//��ȷ,����֡����
			if(RecFrame.FrameData.len == 0) 
			{	//������λ ����Ϊ ���ֵ�Э��
				
			}
			else
			{
				for(i=0;i<RecFrame.FrameData.len;i++)
				{
					RecFrame.FrameData.data[i] = indata[i+7];
				}
			}
			//֡��ȷ ret = 0
		}
		else
		{
			ret = 2; //tem_hard < 4 ��ʱû��Э��֡����С��4
		}
	}
	else
	{
		ret = 1;	//֡������
	}
	return ret;
}
//��װ���� �����͵�Э���װ
static void FrameStructure(u8* indata, u16 inlen,u8* outdata, u8* outlen)
{
	u16 len = FIXATION_LEN+inlen;
	
	outdata[0] = FRAME_HEX_HEADER;
	outdata[1] = (u8)(len>>8);
	outdata[2] = (u8)len;
	outdata[3] = 
	outdata[inlen+FIXATION_LEN] = FRAME_HEX_TAIL;
	
}
//�ж�֡�Ĺ̶�֡ ���� 1:�ɹ� 0:����汾��Ӧ���� 2:Ӳ���汾��Ӧ����
//ps:��Ҫ�Ƚ����������ͨ��֡�������ж�
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
		//����汾�ܶ�Ӧ��
		if(hard == LGJType)	
		{
			//Ӳ���汾�ܶ�Ӧ��	ps:��ʱ��֧��ֱ��Э���޸�Ӳ���汾��֮�������� ���ΪӲ������Ϊ����
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
/*���ݴ��� ��֡�������봦��ת���ɽṹ����Ϣ 
	indata����������� data����������鳤�� outframe������Ľṹ��
	���� 1����ȷ 0��ʧ��*/
static u8 FrameDealDataToStruct(u8* indata, u16 datalen, sFrame* outframe)
{
	//...
}