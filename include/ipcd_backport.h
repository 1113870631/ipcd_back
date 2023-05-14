#ifndef __IPCD_BACK_PORT_H_
#define __IPCD_BACK_PORT_H_

#include "list.h"

#define DllExport   __declspec( dllexport )//宏定义
#define  CONFIG_FILE "config.xml"
#define  MAX_NUM 1024
#define  MAX_LEN 1024

DllExport typedef struct  ipcd_info
{
  int pos;
  char *ipcd_name;
}IPCD_INFO;

DllExport typedef struct  ipcd_manger
{
    char linux_base_dir[MAX_LEN];
    char win_base_dir[MAX_LEN];
    char svn_base_dir[MAX_LEN];
    char win_linux_base_dir[MAX_LEN];
    char win_lint_dir[MAX_LEN];
    int ipcd_num;
    list *ipcd_info_list;
}IPCD_MANGER;

/* 对外接口 */

/* 初始化 */
extern  DllExport void * IPCD_back_start();

extern  DllExport int IPCD_add(char * name, IPCD_MANGER *ipcd_man);
extern  DllExport int IPCD_del(char * name, IPCD_MANGER *ipcd_man);
extern  DllExport int IPCD_lint(char * name, IPCD_MANGER *ipcd_man);
extern  DllExport int IPCD_remove(char * name, IPCD_MANGER *ipcd_man);
extern  DllExport OneNode* IPCD_get_one_node(IPCD_MANGER *ipcd_man, int flag);
extern  DllExport void IPCD_back_destroy(IPCD_MANGER * ipcd_man);


#endif // !__IPCD_BACK_PORT_H_
