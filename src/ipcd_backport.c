#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <errno.h>

#include <ipcd_backport.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <config.h>

#include "list.h"

DllExport IPCD_MANGER * ipcd_man_back = NULL;

void writ_log(char * log)
{
    FILE * log_file;
    log_file  = fopen("back_log.txt", "a");
    fputs(log,log_file);
   //fputs("\n",log_file);
    fclose(log_file);
};

int IPCD_back_init(IPCD_MANGER *ipcd_man)
{
   OneNode NewNode = {0};
    int i = 0; 
    char *name = NULL;
   /* 载入配置文件 */
   config_init();
   
   /* 读取所有的IPCD */
   ipcd_man->ipcd_num = 0;
   while(cfg_get_oneipcd(&name) >= 0)
   {
      ipcd_man->ipcd_num ++;
      writ_log("get one icpd:");
      writ_log(name);
      writ_log("\n");
      list_add_OneNode(ipcd_man->ipcd_info_list, (void *)NULL, name, 0);
   }

   return  0;
};

extern DllExport void* IPCD_back_start()
{ 
   int ret = 0; 
   int i = 0;
   ipcd_man_back =  (IPCD_MANGER*)malloc(sizeof(IPCD_MANGER));
   if(ipcd_man_back == NULL)
   {
      return NULL;
   };
   
   ipcd_man_back->ipcd_info_list = list_create();
   if(ipcd_man_back->ipcd_info_list == NULL)
   {
      return NULL;
   }
   ret = IPCD_back_init(ipcd_man_back);
   if(ret < 0)
   {
     writ_log("back init fail");
   }
   return ipcd_man_back;
};

int IPCD_back_add(char * name, IPCD_MANGER *ipcd_man)
{
   char buffer[1024] = {'\0'};
   /* 添加全局变量 */
   ipcd_man->ipcd_num ++;
   if(list_add_OneNode(ipcd_man->ipcd_info_list, NULL, name, 0) == NULL)
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

int IPCD_back_del(char * name, IPCD_MANGER *ipcd_man)
{
   char buffer[1024] = {'\0'};
   /* 删除全局变量 */
   if(list_del_oneNode(name, ipcd_man->ipcd_info_list) < 0)
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

OneNode* IPCD_back_get_one_node(IPCD_MANGER *ipcd_man, int flag)
{
   if(flag == 1)
   {
      list_for_each(ipcd_man->ipcd_info_list, 1);
   }
   else
   {
      return list_for_each(ipcd_man->ipcd_info_list, 0);
   }
};

/* 对外接口 */
extern  DllExport int IPCD_add(char * name,  IPCD_MANGER *ipcd_man)
{
    return IPCD_back_add(name, ipcd_man);
};
extern  DllExport int IPCD_del(char * name, IPCD_MANGER *ipcd_man)
{
   return IPCD_back_del(name, ipcd_man);
};
extern  DllExport int IPCD_lint(char * name, IPCD_MANGER *ipcd_man)
{
   return IPCD_back_lint(name, ipcd_man);
};

extern  DllExport int IPCD_remove(char * name, IPCD_MANGER *ipcd_man)
{
   return IPCD_back_remove(name, ipcd_man);
};

extern  DllExport OneNode* IPCD_get_one_node(IPCD_MANGER *ipcd_man, int flag)
{
   return IPCD_back_get_one_node(ipcd_man, flag);
};

extern DllExport void IPCD_back_destroy(IPCD_MANGER * ipcd_man)
{
    list_destroy(ipcd_man->ipcd_info_list);
    config_destroy();
};

