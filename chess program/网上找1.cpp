#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include<string.h>
char qipan[10][9]={{'A','B','C','D','E','D','C','B','A'},{'+','+','+','+','+','+','+','+','+'},
{'+','F','+','+','+','+','+','F','+'},{'G','+','G','+','G','+','G','+','G'},
{'+','+','+','+','+','+','+','+','+'},{'+','+','+','+','+','+','+','+','+'},
{'g','+','g','+','g','+','g','+','g'},{'+','f','+','+','+','+','+','f','+'},
{'+','+','+','+','+','+','+','+','+'},{'a','b','c','d','e','d','c','b','a'}};
char a,b,c,d,e,k,f,g,A,B,C,D,E,F,G;
int i,j,m,n,q,x,y,flag,ret,loop;
int step=0;
char qipu[4][4];
char sigezi[4][4];
char hehe[4][4]={"这","下","完","了"};
int che(),ma(),xiang(),shi(),jiang(),bing(),pao();
static const char hanzi[32][4]={"车","马","炮","相","士","帅","兵","車","馬","砲","象","仕","将","卒","进","退","平","前","后","中","一","二","三","四","五","六","七","八","九","十","零"," "};
void**qipan_init()
{
 
 for(i=0;i<10;i++){
  printf("%4d",i);
  for(j=0;j<9;j++){
   switch(qipan[i][j]){
   case 'a':
    printf("%4s",hanzi[0]);break;
   case 'b':
    printf("%4s",hanzi[1]);break;
   case 'f':
    printf("%4s",hanzi[2]);break;
   case 'c':
    printf("%4s",hanzi[3]);break;
   case 'd':
    printf("%4s",hanzi[4]);break;
   case 'e':
    printf("%4s",hanzi[5]);break;
   case 'g':
    printf("%4s",hanzi[6]);break;
   case 'A':
    printf("%4s",hanzi[7]);break;
   case 'B':
    printf("%4s",hanzi[8]);break;
   case 'F':
    printf("%4s",hanzi[9]);break;
   case 'C':
    printf("%4s",hanzi[10]);break;
   case 'D':
    printf("%4s",hanzi[11]);break;
   case 'E':
    printf("%4s",hanzi[12]);break;
   case 'G':
    printf("%4s",hanzi[13]);break;
   case '+':
    printf("%4s",hanzi[31]);break;
  }
   if(j==8)
    printf("\n\n");
  }
 }
  printf("%4c   0   1   2   3   4   5   6   7   8\n",1);
  printf("\n");
  return (char**)qipan;
}
void print(int M,int N,int X,int Y)
{
 qipan[10][9];
 qipan[X][Y]=qipan[M][N];
 qipan[M][N]='+';
 for(i=0;i<10;i++){
  printf("%4d",i);
  for(j=0;j<9;j++){
   switch(qipan[i][j]){
   case 'a':
    printf("%4s",hanzi[0]);break;
   case 'b':
    printf("%4s",hanzi[1]);break;
   case 'f':
    printf("%4s",hanzi[2]);break;
   case 'c':
    printf("%4s",hanzi[3]);break;
   case 'd':
    printf("%4s",hanzi[4]);break;
   case 'e':
    printf("%4s",hanzi[5]);break;
   case 'g':
    printf("%4s",hanzi[6]);break;
   case 'A':
    printf("%4s",hanzi[7]);break;
   case 'B':
    printf("%4s",hanzi[8]);break;
   case 'F':
    printf("%4s",hanzi[9]);break;
   case 'C':
    printf("%4s",hanzi[10]);break;
   case 'D':
    printf("%4s",hanzi[11]);break;
   case 'E':
    printf("%4s",hanzi[12]);break;
   case 'G':
    printf("%4s",hanzi[13]);break;
   case '+':
    printf("%4s",hanzi[31]);break;
  }
   if(j==8)
    printf("\n\n");
  }
 }
  printf("%4c   0   1   2   3   4   5   6   7   8\n",1);
  printf("\n");
}
void zouzi_hou1()//车帅炮兵
{
 if(strcmp(sigezi[2],hanzi[14])==0){
  if(strcmp(sigezi[3],hanzi[20])==0){
   y=n;
   x=m-1;
  }
  else if(strcmp(sigezi[3],hanzi[21])==0){
   y=n;
   x=m-2;
  }
  else if(strcmp(sigezi[3],hanzi[22])==0){
   y=n;
   x=m-3;
  }
  else if(strcmp(sigezi[3],hanzi[23])==0){
   y=n;
   x=m-4;
  }
  else if(strcmp(sigezi[3],hanzi[24])==0){
   y=n;
   x=m-5;
  }
  else if(strcmp(sigezi[3],hanzi[25])==0){
   y=n;
   x=m-6;
  }
  else if(strcmp(sigezi[3],hanzi[26])==0){
   y=n;
   x=m-7;
  }
  else if(strcmp(sigezi[3],hanzi[27])==0){
   y=n;
   x=m-8;
  }
  else if(strcmp(sigezi[3],hanzi[28])==0){
   y=n;
   x=m-9;
  }
 }
 else if(strcmp(sigezi[2],hanzi[15])==0){
  if(strcmp(sigezi[3],hanzi[20])==0){
   y=n;
   x=m+1;
  }
  else if(strcmp(sigezi[3],hanzi[21])==0){
   y=n;
   x=m+2;
  }
  else if(strcmp(sigezi[3],hanzi[22])==0){
   y=n;
   x=m+3;
  }
  else if(strcmp(sigezi[3],hanzi[23])==0){
   y=n;
   x=m+4;
  }
  else if(strcmp(sigezi[3],hanzi[24])==0){
   y=n;
   x=m+5;
  }
  else if(strcmp(sigezi[3],hanzi[25])==0){
   y=n;
   x=m+6;
  }
  else if(strcmp(sigezi[3],hanzi[26])==0){
   y=n;
   x=m+7;
  }
  else if(strcmp(sigezi[3],hanzi[27])==0){
   y=n;
   x=m+8;
  }
  else if(strcmp(sigezi[3],hanzi[28])==0){
   y=n;
   x=m+9;
  }
 }
 else if(strcmp(sigezi[2],hanzi[16])==0){
  if(strcmp(sigezi[3],hanzi[20])==0){
   y=8;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[21])==0){
   y=7;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[22])==0){
   y=6;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[23])==0){
   y=5;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[24])==0){
   y=4;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[25])==0){
   y=3;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[26])==0){
   y=2;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[27])==0){
   y=1;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[28])==0){
   y=0;
   x=m;
  }
 }
}
void zouzi_hou2()//马
{
  if(strcmp(sigezi[3],hanzi[20])==0){
   y=8;
  }
  else if(strcmp(sigezi[3],hanzi[21])==0){
   y=7;
  }
  else if(strcmp(sigezi[3],hanzi[22])==0){
   y=6;
  }
  else if(strcmp(sigezi[3],hanzi[23])==0){
   y=5;
  }
  else if(strcmp(sigezi[3],hanzi[24])==0){
   y=4;
  }
  else if(strcmp(sigezi[3],hanzi[25])==0){
   y=3;
  }
  else if(strcmp(sigezi[3],hanzi[26])==0){
   y=2;
  }
  else if(strcmp(sigezi[3],hanzi[27])==0){
   y=1;
  }
  else if(strcmp(sigezi[3],hanzi[28])==0){
   y=0;
  }
 if(strcmp(sigezi[2],hanzi[14])==0){
  if(abs(n-y)==1)
    x=m-2;
  else if(abs(n-y)==2)
    x=m-1;
 }
 else if(strcmp(sigezi[2],hanzi[15])==0){
  if(abs(n-y)==1)
    x=m+2;
  else if(abs(n-y)==2)
    x=m+1;
 }
}
void zouzi_hou3()
{
  if(strcmp(sigezi[3],hanzi[20])==0){
   y=8;
  }
  else if(strcmp(sigezi[3],hanzi[21])==0){
   y=7;
  }
  else if(strcmp(sigezi[3],hanzi[22])==0){
   y=6;
  }
  else if(strcmp(sigezi[3],hanzi[23])==0){
   y=5;
  }
  else if(strcmp(sigezi[3],hanzi[24])==0){
   y=4;
  }
  else if(strcmp(sigezi[3],hanzi[25])==0){
   y=3;
  }
  else if(strcmp(sigezi[3],hanzi[26])==0){
   y=2;
  }
  else if(strcmp(sigezi[3],hanzi[27])==0){
   y=1;
  }
  else if(strcmp(sigezi[3],hanzi[28])==0){
   y=0;
  }
 if(strcmp(sigezi[2],hanzi[14])==0){
   x=m-2;
 }
 else if(strcmp(sigezi[2],hanzi[15])==0){
   x=m+2;
 }
}
void zouzi_hou4()
{
  if(strcmp(sigezi[3],hanzi[20])==0){
   y=8;
  }
  else if(strcmp(sigezi[3],hanzi[21])==0){
   y=7;
  }
  else if(strcmp(sigezi[3],hanzi[22])==0){
   y=6;
  }
  else if(strcmp(sigezi[3],hanzi[23])==0){
   y=5;
  }
  else if(strcmp(sigezi[3],hanzi[24])==0){
   y=4;
  }
  else if(strcmp(sigezi[3],hanzi[25])==0){
   y=3;
  }
  else if(strcmp(sigezi[3],hanzi[26])==0){
   y=2;
  }
  else if(strcmp(sigezi[3],hanzi[27])==0){
   y=1;
  }
  else if(strcmp(sigezi[3],hanzi[28])==0){
   y=0;
  }
 if(strcmp(sigezi[2],hanzi[14])==0){
   x=m-1;
 }
 else if(strcmp(sigezi[2],hanzi[15])==0){
   x=m+1;
 }
}
void zouzi_qian()
{
  int w;
  w=0;
   if(strcmp(sigezi[1],hanzi[20])==0)
    n=8;
   else if(strcmp(sigezi[1],hanzi[21])==0)
    n=7;
   else if(strcmp(sigezi[1],hanzi[22])==0)
    n=6;
   else if(strcmp(sigezi[1],hanzi[23])==0)
    n=5;
   else if(strcmp(sigezi[1],hanzi[24])==0)
    n=4;
   else if(strcmp(sigezi[1],hanzi[25])==0)
    n=3;
   else if(strcmp(sigezi[1],hanzi[26])==0)
    n=2;
   else if(strcmp(sigezi[1],hanzi[27])==0)
    n=1;
   else if(strcmp(sigezi[1],hanzi[28])==0)
    n=0;
  {
   if(strcmp(sigezi[0],hanzi[0])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='a')
      break;
     }
    m=q;
    zouzi_hou1();
   }
   else if(strcmp(sigezi[0],hanzi[1])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='b')
      break;
     }
    m=q;
    zouzi_hou2();
   }
   else if(strcmp(sigezi[0],hanzi[2])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='f')
      break;
     }
    m=q;
    zouzi_hou1();
   }
   else if(strcmp(sigezi[0],hanzi[3])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='c')
      break;
     }
    m=q;
    zouzi_hou3();
   }
   else if(strcmp(sigezi[0],hanzi[4])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='d')
      break;
     }
    m=q;
    zouzi_hou4();
   }
   else if(strcmp(sigezi[0],hanzi[5])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='e')
      break;
     }
    m=q;
    zouzi_hou1();
   }
   else if(strcmp(sigezi[0],hanzi[6])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='g')
      break;
     }
    m=q;
    zouzi_hou1();
   }
  }
  if(strcmp(sigezi[1],hanzi[0])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='a'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='a'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   zouzi_hou1();
  }
  else if(strcmp(sigezi[1],hanzi[1])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='b'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='b'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   zouzi_hou2();
  }
  else if(strcmp(sigezi[1],hanzi[2])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='f'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='f'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   zouzi_hou1();
  }
  else if(strcmp(sigezi[1],hanzi[3])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='c'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='c'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   zouzi_hou3();
  }
  else if(strcmp(sigezi[1],hanzi[4])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='d'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='d'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   zouzi_hou4();
  }
  else if(strcmp(sigezi[1],hanzi[5])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='e'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='e'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   zouzi_hou1();
  }
  else if(strcmp(sigezi[1],hanzi[6])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='g'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='g'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   zouzi_hou1();
  }
}
void duilian()
{
 int w;
 for(i=0;i<10;i++)
  for(j=0;j<9;j++){
   if(qipan[i][j]=='E')
    for(w=1;w<10;w++){
     if(qipan[i+w][j]!='+'){
      if(qipan[i+w][j]=='e'){
       if(step%2==0){
        printf("老将对脸啦！小黑胜利！！\n");
        for(;;)
          getchar();
       }
       else if(step%2==1){
        printf("老将对脸啦！小红胜利！！\n");
        for(;;)
          getchar();
       }
      }
      else
       break;
     }
    }
  }
}

void hzouzi_hou1()//黑車将砲卒
{
 if(strcmp(sigezi[2],hanzi[14])==0){
  if(strcmp(sigezi[3],hanzi[20])==0){
   y=n;
   x=m+1;
  }
  else if(strcmp(sigezi[3],hanzi[21])==0){
   y=n;
   x=m+2;
  }
  else if(strcmp(sigezi[3],hanzi[22])==0){
   y=n;
   x=m+3;
  }
  else if(strcmp(sigezi[3],hanzi[23])==0){
   y=n;
   x=m+4;
  }
  else if(strcmp(sigezi[3],hanzi[24])==0){
   y=n;
   x=m+5;
  }
  else if(strcmp(sigezi[3],hanzi[25])==0){
   y=n;
   x=m+6;
  }
  else if(strcmp(sigezi[3],hanzi[26])==0){
   y=n;
   x=m+7;
  }
  else if(strcmp(sigezi[3],hanzi[27])==0){
   y=n;
   x=m+8;
  }
  else if(strcmp(sigezi[3],hanzi[28])==0){
   y=n;
   x=m+9;
  }
 }
 else if(strcmp(sigezi[2],hanzi[15])==0){
  if(strcmp(sigezi[3],hanzi[20])==0){
   y=n;
   x=m-1;
  }
  else if(strcmp(sigezi[3],hanzi[21])==0){
   y=n;
   x=m-2;
  }
  else if(strcmp(sigezi[3],hanzi[22])==0){
   y=n;
   x=m-3;
  }
  else if(strcmp(sigezi[3],hanzi[23])==0){
   y=n;
   x=m-4;
  }
  else if(strcmp(sigezi[3],hanzi[24])==0){
   y=n;
   x=m-5;
  }
  else if(strcmp(sigezi[3],hanzi[25])==0){
   y=n;
   x=m-6;
  }
  else if(strcmp(sigezi[3],hanzi[26])==0){
   y=n;
   x=m-7;
  }
  else if(strcmp(sigezi[3],hanzi[27])==0){
   y=n;
   x=m-8;
  }
  else if(strcmp(sigezi[3],hanzi[28])==0){
   y=n;
   x=m-9;
  }
 }
 else if(strcmp(sigezi[2],hanzi[16])==0){
  if(strcmp(sigezi[3],hanzi[20])==0){
   y=0;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[21])==0){
   y=1;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[22])==0){
   y=2;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[23])==0){
   y=3;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[24])==0){
   y=4;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[25])==0){
   y=5;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[26])==0){
   y=6;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[27])==0){
   y=7;
   x=m;
  }
  else if(strcmp(sigezi[3],hanzi[28])==0){
   y=8;
   x=m;
  }
 }
}
void hzouzi_hou2()//黑馬
{
  if(strcmp(sigezi[3],hanzi[20])==0){
   y=0;
  }
  else if(strcmp(sigezi[3],hanzi[21])==0){
   y=1;
  }
  else if(strcmp(sigezi[3],hanzi[22])==0){
   y=2;
  }
  else if(strcmp(sigezi[3],hanzi[23])==0){
   y=3;
  }
  else if(strcmp(sigezi[3],hanzi[24])==0){
   y=4;
  }
  else if(strcmp(sigezi[3],hanzi[25])==0){
   y=5;
  }
  else if(strcmp(sigezi[3],hanzi[26])==0){
   y=6;
  }
  else if(strcmp(sigezi[3],hanzi[27])==0){
   y=7;
  }
  else if(strcmp(sigezi[3],hanzi[28])==0){
   y=8;
  }
 if(strcmp(sigezi[2],hanzi[14])==0){
  if(abs(n-y)==1)
    x=m+2;
  else if(abs(n-y)==2)
    x=m+1;
 }
 else if(strcmp(sigezi[2],hanzi[15])==0){
  if(abs(n-y)==1)
    x=m-2;
  else if(abs(n-y)==2)
    x=m-1;
 }
}
void hzouzi_hou3()//黑相
{
  if(strcmp(sigezi[3],hanzi[20])==0){
   y=0;
  }
  else if(strcmp(sigezi[3],hanzi[21])==0){
   y=1;
  }
  else if(strcmp(sigezi[3],hanzi[22])==0){
   y=2;
  }
  else if(strcmp(sigezi[3],hanzi[23])==0){
   y=3;
  }
  else if(strcmp(sigezi[3],hanzi[24])==0){
   y=4;
  }
  else if(strcmp(sigezi[3],hanzi[25])==0){
   y=5;
  }
  else if(strcmp(sigezi[3],hanzi[26])==0){
   y=6;
  }
  else if(strcmp(sigezi[3],hanzi[27])==0){
   y=7;
  }
  else if(strcmp(sigezi[3],hanzi[28])==0){
   y=8;
  }
 if(strcmp(sigezi[2],hanzi[14])==0){
   x=m+2;
 }
 else if(strcmp(sigezi[2],hanzi[15])==0){
   x=m-2;
 }
}
void hzouzi_hou4()//黑仕
{
  if(strcmp(sigezi[3],hanzi[20])==0){
   y=0;
  }
  else if(strcmp(sigezi[3],hanzi[21])==0){
   y=1;
  }
  else if(strcmp(sigezi[3],hanzi[22])==0){
   y=2;
  }
  else if(strcmp(sigezi[3],hanzi[23])==0){
   y=3;
  }
  else if(strcmp(sigezi[3],hanzi[24])==0){
   y=4;
  }
  else if(strcmp(sigezi[3],hanzi[25])==0){
   y=5;
  }
  else if(strcmp(sigezi[3],hanzi[26])==0){
   y=6;
  }
  else if(strcmp(sigezi[3],hanzi[27])==0){
   y=7;
  }
  else if(strcmp(sigezi[3],hanzi[28])==0){
   y=8;
  }
 if(strcmp(sigezi[2],hanzi[14])==0){
   x=m+1;
 }
 else if(strcmp(sigezi[2],hanzi[15])==0){
   x=m-1;
 }
}void hzouzi_qian()
{
  int w;
  w=0;
   if(strcmp(sigezi[1],hanzi[20])==0)
    n=0;
   else if(strcmp(sigezi[1],hanzi[21])==0)
    n=1;
   else if(strcmp(sigezi[1],hanzi[22])==0)
    n=2;
   else if(strcmp(sigezi[1],hanzi[23])==0)
    n=3;
   else if(strcmp(sigezi[1],hanzi[24])==0)
    n=4;
   else if(strcmp(sigezi[1],hanzi[25])==0)
    n=5;
   else if(strcmp(sigezi[1],hanzi[26])==0)
    n=6;
   else if(strcmp(sigezi[1],hanzi[27])==0)
    n=7;
   else if(strcmp(sigezi[1],hanzi[28])==0)
    n=8;
  {
   if(strcmp(sigezi[0],hanzi[7])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='A')
      break;
     }
    m=q;
    hzouzi_hou1();
   }
   else if(strcmp(sigezi[0],hanzi[8])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='B')
      break;
     }
    m=q;
    hzouzi_hou2();
   }
   else if(strcmp(sigezi[0],hanzi[9])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='F')
      break;
     }
    m=q;
    hzouzi_hou1();
   }
   else if(strcmp(sigezi[0],hanzi[10])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='C')
      break;
     }
    m=q;
    hzouzi_hou3();
   }
   else if(strcmp(sigezi[0],hanzi[11])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='D')
      break;
     }
    m=q;
    hzouzi_hou4();
   }
   else if(strcmp(sigezi[0],hanzi[12])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='E')
      break;
     }
    m=q;
    hzouzi_hou1();
   }
   else if(strcmp(sigezi[0],hanzi[13])==0){
    for(q=0;q<10;q++){
     if(qipan[q][n]=='G')
      break;
     }
    m=q;
    hzouzi_hou1();
   }
  }
  if(strcmp(sigezi[1],hanzi[7])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='A'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='A'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   hzouzi_hou1();
  }
  else if(strcmp(sigezi[1],hanzi[8])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='B'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='B'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   hzouzi_hou2();
  }
  else if(strcmp(sigezi[1],hanzi[9])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='F'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='F'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   hzouzi_hou1();
  }
  else if(strcmp(sigezi[1],hanzi[10])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='C'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='C'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   hzouzi_hou3();
  }
  else if(strcmp(sigezi[1],hanzi[11])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='D'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='D'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   hzouzi_hou4();
  }
  else if(strcmp(sigezi[1],hanzi[12])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='E'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='E'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   hzouzi_hou1();
  }
  else if(strcmp(sigezi[1],hanzi[13])==0){
   if(strcmp(sigezi[0],hanzi[17])==0){
    for(i=9;i>=0;i--){
     for(j=8;j>=0;j--){
      if(qipan[i][j]=='G'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   else if(strcmp(sigezi[0],hanzi[18])==0){
    for(i=0;i<10;i++){
     for(j=0;j<9;j++){
      if(qipan[i][j]=='G'){
       w=1;
       break;
      }
     }
     if(w==1){
      n=j;
      m=i;
      break;
     }
    }
   }
   hzouzi_hou1();
  }
}

void hong()
 {
  char buf[100];
  int pos;
  char *s=buf;
   printf("瞅啥呢？小红走子啊：");
   fflush(stdin);
   fgets(buf,100,stdin);
  if(sscanf(s,"%d%d%d%d",&n,&m,&y,&x)==4)
   printf("输入的是坐标！\n");
  else{
   for(loop=0;loop<4;loop++){
    if(sscanf(s,"%2s%n",qipu[loop], &pos) != 1) { 
     return;
    }
    s+=pos;
    strcpy(sigezi[loop],hehe[loop]);
     for(k=0;k<32;k++){
      if(strcmp(hanzi[k],qipu[loop])==0){
       strcpy(sigezi[loop],hanzi[k]);
       break;
      }
     }
   }
   zouzi_qian();
  }
   flag=0;
   if((m<10)&&(m>=0)&&(n<9)&&(n>=0)&&(x<10)&&(x>=0)&&(y<9)&&(y>=0)){
    switch(qipan[m][n]){
     case'a':
      che(m,n,x,y);flag=che(m,n,x,y);break;
     case'b':
      ma(m,n,x,y);flag=ma(m,n,x,y);break;
     case'c':
      xiang(m,n,x,y);flag=xiang(m,n,x,y);break;
     case'd':
      shi(m,n,x,y);flag=shi(m,n,x,y);break;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
     case'e':
      jiang(m,n,x,y);flag=jiang(m,n,x,y);break;
     case'f':
      pao(m,n,x,y);flag=pao(m,n,x,y);break;
     case'g':
      bing(m,n,x,y);flag=bing(m,n,x,y);break;;
     default:flag=0;printf("傻啊？走错子啦！\n");
     }
   }
   if(qipan[x][y]!='a'&&qipan[x][y]!='b'&&qipan[x][y]!='c'&&qipan[x][y]!='d'&&qipan[x][y]!='e'&&qipan[x][y]!='f'&&qipan[x][y]!='g'){
      if(flag==1){
        if(qipan[x][y]=='E'){
         printf("恭喜大美女小红打败傻冒小黑\n游戏结束\n");
         print(m,n,x,y);
         for(;;)
          getchar();
        }
        print(m,n,x,y); 
        duilian();
        step++;
       }
     }
    else 
     printf("是不是傻？走错啦！重新走\n");
}
void hei()
{
 char buf[100];
  int pos;
  char *s=buf;
   printf("别瞅啦！小黑快走子：");
    fflush(stdin);
    fgets(buf,100,stdin);
  if(sscanf(s,"%d%d%d%d",&n,&m,&y,&x)==4)
   printf("输入的是坐标！\n");
  else{
   for(loop=0;loop<4;loop++){
    if(sscanf(s,"%2s%n",qipu[loop], &pos) != 1) {
     return;
    }
    s+=pos;
    strcpy(sigezi[loop],hehe[loop]);
    for(k=0;k<32;k++){
     if(strcmp(hanzi[k],qipu[loop])==0){
      strcpy(sigezi[loop],hanzi[k]);
      break;
     }
    }
   }
   hzouzi_qian();
  }
   flag=0;
   if((m<10)&&(m>=0)&&(n<9)&&(n>=0)&&(x<10)&&(x>=0)&&(y<9)&&(y>=0)){
    switch(qipan[m][n]){
     case'A':
      che(m,n,x,y);flag=che(m,n,x,y);break;
     case'B':
      ma(m,n,x,y);flag=ma(m,n,x,y);break;
     case'C':
      xiang(m,n,x,y);flag=xiang(m,n,x,y);break;
     case'D':
      shi(m,n,x,y);flag=shi(m,n,x,y);break;
     case'E':
      jiang(m,n,x,y);flag=jiang(m,n,x,y);break;
     case'F':
      pao(m,n,x,y);flag=pao(m,n,x,y);break;
     case'G':
      bing(m,n,x,y);flag=bing(m,n,x,y);break;
     default:flag=0;printf("傻啊？走错子啦！\n");
     }
    if(qipan[x][y]!='A'&&qipan[x][y]!='B'&&qipan[x][y]!='C'&&qipan[x][y]!='D'&&qipan[x][y]!='E'&&qipan[x][y]!='F'&&qipan[x][y]!='G'){
     if(flag==1){
      if(qipan[x][y]=='e'){
       printf("恭喜颜值王小黑打败傻冒小红\n游戏结束\n");
       print(m,n,x,y);
       for(;;)
        getchar();
      }
      print(m,n,x,y);
      duilian();
      step++;
     }
    }
   }
   else
    printf("是不是傻？走错啦！重新走\n");
}
int main()
{
 printf("      中国象棋   \n    作者——NORMAN\n\n\n");
 qipan_init();
 for(;;){
  for(;step%2==0;){
  hong();
  }
  for(;step%2==1;){
  hei();
  }
 }
}
int che(int M,int N,int X,int Y)
{
 int u,v;
 if(M==X){
  if(N>Y)
   ret=0;
  else if(N<Y)
   ret=1;
  for(v=1;v<abs(N-Y);v++){
   switch(ret){
   case 0:
    if(qipan[M][Y+v]!='+')
     return 0;break;
   case 1:
    if(qipan[M][Y-v]!='+')
     return 0;break;
   }
  }
 }
 else if(N==Y){
  if(M>X)
   ret=0;
  else if(M<X)
   ret=1;
  for(u=1;u<abs(M-X);u++){
   switch(ret){
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
 
 if(abs(X-M)==1&&abs(Y-N)==2){
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
 else if(abs(X-M)==2&&abs(Y-N)==1){
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
 return 1;
}
int xiang(int M,int N,int X,int Y)
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
 if(step%2==0&&x>4||step%2==1&&x<5){
  if(abs(X-M)==2&&abs(Y-N)==2){
    switch(ret){
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
int shi(int M,int N,int X,int Y)
{
 if(step%2==0&&X>6&&Y<6&&Y>2||step%2==1&&X<3&&Y<6&&Y>2){
  if(abs(X-M)==1&&abs(Y-N)==1)
   return 1;
 }
 return 0;
}
int jiang(int M,int N,int X,int Y)
{
 if(step%2==0&&X>6&&Y<6&&Y>2||step%2==1&&X<3&&Y<6&&Y>2){
  if(abs(X-M)==1||abs(Y-N)==1){
   if(abs(X-M)!=abs(Y-N))
    return 1;
  }
 }
 return 0;
}
int bing(int M,int N,int X,int Y)
{
 if(M>4){
  if(step%2==0&&X==M-1&&N==Y||step%2==1&&X==M+1&&N==Y||step%2==1&&X==M&&N==Y-1||step%2==1&&X==M&&N==Y+1)
   return 1;
  else
   return 0;
 }
 else if(M<5){
  if(step%2==0&&X==M-1&&N==Y||step%2==0&&X==M&&N==Y-1||step%2==0&&X==M&&N==Y+1||step%2==1&&X==M+1&&N==Y)
   return 1;
  else
   return 0;
 }
}
int pao(int M,int N,int X,int Y)
{
 if(qipan[X][Y]=='+')
  che(M,N,X,Y);
 else if(qipan[X][Y]!='+'){
  int z;
  int u,v;
  if(M==X){
   if(N>Y){
    z=0;
    for(v=1;v<abs(N-Y);v++){
     if(qipan[M][Y+v]!='+')
      z++;
    }
    if(z==1)
     return 1;
    else
     return 0;
   }
   if(N<Y){
    z=0;
    for(v=1;v<abs(N-Y);v++){
     if(qipan[M][Y-v]!='+')
      z++;
    }
    if(z==1)
     return 1;
    else
     return 0;
   }
  }
  else if(Y==N){
   if(M>X){
    z=0;
    for(u=1;u<abs(M-X);u++){
     if(qipan[X+u][N]!='+')
      z++;
    }
    if(z==1)
     return 1;
    else
     return 0;
   }
   if(M<X){
    z=0;
    for(u=1;u<abs(M-X);u++){
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
