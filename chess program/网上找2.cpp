
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define 车 a
#define 马 b
#define 相 c
#define 士 d
#define 帅 e
#define 炮 f
#define 兵 g
#define 車 A
#define 馬 B
#define 象 C
#define 仕 D
#define 将 E
#define 泡 F
#define 卒 G
int i,j;
char a,b,c,d,e,f,g,A,B,C,D,E,F,G;
int m,n,x,y,flag,ret;
int step=0;
int che();
int ma();
int hongxiang();
int heixiang();
int hongshi();
int heishi();
int shuai();
int jiang();
int bing();
int zu();
int pao();
char qipan[10][9]={{'A','B','C','D','E','D','C','B','A'},{'+','+','+','+','+','+','+','+','+'},{'+','F','+','+','+','+','+','F','+'},{'G','+','G','+','G','+','G','+','G'},{'+','+','+','+','+','+','+','+','+'},{'+','+','+','+','+','+','+','+','+'},{'g','+','g','+','g','+','g','+','g'},{'+','f','+','+','+','+','+','f','+'},{'+','+','+','+','+','+','+','+','+'},{'a','b','c','d','e','d','c','b','a'}};
char** qipan_init()
{
 
	for(i=0;i<10;i++)
	{	printf("%4d",i);
		for(j=0;j<9;j++)
			printf("%4c",qipan[i][j]);
			printf("\n\n");
	}
	printf("%4c   0   1   2   3   4   5   6   7   8\n",1);
	return (char**)qipan;
}
void print(int M,int N,int X,int Y)
{
	qipan[10][9];
	qipan[X][Y]=qipan[M][N];
	qipan[M][N]='+';
	for(i=0;i<10;i++)
	{	
		printf("%4d",i);
		for(j=0;j<9;j++)
			printf("%4c",qipan[i][j]);
		printf("\n\n");
	}
	printf("%4c   0   1   2   3   4   5   6   7   8\n",1);
}
void duilian()
{
	int w;
	for(i=0;i<10;i++)
		for(j=0;j<9;j++)
		{
			if(qipan[i][j]=='E')
				for(w=1;w<10;w++)
				{
					if(qipan[i+w][j]!='+')
					{
						if(qipan[i+w][j]=='e')
						{
							if(step%2==0)
							{
								printf("老将对脸啦！黑方胜利！！\n");
								exit(0);
							}
							else if(step%2==1)
							{
								printf("老将对脸啦！红方胜利！！\n");
								exit(0);
							}
						}
						else
							break;
					}
				}
		}
}
int main()
{ 
	qipan_init();
	for(;;)
	{
		do
		{
			printf("请红方走子：");
			scanf("%d%d%d%d",&m,&n,&x,&y);
			if((m<10)&&(m>=0)&&(n<9)&&(n>=0)&&(x<10)&&(x>=0)&&(y<9)&&(y>=0))
			{	flag=0;
				switch(qipan[m][n])
					{
					case'a': 
						che(m,n,x,y);flag=che(m,n,x,y);
						break;
					case'b':
						ma(m,n,x,y);flag=ma(m,n,x,y);
						break;
					case'c':
						hongxiang(m,n,x,y);flag=hongxiang(m,n,x,y);
						break;
					case'd':
						hongshi(m,n,x,y);flag=hongshi(m,n,x,y);
						break;
					case'e':
						shuai(m,n,x,y);flag=shuai(m,n,x,y);
						break;
					case'f':
						pao(m,n,x,y);flag=pao(m,n,x,y);
						break;
					case'g':
						bing(m,n,x,y);flag=bing(m,n,x,y);
						break;;
					default:flag=0;printf("走错子啦！\n");
					}
			}
				if(qipan[x][y]!='a'&&qipan[x][y]!='b'&&qipan[x][y]!='c'&&qipan[x][y]!='d'&&qipan[x][y]!='e'&&qipan[x][y]!='f'&&qipan[x][y]!='g')
					{
						if(flag==1)
							{
								if(qipan[x][y]=='E')
								{
									printf("恭喜红方获得胜利\n游戏结束\n");
									print(m,n,x,y);
									exit(0);
								}
								print(m,n,x,y);
								duilian();
								step++;
							}
					}
				else  
					printf("走错啦，重新走\n");
			}while (step%2==0);
		do{
			printf("请黑方走子：");
			scanf("%d%d%d%d",&m,&n,&x,&y);
			if((m<10)&&(m>=0)&&(n<9)&&(n>=0)&&(x<10)&&(x>=0)&&(y<9)&&(y>=0))
			{
				switch(qipan[m][n])
					{
					case'A':
						che(m,n,x,y);flag=che(m,n,x,y);
						break;
					case'B':
						ma(m,n,x,y);flag=ma(m,n,x,y);
						break;
					case'C':
						heixiang(m,n,x,y);flag=heixiang(m,n,x,y);
						break;
					case'D':
						heishi(m,n,x,y);flag=heishi(m,n,x,y);
						break;
					case'E':
						jiang(m,n,x,y);flag=jiang(m,n,x,y);
						break;
					case'F':
						pao(m,n,x,y);flag=pao(m,n,x,y);
						break;
					case'G':
						zu(m,n,x,y);flag=zu(m,n,x,y);
						break;
					default:flag=0;printf("走错子啦！\n");
					}
				if(qipan[x][y]!='A'&&qipan[x][y]!='B'&&qipan[x][y]!='C'&&qipan[x][y]!='D'&&qipan[x][y]!='E'&&qipan[x][y]!='F'&&qipan[x][y]!='G')
				{
					if(flag==1)
					{
						if(qipan[x][y]=='e')
						{
							printf("恭喜黑方获得胜利\n游戏结束\n");
							print(m,n,x,y);
							exit(0);
						}
						print(m,n,x,y);
						duilian();
						step++;
					}
				}
			}
			else
				printf("走错啦!重新走\n");
		}while(step%2==1);
	}
} 
int che(int M,int N,int X,int Y)
{
	int u,v;
	if(M==X)
	{
		if(N>Y)
			ret=0;
		else if(N<Y)
			ret=1;
		for(v=1;v<abs(N-Y);v++)
		{
			switch(ret)
			{
			case 0:
				if(qipan[M][Y+v]!='+')
					return 0;break;
			case 1:
				if(qipan[M][Y-v]!='+')
					return 0;break;
			}
		}
	}
	else if(N==Y)
	{
		if(M>X)
			ret=0;
		else if(M<X)
			ret=1;
		for(u=1;u<abs(M-X);u++)
		{
			switch(ret)
			{
			case 0:
			if(qipan[X+u][N]!='+')
				return 0;break;
			case 1:
			if(qipan[X-u][N]!='+')
				return 0;break;
			}
		}
	}
	else if(M!=X&&N!=Y)
		return 0;
	return 1;
}
int ma(int M,int N,int X,int Y)
{
	{
		if(X>M&&Y>N)
			ret=0;
		else if(X>M&&Y<N)
			ret=1;
		else if(X<M&&Y>N)
			ret=2;
		else if(X<M&&Y<N)
			ret=3;
	}
	{
	if(abs(X-M)==1&&abs(Y-N)==2)
	{
	switch(ret)
	{
		case 0:
		case 2:
			if(qipan[M][N+1]!='+')
				return 0;break;
		case 1:
		case 3:
			if(qipan[M][N-1]!='+')
				return 0;break;
	}
	}
	else if(abs(X-M)==2&&abs(Y-N)==1)
	{
		switch(ret)
		{
			case 0:
			case 1:
				if(qipan[M+1][N]!='+')
					return 0;break;
			case 2:
			case 3:
				if(qipan[M-1][N]!='+')
					return 0;break;
		}
	}
	else
		return 0;
	}
	return 1;
}
int hongxiang(int M,int N,int X,int Y)
{
	{
		if(X>M&&Y>N)
			ret=0;
		else if(X>M&&Y<N)
			ret=1;
		else if(X<M&&Y>N)
			ret=2;
		else if(X<M&&Y<N)
			ret=3;
	}
	if(abs(X-M)==2&&abs(Y-N)==2)
	{
		if(X>4)
		{
			switch(ret)
			{
			case 0:
				if(qipan[M+1][N+1]!='+')
					return 0;break;
			case 1:
				if(qipan[M+1][N-1]!='+')
					return 0;break;
			case 2:
				if(qipan[M-1][N+1]!='+')
					return 0;break;
			case 3:
				if(qipan[M-1][N-1]!='+')
					return 0;break;
			}
		}
		else
			return 0;
	}
	else 
		return 0;
	return 1;
}
int heixiang(int M,int N,int X,int Y)
{
	{
		if(X>M&&Y>N)
			ret=0;
		else if(X>M&&Y<N)
			ret=1;
		else if(X<M&&Y>N)
			ret=2;
		else if(X<M&&Y<N)
			ret=3;
	}
	if(abs(X-M)==2&&abs(Y-N)==2)
	{
		if(X<5)
		{
			switch(ret)
			{
			case 0:
				if(qipan[M+1][N+1]!='+')
					return 0;break;
			case 1:
				if(qipan[M+1][N-1]!='+')
					return 0;break;
			case 2:
				if(qipan[M-1][N+1]!='+')
					return 0;break;
			case 3:
				if(qipan[M-1][N-1]!='+')
					return 0;break;
			}
		}
		else
			return 0;
	}
	else 
		return 0;
	return 1;
}
int hongshi(int M,int N,int X,int Y)
{
	if(X>6&&Y<6&&Y>2)
	{
		if(abs(X-M)==1&&abs(Y-N)==1)
			return 1;
	}
	return 0;
}
int heishi(int M,int N,int X,int Y)
{
	if(X<3&&Y<6&&Y>2)
	{
		if(abs(X-M)==1&&abs(Y-N)==1)
			return 1;
	}
	return 0;
}
int shuai(int M,int N,int X,int Y)
{
	if(X>6&&Y<6&&Y>2)
	{
		if(abs(X-M)==1||abs(Y-N)==1)
		{
			if(abs(X-M)!=abs(Y-N))
				return 1;
		}
	}
	return 0;
}
int jiang(int M,int N,int X,int Y)
{
	if(X<3&&Y<6&&Y>2)
	{
		if(abs(X-M)==1||abs(Y-N)==1)
		{
			if(abs(X-M)!=abs(Y-N))
				return 1;
		}
	}
	return 0;
}
int bing(int M,int N,int X,int Y)
{
	if(M>4)
	{
		if(X==M-1&&N==Y)
			return 1;
		else 
			return 0;
	}
	if(M<5)
	{
		if(X==M-1&&N==Y)
			return 1;
		else if(X==M&&N==Y-1)
			return 1;
		else if(X==M&&N==Y+1)
			return 1;
		else
			return 0;
	}
}
int zu(int M,int N,int X,int Y)
{
	if(M<5)
	{
		if(X==M+1&&N==Y)
			return 1;
		else
			return 0;
	}
	if(M>4)
	{
		if(X==M+1&&N==Y)
			return 1;
		else if(X==M&&N==Y-1)
			return 1;
		else if(X==M&&N==Y+1)
			return 1;
		else
			return 0;
	}
}
int pao(int M,int N,int X,int Y)
{
	if(qipan[X][Y]=='+')
		che(M,N,X,Y);
	else if(qipan[X][Y]!='+')
	{
		int z;
		int u,v;
		if(M==X)
		{
			if(N>Y)
			{
				z=0;
				for(v=1;v<abs(N-Y);v++)
				{
					if(qipan[M][Y+v]!='+')
						z++;
				}
				if(z==1)
					return 1;
				else
					return 0;
			}
			if(N<Y)
			{
				z=0;
				for(v=1;v<abs(N-Y);v++)
				{
					if(qipan[M][Y-v]!='+')
						z++;
				}
				if(z==1)
					return 1;
				else
					return 0;
			}
		}
		else if(Y==N)
		{
			if(M>X)
			{
				z=0;
				for(u=1;u<abs(M-X);u++)
				{
					if(qipan[X+u][N]!='+')
						z++;
				}
				if(z==1)
					return 1;
				else
					return 0;
			}
			if(M<X)
			{
				z=0;
				for(u=1;u<abs(M-X);u++)
				{
					if(qipan[X-u][N]!='+')
						z++;
				}
				if(z==1)
					return 1;
				else
					return 0;
			}
		}
		else
			return 0;
 
	}
}

