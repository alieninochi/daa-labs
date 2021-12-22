// П.І.Б: Голубкова Зоя Сергіївна
// Група: ТР-з01
// Предмет: Проетування та аналіз алгоритмів
// Лабораторна робота №2


#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#define NUMBER_OF_ELEMENTS 20

typedef struct node
{
	void* value;
	struct node* next;
	struct node* prev;
} node;

typedef struct dblLinkList
{
	size_t size;
	node* head;
	node* tail;
} dblLinkList;

dblLinkList* createDblLinkedList()
{
	dblLinkList* tmp = (dblLinkList*)malloc(sizeof(dblLinkList));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;

	return tmp;
}

void deleteDblLinkedList(dblLinkList** list)
{
	node* tmp = (*list)->head;
	node* next = NULL;

	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}

	free(*list);
	(*list) = NULL;
}

// add element to the head
void pushToHead(dblLinkList* list, void* data)
{
	node* tmp = (node*)malloc(sizeof(node));

	if (tmp == NULL) exit(1);

	tmp->value = data;
	tmp->next = list->head;
	tmp->prev = NULL;

	if (list->head) list->head->prev = tmp;

	list->head = tmp;

	if (list->tail == NULL) list->tail = tmp;

	list->size++;
}

// delete element from head
void* popFromHead(dblLinkList* list)
{
	node* prev;
	void* tmp;
	if (list->head == NULL) exit(2);

	prev = list->head;
	list->head = list->head->next;
	if (list->head) list->head->prev = NULL;

	tmp = prev->value;
	free(prev);

	list->size--;
	return tmp;
}

// add element to tail
void* pushToTail(dblLinkList* list, void* value)
{
	node* tmp = (node*)malloc(sizeof(node));
	if (tmp == NULL) {
		exit(3);
	}
	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail) {
		list->tail->next = tmp;
	}
	list->tail = tmp;

	if (list->head == NULL) {
		list->head = tmp;
	}
	list->size++;
}

// delete element from tail 
void* popFromTail(dblLinkList* list)
{
	node* next;
	void* tmp;

	if (list->tail == NULL) exit(4);

	next = list->tail;
	list->tail = list->tail->prev;

	if (list->tail) list->tail->next = NULL;

	if (next == list->head) list->head = NULL;

	tmp = next->value;
	free(next);

	list->size--;
	return tmp;
}

node* getNthElement(dblLinkList* list, int index)
{
	node* tmp = list->head;
	int i = 0;

	while (tmp && i < index)
	{
		tmp = tmp->next;
		i++;
	}

	return tmp;
}


void printValue(void* value) {
	printf("%d ", *((int*)value));
}

void printList(dblLinkList* list, void (*fun)(void*)) {
	node* tmp = list->head;
	while (tmp) {
		fun(tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

int main()
{
	srand(time(NULL));

	dblLinkList* linkedList = createDblLinkedList();

	// generating array with random numbers
	int array[NUMBER_OF_ELEMENTS];

	for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
	{
		array[i] = rand() % 100;
	}

	// add elements from array to list 
	for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
	{
		if (i < 10) pushToHead(linkedList, &array[i]);
		if (i > 10) pushToTail(linkedList, &array[i]);
	}

	printList(linkedList, printValue);

	// delete 5 elements from head and tail
	for (int i = 0; i < 5; i++)
	{
		popFromHead(linkedList);
		popFromTail(linkedList);
	}

	printList(linkedList, printValue);

	
	while (true)
	{
		int index;
		printf("Enter the index of element or press ESC to exit: \n");
		scanf_s("%d", &index);
		printf("Element with %dth index is %d\n", index, *((int*)(getNthElement(linkedList, index))->value));

		if (_getch() == 27) exit(0);
	}
}