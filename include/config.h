#ifndef  _CONFIG_H_
#define _CONFIG_H_

int config_init();
int cfg_get_base_confing();
int cfg_add_ipcd(char *name);
int cfg_remove_ipcd(char *name);

#endif // ! _CONFIG_H_