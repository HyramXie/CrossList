#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
 

typedef struct{
	int den;
	int mol;
}DataType;

typedef struct OLNode
{
	int row, col;
	DataType value;
	struct OLNode *right, *down;  //同一行、同一列中的下一个非零元素 
}OLNode, *OLink;

typedef struct
{
	char name[10];					//十字链表的名字 
	OLink *row_head, *col_head;  //指向指针的指针，当作数组来用 
	int m, n, len;  			//矩阵的行数、列数、非零元素的个数 
}CrossList; 

CrossList Cross[10];		//十字链表数组用于存放十字链表 
int last=0; 				//该数组已经存放的十字链表个数 

void Initiate();			//创建十字链表 
void PrintCross();			//输出打印十字链表 
void PrintMatrix(int i);	//打印稀疏矩阵 
void PrintMatrix2(int i);	//打印稀疏矩阵 
void SetValue(); 			//设置坐标位置值 
void GetValue();				//获取某一项的值 
void InsertValue(); 		//插入某一项的值 
void DeleteValue();			//删除某一项的值 
void MatrixAdd();			//矩阵加法运算 
void MatrixSub();			//矩阵减法运算 
void MatrixMul();			//矩阵乘法运算 
void Transpose();			//矩阵转置 
void Memory();				//存入文件 
void Maximun();				//求矩阵最值 
void Determinant();			//求行列式 
DataType Determinant1(CrossList *cross);					//求全局行列式 
DataType Determinant2(int x,int y,CrossList *cross);		//求局部行列式 
void Inverse();												//求逆矩阵 
void Distribute(int m,int n);								//给十字链表分配空间 
int gcd(int a,int b);										//求最大公因数 


void Initiate(){
	int i;
	FILE *fp;
	OLNode node,*p=NULL,*q=NULL;
	char s[10]; 
	printf("请输入十字链表名称:");
	scanf("%s",s);
	for(i=0;i<last;i++){						//判断链表是否存在 
		if(strcmp(Cross[i].name,s)==0){
			printf("该十字链表已存在!\n");
			return ;
		}
	}
	strcpy(Cross[last].name,s);
	printf("请输入存储稀疏矩阵的文件名:");
	scanf("%s",s);
	if((fp=fopen(s,"rb"))==NULL){
		printf("不能打开文件!\n");
		return ; 								//对文件打不开的处理 
	}
	fread(&node,sizeof(OLNode),1,fp);			//读取稀疏矩阵的信息 
	Cross[last].len=(int)node.value.den; 	
	Distribute(node.row,node.col);				//分配空间 
	while(fread(&node,sizeof(OLNode),1,fp)) {
		q=(OLNode *)malloc(sizeof(OLNode));
		*q=node;		
		p=Cross[last].row_head[node.row-1];
		while(p->right!=NULL && p->right->col<q->col) 	//寻找结点的位置 将结点插入到对应的地方 
			p=p->right;										
		q->right=p->right;
		p->right=q;
		p=Cross[last].col_head[node.col-1];
		while(p->down!=NULL && p->down->row<q->row) 
			p=p->down;
		q->down=p->down;
		p->down=q;
	}
	PrintMatrix(last);
	last++;
	fclose(fp); 
	printf("创建成功!\n");  
	
}
void SetValue(){
	int i,x,y,tem;
	DataType value;				
	char s[10]; 
	OLNode *p=NULL;
	printf("请输入十字链表名称:");
	scanf("%s",s);
	for(i=0;i<last;i++){						//判断链表是否存在 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("十字链表不存在!\n");
		return ;
	} 
	printf("请输入坐标x y:"); 		
	scanf("%d%d",&x,&y);
	printf("请输入要设置的值:"); 
	value.mol=1;							
	scanf("%d/%d",&value.den,&value.mol);	
	if((tem=gcd(value.den,value.mol))!=1){	
		value.den=value.den/tem;
		value.mol=value.mol/tem;
	}
	p=Cross[i].row_head[x-1]->right;
	while(p!=NULL && p->col<y) 					//寻找坐标 
		p=p->right;	
	if(p!=NULL && p->col==y) {					//修改坐标值 
		p->value=value;
		printf("设置成功!\n");
	}
	else
		printf("该坐标在十字链表不存在!\n");
}
void GetValue(){
	int i,x,y;
	char s[10]; 
	OLNode *p=NULL;
	printf("请输入十字链表名称:");
	scanf("%s",s);
	for(i=0;i<last;i++){					//判断链表是否存在 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("十字链表不存在!\n");
		return ;
	} 
	printf("请输入坐标x y:"); 		
	scanf("%d%d",&x,&y);
	p=Cross[i].row_head[x-1]->right;	
	while(p!=NULL && p->col<y) 				//找坐标 
		p=p->right;	
	if(p!=NULL && p->col==y){				//获取坐标值	
		if(p->value.mol==1)
			printf("坐标值:%d\n",p->value.den);
		else 
			printf("坐标值:%d/%d\n",p->value.den,p->value.mol);
	}
	else
		printf("该坐标在十字链表不存在!\n");
}
void InsertValue(){
	int i,x,y,flag,tem;
	DataType value;				
	char s[10]; 
	OLNode *p=NULL,*q=NULL;
	printf("请输入十字链表名称:");
	scanf("%s",s);
	for(i=0;i<last;i++){							//判断链表是否存在 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("十字链表不存在!\n");
		return ;
	}  
	printf("请输入坐标x y:"); 		
	scanf("%d%d",&x,&y);
	printf("请输入要设置的值:"); 
	value.mol=1;							
	scanf("%d/%d",&value.den,&value.mol);	
	if((tem=gcd(value.den,value.mol))!=1){	
		value.den=value.den/tem;
		value.mol=value.mol/tem;
	}
	p=Cross[i].row_head[x-1];
	while(p->right!=NULL && p->right->col<y) 		//找坐标 
		p=p->right;	
	if(p->right!=NULL && p->right->col==y){			
		printf("该坐标在十字链表已存在，不能插入!\n是否需要修改?\n1:是  2:否");
		scanf("%d",&flag);
		if(flag)  p->right->value=value; 
		return ;
	}
	q=(OLNode *)malloc(sizeof(OLNode));					//插入一个结点	
	q->value=value;q->row=x;q->col=y;
	q->right=p->right;									//行插 
	p->right=q;
	
	p=Cross[i].col_head[y-1];
	while(p->down!=NULL && p->down->row<x) 				//寻找坐标 
		p=p->down;
	q->down=p->down;									//列插 
	p->down=q;
	printf("插入成功!\n");						
}
void DeleteValue(){
	int i,x,y;							
	char s[10]; 
	OLNode *p=NULL,*q=NULL;		
	printf("请输入十字链表名称:");
	scanf("%s",s);
	for(i=0;i<last;i++){							//判断链表是否存在 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("十字链表不存在!\n");
		return ;
	}  
	printf("请输入坐标x y:"); 		
	scanf("%d%d",&x,&y);
	p=Cross[i].row_head[x-1];
	while(p->right!=NULL && p->right->col<y) 		//找坐标 
		p=p->right;	
	if(p->right==NULL || p->right->col!=y){
		printf("该坐标在十字链表不存在，无法删除!\n");
		return ;
	}							
	q=p->right;					
	p->right=q->right;			//从行删除坐标 
	 
	p=Cross[i].col_head[y-1];
	while(p->down->row<x) 		//可以确定该坐标存在所以可以不用判断为空 找坐标 
		p=p->down;
	p->down=q->down;			//从列删除坐标 
	free(q);
	printf("删除成功!\n");		
}

void PrintMatrix(int i){					
	int j,k;
	OLNode *p=NULL;
	for(j=0;j<Cross[i].m;j++){					//从第一行开始遍历 
		p=Cross[i].row_head[j]->right;
		for(k=1;k<=Cross[i].n;k++){				//从第一列开始遍历 
			if(p!=NULL && k==p->col){			
				if(p->value.mol==1)														
					printf("%-5d",p->value.den);
				else 
					printf("%d/%-3d",p->value.den,p->value.mol);
				p=p->right;
			}
			else printf("%-5d",0);
		}
		printf("\n");
	}
}
void PrintMatrix2(int i){
	int j,k;
	OLNode *p=NULL;
	for(j=0;j<Cross[i].n;j++){					//从第一列开始遍历 
		p=Cross[i].col_head[j]->down;
		for(k=1;k<=Cross[i].m;k++){				//从第一列开始遍历 
			if(p!=NULL && k==p->col){		
				if(p->value.mol==1)														 
					printf("%-5d",p->value.den);
				else 
					printf("%d/%-3d",p->value.den,p->value.mol);
				p=p->right;
			}
			else printf("%-5d",0);
		}
		printf("\n");
	}
}

void PrintCross(){					
	int i,j,k;
	char s[10];
	OLNode *p=NULL;
	printf("请输入十字链表名称:");
	scanf("%s",s);
	for(i=0;i<last;i++){
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("十字链表不存在!\n");
		return ;
	}
	for(j=1;j<=6;j++){
		printf("%9d",j);
	}
	printf("\n");
	for(j=0;j<Cross[i].m;j++){					//从第一行开始遍历 
		p=Cross[i].row_head[j];
		printf("%d  ",j+1); 
		for(k=1;k<=Cross[i].n;k++){				//从第一列开始遍历 
			if(p->right!=NULL && k==p->right->col){			
				if(p->right->value.mol==1)														
					printf("--> %-5d",p->right->value.den);
				else 
					printf("--> %d/%-3d",p->right->value.den,p->right->value.mol);
				p=p->right;
			}
			else if(p->right==NULL){
				break;
			}
			else printf("---------");
		}
		printf("\n");
	}
}

void MatrixAdd(){								
	int i,j,x,len=0,tem;
	char s1[10],s2[10]; 
	OLNode *p=NULL,*q=NULL,*w=NULL,*u=NULL,*v=NULL;
	printf("请输入十字链表名称:");
	scanf("%s",s1);
	for(i=0;i<last;i++){						//判断链表是否存在 
		if(strcmp(Cross[i].name,s1)==0)
			break;	
	}
	if(i==last){
		printf("十字链表不存在!\n");
		return ;
	}
	printf("请输入十字链表名称:");				
	scanf("%s",s2);
	for(j=0;j<last;j++){						//判断链表是否存在 
		if(strcmp(Cross[j].name,s2)==0)
			break;	
	}
	if(j==last){
		printf("十字链表不存在!\n");
		return ;
	} 
	if(Cross[i].m!=Cross[j].m || Cross[i].n!=Cross[j].n){		//判断两个链表是否可以相加 
		printf("两个十字链表不能相加!\n");
		return ;
	}
	printf("请输入存储的十字链表名称:");
	scanf("%s",Cross[last].name);
	for(x=0;x<last;x++){									//判断链表是否存在 
		if(strcmp(Cross[x].name,Cross[last].name)==0){
			printf("该十字链表已存在!\n");
			return ;
		}
	}
	Distribute(Cross[i].m,Cross[i].n);
	for(x=0;x<Cross[last].m;x++){					//从第一行开始遍历 
		u=Cross[last].row_head[x];
		p=Cross[i].row_head[x]->right;
		q=Cross[j].row_head[x]->right;
		while(p!=NULL && q!=NULL){					//将坐标小的先插入十字链表 再将坐标相同的相加再插入	
			w=(OLNode *)malloc(sizeof(OLNode));	
			if(p->col<q->col){					
				*w=*p;
				p=p->right;
			}
			else if(p->col>q->col){
				*w=*q;
				q=q->right;
			}
			else {
				w->col=p->col;
				w->row=p->row;
				w->value.den=p->value.den*q->value.mol+q->value.den*p->value.mol;	
				w->value.mol=p->value.mol*q->value.mol;
				if((tem=gcd(w->value.den,w->value.mol))!=1){	
					w->value.den=w->value.den/tem;
					w->value.mol=w->value.mol/tem;
				}
				p=p->right;
				q=q->right;
			}
			len++;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
		}
		while(p!=NULL){									//将剩余的插入 
			w=(OLNode *)malloc(sizeof(OLNode));	
			*w=*p;
			p=p->right;
			len++;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
		}
			
		while(q!=NULL){									//将剩余的插入
			w=(OLNode *)malloc(sizeof(OLNode));	
			*w=*q;
			q=q->right;
			len++;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
		}	
	}
	Cross[last].len=len;
	PrintMatrix(last);
	last++;
}
void MatrixSub(){								
	int i,j,x,len=0,tem;
	char s1[10],s2[10]; 
	OLNode *p=NULL,*q=NULL,*w=NULL,*u=NULL,*v=NULL;
	printf("请输入十字链表名称:");
	scanf("%s",s1);
	for(i=0;i<last;i++){							//判断链表是否存在 
		if(strcmp(Cross[i].name,s1)==0)
			break;	
	}
	if(i==last){
		printf("十字链表不存在!\n");
		return ;
	}
	printf("请输入十字链表名称:");				
	scanf("%s",s2);
	for(j=0;j<last;j++){							//判断链表是否存在 
		if(strcmp(Cross[j].name,s2)==0)
			break;	
	}
	if(j==last){
		printf("十字链表不存在!\n");
		return ;
	} 
	if(Cross[i].m!=Cross[j].m || Cross[i].n!=Cross[j].n){	//判断两个链表是否可以相减 
		printf("两个十字链表不能相减!\n");
		return ;
	}
	printf("请输入存储的十字链表名称:");
	scanf("%s",Cross[last].name);
	for(x=0;x<last;x++){							//判断链表是否存在 
		if(strcmp(Cross[x].name,Cross[last].name)==0){
			printf("该十字链表已存在!\n");
			return ;
		}
	}
	Distribute(Cross[i].m,Cross[i].n);
	for(x=0;x<Cross[last].m;x++){					//从第一行开始遍历 
		u=Cross[last].row_head[x];
		p=Cross[i].row_head[x]->right;
		q=Cross[j].row_head[x]->right;
		while(p!=NULL && q!=NULL){					//将坐标小的先插入十字链表 再将坐标相同的相减再插入	
			w=(OLNode *)malloc(sizeof(OLNode));	
			if(p->col<q->col){
				*w=*p;
				p=p->right;
			}
			else if(p->col>q->col){
				w->row=q->row;
				w->col=q->col;
				w->value.den=-q->value.den;
				w->value.mol=q->value.mol;
				q=q->right;
			}
			else {
				w->col=p->col;
				w->row=p->row;
				w->value.den=p->value.den*q->value.mol-q->value.den*p->value.mol;	
				w->value.mol=p->value.mol*q->value.mol;
				if((tem=gcd(w->value.den,w->value.mol))!=1){	
					w->value.den=w->value.den/tem;
					w->value.mol=w->value.mol/tem;
				}
				p=p->right;
				q=q->right;
			}
			len++;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
		}
		while(p!=NULL){									//将剩余的插入
			w=(OLNode *)malloc(sizeof(OLNode));	
			*w=*p;
			p=p->right;
			len++;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
		}
			
		while(q!=NULL){									//将剩余的插入
			w=(OLNode *)malloc(sizeof(OLNode));	
			w->row=q->row;
			w->col=q->col;
			w->value.den=-q->value.den;
			w->value.mol=q->value.mol;
			q=q->right;
			len++;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
		}	
	}
	Cross[last].len=len;
	PrintMatrix(last);
	last++;
}
void MatrixMul(){												
	int i,j,x,y,len=0,tem1,tem2,tem;
	DataType sum; 
	char s1[10],s2[10]; 
	OLNode *p=NULL,*q=NULL,*w=NULL,*u=NULL,*v=NULL;
	printf("请输入十字链表名称:");
	scanf("%s",s1);
	for(i=0;i<last;i++){							//判断链表是否存在 
		if(strcmp(Cross[i].name,s1)==0)
			break;	
	}
	if(i==last){
		printf("十字链表不存在!\n");
		return ;
	}
	printf("请输入十字链表名称:");				
	scanf("%s",s2);
	for(j=0;j<last;j++){							//判断链表是否存在 
		if(strcmp(Cross[j].name,s2)==0)
			break;	
	}
	if(j==last){
		printf("十字链表不存在!\n");
		return ;
	} 
	if(Cross[i].m!=Cross[j].n){						//判断两个链表是否可以相乘 
		printf("两个十字链表不能相乘!\n");
		return ;
	}
	printf("请输入存储的十字链表名称:");
	scanf("%s",Cross[last].name);
	for(x=0;x<last;x++){							//判断链表是否存在 
		if(strcmp(Cross[x].name,Cross[last].name)==0){
			printf("该十字链表已存在!\n");
			return ;
		}
	}
	Distribute(Cross[i].m,Cross[j].n);
	for(x=0;x<Cross[last].m;x++){					//从第一行开始遍历 
		u=Cross[last].row_head[x];
		p=Cross[i].row_head[x]->right;
		for(y=0;y<Cross[last].n;y++){				//从第一列开始 
			sum.den=0;
			sum.mol=1;
			q=Cross[j].col_head[y]->down;
			while(p!=NULL && q!=NULL){				//算出相乘十字链表的每一项 
				if(p->col<q->row)
					p=p->right;
				else if(p->col>q->row)
					q=q->down;
				else{
					tem1=p->value.den*q->value.den;
					tem2=p->value.mol*q->value.mol;
					sum.den=sum.den*tem2+tem1*sum.mol;
					sum.mol=sum.mol*tem2;
					if((tem=gcd(sum.den,sum.mol))!=1){	
						sum.den=sum.den/tem;
						sum.mol=sum.mol/tem;
					}
					p=p->right;
					q=q->down;
				}
			} 
			if(sum.den!=0){
				len++;
				w=(OLNode *)malloc(sizeof(OLNode));
				w->row=x+1;
				w->col=y+1;
				w->value=sum;
				w->right=u->right;
				u->right=w;
				u=u->right;
				v=Cross[last].col_head[w->col-1];
				while(v->down!=NULL)
					v=v->down;
				w->down=v->down;
				v->down=w;
			}
		}	
	}
	Cross[last].len=len;
	PrintMatrix(last);
	last++;
}


void Transpose(){
	int i,j,max;
	char s[10];
	OLNode *p=NULL,*w,*u,*v;
	printf("请输入十字链表名称:");
	scanf("%s",s);
	for(i=0;i<last;i++){						//判断链表是否存在 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("十字链表不存在!\n");
		return ;
	}
	printf("请输入存储的十字链表名称:");
	scanf("%s",Cross[last].name);
	for(j=0;j<last;j++){						//判断链表是否存在 
		if(strcmp(Cross[j].name,Cross[last].name)==0){
			printf("该十字链表已存在!\n");
			return ;
		}
	}
	Distribute(Cross[i].m,Cross[i].n);
	for(j=0;j<Cross[i].m;j++){
		u=Cross[last].row_head[j];
		p=Cross[i].col_head[j]->down;
		while(p!=NULL){								//将行和列调换 
			w=(OLNode *)malloc(sizeof(OLNode));
			w->row=p->col;
			w->col=p->row;
			w->value=p->value;
			w->right=u->right;
			u->right=w;
			u=u->right;
			v=Cross[last].col_head[w->col-1];
			while(v->down!=NULL)
				v=v->down;
			w->down=v->down;
			v->down=w;
			p=p->down;
		}
	}
	Cross[last].len=Cross[i].len;
	PrintMatrix(last);
	last++;
	
}

void Memory(){
	int i,j;
	FILE *fp;
	OLNode node,*p=NULL;
	char s[10]; 
	printf("请输入十字链表名称:");
	scanf("%s",s);
	for(i=0;i<last;i++){					//判断链表是否存在 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("十字链表不存在!\n");
		return ;
	} 
	printf("请输入存储稀疏矩阵的文件名:");
	scanf("%s",s);
	if((fp=fopen(s,"wb"))==NULL){
		printf("不能打开文件!\n");
		return ; 				//对文件打不开的处理 
	}
	node.row=Cross[i].m;
	node.col=Cross[i].n;
	node.value.mol=1; 								
	node.value.den=Cross[i].len;
	fwrite(&node,sizeof(OLNode),1,fp);
	for(j=0;j<Cross[i].m;j++){					//从第一行开始遍历 写进文件 
		p=Cross[i].row_head[j]->right;
		while(p!=NULL){
			fwrite(p,sizeof(OLNode),1,fp);
			p=p->right;
		}
	}
	fclose(fp);
	PrintMatrix(i);
	printf("存储成功!\n");
}

void Maximun(){
	int i,j;
	DataType max,min;
	char s[10];
	OLNode *p=NULL;
	printf("请输入十字链表名称:");
	scanf("%s",s);
	for(i=0;i<last;i++){						//判断链表是否存在 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("十字链表不存在!\n");
		return ;
	}
	for(j=0;j<Cross[i].m;j++){					//找到第一个值 
		p=Cross[i].row_head[j]->right;
		if(p!=NULL)
			break;
	}
	max=p->value;
	min=max;
	for(j=0;j<Cross[i].m;j++){					//从第一行开始遍历  找最大最小值 
		p=Cross[i].row_head[j]->right;
		while(p!=NULL){										
			if(p->value.den/p->value.mol>max.den/max.mol)
				max=p->value;
			if(p->value.den/p->value.mol<min.den/min.mol)
				min=p->value;
			p=p->right;
		}
	}
	if(max.mol==1)														
		printf("max=%d ",max.den);
	else 
		printf("max=%d/%d",max.den,max.mol);
	if(min.mol==1)															
		printf("min=%d\n",min.den);
	else 
		printf("min=%d/%d\n",min.den,min.mol);
	 
}
void Determinant(){
	int i;
	DataType D;
	char s[10];			
	printf("请输入十字链表名称:");
	scanf("%s",s);
	for(i=0;i<last;i++){					//判断链表是否存在 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("十字链表不存在!\n");
		return ;
	}
	if(Cross[i].m!=Cross[i].n){					//判断链表是否存在行列式 
		printf("非矩阵，不能求行列式!\n");
		return ;
	}
	D=Determinant1(&Cross[i]);
	if(D.mol==1)
		printf("行列式:%d\n",D.den);
	else
		printf("行列式:%d/%d\n",D.den,D.mol);
}

void Inverse(){
	int i,j,k,len=0,tem;
	DataType D,sum;
	char s[10]; 
	OLNode *w=NULL,*u=NULL,*v=NULL;		
	printf("请输入十字链表名称:");
	scanf("%s",s);
	for(i=0;i<last;i++){				//判断链表是否存在 
		if(strcmp(Cross[i].name,s)==0)
			break;	
	}
	if(i==last){
		printf("十字链表不存在!\n");
		return ;
	}
	if(Cross[i].m!=Cross[i].n){			//判断链表是否存在行列式 
		printf("非矩阵，不能求行列式!\n");
		return ;
	}
	D=Determinant1(&Cross[i]);
	if(D.den==0){						//判断链表是否存在逆矩阵 
		printf("该矩阵没有逆矩阵!\n");
		return ;
	}
	printf("请输入存储的十字链表名称:");
	scanf("%s",Cross[last].name);
	for(j=0;j<last;j++){						//判断链表是否存在 
		if(strcmp(Cross[j].name,Cross[last].name)==0){
			printf("该十字链表已存在!\n");
			return ;
		}
	}
	Distribute(Cross[i].m,Cross[i].n);
	for(j=0;j<Cross[i].m;j++){
		u=Cross[last].row_head[j];
		for(k=1;k<=Cross[i].m;k++){				//从第一列开始遍历 
			sum=Determinant2(j,k,&Cross[i]);	//求逆矩阵每一项 并将每一项插入逆矩阵的十字链表 
			sum.den=sum.den*D.mol;
			sum.mol=sum.mol*D.den;
			if((tem=gcd(sum.den,sum.mol))!=1){	
				sum.den=sum.den/tem;
				sum.mol=sum.mol/tem;
			}
			if(sum.den!=0){
				w=(OLNode *)malloc(sizeof(OLNode));
				w->row=j+1;
				w->col=k;
				w->value=sum;
				len++;
				w->right=u->right;
				u->right=w;
				u=u->right;
				v=Cross[last].col_head[k-1];
				while(v->down!=NULL)
					v=v->down;
				w->down=v->down;
				v->down=w;
			}
		}
	}
	Cross[last].len=len;
	PrintMatrix(last);
	last++;
}

DataType Determinant1(CrossList *cross){		//利用交叉相乘再相减的原理 
	int j,k,tem1,tem2;
	DataType tem3,tem4;					
	DataType *a,*b;
	OLNode *p=NULL;
	a=(DataType *)malloc(sizeof(DataType)*cross->m);			
	b=(DataType *)malloc(sizeof(DataType)*cross->m);
	for(j=0;j<cross->m;j++){
		a[j].den=1;
		a[j].mol=1;
		b[j].den=1;
		b[j].mol=1;
	}
	for(j=0;j<cross->m;j++){
		p=cross->row_head[j]->right;
		for(k=1;k<=cross->m;k++){				//从第一列开始遍历 
			tem1=(k-j-1)%cross->m;				//寻找的规律 
			tem2=(k+j)%cross->m;
			if(tem1<0) 
				tem1=cross->m+tem1;
			if(p!=NULL && k==p->col){		
				a[tem1].den=a[tem1].den*p->value.den;				
				a[tem1].mol=a[tem1].mol*p->value.mol;
				b[tem1].den=b[tem1].den*p->value.den;
				b[tem1].mol=b[tem1].mol*p->value.mol;			
				p=p->right;
			}
			else{												
				a[tem1].den=0;
				b[tem2].den=0;
			}
		}
	}
	tem4.den=0;									
	tem4.mol=1;
	for(j=0;j<cross->m;j++){					//相减再相加 
		tem3.den=a[j].den*b[j].mol-b[j].den*a[j].mol;
		tem3.mol=a[j].mol*b[j].mol;
		tem4.den=tem3.den*tem4.mol+tem4.den*tem3.mol;
		tem4.mol=tem3.mol*tem4.mol;
	}
	free(a);
	free(b);
	return tem4;
}

DataType Determinant2(int x,int y,CrossList *cross){
	int j,k,m,n,tem1,tem2;	
	DataType tem3,tem4;				
	DataType *a,*b;
	OLNode *p=NULL;	 
	a=(DataType *)malloc(sizeof(DataType)*cross->m-1);		
	b=(DataType *)malloc(sizeof(DataType)*cross->m-1);
	for(j=0;j<cross->m-1;j++){
		a[j].den=1;
		a[j].mol=1;
		b[j].den=1;
		b[j].mol=1;
	}
	for(j=0;j<cross->m;j++){
		if(j==x)
			continue;
		else if(j>x)
			m=j-1;
		else
			m=j;
		p=cross->row_head[j]->right;
		for(k=1;k<=cross->m;k++){				//从第一列开始遍历 
			if(k==y)
				continue;
			else if(k>y)
				n=k-1;
			else
				n=k;
			tem1=(n-m-1)%cross->m;
			tem2=(n+m)%cross->m;
			if(tem1<0) 
				tem1=cross->m+tem1-1;
			if(p!=NULL && k==p->col){			
				a[tem1].den=a[tem1].den*p->value.den;					
				a[tem1].mol=a[tem1].mol*p->value.mol;
				b[tem2].den=b[tem2].den*p->value.den;
				b[tem2].mol=b[tem2].mol*p->value.mol;			
				p=p->right;
			}
			else{
				a[tem1].den=0;
				b[tem2].den=0;
			}
		}
	}
	tem4.den=0;										
	tem4.mol=1;
	for(j=0;j<cross->m-1;j++){
		tem3.den=a[j].den*b[j].mol-b[j].den*a[j].mol;
		tem3.mol=a[j].mol*b[j].mol;
		tem4.den=tem3.den*tem4.mol+tem4.den*tem3.mol;
		tem4.mol=tem3.mol*tem4.mol;
	}
	free(a);
	free(b);
	return tem4;
}
void Distribute(int m,int n){
	int i;
	Cross[last].m=m;
	Cross[last].n=n;
	Cross[last].row_head=(OLink *)malloc(sizeof(OLink)*Cross[last].m); 		//分配空间 
	for(i=0;i<Cross[last].m;i++) {
		Cross[last].row_head[i]=(OLNode *)malloc(sizeof(OLNode));
		Cross[last].row_head[i]->right=NULL;
	}
	Cross[last].col_head=(OLink *)malloc(sizeof(OLink)*Cross[last].n); 
	for(i=0;i<Cross[last].n;i++) {
		Cross[last].col_head[i]=(OLNode *)malloc(sizeof(OLNode));
		Cross[last].col_head[i]->down=NULL;
	}
}
int gcd(int a,int b){			//求最大公因数 
	if(b==0)
		return a;
	return gcd(b,a%b);
}
