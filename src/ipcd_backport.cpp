#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <errno.h>

#include <ipcd_backport.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <config.h>
using namespace std;

DllExport IPCD_MANGER * ipcd_man_back;

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
   /* 读取配置文件 */
   return  0;
};

extern "C" DllExport void* IPCD_back_start()
{ 
   int ret = 0; 
   ipcd_man_back =  new IPCD_MANGER;
   ret = IPCD_back_init(ipcd_man_back);
   if(ret < 0)
   {
     writ_log("back init fail");
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

extern "C" DllExport void IPCD_back_destroy(void * ipcd_man)
{

};

/* 对外接口 */
extern "C" DllExport int IPCD_add(char * name,  IPCD_MANGER *ipcd_man)
{
    return IPCD_back_add(name, ipcd_man);
};
extern "C" DllExport int IPCD_del(char * name, IPCD_MANGER *ipcd_man)
{
   return IPCD_back_del(name, ipcd_man);
};
extern "C" DllExport int IPCD_lint(char * name, IPCD_MANGER *ipcd_man)
{
   return IPCD_back_lint(name, ipcd_man);
};

extern "C" DllExport int IPCD_remove(char * name, IPCD_MANGER *ipcd_man)
{
   return IPCD_back_remove(name, ipcd_man);
};
