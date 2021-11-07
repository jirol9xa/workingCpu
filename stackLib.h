#ifndef STACKLIB_H
        #define STACKLIB_H

        const type_t POISON = 0xDEAD; 

        /*
                            +--> code, при DEBUG_LVL > 1
                            |
        is_debug(code) -----+
                            |
                            +--> `пустота`, при !(DEBUG_LVL > 1)
        */

        #if DEBUG_LVL > 0
            #define is_debug_lvl_0(code) code
        #else
            #define is_debug_lvl_0(code) ;
        #endif

        #if DEBUG_LVL > 1
            #define is_debug_lvl_1(code) code
        #else
            #define is_debug_lvl_1(code) ;
        #endif

        #ifndef DEBUG
            #define DEBUG

            #define FUNC_REPORT(func, stack)  func;
            
            enum Error {
                    OK = 0, 
                    ERR_CALLING_FUNC_FAILED        =         1,
                    ERR_STACK_ALREARY_CREATED      =    1 << 1,
                    ERR_EMPTY_ELEM_ISNT_POISONED   =    1 << 2,
                    ERR_SIZE_GREATER_CAPACITY      =    1 << 3,
                    ERR_POP_EMPTY_STACK            =    1 << 4,
                    ERR_RIGHT_CANARY_DAMAGED       =    1 << 5,
                    ERR_LEFT_CANARY_DAMAGED        =    1 << 6,
                    ERR_WRONG_HASH                 =    1 << 7,
                    ERR_INVALID_PTR                =    1 << 8,
                    ERR_REALLOC_FAILED             =    1 << 9,
                    ERR_PUSH_FAILED                =    1 << 10,
                    ERR_STACK_ALREADY_CLEANED      =    1 << 11,
                    ERR_LEFT_DATACANARY_DAMAGED    =    1 << 12,
                    ERR_RIGHT_DATACANARY_DAMAGED   =    1 << 13,
                    ERR_RESIZE_FAILED              =    1 << 14,
                    ERR_POP_FAILED                 =    1 << 15,
                    ERR_DUMP_FAILED                =    1 << 16,
                    ERR_STACK_BROKEN               =    1 << 17,
                    EMPTY_STACK                    =    1 << 18
                };

            #if (DEBUG_LVL > 0)
                #define STACK_CREATION_INFO(stack) {                                                                  \
                    LOGSPRINT("Stack \"%s\" was created in function \"%s\" on line %d."                           \
                    "Adress %p with addrreess of data: %p\n\n\n", #stack, __PRETTY_FUNCTION__, __LINE__,              \
                    stack, stack->data);                                                                              \
                }

                #define STACK_DUMP(stack) {                                                                           \
                    verifyStack(stack);                                                                               \
                    stackDump(stack, __func__, #stack);                                                               \
                }   


                #define CHECK_PTR(arg) {                                                                              \
                    if (!(arg)) {                                                                                     \
                        LOGSPRINT("[%s:%d] --- %s failed\n\n\n", __func__, __LINE__, #arg);                       \
                        return ERR_INVALID_PTR;                                                                       \
                    }                                                                                                 \
                }

                #define ASSERT_OK(stack) {                                                                            \
                    if ((stack->status & EMPTY_STACK == 0) && (stack->status & OK != 0)) return ERR_STACK_BROKEN;     \
                }

                #define FUNC_REPORT(func, stack) {                                                                    \
                    int status = (int) func;                                                                          \
                    if (status) {                                                                                     \
                        LOGSPRINT("########################################################################\n"    \
                                    "function \"%s\" was failed with error code:\n", #func);                          \
                        printError(status);                                                                           \
                        LOGSPRINT("\nStack is:\n");                                                               \
                        STACK_DUMP(stack)                                                                             \
                        LOGSPRINT("########################################################################\n\n");\
                    }                                                                                                 \
                }

                #define CANARY(stack) (0xFEE1DEAD^((u_int64_t) stack))

                #define LEFT_CANARY(stack) ((char*) stack->data - sizeof(u_int64_t))

                #define RIGHT_CANARY(stack) ((char*) stack->data + stack->capacity * sizeof(type_t))
            #endif

        #endif

        struct Stack
        {
            is_debug_lvl_1(u_int64_t egg);
            type_t* data;
            int size;
            int capacity;
            is_debug_lvl_0(
                int status;
                is_debug_lvl_1(u_int64_t hash);
                is_debug_lvl_1(u_int64_t chicken);  
            ) 
        };

        /*!
            \brief  Функция создания стека
            \param  [Stack*]stk Указатель на стек
            \param  [int]capacity Емкость стека
            \return 0 или код ошибки
        */
        static int stackCtor(Stack* stk, int capacity);

        /*!
            \brief  Функция уничтожения стека
            \param  [Stack*]stk Указатель на стек
            \return 0 или код ошибки
        */
        static int stackDtor(Stack* stk);

        /*!
            \brief  Функция добавления элемента в стек
            \param  [Stack*]stk Указатель на стек
            \param  [type_t_t]value Значение добавляемого
                    элемента
            \return 0 или код ошибки
        */
        static int stackPush(Stack* stk, type_t value);

        /*!
            \brief  Функция извлечения элемента
            \param  [Stack*]stk Указатель на стек
            \param  [type_t_t*]param Указатель, куда
                    должен быть извлечен элемент
            \return 0 или код ошибки
        */
        static type_t stackPop(Stack* stk, type_t* param);

        /*!
            \brief  Функция вывода информации о
                    стеке и функции, которая его
                    вызвала
        */
        static void stackDump(const Stack* stk, const char* func_name, const char* stack_name);

        /*!
            \brief  Функция проверки стека на
                    корректность
        */
        static void verifyStack(Stack* stk);

        /*!
            \brief  Функция печати ошибок
        */
        static void printError(int Error);



        /*!
        \brief  Функция изменения емкости стека
        \param  [Stack*]stk Указатель на стек
        \param  [int]upper 1, если требуется
                увеличить емкость, 0 -- если
                нужно уменьшить емкость
        \return 0 или код ошибки
    */
    static int stackResize(Stack* stk, int upper);

    /*!
        \brief  Функция копирования памяти
        \param  [void*]destination Место,
                куда надо записать данные
        \param  [void*]sourse Место, откуда
                надо взять данные
        \param  [int]element_siez размер
                элемента
        \return 0 или код ошибки
    */
    static int MemCpy(void* destination, void* sourse, int element_size);

    /*!
        \brief  Функция подсчета хеша
        \param  [Stack*]stk Указатель на стек
        \return 0 или код ошибки
    */
    static unsigned int hashCalc(Stack* stk);

    /*!
        \brief  Функция посчет хеша по 
                алгоритму MurmurHash2
    */
    static unsigned int MurmurHash2(char* key, unsigned int len);

    /*!
        \brief  Функция установки левой или
                правой канарейки для data
        \param  [Stack*]stk Указатель на стек
        \param  [int]is_left 1, если надо 
                установить левую канарейку,
                !1 -- если правую
    */
    static void setCanary(Stack* stk, int is_left);


    int stackCtor(Stack* stk, int capacity) 
    {   
        is_debug_lvl_0(CHECK_PTR(stk));

        stk->capacity = (int) pow(2, (int) (log(capacity) / log(2)) + 1 );
        stk->data = (type_t*) calloc (1 , sizeof(type_t) * stk->capacity);

        is_debug_lvl_1(
            void* temp_ptr = realloc(stk->data, sizeof(type_t) * stk->capacity + 2 * sizeof(u_int64_t));
            if (temp_ptr == nullptr) {
                return ERR_REALLOC_FAILED;
            }

            stk->data = (type_t*) ((char*) temp_ptr + sizeof(u_int64_t));
            stk->egg     = CANARY(stk);
            stk->chicken = CANARY(stk);

            setCanary(stk, 1);
            setCanary(stk, 0);
        )

        for (int i = 0; i < stk->capacity; i++) {
            stk->data[i] = POISON;
        }

        is_debug_lvl_1( if (hashCalc(stk) == ERR_INVALID_PTR) return ERR_INVALID_PTR );

        is_debug_lvl_0(
            STACK_CREATION_INFO(stk)
            stk->status = EMPTY_STACK;
            STACK_DUMP(stk)
        )

        return 0;
    }


    int stackDtor(Stack* stk) 
    {
        is_debug_lvl_0(
            CHECK_PTR(stk)
            STACK_DUMP(stk)
            ASSERT_OK(stk)
        )

        stk->capacity = 0;
        stk->size = 0;

        is_debug_lvl_1(free(LEFT_CANARY(stk)));

        #if DEBUG_LVL <= 1 
            free(stk->data);
        #endif
        stk->data = (type_t*) 0xBEBE;
        return 0;
    }


    int stackPush(Stack* stk, type_t value) 
    {
        is_debug_lvl_0(
            CHECK_PTR(stk)
            STACK_DUMP(stk)
            ASSERT_OK(stk)
        )

        if (stk->size + 1 > stk->capacity) {
            if (stackResize(stk, 1) == ERR_RESIZE_FAILED) {
                is_debug_lvl_0(
                LOGSPRINT("Error in %s on %d line: not enough memory for stack\n\n\n", __FUNCTION__, __LINE__);
                )

                return ERR_PUSH_FAILED;
            }
        }

        stk->size ++;

        MemCpy((char*) &stk->data[stk->size - 1], &value, sizeof(type_t));

        is_debug_lvl_1(
            if (hashCalc(stk) == ERR_INVALID_PTR) return ERR_PUSH_FAILED;
        )

        is_debug_lvl_0(
            STACK_DUMP(stk);
        )
            
        return 0;
    }


    static int stackResize(Stack* stk, int upper) 
    {
        is_debug_lvl_0(CHECK_PTR(stk)
                    STACK_DUMP(stk)
                    ASSERT_OK(stk)
        )

        if (upper) {
            void* temp_ptr = nullptr;
            if (stk->capacity == 0) {
                stk->capacity = 1;
                
                #if DEBUG_LVL < 1
                    temp_ptr = realloc(stk->data, sizeof(type_t));
                #endif
                is_debug_lvl_1(temp_ptr = realloc(LEFT_CANARY(stk), sizeof(type_t) + sizeof(u_int64_t) * 2 ));

                if (temp_ptr != nullptr) {
                    stk->data = (type_t*) ((char*)temp_ptr + sizeof(u_int64_t));

                    is_debug_lvl_1(
                        setCanary(stk, 1);
                        setCanary(stk, 0);   
                    )
                    for (int i = stk->size; i < stk->capacity; i++) {
                        stk->data[i] = POISON;
                    }
                    is_debug_lvl_0(stk->status &= !EMPTY_STACK);
                    is_debug_lvl_1(hashCalc(stk));
                    is_debug_lvl_0(STACK_DUMP(stk));
                    return 0;
                }
                else {

                    is_debug_lvl_0(STACK_DUMP(stk));
                    
                    return ERR_RESIZE_FAILED;
                }
            }
            
            #if DEBUG_LVL < 1
                temp_ptr = realloc(stk->data, sizeof(type_t) * 2 * stk->capacity);
            #endif
            is_debug_lvl_1(temp_ptr = realloc(LEFT_CANARY(stk), sizeof(type_t) * 2 * stk->capacity  + sizeof(u_int64_t) * 2));

            if (temp_ptr != nullptr) {
                stk->capacity *= 2;
                is_debug_lvl_1(stk->data = (type_t*) ((char*) temp_ptr + sizeof(u_int64_t)));

                is_debug_lvl_1(
                    setCanary(stk, 0);
                )
                    
                for (int i = stk->size; i < stk->capacity; i++) {
                    stk->data[i] = POISON;
                }

                is_debug_lvl_1(
                    if (hashCalc(stk) == ERR_INVALID_PTR) return ERR_INVALID_PTR;
                )
                is_debug_lvl_0(STACK_DUMP(stk));

                return 0;
            }
            else {
                is_debug_lvl_0(STACK_DUMP(stk));
                
                return ERR_RESIZE_FAILED;
            }
        }
        else {
            is_debug_lvl_1(
                realloc(LEFT_CANARY(stk), sizeof(type_t) * (stk->capacity / 2) + 2 * sizeof(u_int64_t));
                setCanary(stk, 0);
                hashCalc(stk);
            )

            #if DEBUG_LVL <= 1
                realloc(stk->data, sizeof(type_t) * (stk->capacity / 2));
            #endif

            stk->capacity /= 2;

            return 0;
        }
    }


    int stackPop(Stack* stk, type_t* param)
    {   
        if (stk->size <= 0) {
            return ERR_POP_EMPTY_STACK;
        }
        
        is_debug_lvl_0(
            STACK_DUMP(stk)
            ASSERT_OK(stk)
        )

        stk->size--;
        MemCpy(param, &(stk->data[stk->size]), sizeof(type_t));
        stk->data[stk->size] = POISON;

        while (stk->capacity / 2 - stk->size > 3) {
            is_debug_lvl_1(
                hashCalc(stk);
            )

            FUNC_REPORT(stackResize(stk, 0), stk)
        }

        is_debug_lvl_1(hashCalc(stk));

        is_debug_lvl_0(STACK_DUMP(stk));

        return 0;
    }


    is_debug_lvl_0(
        void verifyStack(Stack* stk){
            if (stk->data == (type_t*) 0xBEBE) {

                stk->status |= ERR_STACK_ALREADY_CLEANED;
            }
            if (((stk->status & ERR_STACK_ALREADY_CLEANED) == 0) && ((stk->status & EMPTY_STACK) == 0)){
                is_debug_lvl_1(
                    if (stk->hash != hashCalc(stk)) {
                        stk->status |= ERR_WRONG_HASH;
                    }
                )                                                                                                 
                if (stk->size > stk->capacity) {  
                    stk->status |= ERR_SIZE_GREATER_CAPACITY;                       
                }
                is_debug_lvl_1(
                    if (stk->egg != CANARY(stk)) {
                        printf("stk->egg ---- %lu\n", stk->egg);
                        stk->status |= ERR_LEFT_CANARY_DAMAGED;
                    }
                    if (stk->chicken != CANARY(stk)) {
                        stk->status |= ERR_RIGHT_CANARY_DAMAGED;
                    }
                    if ( (*((u_int64_t*) (LEFT_CANARY(stk)) )) != CANARY(stk)){
                        stk->status |= ERR_LEFT_DATACANARY_DAMAGED;
                    }
                    if ( (*((u_int64_t*) (RIGHT_CANARY(stk)))) != CANARY(stk)) {
                        stk->status |= ERR_RIGHT_DATACANARY_DAMAGED;
                    }
                )
                for (int i = stk->size; i < stk->capacity; i++){
                    if (stk->data[i] != POISON){
                        stk->status |= ERR_EMPTY_ELEM_ISNT_POISONED;
                    }
                }
            }

        }


        void stackDump(const Stack* stk, const char* func_name, const char* stack_name) {
            LOGSPRINT("Stack <> adress[%p] \"%s\" at %s\n", stk, stack_name, func_name);
            LOGSPRINT("---------------------------------------------------------------------------------\n");
            LOGSPRINT("STATUS = %16s\n" "stack size = %12d\n" "stack capacity = %8d\n" 
                    "data [%p]\n", (stk->status == OK || stk->status == EMPTY_STACK) ? "OK" : "BROKEN", stk->size, stk->capacity, stk->data);

            if (stk->status){
                printError(stk->status);
                LOGSPRINT("\n");
            }
            else {
                for (int i = 0; i < stk->size; i++){
                    LOGSPRINT("*data[%d] = %d\n", i, stk->data[i]);
                }
                for (int i = stk->size; i < stk->capacity; i++){
                    LOGSPRINT("*data[%d] = %X\n", i, stk->data[i]);
                }
            }

            LOGSPRINT("---------------------------------------------------------------------------------\n\n\n");
            fflush(logs);
        }   

    )


    static int MemCpy(void* destination, void* sourse, int element_size)
    {
        #if DEBUG_LVL > 0
            CHECK_PTR(destination)
            CHECK_PTR(sourse)
        #endif

        char* dest = (char*) destination;
        char* srs = (char*) sourse;

        while (element_size >= 16) {
            *((__int128_t*) dest) = *((__int128_t*) srs);

            dest += 16;
            srs += 16;
            element_size -= 16;
        }
        while (element_size >= 8) {
            *((__int64_t*) dest) = *((__int64_t*) srs);

            dest += 8;
            srs += 8;
            element_size -= 8;
        }
        while (element_size >= 4) {
            *((__int32_t*) dest) = *((__int32_t*) srs);

            dest += 4;
            srs += 4;
            element_size -= 4;
        }
        while (element_size >= 2) {
            *((__int16_t*) dest) = *((__int16_t*) srs);

            dest += 2;
            srs += 2;
            element_size -=2;
        }
        if (element_size == 1) {
            *dest = *srs;
        }

        return 0;
    }


    is_debug_lvl_1(
        static unsigned int hashCalc(Stack* stk) 
        {
            CHECK_PTR(stk)

            stk->hash = 0;
            stk->hash = MurmurHash2((char*) stk, sizeof(Stack)) + 
            MurmurHash2((char*) stk->data, 2 * sizeof(u_int64_t) + stk->capacity * sizeof(type_t));

            return stk->hash;
        }
    )


    static unsigned int MurmurHash2(char* key, unsigned int len) 
    {
        // большими буквами хекс
        const unsigned int m = 0x5BD1E995;
        const unsigned int seed = 0;
        const int r = 24;

        unsigned int h = seed ^ len;

        const unsigned char* data = (const unsigned char*) key;
        unsigned int k = 0;

        while (len >= 4) {
            k  = data[0];
            k |= data[1] << 8;
            k |= data[2] << 16;
            k |= data[3] << 24;

            k *= m;
            k ^= k >> r;
            k *= m;

            h *= m;
            h ^= k;

            data += 4;
            len -= 4;
        }

        switch (len) {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
        };
        
        h ^= h >> 13;
        h *= m;
        h ^= h >> 15;

        return h;
    }

    is_debug_lvl_0(
        void printError(int Error) 
        {
            if (Error & 1) 
                LOGSPRINT("ERR_CALLING_FUNC_FAILED ");
            if (Error & (1 << 1))
                LOGSPRINT("ERR_STACK_ALREARY_CREATED ");
            if (Error & (1 << 2))
                LOGSPRINT("ERR_EMPTY_ELEM_ISNT_POISONED ");
            if (Error & (1 << 3))
                LOGSPRINT("ERR_SIZE_GREATER_CAPACITY ");
            if (Error & (1 << 4))
                LOGSPRINT("ERR_POP_EMPTY_STACK ");
            if (Error & (1 << 5))
                LOGSPRINT("ERR_RIGHT_CANARY_DAMAGED ");
            if (Error & (1 << 6))
                LOGSPRINT("ERR_LEFT_CANARY_DAMAGED ");
            if (Error & (1 << 7))
                LOGSPRINT("ERR_WRONG_HASH ");
            if (Error & (1 << 8))
                LOGSPRINT("ERR_INVALID_PTR ");
            if (Error & (1 << 9))
                LOGSPRINT("ERR_REALLOC_FAILED ");
            if (Error & (1 << 10))
                LOGSPRINT("ERR_PUSH_FAILED ");
            if (Error & (1 << 11))
                LOGSPRINT("ERR_STACK_ALREADY_CLEANED ");
            if (Error & (1 << 12))
                LOGSPRINT("ERR_LEFT_DATACANARY_DAMAGED ");
            if (Error & (1 << 13))
                LOGSPRINT("ERR_RIGHT_DATACANARY_DAMAGED ");
            if (Error & (1 << 14))
                LOGSPRINT("ERR_RESIZE_FAILED ");
            if (Error & (1 << 15))
                LOGSPRINT("ERR_POP_FAILED ");
            if (Error & (1 << 16))
                LOGSPRINT("ERR_DUMP_FAILED ");
            if (Error & (1 << 17))
                LOGSPRINT("ERR_STACK_BROKEN ");
        }
    )

    is_debug_lvl_1(
        static void setCanary(Stack* stk, int is_left)
        {
            if (is_left == 1) {
                *((u_int64_t*) LEFT_CANARY(stk)) = CANARY(stk);
            }
            else {
                *((u_int64_t*) RIGHT_CANARY(stk)) = CANARY(stk);
            }
        }
    )

#endif
