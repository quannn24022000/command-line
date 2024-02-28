#include <stdio.h>
#include "intern_cli.h"
#include "lib.h"
#include "lib_cli.h"
#include "lib_topic.h" 
#include "lib_intern.h"

ret_val_t intern_cli_database_show_cb(int argc, char (*argv)[CMDSHELL_MAX_TOKEN_LEN])
{
    return 0;
}

ret_val_t intern_cli_database_show()
{
    int tokencnt = 2;

    struct token token[2] = {
        {
            "intern",
            "Key word specific to interact with intern",
            TOKEN_KEY
        },
        {
            "show",
            "Show all interns database information",
            TOKEN_KEY
        }
    };

    return cmdmgmt_cli_register(token, tokencnt, intern_cli_database_show_cb, STATUS_TRUE, MODULE_INTERN);
}

ret_val_t intern_cli_database_add_cb(int argc, char (*argv)[CMDSHELL_MAX_TOKEN_LEN])
{
	return 0;
}

ret_val_t intern_cli_database_add()
{
    int tokencnt = 6;

    struct token token[6] = {
        {
            "intern",
            "Key word specific to interact with intern",
            TOKEN_KEY
        },
        {
            "add",
            "Add database information for new intern",
            TOKEN_KEY
        },
        {
            "id",
            "identification keyword of new intern",
            TOKEN_KEY
        },
        {
            "",
            "specific identification of new intern",
            TOKEN_ARG
        },
		{
			"name",
			"name keyword of new intern",
			TOKEN_KEY
		},
		{
			"",
			"specific name of new intern",
			TOKEN_ARG
		}
    };

    return cmdmgmt_cli_register(token, tokencnt, intern_cli_database_add_cb, STATUS_TRUE, MODULE_INTERN);
}

ret_val_t intern_cli_init(void)
{
	int ret;
	//cmdmgmt_builder();

	if (RET_ERR_NONE != (ret = intern_cli_database_add()))
		return ret;

	if (RET_ERR_NONE != (ret = intern_cli_database_show()))
		return ret;

	return RET_ERR_NONE;
}


