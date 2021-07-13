#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <climits>
#include "myVector.h"

struct Node
{
	int value;
	Node** table;
};

void getLine(char& command, int& value);
Node* createNode(int size, int value);
void insert(Node* root, int n, int k, int value);
Node** search(Node* root, int n, int k, int value);
void print(Node* root, int n, int k);
void printNode(Node* actualNode, int size);
void lookFor(Node* root, int n, int k, int value);
void deleteNode(Node* root, int n, int k, int value);
bool isLeaf(Node* node, int size);
void clear(Node* root, int n, int k);
void clearNode(Node* node, int size);

int main()
{
	int tests, min, max, n, k;
	scanf("%d %d %d %d %d", &tests, &min, &max, &n, &k);
	getchar();
	getchar();

	Node* root; root = createNode(n, INT_MIN);
	char command;
	int value;
	while (tests--)
	{
		command = 0;
		value = -1;

		getLine(command, value);

		switch (command)
		{
		case 'I':
			insert(root, n, k, value);
			break;
		case 'L':
			lookFor(root, n, k, value);
			break;
		case 'D':
			deleteNode(root, n, k, value);
			break;
		case 'P':
			print(root, n, k);
			printf("\n");
			break;
		default:
			printf("Wrong input command!\n");
			break;
		}
	}
	clear(root, n, k);
	return 0;
}


void clear(Node* root, int n, int k)
{
	Node** actualNode = &root;
	for (int i = 0; i < n; i++)
	{
		if ((*actualNode)->table[i] != NULL)
		{
			clearNode((*actualNode)->table[i], k);
		}
	}
	delete[] root->table;
	root->table = NULL;
	delete root;
	root = NULL;
}


void clearNode(Node* node, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (node->table[i] != NULL)
		{
			clearNode(node->table[i], size);
		}
	}
	delete[] node->table;
	node->table = NULL;
	delete node;
	node = NULL;
}


int searchToDelete(Node* node, int size, int k)
{
	Node** actualNode = &node;
	int result = (*actualNode)->value;
	for (int i = 0; i < size; i++)
	{
		if ((*actualNode)->table[i] != NULL)
		{
			if (isLeaf((*actualNode)->table[i], k))
			{
				result = (*actualNode)->table[i]->value;
				delete (*actualNode)->table[i];
				(*actualNode)->table[i] = NULL;
			}
			else
			{
				result = searchToDelete((*actualNode)->table[i], k, k);
			}
			break;
		}
	}
	return result;
}


bool isLeaf(Node* node, int size)
{
	bool result = true;
	for (int i = 0; i < size; i++)
	{
		if (node->table[i] != NULL)
		{
			result = false;
			break;
		}
	}
	return result;
}


void deleteNode(Node* root, int n, int k, int value)
{
	Node** toDelete = search(root, n, k, value);
	if (*toDelete == NULL)
		printf("%d not exist\n", value);
	else
	{
		int temp;
		if (*toDelete == root)
		{
			if (isLeaf(root, n))
				root->value = INT_MIN;
			else
			{
				temp = searchToDelete(root, n, k);
				root->value = temp;
			}
		}
		else
		{
			if (isLeaf(*toDelete, k))
			{
				delete *toDelete;
				*toDelete = NULL;
			}
			else
			{
				temp = searchToDelete(*toDelete, k, k);
				(*toDelete)->value = temp;
			}
		}
	}
}


void lookFor(Node* root, int n, int k, int value)
{
	Node** foundling = search(root, n, k, value);
	if (*foundling == NULL)
		printf("%d not exist\n", value);
	else
		printf("%d exist\n", value);
}


Node** search(Node* root, int n, int k, int value)
{
	Node** actualNode = &root;
	if ((*actualNode)->value != value && (*actualNode)->value != INT_MIN)
	{
		int quotient = (int)(value / n);
		int insertionPlace = value % n;
		actualNode = &(*actualNode)->table[insertionPlace];
		while (*actualNode != NULL)
		{
			if ((*actualNode)->value == value)
				break;
			else
			{
				insertionPlace = quotient % k;
				quotient = (int)(quotient / k);
				actualNode = &(*actualNode)->table[insertionPlace];
			}
		}
	}
	return actualNode;
}


void insert(Node* root, int n, int k, int value)
{
	Node** actualNode = search(root, n, k, value);
	if (*actualNode == NULL)
		*actualNode = createNode(k, value);
	else if ((*actualNode)->value == INT_MIN)
		(*actualNode)->value = value;
	else
		printf("%d exist\n", value);
}


void print(Node* root, int n, int k)
{
	if (root->value != INT_MIN)
	{
		printf("%d ", root->value);
		for (int i = 0; i < n; i++)
		{
			if (root->table[i] != NULL)
			{
				printNode(root->table[i], k);
			}
		}
	}
}


void printNode(Node* actualNode, int size)
{
	printf("%d ", actualNode->value);
	for (int i = 0; i < size; i++)
	{
		if (actualNode->table[i] != NULL)
		{
			printNode(actualNode->table[i], size);
		}
	}
}


Node* createNode(int size, int value)
{
	Node* result = new Node;
	result->value = value;
	result->table = new Node*[size];
	for (int i = 0; i < size; i++)
		result->table[i] = NULL;
	return result;
}


void getLine(char& command, int& value)
{
	myVector<char> inputText(0, 20);
	char c;
	while (true)
	{
		c = getchar();
		if (c == '\n' || c == EOF)
			break;
		inputText.push_back(c);
	}
	command = inputText[0];
	if (inputText.getSize() > 1)
		value = atoi(&inputText.getVector()[2]);
}