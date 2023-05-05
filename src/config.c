#include <string.h>
#include <stdio.h>
#include "config.h"
#include "ipcd_backport.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlstring.h>
#include <stdbool.h>

IPCD_CON_MAN *IpcdConMan = NULL;

int config_init()
{  
   xmlNodePtr cur = NULL;
   IpcdConMan = (IPCD_CON_MAN *)calloc(1, sizeof(IPCD_CON_MAN));
   /* 获取文件 */
   IpcdConMan->config_doc = xmlReadFile(CONFIG_FILE, NULL, 256);
   if (IpcdConMan->config_doc == NULL ) 
   {
    fprintf(stderr,"Document not parsed successfully. \n");
    return -1;
   }
    /* 获取根节点 */
    IpcdConMan->root_node = xmlDocGetRootElement(IpcdConMan->config_doc);
    if (IpcdConMan->root_node == NULL) {
        fprintf(stderr, "get root_node fail. \n");
        return -1;
    }

    /* 获取IPCD_LIST节点 */
    cur = IpcdConMan->root_node->xmlChildrenNode;
    /* 寻找 IPCD_LIST 节点*/
    while (cur != NULL) 
    {
        if (xmlStrcmp(cur->name, (const xmlChar *) "IPCD_LIST") == 0) {
            break;
        };
        cur = cur->next;
    }
    IpcdConMan->cur = cur;
    IpcdConMan->ipcd_list = cur;

   return 0;
};

int cfg_get_oneipcd(char **ipcd_name) {
    xmlNodePtr root_node = NULL;
    static xmlNodePtr cur = NULL;
    static bool end_flag = false;
    
    if((cur == NULL) && (end_flag != true))
    {
        cur = IpcdConMan->ipcd_list;
        cur = cur->children;
    }

    
    if(cur != NULL)
    {
      *ipcd_name = (char*)cur->name;
      printf("%s\n",cur->name);  
    }
    else
    {
        return -1;
    }
    
    cur = cur->next;

    if(cur == NULL)
    {
      end_flag = true;
    }
    return 0;
};

int cfg_get_base_confing()
{

    return 0;
};
int cfg_add_ipcd(char *name)
{

    return 0;
};
int cfg_remove_ipcd(char *name)
{

    return 0;
};