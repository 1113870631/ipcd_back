#include "include/ipcd_backport.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <stdio.h>
#include "list_kernel.h"

int main() {
    int i = 0;
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    IPCD_MANGER * icpd_man;
    system("pause");
    icpd_man = IPCD_back_init();
    
    //IPCD_back_del("del_test", icpd_man);
    //ipcd_list_for_each();
    for(i=0; i<1000; i++)
    {
        IPCD_add("test", icpd_man);
    }
    system("pause");
    IpcdBackDestroy(icpd_man);
    system("pause");
    // system("pause");
    // IPCD_back_start();
    // IPCD_add("test", ipcd_man_back);
    // IPCD_del("test", ipcd_man_back);
    // printf("hello\n");
    // IPCD_back_destroy(ipcd_man_back);

 }
