#include<windows.h>
#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<iomanip>
#include<time.h>
#include<string>
#include<cassert>
#define DEBUG
using namespace std;
const int size=7;
const int maxn=1000;
int lx=100,ly=100;
void gotoxy(int x,int y)
{
	COORD pos;
	pos.X=2*x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void qxgb()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
}
void show_start()
{
	srand(time(0));
	gotoxy(13,3);
	color(12);
	string wel="Welcome to GALAXY";
	for(int i=0;i<wel.size();i++)
	{
		cout<<wel[i];
		if(wel[i]!=' ')
		Sleep(200);
	}
	cout<<endl;
	Sleep(500);
	qxgb();
	gotoxy(8,4);
	color(3);
	cout<<" -----------------------------------";
	for(int i=5;i<=8;i++)
	{
		gotoxy(8,i);
		cout<<"|";
		gotoxy(26,i);
		cout<<"|";
	}
	gotoxy(15,5);
	color(12);
	cout<<"Game menu";
	gotoxy(10,6);
	color(14);
	cout.width(20);
	cout<<"Game maker: YR JR HSF";
	gotoxy(10,7);
	color(11);
	cout<<"1.start                2.exit";
	color(3);
	gotoxy(9,9);
	cout<<"---------------------------------";
	color(15);
	gotoxy(15,11);
}
struct hero
{
	string name;
	bool alive;
	int hp,atk,def,blue,hx,hl,yz;//Ѫ�� ����  ����  ��  ��Ѫ ���� Ӳֱ 
	int skill[maxn];//���ܱ� 
	int state[maxn];//״̬�� 1��Ѫ 2�ӹ��� 3�ӷ��� 4 ��Ѫ 5 ������ 6 ������ 
};
namespace Skill
{
	bool check(hero t)
	{
		if(t.hp<0)
		{
			t.hp=0;
			t.alive=0;
		}
		return t.alive;
	}
	struct skill{
		int yz;
		int blue;
		int min;
		int max;
		string name;
		void (*p)(hero &,hero &);
	};
	skill skl[maxn];
		void  uwlbf(hero & me,hero & enemy)//�������  1
		{
			if(me.blue<skl[1].blue){cout<<"���������ʹ���������\n";return;}
				me.blue-=skl[1].blue;
			enemy.yz+=skl[1].yz;
			int sh=((rand()-skl[1].min)%skl[1].max+skl[1].min)-enemy.def*(enemy.state[3]>0?1.3:1);
			if(sh<0)sh=0;
			cout<<me.name<<"��"<<enemy.name<<"ʹ����"<<skl[1].name<<"ֻ��"<<enemy.name<<"˲�䱻��ס"
				<<"����"<<enemy.name<<"������"<<sh<<"���˺���";
			enemy.hp-=sh;
			enemy.hp=max(0,enemy.hp);
			return;
		}	
		void uxwzy(hero & me,hero & enemy)
		{
			if(me.blue<skl[2].blue){cout<<"���������ʹ���������\n";return;}
				me.blue-=skl[2].blue;
			enemy.yz+=skl[2].yz;
			int sh=((rand()-skl[2].min)%skl[2].max+skl[2].min)-enemy.def*(enemy.state[3]>0?1.3:1);
			if(sh<0)sh=0;
				cout<<me.name<<"��"<<enemy.name<<"������"<<skl[2].name<<""<<"һ�����۵Ļƹ��"<<me.name<<"���������������������"<<enemy.name<<"�����������"
				<<sh<<"���˺���\n";
			enemy.hp-=sh;
			enemy.hp=max(0,enemy.hp);
			return;
		}
		void   uyx(hero & me,hero & enemy)
		{
			if(me.blue<skl[3].blue)
			{
				cout<<"���������ʹ���������\n";
				return;
			}
			me.blue-=skl[3].blue;
			cout<<me.name<<"��"<<enemy.name<<"ʹ����"<<skl[3].name<<"��"<<me.name<<"ֻ��ԭ������һ��Ӱ��,"<<enemy.name<<"��Χһ�ڣ�ֻ�о�����һ��"<<me.name<<"˲������"<<enemy.name<<"���󣬶�ݺݵ�˦��ذ��ֱͱ"<<enemy.name; 
			int sh=(rand()-skl[3].min)%skl[3].max+skl[3].min-enemy.def*(enemy.state[3]>0?1.3:1);
			if(sh<0)
				sh=0;
			enemy.hp-=sh;
			enemy.hp=max(0,enemy.hp);
			cout<<enemy.name<<"�ܵ�"<<sh<<"���˺���\n";
			enemy.yz+=skl[3].yz;
		}
		void ucqqlsjshdfmlhldxfwsylxqn(hero & me,hero & enemy)
		{
			if(me.blue<skl[4].blue)
			{
				cout<<"���������ʹ���������\n";
				return;
			}
			me.blue-=skl[4].blue;
			int sh=(rand()-skl[4].min)%skl[4].max+skl[4].min-enemy.def*(enemy.state[3]>0?1.3:1);
			enemy.hp-=sh;
			enemy.yz+=skl[4].yz;
			if(sh<0)
			sh=0;
			cout<<me.name<<"��"<<enemy.name<<"ʹ����"<<skl[4].name<<",ֻ��һ�������"<<skl[4].name<<"��"<<me.name<<"��߷ɳ�"<<",������"<<enemy.name<<".�����"<<sh<<"���˺���\n";
			enemy.hp-=sh;
			enemy.hp=max(0,enemy.hp);
		}
		void  usls(hero & me,hero & enemy)
		{
			if(me.blue<skl[5].blue)cout<<"���������ʹ���������\n";
			me.blue-=skl[5].blue;
			int sh=(rand()-skl[5].min)%skl[5].max+skl[5].min-enemy.def*(enemy.state[3]>0?1.3:1);
			if(sh<0)
				sh=0;
			enemy.hp-=sh;
			enemy.hp=max(0,enemy.hp);
			cout<<me.name<<"��"<<enemy.name<<"ʹ����"<<skl[5].name<<"��"<<enemy.name<<"˲�䱻���ڵ�,���ö���,ͬʱ�ܵ�"<<sh<<"���˺�\n"; 
			enemy.yz+=skl[5].yz;
			
		}
		void uhf(hero & me,hero & t)
		{
			if(me.blue<skl[6].blue){cout<<"���������ʹ���������\n";return;}
				me.blue-=skl[6].blue;
				cout<<me.name<<"��������Ѫ3�غ�!\n"; 
			t.state[1]+=3;
			return;
		}
		void uts(hero & me,hero & t)
		{
			if(me.blue<skl[7].blue){cout<<"���������ʹ���������\n";return;}
				me.blue-=skl[7].blue;
				cout<<me.name<<"��ȫ������2�غ�!\n";
				me.state[2]+=2;
				me.state[3]+=2; 
		} 
	void make_skill()
	{ 
		skl[1].yz=2;
		skl[1].blue=30;
		skl[1].name="�������"; 
		skl[1].min=0;
		skl[1].max=50;	
		skl[1].p=uwlbf;
		skl[2].yz=0;
		skl[2].blue=20;
		skl[2].min=70;
		skl[2].max=150;
		skl[2].name="а������";
		skl[2].p=uxwzy;
		skl[3].blue=60;
		skl[3].min=200;
		skl[3].max=250;
		skl[3].yz=0;
		skl[3].name="ҹϮ"; 
		skl[3].p=uyx;
		skl[4].blue=55;
		skl[4].min=100;
		skl[4].max=200;
		skl[4].yz=0;
		skl[4].name="��ǿ�ɷ�β��������ǧ��"; 
		skl[4].p=ucqqlsjshdfmlhldxfwsylxqn;
		skl[5].blue=25;
		skl[5].min=75;
		skl[5].max=250;
		skl[5].yz=1;
		skl[5].name="˫����"; 
		skl[5].p=usls;
		skl[6].yz=0;
		skl[6].blue=40;
		skl[6].name="�ظ�"; 
		skl[6].p=uhf;
		skl[7].blue=30;
		skl[7].name="����";
		skl[7].p=uts;
	}
}
using namespace Skill;
void show_npc(int x,int y,hero & h)
{
	gotoxy(x,y);
	color(11);
	cout<<"         "<<h.name;
	gotoxy(x,++y);
	color(12);
	cout<<"Ѫ��: ";	
	cout.width(4);
	cout<<h.hp;
	color(9);
	cout<<"   ����ֵ: ";
	cout.width(4);
	cout<<h.blue;
	gotoxy(x,++y);
	color(14);
	cout<<"������: ";
	cout.width(4);
	cout<<h.atk;
	cout<<" ������: ";
	cout.width(4);
	cout<<h.def;
	gotoxy(x,++y);
	color(8);
	cout<<"����:";
	gotoxy(x,++y);
	 for(int i=1;i<=size;i++)
	 {
	 	if(h.skill[i]==1)
	 	{
	 		cout<<skl[i].name<<" "<<skl[i].blue;
	 		gotoxy(x,++y);
	 	}		
	 }
	color(6);
	cout<<"״̬:";
	bool ok=0;
	if(h.state[1]>0)cout<<"������Ѫ ",ok=1;
	if(h.state[2]>0)cout<<"���������� ",ok=1;
	if(h.state[3]>0)cout<<"���������� ",ok=1;
	if(h.state[4]>0)cout<<"������Ѫ ",ok=1;
	if(h.state[5]>0)cout<<"�������½� ",ok=1;
	if(h.state[6]>0)cout<<"�������½� ",ok=1;
	if(!ok)cout<<" ��";
	gotoxy(x,++y);	
	color(15);
	cout<<"--------------------------"; 	
}
void make_hero(hero & t)
{
	t.atk=(rand()-20)%60+30;
	t.def=(rand()-15)%70+15;
	t.hp=(rand())%500+300;
	t.blue=(rand()-150)%100+60;
	t.hl=(rand()-3)%7+3;
	for(int i=0;i<maxn;i++)t.state[i]=0,t.skill[i]=0;
	for(int i=4;i>0;i--)
	{
		int k=(rand()-1)%size+1;
		if(t.skill[k]==1){i++;continue;}
		t.skill[k]=1;
	}
}
void show_string(int x,int y,string & s)
{
	gotoxy(x,y);
	color(3);
	cout<<s; 
	color(15);
}
void change(int x,int y,int n,int p)
{
	gotoxy(x,y);
	
	if(p==1)
		color(12);
	else
		color(9);
	cout.width(4);
	cout<<n;
	color(15);
	return;
}
int bx1=3,by1=1,bx2=21,by2=1,fx1=10,fx2=28,fy1=1,fy2=1,hhx=12,hhy=11;
void flush(int x,int y,char ch,int cs,int line)
{
	gotoxy(x,y);
	for(int j=1;j<=line;j++)
	{
		for(int i=1;i<=cs;i++)cout<<ch;
		cout<<endl;
	}
	
}
const int qp=100;
const int ql=25;
void ATK (hero & a,hero &d,bool flag)
{
	gotoxy(0,10);
	flush(0,10,' ',qp,ql);
	gotoxy(0,10);
	char opr;
	color(15);
	cout<<"������ ";
	color(12);
	cout<<a.name;
	color(15);
	cout<<" �Ĺ���ʱ��!"<<endl
	    <<"������Ҫ��ʲô"<<endl;
	color(11);
	cout<<"1 ���� ";
	color(12);
	cout<<"2 ʹ�ü���"<<endl;
	color(13);
	gotoxy(30,10);
	qxgb();
	opr=getch();
	flush(0,10,' ',qp,ql);
	gotoxy(0,10);
	if(opr!='1' and opr!='2')
	{
		cout<<"������벻�ԣ����������룡";
		Sleep(500);
		flush(0,10,' ',qp,ql);
		return ATK(a,d,flag); 
	}
	if (opr=='1'){
		color(12);
		cout<<a.name;
		color(13);
		cout<<" ������ ";
		color(12);
		cout<<d.name;
		color(13);
		cout<<"! �����";
		int sh=a.atk*(a.state[2]>0?1.3:1)-d.def*(d.state[3]>0?1.3:1);
		if(sh<0)sh=0;
		cout<<sh<<"���˺���";
		d.hp=d.hp-sh;
		d.hp=max(0,d.hp);
		if(flag)
			change(bx1,by1,d.hp,1);
		else change(bx2,by2,d.hp,1);		
	}
	else {
		r:
		flush(0,10,' ',qp,25);
		int x=0,y=10;
		gotoxy(x,y);
		 	  for(int i=1;i<=size;i++)
			 {
			 	if(a.skill[i]==1)
			 	{
			 		cout<<i<<' '<<skl[i].name<<" "<<skl[i].blue;
			 		gotoxy(x,++y);
			 	}		
			 }
			 cout<<"������Ҫʹ���ĸ����ܣ�\n";
			 opr=getch();
			 if(!a.skill[opr-'0'])
			 {
			 	cout<<"��û��������ܣ�\n";
			 	Sleep(500);
				 goto r; 
			 }
			 cout<<"������ʹ�ü��ܵĶ���\n";
			 u:
			 cout<<"1 �Լ�         0 ����\n";
			 char t;
			 while(1)
			 {
			 	t=getch();
			 	if(t=='1'||t=='0')break;
			 }
			 if(t=='1')
			 	skl[opr-'0'].p(a,a);
			 else 
			 	skl[opr-'0'].p(a,d);
			 	if(!flag)
			 		change(fx1,fy1,a.blue,0);
			 	else 
			 		change(fx2,fy2,a.blue,0);
			 	if(flag)
			 	{
			 		change(bx1,by1,d.hp,1);
			 		change(bx2,by2,a.hp,1);
			 	}	
				else
				{
					change(bx2,by2,d.hp,1);
					change(bx1,by1,a.hp,1);
				}
	}
	color(15);
	Sleep(2000);
	gotoxy(0,10);
	flush(0,10,' ',qp,ql);
}
int replay=0;
void end (hero p,hero winner)
{
	gotoxy(0,10);
	color(10);
	cout<<"��Ϸ����!"<<endl;
	color(8);
	cout<<p.name;
	color(10);
	cout<<" ����"<<endl<<"ʤ���� ";
	color(12);
	cout<<winner.name<<"!";
	color(10);
	cout<<"�����Ƿ�����?"<<endl
	    <<"Y �� N ��";
	char re=getch();
	if (re=='Y'||re=='y')replay=true;
}
void play ()
{
	replay=false;
	hero p1,p2;
	system("cls");
	color(14);
	cout<<"����ϷΪ˫����Ϸ"<<endl;
	color(11);
	cout<<"�������һ����ҵ�����"<<endl;
	color(12);
	cin>>p1.name;
	color(11);
	cout<<"Ȼ������ڶ�����ҵ�����"<<endl;
	color(12);
	cin>>p2.name;
	color(21);	
	cout<<"����Ϊ��ɫ���似��..."<<endl;
	make_hero(p1);
	make_hero(p2);
	Sleep(100);
	color(7);
	cout<<"ս����ʼ!"<<endl;
	Sleep(1000);
	system("cls");
	show_npc(0,0,p1);
	show_npc(18,0,p2);
	gotoxy(0,10);
	while (true){
		if(p1.yz==0)
			ATK (p1,p2,0);
		else 
		{
			p1.yz--;
			gotoxy(0,18);
			cout<<"����"<<p1.name<<"�ܵ�ѣ��Ч���������������غ�\n"; 
			Sleep(500);
			gotoxy(0,10);
		}
		if (p2.hp==0){end(p2,p1);break;}
		if(p2.yz==0)
			ATK (p2,p1,1);
		else
		{
			p2.yz--;
			gotoxy(0,18);
			cout<<"����"<<p2.name<<"�ܵ�ѣ��Ч���������������غ�\n"; 
			Sleep(500);
			gotoxy(0,10);
		}		
		if (p1.hp==0){end(p1,p2);break;}
		if(p1.state[1]>0)p1.hp+=100;
		if(p2.state[1]>0)p2.hp+=100; 
		for(int i=1;i<=size;i++)
		{
			if(p1.state[i]>0)p1.state[i]--;
			if(p2.state[i]>0)p2.state[i]--;
		}
		p1.blue+=p1.hl;p2.blue+=p2.hl;
	}
	if (replay)play();
}
int main()
{
	cout.setf(ios::left);
	show_start();
	char ch;
	ch=getch();
	if(ch!='1')
	{
		return 0;
	}
	make_skill();
	play();
	color(15);
	return 0;
}
