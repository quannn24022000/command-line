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

struct intern *intern_database_lookup(char *id)
{
	int i;

	if (NULL == id)
		return NULL;

	for (i = 0; i < INTERN_MAX; i++)
	{
		if (TRUE == interns[i].status && !strcmp(interns[i].id, id))
			return &(interns[i]);
	}

	return NULL;
}

struct intern *intern_database_valid_index_get(void)
{
	int i;

	for (i = 0; i < INTERN_MAX; i++)
	{
		if (FALSE == interns[i].status)
			return &interns[i];
	}

	return NULL;
}

ret_val_t intern_database_add(char *id, char *name)
{
	struct intern *intern;

	if (NULL == name || INTERN_NAME_MAX_LENGTH < strlen(name) || 0 >= strlen(name))
		return RET_ERR_INTERN_NAME_INVALID;

	if (NULL == id || INTERN_ID_MAX_LENGTH < strlen(id) || 0 >= strlen(id))
		return RET_ERR_INTERN_ID_INVALID;

	if (NULL != (intern = intern_database_lookup(id)))
		return RET_ERR_INTERN_ID_DUPLICATED;


	if (NULL == (intern = intern_database_valid_index_get()))
		return RET_ERR_INTERN_OVER_MAX;

	intern->status = TRUE;
	strcpy(intern->id, id);
	strcpy(intern->name, name);
	
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
	struct intern *intern;

	if (NULL == id || INTERN_ID_MAX_LENGTH < strlen(id) || 0 >= strlen(id))
    return RET_ERR_INTERN_ID_INVALID;

	if (NULL == (intern = intern_database_lookup(id)))
		return RET_ERR_INTERN_ID_NOT_FOUND;
	
	memset(intern, 0, sizeof(struct intern));
	return RET_ERR_NONE;
}

ret_val_t intern_database_update(char *id, char *name)
{
	struct intern *intern;
	int i, isadd = 0;

	if (NULL == name || INTERN_NAME_MAX_LENGTH < strlen(name) || 0 >= strlen(name))
		return RET_ERR_INTERN_NAME_INVALID;

	if (NULL == id || INTERN_ID_MAX_LENGTH < strlen(id) || 0 >= strlen(id))
		return RET_ERR_INTERN_ID_INVALID;
	
	intern = intern_database_lookup(id);
	if (NULL == intern)
		return RET_ERR_INTERN_ID_NOT_FOUND;

	strcpy(intern->name, name);
	return RET_ERR_NONE;
}

ret_val_t intern_database_builder(char **cli, int *count)
{
	int idx = 0;
	char buf[CMDSHELL_MAX_TOKEN_LEN+1] = {0};

	for (idx = 0; idx < INTERN_MAX; idx ++)
	{
		if (FALSE == interns[idx].status)
			continue;

		snprintf(buf, sizeof(buf), "intern add id %s name %s", interns[idx].id, interns[idx].name);
		strncpy(cli[(*count)++], buf, CMDSHELL_MAX_TOKEN_LEN);
		printf("%s\n", buf);
	}
	return RET_ERR_NONE;
}
