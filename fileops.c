#include <stdio.h>
#define MAX_LENGTH 100

int main(void){
    char *file_input = "input.txt";
    char *file_output = "output.txt";
    FILE *input_stream = fopen(file_input, "r");
    FILE *output_stream = fopen(file_output, "w");
    char file_line[MAX_LENGTH];
    while(fgets(file_line, sizeof(file_line), input_stream) != NULL){
        printf("Next line: %s", file_line);
        fputs(file_line, output_stream);
    }
    fclose(input_stream);
    fclose(output_stream);
}