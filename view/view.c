// view.c
// Let's create a presentation for the metadata[] structure.
// Created by Fred Nora.

#include <sys/stat.h>
#include <fcntl.h>

#include "../gramcnf.h"
#include "view.h"

#include "../model/lexer.h"


static int CreateAppFile2(void);
static int debugShowStat2(void);


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


// Mostra as estatísticas para o desenvolvedor.
static int debugShowStat2(void)
{
    register int i=0;
    int MetadataMaxIndex = 32;

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

    printf("\n");
    printf("==========================================\n");
    printf("Printing metadata structure. :)\n");

// #test
// Creating the final .html file for own application.
    int fd = (int) CreateAppFile2();
    char TmpString[1028];

    for (i=0; i<1028; i++)
        TmpString[i] = (char) 0;    

    if (fd == -1){
        printf("Couldn't create index.html\n");
        goto fail;
    }

// --------------
// Open::
    strcat(TmpString, "<!DOCTYPE html>\n");
    
    // html
    strcat(TmpString, "<html leng=\"en\">\n");

    // head
    strcat(TmpString, "<head>\n");
    strcat(TmpString, "<meta charset=\"UTF-8\">\n");
    strcat(TmpString,"<meta name=\"generator\" content=\"mt interpreter\">\n");
    strcat(TmpString, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n");
    strcat(TmpString, "<title>index.html</title>\n");
    strcat(TmpString, "<link href=\"gramado.css\" rel=\"stylesheet\" >\n");
    strcat(TmpString, "</head>\n");

    // body
    strcat(TmpString, "<body>\n");

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
                strcat(TmpString, "<br>\n");
                strcat(TmpString, "<header>\n");
                if (sizeof(metadata[i].content) < 1028)
                {
                    strcat(TmpString, "<div class=\"gramado-header\">\n");
                    strcat(TmpString, metadata[i].content);
                    strcat(TmpString, "</div>\n");
                }
                strcat(TmpString, "</header>\n");
            }

            // article
            if ( strncmp( metadata[i].name, "article", 7) == 0 )
            {
                strcat(TmpString, "<br>\n");
                strcat(TmpString, "<article>\n");
                if (sizeof(metadata[i].content) < 1028)
                {
                    strcat(TmpString, "<div class=\"gramado-container\">\n");
                    strcat(TmpString, "<p>\n");
                    strcat(TmpString, metadata[i].content);
                    strcat(TmpString, "</p>\n");
                    strcat(TmpString, "</div>\n");
                }
                strcat(TmpString, "</article>\n");
            }

            // section
            if ( strncmp( metadata[i].name, "section", 7) == 0 )
            {
                strcat(TmpString, "<br>\n");
                strcat(TmpString, "<section>\n");
                if (sizeof(metadata[i].content) < 1028)
                {
                    strcat(TmpString, "<div class=\"gramado-container\">\n");
                    strcat(TmpString, metadata[i].content);
                    strcat(TmpString, "</div>\n");
                }
                strcat(TmpString, "</section>\n");
            }

            // ...  #todo

            // footer
            if ( strncmp( metadata[i].name, "footer", 6) == 0 )
            {
                strcat(TmpString, "<br>\n");
                strcat(TmpString, "<footer>\n");
                if (sizeof(metadata[i].content) < 1028)
                {
                    strcat(TmpString, "<div class=\"gramado-footer\">\n");
                    strcat(TmpString, metadata[i].content);
                    strcat(TmpString, "</div>\n");
                }
                strcat(TmpString, "</footer>\n");
            }
        }
    };

    strcat(TmpString, "</body>\n");
    strcat(TmpString, "</html>\n");

// -----------
// Close::
    write(fd, TmpString, 1027);
    close(fd);

    printf("\n");
    printf("==========================================\n");

    return 0;
fail:
    return (int) -1;
}


// Called by main.c
int viewGenerateOutputHTML(void)
{
    debugShowStat2();
    return 0;
}


