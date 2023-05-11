#include"Cross.h"
int CrossOperate();			//十字链表操作界面 
int MatrixCalculate();		//矩阵运算界面 
int MultiMatrix();			//多矩阵运算界面 
int SingleMatrix();			//单矩阵运算界面 
int main(){
	int  n;
	while(1){
		printf("*****************************欢迎使用稀疏矩阵十字链表**************************\n\n");
		printf("1. 创建十字链表	                2. 十字链表操作		        3. 输出十字链表\n\n\n");
		printf("4. 矩阵运算	                5. 存入文件                     6. 退出系统\n\n");
		printf("*******************************************************************************\n");
		printf("请输入需要实现的操作:");
		scanf("%d",&n);
		switch(n){
			case 1:system("cls");Initiate();system("pause");break;
			case 2:system("cls");CrossOperate();break;
			case 3:system("cls");PrintCross();system("pause");break;
			case 4:system("cls");MatrixCalculate();break;
			case 5:system("cls");Memory();system("pause");break;
			case 6:printf("退出成功!\n");exit(0);break;
			default:printf("错误数字!\n");fflush(stdin);system("pause");
		} 
		system("cls");
	}
} 
int CrossOperate(){
	int  n;
	while(1){
		printf("*****************************欢迎使用稀疏矩阵十字链表**************************\n\n");
		printf("1. 获取一项	                2. 设置一项		        3. 插入一项 \n\n\n");
		printf("4. 删除一项		        5. 返回上一界面			6. 退出系统\n\n");
		printf("*******************************************************************************\n");
		printf("请输入需要实现的操作:");
		scanf("%d",&n);
		switch(n){
			case 1:system("cls");GetValue();system("pause");break;
			case 2:system("cls");SetValue();system("pause");break;
			case 3:system("cls");InsertValue();system("pause");break;
			case 4:system("cls");DeleteValue();system("pause");break;
			case 5:return 0;break;
			case 6:printf("退出成功!\n");exit(0);break;
			default:printf("错误数字!\n");fflush(stdin);system("pause");
		} 
		system("cls");
	}
} 
int MatrixCalculate(){
	int  n;
	while(1){
		printf("*****************************欢迎使用稀疏矩阵十字链表**************************\n\n");
		printf("1.多矩阵运算       						2. 单矩阵运算\n\n\n");
		printf("3. 返回上一界面							4. 退出系统\n\n");
		printf("*******************************************************************************\n");
		printf("请输入需要实现的操作:");
		scanf("%d",&n);
		switch(n){
			case 1:system("cls");MultiMatrix();break;
			case 2:system("cls");SingleMatrix();break;
			case 3:return 0;break;
			case 4:printf("退出成功!\n");exit(0);break;
			default:printf("错误数字!\n");fflush(stdin);system("pause");
		} 
		system("cls");
	}
} 
int MultiMatrix(){
	int  n;
	while(1){
		printf("*****************************欢迎使用稀疏矩阵十字链表**************************\n\n");
		printf("1. 矩阵加法       		2. 矩阵减法    			3. 矩阵乘法    \n\n\n");
		printf("	    4. 返回上一界面			5. 退出系统\n\n");
		printf("*******************************************************************************\n");
		printf("请输入需要实现的操作:");
		scanf("%d",&n);
		switch(n){
			case 1:system("cls");MatrixAdd();system("pause");break;
			case 2:system("cls");MatrixSub();system("pause");break;
			case 3:system("cls");MatrixMul();system("pause");break;
			case 4:return 0;break;
			case 5:printf("退出成功!\n");exit(0);break;
			default:printf("错误数字!\n");fflush(stdin);system("pause");
		} 
		system("cls");
	}
} 
int SingleMatrix(){
	int  n;
	while(1){
		printf("*****************************欢迎使用稀疏矩阵十字链表**************************\n\n");
		printf("1. 矩阵逆置			2. 逆矩阵			3. 行列式   \n\n\n");
		printf("4. 最值 		     	5. 返回上一界面			6. 退出系统\n\n");
		printf("*******************************************************************************\n");
		printf("请输入需要实现的操作:");
		scanf("%d",&n);
		switch(n){
			case 1:system("cls");Transpose();system("pause");break;
			case 2:system("cls");Inverse();system("pause");break;
			case 3:system("cls");Determinant();system("pause");break;
			case 4:system("cls");Maximun();system("pause");break;
			case 5:return 0;break;
			case 6:printf("退出成功!\n");exit(0);break;
			default:printf("错误数字!\n");fflush(stdin);system("pause");
		} 
		system("cls");
	}
} 
