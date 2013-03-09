#include "doolittle.h"
#include <stdio.h>
#include "build.h"

/***************************************************************************************************
函  数 : u8 GetAPos(u8 u8Row,u8 u8Col,u8 u8Order)
输  入 : u8Row--矩阵A的某个元素所在行数(1 2 ... N)，u8Col--矩阵A的某个元素所在列数(1 2 ... N)，
            u8Order--A的阶数(N)
输  出 : 矩阵A中某个元素位于数组A的实际序号(0 1 2.... N^2-1)，作为返回值
附  注 : 矩阵A由一维数组存储
*****************************************************************************************************/
/*
u8 GetAPos(u8 u8Row,u8 u8Col,u8 u8Order)
{
	u8 u8Seq = INVALID_SEQ; //明显超出范围的序号

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
函  数 : u8 GetLPos(u8 u8Row,u8 u8Col,u8 u8Order)
输  入 : u8Row--矩阵L的某个元素所在行数(2 3... N)，u8Col--矩阵L的某个元素所在列数(1 2 ... N)，
            u8Order--A的阶数(N)
输  出 : 矩阵L中某个元素位于数组A的实际序号(0 1 2.... N(N-1)/2-1)，作为返回值
附  注 : 矩阵L由一维数组存储，且要求 1 <= col < row <= order，L对角线上为全1
*****************************************************************************************************/
u8 GetLPos(u8 u8Row,u8 u8Col,u8 u8Order)
{
	u8 u8Seq = INVALID_SEQ; //明显超出范围的序号

	if( (u8Order < MAT_ORD_MAX+1) && (u8Col > 0) && (u8Col < u8Row) && (u8Row < u8Order+1) )
	{
		u8Seq = (u8Row-2)*(u8Row-1)/2 + u8Col-1;//矩阵L从l21、l31、l32开始存储
	}
	else
	{
		printf(ERR_L_MSG);
	}

	return u8Seq;
}

/***************************************************************************************************
函  数 : u8 GetUPos(u8 u8Row,u8 u8Col,u8 u8Order)
输  入 : u8Row--矩阵U的某个元素所在行数(1 2 ... N)，u8Col--矩阵U的某个元素所在列数(1 2 ... N)，
            u8Order--A的阶数(N)
输  出 : 矩阵U中某个元素位于数组U的实际序号(0 1 2.... N(N+1)/2-1)，作为返回值
附  注 : 矩阵L由一维数组存储，且要求 1 <=  row <= col <= order
*****************************************************************************************************/
u8 GetUPos(u8 u8Row,u8 u8Col,u8 u8Order)
{
	u8 u8Seq = INVALID_SEQ; //明显超出范围的序号

	if( (u8Order < MAT_ORD_MAX+1) && (u8Row > 0) && ( u8Row< u8Col+1) && (u8Col < u8Order+1) )
	{
		u8Seq = (2*u8Order+2-u8Row)*(u8Row-1)/2 + u8Col-u8Row;//矩阵U从U11、U12、U13开始存储
	}
	else
	{
		printf(ERR_U_MSG);
	}

	return u8Seq;
}

/***************************************************************************************************
函  数 : int GetMatA(char* pFileStr,u8 u8Order,int nSaveA[MAT_ORD_MAX][MAT_ORD_MAX])
输  入 : pFileStr--矩阵A数据所存储的文件
输  出 : nSaveA--存放矩阵A的二维数组首地址
附  注 : 
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
			printf("%s打开失败！\n",pFileStr);
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
		printf("文件读取完毕");
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
函  数 : void GetMatLU(int nMatA[MAT_ORD_MAX][MAT_ORD_MAX],int nSaveL[],int nSaveU[])
输  入 : nMatA--存放矩阵A二维数组首地址，u8 u8Order--矩阵阶数
输  出 : nSaveL--存放矩阵L的一维数组首地址，nSaveU--存放矩阵U的一维数组首地址
附  注 : u8SeqU = (2*u8Order+2-u8Row)*(u8Row-1)/2 + u8Col -u8Row
		   u8SeqL = (u8Row-2)*(u8Row-1)/2 + u8Col-1
*****************************************************************************************************/
int GetMatLU(int nMatA[MAT_ORD_MAX][MAT_ORD_MAX],u8 u8Order,int nSaveL[],int nSaveU[])
{
	u8 u8SeqU = 0,u8SeqL=0;
	u8 i=0,j=0,k=0;
	int nTemp = 0;

	nSaveU[j] = nMatA[0][j]; //U的第1行、第1列
	for(j=2;j<u8Order+1;j++) //
	{
		u8SeqU = j-1; //U的第1行、第（i+1）列
		//u8SeqU = (2*u8Order+2-u8Row)*(u8Row-1)/2 + u8Col -u8Row;
		nSaveU[u8SeqU] = nMatA[0][j-1];//得到U的第1行
	
		u8SeqL = (j-2)*(j-1)/2;//矩阵L从l21、l31、l32开始存储
		//u8SeqL = (u8Row-2)*(u8Row-1)/2 + u8Col-1;//矩阵L从l21、l31、l32开始存储
		nSaveL[u8SeqL] = nMatA[j-1][0]/nSaveU[0]; //Li1 = Ai1/U11，得到L的第1列
	}
	
	for(k=2;k<u8Order+1;k++) //U的第2行、L的第2列开始
	{
		for(j=k;j<u8Order+1;j++)
		{
			nTemp = 0;
			for(i=1;i<k;i++)// [1...k-1]
			{
				u8SeqL = (k-2)*(k-1)/2 + i-1;
				u8SeqU = (2*u8Order+2-i)*(i-1)/2 + j -i;
				nTemp += nSaveL[u8SeqL]*nSaveU[u8SeqU]; // s = ∑Lkt*Utj
			}
			//u8SeqU = (2*u8Order+2-i)*(i-1)/2 + j -i; //求和循环结束i=k，即Ukj
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
				nTemp += nSaveL[u8SeqL]*nSaveU[u8SeqU]; // s = ∑Ljt*Utk
			}
			u8SeqL = (j-2)*(j-1)/2 + i-1; // 求和循环结束，i=k 即Ljk
			u8SeqU = (2*u8Order+2-i)*(i-1)/2 + k -i;//求和循环结束，i=k，即Ukk
		
			if(!nSaveU[u8SeqU]) //被除数为0
			{
				printf("对角元素U[%d][%d]为0，程序退出!\n",k,k);
				return -1;
			}
			nSaveL[u8SeqL] = (nMatA[j-1][k-1] - nTemp)/nSaveU[u8SeqU]; // Ljk = (Ajk-s)/Ukk
		}
	}
	
	return 0;
}