#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "lib_cli.h"
#include "cfg_helper.h"
#include "cmdshell_input.h"
#include "cmdmgmt_cli.h"

#define INPUT_STATE_STOP 0
#define INPUT_STATE_RUN  1

int state = INPUT_STATE_RUN;

static cmdshell_input_prompt()
{
	const char *hostname = cfg_hostname_get();
	printf("%s>", hostname);
}

ret_val_t cmdshell_input_start()
{
	int ret = RET_ERR_NONE;
	char command[CMDSHELL_CMD_MAX_LEN+1] = {0};
	char token[CMDSHELL_MAX_TOKEN][CMDSHELL_MAX_TOKEN_LEN] = {0};
	char *p_c = NULL;
	char *p = NULL;
	int tokencnt = 0;
	int tokenidx = 0;
	char c = 0;

	system ("/bin/stty -icanon min 1");

	while (state)
	{
		cmdshell_input_prompt();
		memset(command, 0, sizeof(command));
		memset(token, 0, sizeof(token));

		tokencnt = 0;
		tokenidx = 0;
	    p = token[tokencnt];

		while (state)
		{
			c = getchar();

			if (CMDSHELL_CHAR_SPACE == c) 
			{
				if (p - token[tokenidx] > 0)
				{
					tokenidx++;
					p = token[tokenidx];
				}
				continue;
			}

			if (CMDSHELL_CHAR_ENTER == c || CMDSHELL_CHAR_NEWLINE == c)
			{
				if (p - token[tokenidx] > 0)
					tokencnt = tokenidx + 1;
				else
					tokencnt = tokenidx;

				if (RET_ERR_NONE != (ret = cmdmgmt_cli_execute(tokencnt, token)))
					return cmdshell_cli_error_display(ret);
				
				break;
			}

			*p++ = c; 
			/* 
			  *p++ = c same as *(p++) = c 
			  Example p = str[100] = "nhatquan"; c = 'N'
			  And assign *p++ = c; or *(p++) = c;
			  
			  Step 1: *p = 'N';       ---> p = str[0] = 'N'
			  Step 2: p++;            ---> p = str[1]
			  If printf("%s\n", p);   ---> 'hatquan' because of p = str[1] so skip str[0]
			  If printf("%s\n", str); ---> 'Nhatquan'
			*/
		}
	}

	return RET_ERR_NONE;
}
