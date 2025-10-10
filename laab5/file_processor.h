#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

typedef enum {
    PROCESS_SUCCESS = 0,                    
    PROCESS_ERROR_OPEN_INPUT,              
    PROCESS_ERROR_OPEN_OUTPUT,             
    PROCESS_ERROR_MEMORY,                  
    PROCESS_ERROR_INVALID_OPERATION        
} ProcessResult;


ProcessResult process_file(const char *input_filename, const char *output_filename, char operation);
ProcessResult remove_digits(const char *input_filename, const char *output_filename);
ProcessResult count_letters_per_line(const char *input_filename, const char *output_filename);
ProcessResult count_special_chars_per_line(const char *input_filename, const char *output_filename);
ProcessResult replace_non_digits_with_hex(const char *input_filename, const char *output_filename);

int is_latin_letter(char c);
int is_arabic_digit(char c);
int is_space(char c);

#endif