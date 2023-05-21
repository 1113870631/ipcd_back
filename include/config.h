#ifndef  _CONFIG_H_
#define _CONFIG_H_
#include "ipcd_backport.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlstring.h>
typedef struct ipcd_config
{
    xmlNodePtr root_node; /* 根节点 */
    xmlNodePtr cur;       /* 当前节点 */
    xmlDocPtr config_doc; /* 配置文件 */
    xmlNodePtr ipcd_list;
}IPCD_CON_MAN;

int config_init(IPCD_CON_MAN *pstIpcdConMan);
void config_destroy(void);
int cfg_get_base_confing();
int cfg_add_ipcd(char *name);
int cfg_remove_ipcd(char *name);
int cfg_get_oneipcd(char **ipcd_name);

#endif // ! _CONFIG_H_