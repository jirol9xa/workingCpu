#ifndef TITLE_H
   #define TITLE_H

   
   int makeOneginGreatAgain(FILE* fp, FILE* out);
   int OneginTest();


   #define CHECK_FUNC(arg) {                                              \
      if (arg){                                                            \
      printf("[%s:%d] --- %s failed\n", __func__, __LINE__, #arg);          \
      return 1;                                                              \
      }                                                                       \
   }                                                                           

   #define CHECK_PTR(arg) {                                               \
      if (!arg){                                                           \
      printf("[%s:%d] --- %s failed\n", __func__, __LINE__, #arg);          \
      return 1;                                                              \
      }                                                                       \
   }


   struct Line {
      char* string;
      int length;
   };

   struct Text {
      long file_length;
      int string_amount;
      char* text_buffer;
      Line* text;
   };

   int constructText(FILE *sourse, Text *text);
   int input(FILE* fp,  int* string_amount, char* text_buffer, long file_length);
   int to_strings(char* text_buffer, Line* text, int string_amount);
   int fileLength(long * file_length, FILE* fp);

   int sorting(Line* text, int string_amount);
   int create_new_poem(Line* text, int string_amount);
   int strcmp_reverse(const void* str1, const void* str2);
   int strcmp_direct(void* string1, void* string2);
   int Qsorting(void* Array, int element_amount, size_t element_size, 
                int (*comp)(void* elem1, void* elem2));
   int finish_poem(Text* Onegin);
   int QsortinGG(void* Array, int element_amount, size_t element_size, 
                int (*comp)(void* elem1, void* elem2), char* buffer);

   int output_original(char* text_buffer, int string_amount, FILE* output);
   int output(Line* text, int string_amount, FILE* out);
                                                                           
#endif
