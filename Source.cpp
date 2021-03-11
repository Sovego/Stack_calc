#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string>
struct Node
{
    std::string value;
    Node* next;
};

bool is_empty(Node* top)
{
	return top==nullptr;
		
	
}
Node* make_stack(std::string b)
{
    
	Node* current { new Node};
   
    current->value = b;
    current->next = nullptr;
    return current;
}
Node* add_element_top(Node* top,std::string num)
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
		if(in_str[0]=='-')
		{
			in_str= '0' + in_str;
		}
	for (int i = 1; i < in_str.length(); ++i) 
		if (in_str[i - 1] == '(' && (in_str[i] == '-' || in_str[i] == '+')) 
			in_str.insert(i,"0");
	for (int i=0;i < in_str.length();i++)
	{
		switch(in_str[i])
		{
		case '+': if (is_empty(top))
			{
				std::string s;
				
					s+=in_str[i];
				
				top=make_stack(s);
			
			} else if(top->value=="*" || top->value=="/" || top->value=="+" || top->value=="-")
			{
				out_str+=top->value;
				out_str+=" ";
				top=del_top(top);
				if(is_empty(top))
				{
					std::string s;
				
					s+=in_str[i];
					top=make_stack(s);
					
				}else 
				{
					std::string s;
				
					s+=in_str[i];
					add_element_top(top,s);
				}
			} else
			{
				std::string s;
				
					s+=in_str[i];
				top=add_element_top(top,s);
			}
			break;
		case '-': 
			if (is_empty(top))
			{
				std::string s;
				
					s+=in_str[i];
				top=make_stack(s);
			
			} else if(top->value=="*" || top->value=="/" || top->value=="+" || top->value=="-")
			{
				out_str+=top->value;
				out_str+=" ";
				top=del_top(top);
				if(is_empty(top))
				{
					std::string s;
				
					s+=in_str[i];
					top=make_stack(s);
					
				}else 
				{std::string s;
				
					s+=in_str[i];
					add_element_top(top,s);
				}
			} else
			{
				std::string s;
				
					s+=in_str[i];
				top=add_element_top(top,s);
			}
			break;
		case '*': if (is_empty(top))
			{
			std::string s;
				
					s+=in_str[i];
				top=make_stack(s);
			
			} else if(top->value=="*" || top->value=="/")
			{
				out_str+=top->value;
				top=del_top(top);
				out_str+=" ";
				if(is_empty(top))
				{
					std::string s;
				
					s+=in_str[i];
					top=make_stack(s);
					
				}else 
				{std::string s;
				
					s+=in_str[i];
					add_element_top(top,s);
				}
			} else
			{
				std::string s;
				
					s+=in_str[i];
				top=add_element_top(top,s);
			}
			break;
		case '/': if (is_empty(top))
			{
			std::string s;
				
					s+=in_str[i];
				top=make_stack(s);
			
			} else if(top->value=="*" || top->value=="/")
			{
				out_str+=top->value;
				out_str+=" ";
				top=del_top(top);
				if(is_empty(top))
				{
					std::string s;
				
					s+=in_str[i];
					top=make_stack(s);
					
				}else 
				{std::string s;
				
					s+=in_str[i];
					add_element_top(top,s);
				}
			} else
			{
				std::string s;
				
					s+=in_str[i];
				top=add_element_top(top,s);
			}
			break;
		case '(': if (is_empty(top))
			{
			std::string s;
				
					s+=in_str[i];
				top=make_stack(s);
			
			} else
			{
				std::string s;
				
					s+=in_str[i];
				top=add_element_top(top,s);
				
			}
			break;
		case ')': if (is_empty(top))
		{
			std::cerr << "ERROR";
		}
			while (top->value!="(")
			{
				
				out_str+=top->value;
				top=del_top(top);
				out_str+=" ";
			}
			top=del_top(top);
			break;
		default:
				if(in_str[i]!=' ')
				{
				int a{i};
				while(in_str[a]!='+' && in_str[a]!='-' && in_str[a]!='/' && in_str[a]!='*' && in_str[a]!='(' && in_str[a]!=')' && a<in_str.length())
				{
					out_str+=in_str[a];
					a++;
				}
				out_str+=" ";
				for (int j=i;j<a;j++)
				{
					in_str[j]=' '; 
				}
				}
				break;
				
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
			double a{atof(top->value.c_str())};
			top=del_top(top);
			double b{atof(top->value.c_str())};
			top=del_top(top);
			switch (out_str[i])
			{
			case '+':top=add_element_top(top,std::to_string(b+a));
					break;
			case '-':top=add_element_top(top,std::to_string(b-a));
					break;
			case '*':top=add_element_top(top,std::to_string(b*a));
					break;
			case '/':top=add_element_top(top,std::to_string(b/a));
					break;
			}
		} else if (out_str[i]!=' ')	
		{
			std::string s;
			int a{i};
		while(a<out_str.length() && out_str[a]!=' ')
		{
			s+=out_str[a];
			a++;
		}
			if (is_empty(top))
			{
				top=make_stack(s);
			} else
			{
			top=add_element_top(top,s);
			}
		for (int j=i;j<a;j++)
		{
			out_str[j]=' ';
		}
		}
		
		 
	}
	std::cout << std::endl << top->value;
}