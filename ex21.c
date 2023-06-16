
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

int are_files_identical(char *filename1, char *filename2) {
    FILE *fp1 = fopen(filename1, "r");
    FILE *fp2 = fopen(filename2, "r");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char buffer1[BUFFER_SIZE], buffer2[BUFFER_SIZE];
    int  is_identical = 1;

    while (fgets(buffer1, BUFFER_SIZE, fp1) != NULL && fgets(buffer2, BUFFER_SIZE, fp2) != NULL) {
        if (strcmp(buffer1, buffer2) != 0) {
            is_identical = 0;
            break;
        }
    }

    if (!(is_identical && fgets(buffer1, BUFFER_SIZE, fp1) == NULL && fgets(buffer2, BUFFER_SIZE, fp2) == NULL)) {
        is_identical = 0;
    }

    fclose(fp1);
    fclose(fp2);

    return is_identical;
}

void setToCheck(char* fileName, char* newFileName){
    FILE *input_file, *output_file;
    char c;
    input_file = fopen(fileName, "r");
    output_file = fopen(newFileName, "w");


    if (newFileName == NULL) {
        printf("Error: Could not create output file '%s'\n", newFileName);
        return;
    }

    while ((c = fgetc(input_file)) != EOF) {
        if (!isspace(c)) {
            fputc(tolower(c), output_file);
        }
    }

    fclose(input_file);
    fclose(output_file);

}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s file1 file2\n", argv[0]);
        exit(1);
    }

    int is_identical = are_files_identical(argv[1], argv[2]);
    if (is_identical) {
        return 1;
    }
    else{
        setToCheck(argv[1],"f1_check.txt");
        setToCheck(argv[2],"f2_check.txt");
        is_identical = are_files_identical("f1_check.txt","f2_check.txt") ;
        if (is_identical) {
            return 3;
        }
        else{
            return 2;
        }

    }
}

