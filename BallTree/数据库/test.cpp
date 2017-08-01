#include <iostream>

#include<fstream>

#define N0 20
#define PAGE_SIZE 65536//0_65535
#define dot_num 51//��������� + 1��id 
#define rid_num (N0*2)//��rid���� 2*n0
#define ball_num_f 60//balltreenode��Ҫ����ļ������ݵĸ���10+2//50

#define demension  50

const char query_path[256] = "Netflix\\src\\query.txt";
const char output_path[256] = "Netflix\\dst\\answer.txt";
const char index_nane[256] = "Netflix\\index\\index.bin";
const char data_nane[256] = "Netflix\\src\\dataset.txt";


#define ball_Node_num (int)(PAGE_SIZE/((root->d+1)*N0*(slot_num)))//ÿ��ҳ������ݸ��� ���ڵ� ;���ٸ�float 
#define node_slot_size ball_num_f//(sizeof(float)* ball_num_f)//����ÿһ���ڵ��slot�Ĵ�С 
#include "BallTree.cpp"
#include "Utility.cpp"

//������ 
int countn=0;//ͳ�����нڵ�ĵ����� 
int count_node=0;//ͳ�����нڵ�ĵ����� 
int temcount=0;// 

using namespace std;

void inotrdercount( BallTreeNode* root, int & countn,int &count_ndoe);

int main() {
	//char ch;
	const int n = 17770;
	const int d  = 50;
	const int qn = 1000;
	
	BallTree test;

	float** data = 0;
	float** query = 0; 

	read_data(n, d, data, data_nane);

	int tem;
	
	test.buildTree(n, d, data);
	cout<<"buildtree success"<<endl;
	
	test.storeTree(index_nane);//�����ִ�У���n�ĵ�ֵ���ᷢ�ֽ��������� 
	cout<<"stortree success"<<endl;
	
	BallTree test1;
	test1.restoreTree(index_nane);
	cout<<"Heve restored tree"<<endl;
	
	cout<<"enter����to continues"<<endl;
	
	if (!read_data(qn, d, query, query_path));
		FILE* fout = fopen(output_path, "w");
	if (!fout) {
		printf("can't open %s!\n", output_path);
		//cin>>ch;
		return 1;
	}
	
	for (int i = 0; i < qn; i++) {
		int index = test1.mipSearch(d, query[i]);
		fprintf(fout, "%d\n", index);
		//int ch;
		//cin>>ch;
	}
	
	fclose(fout);
	
	cout<<"Search Success!!"<<endl;
	
	for (int i = 0; i < n; i++) {
		delete[] data[i];
	}

	for (int i = 0; i < qn; i++) {
		delete[] query[i];
	}
	return 0;
}

