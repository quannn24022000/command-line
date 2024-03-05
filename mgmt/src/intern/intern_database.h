#ifndef __INTERN_DATABASE_H
#define __INTERN_DATABASE_H
#include "lib.h"

ret_val_t intern_database_init(void);
ret_val_t intern_database_add(char *id, char *name);
ret_val_t intern_database_show();
ret_val_t intern_database_del(char *id);
ret_val_t intern_database_update(char *id, char *name);
ret_val_t intern_database_builder(char **cli, int *count);

#endif /*__INTERN_DATABASE_H */
