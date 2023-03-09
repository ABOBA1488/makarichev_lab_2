#include <iostream>
#include <fstream>
#include <stack>
#include <string>

struct stack
{
    int maxsize;    
    char top;
    char *items;
};
struct stack* newStack(int capacity)
{
    struct stack *pt = (struct stack*)malloc(sizeof(struct stack));
 
    pt->maxsize = capacity;
    pt->top = '\0';
    pt->items = (char*)malloc(sizeof(char) * capacity);
 
    return pt;
}
 

int size(struct stack *pt) {
    return pt->top + 1;
}
 

bool isEmpty(struct stack *pt) {
    return pt->top == '\0';       
}
 
void push(struct stack *pt, char x)
{
    pt->items[++pt->top] = x;
}
 
char peek(struct stack *pt)
{
    if (!isEmpty(pt)) 
    {
        return pt->items[pt->top];
    }
    return '\0';
}
 

int pop(struct stack *pt)
{
    return pt->items[pt->top--];
}

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
	if (a == '+' || a == '-' || a == '|')
	{
		return 2;
	}
	if (a == '*' || a == '/' || a == '&')
	{
		return 3;
	}
	if (a == '^')
	{
		return 4;
	}
	return 5;
}

int main() 
{
	char CurrentChar;
	std::string CurrentStr = "";
	std::string ExitStr="";
	//std::stack <char> stack;
	struct stack *pt = newStack(100000);
	std::ifstream fin("input.txt");
	std::ofstream fout("exit.txt");
	while (!fin.eof())
	{
		ExitStr = "";
		getline(fin, CurrentStr);
		for (int i = 0; i < CurrentStr.length(); i++)
		{
			CurrentChar = CurrentStr[i];

			if ((CurrentChar >= '0' && CurrentChar <= '9') ||(CurrentChar>='a' && CurrentChar<='z'))
			{
				ExitStr += CurrentChar;
			}
			else if ((CurrentChar == '+' || CurrentChar == '-' || CurrentChar == '*' || CurrentChar == '/'|| CurrentChar == '|' || CurrentChar == '&' || CurrentChar == '!') && isEmpty(pt))
			{
				//stack.push(CurrentChar);
				push(pt,CurrentChar);
			}
			else if ((CurrentChar == '+' || CurrentChar == '-' || CurrentChar == '*' || CurrentChar == '/'|| CurrentChar == '|' || CurrentChar == '&' || CurrentChar == '!') && !isEmpty(pt) && OperationPriority(CurrentChar) > OperationPriority(peek(pt)))
			{
				//stack.push(CurrentChar);
				push(pt,CurrentChar);
			}
			else if ((CurrentChar == '+' || CurrentChar == '-' || CurrentChar == '*' || CurrentChar == '/'|| CurrentChar == '|' || CurrentChar == '&' || CurrentChar == '!') && !isEmpty(pt) && OperationPriority(peek(pt)) >= OperationPriority(CurrentChar))
			{
				while (!isEmpty(pt) && OperationPriority(peek(pt)) >= OperationPriority(CurrentChar))
				{
					ExitStr += peek(pt);
					pop(pt);
					//stack.pop();
				}
				push(pt,CurrentChar);
				//stack.push(CurrentChar);
			}
			else if (CurrentChar == '(')
			{
			    push(pt,CurrentChar);
				//stack.push(CurrentChar);
			}
			else if (CurrentChar == ')')
			{

				while (!isEmpty(pt) && peek(pt) != '(')
				{
					ExitStr += peek(pt);
					pop(pt);
				//	stack.pop();
				}
				pop(pt);
				//stack.pop();
			}
			else if (CurrentChar == ';')
			{
				while (!isEmpty(pt))
				{
					ExitStr += peek(pt);
					pop(pt);
					//stack.pop();
				}
			}
		}
		fout << ExitStr <<std::endl;
	}

}
