#ifndef __IPCD_BACK_PORT_H_
#define __IPCD_BACK_PORT_H_

#include "list_kernel.h"

#define DllExport   __declspec( dllexport )//宏定义
#define  CONFIG_FILE "config.xml"
#define  MAX_NUM 1024
#define  MAX_LEN 1024

DllExport typedef struct  ipcd_info
{
  struct list_head IpcdListHead;
  int pos;
  char ipcd_name[1024];
}IPCD_INFO_WITHLIST;

DllExport typedef struct  ipcd_manger
{
    char linux_base_dir[MAX_LEN];
    char win_base_dir[MAX_LEN];
    char svn_base_dir[MAX_LEN];
    char win_linux_base_dir[MAX_LEN];
    char win_lint_dir[MAX_LEN];
    int ipcd_num;
    IPCD_INFO_WITHLIST ipcd_info_list;
}IPCD_MANGER;

/* 对外接口 */

/* 初始化 */
//extern  DllExport void * IPCD_back_start();
DllExport IPCD_MANGER *IPCD_back_init(void);
DllExport int IPCD_add(char * name,  IPCD_MANGER *ipcd_man);
DllExport int IPCD_del(char * name, IPCD_MANGER *ipcd_man);
DllExport int IPCD_lint(char * name, IPCD_MANGER *ipcd_man);
DllExport void IpcdBackDestroy(IPCD_MANGER *pstIpcdMan);
DllExport void ipcd_list_for_each(void);

#endif // !__IPCD_BACK_PORT_H_
