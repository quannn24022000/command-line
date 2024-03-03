#include "intern.h"
#include "topic.h"
#include "intern_cli.h"
#include "intern_database.h"

void intern_init()
{
	intern_database_init();
	intern_cli_init();
}

