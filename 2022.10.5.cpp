#include<iostream>
using namespace std;

#define MaxInt 32767  //表示极大值，即无穷大
#define MVNum 20      //最大顶点数

typedef char VerTexType;//顶点的数据类型为字符型
typedef int ArcType;  //每条边的权值大小为整形

bool S[MVNum];   //标记顶点是否进入集合
int D[MVNum];    //用于记录最短路的长度
int P[MVNum];    //用于记录最短路径顶点的上一个顶点

typedef struct
{
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];  //邻接矩阵
	int vexnum, arcnum;  //图当前的顶点数和边的个数
}AMGraph;

int LocateVex(AMGraph G, VerTexType v)
{
	for (int i = 0; i < G.vexnum; ++i)
		if (G.vexs[i] == v)
			return i;
	        return -1;
}   //得到顶点存放的下标，例如0到1存放0，没有找到路径输出-1

void CreateUDN(AMGraph& G)
{
	int i, j, k;
	cout << "请输入总顶点数，总边数，以空格隔开：";  
	cin >> G.vexnum >> G.arcnum;   //输入总顶点，总边数
	cout << endl;
	
	cout << "输入点的名称：如a" << endl;
	for (i = 0; i < G.vexnum; ++i)
	{
		cout << "请输入第" << (i + 1) << "个点的名称：";  
		cin >> G.vexs[i];
	}   //在for循环下依次输入顶点的信息
	cout << endl;
	for (i = 0; i < G.vexnum; ++i)
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MaxInt;   //开始时全部初始化，边的权值都为最大值
	cout << "输入边依附的顶点和权值,如a b 7" << endl;
	for (k = 0; k < G.arcnum; ++k)
	{
		VerTexType v1, v2;
		ArcType w;
		cout << "请输入第" << (k + 1) << "条边的顶点和权值：";
		cin >> v1 >> v2 >> w;
		i = LocateVex(G, v1); j = LocateVex(G, v2);   //确定v1,v2在G中的位置
		G.arcs[i][j] = w;
	}
	cout << endl << "*****有限网G创建完成！*****" << endl;

}   //通过for 循环设置每条边连接的定点和权值

void ShowGraphArcs(AMGraph G)
{
	for (int i = 0; i < G.vexnum; ++i)
	{
		for (int j = 0; j < G.vexnum; ++j)
		{
			if (j != G.vexnum - 1)
			{
				if (G.arcs[i][j] != MaxInt)
					cout << G.arcs[i][j] << "\t";
				else
					cout << "∞" << "\t";
			}
			else
			{
				if (G.arcs[i][j] != MaxInt)
					cout << G.arcs[i][j] << endl;
				else
					cout << "∞" << endl;
			}
		}
	}
}

void ShortesPath_DIJ(AMGraph G, int v0)

{
	int v, i, w, min;
	int n = G.vexnum;
	for (v = 0; v < n; ++v)
	{
		S[v] = false;
		D[v] = G.arcs[v0][v];
		if (D[v] < MaxInt) P[v] = v0;
		else P[v] = -1;
	}
	S[v0] = true;
	D[v0] = 0;
	for (i = 1; i < n; ++i)
	{
		min = MaxInt;
		for (w = 0;w < n;++w)
			if (!S[w] && D[w] < min)
			{
				v = w;
				min = D[w];
			}
		S[v] = true;
		for (w = 0;w < n;++w)
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];
				P[w] = v;
			}
	}
}

void DisplayPath(AMGraph G, int begin, int temp)
{
	if (P[temp] == -1)
		return;
	DisplayPath(G, begin, P[temp]);
	cout << G.vexs[P[temp]] << "-->";
}

int main()
{
	cout << "**********算法6.10 迪杰斯特拉算法**********" << endl << endl;
	AMGraph G;
	CreateUDN(G);
	ShowGraphArcs(G);
	int startId;
	VerTexType start;
	cout << endl << "请依次输入起始点：";
	cin >> start;     //输入一个起始点
	startId = LocateVex(G, start);  //调用函数
	ShortesPath_DIJ(G, startId);

	for (int d = 0; d < G.vexnum; d++)
	{
		if (d != startId)
	 {
			cout << endl;
			cout << G.vexs[startId] << "到" << G.vexs[d] << "长度为：" << D[d];
			cout << "\t最短路径为：";
			DisplayPath(G, startId, d);
			cout << G.vexs[d] << endl;
		}
	}

	for (int i = 0; i < G.vexnum; i++)
	{
		cout << S[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		cout << D[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		cout << P[i] << "\t";
	}
	cout << endl;
	return 0;
}
