#include "include/ipcd_backport.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <stdio.h>
extern IPCD_MANGER * ipcd_man_back;

int main() {
    int i = 0;
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    IPCD_back_start();
    IPCD_add("test", ipcd_man_back);
    IPCD_del("test", ipcd_man_back);
    printf("hello\n");
    IPCD_back_destroy(ipcd_man_back);

}
