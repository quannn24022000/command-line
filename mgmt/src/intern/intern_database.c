#include <stdio.h>
#include <string.h>
#include "intern_database.h"
#include "intern_cli.h"
#include "lib.h"
#include "lib_cli.h"
#include "lib_topic.h" 
#include "lib_intern.h"

struct intern interns[INTERN_MAX];

ret_val_t intern_database_init() 
{	
	int i;

	memset(interns, 0, INTERN_MAX * sizeof(struct intern));
	
	for (i = 0; i < INTERN_MAX; i++)
	{
		interns[i].status = FALSE;
	}

	return RET_ERR_NONE;
}

ret_val_t intern_database_add(char *id, char *name)
{
	int i, isadd = 0;

	if (NULL == id ||  NULL == name)
		return RET_ERR_INVALID_VALUE;

	if (INTERN_NAME_MAX_LENGTH < strlen(name) || 0 >= strlen(name))
		return RET_ERR_INTERN_NAME_INVALID;

	if (INTERN_ID_MAX_LENGTH < strlen(id) || 0 >= strlen(id))
		return RET_ERR_INTERN_ID_INVALID;

	for (i = 0; i < INTERN_MAX; i++)
	{
		if (TRUE == interns[i].status && !strcmp(interns[i].id, id))
			return RET_ERR_INTERN_ID_DUPLICATED; 
	}

	for (i = 0; i < INTERN_MAX; i++)
	{
		if (FALSE == interns[i].status)
		{
			interns[i].status = TRUE;
			strcpy(interns[i].id, id);
			strcpy(interns[i].name, name);
			isadd = 1;
			break;
		}
	}

	if (0 == isadd)
		return RET_ERR_INTERN_OVER_MAX;
	
	return RET_ERR_NONE;
}

ret_val_t intern_database_show(void)
{
    int idx = 0;

    printf("%16s  |  %s\n",
        "       ID       ", "            Name            ");
    
	printf("------------------|--------------------------------------------\n");

    for (idx = 0; idx < INTERN_MAX; idx ++)
    {
        if (FALSE == interns[idx].status)
            continue;

        printf("%16s  |  %s\n", interns[idx].id, interns[idx].name);
    }

    printf("\n");

	return RET_ERR_NONE;
}

ret_val_t intern_database_del(char *id)
{
	return RET_ERR_NONE;
}

ret_val_t intern_database_update(char *id, char *name)
{
	return RET_ERR_NONE;
}

ret_val_t intern_database_builder(void)
{
	int idx = 0;

	for (idx = 0; idx < INTERN_MAX; idx ++)
	{
		if (FALSE == interns[idx].status)
			continue;

		printf("intern add id %s name %s\n", interns[idx].id, interns[idx].name);
	}
	return RET_ERR_NONE;
}
