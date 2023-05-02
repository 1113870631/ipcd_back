#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <errno.h>

#include <ipcd_backport.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <config.h>

DllExport IPCD_MANGER * ipcd_man_back = NULL;

void writ_log(char * log)
{
    FILE * log_file;
    log_file  = fopen("back_log.txt", "a");
    fputs(log,log_file);
    fputs("\n",log_file);
    fclose(log_file);
};

int IPCD_back_getallipcd(IPCD_MANGER * ipcd_man)
{

   return 0;
};

int IPCD_back_init(IPCD_MANGER *ipcd_man)
{
   int i = 0;
   /* 读取配置文件 */
   config_init();
   for(i=0; ;i++)
   {
     if(cfg_get_oneipcd(ipcd_man->ipcd_info_array[i]->ipcd_name) < 0)
     {
      break;
     };
   }

   return  0;
};

extern DllExport void* IPCD_back_start()
{ 
   int ret = 0; 
   ipcd_man_back =  (IPCD_MANGER*)malloc(sizeof(IPCD_MANGER));
   if(ipcd_man_back == NULL)
   {
      return NULL;
   }
   
   ret = IPCD_back_init(ipcd_man_back);
   if(ret < 0)
   {
     //writ_log("back init fail");
   }

};

int IPCD_back_add(char * name, IPCD_MANGER *ipcd_man)
{
    printf("add %s\n",name);
   /* 操作配置文件 */

   /* 克隆代码 */

    return 0;
};

int IPCD_back_del(char * name, IPCD_MANGER *ipcd_man)
{


   /* 操作配置文件 */


   /* 删除代码文件 */

   /* 删除全局变量 */
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

extern DllExport void IPCD_back_destroy(void * ipcd_man)
{

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
