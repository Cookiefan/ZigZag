#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#define MAXN 1205
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;

namespace Leftist_Tree {
typedef long long LL;
int num = 0;
struct HeapNode {
	HeapNode *left, *right;
	int hi, head;
	LL value;
	int height(){
		if (this == NULL)
			return 0;
		else
			return hi;
	}
	HeapNode() {
		left = right = NULL;
	}
	~HeapNode(){
		left = right = NULL;
	}
};
HeapNode* node;
void init(int scale){
	node = new HeapNode[scale];
	num = 0;
}
HeapNode* newnode(LL _value = 0, int _head = -1){
	HeapNode *tmp = &node[num++];
	tmp->value = _value;
	tmp->head = _head;
	tmp->hi = 0;
	// tmp->id = num;
	return tmp;
}
HeapNode* push(HeapNode* p, HeapNode*q){
	if (p == NULL){
		return q;
	} else if (q == NULL){
		return p;
	} else {
		if (p->value > q->value){
			swap(p, q);
		}
		p->right = push(p->right, q);
		if (p->left->height() < p->right->height()){
			swap(p->left, p->right);
		}
		p->hi = p->right->height() + 1;
		return p;
	}
}

HeapNode* merge(HeapNode* p, HeapNode* q){
	if (p == NULL){
		return q;
	} else if (q == NULL){
		return p;
	} else {
		if (p->value > q->value){
			swap(p, q);
		}
		HeapNode* tmp = newnode();
		*tmp = *p;
		tmp->right = merge(p->right, q);
		if (tmp->left->height() < tmp->right->height()){
			swap(tmp->left, tmp->right);
		}
		tmp->hi = tmp->right->height() + 1;
		return tmp;
	}
}

void clear(){
	delete [] node;
}

// void display(HeapNode *cur){
// 	if (cur == NULL){
// 		cout<<"NULL!\n";
// 		return ;
// 	}
// 	int ll = -1, rr = -1, pp = -1;
// 	if (cur->left != NULL)
// 		ll = cur->left->id;
// 	if (cur->right != NULL)
// 		rr = cur->right->id;
// 	printf("id = %d, value = %d, left = %d, right = %d, pre = %d\n", cur->id, cur->value, ll, rr, cur->head);
// 	display(cur->left);
// 	display(cur->right);
// }

}//Leftist_Tree

namespace Graph {
	using Leftist_Tree::HeapNode;
	typedef long long LL;
	typedef pair<int, int> pii;
	typedef pair<LL, int> pli;
	typedef pair<LL, Leftist_Tree::HeapNode*> pln;
	int n, m;
	HeapNode* root[MAXN];

	struct Edge{
		int tail;
		LL value;
		Edge(int _tail, LL _value){
			tail = _tail;
			value = _value;
		}
	};
	vector<Edge> outedge[MAXN];
	void addedge(int x, int y, LL z){
		outedge[x].push_back(Edge(y, z));
	}
	void clear(){
		for (int i = 0; i < n; i++){
			outedge[i].clear();
			root[i] = NULL;
		}
	}
	LL dis[MAXN];
	bool vis[MAXN];
	pii pre[MAXN];
	void dijkstra(int source){
		priority_queue<pli> que;
		memset(vis, 0, sizeof(vis));
		memset(dis, 0x3f, sizeof(dis));
		dis[source] = 0;
		pre[source] = pii(source, -1);
		que.push(pli(0, source));
		while (!que.empty()){
			int cur = que.top().second;
			que.pop();
			if (vis[cur]){
				continue;
			}
			vis[cur] = 1;
			for (int i = 0; i < outedge[cur].size(); i++){
				int nex = outedge[cur][i].tail;
				if (dis[nex] > dis[cur] + outedge[cur][i].value){
					dis[nex] = dis[cur] + outedge[cur][i].value;
					pre[nex].first = cur;
					pre[nex].second = i;
					que.push(pli(-dis[nex], nex));
				}
			}
		}
	}

	void build(int source){
		for (int cur = 0; cur < n; cur++){
			for (int j = 0; j < outedge[cur].size(); j++){
				int nex = outedge[cur][j].tail;
				if (pre[nex].first == cur && pre[nex].second == j) continue;
				LL edgevalue = outedge[cur][j].value;
				HeapNode *tmp = Leftist_Tree::newnode(dis[cur] + edgevalue - dis[nex], cur);
				root[nex] = Leftist_Tree::push(root[nex], tmp);
			}
		}
		queue<int> que;
		que.push(source);
		while (!que.empty()){
			int cur = que.front();
			que.pop();
			for (int j = 0; j < outedge[cur].size(); j++){
				int nex = outedge[cur][j].tail;
				if (pre[nex].first == cur && pre[nex].second == j){
					que.push(nex);
					root[nex] = Leftist_Tree::merge(root[cur], root[nex]);
				}
			}
		}
	}

	LL getksp(int target, int k){
		LL ans;
		if (dis[target] >= INF){
			return -1;
		}
		if (k == 1){
			return dis[target];
		} else {
			priority_queue<pln> que;
			k--;
			if (root[target] != NULL){
				que.push(pln(-dis[target] - root[target]->value, root[target]));
			}
			for (int i = 1; i <= k; i++){
				if (que.empty())
					return -1;
				pln cur = que.top();
				LL cur_dist = -cur.first;
				ans = cur_dist;
				HeapNode *cur_node = cur.second;
				que.pop();
				if (root[cur_node->head] != NULL){
					que.push(pln(-cur_dist - root[cur_node->head]->value, root[cur_node->head]));
				}
				if (cur_node->left != NULL){
					que.push(pln(-cur_dist + cur_node->value - cur_node->left->value, cur_node->left));
				}
				if (cur_node->right != NULL){
					que.push(pln(-cur_dist + cur_node->value - cur_node->right->value, cur_node->right));
				}
			}
			return ans;
		}
	}
}//Graph

int main()
{
	int x, y, z;
	int s, t, k;
	// freopen("ksp.in","r",stdin);
	// freopen("ksp.out","w",stdout);
	using Graph::n;
	using Graph::m;
	while (~scanf("%d %d", &n, &m)){
		Leftist_Tree::init(m*22);
		for (int i = 0; i < m; i++){
			scanf("%d %d %d", &x, &y, &z);
			x--; y--;
			Graph::addedge(x, y, z);
		}
		scanf("%d %d %d", &s, &t, &k);
		s--; t--;
		if (s == t) k++;
		Graph::dijkstra(s);
		// for (int i = 0; i < n; i++){
		// 	cout << i << ' ' << Graph::dis[i] << endl;
		// }
		Graph::build(s);
		// cout<<"ok!"<<endl;
		// for (int i = 0; i < n; i++){
		// 	printf("heap %d:\n", i);
		// 	display(Graph::root[i]);
		// }
		// for (int i = 1; i <= k; i++)
			// cout<<Graph::getksp(t, i)<<endl;
		cout<<Graph::getksp(t, k)<<endl;
		Graph::clear();
		Leftist_Tree::clear();
	}
	return 0;
}
