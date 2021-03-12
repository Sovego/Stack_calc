#include <iostream>
#include <string>

struct node
{
	std::string value;
	node* next{};
};

bool is_empty(node* top)
{
	return top == nullptr;
}

node* make_stack(std::string b)
{
	node* current{new node};

	current->value = std::move(b);
	current->next = nullptr;
	return current;
}

node* add_element_top(node* top, std::string num)
{
	node* current{new node};
	current->value = std::move(num);
	current->next = top;
	return current;
}

node* del_top(node* front)
{
	node* temp{front->next};
	delete front;
	return (temp);
}

void del_all(node* top)
{
	node* temp{top};
	node* current;
	while (temp->next != nullptr)
	{
		temp = temp->next;
		if (temp->next == nullptr)
		{
			current = temp;
			delete current;
			return;
		}
		current = temp->next;
		temp->next = current->next;
		delete current;
	}
}

void output_list(node* top)
{
	for (node* current{top}; current != nullptr; current = current->next)
	{
		std::cout << current->value << "  ";
	}
	std::cout << std::endl;
}

int getPriority(char c) {
	if (c == '-' || c == '+') return 1;
	else if (c == '*' || c == '/') return 2;
	return 0;
}

std::string ToStackCalculator(std::string str, struct node* Stack) {
	node* TempStack = new node;
	std::string x;
	while (str.length() > 0) {
		x = "";
		if (str[0] == '(') {		
			Stack=add_element_top(Stack, "(");	
			str.erase(0, 1);		
		}							
		else if (str[0] == ')') {								
			while (Stack->value != "(") {				
				TempStack=add_element_top(TempStack, Stack->value);	
				Stack=del_top(Stack);							
			}													
			Stack=del_top(Stack);									
			str.erase(0, 1);									
		}														 
		else if (!isdigit(str[0]) && str[0] != ',') {												
			x = str[0];																				
			while (Stack!=nullptr && getPriority(Stack->value[0]) >= getPriority(x[0])) {	
				TempStack=add_element_top(TempStack, Stack->value);										
				Stack=del_top(Stack);																
			}																						
			Stack=add_element_top(Stack, x);																	
		}																							
		else {															
			for (char& c : str) if (isdigit(c) || c == ',') x = x + c;	
			else break;													
			TempStack=add_element_top(TempStack, x);									
		}																
		str.erase(0, x.length());									
	}																	
	while (Stack!=nullptr) {
		TempStack=add_element_top(TempStack, Stack->value);
		Stack=del_top(Stack);
	}
	x="";
	while(TempStack!=nullptr)
	{
		x=" " + TempStack->value + x;
		TempStack=del_top(TempStack);
	}
	return x;
}
int main()
{
	std::string in_str;
	node* top = nullptr;
	std::cout << "Input ";
	std::cin >> in_str;
	if (in_str[0] == '-')
	{
		in_str = '0' + in_str;
	}
	for (int i = 1; i < in_str.length(); ++i)
		if (in_str[i - 1] == '(' && (in_str[i] == '-' || in_str[i] == '+'))
			in_str.insert(i, "0");
	
	std::string out_str = ToStackCalculator(in_str, top);
	std::cout << std::endl << out_str;


	for (int i = 0; i < out_str.length(); i++)
	{
		if (out_str[i] == '*' || out_str[i] == '/' || out_str[i] == '+' || out_str[i] == '-')
		{
			double a{atof(top->value.c_str())};
			top = del_top(top);
			double b{atof(top->value.c_str())};
			top = del_top(top);
			switch (out_str[i])
			{
			case '+': top = add_element_top(top, std::to_string(b + a));
				break;
			case '-': top = add_element_top(top, std::to_string(b - a));
				break;
			case '*': top = add_element_top(top, std::to_string(b * a));
				break;
			case '/': top = add_element_top(top, std::to_string(b / a));
				break;
			default: break;
			}
		}
		else if (out_str[i] != ' ')
		{
			std::string s;
			int a{i};
			while (a < out_str.length() && out_str[a] != ' ')
			{
				s += out_str[a];
				a++;
			}
			if (is_empty(top))
			{
				top = make_stack(s);
			}
			else
			{
				top = add_element_top(top, s);
			}
			for (int j = i; j < a; j++)
			{
				out_str[j] = ' ';
			}
		}
	}
	std::cout << std::endl << top->value;
}
