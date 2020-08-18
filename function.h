#pragma once
#include <string>
#include <vector>
using namespace std;

int findpoint(char* vec, int len)
{
	int index = -1;
	for (int i = 0; i < len; i++)
	{
		if (vec[i] == '.')
			index = i;
	}
	return index;
}

int DecimalPlaces(char* vec, int len)
{
	int point = findpoint(vec, len);
	if (point == -1)
		return 0;
	else
		return len - point - 1;
}

int findopreator(string str)
{
	int opea = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			opea = i;
			break;
		}
	}
	return opea;
}

bool Biger(vector<int>num1, vector<int>num2)
{
	//num1比num2大返回true，否则返回false
	//1.判断位数
	if (num1.size() > num2.size())
		return true;
	else if (num1.size() < num2.size())
		return false;
	//2.从最大位开始往后比较
	for (int i = 0; i < num1.size(); i++)
	{
		if (num1[i] > num2[i])
			return true;
		else if (num1[i] < num2[i])
			return false;
	}
	return true;
}

bool isNumberofTen(string str)
{
	if (str[0] != '1')
		return false;
	for (int i = 1; i < str.length(); i++)
	{
		if (str[i] != '0')
			return false;
	}
	return true;
}

bool NumberisZero(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != '0')
			return false;
	}
	return true;
}

void PrintAnswer(vector<int>vec, bool equal = true, bool style = true)
{
	if (style)
	{
		if (equal)
			cout << "=";
		for (int i = 0; i < vec.size(); i++)
			cout << vec[i];
	}
	else
	{
		for (int i = 0; i < vec.size(); i++)
			cout << vec[i] << ", ";
	}
}

void PrintAnswer(vector<char>vec, bool equal = true, bool style = true)
{
	if (style)
	{
		if (equal)
			cout << "=";
		for (int i = 0; i < vec.size(); i++)
			cout << vec[i];
	}
	else
	{
		for (int i = 0; i < vec.size(); i++)
			printf("\'%c\', ", vec[i]);
	}
}

vector<char> VecInttoChar(vector<int>vec)
{
	vector <char> out;
	for (int i = 0; i < vec.size(); i++)
		out.push_back((char)(vec[i] + 48));
	return out;
}

vector<char> FilterZero(vector<char>vec)
{
	while (true)
	{
		if (vec[0] != '0')
			break;
		else if (vec[0] == '0' and vec[1] == '.')
			break;
		else if (vec[0] == '0' and vec[1] == '0')
			vec.erase(vec.begin());
		else if (vec[0] == '0' and vec[1] != '0')
		{
			if (vec[1] == '.')
				break;
			else
				vec.erase(vec.begin());
		}
	}
	return vec;
}

vector<char> InsertPoint(vector<char>vec, int decimal)
{
	if (vec.size() < decimal)
		vec.insert(vec.begin(), decimal - vec.size(), '0');
	vec.insert(vec.end() - decimal, '.');
	return vec;
}

vector<char> StringtoCharVec(string str)
{
	vector <char> vec;
	for (int i = 0; i < str.length(); i++)
		vec.push_back(str[i]);
	return vec;
}

vector<char> MovePoint(vector<char> vec, int move)
{
	int Before = findpoint(&vec[0], vec.size());
	if (Before == -1)
		Before = 0;
	else
		vec.erase(vec.begin() + Before);
	int New = Before + move;
	if (New > DecimalPlaces(&vec[0], vec.size()))
		vec.insert(vec.end(), New - DecimalPlaces(&vec[0], vec.size()), '0');
	else if (New == 0)
	{
		vec.insert(vec.begin(), '.');
		vec.insert(vec.begin(), '0');
	}
	else if (New < 0)
	{
		while (New <= 1)
		{
			vec.insert(vec.begin(), '0');
			New++;
		}
		vec.insert(vec.begin() + New, '0');
	}
	
	return vec;
}

vector<int> VecChartoInt(vector<char>vec)
{
	vector <int> out;
	for (int i = 0; i < vec.size(); i++)
		out.push_back((char)vec[i] - 48);
	return out;
}

vector<int> AddinMul(vector<int>num1, vector<int>num2)
{
	//前补0对齐
	if (num1.size() > num2.size())
		num2.insert(num2.begin(), num1.size() - num2.size(), 0);
	if (num1.size() < num2.size())
		num1.insert(num1.begin(), num2.size() - num1.size(), 0);

	vector <int> ans;
	int unit = 0;
	int ten = 0;
	int temp = 0;

	for (int i = num1.size() - 1; i >= 0; i--)
	{
		temp = num1[i] + num2[i] + ten;
		unit = temp / 1 % 10;
		ten = temp / 10 % 10;
		ans.push_back(unit);
	}
	if (ten != 0)
		ans.push_back(ten);
	reverse(ans.begin(), ans.end());
	return ans;
}

vector<int> SubinDiv(vector<int>num1, vector<int>num2)
{
	//传参时保证num1 > num2
	//补0对齐
	if (num1.size() > num2.size())
		num2.insert(num2.begin(), num1.size() - num2.size(), 0);
	
	vector <int> vec;
	int temp = 0;
	for (int i = num1.size() - 1; i >= 0; i--)
	{
		if (num1[i] >= num2[i])
			temp = num1[i] - num2[i];
		else
		{
			temp = num1[i] - num2[i] + 10;
			num1[i - 1]--;
		}
		vec.push_back(temp);
	}
	reverse(vec.begin(), vec.end());
	return vec;
}

vector<int> ReplaceVar(vector<int>vec, vector<int>child, int replacepoint, int filter = false)
{
	int j = child.size() - 1;
	for (int i = replacepoint; i >= 0; i--)
	{
		if (j >= 0)
			vec[i] = child[j];
		else
			vec[i] = 0;
		j--;
	}
	if (filter)
	{
		for (int i = 0; vec[0] == 0; i++)
			vec.erase(vec.begin());
	}
	return vec;
}

vector<int> FilterVecZero(vector<int> vec)
{
	
	for (int i = 0; vec[0] == 0; i++)
	{
		if (vec.size() == 1 and vec[0] == 0)
		{
			vec.clear();
			return vec;
		}
		vec.erase(vec.begin());
	}
	return vec;
}

vector<int> ExtractVec(vector<int>vec, int begin, int end)
{
	vector <int> out;
	for (int i = begin; i <= end; i++)
		out.push_back(vec[i]);
	return out;
}

vector<string> split(const string& src, string separate_character)
{
	vector<string> strs;
	int separate_characterLen = separate_character.size();
	int lastPosition = 0, index = -1;
	while (-1 != (index = src.find(separate_character, lastPosition)))
	{
		strs.push_back(src.substr(lastPosition, index - lastPosition));
		lastPosition = index + separate_characterLen;
	}
	string lastString = src.substr(lastPosition);
	if (!lastString.empty())
		strs.push_back(lastString);
	return strs;
}
