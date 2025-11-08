#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

int main(void)  
{
    char filein_name[BUFFER_SIZE];
    char fileout_name[BUFFER_SIZE];
    
    if (fgets(filein_name, BUFFER_SIZE, stdin) == NULL || 
        fgets(fileout_name, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "error: cant read\n");
        return -1;
    }
    
    filein_name[strcspn(filein_name, "\n")] = '\0';
    fileout_name[strcspn(fileout_name, "\n")] = '\0';
    
    if (strcmp(filein_name, fileout_name) == 0 || 
        same_files(filein_name, fileout_name) == STATUS_SAME_FILES) {
        fprintf(stderr, "error: same files\n");
        return -1;
    }
    
    FILE * filein = fopen(filein_name, "r");
    FILE * fileout = fopen(fileout_name, "w");
    
    if (!filein || !fileout){
        if (filein) fclose(filein);
        if (fileout) fclose(fileout);
        fprintf(stderr, "error: cant open the file\n");
        return -1;
    }
    
    char buf[BUFFER_SIZE];
    
    while (fgets(buf, BUFFER_SIZE, filein) != NULL) {
        buf[strcspn(buf, "\n")] = '\0';
        
        int start = 0;
        while (buf[start] && isspace(buf[start])) {
            start++;
        }
        
        if (buf[start] == '\0') {
            fprintf(fileout, "\n");
            continue;
        }
        
        char *trimmed = buf + start;
        int buf_len = strlen(trimmed);
        
        if (buf_len <= 80) {
            fprintf(fileout, "%s\n", trimmed);
            continue;
        }
        
        
        char *work_buf = malloc(strlen(trimmed) + 1);
        if (!work_buf) continue;
        strcpy(work_buf, trimmed);
        
        while (strlen(work_buf) > 0) {
            char *cur = obrez(work_buf);
            if (!cur) break;
            
            cur = add_probel(cur);
            
            fprintf(fileout, "%s\n", cur);
            free(cur);
        }
        
        free(work_buf);
    }
    
    fclose(filein);
    fclose(fileout);
    
    return 0;
}