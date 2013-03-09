#include "doolittle.h"
#include "typedef.h"
#include <stdio.h>
#include <ctype.h> // isdigit
#include <stdlib.h> // atoi
#include "build.h"

//======== 定义命令行参数的顺序 =======//
#define   PROG_SEQ        0
#define   FILE_SEQ           1
#define   ORDER_SEQ      2

int main(int argc,char* argv[])
{
	//s8  s8MatricA[MAT_ORD_MAX*MAT_ORD_MAX];
	u8 u8Order = 0;
//	s8  s8OrderChar=0;
	int i = 0,j=0,nSeq = 0;
	int   u32MatA[MAT_ORD_MAX][MAT_ORD_MAX];//存放矩阵A的数据
	int  nMatU[MAT_U_SEQ_MAX],nMatL[MAT_L_SEQ_MAX];

	if(argc !=3)
	{
		printf("dolt使用方法：dolt datefile order\n");
	}
	else
	{
		#if(DBG_MSG)
		printf("argc = %d\n",argc);
		printf("argv[PROG_SEQ] = %s\t",argv[0]);
		printf("argv[FILE_SEQ] = %s\t",argv[1]);
		printf("argv[ORDER_SEQ] = %s\n",argv[ORDER_SEQ]);
		printf("argv[ORDER_SEQ]1=%d,argv[ORDER_SEQ]2=%d\n",*argv[ORDER_SEQ],*(argv[ORDER_SEQ]+1));
		#endif
		i = 0;
	
		u8Order = (u8)atoi(argv[ORDER_SEQ]); //字符串 ---> 整数
		if(!u8Order)
		{
			printf("第3个参数只能是10进制数字!\n");
			return 0;
		}
		else if(u8Order>MAT_ORD_MAX)
		{
			printf("矩阵阶数过大!\n");
			return 0;
		}
		#if(DBG_MSG)
		printf("字符串转换整型数，%d",u8Order);
		#endif
		
		//GetMatA(argv[1],u8Order);//从argv[1]指定的参数中获取数据文件
		nSeq = GetMatA(argv[FILE_SEQ],u8Order,u32MatA);//从argv[1]指定的参数中获取数据文件，存放至u32MatA[][]
		if(nSeq != 0) //获取A出现故障
		{
			printf("未获取到矩阵A的数据\n");
			return 0;
		}
		
		//数组初始化
		for(i=0;i<MAT_U_SEQ_MAX;i++)
		{
			nMatU[i] = 0;
		}
		for(i=0;i<MAT_L_SEQ_MAX;i++)
		{
			nMatL[i] = 0;
		}
		
		nSeq = GetMatLU(u32MatA,u8Order,nMatL,nMatU);//从分解A得到L和U
		if(nSeq != 0) //获取L、U出现异常
		{
			return 0;
		}
	
		printf("\n============ Matric A =========");
		for(i=0;i<u8Order;i++)
		{
			printf("\n");
			for(j=0;j<u8Order;j++)
			{
				printf("%d\t",u32MatA[i][j]);
			}
		}
	
		//======== 显示L========//
		printf("\n\n============ Matric L =========");
		for(i=1;i<u8Order+1;i++)
		{
			printf("\n");
			for(j=1;j<i;j++)
			{
				nSeq = (i-2)*(i-1)/2 + j-1;
				printf("%d\t",nMatL[nSeq]);
			}
			printf("1");//把对角上的1打印出来
		}
	
		//======== 显示U========//
		printf("\n\n============ Matric U =========");
		for(i=1;i<u8Order+1;i++)
		{
			printf("\n");
			for(j=0;j<i-1;j++)
			{
				printf("\t");
			}
			for(j=i;j<u8Order+1;j++)
			{
				nSeq = (2*u8Order+2-i)*(i-1)/2 + j -i;
				printf("%d\t",nMatU[nSeq]);
			}
		}
	}
	
	return 0;
}
