#ifndef TEXTLIB_H
   #define TEXTLIB_H

    #if DEBUG_LVL > 0

        #define CHECK_FUNC(arg)                                                       \
        {                                                                              \
            if (arg){                                                                   \
            LOGSPRINT("[%s:%d] --- %s failed\n", __func__, __LINE__, #arg);   \
            return 1;                                                                     \
            }                                                                              \
        }

        #define CHECK_PTR(arg) {                                                               \
            if (!(arg)) {                                                                       \
                LOGSPRINT("[%s:%d] --- %s failed\n\n\n", __func__, __LINE__, #arg);   \
                return 1;                                                                         \
            }                                                                                      \
        }                                                                           
    #else
        #define CHECK_PTR(arg) ;
        #define CHECK_FUNC(arg) arg

    #endif
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


    static int constructText(FILE *sourse, Text *text);
    static int input(FILE* fp, int *string_amount, char *text_buffer, long file_length);
    static int to_strings(char *text_buffer, Line *text, int string_amount);
    static int fileLength(long *file_length, FILE *fp);
    static int output(Line *text, int string_amount, FILE *out);
    static int skipSpace(char *string);
    static int finish_text(Text* Onegin);


    static int constructText(FILE *sourse, Text *text)
    {
        CHECK_FUNC(fileLength(&(text->file_length), sourse));

        text->text_buffer = (char *) calloc(text->file_length + 1, sizeof(char));
        CHECK_PTR(text->text_buffer);

        input(sourse, &(text->string_amount), text->text_buffer, text->file_length);    
        text->text = (Line*) calloc(text->string_amount, sizeof(Line)); 

        CHECK_PTR(text->text);

        CHECK_FUNC(to_strings(text->text_buffer, text->text, text->string_amount));
    }


    /*!
    \brief   Функция ввода текста из файла
    \param   [FILE*] fp указатель на файл, из которого считывается текст
    \param   [int*] string_amount указатель на число строк в тексте
    \param   [char*] text_buffer Буфер. хранящий весь текст целиком
    \param   [long ing] file_length Общее количество символов в файле
    \return  0 если функция завершилась успешно,
             1 в случае ошибки
    \details Функция считывает текст из файла, записывая значения 
             числа строк и общего числа символов.
    \details Функция возвращает указатель на массив с текстом.
    */
    static int input(FILE* fp, int* string_amount, char* text_buffer, long file_length) 
    {
        CHECK_PTR(fp);
        CHECK_PTR(string_amount);
        CHECK_PTR(text_buffer);

        fread(text_buffer, sizeof(char), file_length, fp);
        text_buffer[file_length] = '\0';

        for (int i = 0; i < file_length; i++) {
            if (text_buffer[i] == '\n') {
                (*string_amount)++;
            }
        }

        return 0;
    }


    /*!
    \brief   Функция вывода текста
    \param   [Text*] text Массив, хранящий отсортированный текст построчно
    \param   [int] string_amount Число строк в массиве
    \param   [FILE*] out Указатель на файл, куда будет
             происходить печать текста
    \return  0 если функция завершилась успешно,
             1 в случае ошибки
    \details Функция выыодит отсортированный текст построчно.
    */
    static int output(Line* text, int string_amount, FILE* out) 
    {
        CHECK_PTR(text);
        CHECK_PTR(out);

        for (int i = 0; i < string_amount; i++) {
            fprintf(out, "%s" "\n", text[i].string);
        }

        return 0;
    }


    /*!
    \brief   Функция преобразование массива текст в двумерный
    \param   [char*] text_buffer Массив всех символов текста
    \param   [Text*] text Двумерный массив, хранящий текст построчно
    \param   [int] string_amount Общее число строк в тексте
    \return  0 если функция завершилась успешно,
             1 в случае ошибки
    \details Данная функция разбивает массив с текстом на 
             строки для дальнейшей сортировки
    */
    static int to_strings(char *text_buffer, Line *text, int string_amount) 
    {
        CHECK_PTR(text_buffer);
        CHECK_PTR(text);

        for (int i = 0; i < string_amount; i++) {

            text[i].string = text_buffer;  

            while (*text_buffer != '\n' && *text_buffer != '\0') {
                text_buffer++;
            }

            (*text_buffer) = '\0';
            text[i].length = strlen(text[i].string);
            text_buffer++;   
        }

        return 0;
    }


    /*!
    \brief  Функция измерения длины файла
    \param  [long int*] file_length Переменная, 
            куда будет записана длина файла
    \param  [FILE*] fp Указатель на файл, длину 
            которого надо узнать
    \return 0 если функция завершилась успешно,
            1 в случае ошибки
    */
    static int fileLength(long *file_length, FILE *fp) 
    {
        CHECK_PTR(file_length);
        CHECK_PTR(fp);

        CHECK_FUNC(fseek(fp, 0L, SEEK_END));

        *file_length = ftell(fp);
        CHECK_PTR(*file_length);

        CHECK_FUNC(fseek(fp, 0L, SEEK_SET));

        return 0;
    }


    /*!
    \brief Функция очистки памяти
    */
    static int finish_text(Text *Onegin) 
    {
        CHECK_PTR(Onegin)

        free(Onegin->text_buffer);
        free(Onegin->text);

        return 0;
    }


    /*!
    \brief  Функция пропуска пробелов в строке
    \param  [char *]string Строка, в которой
            необходимо пропустить пробелы
    \return Количество пробелов в строке до
            первого непробельного символа 
    */
    static int skipSpace(char *string)
    {
        int space_amount = 0;
        for (int i = 0; i < strlen(string) && string[i] == ' '; i++)
        {
            space_amount ++;
        }

        return space_amount;
    }


#endif