#include <iostream>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "ipcd_backport.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlstring.h>

using namespace std;

xmlDocPtr config_doc = NULL;
int config_init()
{  

   config_doc = xmlReadFile(CONFIG_FILE, NULL, 256);
   if (config_doc == NULL ) 
   {
    fprintf(stderr,"Document not parsed successfully. \n");
    return -1;
   }
   return 0;
};

int cfg_get_allipcd(IPCD_MANGER *ipcd_man) {
    xmlNodePtr root_node = NULL;
    xmlNodePtr cur = NULL;
    int i = 0;

    if (config_doc == NULL) {
        return -1;
    }

    root_node = xmlDocGetRootElement(config_doc);
    if (root_node == NULL) {
        fprintf(stderr, "get root_node fail. \n");
        return -1;
    }

    cur = root_node->xmlChildrenNode;
    /* 寻找 IPCD_LIST 节点*/
    while (cur != NULL) {
        if (xmlStrcmp(cur->name, (const xmlChar *) "IPCD_LIST") == 0) {
            break;
        };
        cur = cur->next;
    }
    cur = cur->next;
    if (cur == NULL)
    {
        printf("get icpd list node fali");
        return  -1;
    }
    while(cur != NULL)
    {
      ipcd_man->ipcd_num++;
      ipcd_man->ipcd_list[i]->ipcd_name = (char*)cur->name;;
      i++;
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