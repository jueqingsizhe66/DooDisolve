#ifndef _DOOLITTLE_H_
#define _DOOLITTLE_H_

#include "typedef.h"

#define  MAT_ORD_MAX    15  //矩阵最高阶数
#define  INVALID_SEQ       (MAT_ORD_MAX*MAT_ORD_MAX) 
#define  MAT_L_SEQ_MAX  (MAT_ORD_MAX*(MAT_ORD_MAX-1)/2)  //(n*(n-1)/2)
#define  MAT_U_SEQ_MAX  (MAT_ORD_MAX*(MAT_ORD_MAX+1)/2) //(n*(n+1)/2)

#define  ERR_A_MSG   "A行列参数或矩阵A阶数有误\n"
#define  ERR_L_MSG   "L行列参数不匹配或矩阵A阶数有误\n"
#define  ERR_U_MSG   "U行列参数不匹配或矩阵A阶数有误\n"

#define  TYPE_FLOAT    1
#define  TYPE_S8          2
#define  TYPE_S16        3
#define  TYPE_S32        4

//================ 函数声明 ==================//
//u8 GetAPos(u8 u8Row,u8 u8Col,u8 u8Order);
u8 GetLPos(u8 u8Row,u8 u8Col,u8 u8Order);
u8 GetUPos(u8 u8Row,u8 u8Col,u8 u8Order);

//void GetMatA(s8 *pMatricA);//用户输入矩阵A的各元素，返回矩阵阶数
//void GetMatA(char* pFileStr,u8 u8Order,int nSaveA[MAT_ORD_MAX][MAT_ORD_MAX]);//数组参数至少确定一维
int GetMatA(char* pFileStr,u8 u8Order,int nSaveA[MAT_ORD_MAX][MAT_ORD_MAX]);//数组参数至少确定一维
int GetMatLU(int nMatA[MAT_ORD_MAX][MAT_ORD_MAX],u8 u8Order,int nSaveL[],int nSaveU[]);
#endif