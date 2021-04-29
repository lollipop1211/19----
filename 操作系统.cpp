#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
struct PCB
{
	string name;
	int arrivetime;//����
	int servicetime;//����
	int finishtime;//���
	int waittime;//�ȴ�
	double quan;//HRRN�е�Ȩ
	int priority;//SP�е�Ȩ
	bool ifrun;//�Ƿ�ִ��
	int RR_time;//ִ��ʱ��
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
	printf("���������������������������̹���ϵͳ������������������������������������\n\n");
	printf("������������������������1. ����������������������������������������\n\n");
	printf("������������������������2. ��ʾ�������������������������������������\n\n");
	printf("������������������������3. ����ҵ�����㷨��������������������������\n\n");
	printf("������������������������4. ����Ӧ�������㷨����������������������\n\n");
	printf("������������������������5. ʱ��Ƭ��ת�㷨��������������������������\n\n");
	printf("������������������������6. ��̬����Ȩ�㷨��������������������������\n\n");
	printf("������������������������0. �˳���������������������������������\n\n");
}
void input(int n)
{
	for(int i=0; i<n; i++)
	{
		printf("����%d:\n",i);
		printf("�������������:");
		cin>>pcb[i].name;
		printf("�����뵽��ʱ��:");
		cin>>pcb[i].arrivetime;
		printf("���������ʱ��:");
		cin>>pcb[i].servicetime;
		printf("\n");
	}
}
void display(int n)
{
	printf("����");
	printf("     ");
	for(int i=0; i<n; i++)
		cout<<pcb[i].name<<" ";
	printf("\n����ʱ�� ");
	for(int i=0; i<n; i++)
		cout<<pcb[i].arrivetime<<" ";
	printf("\n����ʱ�� ");
	for(int i=0; i<n; i++)
		cout<<pcb[i].servicetime<<" ";
	printf("\n");
	system("pause");
}
void outputQue(int front,int rear)
{

	printf("\t��ǰ��������: " );
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
	int flag = 0; //0���� 1����
	int r=0;
	while(1)
	{
		//�����ǰ���У����Ҳ��ǵ�һ�ο��У�˵���н���ִ�����
		if(flag == 0&&p.name!="0")
		{
			cout<<now<<" "<<p.name<<"ִ�����"<<endl;
			p.ifrun = true;
			sjf[top++]=p;//ֻ�е�ִ������˲Ű�p�Ž�ȥ
		}
		//�������ȫ��ִ����
		if(top == n)
			break;
		//�鿴��һ���Ƿ��н��̵���
		for(int i=r; i<n; i++)
		{
			if(pcb[i].arrivetime == now)   //��ʱ���н��̵���
			{
				Que[rear++]=pcb[i]; //���
				cout<<now<<" "<<pcb[i].name<<"����"<<endl;
				sort(Que+front,Que+rear,cmpSJF);//�����������еĽ��̰��շ���ʱ��������򣬷���ʱ��̵���ǰ��
				r=i+1;
			}
		}
		if(flag == 0&&front!=rear)   //����,������׵��ڶ�β��ô���ǿ��е�
		{
			//ȡ��ͷִ��
			p = Que[front++];//����p=Que[front],front++,ȡ���ײ��ҳ���
			cout<<now<<" "<<p.name<<"��ʼִ��"<<endl;
			p.finishtime = p.servicetime+now;
			flag = p.servicetime;
		}
		//��һ��
		now++;
		if(flag>0)
			flag--;
		Sleep(500);
	}
	int sumzhou = 0;
	double sumdai = 0;
	printf("����\t����ʱ��\t����ʱ��\t���ʱ��\t��תʱ��\t��Ȩ��תʱ��\n");
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
	printf("ƽ����תʱ�䣺%.2f   ƽ����Ȩ��תʱ�䣺%.2f",sumzhou*1.0/n,sumdai/n);
	system("pause");
}
void SP(int n)
{
	for(int i=0; i<n; i++)
	{
		printf("����%d:\n",i);
		printf("�������������:");
		cin>>pcb[i].name;
		printf("�����뵽��ʱ��:");
		cin>>pcb[i].arrivetime;
		printf("���������ʱ��:");
		cin>>pcb[i].servicetime;
		printf("����������Ȩ:");
		cin>>pcb[i].priority;
		printf("\n");
	}
	top = 0;
	int front = 0;
	int rear = 0;
	PCB p= {"0",0,0,0};
	int now = 0;
	int flag = 0; //0���� 1����
	int r=0;
	while(1)
	{
		//printf("%d\n",now);
		//�����ǰ���У����Ҳ��ǵ�һ�ο��У�˵���н���ִ�����
		if(flag == 0&&p.name!="0")
		{
			cout<<now<<" "<<p.name<<"ִ�����"<<endl;
			p.ifrun = true;
			sp[top++]=p;//ֻ�е�ִ������˲Ű�p�Ž�ȥ
		}
		//�������ȫ��ִ����
		if(top == n)
			break;
		//�鿴��һ���Ƿ��н��̵���
		for(int i=r; i<n; i++)
		{
			if(pcb[i].arrivetime == now)   //��ʱ���н��̵���
			{
				Que[rear++]=pcb[i]; //���
				cout<<now<<" "<<pcb[i].name<<"����"<<endl;
				sort(Que+front,Que+rear,cmpSP);//���������а�������Ȩ������������Ȩ��ķ���ǰ��
				r=i+1;
			}
		}
		if(flag == 0&&front!=rear)   //����,������׵��ڶ�β��ô���ǿ��е�
		{
			//ȡ��ͷִ��
			p = Que[front++];//����p=Que[front],front++,ȡ���ײ��ҳ���
			cout<<now<<" "<<p.name<<"��ʼִ��"<<endl;
			p.finishtime = p.servicetime+now;
			flag = p.servicetime;
		}
		//��һ��
		now++;
		if(flag>0)
			flag--;
		Sleep(500);
	}
	int sumzhou = 0;
	double sumdai = 0;
	printf("����\t����ʱ��\t����ʱ��\t����Ȩ\t���ʱ��\t��תʱ��\t��Ȩ��תʱ��\n");
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
	printf("ƽ����תʱ�䣺%.2f   ƽ����Ȩ��תʱ�䣺%.2f",sumzhou*1.0/n,sumdai/n);
	system("pause");
}
void HRRN(int n)
{
	top = 0;
	int front = 0;
	int rear = 0;
	PCB p= {"0",0,0,0};
	int now = 0;
	int flag = 0; //0���� 1����
	int r=0;
	while(1)
	{
		//printf("%d\n",now);
		//�����ǰ���У����Ҳ��ǵ�һ�ο��У�˵���н���ִ�����
		if(flag == 0&&p.name!="0")
		{
			cout<<now<<" "<<p.name<<"ִ�����"<<endl;
			p.ifrun = true;
			hrrn[top++]=p;//ֻ�е�ִ������˲Ű�p�Ž�ȥ
		}
		//�������ȫ��ִ����
		if(top == n)
			break;
		//�鿴��һ���Ƿ��н��̵���
		for(int i=r; i<n; i++)
		{
			if(pcb[i].arrivetime == now)   //��ʱ���н��̵���
			{
				cout<<now<<" "<<pcb[i].name<<"����"<<endl;
				Que[rear++]=pcb[i]; //���
				r=i+1;
			}
		}
		if(flag == 0&&front!=rear)   //����
		{
			//��������Ȩ������
			for(int j=front; j<rear; j++)
				Que[j].quan = (Que[j].waittime*1.0+Que[j].servicetime)/Que[j].servicetime;//��̬����Ȩ�ļ��㣬����Ȩ=���ȴ�ʱ��+����ʱ�䣩/����ʱ��
			sort(Que+front,Que+rear,cmpHRRN);//�Ѿ�����İ�������Ȩ�������򣬰�����Ȩ��ķ���ǰ�ߣ�����Ȩ�ļ�����ǵȴ�ʱ��/����ʱ��+1
			//ȡ��ͷ
			p = Que[front++];//ȡ��ͷȻ�����
			cout<<now<<" "<<p.name<<"��ʼִ��"<<endl;
			p.finishtime = p.servicetime+now;
			flag = p.servicetime;
		}
		//��һ��
		now++;
		for(int i = front; i<rear; i++)
		{
			Que[i].waittime++;//ʱ��ÿ����һ�룬ÿ�����̵ĵȴ�ʱ���һ
		}
		if(flag>0)
			flag--;
		Sleep(500);
	}
	int sumzhou = 0;
	double sumdai = 0;
	printf("����\t����ʱ��\t����ʱ��\t���ʱ��\t��תʱ��\t��Ȩ��תʱ��\n");
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
	printf("ƽ����תʱ�䣺%.2f   ƽ����Ȩ��תʱ�䣺%.2f",sumzhou*1.0/n,sumdai/n);
	system("pause");
}

void RR(int n)
{
	int t=0;//����ͳ��ʱ��Ƭ�Ƿ������
	top = 0;
	int front = 0;
	int rear = 0;
	PCB p={"0",0,0,0};
	int now = 0;//����ͳ�����ڵ�ʱ���
	int r=0;//���г���ĺ��ƣ��Ͳ��ٿ����Ѿ��Ž����еĳ���
	int time;
	printf("������ʱ��Ƭ���:");
	scanf("%d",&time);//time��ʱ��Ƭ�ļ��
	while(1)
	{
		if(t == time)//ʱ��Ƭ����
			t=0;
		//ɨ�����
		for(int i=r; i<n; i++)
		{
			if(pcb[i].arrivetime == now)   //��ʱ���н��̵���
			{
				cout<<now<<" "<<pcb[i].name<<"����"<<endl;
				Que[rear++]=pcb[i]; //���
				outputQue(front,rear);//�����ǰ��������
				r=i+1;
			}
		}
		if(p.name!="0") //���ǵ�һ�Σ����������н��̣��жϽ����Ƿ�ȫ������ʱ�����껹�ǽ���ʱ��Ƭ����
		{
			if(p.RR_time >= p.servicetime)//����Ѿ���ɷ���ʱ��
			{
				cout<<now<<" "<<p.name<<" "<<"����!"<<endl;
				p.finishtime=now;//���ʱ��������ڵ�ʱ��now
				t=0;//���Ǹ�ʱ��Ƭ����
				rr[top++]=p;//ִ���꽫���̷Ž�rr��
				if(top == n)
					break;
				p.name="0";//�����������Ѿ���ͳ�ƹ��˾�������治�ڿ���
			}
			else if(t == 0) //���û����ɲ���ʱ��Ƭ������
			{
				cout<<now<<" "<<p.name<<" "<<"ʱ��Ƭ����!"<<endl;
				Que[rear++]=p;//�������ʱ��Ƭ��������̲�û�н����������ٴν�����ѹ�����
				outputQue(front,rear);
			}

		}
		if(t == 0 && front!=rear)//˵������ʱ��Ƭ���꣬���Կ�ʼִ���µĽ��̣�������ʱ��Ƭ����Ȼ��������������еȴ��Ľ���
		{
			p = Que[front++];//ȡ���׿�ʼִ��
			cout<<now<<" "<<p.name<<"��ʼִ��"<<endl;
			outputQue(front,rear);//��ʼִ����������ڶ�������ľ�������
		}
		now++;
		t++;//��ʱ��Ƭ�Ƿ������
		p.RR_time++;//�����̵ķ���ʱ���Ƿ������
		Sleep(500);
	}
	int sumzhou = 0;
	double sumdai = 0;
	printf("����\t����ʱ��\t����ʱ��\t���ʱ��\t��תʱ��\t��Ȩ��תʱ��\n");
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
	printf("ƽ����תʱ�䣺%.2f   ƽ����Ȩ��תʱ�䣺%.2f",sumzhou*1.0/n,sumdai/n);
	system("pause");
}
int main()
{
	int n,m;
	printf("�������������");
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
				printf("��������Чѡ��!\n");
		}
	}
}
