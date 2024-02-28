#ifndef __LIB_CLI_H
#define __LIB_CLI_H

#include "lib.h"

#define CMDSHELL_MAX_TOKEN      15
#define CMDSHELL_MAX_TOKEN_LEN  50
#define CMDSHELL_MAX_HELP_LEN   100
#define CMDSHELL_CMD_MAX_LEN    1000

typedef enum _module_type 
{
	MODULE_MIN = 0,
    MODULE_CMDMGMT = MODULE_MIN,
    MODULE_CMDSHELL,
    MODULE_ITMGMT,
    MODULE_INTERN,
    MODULE_TOPIC,
	MODULE_CORE,
    MODULE_CFG,
    MODULE_LIB,
    MODULE_MAX = 255
} module_type_t;

typedef enum _status_type 
{
    STATUS_FALSE = FALSE,
    STATUS_TRUE = TRUE,
} status_type_t;

typedef enum _token_type 
{
	TOKEN_MIN,
    TOKEN_ARG,
    TOKEN_KEY,
    TOKEN_MAX
} token_type_t;

struct token 
{
	char token[CMDSHELL_MAX_TOKEN_LEN];
	char help[CMDSHELL_MAX_HELP_LEN];
	token_type_t type;
};

struct cli 
{
	struct token tokenlist[CMDSHELL_MAX_TOKEN];
	int tokencnt;
	ret_val_t (*func)(int argc, char (*argv)[CMDSHELL_MAX_TOKEN_LEN]);
	module_type_t module;
	status_type_t status;
};

struct cli_builder
{
	ret_val_t (*func)(char **cli, int count);
};

#endif /*__LIB_CLI_H*/
