#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "intern.h"
#include "topic.h"
#include "cfg_version.h"
#include "cfg_helper.h"
#include "cmdmgmt_cli.h"
#include "cmdshell_cli.h"
#include "cmdshell_banner.h"

const char *appname;

int main (int argc, char **argv)
{
	appname = argv[0];
	
	if (argc != 2)
	{
		cfg_helper_show();
		return 0;
	}

	if (!strcasecmp(argv[1], "-h") || !strcasecmp(argv[1], "--help"))
	{
		cfg_helper_show();
	}
	else if (!strcasecmp(argv[1], "-a") || !strcasecmp(argv[1], "--auth"))
	{
		cfg_auth_show();
	}
	else if (!strcasecmp(argv[1], "-v") || !strcasecmp(argv[1], "--version"))
	{
		cfg_version_show();
	}
	else if (!strcasecmp(argv[1], "test"))
	{
		printf("Just for testing function\n");
	}
	else if (!strcasecmp(argv[1], "run"))
	{	
		cmdmgmt_cli_init();	
		cmdshell_cli_init();
		intern_cli_init();


		cmdshell_banner_show();
		cmdshell_input_start();

		/*printf("%d %s %s %d\n %s %s %d \n%s %s %d\n", cmds.list[0].tokencnt, cmds.list[0].tokenlist[0].token, cmds.list[0].tokenlist[0].help, cmds.list[0].tokenlist[0].type, cmds.list[0].tokenlist[1].token, cmds.list[0].tokenlist[1].help, cmds.list[0].tokenlist[1].type, cmds.list[0].tokenlist[2].token, cmds.list[0].tokenlist[2].help, cmds.list[0].tokenlist[2].type);*/

	}
	else
	{
		cfg_helper_show();
	}

	return 0;
}
