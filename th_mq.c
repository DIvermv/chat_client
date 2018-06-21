#include "func.h"
#include <pthread.h>
int prgs;
//struct mq_attr attr;
int Server_mq(void * f_data)
{	
 WINDOW *win = newwin(LINES-5,COLS-1 , 1, 1);
  char room[] = "Chat room :";
	sleep(2);
	char temp[256];
	int msqid; // IPC дескриптор для очереди сообщений 
   char pathname[] = "/initrd.img"; // Имя файла,  использующееся для генерации ключа.
    key_t key; /* IPC ключ */
   struct mymsgbuf
    {
        long mtype;
	struct mysbuf
	{
	short pid;	
        char mtext[256];
	} myscbuf;
    }mybuf;
   pid_t Pid;
   Pid=getpid();
    if((key = ftok(pathname,0)) < 0){// генерируем ключ
       mvwprintw(win,5,5,"Can\'t generate key\n");
    wrefresh(win);
        exit(-1);
    }
    // Пытаемся получить доступ по ключу к очереди сообщений, если она существует, или создать ее, с правами доступа read & write для всех пользователей 
    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
       mvwprintw(win,6,0,"Can\'t get msqid\n");
    wrefresh(win);
        exit(-1);
    }
int c=0;
int len;
 while(1)
   {
	c=0;   
	while((len = msgrcv(msqid, (struct msgbuf *) &mybuf, 256, Pid, 0))>0)   
          { 
            pthread_mutex_lock(&mut);
          // werase(win); //чистим экран
         //  box(win, 0, 0);
           mvwaddstr(win,0, 0, room);
           mvwaddstr(win,c+1, 0, mybuf.myscbuf.mtext);
          // mvwprintw(win,2, 0,"%i",len);
            c++;
           wrefresh(win);
            pthread_mutex_unlock(&mut);
          }
    sleep(1);
   } 
    delwin(win);
pthread_exit(0); }  






int Client_mq(void * f_data)
 {
   int msqid; // IPC дескриптор для очереди сообщений 
   char pathname[] = "/initrd.img"; // Имя файла,  использующееся для генерации ключа.
   key_t key; // IPC ключ
   pid_t Pid;
   struct mymsgbuf
    {
        long mtype;
	struct mysbuf
	{
	short pid;	
        char mtext[256];
	} myscbuf;
    }mybuf;
   Pid=getpid();
 if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
    pthread_exit(-1);
    } 
 if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
    pthread_exit(-1);
    }

    char temp[256];
    char nik[256];
    unsigned int prio = 1;
    WINDOW *win_c = newwin(4,COLS-1 , LINES-4, 1);
 
   // pthread_mutex_lock(&mut);
   
      mvwaddstr(win_c,1, 1, "Enter your nickname:");
      wrefresh(win_c);
   // pthread_mutex_unlock(&mut);
      mvwgetstr(win_c,2, 1, nik);
    // регистрируемся 
    mybuf.mtype=1;
    mybuf.myscbuf.pid=Pid;
    strcpy(mybuf.myscbuf.mtext,nik);
   int len=strlen(mybuf.myscbuf.mtext)+sizeof(Pid)+1;
     msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0);



      strcpy(temp,"");
      strcat(temp,"Your nickname: ");
     strcat(temp,nik);
     char nk[256];
    strcpy(nk,temp); 
    char t[256];
   // mybuf.mtype=1;
   // mybuf.myscbuf.pid=Pid;
   while(1)
   {
            pthread_mutex_lock(&mut);
      werase(win_c); //чистим экран
      box(win_c, 0, 0);
      mvwaddstr(win_c,0, 1, nk);
      wrefresh(win_c);
            pthread_mutex_unlock(&mut);
      mvwgetstr(win_c,1, 1, temp);
      strcpy(mybuf.myscbuf.mtext,temp);
     msgsnd(msqid, (struct msgbuf *) &mybuf, strlen(mybuf.myscbuf.mtext)+sizeof(Pid), 0);
   }
    delwin(win_c);
    pthread_exit(0);
 }

