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

typedef void (*process)(IPCD_INFO_WITHLIST *ipcd_info, void * userdata);

/* 对外接口 */
DllExport void *IPCD_init(void);
DllExport void IPCD_destroy(void *ipcd_man);
DllExport int IPCD_add(char * name,  void *ipcd_man);
DllExport int IPCD_del(char * name, void *ipcd_man);
DllExport int IPCD_lint(char * name, void *ipcd_man);
DllExport int IPCD_list_foreach(void *pstIpcdMan, void ** ppaptrarr);
DllExport void *IPCD_node2info(void* node);
#endif // !__IPCD_BACK_PORT_H_
