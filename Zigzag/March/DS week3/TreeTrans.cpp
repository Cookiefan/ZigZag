#include <bits/stdc++.h>
using namespace std;

struct Node
{
	vector<Node*> son;
	int val;
	Node(){ son.clear(); }
};

typedef Node Tree;
typedef vector<Tree*> Forest;

Tree *trans(Forest now)
{
	Tree *btree=now[0];
	now.erase(0);
	Forest tmp;
	for (int num=btree->son.size(), i=0; i<num;i++)
		tmp.push_back(btree->son[i]);
	btree->son.clear();
	if (!tmp.empty()) btree->son.push_back(trans(tmp));
	if (!now.empty()) btree->son.push_back(trans(now));
	return btree;
}

int main()
{

	return 0;
}