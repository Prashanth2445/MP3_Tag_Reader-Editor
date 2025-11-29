#ifndef ID3_H
#define ID3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_handling.h"

// TagData structure
typedef struct
{
    char *version;
    char *title;
    char *artist;
    char *album;
    char *year;
    char *comment;
    char *genre;
    int commentSize;
} TagData;

// Utils
TagData *create_tag_data();
void free_tag_data(TagData *data);

// Reader
TagData *read_id3_tags(const char *filename);
void display_metadata(const TagData *data, const char *filename);
void view_tags(const char *filename);

// Writer
int write_id3_tags(const char *filename, const TagData *data);
int edit_tag(const char *filename, const char *tag, const char *value);

#endif
