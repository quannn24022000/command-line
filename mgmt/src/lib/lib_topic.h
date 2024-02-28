#ifndef __LIB_TOPIC_H
#define __LIB_TOPIC_H

#ifndef TOPIC_MAX
#define TOPIC_MAX                       30
#endif

#ifndef INTERN_MAX
#define INTERN_MAX                      30
#endif

#define TOPIC_ID_MAX_LENGTH            16
#define TOPIC_NAME_MAX_LENGTH          30

struct topic
{
    char name[TOPIC_NAME_MAX_LENGTH+1];
    char id[TOPIC_ID_MAX_LENGTH+1];
    int status;
    struct intern *interns[INTERN_MAX];
};

#endif /* __LIB_TOPIC_H */
