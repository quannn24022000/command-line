#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lib.h"
#include "cmdmgmt_cli.h"

struct cmdmgmt cmds;
struct cmdmgmt_builder cmdbuilders;

/* module name should have the same length --> align name of module*/
module_name_map_t module_name_map[] = {
    {MODULE_CMDSHELL, "MODULE CMDSHELL"},
    {MODULE_ITMGMT,   " MODULE ITMGMT "},
    {MODULE_CFG,      "  MODULE CFG   "},
    {MODULE_INTERN,   " MODULE INTERN "},
    {MODULE_TOPIC,    " MODULE_TOPIC  "},
    {FIRST_SENTINAL, SECOND_SENTINAL}
};

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

ret_val_t cmdmgmt_cli_builder_register(module_type_t module, ret_val_t (*func)(char**, int*))
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

void cmdmgmt_cli_module_running_show(int module, char **cli, int *count)
{
	int i, idx, size;

	size = sizeof(module_name_map)/sizeof(module_name_map_t);

	for (i = 0; i < size; i++) 
	{
		if (module_name_map[i].module == module)
		{
			idx = i;
			break;
		}
	}
	for (i = 0; i < 50; i++)
		printf("-");
	printf("%s", module_name_map[idx].name);
	for (i = 0; i < 50; i++)
		printf("-");
	printf("\n");

	if (NULL !=  cmdbuilders.list[module].func)
		cmdbuilders.list[module].func(cli, count);
	
	printf("\n\n");
}

ret_val_t cmdmgmt_cli_running_show()
{
	ret_val_t ret;

	char **cli = NULL;
	int i, idx, size;
	int count = 0;

	if (NULL == (cli = (char**) malloc (CMDMGMT_CLI_LIST_MAX * sizeof(char*))))
		return RET_ERR_NO_MEM;

	for (i = 0; i < CMDMGMT_CLI_LIST_MAX; i++)
	{
		if (NULL == (cli[i] = (char*) malloc (CMDSHELL_MAX_TOKEN_LEN * sizeof(char))))
			goto __mem_free;
	}

	cmdmgmt_cli_module_running_show(MODULE_CMDSHELL, cli, &count);
	cmdmgmt_cli_module_running_show(MODULE_INTERN, cli, &count);

	printf("\nTOTAL COMMAND = %d, ALL SYSTEM COMMANDS:\n\n", count);
	for (i = 0; i < count; i++)
	{
		if (cli && cli[i])
			printf("%-4d%s\n", i+1, cli[i]);
	}
	
__mem_free:
    for (i = 0; i < CMDMGMT_CLI_LIST_MAX; i++)
	{
        if (NULL != cli[i])
            free(cli[i]);
    }

    if (NULL != cli)
        free(cli);

	return RET_ERR_NONE;
}
