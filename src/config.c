#include <string.h>
#include <stdio.h>
#include "config.h"
#include "ipcd_backport.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlstring.h>
#include <stdbool.h>
IPCD_CON_MAN *IpcdConMan = NULL;

int config_init(IPCD_CON_MAN *pstIpcdConMan)
{  
   xmlNodePtr cur = NULL;
   /* 获取文件 */
   pstIpcdConMan->config_doc = xmlReadFile(CONFIG_FILE, NULL, 256);
   if (pstIpcdConMan->config_doc == NULL ) 
   {
    fprintf(stderr,"Document not parsed successfully. \n");
    return -1;
   }
    /* 获取根节点 */
    pstIpcdConMan->root_node = xmlDocGetRootElement(pstIpcdConMan->config_doc);
    if (pstIpcdConMan->root_node == NULL) {
        fprintf(stderr, "get root_node fail. \n");
        return -1;
    }

    /* 获取IPCD_LIST节点 */
    cur = pstIpcdConMan->root_node->xmlChildrenNode;
    /* 寻找 IPCD_LIST 节点*/
    while (cur != NULL) 
    {
        if (xmlStrcmp(cur->name, (const xmlChar *) "IPCD_LIST") == 0) {
            break;
        };
        cur = cur->next;
    }
    pstIpcdConMan->cur = cur;
    pstIpcdConMan->ipcd_list = cur;
    IpcdConMan = pstIpcdConMan;
   return 0;
};

void config_destroy(IPCD_CON_MAN *pstIpcdConMan)
{
  if(pstIpcdConMan->config_doc != NULL)
  {
    xmlFreeDoc(pstIpcdConMan->config_doc);
    xmlCleanupParser();
    xmlMemoryDump();
  }
}

int cfg_get_oneipcd(char **ipcd_name) {
    xmlNodePtr root_node = NULL;
    static xmlNodePtr cur = NULL;
    static bool end_flag = false;
    char * tmp;
    
    if((cur == NULL) && (end_flag != true))
    {
        cur = IpcdConMan->ipcd_list;
        cur = cur->children;
    }

    
    if(cur != NULL)
    {
       tmp = (char*)XML_GET_CONTENT(cur->children);
      *ipcd_name = tmp;
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
    if(IpcdConMan == NULL)
    {
        return -1;
    }
    if(IpcdConMan->ipcd_list == NULL)
    {
        return -1;
    }

    if(xmlNewChild(IpcdConMan->ipcd_list, NULL, "ipcd", name) == NULL)
    {
        return -1;
    };
    
    if(xmlSaveFormatFileEnc(CONFIG_FILE, IpcdConMan->config_doc, "UTF-8", 1) < 0)
    {
        return -1;
    };

    return 0;
};

int cfg_remove_ipcd(char *name)
{
    xmlNodePtr tmpNode = NULL;
    xmlChar *content = NULL;
    char * tmp = NULL;
    if(IpcdConMan == NULL)
    {
        return -1;
    }
    if(IpcdConMan->ipcd_list == NULL)
    {
        return -1;
    }
    tmpNode = IpcdConMan->ipcd_list->children;

    while(tmpNode != NULL)
    {   
        //tmp = (char*)xmlNodeGetContent( tmpNode->children );
        tmp = XML_GET_CONTENT(tmpNode->children);
        if(strcmp(name, tmp) == 0)
        {
            xmlUnlinkNode(tmpNode);
            xmlFreeNode(tmpNode);
            if(xmlSaveFormatFileEnc(CONFIG_FILE, IpcdConMan->config_doc, "UTF-8", 1) < 0)
            {
                return -1;
            };
            return 0;
        }
        else
        {
           tmpNode = tmpNode->next; 
        };
    }

    return -1;
};