#include<iostream>
#include<queue>

using namespace std;

struct Node
{
	int color;
	Node* next;
	Node(int color, Node* next = nullptr) : color(color), next(next) {}
};
//вмъкване на елемент в края на списъка
void insertAtTheEnd(Node** list, int newValue)
{
	Node* newNode = new Node(newValue, nullptr);
	if (*list == nullptr)
	{
		*list = newNode;
		return;
	}
	Node* last = *list;
	while (last->next != nullptr)
	{
		last = last->next;
	}
	last->next = newNode;
}
//вмъкване след даден елемент
void insertAfter(Node* iter, int newValue)
{
	if (iter == nullptr)
	{
		cout << "previous can not be NULL";
		return;
	}
	Node* newNode = new Node(newValue, iter->next);
	iter->next = newNode;
}
//изтрива елемент на дадена позиция
void removePos(Node*& head, int pos)
{
	Node* iter = head;
	for (int i = 0; i < pos; i++)
	{
		iter = iter->next;
	}
	Node* toDelete = iter->next;
	iter->next = iter->next->next;
	delete toDelete;
}
int findSameElem1(Node* head, int pos, int elem)
{
	Node* iter = head;
	int i = 0;
	int count = 0;
	while (iter != nullptr)
	{
		i++;
		if (iter->color == elem)
		{
			i--;
			while (iter->color == elem)
			{

				count++;
				i++;
				iter = iter->next;
			}
			if (i >= pos)
			{
				return count;
			}
			else
			{
				count = 0;
			}
		}
		iter = iter->next;
	}
}
int returnColor(Node* head, int pos)
{
	Node* iter = head;
	int i = 0;
	while (i < pos)
	{
		iter = iter->next;
	}
	return iter->color;
}

//принтиране на списък
void print(Node* list)
{
	Node* current = list;
	while (current != nullptr)
	{
		cout << current->color << " ";
		current = current->next;
	}
	cout << endl;
}
int findSame(Node* head, int pos)
{
	Node* iter = head;
	int i = 0;
	int count = 0;
	while (iter != nullptr)
	{
		
		if (iter->color == iter->next->color)
		{
			i--;
			while (iter->color == iter->next->color)
			{
				count++;
				i++;
				iter = iter->next;
			}
			if (i >= pos)
			{
				return count;
			}
			else
			{
				count = 0;
			}
		}
		iter = iter->next;
	}
}

void game(Node* head, int q, queue<int> numberQ, queue<int> colorQ)
{
	int i = 0;
	while (i < q)
	{
		Node* iter = head;
		int j = 0;
		if (!numberQ.empty() && !colorQ.empty())
		{
			int Pi = numberQ.front();
			int Qi = colorQ.front();

			while (j < Pi)
			{
				iter = iter->next;
				j++;
			}
			insertAfter(iter, Qi);
			print(head);
			int k = 0;
			Node* temp1 = head;
			if ((findSameElem1(temp1, Pi, Qi)) >= 3)
			{
				int br = 0;
				
				int same = findSameElem1(temp1, Pi, Qi);
				br += same;
				while (k < same && temp1 != nullptr)
				{
					//Node* temp = head;
					removePos(temp1, Pi);
					k++;
					}
				cout << br << endl;
			}
			else
			{
				cout << 0 << endl;
			}
			//print(head);
			numberQ.pop();
			colorQ.pop();
			if (head == nullptr)
			{
				cout << "Game Over" << endl;
			}
		}
		i++;
	}
	if (head != nullptr)
	{
		print(head);
	}
	else
	{
		cout << "-1" << endl;
	}
}

int main()
{
	int n;
	cout << "N > ";
	cin >> n;

	cout << "Colors > ";
	queue<int> colors;
	int i = 0;
	int temp = 0;
	while (i < n)
	{
		cin >> temp;
		colors.push(temp);
		i++;
	}

	//Създава лист от цветовете
	Node* head = new Node(colors.front());
	colors.pop();
	while (!colors.empty())
	{
		insertAtTheEnd(&head, colors.front());
		colors.pop();
	}

	int q;
	cout << "Q > ";
	cin >> q;
	temp = 0;
	int temp1 = 0;
	queue<int> numberQ;
	queue<int> colorQ;
	i = 0;
	//Създава две опашки от заявки, една за номера на топчето, друга за цвета
	cout << "Requests: " << endl;
	while (i < q)
	{
		cin >> temp;
		cin >> temp1;
		numberQ.push(temp);
		colorQ.push(temp1);
		i++;
	}

	game(head, q, numberQ, colorQ);

	return 0;


}