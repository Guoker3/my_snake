#include<stdio.h>       //��׼�������  
#include<stdlib.h>      //��׼�⺯�� 
#include<conio.h>		//����̨������� 
#include<windows.h>		//����windows�Ŀ��� 
#include<time.h>

#define height 20
#define width 30 

int canvas[height][width]={0};      //ȫ�ֱ���
int foodx,foody;
int demonx,demony,demonnumber;
int movedirection,taildirection;                  //1��3��4��2�� 
int oldtaili,oldtailj,newheadi,newheadj;
int ray=0,snakelength=5,lifenumber=0;				//���� ,�߳��� 


void playagain()					//���¿�ʼ 
{
	int confirm,flag=1;
	system("pause");
	system("cls");
	Sleep(2000);
	printf("input r to get another entirely brandly new life\n");
	while(flag)
	{
		int i,j; 
		scanf("%c",&confirm);
		setbuf(stdin,NULL); 
		if(confirm=='r'||confirm=='R')
		{
			if((lifenumber++)%2==1)            //������ 
			{
				for(i=0;i<height;i++)
					{
					for(j=0;j<width;j++)
						{
						canvas[i][j]=0;		
						}
					}				
			}
			
			if(lifenumber%10==9)
			{
				snakeonion();               //��������� 
			}
			if(snakelength>=200)
			{
				snakeonion();
			}
			
			 
			system("cls");	
			main();
		}
		else if(confirm!='r'||confirm!='R')
		{
		printf("you may not catch the r\n");
		}
	}
} 

void startup()        //��ʼ��  
{
	int i,j;
	for(i=0;i<height;i++) //�߿�
	{
		canvas[i][0]=-1;
		canvas[i][width-1]=-1;
	} 
	for(j=0;j<width;j++)
	{
		canvas[0][j]=-1;
		canvas[height-1][j]=-1;
	}
	
	movedirection=1;			//���� 
	taildirection=4;
	
	canvas[height/2][width/2]=1; //��
	newheadi=height/2;
	newheadj=width/2;
	for(i=1;i<=4;i++)
		{
		canvas[height/2][width/2-i]=i+1; 
		}
	oldtaili=height/2;
	oldtailj=width/2-i+1;	
	snakelength=5; 
	
	srand((unsigned)time(NULL));	
	foodx=rand()%(height-2)+1;    //ˮ�� 
	foody=rand()%(width-2)+1;
	while(canvas[foodx][foody]!=0)
	{
		foodx=rand()%(height-2)+1;
		foody=rand()%(width-2)+1;
    }
	canvas[foodx][foody]=-2;
	
	demonnumber=1;
	srand((unsigned)time(NULL));	
	demonx=rand()%(height-2)+1;    //��ħ
	demony=rand()%(width-2)+1;
	while(canvas[demonx][demony]!=0)
	{
		demonx=rand()%(height-2)+1;
		demony=rand()%(width-2)+1;
    }
	canvas[demonx][demony]=-3;
}

void gotoxy()           //�������                    
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=0;
	pos.Y=0;
	SetConsoleCursorPosition(handle,pos); 
} 


void show()      //��ʾͼ�� 
{
	gotoxy();
	int i,j;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			switch(canvas[i][j])
			{
				case 0:printf(" ");     //�ո� 
					break;
				case -1:printf("#");	//ǽ 
					break;
				case 1:printf("@");		//��ͷ 
					break;
				case -2:printf("A");	//��ʵ 
					break;
				case -3:printf("$");	//��ħ 
					break;
				case -4:printf("|");	//����
					break;				
				case -5:printf("O");	//ʯͷ 
					break;
				default:printf("*");	//���� 
					break;
			}
		}
		printf("\n"); 
	}
} 

void direction()
{
	char input;
	if(kbhit())
	{
		input=getch();
		if(input=='v')ray=1;
		
		else if(input=='a')
			{
				if (movedirection==1)movedirection=3;
				else if (movedirection==2)movedirection=1;
				else if (movedirection==3)movedirection=4;
				else if (movedirection==4)movedirection=2;
				taildirection=5-movedirection;
			}
		else if(input=='d')
			{
				if (movedirection==1)movedirection=2;
				else if (movedirection==2)movedirection=4;
				else if (movedirection==3)movedirection=1;
				else if (movedirection==4)movedirection=3;
				taildirection=5-movedirection;
			}	 
		
	}
if(ray==1)return;	
else if (movedirection==1)newheadj++;
else if (movedirection==2)newheadi++;
else if (movedirection==3)newheadi--;
else if (movedirection==4)newheadj--;
}

void iswall()
{
if (canvas[newheadi][newheadj]==-1)
	{
		printf("wall is tough!\n");
		Sleep(2000);
		playagain();
	}
}

void isstone()
{
if (canvas[newheadi][newheadj]==-5)
	{
		printf("stiff body is not for picnic!\n");
		Sleep(2000);
		playagain();	
	}
}

void istail()
{
if (canvas[newheadi][newheadj]>1)
{
snakelength=canvas[newheadi][newheadj]-1;	
int i,j;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(canvas[i][j]>canvas[newheadi][newheadj])canvas[i][j]=-5;		
		}
	}	
}	
}

void isdemon()
{
int i,j,isdeath=0;
int tail1i,tail1j,tail2i,tail2j,tail3i,tail3j;
				
if (canvas[newheadi][newheadj]==-3)	
	{
		snakelength+=3;
		if(taildirection==1)   //β���������� 
		{
			
			for(i=1;i<=3;i++)
			{
				if (canvas[oldtaili][oldtailj+1]<0||canvas[oldtaili][oldtailj+1]==1)
					{
						isdeath=1;
					}	
				else if(canvas[oldtaili][oldtailj+1]>1)	
					{
							for(i=0;i<height;i++)
							{
							for(j=0;j<width;j++)
							{
							if(canvas[i][j]>canvas[oldtaili][oldtailj+1])canvas[i][j]==-5;		
							}	
							}
					oldtailj++;			
					}
				else if(canvas[oldtaili][oldtailj+1]==0)
					{
						canvas[oldtaili][oldtailj+1]=canvas[oldtaili][oldtailj]+1;
						oldtailj++;
					}	
			}
		}
		else if(taildirection==2)//β���������� 
		{
				for(i=1;i<=3;i++)
			{
				if (canvas[oldtaili+1][oldtailj]<0||canvas[oldtaili+1][oldtailj]==1)
					{
						isdeath=1;
					}	
				else if(canvas[oldtaili+1][oldtailj]>1)	
					{
							for(i=0;i<height;i++)
							{
							for(j=0;j<width;j++)
							{
							if(canvas[i][j]>canvas[oldtaili+1][oldtailj])canvas[i][j]==-5;		
							}	
							}	
					canvas[oldtaili+1][oldtailj]=canvas[oldtaili][oldtailj]+1;
					oldtaili++;		
					}
				else if(canvas[oldtaili+1][oldtailj]==0)
					{
					canvas[oldtaili+1][oldtailj]=canvas[oldtaili][oldtailj]+1;
					oldtaili++;
					}	
			}
		}
		else if(taildirection==3) //β���������� 
		{
					for(i=1;i<=3;i++)
			{
				if (canvas[oldtaili-1][oldtailj]<0||canvas[oldtaili-1][oldtailj]==1)
					{
						isdeath=1;
					}	
				else if(canvas[oldtaili-1][oldtailj]>1)	
					{
							for(i=0;i<height;i++)
							{
							for(j=0;j<width;j++)
							{
							if(canvas[i][j]>canvas[oldtaili-1][oldtailj])canvas[i][j]==-5;		
							}	
							}	
					canvas[oldtaili-1][oldtailj]=canvas[oldtaili][oldtailj]+1;
					oldtaili--;		
					}
				else if(canvas[oldtaili+1][oldtailj]==0)
					{
					canvas[oldtaili-1][oldtailj]=canvas[oldtaili][oldtailj]+1;
					oldtaili--;
					}	
			}
		}	
		else if(taildirection==4)   //β���������� 
		{
				for(i=1;i<=3;i++)
			{
				if (canvas[oldtaili][oldtailj-1]<0||canvas[oldtaili][oldtailj-1]==1)
					{
						isdeath=1;
					}	
				else if(canvas[oldtaili][oldtailj-1]>1)	
					{
							for(i=0;i<height;i++)
							{
							for(j=0;j<width;j++)
							{
							if(canvas[i][j]>canvas[oldtaili][oldtailj-1])canvas[i][j]==-5;		
							}	
							}
					oldtailj--;	
					}
				else if(canvas[oldtaili][oldtailj-1]==0)
					{
						canvas[oldtaili][oldtailj-1]=canvas[oldtaili][oldtailj]+1;
						oldtailj--;
					}	
			}
		}
	if(demonnumber<=7)
	{
		srand((unsigned)time(NULL));	
		demonx=rand()%(height-2)+1;    //��ħˢ�� 
		demony=rand()%(width-2)+1;
		while(canvas[demonx][demony]!=0)
		{
			demonx=rand()%(height-2)+1;
			demony=rand()%(width-2)+1;
	    }
	canvas[demonx][demony]=-3;
	demonnumber++;	
	}
}

if(isdeath)
	{
		printf("welcome to the hell!\ntail grows against the head\n");
		Sleep(2000);
		playagain();
	}	
	
}

void isfruitABOUTtail()    
{
	int i,j;
	if(canvas[newheadi][newheadj]==-2)
	{
		snakelength++;
		canvas[foodx][foody]=0;
		srand((unsigned)time(NULL));
		foodx=rand()%(height-2)+1;
		foody=rand()%(width-2)+1;
		while(canvas[foodx][foody]!=0)
		{
		foodx=rand()%(height-2)+1;
		foody=rand()%(width-2)+1;
		}
			canvas[foodx][foody]=-2;	
	}

	else
	{
		canvas[oldtaili][oldtailj]=0;
		for(i=0;i<height;i++)
		{
			for(j=0;j<width;j++)
			{
				if(canvas[i][j]>canvas[oldtaili][oldtailj])
				{
					oldtaili=i;
					oldtailj=j;
				}		
			}
		}	
	}
}


void isray()
{
int i,j;	
if(ray&&snakelength>=3)
{
	snakelength--;
	if(movedirection==1)   //����
		{
			for(i=1;i<=3;i++)
   			{
			if(canvas[newheadi][newheadj+i]==-5||canvas[newheadi][newheadj+i]==0)
			{
			canvas[newheadi][newheadj+i]=-4;
			}
			}
		}
	else if(movedirection==2) //����
		{
			for(i=1;i<=3;i++)
			{
			if(canvas[newheadi+i][newheadj]==-5||canvas[newheadi+i][newheadj]==0)
			{
			canvas[newheadi+i][newheadj]=-4;
			}
			}
		}
	else if(movedirection==3) //����
		{
			for(i=1;i<=3;i++)
			{
			if(canvas[newheadi-i][newheadj]==-5||canvas[newheadi-i][newheadj]==0)
			{
			canvas[newheadi-i][newheadj]=-4;
			}
			} 
		}
	else if(movedirection==4) //���� 
		{
			for(i=1;i<=3;i++)
			{
			if(canvas[newheadi][newheadj-i]==-5||canvas[newheadi][newheadj-i]==0)
			{
			canvas[newheadi][newheadj-i]=-4;
			}
			} 
		}
show();
Sleep(200);
int maxi=0,maxj=0,maxtaili=0,maxtailj=0;
for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(canvas[i][j]==-4)canvas[i][j]=0;
			if(canvas[i][j]>canvas[maxi][maxj]) 
			{
				maxtaili=maxi;
				maxtailj=maxj;
				maxi=i;
				maxj=j;
			}		
		}
	}	
canvas[maxi][maxj]=0;
oldtaili=maxtaili;
oldtailj=maxtailj;		
}
ray=0;
}

void issuccess()
{
int i,j;
	for(i=1;i<height-1;i++)
	{
		for(j=1;j<width-1;j++)
		{
			if(canvas[i][j]<1)return;
		}
	}	
	printf("You have successfully eaten the map!\n");	
	Sleep(1000);
	printf("si si \n");
	Sleep(3000);
	printf("burpppppppp\n");
}

void moveon()
{
	int i,j;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(canvas[i][j]>0)
				{
				canvas[i][j]++;		
				}
		}
	}
	canvas[newheadi][newheadj]=1;	
}



int main()
{	//��ʼ���� 
	printf("Imagine you are a snake\nPress A to left and D to right and v to clean\nImagine A is the fruit for growing and $ is the demon unimaginable\nFill the map to win\nInput 'P' to begin\n");
	char confirm3; 
	int flag3=1;
		while(flag3==1)
		{
			scanf("%c",&confirm3);
			setbuf(stdin,NULL);    //������뻺���� 
			if(confirm3=='p'||confirm3=='P')
			{
			flag3=0;
			}
			else if(confirm3!='p'||confirm3!='P')
			{
			printf("is it the p?\n");
			}
		}
	system("cls"); 
	startup();
	//����ʼ
while(1)
{	
	system("cls");
	gotoxy();
	show(); 
    direction();
if(ray!=1)
{ 
    isfruitABOUTtail();
	iswall();
	isstone();
	isdemon();
	istail();
	moveon();
}
	isray();
	issuccess();

Sleep(200);
}
return 0; 
}
									 
 
 
