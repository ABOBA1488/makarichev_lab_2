#include <iostream>
#include <fstream>
#include <stack>
#include <string>
int OperationPriority(char a) 
{
	if (a=='(') 
	{
		return 0;
	}
	if (a == ')')
	{
		return 1;
	}
	if (a == '+' || a == '-')
	{
		return 2;
	}
	if (a == '*' || a == '/')
	{
		return 3;
	}
	if (a == '^')
	{
		return 4;
	}
	return 0;
}

int main() 
{
	char CurrentChar;
	std::string CurrentStr = "";
	std::string ExitStr="";
	std::stack <char> stack;
	std::ifstream fin("input.txt");
	std::ofstream fout("exit.txt");
	while (!fin.eof())
	{
		ExitStr = "";
		getline(fin, CurrentStr);
		for (int i = 0; i < CurrentStr.length(); i++)
		{
			CurrentChar = CurrentStr[i];

			if (CurrentChar >= '0' && CurrentChar <= '9')
			{
				ExitStr += CurrentChar;
			}
			else if ((CurrentChar == '+' || CurrentChar == '-' || CurrentChar == '*' || CurrentChar == '/') && stack.empty())
			{
				stack.push(CurrentChar);
			}
			else if ((CurrentChar == '+' || CurrentChar == '-' || CurrentChar == '*' || CurrentChar == '/') && !stack.empty() && OperationPriority(CurrentChar) > OperationPriority(stack.top()))
			{
				stack.push(CurrentChar);
			}
			else if ((CurrentChar == '+' || CurrentChar == '-' || CurrentChar == '*' || CurrentChar == '/') && !stack.empty() && OperationPriority(stack.top()) >= OperationPriority(CurrentChar))
			{
				while (!stack.empty() && OperationPriority(stack.top()) >= OperationPriority(CurrentChar))
				{
					ExitStr += stack.top();
					stack.pop();
				}
				stack.push(CurrentChar);
			}
			else if (CurrentChar == '(')
			{
				stack.push(CurrentChar);
			}
			else if (CurrentChar == ')')
			{

				while (!stack.empty() && stack.top() != '(')
				{
					ExitStr += stack.top();
					stack.pop();
				}
				stack.pop();
			}
			else if (CurrentChar == ';')
			{
				while (!stack.empty())
				{
					ExitStr += stack.top();
					stack.pop();
				}
			}
		}
		fout << ExitStr <<std::endl;
	}

}