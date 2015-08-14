#include "stdafx.h"
#include "AutoConstruct.h"


AutoConstruct::AutoConstruct()
{
	memset(isOk, true, sizeof(isOk));
	Let_Begin = "";
	Let_Begin += "S->";
	Total_sta = 0;
}


AutoConstruct::~AutoConstruct()
{
}

bool operator ==(const node &n1, const node &n2){
	if (n1.n_str != n2.n_str) return false;
	if (n1.n_set.size() != n2.n_set.size()) return false;
	Set_Ch_Itr t_set_ch_i = n1.n_set.begin();
	for (; t_set_ch_i != n1.n_set.end(); t_set_ch_i++) {
		if (n2.n_set.end() == n2.n_set.find(*t_set_ch_i)) {
			return false;
		}
	}
	return true;
}



void AutoConstruct::getVt() {
	Set_Ch_Itr it;
	for (it = allChar.begin(); it != allChar.end(); ++it) {
		if (Get_Vn.end() == Get_Vn.find(*it)) {
			Get_Vt.insert(*it);
		}
	}
}


void AutoConstruct::getInfile(string inputFile) {
	ifstream infile;
	infile.open(inputFile);
	string str;
	int pos = -1;
	while (getline(infile, str)) {
		Num_Gra.push_back(str);
		for (int i = 0; i < str.size(); i++) {
			if ('-' != str[i] && '>' != str[i] && '|' != str[i]) { allChar.insert(str[i]); }
		}
		if (-1 == pos) myBegin = str[0];
		string t_str;
		pos = str[0] - 'A';
		Get_Vn.insert(str[0]);
		for (int i = 0; i < 3; i++) {
			t_str += str[i];
		}
		for (int j = 3; j < str.size(); j++) {
			string str1 = "";
			while (j < str.size() && '|' != str[j]) {
				str1 += str[j];
				j++;
			}
			Grammar[pos].push_back(t_str + str1);
		}
	}
	Vn_Num = Get_Vn.size();
	Vt_Num = allChar.size() - Get_Vn.size();
	getVt();
	Get_Vt.insert('#');
	infile.clear();
	infile.close();
	//Get_Num_Gra();
}

void AutoConstruct::Get_Num_Gra() {
	for (int i = 0; i < MAX_Char_Num; i++) {
		for (int j = 0; j < Grammar[i].size(); j++) {
			Num_Gra.push_back(Grammar[i][j]);
		}
	}
}

bool AutoConstruct::JudgeChar(char c)
{
	if (c >= 'A' && c <= 'Z') return true;
	else return false;
}

// 判断是否遇到空串，并给出对空串的处理方法
bool AutoConstruct::JudgeNullStr(string str, int pos, int &ptr) {
	if (ptr == str.find("ε")) {
		ptr += 2;
		myFirst[pos].insert(Null_str_char);
		return true;
	}
	return false;
}

// 构建First集合
bool AutoConstruct::Get_FIRST_Insert(int ptr, string str, int pos)
{
	if (str.size() == ptr) {
		// 读到字符串尾部，将空串放入 FIRST 集合
		myFirst[pos].insert(Null_str_char);
		return true;
	}
	if (!JudgeChar(str[ptr])) {
		// 终结符直接放入 FIRST 集合
		myFirst[pos].insert(str[ptr]);
		return true;
	}
	else {
		// 遇非终结符的处理办法
		int t_c = str[ptr] - 'A';
		if (isOk[t_c] && !myFirst[t_c].empty()) {
			// 如果已经获取 t_c 的 FIRST 集合，并且非空，则判断其中有无空串，若有则继续搜索
			if (myFirst[t_c].end() != myFirst[t_c].find(Null_str_char)) {
				if (!Get_FIRST_Insert(ptr + 1, str, pos)) {
					// 深搜
					return false;
				}
			}
			//将 t_c 的 FIRST 集合放到 当前字符的 FIRST 集合
			Set_Ch_Itr set_itr = myFirst[t_c].begin();
			for (; set_itr != myFirst[t_c].end(); set_itr++) {
				if (*set_itr != Null_str_char) {
					myFirst[pos].insert(*set_itr);
				}
			}
			return true;
		}
		else return false;
	}
}


// 获取 FIRST 集合关键：截取字符串处理
void AutoConstruct::Get_FIRST_Nonterminal()
{
	set<char> t_set;
	while (t_set.size() < Vn_Num) {
		// 终止条件：已将所有的非终结符 FIRST 集合找完
		for (int j = 0; j < MAX_Char_Num; j++) {
			if (Grammar[j].empty()) continue; // 没有此非终结符，跳过，继续遍历
			string t_str;
			int pos, ptr;
			int i = 0;
			for (; i < Grammar[j].size(); i++) {
				// 根据此非终结符引出的文法，进行查找First集合
				t_str = Grammar[j][i];
				pos = t_str[0] - 'A';
				ptr = 3;
				bool t_b = true;
				while (ptr < t_str.size()) {
					if (JudgeNullStr(t_str, pos, ptr)) { continue; }
					if ((3 == ptr) || (ptr < t_str.size() && ('|' == t_str[ptr]) && (++ptr) < t_str.size())) {
						if (t_str[0] == t_str[ptr]) { ptr++; continue; }
						if (JudgeNullStr(t_str, pos, ptr)) continue;
						if (!Get_FIRST_Insert(ptr, t_str, pos)) {
							// 当前非终结符所需要的非终结符 FIRST 集合还没有找，故而无法获取当前非终结符的 FIRST 集合
							t_b = false;
							break;
						}
					}
					ptr++;
				}
				if (!t_b) break;
			}
			if (i == Grammar[j].size()) {
				// 此时对一个非终结符 FIRST 集合已找完
				isOk[pos] = true;
				t_set.insert(char('A' + pos));
			}
			else isOk[pos] = false;
		}
	}
}


void AutoConstruct::Get_FIRST_Insert_For_Clo(int ptr, string str, set<char> &set_Ch)
{
	if (str.size() == ptr) {
		return;
	}
	if (!JudgeChar(str[ptr])) {
		// 终结符直接放入 FIRST 集合
		set_Ch.insert(str[ptr]);
		return;
	}
	else {
		// 遇非终结符的处理办法
		int t_c = str[ptr] - 'A';
		// 如果已经获取 t_c 的 FIRST 集合，并且非空，则判断其中有无空串，若有则继续搜索
		if (myFirst[t_c].end() != myFirst[t_c].find(Null_str_char)) {
			Get_FIRST_Insert_For_Clo(ptr + 1, str, set_Ch);
		}
		//将 t_c 的 FIRST 集合放到 当前字符的 FIRST 集合
		Set_Ch_Itr set_itr = myFirst[t_c].begin();
		for (; set_itr != myFirst[t_c].end(); set_itr++) {
			if (*set_itr != Null_str_char) {
				set_Ch.insert(*set_itr);
			}
		}
		return;
	}
}

// 求闭包时，需用的 FIRST集
set<char> AutoConstruct::Get_First(string str)
{
	set<char> t_set_Ch;
	Get_FIRST_Insert_For_Clo(0, str, t_set_Ch);
	return t_set_Ch;
}
// 构造闭包
void AutoConstruct::Closure(node nd, int Sta)
{
	int myJudge = 0;
	// 判断闭包中是否已有要加入的产生式，要有，则增加搜索符
	for (int i = 0; i < DFA[Sta].size(); i++) {
		if (DFA[Sta][i].n_str == nd.n_str) {
			myJudge = 1;
			Set_Ch_Itr t_set_ch0 = nd.n_set.begin();
			for (; t_set_ch0 != nd.n_set.end(); t_set_ch0++) {
				if (DFA[Sta][i].n_set.end() == DFA[Sta][i].n_set.find(*t_set_ch0)) {
					DFA[Sta][i].n_set.insert(*t_set_ch0);
					myJudge = 2;
				}
			}
			if (1 == myJudge) return; // 闭包中已完全包含了要加入的产生式及其搜索符串，无需再加入，因为之前已处理过
			break;
		}
	}
	if (0 == myJudge) DFA[Sta].push_back(nd); // 闭包中无要加入的产生式，要把产生式加进去
	string str = nd.n_str;
	int ptr;
	// 防止不含 '.' 的产生式进入
	if (str.npos != str.find(mark_ch)) { ptr = str.find(mark_ch); }
	else { cerr << "ERROR" << endl; system("pause"); }
	ptr++;
	// 只有当 '.' 后为大写字母才可能继续求其闭包
	if (ptr < str.size() && JudgeChar(str[ptr])) {
		string tail_of_str = "";
		set<char> t_set;
		//////////////////////////////////////////////////////////////////////////
		//为求 FIRST集做准备
		for (int i = ptr + 1; i < str.size(); i++) {
			tail_of_str += str[i];
		}
		if (tail_of_str == "") {
			// 注意此处：若 str[ptr] 为最后一个字符，则将搜索符串全部放入
			Set_Ch_Itr t_set_itr = nd.n_set.begin();
			for (; t_set_itr != nd.n_set.end(); t_set_itr++) {
				t_set.insert(*t_set_itr);
			}
		}
		else { t_set = Get_First(tail_of_str); }
		//////////////////////////////////////////////////////////////////////////

		Vec_Str_Itr t_vec_str = Grammar[str[ptr] - 'A'].begin();
		for (; t_vec_str != Grammar[str[ptr] - 'A'].end(); t_vec_str++) {
			string t_str = *t_vec_str;
			t_str.insert(3, ".");
			node nd1;
			nd1.n_str = t_str;
			nd1.n_set = t_set;
			Closure(nd1, Sta); // 进一步搜索
		}
	}
}

// 求 DFA 各个状态时，判断当前要插入的状态是否和之前状态重叠
int AutoConstruct::Judge_Same(int sta)
{
	for (int i = 0; i < sta; i++) {
		if (DFA[sta].size() != DFA[i].size()) continue;
		int j = 0;
		for (; j < DFA[sta].size(); j++) {
			int k = 0;
			for (; k < DFA[i].size(); k++) {
				if (DFA[i][k] == DFA[sta][j]) {
					break;
				}
			}
			if (k == DFA[i].size()) { break; }
		}
		if (j == DFA[sta].size()) return i;
	}
	return sta;
}
// 寻找同心项目集
int AutoConstruct::Merge(int sta) {
	int ans = sta;
	// 遍历所有状态，查找同心项目集
	for (int i = 0; i < sta; ++i) {
		// 集合不等，必不是同心项目集，跳过此状态，继续遍历
		if (DFA[sta].size() != DFA[i].size()) continue;
		int j = 0;
		for (; j < DFA[sta].size(); ++j) {
			// 比对状态集合
			int k = 0;
			for (; k < DFA[i].size(); ++k) {
				if (DFA[i][k].n_str == DFA[sta][j].n_str) {
					// 两个集合中，有一个元素获得匹配
					break;
				}
			}
			if (k == DFA[i].size()) { 
				// 与之比对的状态的集合元素已遍历结束
				break;
			}
		}
		if (j == DFA[sta].size()) {
			// 两个集合所有元素匹配
			ans = i;
			break;
		}
	}
	if (ans == sta) return sta; // 未找到任何同心项目集
	// 合并同心项目集的搜索符
	for (int i = 0; i < DFA[sta].size(); ++i) {
		for (int j = 0; j < DFA[ans].size(); ++j) {
			if (DFA[sta][i].n_str == DFA[ans][j].n_str) {
				Set_Ch_Itr it = DFA[sta][i].n_set.begin();
				for (; it != DFA[sta][i].n_set.end(); ++it) {
					DFA[ans][j].n_set.insert(*it);
				}
			}
		}
	}
	return ans; // 返回同心项目集合并后的状态标识
}

void AutoConstruct::Goto()
{
	int Sta = 0;
	node nd;
	Let_Begin += myBegin;
	nd.n_str = Let_Begin;
	nd.n_str = nd.n_str.insert(3, ".");
	nd.n_set.insert('#');
	Closure(nd, Sta); // 构造第一个闭包，即第一个状态
	que_for_go.push(Sta); // 通过第一个状态去查找其他状态
	while (!que_for_go.empty()){ 
		// 直至查找不到更多的状态
		int t_sta = que_for_go.front();
		que_for_go.pop();
		Set_Ch_Itr t_set_ch_itr = allChar.begin();
		for (; t_set_ch_itr != allChar.end(); t_set_ch_itr++)  
		// 遍历所有终结符与非终结符，进行搜索
		{
			bool Judge_to_Total = true;
			Total_sta++; // 默认增加了状态数（若没有，后面有纠正）
			for (int i = 0; i < DFA[t_sta].size(); i++) {
				string str = DFA[t_sta][i].n_str;
				int pos = str.find(mark_ch);
				if (pos + 1 == str.size()) continue;
				if (*t_set_ch_itr == str[pos + 1]) {
					// 可以构造另一状态
					Judge_to_Total = false;
					str.erase(pos, 1);
					str.insert(pos + 1, ".");
					node nd1;
					nd1.n_str = str;
					nd1.n_set = DFA[t_sta][i].n_set;
					Closure(nd1, Total_sta); // 构造该状态闭包
				}
			}
			if (Judge_to_Total) Total_sta--; // 若没有发现可以构造另一状态，则纠正总的状态数
			else {
				//int t_to = Judge_Same(Total_sta);
				int t_to = Merge(Total_sta);
				if (t_to != (Total_sta)) {
					// 状态发生重叠现象
					DFA[Total_sta].clear();
					Total_sta--;
				}
				else {
					// 若没有发生重叠，则通过此状态再去找其他状态
					que_for_go.push(t_to); 
				}
				// 构建 DFA 各个状态之间的转换关系
				Go_node t_Go_node;
				t_Go_node.go_ch = *t_set_ch_itr;
				t_Go_node.to = t_to;
				GoTo[t_sta].push_back(t_Go_node);
			}
		}
	}
}

// 建立LALR(1)分析表
void AutoConstruct::Get_Table()
{
	for (int i = 0; i <= Total_sta; i++) {
		set<char> del;
		for (int k = 0; k < DFA[i].size(); k++) {
			string str = DFA[i][k].n_str;
			int pos = str.find('.') + 1;
			if (pos == str.size()) {
				// '.' 即当前产生式最后一个字符
				str.erase(pos - 1, 1);
				if (str == Let_Begin) {
					//判断是否ACC
					For_Tab_node t_Tab_node;
					t_Tab_node.Judge = "ACC";
					t_Tab_node.meet = '#';
					t_Tab_node.Go = -1;
					// 构建ACTION表
					Action[i].push_back(t_Tab_node);
					continue;
				}
				//规约
				Set_Ch_Itr t_ch_itr = DFA[i][k].n_set.begin();
				for (; t_ch_itr != DFA[i][k].n_set.end(); t_ch_itr++) {
					For_Tab_node t_Tab_node;
					t_Tab_node.Judge = "R";
					t_Tab_node.meet = *t_ch_itr;

					int sec = 0;
					// 查找规约时，是利用输入文法时的第几个产生式
					for (; sec < Num_Gra.size(); sec++) {
						if (Num_Gra[sec] == str) {
							break;
						}
					}
					// 若没查找到，文法有问题
					if (sec == Num_Gra.size()) {
						cerr << "Can't Find!!!" << endl;
						system("pause");
					}
					t_Tab_node.Go = sec;
					Action[i].push_back(t_Tab_node);
				}
				continue;
			}
			char t_ch = str[pos];
			if (del.end() != del.find(t_ch)) {
				continue;
			}
			del.insert(t_ch);
			if (!JudgeChar(t_ch)) {
				// 移进
				For_Tab_node t_Tab_node;
				t_Tab_node.Judge = "S";
				int sec = 0;
				// 查找移进时，进入的下一个状态
				for (; sec < GoTo[i].size(); sec++) {
					if (GoTo[i][sec].go_ch == t_ch) {
						break;
					}
				}
				t_Tab_node.meet = t_ch;
				t_Tab_node.Go = GoTo[i][sec].to;
				Action[i].push_back(t_Tab_node);
			}
			else {
				// 遇到 大写字母，构建 GOTO
				For_Tab_node t_Tab_node;
				t_Tab_node.Judge = "";
				int sec = 0;
				for (; sec < GoTo[i].size(); sec++) {
					if (GoTo[i][sec].go_ch == t_ch) {
						break;
					}
				}
				t_Tab_node.meet = t_ch;
				t_Tab_node.Go = GoTo[i][sec].to;
				// 构建GOTO表
				GOTO[i].push_back(t_Tab_node);
			}
		}
	}
}

void AutoConstruct::ConstructTable() {
	Get_FIRST_Nonterminal();
	Goto();
	Get_Table();
}

int AutoConstruct::getTotalSta() {
	return Total_sta;
}

char AutoConstruct::getBegin() {
	return myBegin;
}


// 注意一下"ε"的处理即可
string AutoConstruct::Get_FIRST_View()
{
	string strTmp = "";
	Get_FIRST_Nonterminal();
	for (int i = 0; i < MAX_Char_Num; i++) {
		if (myFirst[i].empty()) continue;
		Set_Ch_Itr set_itr = myFirst[i].begin();
		strTmp += "FIRST (";
		strTmp += (char)('A' + i);
		strTmp += ") = {";
		for (; set_itr != myFirst[i].end();) {
			if (*set_itr == Null_str_char) {
				strTmp += "ε";
				if (++set_itr != myFirst[i].end()) {
					strTmp += ", ";
				}
				continue;
			}
			strTmp += (*set_itr);
			if (++set_itr != myFirst[i].end()) {
				strTmp += ", ";
			}
		}
		strTmp += "}";
		strTmp += "\r\n";
	}
	return strTmp;
}

string AutoConstruct::Get_Closure_View()
{
	string strTmp;
	for (int i = 0; i <= Total_sta; i++) {
		strTmp += ('0' + i);
		strTmp += ":\r\n";
		for (int j = 0; j < DFA[i].size(); j++) {
			strTmp += DFA[i][j].n_str;
			strTmp += ",";
			Set_Ch_Itr t_set_ch = DFA[i][j].n_set.begin();
			for (; t_set_ch != DFA[i][j].n_set.end(); t_set_ch++) {
				if (t_set_ch != DFA[i][j].n_set.begin()) {
					strTmp += "/";
				}
				strTmp += *t_set_ch;
			}
			strTmp += "\r\n";
		}
	}
	return strTmp;
}

string AutoConstruct::Get_Goto_View()
{
	string strTmp = "";
	for (int i = 0; i <= Total_sta; i++) {
		strTmp += ('0' + i);
		strTmp += ":\r\n";
		for (int j = 0; j < GoTo[i].size(); j++) {
			strTmp += "\tby\t";
			strTmp += GoTo[i][j].go_ch;
			strTmp += "\tto\t";
			strTmp += ('0' + GoTo[i][j].to);
			strTmp += "\r\n";
		}
	}
	return strTmp;
}