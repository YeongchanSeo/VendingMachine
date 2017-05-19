#include "linkedlist.h"

Node *appendFromTail(Linkedlist *lp, void *item, size_t size, void(*myMemCpy)(void *, void*))
{
	lp->curp = (Node *)calloc(1, sizeof(Node) + size);
	assert(lp->curp != NULL);
	lp->curp->prev = lp->tailp->prev;
	lp->curp->next = lp->tailp;
	lp->curp->prev->next = lp->curp;
	lp->tailp->prev = lp->curp;
	lp->len++;
	//strcpy(lp->curp->name, np);
	myMemCpy(lp->curp + 1, item);
	return lp->curp;
}
Node *searchUniqne(Linkedlist *lp, void *target, int(*compare)(void *, void *))//단일검색
{
	lp->curp = lp->headp->next;//처음 데이터가 있는 노드로 이동	
	while (lp->curp != lp->tailp)
	{
		if (compare(lp->curp + 1, target) == 0)//현재 커서가 잇는 노드에서 +1값은 person구조체 부분만 보냄.
		{
			break; //맨 처음값 하나만 찾으면 break;

		}
		else
		{
			lp->curp = lp->curp->next;
		}

	}
	if (lp->curp == lp->tailp)
	{
		lp->curp = NULL;
	}
	return lp->curp;
}//수정완료
void destory(Linkedlist *lp, void(*dataFree)(void *))
{
	dataFree(lp->curp + 1);
	lp->curp->prev->next = lp->curp->next;
	lp->curp->next->prev = lp->curp->prev;
	free(lp->curp);
}
void create(Linkedlist *lp)//수정 완료.
{
	lp->headp = (Node *)calloc(1, sizeof(Node));
	assert(lp->headp != NULL);
	lp->tailp = (Node*)calloc(1, sizeof(Node));
	assert(lp->tailp != NULL);
	lp->headp->next = lp->tailp;
	lp->headp->prev = lp->headp;
	lp->tailp->prev = lp->headp;
	lp->tailp->next = lp->tailp;
	lp->curp = NULL;
	lp->len = 0;
	return;
}