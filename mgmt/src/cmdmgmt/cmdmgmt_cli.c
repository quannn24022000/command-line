#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lib.h"
#include "cmdmgmt_cli.h"

struct cmdmgmt cmds;
struct cmdmgmt_builder cmdbuilders;

ret_val_t cmdmgmt_cli_init()
{
	int i;

	memset(&cmds, 0, sizeof(struct cmdmgmt));

	for (i = 0; i < CMDMGMT_CLI_LIST_MAX; i++)
	{
		cmds.list[i].status = STATUS_FALSE;
	}

	return RET_ERR_NONE;
}

ret_val_t cmdmgmt_cli_builder_init()
{
	memset(&cmdbuilders, 0, sizeof(struct cmdmgmt_builder));
	return RET_ERR_NONE;
}

ret_val_t cmdmgmt_init()
{
	ret_val_t ret = RET_ERR_NONE;

	if (RET_ERR_NONE != (ret = cmdmgmt_cli_init()))
		return ret;

	if (RET_ERR_NONE != (ret = cmdmgmt_cli_builder_init()))
		return ret;

	return ret;
}

ret_val_t cmdmgmt_cli_register(struct token tokenlist[], int tokencnt, ret_val_t (*func)(int, char (*)[CMDSHELL_MAX_TOKEN_LEN]), status_type_t status, module_type_t module)
{
	int i;

	if (!tokencnt || !tokenlist || !status || !func)
	{
		return RET_ERR_INVALID_VALUE;
	}

	for (i = 0; i < CMDMGMT_CLI_LIST_MAX; i++)
	{
		if (STATUS_FALSE == cmds.list[i].status)
		{
			memcpy(cmds.list[i].tokenlist, tokenlist, tokencnt*sizeof(struct token));
			cmds.list[i].tokencnt = tokencnt;
			cmds.list[i].status = status;
			cmds.list[i].module = module;
			cmds.list[i].func = func;
			break;
		}
	}

	return RET_ERR_NONE;
}

ret_val_t cmdmgmt_cli_builder_register(module_type_t module, ret_val_t (*func)(char**, int))
{
	cmdbuilders.list[module].func = func;
	return RET_ERR_NONE;
}

struct cli *cmdmgmt_cli_parse(int tokencnt, char (*token)[CMDSHELL_MAX_TOKEN_LEN])
{
	int i = 0;
	int j = 0;
	int isfound = 0;

	if (!tokencnt || !token)
	{
		return NULL;
	}

	for (i = 0; i < CMDMGMT_CLI_LIST_MAX; i++)
	{
		if (STATUS_FALSE == cmds.list[i].status)
			continue;

		if (tokencnt != cmds.list[i].tokencnt)
			continue;
		
		for (j = 0; j < tokencnt; j++)
		{
			if (TOKEN_ARG == cmds.list[i].tokenlist[j].type)
				continue;

			if (strcmp(token[j], cmds.list[i].tokenlist[j].token))
			{
				isfound = 0;
				break;
			}
			
			isfound = 1;
		}

		if (isfound)
		{
			return &(cmds.list[i]);
		}
	}

	return NULL;
}

ret_val_t cmdmgmt_cli_execute(int tokencnt, char (*token)[CMDSHELL_MAX_TOKEN_LEN])
{
	struct cli *cli = NULL;

	if (!tokencnt || !token)
	{
		return RET_ERR_NONE;
	}

	if (tokencnt == 1 && !strcasecmp(token[0], "exit"))
	{
		return RET_ERR_EXIT;
	}

	cli = cmdmgmt_cli_parse(tokencnt, token);
	
	if (NULL != cli)
	{
		return cli->func(tokencnt, token);
	}

	return RET_ERR_NONE;
}

ret_val_t cmdmgmt_cli_running_show()
{
	char **cli;
	
	if (NULL != cmdbuilders.list[MODULE_CMDSHELL].func)
		cmdbuilders.list[MODULE_CMDSHELL].func(cli,1);
	
	if (NULL != cmdbuilders.list[MODULE_INTERN]. func)
		cmdbuilders.list[MODULE_INTERN].func(cli,1);

	return RET_ERR_NONE;
}
