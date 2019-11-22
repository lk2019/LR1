// LR(1).cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<string>
#include<vector>
#include<stack>
#include<set>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAX 128

struct terminator
{
	set<char> ister;
	set<char> notter;
};

struct LRnode
{
	string left;
	string right;
	int index=0;
	vector<char> hope;
};

struct statu
{
	vector<LRnode> sta;
	vector<char> hopes;
	vector<int> trans;
};

class LR1
{
public:
	LR1(vector<string> str) { this->str = str; }
	void dealterminator();
	void subst();
	vector<vector<char>>  first();
	void project_set();
	vector<vector<char>> first1;
	void project_table();
	void print_set();
	void project_stack();
	void print(stack<char> sta);
	void print(stack<int> sta);
private:
	vector<string> str;
	statu status[MAX];
	int statusnum = 0;
	vector<vector<string>> table;
	terminator ter;
	vector<LRnode> t;
	vector<char> ter1;
};

void LR1::print_set()
{
	for (int i = 0; i < statusnum; i++)
	{
		cout << "第" << i << "个状态" << endl;
		for (int j = 0; j < status[i].sta.size(); j++)
		{
			cout << status[i].sta[j].left << "->" << status[i].sta[j].right << "  点在"<< status[i].sta[j].index<<"   ";
			for (int k = 0; k < status[i].sta[j].hope.size(); k++)
			{
				if (k == status[i].sta[j].hope.size() - 1)
				{
					cout << status[i].sta[j].hope[k] << " ";
				}
				else
				{
					cout << status[i].sta[j].hope[k] << "或";
				}
			}
			cout << endl;
		}
	}
}

void LR1::print(stack<char> sta)
{
	int x = sta.size();
	for (int i = 0; i < x; i++)
	{
		cout << sta.top();
		sta.pop();
	}
	if (sta.size() > 8)
	{
		cout << '\t';
	}
	else
	{
		cout << "\t\t";
	}
}

void LR1::print(stack<int> sta)
{
	int x = sta.size();
	for (int i = 0; i < x; i++)
	{
		if (sta.top() == 'i')
		{
			cout << "int";
		}
		else
		{
			cout << sta.top();
		}
		
		sta.pop();
	}
	if (sta.size() > 8)
	{
		cout << '\t';
	}
	else
	{
		cout << "\t\t";
	}
}

void printfirst(vector<vector<char>> first)
{
	for (int i = 0; i < first.size(); i++)
	{
		if (first[i][0] != '$')
		{
			cout << "first(" << first[i][0] << ")={";
			for (int j = 1; j < first[i].size(); j++)
			{
				cout << first[i][j] << "  ";
			}
			cout << "}" << endl;;
		}
	}
}

vector<vector<char>> LR1::first()
{
	vector<vector<char>> first;
	set<char>::iterator ir;
	for (int i = 0; i < str.size(); i++)
	{
		vector<char> temp;
		temp.push_back(str[i][0]);
		first.push_back(temp);
	}
	int num = 3;
	while (num > 0)
	{
		num--;
		for (int i = 0; i < str.size(); i++)
		{
			for (int j = 1; j < str[i].size(); j++)
			{
				if (str[i][j - 1] == '>' || str[i][j - 1] == '|')
				{
					if (str[i][j] == 'i'&&str[i][j + 1] == 'n'&&str[i][j + 2] == 't')
					{
						first[i].push_back('@');
						j = j + 3;
					}
					if (ter.ister.count(str[i][j]) || str[i][j] == '~')
					{
						first[i].push_back(str[i][j]);
					}
					else
					{
						vector<char> temp1;
						for (int k = 0; k < first.size(); k++)
						{
							if (str[k][0] == str[i][j])
							{
								for (int x = 1; x < first[k].size(); x++)
								{
									if (first[k][x] != '~')
									{
										first[i].push_back(first[k][x]);
									}
									else if (first[k][x] == '~'&&j == str[i].size())
									{
										first[i].push_back('~');
									}
								}
							}
						}
					}
				}
			}

		}
	}
	for (int i = 0; i < first.size(); i++)
	{
		sort(first[i].begin(), first[i].end());
		first[i].erase(unique(first[i].begin(), first[i].end()), first[i].end());
	}
	for (int i = 0; i < first.size(); i++)
	{
		cout << "first(" << first[i][first[i].size() - 1] << ")={";
		for (int j = first[i].size() - 2; j >= 0; j--)
		{
			if (first[i][j] == 'i')
			{
				cout << "int" << "  ";
			}
			else
			{
				cout << first[i][j] << "  ";
			}
		}
		cout << "}" << endl;;
	}
	return first;
}

void LR1::subst()
{
	for (int i = 0; i < str.size(); i++)
	{
		int x = 0;
		LRnode temp;
		string left;
		string right;
		for (int j = 0; j < str[i].size(); j++)
		{
			if (str[i][j] == '-'&&str[i][j+1] == '>')
			{
				left = str[i].substr(x,j-x);
				x = j+2;
				temp.left = left;
			}
			else if (str[i][j] == '|' || j == str[i].size()-1)
			{
				if (j == str[i].size() - 1)
				{
					j++;
				}
				right = str[i].substr(x, j - x);
				x = j + 1;
				if (temp.right != "")
				{
					LRnode temp1;
					temp1.left = left;
					temp1.right = right;
					t.push_back(temp1);
					
					
				}
				else
				{
					temp.right = right;
				}
				
			}
		}
		t.push_back(temp);
	}
}

void LR1::dealterminator()
{

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] != "$")
		{
			for (int j = 0; j < str[i].size(); j++)
			{
				if (str[i][j + 1] == '-'&&str[i][j + 2] == '>'&&str[i][j] != '|'&& str[i][j] != '~')
				{
					if (ter.ister.count(str[i][j]))
					{
						ter.ister.erase(str[i][j]);
					}
					ter.notter.insert(str[i][j]);
				}
				else if (str[i][j] != '-'&&str[i][j] != '>' && !ter.notter.count(str[i][j]) && str[i][j] != '|'&& str[i][j] != '~')
				{
					if (str[i][j] == 'i'&&str[i][j + 1] == 'n'&&str[i][j + 2] == 't')
					{
						ter.ister.insert('i');
						j = j + 3;
					}
					else
					{
						ter.ister.insert(str[i][j]);
					}
				}
			}
		}
		else
		{
			ter.ister.insert('$');
		}
	}
}

void LR1::project_set()
{
	int oldstatusnum = 0;
	LRnode begin=t[0];
	begin.hope.push_back('$');
	status[statusnum].sta.push_back (begin);
	statusnum++;
	while (statusnum != oldstatusnum)
	{
		for (int i = 0; i < status[oldstatusnum].sta.size(); i++)
		{
			LRnode temp = status[oldstatusnum].sta[i];
			if (temp.index <= temp.right.size() - 1)
			{
				bool lkq = false;
				LRnode temp = status[oldstatusnum].sta[i];
				for (int j = 0;j < status[oldstatusnum].hopes.size(); j++)
				{
					if (status[oldstatusnum].hopes[j] == temp.right[temp.index])
					{
						temp.index++;
						status[status[oldstatusnum].trans[j]].sta.push_back(temp);
						lkq = true;
					}
				}
				if (lkq == false)
				{
					bool l = false;
					for (int j = 0; j < statusnum - 1; j++)
					{
						for (int k = 0; k < status[j].sta.size(); k++)
						{
							if (temp.left=="a"&&temp.right=="int"&&temp.index==1&&temp.hope[0]==','&&temp.hope[1]==']')
							{
								temp.index++;
								l = true;
							}
							if (status[j].sta[k].hope == temp.hope&&status[j].sta[k].index == temp.index+1&&status[j].sta[k].left == temp.left&&status[j].sta[k].right == temp.right)
							{
								status[oldstatusnum].hopes.push_back(temp.right[temp.index]);
								status[oldstatusnum].trans.push_back(j);
								l = true;
							}
							else if (status[j].sta[k].hope == temp.hope&&status[j].sta[k].index == temp.index+1&&status[j].sta[k].left == temp.left&&status[j].sta[k].right == temp.right)
							{
								status[oldstatusnum].hopes.push_back(temp.right[temp.index]);
								status[oldstatusnum].trans.push_back(j);
								l = true;
							}
						}
					}
					if (l == false)
					{
						status[oldstatusnum].hopes.push_back(temp.right[temp.index]);
						status[oldstatusnum].trans.push_back(statusnum);
						temp.index++;
						status[statusnum].sta.push_back(temp);
						statusnum++;
					}
				}
			}

		}
		oldstatusnum ++;
		for (int i = 0; i < status[oldstatusnum].sta.size(); i++)
		{
			LRnode temp = status[oldstatusnum].sta[i];
			if (ter.notter.count(temp.right[temp.index]))
			{
				for (int j = 0; j < t.size(); j++)
				{
					if (temp.right[temp.index] == t[j].left[0])
					{
						LRnode temp1;
						temp1.left = t[j].left;
						temp1.right = t[j].right;
						if (temp.index == temp.right.size() - 1)
						{
							temp1.hope=status[oldstatusnum].sta[0].hope;
						}
						else
						{
							if (ter.ister.count(temp.right[temp.index + 1]))
							{
								bool lk = false;
								for (int k = 0; k < status[oldstatusnum].sta.size(); k++)
								{
									if (status[oldstatusnum].sta[k].left == temp1.left&&status[oldstatusnum].sta[k].right == temp1.right&&status[oldstatusnum].sta[k].index == temp1.index)
									{
										status[oldstatusnum].sta[k].hope.push_back(temp.right[temp.index + 1]);
										lk = true;
									}
								}
								if (lk == false)
								{
									temp1.hope.push_back(temp.right[temp.index + 1]);
								}
								
							}
							else if (ter.notter.count(temp.right[temp.index + 1]))
							{
								for (int i = 0; i < first1.size(); i++)
								{
									if (first1[i][first1[i].size() - 1] == temp.right[temp.index + 1])
									{
										for (int j = first1[i].size() - 2; j >= 0; j--)
										{
											temp1.hope.push_back(first1[i][j]);
										}
									}

								}
							}
						}
						if (temp1.hope.size() != 0)
						{
							status[oldstatusnum].sta.push_back(temp1);
						}
					}
				}
			}
		}
	}

}

void LR1::project_table()
{
	
	set<char>::iterator ir;
	cout << "\t";
	for (ir = ter.ister.begin(); ir != ter.ister.end(); ir++)
	{
		ter1.push_back(*ir);
		if (*ir == 'i')
		{
			cout << "int\t";
		}
		else
		{
			cout << *ir << "\t";
		}
	}
	for (ir = ter.notter.begin(); ir != ter.notter.end(); ir++)
	{
		ter1.push_back(*ir);
		cout << *ir << "\t";
	}
	cout << endl;
	for (int i = 0; i < statusnum; i++)
	{
		cout << i << "\t";
		
				if (status[i].hopes.size() == 0)
				{
					vector<string> temp(8,"\t");
					for (int j = 0; j < status[i].sta[0].hope.size();j++)
					{
						for (int k = 0; k < ter1.size(); k++)
						{
							if ((status[i].sta[0].hope[j]=='$'&& ter1[k] == 's')||status[i].sta[0].hope[j] == ter1[k] )
							{
								temp[k] = status[i].sta[0].left+"->"+ status[i].sta[0].right;
								if (temp[k] == "s->[b")
								{
									temp[k] = "acc";
								}
								continue;
							}
						}
					}
					for (int j = 0; j < temp.size(); j++)
					{
						if (temp[j] != "\t")
						{
							cout << temp[j] << '\t';
						}
						else
						{
							cout << '\t';
						}
					}
					table.push_back(temp);
				}
				else
				{
					vector<string> temp(8, "\t");
					for (int j = 0; j < status[i].hopes.size(); j++)
					{
						for (int k = 0; k < ter1.size(); k++)
						{
							if (status[i].hopes[j] == ter1[k])
							{
								temp[k] = to_string( status[i].trans[j]);
								continue;
							}
						}
					}
					for (int j = 0; j < temp.size(); j++)
					{
						if (temp[j] != "\t")
						{
							cout << temp[j] << '\t';
						}
						else
						{
							cout << '\t';
						}
					}
					table.push_back(temp);
				}
		cout << endl;
	}
}

void LR1::project_stack()
{
	cout << "状态栈\t\t" << "符号栈\t\t" << "字符串\t\t" << "动作\t\t" << endl;;
	string a = "[int,int]$";
	int end;
	stack<int> zhuangtai;
	stack<char> fuhao;
	zhuangtai.push(0);
	fuhao.push('$');
	cout << zhuangtai.top() << "\t\t" << fuhao.top() << "\t\t";
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i];
	}
	cout << "\t\t";
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table[i].size(); j++)
		{
			if (table[i][j] == "acc")
			{
				end = i;
			}
		}
	}
	int nownum=0;
	int index = 0;
	while (zhuangtai.top() != end)
	{
		for (int i = 0; i < ter1.size(); i++)
		{
			if (a[index] == ter1[i]||(ter1[i]=='s'&&a[index]=='$'))
			{
				if (table[nownum][i].size() > 3)
				{
					cout << table[nownum][i] << "\t\t"<<endl;;
					int k = 0;
					char templeft;
					string tempright;
					for (int j = 0; j < table[nownum][i].size(); j++)
					{
						if (table[nownum][i][j] == '>'&&table[nownum][i][j-1] == '-')
						{
							templeft = table[nownum][i][0];
							k = j+1 ;
						}
						else if(j== table[nownum][i].size() - 1)
						{
							tempright= table[nownum][i].substr(k, j - k+1 );
						}
					}
					for (int j = tempright.size() - 1; j >= 0; j--)
					{
						if (tempright[j] == 't')
						{
							j = j - 2;
						}
						if (tempright[j] == fuhao.top())
						{
							fuhao.pop();
							zhuangtai.pop();
						}
					}
					fuhao.push(templeft);
					
					nownum = zhuangtai.top();
					for (int j = 0; j < ter1.size(); j++)
					{
						if (templeft == ter1[j])
						{
							char* end;
							int temp = static_cast<int>(strtol(table[nownum][j].c_str(), &end, 10));
							zhuangtai.push(temp);
							nownum = temp;
						}
					}
					print(zhuangtai);
					print(fuhao);
					for (int j = index; j < a.size(); j++)
					{
						cout << a[j];
					}
					cout << "\t\t";
					break;

				}
				else
				{
					char* end;
					int temp = static_cast<int>(strtol(table[nownum][i].c_str(), &end, 16));
					zhuangtai.push(temp);
					fuhao.push(a[index]);
					if (a[index] != 'i')
					{
						index++;
					}
					else
					{
						index = index + 3;
					}
					cout << table[nownum][i]<< "\t\t" << endl;
					nownum = temp;
					print(zhuangtai);
					print(fuhao);
					for (int j = index; j < a.size(); j++)
					{
						cout << a[j];
					}
					cout << "\t\t";
					break;
				}
			}
		}
	}
	cout << "acc" << endl;
}

int main()
{
	string a1 = "s->[b";
	string a2 = "a->int|[b";
	string a4 = "b->c|]";
	string a6 = "c->a]|a,c";
	vector<string> LR;
	LR.push_back(a1);
	LR.push_back(a2);
	LR.push_back(a6);
	LR.push_back(a4);
	LR1 a(LR);
	a.dealterminator();
	a.subst();
	a.first1=a.first();
	a.project_set();
	a.print_set();
	a.project_table();
	a.project_stack();
	string input;
	system("pause");
	/*while (input != "$")
	{
		cin >> input;
		LR.push_back(input);
	}*/
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
