/*
 *
 * Memshare, quick and easy IPC.
 * Copyright (C) 2012  Tommy Wiklund
 *
 */

#ifndef _MEMSHARE_API_H
#define _MEMSHARE_API_H

typedef void (*callback_1) (char *, int);
typedef void (*callback_2) (char *, int, int);
typedef void (*callback_3) (char *, int, int, int);
typedef void (*callback_data) (char *, char *, int);
typedef void (*callback_extlog) (int, const char *, ...);

#define PROC_NAME_SIZE 20
int print(int level, const char *format, ...);

/*****************************************************************************/
/* Function Name      : add_log_function                                     */
/* Description        : Add a function to be called when logging             */
/* Input(s)           : a function func(int , const char *, ...)             */
/* Output(s)          : None.                                                */
/* Return Value(s)    : None.                                                */
/*****************************************************************************/
void logfunction_register(callback_extlog);

/*****************************************************************************/
/* Function Name      : set_print_level                                      */
/* Description        : Sets the verbose level for output, every thing below */
/*                    : will be printed.                                     */
/* Input(s)           : From 0 to 7, syslog levels can be used (int)         */
/*                    : If an external logfunction is used this level is     */
/*                    : bypassed                                             */
/* Output(s)          : None.                                                */
/* Return Value(s)    : 0 ok                                                 */
/*****************************************************************************/
int set_print_level(int);

/*****************************************************************************/
/* Function Name      : init_memshare                                        */
/* Description        : This function initialises the memshare lib           */
/* Input(s)           : proc name(string 20 char)                            */
/*                      Size of memory for receiving buffer, null means that */
/*                      the proccess will not register for receive(int byte) */
/*                      The queue size as buffer for receiving (int entries) */
/*                                                                           */
/* Output(s)          : None.                                                */
/* Return Value(s)    : 0 ok                                                 */
/*                      1 already initialized                                */
/*                      2 a NULL pointer as a proc name                      */
/*                      3 semaphore allocation failure                       */
/*                      4 proc name already exists                           */
/*                      5 Max num of processes registered                    */
/*                      6 Shared memory problems                             */
/*****************************************************************************/
int init_memshare(char *, int, int);

/*****************************************************************************/
/* Function Name      : data_register                                        */
/* Description        : This function registers a function that will be      */
/*                      called whenever a data is received.                  */
/* Input(s)           : a function func(char *msg, int len)                  */
/* Output(s)          : None.                                                */
/* Return Value(s)    : None.                                                */
/*****************************************************************************/
void data_register(callback_data);

/*****************************************************************************/
/* Function Name      : signal1_register                                     */
/* Description        : This function registers a function that will be      */
/*                      called whenever a signal1 is received.               */
/* Input(s)           : a function func(int sig)                             */
/* Output(s)          : None.                                                */
/* Return Value(s)    : None.                                                */
/*****************************************************************************/
void signal1_register(callback_1);

/*****************************************************************************/
/* Function Name      : signal2_register                                     */
/* Description        : This function registers a function that will be      */
/*                      called whenever a signal2 is received.               */
/* Input(s)           : a function func(int sig1, int sig2)                  */
/* Output(s)          : None.                                                */
/* Return Value(s)    : None.                                                */
/*****************************************************************************/
void signal2_register(callback_2);

/*****************************************************************************/
/* Function Name      : signal3_register                                     */
/* Description        : This function registers a function that will be      */
/*                      called whenever a signal3 is received.               */
/* Input(s)           : a function func(int sig1, int sig2, int sig3)        */
/* Output(s)          : None.                                                */
/* Return Value(s)    : None.                                                */
/*****************************************************************************/
void signal3_register(callback_3);

/*****************************************************************************/
/* Function Name      : data                                                 */
/* Description        : This functionsn will send a data block to a specific */
/*                      dest proc                                            */
/* Input(s)           : destination proc(char*), data block(char*),          */
/*                      length of data block(int)                            */
/* Output(s)          : None.                                                */
/* Return Value(s)    : 0 ok                                                 */
/*                      1 No dest process process available                  */
/*                      2 Memshare not initialized                           */
/*****************************************************************************/
int data(char *, char *, int);

/*****************************************************************************/
/* Function Name      : signal1                                              */
/* Description        : This function will send an integer to a specific     */
/*                      dest proc                                            */
/* Input(s)           : destination proc(char*), integer(int)                */
/* Output(s)          : None.                                                */
/* Return Value(s)    : 0 ok                                                 */
/*                      1 No dest process process available                  */
/*                      2 Memshare not initialized                           */
/*****************************************************************************/
int signal1(char *, int);

/*****************************************************************************/
/* Function Name      : signal2                                              */
/* Description        : This function will send two integers to a specific   */
/*                      dest proc                                            */
/* Input(s)           : destination proc(char*), integer1(int), integer1(int)*/
/* Output(s)          : None.                                                */
/* Return Value(s)    : 0 ok                                                 */
/*                      1 No dest process process available                  */
/*                      2 Memshare not initialized                           */
/*****************************************************************************/
int signal2(char *, int, int);

/*****************************************************************************/
/* Function Name      : signal3                                              */
/* Description        : This function will send three integers to a specific */
/*                      dest proc                                            */
/* Input(s)           : destination proc(char*), integer1(int), integer2(int)*/
/*                      integer3(int)                                        */
/* Output(s)          : None.                                                */
/* Return Value(s)    : 0 ok                                                 */
/*                      1 No dest process process available                  */
/*                      2 Memshare not initialized                           */
/*****************************************************************************/
int signal3(char *, int, int, int);

/*****************************************************************************/
/* Function Name      : get_datasize                                         */
/* Description        : This function ask for the size of data a process     */
/*                      can receive                                          */
/* Input(s)           : proc(char*)                                          */
/* Output(s)          : None.                                                */
/* Return Value(s)    : 0 No such process                                    */
/*                      n The max size in bytes that can be sent with data   */
/*****************************************************************************/
int get_datasize(char *);

#endif				/* _MEMSHARE_API_H */
