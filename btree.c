#include "btree.h"
#include <stdlib.h>

void Initialize (pointerType tree)
{
    tree = NULL;
}

bool bTreeSearch (Data *x, pointerType pt)
{
    long i = 1;
    if (pt == NULL)
        return false;

    while (i < pt-> n && x->key > pt->r[i -1].key)
        i++;
    
    if (x->key == pt->r[i -1].key)
        return true;
    
    if (x->key > pt->r[i -1].key)
        bTreeSearch (x, pt->p[i]);
    else
        bTreeSearch(x, pt->p[i]);
}

void InsertIntoThePage (pointerType pt, Data data, pointerType rightpt)
{
    short pNotFound;
    int k;
    k = pt->n;
    pNotFound = (k > 0);
    while (pNotFound)
    {
        if (data.key >= pt->r[k-1].key)
        {
            pNotFound = 0;
            break;
        }
        pt->r[k] = pt->r[k-1];
        pt->p[k+1] = pt->p[k];
        k--;
        if  (k < 1)
            pNotFound = 0;

    }
    
    pt->r[k] = data;
    pt->p[k+1] = rightpt;
    pt->n++;
}

bool Ins (Data data, pointerType pt, bool *hasGrown, Data *dataReturn, pointerType *ptReturn)
{
    long i = 1;
    long j;
    pointerType ptTemp;
    if (pt == NULL)
    {
        *hasGrown = true;
        (*dataReturn) = data;
        (*ptReturn) = pt;
        return false;
    }

    while (i < pt->n && data.key > pt->r[i-1].key)
        i++;
    
    if (data.key == pt->r[i-1].key)
    {
        *(hasGrown) = false;
        return false;
    }
    if (data.key < pt->r[i-1].key)
        i--;
    Ins(data, pt->p[i], hasGrown, dataReturn, ptReturn);
    if(!*hasGrown)
        return true;
    if (pt->n < MM)
    {
        InsertIntoThePage(pt, *dataReturn, *ptReturn);
        *hasGrown = false;
        return true;
    }
    ptTemp = (pointerType)malloc(sizeof(Data));
    ptTemp->n = 0;
    ptTemp->p[0] = NULL;
    if (i < M+1)
    {
        InsertIntoThePage(ptTemp, pt->r[MM-1], pt->p[MM]);
        pt->n--;
        InsertIntoThePage(pt, *dataReturn, *ptReturn);
    }else 
        InsertIntoThePage(ptTemp,*dataReturn, *ptReturn);
    
    for (j = M + 2; j <= MM; j++)
    {
        InsertIntoThePage(ptTemp, pt->r[j-1], pt->p[j]);
        pt->n = M;
        ptTemp->p[0] = pt->p[M+1];
        *dataReturn = pt->r[M];
        *ptReturn = ptTemp;
    }
    
}

void Insert (Data data, pointerType *pt)
{
    bool hasGrown;
    Data dataReturn;
    PageType *ptReturn, *ptTemp;
    Ins (data, *pt, &hasGrown, &dataReturn, &ptReturn);
    if (hasGrown)
    {
        ptTemp = (PageType *) malloc(sizeof(PageType));
        ptTemp->n = 1;
        ptTemp->r[0] = dataReturn;
        ptTemp->p[1] = ptReturn;
        ptTemp->p[0] = *pt;
        *pt = ptTemp;
    }
}