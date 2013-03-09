#ifndef _DOOLITTLE_H_
#define _DOOLITTLE_H_

#include "typedef.h"

#define  MAT_ORD_MAX    15  //������߽���
#define  INVALID_SEQ       (MAT_ORD_MAX*MAT_ORD_MAX) 
#define  MAT_L_SEQ_MAX  (MAT_ORD_MAX*(MAT_ORD_MAX-1)/2)  //(n*(n-1)/2)
#define  MAT_U_SEQ_MAX  (MAT_ORD_MAX*(MAT_ORD_MAX+1)/2) //(n*(n+1)/2)

#define  ERR_A_MSG   "A���в��������A��������\n"
#define  ERR_L_MSG   "L���в�����ƥ������A��������\n"
#define  ERR_U_MSG   "U���в�����ƥ������A��������\n"

#define  TYPE_FLOAT    1
#define  TYPE_S8          2
#define  TYPE_S16        3
#define  TYPE_S32        4

//================ �������� ==================//
//u8 GetAPos(u8 u8Row,u8 u8Col,u8 u8Order);
u8 GetLPos(u8 u8Row,u8 u8Col,u8 u8Order);
u8 GetUPos(u8 u8Row,u8 u8Col,u8 u8Order);

//void GetMatA(s8 *pMatricA);//�û��������A�ĸ�Ԫ�أ����ؾ������
//void GetMatA(char* pFileStr,u8 u8Order,int nSaveA[MAT_ORD_MAX][MAT_ORD_MAX]);//�����������ȷ��һά
int GetMatA(char* pFileStr,u8 u8Order,int nSaveA[MAT_ORD_MAX][MAT_ORD_MAX]);//�����������ȷ��һά
int GetMatLU(int nMatA[MAT_ORD_MAX][MAT_ORD_MAX],u8 u8Order,int nSaveL[],int nSaveU[]);
#endif