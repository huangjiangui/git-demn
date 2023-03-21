#include<iostream>
using namespace std;

#define MaxInt 32767  //��ʾ����ֵ���������
#define MVNum 20      //��󶥵���

typedef char VerTexType;//�������������Ϊ�ַ���
typedef int ArcType;  //ÿ���ߵ�Ȩֵ��СΪ����

bool S[MVNum];   //��Ƕ����Ƿ���뼯��
int D[MVNum];    //���ڼ�¼���·�ĳ���
int P[MVNum];    //���ڼ�¼���·���������һ������

typedef struct
{
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];  //�ڽӾ���
	int vexnum, arcnum;  //ͼ��ǰ�Ķ������ͱߵĸ���
}AMGraph;

int LocateVex(AMGraph G, VerTexType v)
{
	for (int i = 0; i < G.vexnum; ++i)
		if (G.vexs[i] == v)
			return i;
	        return -1;
}   //�õ������ŵ��±꣬����0��1���0��û���ҵ�·�����-1

void CreateUDN(AMGraph& G)
{
	int i, j, k;
	cout << "�������ܶ��������ܱ������Կո������";  
	cin >> G.vexnum >> G.arcnum;   //�����ܶ��㣬�ܱ���
	cout << endl;
	
	cout << "���������ƣ���a" << endl;
	for (i = 0; i < G.vexnum; ++i)
	{
		cout << "�������" << (i + 1) << "��������ƣ�";  
		cin >> G.vexs[i];
	}   //��forѭ�����������붥�����Ϣ
	cout << endl;
	for (i = 0; i < G.vexnum; ++i)
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MaxInt;   //��ʼʱȫ����ʼ�����ߵ�Ȩֵ��Ϊ���ֵ
	cout << "����������Ķ����Ȩֵ,��a b 7" << endl;
	for (k = 0; k < G.arcnum; ++k)
	{
		VerTexType v1, v2;
		ArcType w;
		cout << "�������" << (k + 1) << "���ߵĶ����Ȩֵ��";
		cin >> v1 >> v2 >> w;
		i = LocateVex(G, v1); j = LocateVex(G, v2);   //ȷ��v1,v2��G�е�λ��
		G.arcs[i][j] = w;
	}
	cout << endl << "*****������G������ɣ�*****" << endl;

}   //ͨ��for ѭ������ÿ�������ӵĶ����Ȩֵ

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
					cout << "��" << "\t";
			}
			else
			{
				if (G.arcs[i][j] != MaxInt)
					cout << G.arcs[i][j] << endl;
				else
					cout << "��" << endl;
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
	cout << "**********�㷨6.10 �Ͻ�˹�����㷨**********" << endl << endl;
	AMGraph G;
	CreateUDN(G);
	ShowGraphArcs(G);
	int startId;
	VerTexType start;
	cout << endl << "������������ʼ�㣺";
	cin >> start;     //����һ����ʼ��
	startId = LocateVex(G, start);  //���ú���
	ShortesPath_DIJ(G, startId);

	for (int d = 0; d < G.vexnum; d++)
	{
		if (d != startId)
	 {
			cout << endl;
			cout << G.vexs[startId] << "��" << G.vexs[d] << "����Ϊ��" << D[d];
			cout << "\t���·��Ϊ��";
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
