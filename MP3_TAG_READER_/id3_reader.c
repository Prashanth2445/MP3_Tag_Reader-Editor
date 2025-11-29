#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "id3.h"
#include "error_handling.h"

// view_tags function to read and display ID3 tags.
void view_tags(const char *filename)
{
    TagData *data = read_id3_tags(filename);        // Read the metadata from mp3 file.
    if (!data)
    {
        printf("Failed to read ID3 tags.\n");
        return;
    }
    display_metadata(data, filename);           // Display the metadata
    free_tag_data(data);                        // Free the allocated memory
}

// Reads ID3 tags from an MP3 file
TagData *read_id3_tags(const char *filename)
{
    FILE *fptr = fopen(filename, "r");          // Open the MP3 file for reading
    if (fptr == NULL)
    {
        printf("File not found\n");
        return 0;
    }
    char header[10];
    fread(header, 1, 10, fptr);                 // Reading ID3 header

    if (!(header[0] == 'I' && header[1] == 'D' && header[2] == '3')) // checking if it is a ID3 tag mp3 file
    {
        return 0;
    }

    TagData *data = create_tag_data();          // Initialize tag data structure
    for (int i = 0; i < 6; i++)
    {
        char Tag_Name[5];
        char Size_Byte[4];
        fread(Tag_Name, sizeof(char), 4, fptr);     // Read Tag name
        Tag_Name[4] = '\0';

        fread(Size_Byte, sizeof(char), 4, fptr);    // Read Tag size

        int Size = Size_Byte[0] << 24 | Size_Byte[1] << 16 | Size_Byte[2] << 8 | Size_Byte[3]; // converting to little endian

        if (strcmp(Tag_Name, "COMM") == 0)
            data->commentSize = Size;           // Store comment size

        fseek(fptr, 3, SEEK_CUR);               // Skip flags and encoding byte
        char *Content = malloc(Size);           // Allocate memory for tag content
        fread(Content, 1, Size - 1, fptr);      // Read tag content
        Content[Size - 1] = '\0';               // Terminate the string with NULL
        copydata(data, Content, Tag_Name);
    }
    fclose(fptr);           // close the file
    return data;
}

// copydata function compare tag names and stores the content.
void copydata(TagData *data, char *Content, char *Tag_Name)
{
    if (strcmp(Tag_Name, "TIT2") == 0)
        data->title = Content;
    else if (strcmp(Tag_Name, "TPE1") == 0)
        data->artist = Content;
    else if (strcmp(Tag_Name, "TALB") == 0)
        data->album = Content;
    else if (strcmp(Tag_Name, "TYER") == 0)
        data->year = Content;
    else if (strcmp(Tag_Name, "TCON") == 0)
        data->genre = Content;
    else if (strcmp(Tag_Name, "COMM") == 0)
        data->comment = Content;
}

// Displays the metadata from TagData structure in a formatted manner.
void display_metadata(const TagData *data, const char *filename)
{
    printf("\n\t============================================\n");
    printf("\t               MP3 TAG READER        \n");
    printf("\t============================================\n");
    printf("\tFile Name : %s\n", filename);
    printf("\tVersion   : ID3v2.3\n");
    printf("\t--------------------------------------------\n");
    printf("\tTitle     : %s\n", data->title);
    printf("\tArtist    : %s\n", data->artist);
    printf("\tAlbum     : %s\n", data->album);
    printf("\tYear      : %s\n", data->year);
    printf("\tComment   : ");
    if (data->comment != NULL)
    {
        // Print each character in comment, even if nulls are present

        for (int i = 0; i < data->commentSize; i++)
        {
            putchar(data->comment[i]);
        }
    }
    putchar('\n');
    printf("\tGenre     : %s\n", data->genre);
    printf("\t=============================================\n\n");
}