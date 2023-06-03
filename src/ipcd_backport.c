#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <errno.h>

#include <ipcd_backport.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <config.h>

#include "log.h"
#include "list_kernel.h"

IPCD_CON_MAN stCfgMan = {0};   /** 问题单管理配置文件 */
IPCD_MANGER stIpcdMan = {0};   /** 问题单管理实例 */

FILE *file_info_log = NULL;  /** info日志文件描述符 */
FILE *file_debug_log = NULL; /** debug日志文件描述符 */

char * path_info_log = "./log_info.txt";
char * path_debug_log = "./log_debug.txt";

/**
 * @brief 
 * IpcdManAddOne
 * 添加一个问题单
 * @param pstIpcdMan 问题单管理实例
 * @param name       要添加的问题单名称
 * @return int 
 */
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

/**
 * @brief 
 * IpcdManDelOne 
 * 删除一个问题单
 * @param pstIpcdMan 问题单管理实例
 * @param name       要删除的问题单名称
 * @return int       
 */
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

int IPCD_logsys_init(void)
{
    log_set_level(0);
    log_set_quiet(0);

    file_info_log = fopen(path_info_log, "ab");
    if(file_info_log == NULL)
        return -1;

    file_debug_log = fopen(path_debug_log, "ab");
    if(file_debug_log == NULL)
        return -1;

    log_add_fp(file_info_log, LOG_INFO);
    log_add_fp(file_debug_log, LOG_DEBUG);
    
    return 0;
}

void IPCD_logsys_destroy(void)
{
   if(NULL != file_info_log)
   {
      fclose(file_info_log);
   }

   if(NULL != file_debug_log)
   {
      fclose(file_debug_log);
   }
}

/**
 * @brief 
 * IPCD_back_init
 * 初始化
 * @return void* 
 */
void *IPCD_back_init(void)
{
    int i = 0; 
    char *name = NULL;

    /* 初识化日志系统 */
   IPCD_logsys_init();
   log_info("log sys ok");
   /* 载入配置文件 */
   memset(&stCfgMan, 0 ,sizeof(stCfgMan));
   config_init(&stCfgMan);

   /* 初识化IPCD_man */
   memset(&stIpcdMan, 0 ,sizeof(stIpcdMan));
   INIT_LIST_HEAD(&stIpcdMan.ipcd_info_list.IpcdListHead);
   
   /* 读取所有的IPCD */
   while(cfg_get_oneipcd(&name) >= 0)
   {
      log_info("init add ipcd:%s",name);
      IpcdManAddOne(&stIpcdMan, name);
   }

   return &stIpcdMan;
};

/**
 * @brief 
 * IpcdBackDestroy
 * 销毁
 * @param pstIpcdMan 
 */
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
/**
 * @brief 
 * IPCD_back_list_foreach
 * 遍历得到所有问题单节点的地址
 * @param pstIpcdMan 
 * @param ppaptrarr （ipcd1的地址，icpd2的地址 ......）
 * @return int 得到的问题单总数
 */
int IPCD_back_list_foreach(IPCD_MANGER *pstIpcdMan, void ** ppaptrarr)
{ 
   int i = 0;
   void * paptrarr;
   struct list_head *pstTmpHead;
   struct list_head **ppstTmpHead;
   IPCD_INFO_WITHLIST * pstTmpInfo;
   
   /* 申请内存存储所有节点的地址 */
   paptrarr = (struct list_head *)calloc(1, pstIpcdMan->ipcd_num * sizeof(void *));
   if(paptrarr != NULL)
   {
      *ppaptrarr = paptrarr;
   }
   else
   {
      return -1;
   }
   /* 遍历得到所有节点的地址 */
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

/**
 * @brief 
 * IPCD_back_add
 * 添加一个问题单
 * @param name 
 * @param ipcd_man 
 * @return int 
 */
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
   system(buffer);
   return 0;
};

/**
 * @brief 
 * IPCD_back_del
 * 删除一个问题单
 * @param name 
 * @param ipcd_man 
 * @return int 
 */
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

/**
 * @brief 
 * IPCD_back_lint
 * pc lint
 * @param name 
 * @param ipcd_man 
 * @return int 
 */
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
   IPCD_logsys_destroy();
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

