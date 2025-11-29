/*
 * Name:Prashanth reddy
 * A.no:25021_303
 * Date:11/10/2025
 * Description:
        MP3 Tag Editor is a console based project  written in C for reading, displaying, and editing ID3v2.3 metadata tags embedded in MP3 audio files.
        ID3 tags are used to store information such as the title, artist, album, year, genre, and comments about a music track.
*/

#include <stdio.h>
#include <string.h>

#include "id3.h"
#include "id3.h"
#include "error_handling.h"

// main function
int main(int argc, char *argv[])
{
    if (argc < 2) // Not enough arguments provided
    {
        display_Error(argv);
        return 1;
    }
    if (strcmp(argv[1], "-h") == 0) // Display help menu
    {
        display_help(argv);
        return 0;
    }
    else if (strcmp(argv[1], "-v") == 0 && argc == 3) // View tags in the MP3 file
    {
        view_tags(argv[2]);
    }
    else if (strcmp(argv[1], "-e") == 0 && argc == 5) // Edit tags in the MP3 file
    {
        char *filename = argv[2]; // mp3 file name
        char *tag = argv[3];      // Tag modifier
        char *value = argv[4];    // Tag Value

        if (edit_tag(filename, tag, value) != 0)
        {
            printf("Failed to edit Tag.\n");
            return 1;
        }
        printf("Tag edited successfully.\n");
    }
    else
    {
        display_help(argv);
        return 1;
    }
    return 0;

    // Displays the help message for the MP3 Tag Reader application.
    void display_help(char *argv[])
    {
        printf("Help menu for Mp3 Tag Reader and Editor:\n\n");
        printf("For viewing the tags- %s -v <filename.mp3>\n", argv[0]);
        printf("For editing the tags- %s -e <filename.mp3> <modifier> <value>\n\n", argv[0]);
        printf("Modifier Function\n");
        printf("-t\t\tModify Title Tag\n-a\t\tModify Artist Tag\n-A\t\tModify Album Tag\n-y\t\tModify Year Tag\n-c\t\tModify Comment Tag\n-g\t\tModify Genre Tag\n");
    }

    // Displays an error message for incorrect command usage.
    void display_Error(char *argv[])
    {
        printf("ERROR: Incorrect format of command line arguments.\n");
        printf("Please use "
               "%s -h"
               " for help\n",
               argv[0]);
    }
}
