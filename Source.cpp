#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string>
struct Node
{
    char value;
    Node* next;
};

int ChartoInt(char a)
{
	if ((int)a > 0) return (int)a - 48;
}
char InttoChar(int a)
{
	if (a >= 0 && a < 10) return (char)a + 48;
}
bool is_empty(Node* top)
{
	return top==nullptr;
		
	
}
Node* make_stack(char b)
{
    
	Node* current { new Node};
   
    current->value = b;
    current->next = nullptr;
    return current;
}
Node* add_element_top(Node* top,char num)
{
	Node* current { new Node};
	current->value = num;
	current->next = top;
	return current;
}
 Node* del_top(Node* front)
{
	 Node* temp {front->next};
	delete front;
	return(temp); // новый корень списка
}
void del_all(Node* top)
{
	Node* temp {top};
    Node* current;
	while (temp->next != nullptr)
	{
		temp = temp->next;
		if (temp->next==nullptr)
		{
			current = temp;
			delete current;
			return;
		}
		else
		{
			current = temp->next;
			temp->next = current->next;
			delete current;
		}
	}
}
void output_list(Node* top)
{
	for (Node* current{top}; current != nullptr; current = current->next)
	{
		std::cout << current->value << "  ";
	}
	std::cout << std::endl;
}

int main()
{
	std::string in_str,out_str;
	Node* top=nullptr;
	std::cout << "Input ";
	std::cin >> in_str;
	for (int i=0;i < in_str.length();i++)
	{
		switch(in_str[i])
		{
		case '+': if (is_empty(top))
			{
				top=make_stack(in_str[i]);
			
			} else if(top->value=='*' || top->value=='/' || top->value=='+' || top->value=='-')
			{
				out_str+=" ";
				out_str+=top->value;
				
				top=del_top(top);
				if(is_empty(top))
				{
					top=make_stack(in_str[i]);
					
				}else add_element_top(top,in_str[i]);
			} else
			{
				top=add_element_top(top,in_str[i]);
			}
			break;
		case '-': if (is_empty(top))
			{
				top=make_stack(in_str[i]);
			
			} else if(top->value=='*' || top->value=='/' || top->value=='+' || top->value=='-')
			{
				out_str+=" ";
				out_str+=top->value;
				
				top=del_top(top);
				if(is_empty(top))
				{
					top=make_stack(in_str[i]);
					
				}else add_element_top(top,in_str[i]);
			} else
			{
				top=add_element_top(top,in_str[i]);
			}
			break;
		case '*': if (is_empty(top))
			{
				top=make_stack(in_str[i]);
			
			} else if(top->value=='*' || top->value=='/')
			{
				out_str+=" ";
				out_str+=top->value;
				top=del_top(top);
				
				if(is_empty(top))
				{
					top=make_stack(in_str[i]);
					
				}else add_element_top(top,in_str[i]);
			} else
			{
				top=add_element_top(top,in_str[i]);
			}
			break;
		case '/': if (is_empty(top))
			{
				top=make_stack(in_str[i]);
			
			} else if(top->value=='*' || top->value=='/')
			{
				out_str+=" ";
				out_str+=top->value;
				
				top=del_top(top);
				if(is_empty(top))
				{
					top=make_stack(in_str[i]);
					
				}else add_element_top(top,in_str[i]);
			} else
			{
				top=add_element_top(top,in_str[i]);
			}
			break;
		case '(': if (is_empty(top))
			{
				top=make_stack(in_str[i]);
			
			} else
			{
				top=add_element_top(top,in_str[i]);
				
			}
			break;
		case ')': if (is_empty(top))
		{
			std::cerr << "ERROR";
		}
			while (top->value!='(')
			{
				out_str+=" ";
				out_str+=top->value;
				top=del_top(top);
				
			}
			top=del_top(top);
			break;
		default: if(in_str[i+1]=='*' || in_str[i+1]=='/' || in_str[i+1]=='+' || in_str[i+1]=='-')
		{
			out_str+=in_str[i];
			out_str+=" ";
		} else 
		{
			
			out_str+=in_str[i];
			out_str+=" ";
		}
	}
	while (top!=nullptr)
	{
		out_str+=" ";
		out_str+=top->value;
		
		top=del_top(top);
	}
	std::cout << std::endl << out_str;
	
	for (int i=0;i < out_str.length();i++)
	{
		if (out_str[i]=='*' || out_str[i]=='/' || out_str[i]=='+' || out_str[i]=='-')
		{
			int a{ChartoInt(top->value)};
			top=del_top(top);
			int b{ChartoInt(top->value)};
			top=del_top(top);
			switch (out_str[i])
			{
			case '+':top=add_element_top(top,InttoChar(a+b));
					break;
			case '-':top=add_element_top(top,InttoChar(a-b));
					break;
			case '*':top=add_element_top(top,InttoChar(a*b));
					break;
			case '/':top=add_element_top(top,InttoChar(a/b));
					break;
			}
		} else if (out_str[i]!=' ')
			if(out_str[i+1]==' ')
		{
			if (is_empty(top))
			{
				top=make_stack(out_str[i]);
			} else
				top=add_element_top(top,out_str[i]);
			
		} else
		{
			if (is_empty(top))
			{
				top=make_stack(out_str[i]+out_str[i+1]);
			} else
			top=add_element_top(top,out_str[i]+out_str[i+1]);
			out_str[i+1]=' ';
		}
	}
	std::cout << std::endl << top->value;
}

}

