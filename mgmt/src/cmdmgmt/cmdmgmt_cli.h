#ifndef __CMDMGMT_CLI_H
#define __CMDMGMT_CLI_H

#include "lib.h"
#include "lib_cli.h"

#define CMDMGMT_CLI_LIST_MAX 1000

struct cmdmgmt 
{
	struct cli list[CMDMGMT_CLI_LIST_MAX];
};

struct cmdmgmt_builder
{
	struct cli_builder list[MODULE_MAX];
};

ret_val_t cmdmgmt_cli_init(void);
ret_val_t cmdmgmt_cli_builder_init(void);
ret_val_t cmdmgmt_cli_register(struct token tokenlist[], int tokencnt, ret_val_t (*func)(int, char (*)[CMDSHELL_MAX_TOKEN_LEN]), status_type_t status, module_type_t module);
ret_val_t cmdmgmt_cli_builder_register(module_type_t module, ret_val_t (*func)(char**, int));
ret_val_t cmdmgmt_cli_execute(int tokencnt, char (*token)[CMDSHELL_MAX_TOKEN_LEN]);

#endif /* __CMDMGMT_CLI_H */
