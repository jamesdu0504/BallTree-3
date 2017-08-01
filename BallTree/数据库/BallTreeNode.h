#include"math.h"
#include<iostream>
using namespace std;
struct rid {
//	private:
public:
		int page;
		int slot;
		public:
		rid(int _page = -1,int _slot = -1) {
			page = _page;
			slot = _slot;
			}
		void set_rid(int _page,int _slot) {
			page = _page;
			slot = _slot;
			}

};

struct Query{
	float index;
	float maxproduct;
	Query(float in = -1, float max = -1){
		index = in;
		maxproduct = max;
	}
	void set(float in, float max){
		index = in;
		maxproduct = max;
	}
};

 
struct BallTreeNode
{
	//����������ÿ���ڵ���ֵ
	float **data;/*��ǰBall���������*/
	float *center;/*Ball������*/
	float radius;/*�뾶*/
	int D;/*��ǰBall�ܹ��ж��������� ����ҪС��N0*/ //�����ж��Ƿ�ΪҶ�ӽڵ� 
	int d;/*ÿ�������ж೤*/
	int node_num;//�ڵ��ţ�������ڵ�ô��ҳ�ţ�ÿ��Ҷ������ݸ�����slotռ���ֽڣ�sizeof(float)* 14; PAGE_SIZE/sizeof(float)/(sizeof(float)* (14-3))
	BallTreeNode*left;
	BallTreeNode*right;
	BallTreeNode();
	~BallTreeNode();
	BallTreeNode(float **&_data, int _D/*n*/, int _d);
	void getcenter();
	void getradius();

	rid left_rid,right_rid, list_rid;//���Һ��ӵ�����rid�����������Ĳ���Ч��list_rid(ָ������������е�Ķ�Ӧ��rid�ĵ�slot���ٶ�Ϊ20��rid))

};

BallTreeNode::BallTreeNode() {
	data = 0;
	center = 0;
	radius = 0;
	D = 0;
	d = 0;
	left = 0;
	right = 0;
	list_rid.page=-1;
	list_rid.slot=-1;
}
inline BallTreeNode::~BallTreeNode()//�ͷŴ���
{
//	cout<<"delete"<<endl;//�鿴��
	delete[]data;
}

BallTreeNode::BallTreeNode(float **&_data, int _D, int _d) {
		data = new float*[_D];//n
	for (int i = 0; i < _D; i++) {
		data[i] = new float[_d+1];//������1
		for (int j = 0; j < _d+1; j++) {
			data[i][j] = _data[i][j];
		}
	}
	D = _D;
	d = _d;
	//����һ������
	left = 0;
	right = 0;
	getcenter();
	getradius();
}

void BallTreeNode::getcenter() {
	center = new float[d];
	for (int i = 0; i < d; i++) {
		center[i] = 0;
	}
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < D; j++) {
			center[i] += data[j][i];
			//center[i] += data[i][j];���� 
		}
	}
	for (int i = 0; i < d; i++) {
		center[i] /= D;
	}
}

void BallTreeNode::getradius() {
	float max = 0;
	float temp = 0;
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < d; j++) {
			temp += (data[i][j] - center[j])*(data[i][j] - center[j]);
		}
		if (temp > max) {
			max = temp;
		}
		temp = 0;//��0������������ץ��
	}
	radius = sqrt(max);

}


float distance(float *a, float *b, int _d) {
	float res = 0.0;
	for (int i = 0; i < _d; i++) {
		res += (a[i] - b[i])*(a[i] - b[i]);
	}
	return sqrt(res);
}



