#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

// display error function call
void display_error(const char *message);

// check the ID3 presence
int check_id3_tag_presence(const char *filename);

#endif      // ERROR_HANDLING_H
