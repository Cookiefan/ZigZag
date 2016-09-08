#include <bits/stdc++.h>
 
using namespace std;
 
#define N 50005
 
#define lson rt << 1
#define rson rt << 1 | 1
#define Pair pair<double, Node>
#define Sqrt2(x) (x) * (x)
 
int n, k, idx;
 
struct Node
{
    int feature[5];     //定义属性数组
    Node *lc, *rc;
    bool operator < (const Node &u) const
    {
        return feature[idx] < u.feature[idx];
    }
}_data[N];   //_data[]数组代表输入的数据
 
priority_queue<Pair> Q;     //队列Q用于存放离p最近的m个数据
 
class KDTree{
 
    public:
        Node* Build(int, int, int);     //建树
        void Query(Node*, Node, int, int);    //查询
        Node *rot;      //用于标记某个节点是否存在，1表示存在，-1表示不存在
}kd;
 
//建树步骤，参数dept代表树的深度
Node* KDTree::Build(int l, int r, int dept)
{
    if(l > r) return NULL;
    //当前节点的孩子暂时标记不存在
    Node *now=new Node();
    idx = dept % k;                 //按照编号为idx的属性进行划分
    int mid = (l + r) >> 1;
    nth_element(_data + l, _data + mid, _data + r + 1);   //nth_element()为STL中的函数
    memcpy(now->feature, _data[mid].feature, sizeof(now->feature));
    now->lc=Build(l, mid - 1, dept + 1);  //递归左子树
    now->rc=Build(mid + 1, r, dept + 1);  //递归右子树
    return now;
}
 
//查询函数，寻找离p最近的m个特征属性
void KDTree::Query(Node *rt, Node p, int m, int dept)
{
    if (rt==NULL)  return; //不存在的节点不遍历
    Pair cur(0, *rt);       //获取当前节点的数据和到p的距离
    for(int i = 0; i < k; i++)
        cur.first += Sqrt2(cur.second.feature[i] - p.feature[i]);
    //cout<<cur.first<<endl;
    int dim = dept % k;          //跟建树一样，这样能保证相同节点的dim值不变
    bool fg = 0;                 //用于标记是否需要遍历右子树
    Node* x = rt->lc;
   	Node* y = rt->rc;
    if(p.feature[dim] >= rt->feature[dim]) //数据p的第dim个特征值大于等于当前的数据，则需要进入右子树
        swap(x, y);
    Query(x, p, m, dept + 1);      //如果节点x存在，则进入子树继续遍历
 
    //以下是回溯过程，维护一个优先队列
    if(Q.size() < m)   //如果队列没有满，则继续放入
    {
        Q.push(cur);
        Query(y, p, m, dept + 1);
    }
    else
    {
        if(cur.first < Q.top().first)  //如果找到更小的距离，则用于替换队列Q中最大的距离的数据
        {
            Q.pop();
            Q.push(cur);
        }
        if(Sqrt2(p.feature[dim] - rt->feature[dim] )< Q.top().first)
        {
            Query(y, p, m, dept + 1);
        }
    } 
        
}
 
//输出结果
void Print(Node data)
{
    for(int i = 0; i < k; i++)
        printf("%d%c", data.feature[i], i == k - 1 ? '\n' : ' ');
}
 
int main()
{
    // freopen("2.in","r",stdin);
    // freopen("2.out","w",stdout);
    while(scanf("%d%d", &n, &k)!=EOF)
    {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < k; j++)
                scanf("%d", &_data[i].feature[j]);
        kd.rot=kd.Build(0, n - 1, 0);
        int t, m;
        scanf("%d", &t);
        while(t--)
        {
            Node p;
            for(int i = 0; i < k; i++)
                scanf("%d", &p.feature[i]);
            scanf("%d", &m);
            while(!Q.empty()) Q.pop();   
            kd.Query(kd.rot, p, m, 0);
            printf("the closest %d points are:\n", m);
            Node tmp[25];
            for(int i = 0; !Q.empty(); i++)
            {
                tmp[i] = Q.top().second;
                Q.pop();
            }
            for(int i = m - 1; i >= 0; i--)
                Print(tmp[i]);
        }
    }
    return 0;
}