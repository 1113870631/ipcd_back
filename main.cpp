#include <iostream>
#include "include/ipcd_backport.h"
#include <libxml/tree.h>
#include <libxml/parser.h>

int main(int, char**) {
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    std::cout << "Hello, world!\n";
      

//   doc = xmlReadFile(CONFIG_FILE, NULL, 256);
//   if (doc == NULL )
//   {
//    fprintf(stderr,"Document not parsed successfully. \n");
//    return 0;
//   }
//   cur = xmlDocGetRootElement(doc);
//   if(cur == NULL)
//   {
//    fprintf(stderr,"get cur fail. \n");
//    return 0;
//   }
//   //cur = cur->next;
//   printf("%s\n", cur->name);

}
