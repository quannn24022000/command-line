#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib.h"
#include "lib_cli.h"
#include "cfg_helper.h"					/*Missing prototype lead to return 4 byte interger instead 8 byte pointer so segmentation fault*/
#include "cmdmgmt_cli.h"
#include "cmdshell_cli.h"
#include "lib_intern.h"
#include "lib_topic.h"
#include "cfg_helper.h"

ret_val_t cmdshell_cli_error_display(int ret)
{
    switch(ret)
    {
        case RET_ERR_NONE:
        case RET_ERR_EXIT:
            break;

        case RET_ERR_NO_MEM:
            printf("%%ERROR: No have enough memory.\n");
            break;

        case RET_ERR_INVALID_PARAM:
            printf("%%ERROR: Invalid param.\n");
            break;

        case RET_ERR_INVALID_VALUE:
            printf("%%ERROR: Invalid value.\n");
            break;

        case RET_ERR_TOKEN_PARAM:
            printf("%%ERROR: Invalid token params.\n");
            break;

        case RET_ERR_CMDMGMT_NOT_FOUND:
            printf("%%ERROR: Not found the command.\n");
            break;

        case RET_ERR_DEBUG_OPTION_INVALID:
            printf("%%ERROR: Invalid debugging option. Choose \"on|off\".\n");
            break;

        case RET_ERR_INTERN_NAME_INVALID:
            printf("%%ERROR: Invalid intern name. Max len is %d\n", INTERN_NAME_MAX_LENGTH);
            break;

        case RET_ERR_INTERN_ID_NOT_FOUND:
            printf("%%ERROR: Not found the intern ID\n");
            break;

        case RET_ERR_INTERN_ID_INVALID:
            printf("%%ERROR: Invalid intern ID, must be positive and unique\n");
            break;

        case RET_ERR_INTERN_ID_DUPLICATED:
            printf("%%ERROR: Duplicated intern ID\n");
            break;

        case RET_ERR_INTERN_OVER_MAX:
            printf("%%ERROR: Over max number of interns. Max is %d\n", INTERN_MAX);
            break;

        case RET_ERR_TOPIC_NAME_INVALID:
            printf("%%ERROR: Invalid topic name. Max len is %d\n", TOPIC_NAME_MAX_LENGTH);
            break;

        case RET_ERR_TOPIC_ID_NOT_FOUND:
            printf("%%ERROR: Not found the topic ID\n");
            break;

        case RET_ERR_TOPIC_ID_INVALID:
            printf("%%ERROR: Invalid topic ID, must be positive and unique\n");
            break;

        case RET_ERR_TOPIC_ID_DUPLICATED:
            printf("%%ERROR: Duplicated topic ID\n");
            break;

        case RET__ERR_TOPIC_OVER_MAX:
            printf("%%ERROR: Over max number of topics. Max is %d\n", TOPIC_MAX);
            break;

        case RET_ERR_ITMGMT_INTERN_ENROLL_TOPIC_FAILED:
            printf("%%ERROR: Failed to enroll the topic from interns\n");
            break;

        case RET_ERR_ITMGMT_INTERN_LEAVE_TOPIC_FAILED:
            printf("%%ERROR: Failed to leave the topic from interns\n");
            break;

        case RET_ERR_ITMGMT_INTERN_ENROLLED:
            printf("%%ERROR: the intern enrolled the topic before\n");
            break;

        case RET_ERR_ITMGMT_INTERN_LEFT:
            printf("%%ERROR: the intern left the topic before\n");
            break;

        default:
            printf("%%ERROR: Unknown.\n");
            break;
    }

    return 0;
}

ret_val_t cmdshell_cli_show_hostname_cb(int argc, char (*argv)[CMDSHELL_MAX_TOKEN_LEN])
{
	char *hostname;

	hostname = cfg_hostname_get();
	printf("\nHOSTNAME: %s\n\n", hostname);
	return RET_ERR_NONE;
}

ret_val_t cmdshell_cli_show_hostname_define()
{
	int tokencnt = 3;

	struct token token[3] = {
		{
			"cmdshell",
			"Key word specific to show cmdshell config",
			TOKEN_KEY 
		},
		{
			"show",
			"Show action to get information",
			TOKEN_KEY
		},
		{
			"hostname",
			"Current host name of system",
			TOKEN_KEY
		}
	};

	return cmdmgmt_cli_register(token, tokencnt, cmdshell_cli_show_hostname_cb, STATUS_TRUE, MODULE_CMDSHELL);
}

ret_val_t cmdshell_cli_set_hostname_cb(int argc, char (*argv)[CMDSHELL_MAX_TOKEN_LEN])
{
	cfg_hostname_set(argv[argc-1]);
	return RET_ERR_NONE;
}

ret_val_t cmdshell_cli_set_hostname_define()
{
	int tokencnt = 4;

	struct token token[4] = {
		{
			"cmdshell",
			"Key word specific to show cmdshell config",
			TOKEN_KEY
		},
		{
			"set",
			"Set information",
			TOKEN_KEY
		},
		{
			"hostname",
			"Host name information",
			TOKEN_KEY
		},
		{
			"",
			"New host name to set",
			TOKEN_ARG
		}
	};

	return cmdmgmt_cli_register(token, tokencnt, cmdshell_cli_set_hostname_cb, STATUS_TRUE, MODULE_CMDSHELL);
}

ret_val_t cmdshell_cli_show_running_cb(int argc, char (*argv)[CMDSHELL_MAX_TOKEN_LEN])
{
    return cmdmgmt_cli_running_show();
}

ret_val_t cmdshell_cli_show_running_define()
{
    int tokencnt = 3;

    struct token token[3] = {
        {
            "cmdshell",
            "Key word specific to show cmdshell config",
            TOKEN_KEY
        },
        {
            "show",
            "Show action",
            TOKEN_KEY
        },
        {
            "running",
            "Current running command",
            TOKEN_KEY
        }
    };

    return cmdmgmt_cli_register(token, tokencnt, cmdshell_cli_show_running_cb, STATUS_TRUE, MODULE_CMDSHELL);
}

ret_val_t cmdshell_cli_builder(char **cli, int count)
{
	char *hostname = NULL;
	
	hostname = cfg_hostname_get();
	if (strcmp(hostname, HOSTNAME)) {
		printf("cmdshell set hostname %s\n", hostname);
	}

	return RET_ERR_NONE;
}

ret_val_t cmdshell_cli_init()
{
	ret_val_t ret = RET_ERR_NONE;

	cmdmgmt_cli_builder_register(MODULE_CMDSHELL, cmdshell_cli_builder);

	if (RET_ERR_NONE != (ret = cmdshell_cli_show_hostname_define()))
		return ret;

	if (RET_ERR_NONE != (ret = cmdshell_cli_set_hostname_define()))
		return ret;

	if (RET_ERR_NONE != (ret = cmdshell_cli_show_running_define()))
		return ret;

	return RET_ERR_NONE;
}


