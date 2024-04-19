

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define CONTINUE 1
#define QUIT 0

int main(int argc, char* argv[]) {

  FILE* wx_data = fopen("./weather_data.txt", "r");
  if(!wx_data) {
    printf("Failed to open file!\n");
  }


  char* file_name;
  char* file_loc;

  file_name = argv[1];

  FILE* solar = fopen(file_name, "a");
  if(!solar) {
    printf("Failed to open solar data file for appending!\n");
    exit(EXIT_FAILURE);
  }

  
  fseek(wx_data, 0, SEEK_END);
  unsigned long file_size = ftell(wx_data);

  char ch[100];
  fseek(wx_data, 0, SEEK_SET);

  char test = 0;
  int matches = 0;
  char check_chars[20];
  char* storage;
  storage = (char*)malloc(sizeof(char)*file_size);
  // char solar_rad_data[file_size];
  // char time_data[file_size];
  if(storage == NULL) {
    printf("Failed to allocate memory!");
    exit(EXIT_FAILURE);
  }

  fread(storage, sizeof(char), file_size, wx_data);
  fputs("Date,", solar);
  fputs("Temperature,", solar);
  fputs("Humidity,", solar);
  fputs("Solar Radiation,", solar);
  // fputs("Dew Point,", solar);
  fputs("\n\n", solar);

  // printf("Got here!\n");

  for(unsigned long i = 0; i < file_size; i++) {
    if(storage[i] == 'd' && storage[i+1] == 'a' && storage[i+2] == 't' && storage[i+3] == 'e') {
      int inc = 0;
      while(storage[i+8+inc] != '&') {
        fputc(storage[i+8+inc], solar);
        printf("%c", storage[i+inc]);
        inc++;
      }
      fputc(',', solar);
      // printf("\n");
    }
    // printf("%c", storage[9]);

    if(storage[i] == 't' && storage[i+1] == 'e' && storage[i+2] == 'm' && storage[i+3] == 'p' && storage[i+4] == 'f') {
      int inc = 0;
      while(storage[i+6+inc] != '&') {
        fputc(storage[i+6+inc], solar);
        // printf("%c", storage[i+inc]);
        inc++;
      }
      fputc(',', solar);
      // printf("\n");
    }

    if(storage[i] == 'h' && storage[i+1] == 'u' && storage[i+2] == 'm' && storage[i+3] == 'i' && storage[i+4] == 'd' && storage[i+5] == 'i' && storage[i+6] == 't' &&
       storage[i+7] == 'y' && storage[i+8] == '=') {
      int inc = 0;
      while(storage[i+9+inc] != '&') {
        fputc(storage[i+9+inc], solar);
        // printf("%c", storage[i+inc]);
        inc++;
      }
      fputc(',', solar);
      // fputc('\n', solar);
      // fputc('\n', solar);
    }

    if(storage[i] == 's' && storage[i+1] == 'o' && storage[i+2] == 'l') {
      int inc = 0;
      while(storage[i+15+inc] != '&') {
        fputc(storage[i+15+inc], solar);
        printf("%c", storage[i+inc]);
        inc++;
      }
      // fputc('\n', solar);
      fputc('\n', solar);
      // printf("\n\n");

    }
    printf("%c", storage[i]);
    // fputc('\n', solar);
    // printf("\n\n");
  }

  free(storage);
  fclose(solar);
  fclose(wx_data);

  return 0;
}



