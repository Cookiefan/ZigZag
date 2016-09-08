#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#define oo 1000000007
#define maxn 8000

using namespace std;

class Node
{
public:
	Node *c[2];
	int h,s,val;
	Node(){}
	Node(int val):h(0),s(1),val(val){c[0]=c[1]=NULL;}
};

class AVL
{
public:
	Node *rot;
	AVL(){ rot=NULL; }
	int height(Node* x)
	{
		return (x==NULL)?-1:x->h;
	}

	int size(Node* x)
	{
		return (x==NULL)?0:x->s;
	} 

	void update(Node* x)
	{
		x->h=max(height(x->c[0]),height(x->c[1]))+1;
		x->s=size(x->c[0])+size(x->c[1])+1;
	}

	Node* Find(Node* t, int z)
	{
		if (t==NULL)
			return NULL;
		else
		{
			if (z==t->val) return t;
			if (z<t->val) return Find(t->c[0], z);
			if (z>t->val) return Find(t->c[1], z);
		}
	}

	Node* Select_Min(Node* t, int k)
	{
		if (k>size(t)) return NULL;
		if (k==size(t->c[0])+1) return t;
		if (k<size(t->c[0])+1)
			return Select_Min(t->c[0], k);
		else
			return Select_Min(t->c[1], k-size(t->c[0])-1);
	}

	void Rotate(Node* &x, int p)//p=0 left;p=1 right;
	{
		Node* y=x->c[p^1];
		x->c[p^1]=y->c[p];
		y->c[p]=x;
		update(x);
		update(y);
		x=y;
	}

	void Zig_Zag(Node* &x, int p)//p=0 left-right;p=1 right-left;
	{
		Rotate(x->c[p],p);
		Rotate(x,p^1);
	}

	void Insert(Node* &t, int z)
	{
		if (t==NULL) t=new Node(z);
		else
		{
			if (z<=t->val)
			{
				Insert(t->c[0], z);
				if (height(t->c[0])-height(t->c[1])==2)
				{
					if (z<=t->c[0]->val)
						Rotate(t, 1);
					else
						Zig_Zag(t, 0);
				}
			}
			else
			{
				Insert(t->c[1], z);
				if (height(t->c[1])-height(t->c[0])==2)
				{
					if (z>t->c[1]->val)
						Rotate(t, 0);
					else
						Zig_Zag(t, 1);
				}
			}
			update(t);
		}
	}
	void clear(Node* t)
	{
		if (t->c[0]!=NULL) clear(t->c[0]);
		if (t->c[1]!=NULL) clear(t->c[1]);
		delete t;
	}
};

int n;
int a[maxn];
map<int, int> ans;

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		ans.clear();
		
		for (int i=1;i<=n;i++)
		{
			AVL s;
			for (int j=i;j<=n;j++)
			{
				// cout<<i<<' '<<j<<' ';
				s.Insert(s.rot, a[j]);
				if ((j-i+1)%2==1)
				{
					int x=s.Select_Min(s.rot, (j-i)/2+1)->val;
					// cout<<x<<endl;
					if (ans.find(x)==ans.end()) ans[x]=0;
					ans[x]++;
				}
				else
				{
					int x=s.Select_Min(s.rot, (j-i)/2+1)->val;
					int y=s.Select_Min(s.rot, (j-i)/2+2)->val;
					// cout<<x<<' '<<y<<endl;
					if ((x+y)%2==0)
					{
						if (ans.find((x+y)/2)==ans.end()) ans[(x+y)/2]=0;
						ans[(x+y)/2]++;
					}
				}
			}
			s.clear(s.rot);
		}
		for (int i=1;i<=n;i++)
			if (ans.find(a[i])!=ans.end())
				printf(i==n?"%d\n":"%d ",ans[a[i]]);
			else
				printf(i==n?"%d\n":"%d ",0);
	}
	return 0;
}