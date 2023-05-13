#ifndef  __LIST_H__
#define __LIST_H__
#include<stdio.h>

/* One Node */
typedef struct Node {
    unsigned int uldatalen;
    void *pUserdata;
    char szNodeName[1024];
    unsigned int ulPos;	
	struct Node *pstnext;	
} OneNode;

typedef struct list
{
   OneNode *pstTailNode;
   OneNode *pstHeadNode;
   unsigned int ulNodeNum;
}list;

/* 创建链表 */
list* list_create(void);

/* 销毁链表 */
void list_destroy(list* pstList);

/* 添加一个元素 */
OneNode* list_add_OneNode(list *pstList, void* pUserData,char * pzNodeName,unsigned int ulSize);
/* 删除一个元素 */
int list_del_oneNode(char *pcnode_name, list *pstlist);
/* 搜索一个元素 */
OneNode* list_search_byName(char *pcnode_name, list *pstlist);
/* 插入一个元素 */
int list_insert_oneNode(int ulpos, void* puserdata, list *pstlist);

/* 遍历链表所有元素 */
OneNode * list_for_each(list *pstlist, unsigned ulResetFlag);

#endif // ! __LIST_H__ 
