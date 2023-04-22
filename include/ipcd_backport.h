#ifndef __IPCD_BACK_PORT_H_
#define __IPCD_BACK_PORT_H_

#include <iostream>
#include <strings.h>

using namespace std;

#define DllExport   __declspec( dllexport )//宏定义
#define  CONFIG_FILE "config.xml"
#define  MAX_NUM   1024

class DllExport IPCD_INFO
{
  public:
  int pos;
  string ipcd_name;
};

class DllExport IPCD_MANGER 
{
    public:
    string linux_base_dir;
    string win_base_dir;
    string svn_base_dir;
    string win_linux_base_dir;
    string win_lint_dir;
    int ipcd_num;
    IPCD_INFO *ipcd_list[MAX_NUM];
};

/* 对外接口 */

/* 初始化 */
extern "C" DllExport void * IPCD_back_start();

extern "C" DllExport int IPCD_add(char * name, IPCD_MANGER *ipcd_man);
extern "C" DllExport int IPCD_del(char * name, IPCD_MANGER *ipcd_man);
extern "C" DllExport int IPCD_lint(char * name, IPCD_MANGER *ipcd_man);
extern "C" DllExport int IPCD_remove(char * name, IPCD_MANGER *ipcd_man);

extern "C" DllExport void IPCD_back_destroy(void * ipcd_man);


#endif // !__IPCD_BACK_PORT_H_
