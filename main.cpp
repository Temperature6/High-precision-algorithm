//version:20200818 —— 第一个可以正常使用的版本
#include <iostream>
#include <vector>
#include <string>
#include "function.h"
using namespace std;
bool isNegative = false;
bool* p_negative = &isNegative;

vector<char> Addition(string num1, string num2);
vector<char> Subtraction(string num1, string num2);
vector<char> Multiplication(string num1, string num2);
vector<char> Division(string num1, string num2, int decimal);
void ErrorExit(char pos);

int main()
{
	system("title 高精度运算算法");
FLAG:
	vector <char> answer;
	string Str;
	cout << "输入表达式>>>";
	cin >> Str;
	if (Str == "github")
	{
		system("start https://github.com/Temperature6/High-precision-algorithm");
		goto FLAG;
	}
	//寻找运算符
	int opea = findopreator(Str);
	//判断是否合法并开始调用计算函数
	if (opea == 0)
	{
		printf("——警告:\n\t程序没有在表达式中找到运算符\n\n");
		printf("参考以下举例:\n\t相加(+); \n\t相减(-); \n\t相乘(*); \n\t除以(/); \n\n");
		system("pause");
		goto FLAG;
	}
	else
	{
		vector <string> v;
		switch (Str[opea])
		{
		case '+':
			v = split(Str, "+");
			answer = Addition(v[0], v[1]);
			break;
		case '-':
			v = split(Str, "-");
			answer = Subtraction(v[0], v[1]);
			break;
		case '*':
			v = split(Str, "*");
			answer = Multiplication(v[0], v[1]);
			break;
		case '/':
			v = split(Str, "/");
			if (isNumberofTen(v[1]))
			{
				printf("只需移动小数点的表达式不予计算");
				break;
			}
			if (NumberisZero(v[1]))
			{
				printf("警告!除数为零!");
				break;
			}
			int dec = 0;
			printf("输入答案的总位数(包括整数部分):");
			cin >> dec;
			answer = Division(v[0], v[1], dec);
			break;
		}
	}
	if (answer.size() != 0)
	{
		printf("\n");
		PrintAnswer(answer);
		printf("\n\n");
		system("pause");
	}
	printf("\n");
	goto FLAG;
}

void ErrorExit(char pos)
{
	printf("——————");
	printf("警告，程序出现错误！\n\n");
	printf("请检查您的输入是否存在数学错误\n\n");
	switch (pos)
	{
	case 'A':
		printf("调用时出现错误的函数:Addition");
		break;
	case 'S':
		printf("调用时出现错误的函数:Subtraction");
		break;
	case 'M':
		printf("调用时出现错误的函数:Multiplication");
		break;
	case 'D':
		printf("调用时出现错误的函数:Division");
		break;
	}
	printf("\n\n");
	system("pause");
	exit(1);
}

vector<char> Addition(string num1, string num2)
{
	//string类型存入vector
	vector <char> Num1 = StringtoCharVec(num1);
	vector <char> Num2 = StringtoCharVec(num2);
	//检查是否存在小数点，若没有则添加
	if (findpoint(&Num1[0], Num1.size()) == -1)
	{
		Num1.push_back('.');
		Num1.push_back('0');
	}
	if (findpoint(&Num2[0], Num2.size()) == -1)
	{
		Num2.push_back('.');
		Num2.push_back('0');
	}
	//获取小数点位置,小数位数
	int Num1point = findpoint(&Num1[0], Num1.size());
	int Num2point = findpoint(&Num2[0], Num2.size());
	int Num1decimal = DecimalPlaces(&Num1[0], Num1.size());
	int Num2decimal = DecimalPlaces(&Num2[0], Num2.size());
	//整数部分对齐
	if (Num1point > Num2point)
		Num2.insert(Num2.begin(), Num1point - Num2point, '0');
	if (Num1point < Num2point)
		Num1.insert(Num1.begin(), Num2point - Num1point, '0');
	//小数部分对齐
	if (Num1decimal > Num2decimal)
		Num2.insert(Num2.end(), Num1decimal - Num2decimal, '0');
	if (Num1decimal < Num2decimal)
		Num1.insert(Num1.end(), Num2decimal - Num1decimal, '0');
	//确定最后的小数点位置
	int Anspoint = 0;
	if (findpoint(&Num1[0], Num1.size()) != findpoint(&Num2[0], Num2.size()))
		ErrorExit('A');
	else
		Anspoint = findpoint(&Num1[0], Num1.size());
	//去掉小数点
	Num1.erase(Num1.begin() + findpoint(&Num1[0], Num1.size()));
	Num2.erase(Num2.begin() + findpoint(&Num2[0], Num2.size()));
	//字符数组转整型数组
	vector <int> Number1 = VecChartoInt(Num1);
	vector <int> Number2 = VecChartoInt(Num2);
	//开始计算
	int unit = 0;
	int ten = 0;
	int temp = 0;
	vector <int> ReverseAns;
	
	for (int i = Number1.size() - 1; i >= 0; i--)
	{
		temp = Number1[i] + Number2[i] + ten;
		unit = temp / 1 % 10;
		ten = temp / 10 % 10;
		ReverseAns.push_back(unit);
	}
	if (ten != 0)
	{
		ReverseAns.push_back(ten);
		Anspoint++;
	}
	reverse(ReverseAns.begin(), ReverseAns.end());
	vector <char> out = VecInttoChar(ReverseAns);
	out.insert(out.begin() + Anspoint, '.');
	return out;
}

vector<char> Subtraction(string num1, string num2)
{
	//string类型存入vector
	vector <char> Num1 = StringtoCharVec(num1);
	vector <char> Num2 = StringtoCharVec(num2);
	//检查是否存在小数点，若没有则添加
	if (findpoint(&Num1[0], Num1.size()) == -1)
	{
		Num1.push_back('.');
		Num1.push_back('0');
	}
	if (findpoint(&Num2[0], Num2.size()) == -1)
	{
		Num2.push_back('.');
		Num2.push_back('0');
	}
	//获取小数点位置,小数位数
	int Num1point = findpoint(&Num1[0], Num1.size());
	int Num2point = findpoint(&Num2[0], Num2.size());
	int Num1decimal = DecimalPlaces(&Num1[0], Num1.size());
	int Num2decimal = DecimalPlaces(&Num2[0], Num2.size());
	//整数部分对齐
	if (Num1point > Num2point)
		Num2.insert(Num2.begin(), Num1point - Num2point, '0');
	if (Num1point < Num2point)
		Num1.insert(Num1.begin(), Num2point - Num1point, '0');
	//小数部分对齐
	if (Num1decimal > Num2decimal)
		Num2.insert(Num2.end(), Num1decimal - Num2decimal, '0');
	if (Num1decimal < Num2decimal)
		Num1.insert(Num1.end(), Num2decimal - Num1decimal, '0');
	//确定最后的小数点位置
	int Anspoint = 0;
	if (findpoint(&Num1[0], Num1.size()) != findpoint(&Num2[0], Num2.size()))
		ErrorExit('S');
	else
		Anspoint = findpoint(&Num1[0], Num1.size());
	//去掉小数点
	Num1.erase(Num1.begin() + findpoint(&Num1[0], Num1.size()));
	Num2.erase(Num2.begin() + findpoint(&Num2[0], Num2.size()));
	//字符数组转整型数组
	vector <int> Number1 = VecChartoInt(Num1);
	vector <int> Number2 = VecChartoInt(Num2);
	//开始计算
	vector <int> ReverseAns;
	int unit = 0;
	int temp = 0;

	for (int i = Number1.size() - 1; i >= 0; i--)
	{
		if (Number1[i] >= Number2[i])
			temp = Number1[i] - Number2[i];
		else
		{
			//如果到最后一位还要借位，则判断为负数，并交换传参再调用;
			if (i == 0)
			{
				*p_negative = true;
				vector <char> n_out;
				n_out = Subtraction(num2, num1);
				return n_out;
			}
			else
			{
				temp = Number1[i] - Number2[i] + 10;
				Number1[i - 1]--;
			}
		}
		ReverseAns.push_back(temp);
	}
	reverse(ReverseAns.begin(), ReverseAns.end());
	vector <char> out = VecInttoChar(ReverseAns);
	out.insert(out.begin() + Anspoint, '.');
	//过滤无意义的0
	out = FilterZero(out);

	if (*p_negative)
	{
		out.insert(out.begin(), '-');
		*p_negative = false;
	}

	return out;
}

vector<char> Multiplication(string num1, string num2)
{
	//string类型存入vector
	vector <char> Num1 = StringtoCharVec(num1);
	vector <char> Num2 = StringtoCharVec(num2);
	//获取小数位数
	int Num1decimal = DecimalPlaces(&Num1[0], Num1.size());
	int Num2deciaml = DecimalPlaces(&Num2[0], Num2.size());
	//去0操作 0.56 —> .56
	if (findpoint(&Num1[0], Num1.size()) != -1 and Num1[0] == '0' and Num1[1] == '.')
		Num1.erase(Num1.begin());
	if (findpoint(&Num2[0], Num2.size()) != -1 and Num2[0] == '0' and Num2[1] == '.')
		Num2.erase(Num2.begin());
	//去小数点操作 78.32 —> 7832
	if (findpoint(&Num1[0], Num1.size()) != -1)
		Num1.erase(Num1.begin() + findpoint(&Num1[0], Num1.size()));
	if (findpoint(&Num2[0], Num2.size()) != -1)
		Num2.erase(Num2.begin() + findpoint(&Num2[0], Num2.size()));
	//字符数组转整型数组
	vector <int> Number1 = VecChartoInt(Num1);
	vector <int> Number2 = VecChartoInt(Num2);
	//保证位数小的在下面
	if (Number2.size() > Number1.size())
		Number1.swap(Number2);
	
	vector <int> Answer;
	
	int calccount = 0;
	
	for (int i = Number2.size() - 1; i >= 0; i--)
	{
		int unit = 0;
		int ten = 0;
		int temp = 0;
		vector <int> tempvec;
		for (int j = Number1.size() - 1; j >= 0; j--)
		{
			temp = Number1[j] * Number2[i] + ten;
			unit = temp / 1 % 10;
			ten = temp / 10 % 10;
			tempvec.push_back(unit);
		}
		if (ten != 0)
			tempvec.push_back(ten);
		tempvec.insert(tempvec.begin(), calccount, 0); //保证其他位运算时不会差10
		reverse(tempvec.begin(), tempvec.end()); //倒置数组,使数字顺序正确
		//如果是第一次计算，最后的Answer数组不参与加法计算
		if (calccount == 0)
			Answer.swap(tempvec);
		else
			Answer = AddinMul(Answer, tempvec);
		calccount++; //补零计数
	}
	vector <char> out;
	out = VecInttoChar(Answer);
	out = InsertPoint(out, Num1decimal + Num2deciaml);
	//使输出格式规范
	if (out[0] == '.')
		out.insert(out.begin(), '0');
	if (out[out.size() - 1] == '.')
		out.push_back('0');
	//头去零
	if (out.size() >= 2)
	{
		if (out[0] == '0' and out[1] == '0')
			out.erase(out.begin());
	}
	//返回
	return out;
}

vector<char> Division(string num1, string num2, int decimal)
{
	//string类型存入vector
	vector <char> Num1 = StringtoCharVec(num1);
	vector <char> Num2 = StringtoCharVec(num2);
	//获取小数位数
	int Num1decimal = DecimalPlaces(&Num1[0], Num1.size());
	int Num2deciaml = DecimalPlaces(&Num2[0], Num2.size());
	/*//去0操作 0.56 —> .56
	if (findpoint(&Num1[0], Num1.size()) != -1 and Num1[0] == '0' and Num1[1] == '.')
		Num1.erase(Num1.begin());
	if (findpoint(&Num2[0], Num2.size()) != -1 and Num2[0] == '0' and Num2[1] == '.')
		Num2.erase(Num2.begin());
	//去小数点操作 78.32 —> 7832
	if (findpoint(&Num1[0], Num1.size()) != -1)
		Num1.erase(Num1.begin() + findpoint(&Num1[0], Num1.size()));
	if (findpoint(&Num2[0], Num2.size()) != -1)
		Num2.erase(Num2.begin() + findpoint(&Num2[0], Num2.size()));*/
	if (Num1decimal > Num2deciaml)
	{
		if (findpoint(&Num1[0], Num1.size()) != -1)
			Num1.erase(Num1.begin() + findpoint(&Num1[0], Num1.size()));
		Num2 = MovePoint(Num2, Num1decimal);
	}
	if (Num2deciaml > Num1decimal)
	{
		if (findpoint(&Num2[0], Num2.size()) != -1)
			Num2.erase(Num2.begin() + findpoint(&Num2[0], Num2.size()));
		Num1 = MovePoint(Num1, Num2deciaml);
	}
	//字符数组转整型数组
	vector <int> Number1 = VecChartoInt(Num1);
	vector <int> Number2 = VecChartoInt(Num2);
	//保证位数小的在下面
	int numpoint = 0;
	int moveplace = 0;
	if (Number1.size() < Number2.size())
	{
		moveplace = Number2.size() - Number1.size();
		Number1.insert(Number1.end(), Number2.size() - Number1.size(), 0);
	}

	int Num2size = Number2.size();
	int pos = 0;
	
	vector <int> ans;
	vector <int> temp;

	while (ans.size() <= decimal)
	{
		if (pos == Number1.size())
			numpoint = ans.size();
		int unit = 0;
		if (pos <= Number1.size() - 1)
			temp.push_back(Number1[pos]);
		else
			temp.push_back(0);
		if (Biger(temp, Number2))
		{
			while (Biger(temp, Number2))
			{
				temp = SubinDiv(temp, Number2);
				temp = FilterVecZero(temp);
				unit++;
			}
			ans.push_back(unit);
			pos++;
		}
		else
		{
			ans.push_back(0);
			pos++;
		}
		if (temp.empty() and pos == num2.size() - 1)
			break;
	}
	vector <char> out;
	out = VecInttoChar(ans);
	if (numpoint != 0)
		out.insert(out.begin() + numpoint - moveplace, '.');
	out = FilterZero(out);

	return out;
}
