#include "doolittle.h"
#include <stdio.h>
#include "build.h"

/***************************************************************************************************
��  �� : u8 GetAPos(u8 u8Row,u8 u8Col,u8 u8Order)
��  �� : u8Row--����A��ĳ��Ԫ����������(1 2 ... N)��u8Col--����A��ĳ��Ԫ����������(1 2 ... N)��
            u8Order--A�Ľ���(N)
��  �� : ����A��ĳ��Ԫ��λ������A��ʵ�����(0 1 2.... N^2-1)����Ϊ����ֵ
��  ע : ����A��һά����洢
*****************************************************************************************************/
/*
u8 GetAPos(u8 u8Row,u8 u8Col,u8 u8Order)
{
	u8 u8Seq = INVALID_SEQ; //���Գ�����Χ�����

	if( (u8Order < MAT_ORD_MAX+1) && (u8Row < u8Order+1) && (u8Col < u8Order+1) 
		&& (u8Row>0) && (u8Col > 0) )
	{
		u8Seq = (u8Row-1)*u8Order + u8Col-1;
	}
	else
	{
		printf(ERR_A_MSG);
	}

	return u8Seq;
}
*/
/***************************************************************************************************
��  �� : u8 GetLPos(u8 u8Row,u8 u8Col,u8 u8Order)
��  �� : u8Row--����L��ĳ��Ԫ����������(2 3... N)��u8Col--����L��ĳ��Ԫ����������(1 2 ... N)��
            u8Order--A�Ľ���(N)
��  �� : ����L��ĳ��Ԫ��λ������A��ʵ�����(0 1 2.... N(N-1)/2-1)����Ϊ����ֵ
��  ע : ����L��һά����洢����Ҫ�� 1 <= col < row <= order��L�Խ�����Ϊȫ1
*****************************************************************************************************/
u8 GetLPos(u8 u8Row,u8 u8Col,u8 u8Order)
{
	u8 u8Seq = INVALID_SEQ; //���Գ�����Χ�����

	if( (u8Order < MAT_ORD_MAX+1) && (u8Col > 0) && (u8Col < u8Row) && (u8Row < u8Order+1) )
	{
		u8Seq = (u8Row-2)*(u8Row-1)/2 + u8Col-1;//����L��l21��l31��l32��ʼ�洢
	}
	else
	{
		printf(ERR_L_MSG);
	}

	return u8Seq;
}

/***************************************************************************************************
��  �� : u8 GetUPos(u8 u8Row,u8 u8Col,u8 u8Order)
��  �� : u8Row--����U��ĳ��Ԫ����������(1 2 ... N)��u8Col--����U��ĳ��Ԫ����������(1 2 ... N)��
            u8Order--A�Ľ���(N)
��  �� : ����U��ĳ��Ԫ��λ������U��ʵ�����(0 1 2.... N(N+1)/2-1)����Ϊ����ֵ
��  ע : ����L��һά����洢����Ҫ�� 1 <=  row <= col <= order
*****************************************************************************************************/
u8 GetUPos(u8 u8Row,u8 u8Col,u8 u8Order)
{
	u8 u8Seq = INVALID_SEQ; //���Գ�����Χ�����

	if( (u8Order < MAT_ORD_MAX+1) && (u8Row > 0) && ( u8Row< u8Col+1) && (u8Col < u8Order+1) )
	{
		u8Seq = (2*u8Order+2-u8Row)*(u8Row-1)/2 + u8Col-u8Row;//����U��U11��U12��U13��ʼ�洢
	}
	else
	{
		printf(ERR_U_MSG);
	}

	return u8Seq;
}

/***************************************************************************************************
��  �� : int GetMatA(char* pFileStr,u8 u8Order,int nSaveA[MAT_ORD_MAX][MAT_ORD_MAX])
��  �� : pFileStr--����A�������洢���ļ�
��  �� : nSaveA--��ž���A�Ķ�ά�����׵�ַ
��  ע : 
*****************************************************************************************************/
//void GetMatA(char* pFileStr,u8 u8Order,int nSaveA[][])
int GetMatA(char* pFileStr,u8 u8Order,int nSaveA[MAT_ORD_MAX][MAT_ORD_MAX])
{
	FILE* pDateFile;
	u8 i = 0,j=0;
	
	if(u8Order <= MAT_ORD_MAX)
	{
		pDateFile = fopen(pFileStr,"r");
		if(!pDateFile)
		{
			printf("%s��ʧ�ܣ�\n",pFileStr);
			return -1;
		}
		
		for(i=0;i<u8Order;i++)
		{
			for(j=0;j<u8Order;j++)
			{
				//fscanf(pDateFile,"%d",&u32MatA[i][j]);
				fscanf(pDateFile,"%d",&nSaveA[i][j]);
			}
		}
		
		#if(DBG_MSG)
		printf("�ļ���ȡ���");
		for(i=0;i<u8Order;i++)
		{
			printf("\n");
			for(j=0;j<u8Order;j++)
			{
				printf("%d\t",u32MatA[i][j]);
			}
		}
		#endif
		fclose(pDateFile);
	}
	return 0;
}

/***************************************************************************************************
��  �� : void GetMatLU(int nMatA[MAT_ORD_MAX][MAT_ORD_MAX],int nSaveL[],int nSaveU[])
��  �� : nMatA--��ž���A��ά�����׵�ַ��u8 u8Order--�������
��  �� : nSaveL--��ž���L��һά�����׵�ַ��nSaveU--��ž���U��һά�����׵�ַ
��  ע : u8SeqU = (2*u8Order+2-u8Row)*(u8Row-1)/2 + u8Col -u8Row
		   u8SeqL = (u8Row-2)*(u8Row-1)/2 + u8Col-1
*****************************************************************************************************/
int GetMatLU(int nMatA[MAT_ORD_MAX][MAT_ORD_MAX],u8 u8Order,int nSaveL[],int nSaveU[])
{
	u8 u8SeqU = 0,u8SeqL=0;
	u8 i=0,j=0,k=0;
	int nTemp = 0;

	nSaveU[j] = nMatA[0][j]; //U�ĵ�1�С���1��
	for(j=2;j<u8Order+1;j++) //
	{
		u8SeqU = j-1; //U�ĵ�1�С��ڣ�i+1����
		//u8SeqU = (2*u8Order+2-u8Row)*(u8Row-1)/2 + u8Col -u8Row;
		nSaveU[u8SeqU] = nMatA[0][j-1];//�õ�U�ĵ�1��
	
		u8SeqL = (j-2)*(j-1)/2;//����L��l21��l31��l32��ʼ�洢
		//u8SeqL = (u8Row-2)*(u8Row-1)/2 + u8Col-1;//����L��l21��l31��l32��ʼ�洢
		nSaveL[u8SeqL] = nMatA[j-1][0]/nSaveU[0]; //Li1 = Ai1/U11���õ�L�ĵ�1��
	}
	
	for(k=2;k<u8Order+1;k++) //U�ĵ�2�С�L�ĵ�2�п�ʼ
	{
		for(j=k;j<u8Order+1;j++)
		{
			nTemp = 0;
			for(i=1;i<k;i++)// [1...k-1]
			{
				u8SeqL = (k-2)*(k-1)/2 + i-1;
				u8SeqU = (2*u8Order+2-i)*(i-1)/2 + j -i;
				nTemp += nSaveL[u8SeqL]*nSaveU[u8SeqU]; // s = ��Lkt*Utj
			}
			//u8SeqU = (2*u8Order+2-i)*(i-1)/2 + j -i; //���ѭ������i=k����Ukj
			u8SeqU = (2*u8Order+2-k)*(k-1)/2 + j -k; 
			nSaveU[u8SeqU] = nMatA[k-1][j-1] - nTemp; // Ukj = Akj - s
		}
	
		for(j=k+1;j<u8Order+1;j++)
		{
			nTemp = 0;
			for(i=1;i<k;i++) // [1...k-1]
			{
				u8SeqL = (j-2)*(j-1)/2 + i-1;
				u8SeqU = (2*u8Order+2-i)*(i-1)/2 + k -i;
				nTemp += nSaveL[u8SeqL]*nSaveU[u8SeqU]; // s = ��Ljt*Utk
			}
			u8SeqL = (j-2)*(j-1)/2 + i-1; // ���ѭ��������i=k ��Ljk
			u8SeqU = (2*u8Order+2-i)*(i-1)/2 + k -i;//���ѭ��������i=k����Ukk
		
			if(!nSaveU[u8SeqU]) //������Ϊ0
			{
				printf("�Խ�Ԫ��U[%d][%d]Ϊ0�������˳�!\n",k,k);
				return -1;
			}
			nSaveL[u8SeqL] = (nMatA[j-1][k-1] - nTemp)/nSaveU[u8SeqU]; // Ljk = (Ajk-s)/Ukk
		}
	}
	
	return 0;
}