#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "cfg_helper.h"

extern const char *appname;
char hostname[30] = HOSTNAME;

static void usage_print()
{
    fprintf(stderr,
	"\nUsage: %s [command] [<arguments>]\n\n"
	"These are common commands and arguments used in various situation:\n",
	appname);
}

static commands_t cmds[] = {
	{1, "run"   , "Start up CLI application"},
	{2, "test"  , "Just for testing"},
	{3,  NULL   ,  NULL}
};

static options_t opts[] = {
	{1, "-h", "--help"   , "Usage helper"},
	{2, "-a", "--auth"   , "Authentication vendor"},
	{3, "-v", "--version", "Current release version"},
	{4, NULL, NULL       , NULL}
};

static void commands_print()
{
	int i = 0;
	int cmdsz = sizeof(cmds)/sizeof(struct commands);

	printf("\ncommand:\n");
	for (i = 0; i < cmdsz - 1 ; i++)
	{
		printf("\t%-10s %-100s\n", cmds[i].cmd, cmds[i].desc);
	}
}

static void options_print()
{
	int i = 0;
	int optsz = sizeof(opts)/sizeof(struct options);
	
	printf("\narguments:\n");
	for (i = 0; i < optsz - 1 ; i++)
	{
		printf("\t%-2s, %-15s %-100s\n", opts[i].sopt, opts[i].lopt, opts[i].desc);
	}
	printf("\n");
}

void cfg_hostname_set(const char *name)
{
	if (!name)
	{
		return; 
	}

	strncpy(hostname, name, sizeof(hostname) - 1);
}

const char *cfg_hostname_get()
{
	return hostname;
}

int cfg_hostname_length_get()
{
	return strlen(hostname);
}

void cfg_helper_show()
{
	usage_print();
	commands_print();
	options_print();
}
