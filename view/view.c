// view.c
// Let's create a presentation for the metadata[] structure.
// Created by Fred Nora.

#include <sys/stat.h>
#include <fcntl.h>

#include "../gramcnf.h"
#include "view.h"

#include "../model/lexer.h"


// The buffer for the final html file.
static char html_buffer[4096];
//char *pt_html_buffer;

//
// ========================================
//

static int CreateAppFile2(void);
static int __generate_html_output_file(void);

//
// ========================================
//

static int CreateAppFile2(void)
{
    int filedes=0;

    filedes = creat( "index.html",
                 S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP );
    if (filedes != -1) {
        /* process file */
        // close( filedes );
        //return EXIT_SUCCESS;
        return (int) filedes;
    }

    return -1;
}

// Generate a html output file baseed on the metadata structure.
static int __generate_html_output_file(void)
{
    register int i=0;
    int MetadataMaxIndex = 32;

    FILE *fp; // for "open" tag.
    int C;  // byte from file
    char FileBuffer[1028];
    int counter=0;

    printf("\n");
    printf("==========================================\n");
    printf("Generate the html file\n");

// --------------
// Creating the final .html file for own application.
    int fd = (int) CreateAppFile2();
    if (fd == -1){
        printf("Couldn't create index.html\n");
        goto fail;
    }

// --------------
    for (i=0; i<4096; i++)
        html_buffer[i] = (char) 0;    

// --------------
// Open::
    strcat(html_buffer, "<!DOCTYPE html>\n");
    
    // html
    strcat(html_buffer, "<html leng=\"en\">\n");

    // head
    strcat(html_buffer, "<head>\n");
    strcat(html_buffer, "<meta charset=\"UTF-8\">\n");
    strcat(html_buffer,"<meta name=\"generator\" content=\"mt interpreter\">\n");
    strcat(html_buffer, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n");
    strcat(html_buffer, "<title>index.html</title>\n");
    strcat(html_buffer, "<link href=\"gramado.css\" rel=\"stylesheet\" >\n");
    strcat(html_buffer, "</head>\n");

    // body
    strcat(html_buffer, "<body>\n");

// Metadata
    for (i=0; i<MetadataMaxIndex; i++)
    {
        if (metadata[i].initialized == TRUE)
        {
            printf("\n");
            printf("id{%d}: tag{%s} name{%s} content{%s}\n",
                metadata[i].id,
                metadata[i].meta_tag,
                metadata[i].name,
                metadata[i].content );
            //printf("name{%s}\n",    metadata[i].name); 
            //printf("content{%s}\n", metadata[i].content);

            // header
            if ( strncmp( metadata[i].name, "header", 6) == 0 )
            {
                strcat(html_buffer, "<br>\n");
                strcat(html_buffer, "<header>\n");
                if (sizeof(metadata[i].content) < 1028)
                {
                    strcat(html_buffer, "<div class=\"gramado-header\">\n");
                    strcat(html_buffer, metadata[i].content);
                    strcat(html_buffer, "</div>\n");
                }
                strcat(html_buffer, "</header>\n");
            }

            // article
            if ( strncmp( metadata[i].name, "article", 7) == 0 )
            {
                strcat(html_buffer, "<br>\n");
                strcat(html_buffer, "<article>\n");
                if (sizeof(metadata[i].content) < 1028)
                {
                    strcat(html_buffer, "<div class=\"gramado-container\">\n");
                    strcat(html_buffer, "<p>\n");
                    strcat(html_buffer, metadata[i].content);
                    strcat(html_buffer, "</p>\n");
                    strcat(html_buffer, "</div>\n");
                }
                strcat(html_buffer, "</article>\n");
            }

            // section
            if ( strncmp( metadata[i].name, "section", 7) == 0 )
            {
                strcat(html_buffer, "<br>\n");
                strcat(html_buffer, "<section>\n");
                if (sizeof(metadata[i].content) < 1028)
                {
                    strcat(html_buffer, "<div class=\"gramado-container\">\n");
                    strcat(html_buffer, metadata[i].content);
                    strcat(html_buffer, "</div>\n");
                }
                strcat(html_buffer, "</section>\n");
            }

            // ...  #todo

            // footer
            if ( strncmp( metadata[i].name, "footer", 6) == 0 )
            {
                strcat(html_buffer, "<br>\n");
                strcat(html_buffer, "<footer>\n");
                if (sizeof(metadata[i].content) < 1028)
                {
                    strcat(html_buffer, "<div class=\"gramado-footer\">\n");
                    strcat(html_buffer, metadata[i].content);
                    strcat(html_buffer, "</div>\n");
                }
                strcat(html_buffer, "</footer>\n");
            }

            // open
            if ( strncmp( metadata[i].name, "open", 4) == 0 )
            {
                if (sizeof(metadata[i].content) < 1028)
                {
                    fp = fopen((char *) metadata[i].content, "rb");
                    if ((void*) fp != NULL)
                    {
                        counter=0;
                        memset(FileBuffer,0,1028);
                        while (1)
                        {
                            if (counter >= 64)
                                break;

                            C = (int) getc(fp);
                            if (C == EOF)
                                break;
                            if (C == 0)
                                break;
                            
                            FileBuffer[counter] = (char) C;
                            counter++;
                        };
                        
                        // #bugbug: Buffer overflow
                        // The One big buffer inside a small buffer.
                        strcat(html_buffer, FileBuffer);
                        fclose(fp);
                        fp = NULL;
                    }
                }
            }
        }
    };

    strcat(html_buffer, "</body>\n");
    strcat(html_buffer, "</html>\n");

// -----------
// Close::
    write(fd, html_buffer, 1027);
    close(fd);

    printf("\n");
    printf("==========================================\n");

    return 0;
fail:
    return (int) -1;
}

int viewPrintStats(void)
{
    printf("\n");
    printf("debugShowStat\n");

// -------------------------
// Lexer
    printf("==========================================\n");
    printf("== Lexer info ==\n");
    printf("number of lines: {%d}\n",lexer_number_of_lines);
    printf("first line:      {%d}\n",lexer_firstline);
    printf("last line:       {%d}\n",lexer_lastline);
    printf("current line:    {%d}\n",lexer_currentline);  // The number of lines.
    printf("token count:     {%d}\n",lexer_token_count);
    // ...

// -------------------------
// Parser
    printf("==========================================\n");
    printf("== Parser info ==\n");
    printf("infile_size:     {%d bytes}\n",infile_size);
    printf("outfile_size:    {%d bytes}\n",outfile_size);
	// ...

    return 0;
}


// Called by main.c
int viewGenerateOutputFile(void)
{

//
// Select the type of output file.
//

    //#todo: Get this info from the user.
    int output_type = 1;

    // html
    if (output_type == 1){
        __generate_html_output_file();
    
    // #todo: 
    // We can create more options and more workers.

    // ?
    } else if (output_type == 2){
        printf("Invalid output_type\n");
        exit(1);

    // ...
    }else{
        printf("Invalid output_type\n");
        exit(1);
    };

    return 0;
}


