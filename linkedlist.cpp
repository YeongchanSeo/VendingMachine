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
Node *searchUniqne(Linkedlist *lp, void *target, int(*compare)(void *, void *))//���ϰ˻�
{
	lp->curp = lp->headp->next;//ó�� �����Ͱ� �ִ� ���� �̵�	
	while (lp->curp != lp->tailp)
	{
		if (compare(lp->curp + 1, target) == 0)//���� Ŀ���� �մ� ��忡�� +1���� person����ü �κи� ����.
		{
			break; //�� ó���� �ϳ��� ã���� break;

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
}//�����Ϸ�
void destory(Linkedlist *lp, void(*dataFree)(void *))
{
	dataFree(lp->curp + 1);
	lp->curp->prev->next = lp->curp->next;
	lp->curp->next->prev = lp->curp->prev;
	free(lp->curp);
}
void create(Linkedlist *lp)//���� �Ϸ�.
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