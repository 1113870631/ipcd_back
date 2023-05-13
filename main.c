#include "include/ipcd_backport.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <stdio.h>
extern IPCD_MANGER * ipcd_man_back;

int main() {
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    IPCD_back_start();
    ipcd_man_back;
    printf("hello\n");
  // doc = xmlReadFile(CONFIG_FILE, NULL, 256);
  // if (doc == NULL )
  // {
  //  fprintf(stderr,"Document not parsed successfully. \n");
  //  return 0;
  // }
  // cur = xmlDocGetRootElement(doc);
  // if(cur == NULL)
  // {
  //  fprintf(stderr,"get cur fail. \n");
  //  return 0;
  // }
  // //cur = cur->next;
  // printf("%s\n", cur->name);
  // system("pause");

}
