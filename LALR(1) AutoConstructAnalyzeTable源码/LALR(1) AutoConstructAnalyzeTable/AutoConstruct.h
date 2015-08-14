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
const string NULL_str = "ε";
const char mark_ch = '.';
struct node { string n_str; set<char> n_set; };
struct Go_node { char go_ch; int to; };
struct For_Tab_node { char meet; string Judge; int Go; };

class AutoConstruct
{
private:
	set<char> allChar; // 存储文法中出现的所有终结符和非终结符
	char myBegin;  // 开始符号
	vector<string> Grammar[MAX_Char_Num];  // 存储文法（式子左边字母排序）
	int Vn_Num;  // 非终结符个数
	int Vt_Num;  // 终结符个数
	
	vector<string> Num_Gra; // 存储文法 （为文法中的每个表达式标号）
	set<char> myFirst[MAX_Char_Num]; // 存储 FIRST 集合
	bool isOk[MAX_Char_Num]; // 在产生 FIRST 集合时，判断相应非终结符是否已产生 FIRST 集合完毕
	void getVt();  // 获取终结符
	vector<node> DFA[MAX_Status];  // 存储 DFA 状态
	int Judge_Same(int sta); // 求 DFA 各个状态时，判断当前要插入的状态是否和之前状态重叠
	void Goto();
	string Let_Begin; // 新产生式 S-> myBegin
	queue<int> que_for_go;
	int Total_sta; // 总的状态个数
	vector<Go_node> GoTo[MAX_Status];  // 存储 DFA 各个状态之间的转换关系
	void Get_Table(); // 建立分析表
	int Merge(int sta);

	//////////////////////////////////////////////////////////////////////////
	void Get_Num_Gra(); // 获得 Num_Gra
	bool JudgeChar(char c); // 判断是否为终结符
	bool JudgeNullStr(string str, int pos, int &ptr); //判断是否遇到空串，并给出对空串的处理方法
	bool Get_FIRST_Insert(int ptr, string str, int pos); // 辅助求First集
	void Get_FIRST_Nonterminal(); // 求First集
	void Get_FIRST_Insert_For_Clo(int ptr, string str, set<char> &set_Ch); // 辅助求闭包 First集
	set<char> Get_First(string str); // 求闭包时，需用的 FIRST集
	void Closure(node nd, int Sta); // 构造闭包
	//////////////////////////////////////////////////////////////////////////
	friend bool operator ==(const node &n1, const node &n2);
public:
	vector<For_Tab_node> Action[MAX_Status];
	vector<For_Tab_node> GOTO[MAX_Status];
	set<char> Get_Vn; // 获取非终结符
	set<char> Get_Vt; // 获取终结符
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

