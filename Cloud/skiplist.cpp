#include <bits/stdc++.h>
using namespace std;

struct Node
{
	Node *nx,*dw;
	int key,val;
	Node(){}
	Node(Node *nx, Node *dw, int key, int val):nx(nx),dw(dw),key(key),val(val){}
};

int cnt;

struct SkipList
{
	Node *st[100];
	int MAX_LEV;
	void build()
	{
		MAX_LEV=1;
		st[1]=new Node(NULL,NULL,-1,0);
	}
	Node *find(int x)
	{
		Node *now=st[MAX_LEV];
		for (int i=MAX_LEV;i;i--)
		{
			while (now->nx!=NULL && x>now->nx->val) now=now->nx,cnt++;
			if (now->dw!=NULL) now=now->dw;
			else return now->nx;
		}
	}
	int rand_lev()
	{
		int x=1;
		while (rand()%2==0) x++;
		return x;
	}
	void add(int p, int x)
	{
		int lev=rand_lev();
		while (lev>MAX_LEV)
		{
			MAX_LEV++;
			st[MAX_LEV]=new Node(NULL,st[MAX_LEV-1],-1,0);
		}
		Node *now=st[MAX_LEV],*tmp=NULL,*last=NULL;
		for (int i=MAX_LEV;i;i--)
		{
			while (now->nx!=NULL && x>now->nx->val) now=now->nx;
			if (i<=lev)
			{
				tmp=new Node(now->nx,NULL,p,x);
				now->nx=tmp;
				if (last!=NULL) last->dw=tmp;
				last=tmp;
			}
			if (now->dw!=NULL) now=now->dw;
			else return;
		}

	}
	void remove(int x)
	{
		Node *now=st[MAX_LEV],*tmp;
		for (int i=MAX_LEV;i;i--)
		{
			while (now->nx!=NULL && x>now->nx->val) now=now->nx;
			if (now->nx!=NULL && now->nx->val==x)
			{
				tmp=now->nx;
				now->nx=now->nx->nx;
				delete tmp;
			}
			if (now->dw!=NULL) now=now->dw;
			else return;
		}
	}
	void display()
	{
		printf("SkipList:\n");
		for (int i=MAX_LEV;i;i--)
		{
			Node *now=st[i];
			while (now!=NULL)
			{
				printf("%d-->",now->val);
				now=now->nx;
			}
			printf("NULL\n");
		}
	}
};

int main()
{
	srand(time(0));
	SkipList S;
	S.build();
	int n=1000000;
	cnt=0;
	for (int i=1;i<=n;i++) S.add(i,rand()%n+1);
	cout<<S.MAX_LEV<<endl;
	for (int i=1;i<=n;i++) S.remove(rand()%n+1);
	return 0;
}