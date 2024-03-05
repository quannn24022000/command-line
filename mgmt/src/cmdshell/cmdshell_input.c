
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
	printf("%s> ", hostname);
}

ret_val_t cmdshell_input_start()
{
	int ret = RET_ERR_NONE;
	char command[CMDSHELL_CMD_MAX_LEN+1] = {0};
	char token[CMDSHELL_MAX_TOKEN][CMDSHELL_MAX_TOKEN_LEN] = {0};
	int cur_cmd_len = 0;
	int cur_token_len = 0;
	int hostname_len = 0;
	char *p_c = NULL;
	char *p = NULL;
	int tokencnt = 0;
	int tokenidx = 0;
	int idx = 0;
	int len = 0;
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
		p_c = command;

		while (state)
		{
			//1. Validate for exceed token of one cli or exceed character of one token
			if (tokenidx >= CMDSHELL_MAX_TOKEN)
			{
				printf("\n%%ERROR: exceed maximum token of one cli. \
						Maximum token is %d\n", CMDSHELL_MAX_TOKEN);
				break;
			}

			if (p - token[tokenidx] >= CMDSHELL_MAX_TOKEN_LEN)
			{
				printf("\n%%ERROR: exceed maximum character of one token. \ 
						Maximum character is %d\n", CMDSHELL_MAX_TOKEN_LEN);
				break;
			}


			//2. Get one character one time
			c = getchar();


			//3. Handle for space character
			if (CMDSHELL_CHAR_SPACE == c) 
			{
				if (p - token[tokenidx] > 0)
				{
					tokenidx++;
					p = token[tokenidx];
				}

				*p_c++ = c;
				continue;
			}

			//4. Handle for backspace character
			if (CMDSHELL_CHAR_BS == c)
			{
				cur_cmd_len = p_c - command;
				cur_token_len = p - token[tokenidx];
				hostname_len = cfg_hostname_length_get();

				if (0 >= cur_cmd_len)
					goto PRINT_PROMPT;

				
				// Solution 1
				/*if (CMDSHELL_CHAR_SPACE != *(p_c - 1))
				{
					if (0 >= cur_token_len)
					{
						tokenidx--;
						p = token[tokenidx] + strlen(token[tokenidx]);
					}
					*(--p) = '\0';
				}*/


				// Solution 2
				if (CMDSHELL_CHAR_SPACE == *(p_c - 1) && CMDSHELL_CHAR_SPACE != *(p_c - 2))
				{
					tokenidx --;
					p = token[tokenidx] + strlen(token[tokenidx]);
				}
				if (CMDSHELL_CHAR_SPACE != *(p_c - 1))
					*(--p) = '\0';
				
				*(--p_c) = '\0';

				/*
				1. *(p_c - 1) 
				Check value of p_c - 1 and not change value in p_c
				2. *(--p_c) = '0'
				Change value in p_c - 1
				p_c = p_c - 1;
				*p_c = '0';
				*/

PRINT_PROMPT:
				len = hostname_len + 2 + cur_cmd_len + 2; // 2 for "> " and 2 for "^H"
				printf("\r");
				for (idx = 0; idx < len; idx++)
					printf("%c", CMDSHELL_CHAR_SPACE);
				printf("\r");
				
				cmdshell_input_prompt();
				printf("%s", command);
				continue;	
			}

			//5. Handle for newline or enter character
			if (CMDSHELL_CHAR_ENTER == c || CMDSHELL_CHAR_NEWLINE == c)
			{
				if (p - token[tokenidx] > 0)
					tokencnt = tokenidx + 1;
				else
					tokencnt = tokenidx;
				
				if (0 == strcasecmp(command, "exit"))
					return RET_ERR_EXIT;

				if (RET_ERR_NONE != (ret = cmdmgmt_cli_execute(tokencnt, token)))
					cmdshell_cli_error_display(ret);

				break;
			}

			*p++ = c;
			*p_c++ = c;

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

	system ("/bin/stty cooked");
	return RET_ERR_NONE;
}
