// Implementation of functions for writing and editing ID3 tags in MP3 files.

#include <stdio.h>
#include <string.h>
#include "id3.h"
#include "id3.h"
#include "id3.h"
#include <stdlib.h>

// Edit the content of specific ID3 Tag
void edit_content(char *Tag_Name, char *flag, const char *value, FILE *nptr)
{
    int new_size = strlen(value) + 1;
    unsigned char new_sizebyte[4];
    
    // Convert new_size to Big endian(4 bytes)
    new_sizebyte[0] = new_size >> 24 & 0xFF;
    new_sizebyte[1] = new_size >> 16 & 0xFF;
    new_sizebyte[2] = new_size >> 8 & 0xFF;
    new_sizebyte[3] = new_size & 0xFF;
    fwrite(Tag_Name, 1, 4, nptr);
    fwrite(new_sizebyte, 1, 4, nptr);
    fwrite(flag, 1, 2, nptr);
    fwrite("\0", 1, 1, nptr);
    fwrite(value, 1, new_size - 1, nptr); // write new content
}

// To ask conformation for editing
int Conform(const char *tag, const char *value)
{
    const char *title;

    if (strcmp(tag, "-t") == 0)
        title = "Title";
    else if (strcmp(tag, "-a") == 0)
        title = "Artist";
    else if (strcmp(tag, "-A") == 0)
        title = "Album";
    else if (strcmp(tag, "-y") == 0)
    {
        // validation for year
        title = "Year";
        if (strlen(value) == 4)
        {
            int i = 0;
            while (i < 4)
            {
                if (!(value[i] >= '0' && value[i] <= '9'))
                {
                    printf("Invalid Year!!!\n");
                    return 1;
                }
                i++;
            }
        }
        else
        {
            printf("Invalid Year!!!\n");
            return 1;
        }
    }
    else if (strcmp(tag, "-c") == 0)
        title = "Comment";
    else if (strcmp(tag, "-g") == 0)
        title = "Genre";
    else
    {
        printf("Invalid Tag!!!\n");
        return 1;
    }
    // Asking user to conformation for edit
    printf("%s : %s\n", title, value);
    printf("Do you want to edit? (y/n): ");

    char ch;
    scanf(" %c", &ch);
    if (ch == 'y' || ch == 'Y')
        return 0;
    return 1;
}

// Edit a specific tag in an MP3 file and writes the result to a new file and rename to existing file.
int edit_tag(const char *filename, const char *tag, const char *value)
{
    FILE *nptr = fopen("new.mp3", "w"); // open a new mp3 file
    FILE *fptr = fopen(filename, "r");  // open the existing file to read

    if (fptr == NULL || nptr == NULL)
    {
        printf("No file found\n");
        return 1;
    }
    if (Conform(tag, value)) // Function call to confirm the edit
        return 1;

    char header[10];
    fread(header, 1, 10, fptr); // read header byte

    if (!(header[0] == 'I' && header[1] == 'D' && header[2] == '3')) // checking if it is a ID3 tag mp3 file
        return 1;

    fwrite(header, 1, 10, nptr); // write header byte into new file

    int i = 0;
    while (i < 6)
    {
        i++;
        char Tag_Name[5];
        unsigned char size_bytes[4];
        char flag[3] = "00";
        fread(Tag_Name, 1, 4, fptr);   // Read Tag name
        fread(size_bytes, 1, 4, fptr); // Read size
        fread(flag, 1, 3, fptr);       // Read flags and NULL byte

        // converting to little endian
        int size = size_bytes[0] << 24 | size_bytes[1] << 16 | size_bytes[2] << 8 | size_bytes[3];
        char *content = malloc(size - 1);  // allocating size for the content
        fread(content, 1, size - 1, fptr); // Read the content

        int modified = 0;

        if ((strcmp("-t", tag) == 0 && strcmp("TIT2", Tag_Name) == 0) || (strcmp("-a", tag) == 0 && strcmp("TPE1", Tag_Name) == 0) || (strcmp("-A", tag) == 0 && strcmp("TALB", Tag_Name) == 0) || (strcmp("-y", tag) == 0 && strcmp("TYER", Tag_Name) == 0) || (strcmp("-c", tag) == 0 && strcmp("COMM", Tag_Name) == 0) || (strcmp("-g", tag) == 0 && strcmp("TCON", Tag_Name) == 0))
        {
            edit_content(Tag_Name, flag, value, nptr); // To write the updated conntent
            modified = 1;
        }
        // If not modified, write original data to new file
        if (!modified)
        {
            // write bytes into new file
            fwrite(Tag_Name, 1, 4, nptr);
            fwrite(size_bytes, 1, 4, nptr);
            fwrite(flag, 1, 2, nptr);
            fwrite("\0", 1, 1, nptr);
            fwrite(content, 1, size - 1, nptr);
        }

        free(content); // clean the memory
    }
    // Copy remaining MP3 data after the Comment tag
    char ch;
    while (fread(&ch, 1, 1, fptr) > 0)
        fwrite(&ch, 1, 1, nptr);

    // close the files
    fclose(fptr);
    fclose(nptr);

    remove(filename);            // Remove the old  mp3 file
    rename("new.mp3", filename); // replace the name of new mp3 file with old mp3 file
    view_tags(filename);         // Display the updated metadata
    return 0;
}
