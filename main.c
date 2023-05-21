#include "include/ipcd_backport.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <stdio.h>
#include "list_kernel.h"
void process1(IPCD_INFO_WITHLIST *ipcd_info)
{
    printf("name:%s\n",ipcd_info->ipcd_name);
};
int main() {
    int i = 0;
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    IPCD_MANGER * ipcd_man;
    struct list_head* info_tmp = NULL;

    ipcd_man = IPCD_init();
    void *info;
    int  tmp = IPCD_list_foreach(ipcd_man, &info);
    for(i=0; i<tmp; i++)
    {
       info_tmp = *(struct list_head**)info;
       printf("%s\n",((IPCD_INFO_WITHLIST *)info_tmp)->ipcd_name);
       info+=sizeof(void*);
    }

   // Ipcd_List_For_Each(process1);
    IPCD_destroy(ipcd_man);
 }
