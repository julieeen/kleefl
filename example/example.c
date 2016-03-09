#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int buffer[256];

void init_buffer(){
  int i;
  for (i = 0; i < 256; ++i){
    buffer[i] = i;
  }
}

int processing_data(char * filename) {

  char stack_buffer[32];
  char* heap_buffer = malloc(32);

  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(filename, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // processing lines in file
  while ((read = getline(&line, &len, fp)) != -1) {
    //printf("parsing line of length %zu :", read);
    printf("read> %s", line);

    // skip short lines
    if(read < 5)
      continue;

    // BUG: BUFFER OVERFLOW // DETECTED BY Klee->AFL setup
    // line starts with "stack", load rest of line to stack_buff
    if(!strncmp(line,"stack",5)){
      //printf("found mem load marker\n");
      char copy[read-5];
      strncpy(copy, line+5, strlen(line)-1);
      strcpy(stack_buffer, copy);
      printf("load to stack: %s", stack_buffer);
      continue;
    }

    // BUG: DIV BY ZERO             
    // line starts with "value"
    if(!strncmp(line,"value",5)){
      //printf("found mem load marker\n");
      char copy[read-5];
      strncpy(copy, line+5, strlen(line)-1);
      int value = atoi(copy);
      float a = (100/(42-value));
      printf("\ncalc 100/(42-%d) \n",value);        // found by KLEE (and AFL)
      printf("= %f\n",a);
      continue;
    }

    // BUG: OUT OF BOUNDS READ
    // found by AFL
    if(!strncmp(line,"buffr",5)){
      //printf("found mem load marker\n");
      init_buffer();
      char copy[read-5];
      strncpy(copy, line+5, strlen(line)-1);
      int value = atoi(copy);
      printf("\nread value from buffer[%d]\n",value);
      printf("= %d\n",buffer[value]);

      printf("\ncalc 100/(42-buffer[%d]) \n", buffer[value]);
      float a = (100/(42-buffer[value]));
      printf("= %f\n",a);
      continue;
    }

  }

  return 0;
} 

int main (int argc, char **argv){
  int hflag = 0;
  char* file_input = NULL;
  int index;
  int c;
  int heap_mode = 0;
  int stack_mode = 0;

  opterr = 0;
  while ((c = getopt (argc, argv, "hf:")) != -1)
    switch (c){
      case 'h': hflag = 1; break;
      case 'f': file_input = optarg; break;
      case '?':
        if (optopt == 'f')
          fprintf (stderr, "Option -%c requires input file\n", optopt);
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
    // here you can find an official not suported option \o/
    if(!strcmp(argv[index], "secret_mode")){
      printf("You found the super secret mode!\n");
      return 0;
    }
  }

  if(hflag){
      printf("Helptext: ");
      printf("One can use one of the following options:\n");
      printf("-h\t\tshow this help text\n");
      printf("-f <file>\tdo calc based on a file input\n");
      printf("???\t\tmore options still under development\n");    
      return 0;
    }
  
  if(file_input){
    processing_data(file_input);
    return 0;
  }

  return 0;
}


