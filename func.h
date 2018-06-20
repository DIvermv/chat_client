#ifndef FUNC_H
#define FUNC_H


#include <string.h>
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <mqueue.h>
#include <locale.h>

#define QUEUE_NAME "/my_queue" // имя очереди
#define PRIORITY   1
#define SIZE       256
struct displey {
	char List[256][256];// список сообщений
	char User_Name[256];// ник пользователя
               };
//struct  Panel  ReadDir(char * Dir_Name); // функция смены каталога
//void update_screen(struct DCommander DCommander);
//void update_panel(struct Panel Pan, int delta, int activ);
//struct DCommander press_enter(struct DCommander DCom);
//int Th_Copy_file(char* Sourse_Dir,char * Dest_Dir, char* File_Name );
 // потоковые функции
pthread_mutex_t mut;
int Server_mq(void * f_data);
int Client_mq(void * f_data);
// int Copy_file(void * f_name_data);
// int Copy_Progress(void * f_data);
#endif
