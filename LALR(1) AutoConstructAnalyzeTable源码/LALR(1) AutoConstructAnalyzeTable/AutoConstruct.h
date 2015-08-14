#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <string>
#include <fstream>
using namespace std;
typedef set<char>::iterator Set_Ch_Itr;
typedef vector<string>::iterator Vec_Str_Itr;
const int MAX_Char_Num = 26;
const int MAX_Status = 100;
const char Null_str_char = '?';
const string NULL_str = "��";
const char mark_ch = '.';
struct node { string n_str; set<char> n_set; };
struct Go_node { char go_ch; int to; };
struct For_Tab_node { char meet; string Judge; int Go; };

class AutoConstruct
{
private:
	set<char> allChar; // �洢�ķ��г��ֵ������ս���ͷ��ս��
	char myBegin;  // ��ʼ����
	vector<string> Grammar[MAX_Char_Num];  // �洢�ķ���ʽ�������ĸ����
	int Vn_Num;  // ���ս������
	int Vt_Num;  // �ս������
	
	vector<string> Num_Gra; // �洢�ķ� ��Ϊ�ķ��е�ÿ�����ʽ��ţ�
	set<char> myFirst[MAX_Char_Num]; // �洢 FIRST ����
	bool isOk[MAX_Char_Num]; // �ڲ��� FIRST ����ʱ���ж���Ӧ���ս���Ƿ��Ѳ��� FIRST �������
	void getVt();  // ��ȡ�ս��
	vector<node> DFA[MAX_Status];  // �洢 DFA ״̬
	int Judge_Same(int sta); // �� DFA ����״̬ʱ���жϵ�ǰҪ�����״̬�Ƿ��֮ǰ״̬�ص�
	void Goto();
	string Let_Begin; // �²���ʽ S-> myBegin
	queue<int> que_for_go;
	int Total_sta; // �ܵ�״̬����
	vector<Go_node> GoTo[MAX_Status];  // �洢 DFA ����״̬֮���ת����ϵ
	void Get_Table(); // ����������
	int Merge(int sta);

	//////////////////////////////////////////////////////////////////////////
	void Get_Num_Gra(); // ��� Num_Gra
	bool JudgeChar(char c); // �ж��Ƿ�Ϊ�ս��
	bool JudgeNullStr(string str, int pos, int &ptr); //�ж��Ƿ������մ����������Կմ��Ĵ�����
	bool Get_FIRST_Insert(int ptr, string str, int pos); // ������First��
	void Get_FIRST_Nonterminal(); // ��First��
	void Get_FIRST_Insert_For_Clo(int ptr, string str, set<char> &set_Ch); // ������հ� First��
	set<char> Get_First(string str); // ��հ�ʱ�����õ� FIRST��
	void Closure(node nd, int Sta); // ����հ�
	//////////////////////////////////////////////////////////////////////////
	friend bool operator ==(const node &n1, const node &n2);
public:
	vector<For_Tab_node> Action[MAX_Status];
	vector<For_Tab_node> GOTO[MAX_Status];
	set<char> Get_Vn; // ��ȡ���ս��
	set<char> Get_Vt; // ��ȡ�ս��
	AutoConstruct();
	~AutoConstruct();
	void getInfile(string inputFile);
	void ConstructTable();
	int getTotalSta();
	char getBegin();
	string Get_FIRST_View();
	string Get_Closure_View();
	string Get_Goto_View();
};

