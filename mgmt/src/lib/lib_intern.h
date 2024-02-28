#ifndef __LIB_INTERN_H
#define __LIB_INTERN_H

#ifndef TOPIC_MAX
#define TOPIC_MAX                       30
#endif

#ifndef INTERN_MAX
#define INTERN_MAX                      30
#endif

#define INTERN_ID_MAX_LENGTH            16
#define INTERN_NAME_MAX_LENGTH          30

struct intern
{
    char name[INTERN_NAME_MAX_LENGTH+1];
    char id[INTERN_ID_MAX_LENGTH+1];
    int status;
    struct topic *topics[TOPIC_MAX];
};

#endif /* __LIB_INTERN_H */
