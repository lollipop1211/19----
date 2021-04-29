#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
struct PCB
{
	string name;
	int arrivetime;//到达
	int servicetime;//服务
	int finishtime;//完成
	int waittime;//等待
	double quan;//HRRN中的权
	int priority;//SP中的权
	bool ifrun;//是否执行
	int RR_time;//执行时间
} pcb[10];
queue<PCB> q;
PCB Que[100];
PCB sjf[10];
PCB hrrn[10];
PCB rr[10];
PCB sp[10];
int top=0;
bool cmpSJF(PCB a,PCB b)
{
	return a.servicetime<b.servicetime;
}

bool cmpHRRN(PCB a,PCB b)
{
	return a.quan>b.quan;
}
bool cmpSP(PCB a,PCB b)
{
	return a.priority>b.priority;
}
void menu()
{
	printf("————————————进程管理系统——————————————————\n\n");
	printf("————————————1. 输入进程情况———————————————\n\n");
	printf("————————————2. 显示进程情况———————————————\n\n");
	printf("————————————3. 短作业优先算法—————————————\n\n");
	printf("————————————4. 高响应比优先算法———————————\n\n");
	printf("————————————5. 时间片轮转算法—————————————\n\n");
	printf("————————————6. 静态优先权算法—————————————\n\n");
	printf("————————————0. 退出————————————————\n\n");
}
void input(int n)
{
	for(int i=0; i<n; i++)
	{
		printf("进程%d:\n",i);
		printf("请输入进程名称:");
		cin>>pcb[i].name;
		printf("请输入到达时间:");
		cin>>pcb[i].arrivetime;
		printf("请输入服务时间:");
		cin>>pcb[i].servicetime;
		printf("\n");
	}
}
void display(int n)
{
	printf("名称");
	printf("     ");
	for(int i=0; i<n; i++)
		cout<<pcb[i].name<<" ";
	printf("\n到达时间 ");
	for(int i=0; i<n; i++)
		cout<<pcb[i].arrivetime<<" ";
	printf("\n服务时间 ");
	for(int i=0; i<n; i++)
		cout<<pcb[i].servicetime<<" ";
	printf("\n");
	system("pause");
}
void outputQue(int front,int rear)
{

	printf("\t当前就绪队列: " );
	for(int i=front; i<rear; i++)
	{
		cout<<Que[i].name;
	}
	cout<<endl;
}
void SPF(int n)
{
	top = 0;
	int front = 0;
	int rear = 0;
	PCB p= {"0",0,0,0};
	int now = 0;
	int flag = 0; //0空闲 1运行
	int r=0;
	while(1)
	{
		//如果当前空闲，并且不是第一次空闲，说明有进程执行完毕
		if(flag == 0&&p.name!="0")
		{
			cout<<now<<" "<<p.name<<"执行完毕"<<endl;
			p.ifrun = true;
			sjf[top++]=p;//只有当执行完毕了才把p放进去
		}
		//如果进程全部执行完
		if(top == n)
			break;
		//查看这一秒是否有进程到达
		for(int i=r; i<n; i++)
		{
			if(pcb[i].arrivetime == now)   //此时间有进程到达
			{
				Que[rear++]=pcb[i]; //入队
				cout<<now<<" "<<pcb[i].name<<"到达"<<endl;
				sort(Que+front,Que+rear,cmpSJF);//将就绪队列中的进程按照服务时间进行排序，服务时间短的在前边
				r=i+1;
			}
		}
		if(flag == 0&&front!=rear)   //空闲,如果队首等于队尾那么就是空闲的
		{
			//取队头执行
			p = Que[front++];//或者p=Que[front],front++,取队首并且出队
			cout<<now<<" "<<p.name<<"开始执行"<<endl;
			p.finishtime = p.servicetime+now;
			flag = p.servicetime;
		}
		//下一秒
		now++;
		if(flag>0)
			flag--;
		Sleep(500);
	}
	int sumzhou = 0;
	double sumdai = 0;
	printf("名称\t到达时间\t服务时间\t完成时间\t周转时间\t带权周转时间\n");
	for(int i=0; i<n; i++)
	{
		cout<<sjf[i].name<<"\t";
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%.2f\n",sjf[i].arrivetime,sjf[i].servicetime,sjf[i].finishtime,sjf[i].finishtime-sjf[i].arrivetime,(sjf[i].finishtime*1.0-sjf[i].arrivetime)/sjf[i].servicetime*1.0);
	}
	for(int i=0; i<n; i++)
	{
		sumzhou+=sjf[i].finishtime-sjf[i].arrivetime;
		sumdai+=(sjf[i].finishtime*1.0-sjf[i].arrivetime)/sjf[i].servicetime*1.0;
	}
	printf("平均周转时间：%.2f   平均带权周转时间：%.2f",sumzhou*1.0/n,sumdai/n);
	system("pause");
}
void SP(int n)
{
	for(int i=0; i<n; i++)
	{
		printf("进程%d:\n",i);
		printf("请输入进程名称:");
		cin>>pcb[i].name;
		printf("请输入到达时间:");
		cin>>pcb[i].arrivetime;
		printf("请输入服务时间:");
		cin>>pcb[i].servicetime;
		printf("请输入优先权:");
		cin>>pcb[i].priority;
		printf("\n");
	}
	top = 0;
	int front = 0;
	int rear = 0;
	PCB p= {"0",0,0,0};
	int now = 0;
	int flag = 0; //0空闲 1运行
	int r=0;
	while(1)
	{
		//printf("%d\n",now);
		//如果当前空闲，并且不是第一次空闲，说明有进程执行完毕
		if(flag == 0&&p.name!="0")
		{
			cout<<now<<" "<<p.name<<"执行完毕"<<endl;
			p.ifrun = true;
			sp[top++]=p;//只有当执行完毕了才把p放进去
		}
		//如果进程全部执行完
		if(top == n)
			break;
		//查看这一秒是否有进程到达
		for(int i=r; i<n; i++)
		{
			if(pcb[i].arrivetime == now)   //此时间有进程到达
			{
				Que[rear++]=pcb[i]; //入队
				cout<<now<<" "<<pcb[i].name<<"到达"<<endl;
				sort(Que+front,Que+rear,cmpSP);//将就绪队列按照优先权进行排序，优先权大的放在前面
				r=i+1;
			}
		}
		if(flag == 0&&front!=rear)   //空闲,如果队首等于队尾那么就是空闲的
		{
			//取队头执行
			p = Que[front++];//或者p=Que[front],front++,取队首并且出队
			cout<<now<<" "<<p.name<<"开始执行"<<endl;
			p.finishtime = p.servicetime+now;
			flag = p.servicetime;
		}
		//下一秒
		now++;
		if(flag>0)
			flag--;
		Sleep(500);
	}
	int sumzhou = 0;
	double sumdai = 0;
	printf("名称\t到达时间\t服务时间\t优先权\t完成时间\t周转时间\t带权周转时间\n");
	for(int i=0; i<n; i++)
	{
		cout<<sp[i].name<<"\t";
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%.2f\n",sp[i].arrivetime,sp[i].servicetime,sp[i].priority,sp[i].finishtime,sp[i].finishtime-sp[i].arrivetime,(sp[i].finishtime*1.0-sp[i].arrivetime)/sp[i].servicetime*1.0);
	}
	for(int i=0; i<n; i++)
	{
		sumzhou+=sp[i].finishtime-sp[i].arrivetime;
		sumdai+=(sp[i].finishtime*1.0-sp[i].arrivetime)/sp[i].servicetime*1.0;
	}
	printf("平均周转时间：%.2f   平均带权周转时间：%.2f",sumzhou*1.0/n,sumdai/n);
	system("pause");
}
void HRRN(int n)
{
	top = 0;
	int front = 0;
	int rear = 0;
	PCB p= {"0",0,0,0};
	int now = 0;
	int flag = 0; //0空闲 1运行
	int r=0;
	while(1)
	{
		//printf("%d\n",now);
		//如果当前空闲，并且不是第一次空闲，说明有进程执行完毕
		if(flag == 0&&p.name!="0")
		{
			cout<<now<<" "<<p.name<<"执行完毕"<<endl;
			p.ifrun = true;
			hrrn[top++]=p;//只有当执行完毕了才把p放进去
		}
		//如果进程全部执行完
		if(top == n)
			break;
		//查看这一秒是否有进程到达
		for(int i=r; i<n; i++)
		{
			if(pcb[i].arrivetime == now)   //此时间有进程到达
			{
				cout<<now<<" "<<pcb[i].name<<"到达"<<endl;
				Que[rear++]=pcb[i]; //入队
				r=i+1;
			}
		}
		if(flag == 0&&front!=rear)   //空闲
		{
			//计算优先权并排序
			for(int j=front; j<rear; j++)
				Que[j].quan = (Que[j].waittime*1.0+Que[j].servicetime)/Que[j].servicetime;//动态优先权的计算，优先权=（等待时间+服务时间）/服务时间
			sort(Que+front,Que+rear,cmpHRRN);//已经到达的按照优先权进行排序，把优先权大的放在前边，优先权的计算就是等待时间/服务时间+1
			//取队头
			p = Que[front++];//取队头然后出队
			cout<<now<<" "<<p.name<<"开始执行"<<endl;
			p.finishtime = p.servicetime+now;
			flag = p.servicetime;
		}
		//下一秒
		now++;
		for(int i = front; i<rear; i++)
		{
			Que[i].waittime++;//时间每增加一秒，每个进程的等待时间加一
		}
		if(flag>0)
			flag--;
		Sleep(500);
	}
	int sumzhou = 0;
	double sumdai = 0;
	printf("名称\t到达时间\t服务时间\t完成时间\t周转时间\t带权周转时间\n");
	for(int i=0; i<n; i++)
	{
		cout<<hrrn[i].name<<"\t";
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%.2f\n",hrrn[i].arrivetime,hrrn[i].servicetime,hrrn[i].finishtime,hrrn[i].finishtime-hrrn[i].arrivetime,(hrrn[i].finishtime*1.0-hrrn[i].arrivetime)/hrrn[i].servicetime*1.0);
	}
	for(int i=0; i<n; i++)
	{
		sumzhou+=hrrn[i].finishtime-hrrn[i].arrivetime;
		sumdai+=(hrrn[i].finishtime*1.0-hrrn[i].arrivetime)/hrrn[i].servicetime*1.0;
	}
	printf("平均周转时间：%.2f   平均带权周转时间：%.2f",sumzhou*1.0/n,sumdai/n);
	system("pause");
}

void RR(int n)
{
	int t=0;//用来统计时间片是否用完的
	top = 0;
	int front = 0;
	int rear = 0;
	PCB p={"0",0,0,0};
	int now = 0;//用来统计现在的时间的
	int r=0;//进行程序的后移，就不再考虑已经放进队列的程序
	int time;
	printf("请输入时间片间隔:");
	scanf("%d",&time);//time是时间片的间隔
	while(1)
	{
		if(t == time)//时间片用完
			t=0;
		//扫描入队
		for(int i=r; i<n; i++)
		{
			if(pcb[i].arrivetime == now)   //此时间有进程到达
			{
				cout<<now<<" "<<pcb[i].name<<"到达"<<endl;
				Que[rear++]=pcb[i]; //入队
				outputQue(front,rear);//输出当前就绪队列
				r=i+1;
			}
		}
		if(p.name!="0") //不是第一次，并且里面有进程，判断进程是否全部服务时间用完还是仅是时间片用完
		{
			if(p.RR_time >= p.servicetime)//如果已经完成服务时间
			{
				cout<<now<<" "<<p.name<<" "<<"结束!"<<endl;
				p.finishtime=now;//完成时间就是现在的时间now
				t=0;//这是给时间片清零
				rr[top++]=p;//执行完将进程放进rr中
				if(top == n)
					break;
				p.name="0";//如果这个进程已经被统计过了就清零后面不在考虑
			}
			else if(t == 0) //如果没有完成并且时间片用完了
			{
				cout<<now<<" "<<p.name<<" "<<"时间片用完!"<<endl;
				Que[rear++]=p;//如果仅是时间片用完而进程并没有结束，还需再次将程序压入队列
				outputQue(front,rear);
			}

		}
		if(t == 0 && front!=rear)//说明进程时间片用完，可以开始执行新的进程，这里是时间片用完然后就绪队列里面有等待的进程
		{
			p = Que[front++];//取队首开始执行
			cout<<now<<" "<<p.name<<"开始执行"<<endl;
			outputQue(front,rear);//开始执行是输出现在队列里面的就绪队列
		}
		now++;
		t++;//看时间片是否用完的
		p.RR_time++;//看进程的服务时间是否用完的
		Sleep(500);
	}
	int sumzhou = 0;
	double sumdai = 0;
	printf("名称\t到达时间\t服务时间\t完成时间\t周转时间\t带权周转时间\n");
	for(int i=0; i<n; i++)
	{
		cout<<rr[i].name<<"\t";
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%.2f\n",rr[i].arrivetime,rr[i].servicetime,rr[i].finishtime,rr[i].finishtime-rr[i].arrivetime,(rr[i].finishtime*1.0-rr[i].arrivetime)/rr[i].servicetime*1.0);
	}
	for(int i=0; i<n; i++)
	{
		sumzhou+=rr[i].finishtime-rr[i].arrivetime;
		sumdai+=(rr[i].finishtime*1.0-rr[i].arrivetime)/rr[i].servicetime*1.0;
	}
	printf("平均周转时间：%.2f   平均带权周转时间：%.2f",sumzhou*1.0/n,sumdai/n);
	system("pause");
}
int main()
{
	int n,m;
	printf("请输入进程数：");
	cin>>n;

	while(1)
	{
		menu();
		scanf("%d",&m);
		switch(m)
		{
			case 1:
				input(n);
				break;
			case 2:
				display(n);
				break;
			case 3:
				FCFS(n);
				break;
			case 4:
				SPF(n);
				break;
			case 5:
				HRRN(n);
				break;
			case 6:
				RR(n);
				break;
            case 7:
                SP(n);
                break;
			case 0:
				exit(1);
				break;
			default :
				printf("请输入有效选项!\n");
		}
	}
}
