#include <stdio.h>
#include "intern_cli.h"
#include "intern_database.h"
#include "lib.h"
#include "lib_cli.h"
#include "lib_topic.h" 
#include "lib_intern.h"

ret_val_t intern_cli_add_cb(int argc, char (*argv)[CMDSHELL_MAX_TOKEN_LEN])
{
	return intern_database_add(argv[3], argv[5]);
}

ret_val_t intern_cli_add_define()
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

    return cmdmgmt_cli_register(token, tokencnt, intern_cli_add_cb, STATUS_TRUE, MODULE_INTERN);
}

ret_val_t intern_cli_show_cb(int argc, char (*argv)[CMDSHELL_MAX_TOKEN_LEN])
{
    return intern_database_show();
}

ret_val_t intern_cli_show_define()
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

    return cmdmgmt_cli_register(token, tokencnt, intern_cli_show_cb, STATUS_TRUE, MODULE_INTERN);
}

ret_val_t intern_cli_del_cb(int argc, char (*argv)[CMDSHELL_MAX_TOKEN_LEN])
{
    return intern_database_del(argv[3]);
}

ret_val_t intern_cli_del_define()
{
    int tokencnt = 2;

    struct token token[2] = {
        {
            "intern",
            "Key word specific to interact with intern",
            TOKEN_KEY
        },
        {
            "del",
            "delete interns action",
            TOKEN_KEY
        },
		{
			"",
			"id of intern that we want to delete",
			TOKEN_ARG
		}
    };

    return cmdmgmt_cli_register(token, tokencnt, intern_cli_del_cb, STATUS_TRUE, MODULE_INTERN);
}

ret_val_t intern_cli_update_cb(int argc, char (*argv)[CMDSHELL_MAX_TOKEN_LEN])
{
    return intern_database_update(argv[3], argv[5]);
}

ret_val_t intern_cli_update_define()
{
    int tokencnt = 6;

    struct token token[6] = {
		{
			"intern",
			"Key word specific to interact with intern",
			TOKEN_KEY
		},
		{
			"update",
			"Update database information for existed intern",
			TOKEN_KEY
		},
		{
			"id",
			"identification keyword of existed intern",
			TOKEN_KEY
		},
		{
			"",
			"specific identification of existed intern",
			TOKEN_ARG
		},
		{
			"name",
			"name keyword of existed intern",
			TOKEN_KEY
		},
		{
			"",
			"specific name of existed intern",
			TOKEN_ARG
		}
	};

    return cmdmgmt_cli_register(token, tokencnt, intern_cli_update_cb, STATUS_TRUE, MODULE_INTERN);
}

ret_val_t intern_cli_builder(char **cli, int count)
{
	return intern_database_builder();
}

ret_val_t intern_cli_init(void)
{
	ret_val_t ret = RET_ERR_NONE;

	cmdmgmt_cli_builder_register(MODULE_INTERN, intern_cli_builder);
	
	if (RET_ERR_NONE != (ret = intern_cli_add_define()))
		return ret;

	if (RET_ERR_NONE != (ret = intern_cli_show_define()))
		return ret;

	if (RET_ERR_NONE != (ret = intern_cli_del_define()))
		return ret;

	if (RET_ERR_NONE != (ret = intern_cli_update_define()))
		return ret;

	return RET_ERR_NONE;
}


