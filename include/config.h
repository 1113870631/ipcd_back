#ifndef  _CONFIG_H_
#define _CONFIG_H_
#include "ipcd_backport.h"

int config_init();
int cfg_get_base_confing();
int cfg_add_ipcd(char *name);
int cfg_remove_ipcd(char *name);
int cfg_get_oneipcd(char *ipcd_name);
#endif // ! _CONFIG_H_