#include<iostream>
#include<fstream>

//dynamic stack
struct Node
{
	char data;
	Node* prev;
};

//dynamic queue
struct NodeQ
{
	int data;
	NodeQ* next;
};
struct Fifo
{
	NodeQ* head;
	NodeQ* tail;
};
void initFifo(Fifo& queue)
{
	queue.head = nullptr;
	queue.tail = nullptr;
}
void pushBack(Fifo& que, int key)
{
	NodeQ* temp = new NodeQ; //create empty node for queue
	temp->data = key; //put key into queue
	temp->next = nullptr;
	if (que.tail) //if there are elements in the queue
	{
		que.tail->next = temp; //remove tail pointer on the new element
	}
	else
	{
		que.head = temp; //if queue is empty element temp goes to head
	}
	que.tail = temp;
}
int popFront(Fifo& que)
{
	int key;
	NodeQ* temp = que.head; //copy of the head of the queue
	if (que.head == nullptr) return 0; //if queue is empty quit the function
	else
	{
		key = que.head->data; //insert data from queue head into key
	}
	que.head = temp->next;
	delete temp;
	return key;
}

//dynamic stack
void push(Node*& top, char key)
{
	Node* temp = new Node; //creating empty Node
	temp->data = key; //putting key into the stack
	temp->prev = top; //putting pointer to previous top of the stack
	top = temp; //changing the top
}
char pop(Node*& top)
{
	char key = 0;
	if (top != nullptr)
	{
		key = top->data; //assign key data which we want to delete
		Node* temp = top->prev; //create temp pointer to previous element in order to save it after deleting
		delete top; //delete top of the stack
		top = temp;
	}
	return key;
}
char top(Node* top) //watch what is on the top
{
	return top->data;
}
void revPolNot(char*& str)
{
	Node* stack = nullptr;
	char* newStr = new char[100];
	int i = 0; //for str
	int j = 0; //for newStr cause newStr must have backspaces between numbers
	while (str[i])
	{
		if (isdigit(str[i])) //put in newStr if isdigit and then put backspace
		{
			while (isdigit(str[i]))
			{
				newStr[j++] = str[i++];
			}
			newStr[j++] = ' ';
			i--;
		}
		else if (str[i] == '(') push(stack, str[i]);
		else if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') && !stack) //if operator met and stack is empty
		{
			push(stack, str[i]);
		}
		else if (str[i] == '*' || str[i] == '/')
		{
			if (top(stack) == '+' || top(stack) == '-' || top(stack) == '(') push(stack, str[i]);
			else
			{
				newStr[j++] = pop(stack);
				newStr[j++] = ' ';
				push(stack, str[i]);
			}
		}
		else if (str[i] == '+' || str[i] == '-')
		{
			if (top(stack) != '(')
			{
				newStr[j++] = pop(stack);
				newStr[j++] = ' ';
			}
			push(stack, str[i]);
		}
		else if (str[i] == ')')
		{
			while (top(stack) != '(')
			{
				newStr[j++] = pop(stack);
				newStr[j++] = ' ';
			}

			pop(stack);
		}

		i++;
	}

	while (stack)
	{
		newStr[j++] = pop(stack);
		newStr[j++] = ' ';
	}

	newStr[j] = '\0';
	delete[]str;
	str = newStr;
	}

//ring array
struct ringArray
{
	const static size_t size = 5;
	int queue[size];
	size_t tail;
	size_t head;
};
void push(ringArray& q, int key)
{
	if (q.tail + 1 == q.head || q.tail + 1 == q.size && q.head == 0)
	{
		std::cout << "Queue is full";
		return;
	}
	q.tail++;
	if (q.tail == q.size) // create ring
	{
		q.tail = 0;
	}
	q.queue[q.tail] = key;
}
int popFrontRing(ringArray& q)
{
	if (q.head == q.tail)
	{
		std::cout << "Queue is empty.\n";
		return 0;
	}
	q.head++;
	if (q.head == q.size)
		q.head = 0;
	int key;
	key = q.queue[q.head];
}

void initRing(Fifo& q)
{
	q.head = nullptr;
	q.tail = nullptr;
}

int main()
{
	// reverse polish notation
	std::ifstream fin("input.txt");
	if (fin)
	{
		char* str = new char[100];
		fin.getline(str, 100);
		revPolNot(str);
		std::cout << str << "\n";
		delete[]str;
	}
	else
	{
		std::cout << "Not file\n";
	}

	

	system("pause");
	return 0;
}