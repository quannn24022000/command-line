#ifndef __CFG_HELPER_H
#define __CFG_HELPER_H

#include <stdint.h>
#include <unistd.h>

#define HOSTNAME "admin"

typedef struct commands 
{
	uint8_t id;
	char *cmd;
	char *desc;
} commands_t;

typedef struct options 
{
	uint8_t id;
	char *sopt;
	char *lopt;
	char *desc;
} options_t;

void cfg_helper_show(void);
void cfg_hostname_set(const char *name);
const char *cfg_hostname_get(void);
int cfg_hostname_length_get(void);

#endif /* __CFG_HELPER_H */
