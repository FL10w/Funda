#include "func.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

char * obrez(char * string){
    size_t len = strlen(string);
    char *castrt = malloc(len + 1);
    char *buf = malloc(len + 1);
    
    if (!castrt || !buf) {
        free(castrt);
        free(buf);
        return NULL;
    }
    
    size_t i = 79;
    
    if (len <= 80) {
        strcpy(castrt, string);
        i = len;
        while(i > 0 && castrt[i - 1] == ' ') {
            castrt[i - 1] = '\0';
            i--;
        }
        string[0] = '\0';
        free(buf);
        return castrt;
    }
    
    if (i + 1 < len && string[i + 1] == ' ' && string[i] != ' '){
        i++;
    } else {
        while (i > 0 && string[i] != ' '){
            i--;
        }
        
        if (i == 0){
            i = 79;
            while (i < len && string[i] != ' ') {
                i++;
            }
        }
    }
    
    strncpy(castrt, string, i);
    castrt[i] = '\0';
    
    size_t k = 0;
    size_t j = i;
    while (string[j] != '\0') {
       buf[k++] = string[j++];
    }
    
    memset(string, '\0', len); 
    buf[k] = '\0';
    
    if (buf[0] == ' ') {
        k = 1;
    } else {
        k = 0;
    }
    
    j = 0;
    while (buf[k] != '\0') {
        string[j++] = buf[k++];
    }
    string[j] = '\0';
    
    free(buf);
    return castrt;
}   

char * add_probel(char* string) {
    size_t len = strlen(string);
    if (len >= 80) {
        return string;
    }
    
    char *temp = malloc(len + 1);
    if (!temp) return string;
    strcpy(temp, string);
    
    free(string);
    
    if (len >= 80) {
        return temp;
    }
    
    size_t space_count = 0;
    size_t i = 0;
    while (i < len) {
        if (temp[i] == ' ') {
            space_count++;
            while (i < len && temp[i] == ' ') {
                i++;
            }
        } else {
            i++;
        }
    }
    
    if (space_count == 0) {
        char *new_str = realloc(temp, 81);
        if (!new_str) {
            new_str = temp;
        }
        for (i = len; i < 80; i++) {
            new_str[i] = ' ';
        }
        new_str[80] = '\0';
        return new_str;
    }
    
    size_t spaces_to_add = 80 - len;
    char *new_str = malloc(81);
    if (!new_str) {
        return temp;
    }
    
    size_t new_pos = 0;
    size_t added = 0;
    i = 0;
    
    while (i < len && new_pos < 80) {
        if (temp[i] == ' ') {
            while (i < len && temp[i] == ' ') {
                new_str[new_pos++] = ' ';
                i++;
            }
            if (added < spaces_to_add && space_count > 0) {
                size_t to_add = (spaces_to_add - added + space_count - 1) / space_count;
                for (size_t j = 0; j < to_add && new_pos < 80 && added < spaces_to_add; j++) {
                    new_str[new_pos++] = ' ';
                    added++;
                }
                space_count--;
            }
        } else {
            new_str[new_pos++] = temp[i++];
        }
    }
    
    new_str[new_pos] = '\0';
    free(temp);
    return new_str;
}

int same_files(const char *file1, const char *file2) {
    struct stat st1, st2;
    if (stat(file1, &st1) != 0) return STATUS_OK;    
    if (stat(file2, &st2) != 0) return STATUS_OK;    
    
    if ((st1.st_dev == st2.st_dev) && (st1.st_ino == st2.st_ino)) {
        return STATUS_SAME_FILES;
    }
    return STATUS_OK;
}