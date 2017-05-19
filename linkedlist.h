#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <Windows.h>
#pragma once
#pragma warning(disable : 4996)
typedef struct _node Node;
typedef struct _node{
	Node *prev;
	Node *next;
}Node;
typedef struct _linkedList{
	Node *headp;
	Node *tailp;
	Node *curp;
	int len;
}Linkedlist;
Node *appendFromTail(Linkedlist *lp, void *item, size_t size, void(*myMemCpy)(void *, void*));
Node *searchUniqne(Linkedlist *lp, void *target, int(*compare)(void *, void *));
void destory(Linkedlist *lp, void(*dataFree)(void *));
void create(Linkedlist *lp);