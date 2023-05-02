#ifndef __IPCD_BACK_PORT_H_
#define __IPCD_BACK_PORT_H_

#include <strings.h>

#define DllExport   __declspec( dllexport )//宏定义
#define  CONFIG_FILE "config.xml"
#define  MAX_NUM 1024
#define  MAX_LEN 1024

DllExport typedef struct  ipcd_info
{
  int pos;
  char ipcd_name[MAX_LEN];
}IPCD_INFO;

DllExport typedef struct  ipcd_manger
{
    char linux_base_dir[MAX_LEN];
    char win_base_dir[MAX_LEN];
    char svn_base_dir[MAX_LEN];
    char win_linux_base_dir[MAX_LEN];
    char win_lint_dir[MAX_LEN];
    int ipcd_num;
    IPCD_INFO *ipcd_info_array[MAX_NUM];
}IPCD_MANGER;

/* 对外接口 */

/* 初始化 */
extern  DllExport void * IPCD_back_start();

extern  DllExport int IPCD_add(char * name, IPCD_MANGER *ipcd_man);
extern  DllExport int IPCD_del(char * name, IPCD_MANGER *ipcd_man);
extern  DllExport int IPCD_lint(char * name, IPCD_MANGER *ipcd_man);
extern  DllExport int IPCD_remove(char * name, IPCD_MANGER *ipcd_man);

extern  DllExport void IPCD_back_destroy(void * ipcd_man);


#endif // !__IPCD_BACK_PORT_H_
