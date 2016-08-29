#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

list_t list_create()
{
	//Really ugly hack. Better way to do this?
	list_t newlist = malloc(sizeof(int)*10);

	newlist->head = NULL;
	newlist->tail = NULL;
	newlist->length = 0;
	
	return newlist;
}

void list_delete(list_t list)
{
	node* currentNode = list->head;
	node* nextNode;
	while(currentNode != list->tail) {
		nextNode = currentNode->next;
		free(currentNode);
		currentNode = nextNode;
	}
	free(currentNode);
	free(list);
}

void list_insert(list_t list, int index, int data)
{
	//Skip to the node before where we insert
	node* currentNode = list->head;
	for (int i=0; i<index-1; i++) {
		currentNode = currentNode->next;
	}

	node* newnode = malloc(sizeof(node));
	newnode->prev = currentNode;
	newnode->next = currentNode->next;
	newnode->data = data;

	currentNode->next->prev = newnode;
	currentNode->next = newnode;
	list->length++;
}

void list_append(list_t list, int data)
{
	node* newnode = malloc(sizeof(node));

	newnode->next = NULL;
	newnode->prev = list->tail;
	newnode->data = data;

	if (list->length > 0) {
		list->tail->next = newnode;
	}
	list->tail = newnode;
	if (list->length == 0) {
		list->head = newnode;
	}
	list->length++;

}

void list_print(list_t list)
{
	if (list->length == 0) {
		return;
	}

	node* currentNode = list->head;
	while (currentNode != list->tail) {
		printf("%i ",currentNode->data);
		currentNode = currentNode->next;
	}
	printf("%i\n", currentNode->data);
}

long list_sum(list_t list)
{
	node* currentNode = list->head;
	long sum = 0;
	while (currentNode != list->tail) {
		sum += currentNode->data;
		currentNode = currentNode->next;
	}
	sum += currentNode->data;

	return sum;
}

int list_get(list_t list, int index)
{
	node* currentNode = list->head;
	for (int i=0;i<index;i++) {
		currentNode = currentNode->next;
	}

	return currentNode->data;
}

int list_extract(list_t list, int index)
{
	node* currentNode = list->head;
	for (int i=0;i<index;i++) {
		currentNode = currentNode->next;
	}

	int returnVal = currentNode->data;
	if (currentNode != list->head) {
		currentNode->prev->next = currentNode->next;
	} else {
		list->head = currentNode->next;
	}
	if (currentNode != list->tail) {
		currentNode->next->prev = currentNode->prev;
	} else {
		list->tail = currentNode->prev;
	}
	free(currentNode);
	list->length--;

	return returnVal;
}
