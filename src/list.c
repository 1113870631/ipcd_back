#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"


/* 创建链表 */
list* list_create(void)
{ 
   list *pstTmp = malloc(sizeof(list));
   if(pstTmp == NULL)
   {
      return NULL;
   }
   pstTmp->pstHeadNode = (OneNode *)malloc(sizeof(OneNode));
   memset(pstTmp->pstHeadNode, 0, sizeof(OneNode));

   pstTmp->pstTailNode = pstTmp->pstHeadNode;
   pstTmp->ulNodeNum = 1;
   pstTmp->pstHeadNode->ulPos = 1;
   return pstTmp;
};

/* 添加一个元素 */
OneNode* list_add_OneNode(list *pstList, void* pUserData,char * pzNodeName,unsigned int ulSize)
{
   if(pstList->pstTailNode != NULL)
   {
      pstList->pstTailNode->pstnext = (OneNode *)malloc(sizeof(OneNode));
      pstList->pstTailNode->pstnext->pUserdata = (OneNode *)malloc(ulSize);
      pstList->pstTailNode = pstList->pstTailNode->pstnext;
      pstList->pstTailNode->pstnext = NULL;
      memcpy(pstList->pstTailNode->pUserdata, pUserData, ulSize);
      pstList->pstTailNode->uldatalen = ulSize;
      strncpy(pstList->pstTailNode->szNodeName,pzNodeName,sizeof(pstList->pstTailNode->szNodeName));
      pstList->ulNodeNum++;
      pstList->pstTailNode->ulPos = pstList->ulNodeNum;
   }
};

/* 删除一个元素 */
int list_del_oneNode(char *pcnode_name, list *pstlist)
{

};
/* 搜索一个元素 */
OneNode* list_search_byName(char *pcnode_name, list *pstlist)
{

};
/* 插入一个元素 */
int list_insert_oneNode(int ulpos, void* puserdata, list *pstlist)
{

};

/* 遍历链表所有元素 */
OneNode * list_for_each(list *pstlist, unsigned ulResetFlag)
{
   static OneNode * tmp = NULL;

   if(ulResetFlag == 1)
   {
       tmp = NULL;
       return NULL;
   }

   if(tmp == NULL)
   {
     tmp = pstlist->pstHeadNode;
   }
   
   if(tmp->pstnext != NULL)
   {
     tmp = tmp->pstnext;
     return tmp;
   }
   else
   {
      return NULL;
   }

};
/* 销毁链表 */
void list_destroy(list* pstList)
{
   OneNode *psttmp = NULL;
   OneNode *pstNodetmp = NULL;
   if(pstList == NULL)
   {
      return;
   }
    /* 释放用户内存 */
   for(;;)
   {
      psttmp = list_for_each(pstList, 0);
      if(psttmp != NULL)
      {
         free(psttmp->pUserdata);
      }
      else
      {
         list_for_each(pstList, 1);
         break;
      }
   }

   /* 释放Node内存 */
   psttmp = pstList->pstHeadNode->pstnext;
   free(pstList->pstHeadNode);
   for(;;)
   {
      if(psttmp != NULL)
      {
         pstNodetmp = psttmp->pstnext;
         free(psttmp);
         psttmp = pstNodetmp;
      }
      else
      {
         break;
      }
   }

   /* 释放链表管理结构体 */
   free(pstList);
   pstList = NULL;
};