#include<iostream>
#include<fstream>
#include<stack>
#include<queue>

const int BUFF_SIZE = 1024;

//Помощна функция за намиране на mod
int mod(int num, int num2)
{
	return num % num2;
}
//Помощна функция за намиране на факториел
int fact(int num)
{
	if (num > 1)
	{
		return (num * fact(num - 1));
	}
	else
	{
		return 1;
	}
}
//Функции за пресмятане на изразите
int f(int num)
{
	num *= num;
	num = mod(num, 100);
	return num;
}
int g(int num)
{
	num = mod(num, 5);
	return fact(num);
}
int m(int num1, int num2)
{
	if (num1 <= num2)
	{
		return num1;
	}
	else
	{
		return num2;
	}
}
//Функция за преобразуване на char(числатва в изразите от файла) в int
int charToInt(char c)
{
	int n = 0;
	switch (c)
	{
	case '0': n = 0; break;
	case '1': n = 1; break;
	case '2': n = 2; break;
	case '3': n = 3; break;
	case '4': n = 4; break;
	case '5': n = 5; break;
	case '6': n = 6; break;
	case '7': n = 7; break;
	case '8': n = 8; break;
	default: n = 9;
	}
	return n;
}
//Функция, която връща цяло число от елементите на подадената опашката
int toNumber(std::queue<int> s2)
{
	int num = 0;
	int count = 0;
	int i = 1;
	while (!s2.empty())
	{
		if (count == 0)
		{
			num = num + s2.front();
		}
		else
		{
			i = i * 10;
			num = num * i + s2.front();
		}
		count++;
		s2.pop();
	}
	return num;
}
//Функция за оценка на израз
int formula(char* s)
{
	std::stack<char> s1;
	std::stack<int> s2;
	std::queue<int> temp;

	int result = 0;
	char c;
	int i = 0, len = strlen(s);

	while (i < len)
	{
		if (s[i] == 'f' || s[i] == 'g' || s[i]=='m')
		{
			s1.push(s[i]);       //записва индикаторите на изразите в стек s1
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			while (s[i] >= '0' && s[i] <= '9')
			{
				temp.push(charToInt(s[i]));
				i++;
			}
			s2.push(toNumber(temp));   //записва вече преобразуваните числа в s2
			while (!temp.empty())
			{
				temp.pop();
			}
			i--;
		}
		else if (s[i] == ')')
		{
			c = s1.top();
			s1.pop();
			//спрямо индикаторите в s1 се вика съответната функция
			if (c == 'g')
			{
				result = (g(s2.top()));
				s2.pop();
				s2.push(result);
			}
			else if (c == 'f')
			{
				result = (f(s2.top()));
				s2.pop();
				s2.push(result);
			}
			else if (c == 'm')
			{
				int t = 0;
				t=s2.top();
				s2.pop();
				result = (m(t,s2.top()));
				s2.pop();
				s2.push(result);
			}
		}
		i++;
	}
	int res = 0;
	res = s2.top();

	return res;
}
int main()
{
	std::ifstream file("text.txt");
	if (!file.is_open())
	{
		std::cout << "Error!" << std::endl;
		return -1;
	}
	
	int i = 0;
	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	char s[100];
	
	while (i<length)    
	{
		char c;
		file.get(c);
		
		std::cout << c;
		s[i] = c;
		if (c == '\n')
		{
			std::cout <<"->"<< formula(s) <<std::endl;
			i++;
		}
        i++;	
	}
	file.close();

	return 0;
}
