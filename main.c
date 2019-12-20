/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main()
{

    int f1[2];  // Used to store two ends of first pipe 

    int f2[2];  // Used to store two ends of second pipe 

  

    char fixed_str[] = " the sum of even digits in the input number :"; 
    int input_str[100]; 
    pid_t p; 

  

    if (pipe(f1)==-1) 
    { 

        fprintf(stderr, "Pipe Failed" ); 
        return 1; 

    } 

    if (pipe(f2)==-1) 
    { 

        fprintf(stderr, "Pipe Failed" ); 
        return 1; 

    } 
    scanf("%s", input_str); 
    p = fork(); 
    if (p < 0) 
    { 

        fprintf(stderr, "fork Failed" ); 
        return 1; 

    } 

    // Parent process 

    else if (p > 0) 
    { 

        char concat_str[100]; 
        close(f1[0]);  // Close reading end of first pipe 

        // Write input string and close writing end of first 

        // pipe. 

        write(f1[1], input_str, strlen(input_str)+1); 
        close(f1[1]); 

        // Wait for child to send a string 

        wait(NULL); 

        close(f2[1]); // Close writing end of second pipe 

  
        // Read string from child, print it and close 

        // reading end. 

        read(f2[0], concat_str, 100); 
        printf( concat_str); ////////,"%d"
        close(f2[0]); 

    } 

  

    // child process 

    else
    { 

        close(f1[1]);  // Close writing end of first pipe 

        // Read a string using first pipe 

        char concat_str[100]; 
        read(f1[0], concat_str, 100); 

  

        // Concatenate a fixed string with it 

        int k = strlen(concat_str); 
        int i; 
        for (i=0; i<strlen(fixed_str); i++) 

            concat_str[k++] = fixed_str[i]; 

        concat_str[k] = '\0';   // string ends with '\0' 

  

        // Close both reading ends 

        close(f1[0]); 
        close(f2[0]); 

  

        // Write concatenated string and close writing end 

        write(f2[1], concat_str, strlen(concat_str)+1); 
        close(f2[1]); 

  
        exit(0); 

    } 
}
