#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int DEF_BUF_SIZE = 8;
int history[4] = { 100, 42, -42, 33 };

int read_from_file(char *);

int main (int argc, char **argv){
  int hflag = 0;
  int iflag = 0;
  int pflag = 0;
  char stack_buffer[11];
  char* heap_buffer = malloc(11);
  char* file_input = NULL;
  char* user_input = NULL;
  int index;
  int c;
  int heap_mode = 0;
  int stack_mode = 0;
  int hist_index = 0;

  opterr = 0;
  while ((c = getopt (argc, argv, "hi:f:p:")) != -1)
    switch (c){
      case 'h': hflag = 1; break;
      // case 'i': iflag = 1; user_input = optarg; break;
      case 'f': file_input = optarg; break;
      // case 'p': pflag = 1; hist_index = atoi(optarg); break;
      case '?':
        // if (optopt == 'i')
        //   fprintf (stderr, "Option -%c requires an input argument\n", optopt);
        else if (optopt == 'f')
          fprintf (stderr, "Option -%c requires input file\n", optopt);
        // else if (optopt == 'p')
        //   fprintf (stderr, "Option -%c requires history index num\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        return 1;
      default:
        abort ();
    }

  for (index = optind; index < argc; index++){
    printf ("Non-option argument %s\n", argv[index]);
    if(!strcmp(argv[index], "stack")){
      printf("You found the super secret stack mode!\n");
      stack_mode = 1;
    }
    if(!strcmp(argv[index], "heap")){
      printf("You found the super secret heap mode!\n");
      heap_mode = 1;
    }
  }

  if(hflag){
      printf("Helptext: ");
      printf("One can use one of the following options:\n");
      printf("-h\t\tshow this help text\n");
      printf("-i\t\tdo calc based on a given number\n");
      printf("-f <file>\tdo calc based on a file input\n");
      printf("-p {prev} \tdo calc based on previous input\n");
      printf("???\t\tmore options always still under development\n");    
      return 0;
    }
  
  // BUG: stack overflow if file contains to long string
  if(stack_mode && file_input){
    printf("(secret) strcpy buffer code :X\n");
    FILE *fp;
    fp = fopen(file_input,"r"); 
    if(fp == NULL){ perror("Error: "); exit(EXIT_FAILURE); }
    
    char line[1024]; 
    if(strlen(fgets(line, sizeof(line), fp)) > 0){
      printf("copy %lu bytes to stack\n",strlen(line));
      strcpy(stack_buffer, line); 
    }
    return 0;
  }

  // BUG: heap overflow if file contains to long string
  if(heap_mode && file_input){    
    printf("strcpy file on heap :X\n");
    FILE *fp;
    fp = fopen(file_input,"r"); // read file
    if(fp == NULL){ perror("Error: "); exit(EXIT_FAILURE); }
    
    char line[1024]; 
    if(strlen(fgets(line, sizeof(line), fp)) > 0){
      printf("copy %lu bytes to stack\n",strlen(line));
      strcpy(stack_buffer, line);  // BUG: BUFFER OVERFLOW (SEGFAULT)
    }
    strcpy(heap_buffer, line);     // BUG: HEAP OVERFLOW
    return 0;
  }

  // BUG when index = 2, Found by klee (fast)
  // BUG when index out of bounds, Found by klee (fast)
  if(pflag){
    printf("Do calc based on history[%d]: %d\n", hist_index, history[hist_index]);
    int saved_value = history[hist_index]; // BUG: OUT OF BOUND INDEX SEGFAULT
    float a = (100 / (42+saved_value));
    printf("magic(%d) = %f \n",saved_value, a);
    return 0;
  }

  // BUG when file_value == user_value
  if(iflag && file_input){
    printf("calculation based on file and user input :) \n");
    int user_value = atof(user_input);
    int file_value = read_from_file(file_input);
    float a = (100 / (user_value - file_value));  
    printf("magic(%d,%d) = %f \n",user_value, file_value, a);
    return 0;
  }

  // BUG when user input = 42, found by klee (fast)
  if(iflag){
    printf("Calculating with user input: %s\n",user_input);
    int user_value = atoi(user_input);
    float a = (100/(42-user_value));
    printf("f(%d) = %f \n",user_value, a);
    return 0;
  }

  // BUG when file_value = 42, Found by klee (midtime)
  if(file_input){
    printf("super safe file read and calculate\n");
    int user_value = read_from_file(file_input);
    printf("calculate with value: %d \n",user_value);
    float a = (100/(42-user_value));
    printf("f(%d) = %f \n",user_value, a);
    return 0;
  }

  return 0;
}

// safe read from file
int read_from_file(char * file_input){
  FILE *fp;
  fp = fopen(file_input,"r"); // read file
  if(fp == NULL){ 
    perror("Error: "); exit(EXIT_FAILURE);
  }
 
  // maxint = 2147483647
  char buffer[11];
  if(!fgets(buffer, sizeof(buffer), fp)){
    printf("nothing to read\n");
    exit(EXIT_FAILURE);
  }
  buffer[10] = '\x00';

  return atoi(buffer);
}

