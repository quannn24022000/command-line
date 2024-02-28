#ifndef __CMDSHELL_INPUT_H
#define __CMDSHELL_INPUT_H

#define CMDSHELL_CHAR_BS          8
#define CMDSHELL_CHAR_TAB         9
#define CMDSHELL_CHAR_ENTER       10
#define CMDSHELL_CHAR_NEWLINE     13
#define CMDSHELL_CHAR_SPACE       32
#define CMDSHELL_CHAR_DOUBLEQUOTE 34
#define CMDSHELL_CHAR_SINGLEQUOTE 39
#define CMDSHELL_CHAR_QUESTION    63

ret_val_t cmdshell_input_start();

#endif /* __CMDSHELL_INPUT_H */ 
