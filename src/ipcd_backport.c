#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <errno.h>

#include <ipcd_backport.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <config.h>

#include "list_kernel.h"
IPCD_CON_MAN stCfgMan = {0};
IPCD_MANGER stIpcdMan = {0};

void writ_log(char * log)
{
    FILE * log_file;
    log_file  = fopen("back_log.txt", "a");
    fputs(log,log_file);
   //fputs("\n",log_file);
    fclose(log_file);
};

int IpcdManAddOne(IPCD_MANGER *pstIpcdMan, char *name)
{
   IPCD_INFO_WITHLIST * new = (IPCD_INFO_WITHLIST *)calloc(1,sizeof(IPCD_INFO_WITHLIST));
   if(NULL == new)
   {
      return -1;
   }
   strncpy(new->ipcd_name, name, sizeof(new->ipcd_name));
   list_add_tail(&new->IpcdListHead, &pstIpcdMan->ipcd_info_list.IpcdListHead);
   pstIpcdMan->ipcd_num++;
   return 0;
};

int IpcdManDelOne(IPCD_MANGER *pstIpcdMan, char *name)
{
   struct list_head *pstTmpHead;
    struct list_head *n;
   IPCD_INFO_WITHLIST * pstTmpInfo;

   list_for_each_safe(pstTmpHead, n, &pstIpcdMan->ipcd_info_list.IpcdListHead)
   {
      pstTmpInfo = (IPCD_INFO_WITHLIST *)pstTmpHead;
      if(strcmp(name,pstTmpInfo->ipcd_name) == 0)
      {
         list_del(pstTmpHead);
         pstIpcdMan->ipcd_num--;
         return 0;
      };
   };

   return -1;
};

void *IPCD_back_init(void)
{
    int i = 0; 
    char *name = NULL;
   /* 载入配置文件 */
   memset(&stCfgMan, 0 ,sizeof(stCfgMan));
   config_init(&stCfgMan);

   /* 初识化IPCD_man */
   memset(&stIpcdMan, 0 ,sizeof(stIpcdMan));
   INIT_LIST_HEAD(&stIpcdMan.ipcd_info_list.IpcdListHead);
   
   /* 读取所有的IPCD */
   while(cfg_get_oneipcd(&name) >= 0)
   {
      writ_log("get one icpd:");
      writ_log(name);
      writ_log("\n");
      IpcdManAddOne(&stIpcdMan, name);
   }

   return &stIpcdMan;
};

void IpcdBackDestroy(IPCD_MANGER *pstIpcdMan)
{
   struct list_head *pstTmpHead;
   struct list_head *n;
   IPCD_INFO_WITHLIST * pstTmpInfo;

   list_for_each_safe(pstTmpHead, n, &pstIpcdMan->ipcd_info_list.IpcdListHead)
   {
      pstTmpInfo = (IPCD_INFO_WITHLIST *)pstTmpHead;
      list_del(pstTmpHead);
      if(pstTmpInfo != NULL)
      {
         free(pstTmpInfo);
      }
   };
};

int IPCD_back_list_foreach(IPCD_MANGER *pstIpcdMan, void ** ppaptrarr)
{ 
   int i = 0;
   void * paptrarr;
   struct list_head *pstTmpHead;
   struct list_head **ppstTmpHead;
   IPCD_INFO_WITHLIST * pstTmpInfo;

   paptrarr = (struct list_head *)calloc(1,pstIpcdMan->ipcd_num * sizeof(void *));
   if(paptrarr != NULL)
   {
      *ppaptrarr = paptrarr;
   }
   else
   {
      return -1;
   }

   list_for_each(pstTmpHead, &pstIpcdMan->ipcd_info_list.IpcdListHead)
   {
      i++;
      if(i > pstIpcdMan->ipcd_num)
      {
         break;
      }
      ppstTmpHead = (struct list_head **)paptrarr;
      *ppstTmpHead = pstTmpHead;
      paptrarr+=sizeof(struct list_head*);
   };
   return i;
};

int IPCD_back_add(char * name, IPCD_MANGER *ipcd_man)
{
   char buffer[1024] = {'\0'};
   /* 添加全局变量 */
   if(IpcdManAddOne(ipcd_man, name) < 0)
   {
      return -1;
   };
   /* 操作配置文件 */
   if(cfg_add_ipcd(name) < 0)
   {
      return -1;
   };

   /* 克隆代码 */
   sprintf(buffer, "svn_get_code.bat %s", name);
   //system(buffer);
   return 0;
};

int IPCD_back_del(char * name, IPCD_MANGER *ipcd_man)
{
   char buffer[1024] = {'\0'};
   /* 删除全局变量 */
   if(IpcdManDelOne(ipcd_man, name) < 0)
   {
      return -1;
   };
   
   /* 操作配置文件 */
    if(cfg_remove_ipcd(name) < 0)
    {
       return -1;
    }

   /* 删除代码文件 */
   sprintf(buffer, "svn_remove_code.bat %s", name);
   system(buffer);
   return 0;
};

int IPCD_back_lint(char * name ,IPCD_MANGER *ipcd_man)
{
   printf("lint %s\n",name);
   return 0;
};

int IPCD_back_remove(char * name, IPCD_MANGER *ipcd_man)
{
   printf("remove %s\n",name);
   return 0;
};

/* 对外接口 */
int IPCD_add(char * name,  void *ipcd_man)
{
    return IPCD_back_add(name, ipcd_man);
};

int IPCD_del(char * name, void *ipcd_man)
{
   return IPCD_back_del(name, ipcd_man);
};

int IPCD_lint(char * name, void *ipcd_man)
{
   return IPCD_back_lint(name, ipcd_man);
};

void IPCD_destroy(void *ipcd_man)
{
   IpcdBackDestroy(ipcd_man);
   config_destroy();
};

void * IPCD_init()
{
   return IPCD_back_init();
};
void* IPCD_node2info(void* node)
{  
   IPCD_INFO_WITHLIST * info = (IPCD_INFO_WITHLIST *)node;
   return &info->ipcd_name;
};
int IPCD_list_foreach(void *pstIpcdMan, void ** ppaptrarr)
{
   return IPCD_back_list_foreach(pstIpcdMan, ppaptrarr);
};

