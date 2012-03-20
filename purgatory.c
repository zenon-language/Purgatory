/**
Copyright (C) 2012, Edward Chernysh
All rights reserved.

This file is part of Zenon. 
Zenon Purger (Purgatory, this header is to be included with external projects, inorder to call
functions from 'purgratory.c'.

This program depends on ZENON and is distributed with it.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the author nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <EDWARD CHERNYSH> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

**/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "purgatory.h"

#ifndef DATA_DECLARATIONS
#define DATA_DECLARATIONS

#ifndef FILEERROR
#define FILEERROR (0)
#endif

#ifndef FOREVER
#define FOREVER (1) // true
#endif

#endif

/* NOTICE:
   The main function is a filler, and is not meant to be used in real-runtime.          
*/

int main(int argc, char *argv[]) {
    if (argc >= 1) {
    short c;
    while (--argc > 0 && (*++argv)[0] == '-')
          c = *++argv[0];
    switch (c) {           
           case 'c': // create
                createPurgatory();
           break;
           case 'e': // evalaute                
                if(!enabled())
                     prompt();                                   
           break;
           case 'h':
                printf("usage:\n");
                printf("-c\t\tCreate Purgatory\n");
                printf("-e\t\tEvaluate [command] (internal)\n");
                printf("-h\t\tShow this list of arguments\n");
                printf("-m\t\tModify Settings <boolean>\n");
                printf("-r\t\tExecute <zenon script-line>\n");
           break;
           case 'm': // modify
                if (argc == 1)                          
                     if (!strcmp(argv[argc - 1], "true") || !strcmp(argv[argc - 1], "false"))
                        replaceID(argv[0]);
           break;
           case 'r':
                #ifdef _WIN32
                       system(strcat("zenon.exe ", argv));
                #elif __APPLE__
                       system(strcat("./zenon.out ", argv));
                #elif __linux__
                       system(strcat("./zenon.out ", argv));
                #endif
           break;
           default:
                   printf("error: '-%c' is not valid.\n", (char)argv[0]);
           break;
           
    };
}
}

int replaceID(char *args) {
    FILE *purgatory = fopen("zenon.purgatory", "r");
    char recipent[strlen(args)], *p;
    short s = 0;
    if (purgatory != FILEERROR)
       while ((recipent[s] = fgetc(purgatory)) != EOF)
             s++;         
       if (recipent[0] == 't' || recipent[0] == 'f') {          
          fclose(purgatory);
          while (FOREVER) {
                purgatory = fopen("zenon.purgatory", "w");
                for (s = 0; s < strlen(args); ++s)
                    fputc(args[s], purgatory);
                fclose(purgatory);
                break;
          }                
       }          
}

void createPurgatory(void) {
    FILE *purgatory = fopen("zenon.purgatory", "w");
    fprintf(purgatory, "false");
    fclose(purgatory);
    mkdir("purgatory");
}

int enabled(void) {
    FILE *purgatory = fopen("zenon.purgatory", "r");     
    char recpt;
    short count = 0;
    while ((recpt = fgetc(purgatory)) != EOF)
          count++;
    char data[count];
    count = 0;
    while ((data[count] = fgetc(purgatory)) != EOF)
          ;
    fclose(purgatory);
    if (data[0] == 't')
       return 1;
    else 
         return 0;    
}

int prompt(void) {    
    printf("\a\a\aWARNING!\nTHIS SCRIPT IS REQUESTING SYSTEM ACCESS.\nFOR YOUR SAFETY THIS SCRIPT HAS BEEN PLACED IN PURGATORY.\nALLOW SYSTEM ACCESS? (Y/N): ");
    char c = getchar();
    if (tolower(c) == 'y')
       return 1;
    else if (tolower(c) == 'n')
       return 0;
    else prompt();    
}
