#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#define SIZE 150
int handleStudent(char* directory, char* input_path, int errors_fd, char* cor_output_path, char* comp_path);
int compileFile(char* directory,int errors);
int runCode(int errors_fd, int input_fd, char* cor_output_path, char* comp_path);
void writeGrades(int number,char* name,int results_fd);
void alarm_handler (int s);
int main(int argc, char *argv[]) {

    int argFile = open(argv[1], O_RDONLY);
    if (argFile == -1) {
        perror("Error in: open");
        exit(-1);
    }
    char fileContent[SIZE*3];
    if(read(argFile,fileContent,SIZE*3)<0){
        perror("Error in: read");
        exit(-1);
    }
    char currentPath[SIZE];
    char full_output_path[SIZE];
    char full_input_path[SIZE];
    char full_comp_path[SIZE];
    if (getcwd(currentPath, sizeof(currentPath)) != NULL) {
        //printf("Current working directory: %s\n", currentPath);
    } else {
        perror("Error in: getcwd");
        exit(-1);
    }

    char folder[150], input[150], correctOutput[150];
    strcpy( folder,strtok(fileContent, "\n"));
    strcpy( input,strtok(NULL, "\n"));
    strcpy( correctOutput,strtok(NULL, "\n"));
    // if the path is relative, make it absolute path
    strcpy(full_comp_path,currentPath);
    if (input[0] != '/') {
        strcpy(full_input_path,currentPath);
        strcat(full_input_path,"/");
        strcat(full_input_path,input);
    }
    else {
        strcpy(full_input_path,input);
    }
    if (correctOutput[0] != '/') {
        strcpy(full_output_path,currentPath);
        strcat(full_output_path,"/");
        strcat(full_output_path,correctOutput);
    }
    else {
        strcpy(full_output_path,correctOutput);
    }

    strcat(full_comp_path, "/comp.out"); //need this later to run my code

    int errors = open("errors.txt", O_WRONLY | O_TRUNC | O_CREAT, 0666);
    if (errors < 0) {
        perror("Error in: open");
        exit(-1);
    }
    int results_fd = open("results.csv", O_WRONLY | O_APPEND|O_CREAT, 0666);
    if (chdir(folder) == -1) { // change directory to the first line of the file
        perror("Error in: chdir"); // print error message if chdir fails
        exit(-1);
    }
    DIR* dir = opendir(".");
    if (dir == NULL) {
        exit(-1);
    }
    struct dirent* entry;
    int grade_type;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            // Exclude the current directory (".") and parent directory ("..")
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                // take care of the current student
                grade_type=handleStudent(entry->d_name, full_input_path, errors, full_output_path, full_comp_path);
                writeGrades(grade_type,entry->d_name,results_fd);
            }
        }
    }
    closedir(dir);
    close(results_fd);
    close(errors);
}


int handleStudent(char* directory,char* input_path,int errors_fd,  char* cor_output_path, char* comp_path){
    int studentGrade=1;
    studentGrade=compileFile(directory, errors_fd); //compile the c file
    if(studentGrade<=2){
        chdir("..");
        return studentGrade;
    }
    int input_fd = open(input_path, O_RDONLY);
    if (input_fd < 0) {
        perror("Error in: open");
        exit(-1);
    }
    studentGrade=runCode(errors_fd,input_fd,cor_output_path, comp_path); //run the c file
    //printf("the grade is %d\n",studentGrade);
    close(input_fd);
    remove("a.out");
    remove("output.txt");
    chdir("..");
    return studentGrade;

}
void alarm_handler (int s) {}
int runCode(int errors_fd, int input_fd, char* cor_output_path, char* comp_path){
    int output_fd = open("output.txt", O_WRONLY | O_TRUNC | O_CREAT, 0666);
    if (output_fd < 0) {
        perror("Error in: open");
        return(-1);
    }
    pid_t pid = fork();

    if (pid == -1) {
        return -1;
    }
    else if (pid == 0) {
        // Child process
        dup2(errors_fd, 2);
        dup2(output_fd, 1);
        dup2(input_fd, 0);
        signal(SIGALRM, alarm_handler);
        alarm(5);
        //run the code
        execvp("./a.out", (char*[]){"./a.out", NULL});
        exit(-1);
    }
    else {
        // Parent process
        int status;
        wait(&status);
        if (WIFSIGNALED(status)){
           // printf("bling bling alaram was set\n");
            return 3;
        }
    }
    char output_path[SIZE];
    getcwd(output_path, sizeof(output_path));
    strcat(output_path, "/output.txt"); //need this later to run my code
    pid = fork();
    if (pid == -1) {
        return 0;
    }
    else if (pid == 0) {
        // Child process
        //printf("i compile %s\n",comp_path);
        dup2(errors_fd, 2);
        //run the code
        execvp(comp_path, (char*[]){comp_path,cor_output_path,output_path,NULL});
        exit(-1);
    }
    else {
        // Parent process
        int status;
        wait(&status);


        int ret_value=WEXITSTATUS(status);
        //printf("the return value is %d\n",ret_value);
        if(ret_value==2){ //files are different
            return 4;
        }
        if(ret_value==3){ //files are similar
            return 5;
        }
        if(ret_value==1){ //files are equal
            return 6;
        }
    }


}

int compileFile(char* directory,int errors){
    //printf("i am in this  directory: %s\n", directory);
    DIR *dir;
    int file_count=0;
    char file_name[SIZE] ;
    struct dirent *entry;
    if (chdir(directory) == -1) { // change directory to the first line of the file
        perror("Error in: chdir"); // print error message if chdir fails
        return 0; // return failure
    }
    // Open the directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Error:in open");
        return 0;
    }

    // Loop through directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Check if the entry is a file and ends with ".c"
        if (entry->d_type == DT_REG && strstr(entry->d_name, ".c") != NULL && strcmp(strrchr(entry->d_name, '.'), ".c") == 0) {
            file_count++;
            strcpy(file_name, entry->d_name);
            break;
        }
    }
    if (file_count == 0) {
        return 1;
    }
    char *gcc_args[] = {"gcc", file_name, NULL};
    // Execute the GCC command
    pid_t pid = fork();

    if (pid == -1) {
        return 0;
    }
    else if (pid == 0) {
        // Child process
        dup2(errors, 2);
        execvp("gcc", gcc_args);
        exit(-1);
    }
    else {
        // Parent process
        int status;
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {
            return 3;
        }
        else {
            return 2;
        }
    }
}

void writeGrades(int number, char* name, int results_fd){
    char* message;

    switch (number) {
        case 1:
            message = ",0,NO_C_FILE\n";
            //printf("NO_C_FILE\n");
            break;
        case 2:
            //printf("COMPILATION_ERROR\n");
            message = ",10,COMPILATION_ERROR\n";
            break;
        case 3:
            //printf(",20,TIMEOUT\n");
            message = ",20,TIMEOUT\n";
            break;
        case 4:
            //printf("WRONG\n");
            message = ",50,WRONG\n";
            break;
        case 5:
            //printf("SIMILAR 5\n");
            message = ",75,SIMILAR\n";
            break;
        case 6:
            //printf("EXCELLENT\n");
            message = ",100,EXCELLENT\n";
            break;
    }
    char resultToAdd [SIZE] ;
    strcpy(resultToAdd,name);
    strcat(resultToAdd, message);

    int resultLen = strlen(resultToAdd);
    write(results_fd, resultToAdd, resultLen) ;
}


