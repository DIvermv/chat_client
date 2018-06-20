#include "func.h"
#include <pthread.h>
int prgs;
struct mq_attr attr;
int Server_mq(void * f_data)
{	
	char temp[256];
//	struct mq_attr attr;
  mqd_t mqd; // идентификатор очереди
	sleep(2);
	if(( mqd = mq_open(QUEUE_NAME,O_RDONLY,0777,NULL)) == (mqd_t)-1){

    perror("Opening queue error");
    sleep(3);
  endwin();// разрушаем окно
    return -1;
    }
 
 else // удачное открытие очереди
 {	 
//	 Mq_getattr(mqd, &attr);
 WINDOW *win = newwin(LINES-5,COLS-1 , 1, 1);
   // char hello[] = "Hello, world!";
  // char hello[] = QUEUE_NAME;
  char room[] = "Chat room :";
  strcat(room,QUEUE_NAME);
int c=0;
 while(1)
   {int n=mq_receive(mqd, temp, 256, NULL);
	  
    // printf("read %ld bytesn", (long) n);
    
//    if (errno != EAGAIN)
  //   err_sys("mq_receive error"); 
   // pthread_mutex_lock(&mut);
    werase(win); //чистим экран
     // box(win, 0, 0);
      mvwaddstr(win,0, 0, room);
      mvwaddstr(win,1, 0, temp);
      mvwprintw(win,2, 0,"%i long %i",c,n);
      c++;
    wrefresh(win);
   // pthread_mutex_unlock(&mut);
   // getch();
    sleep(1);
   } 
    delwin(win);
 }
pthread_exit(0); }  

int Client_mq(void * f_data)
 {
 // struct _f_name_data f_name_data= * (struct _f_name_data * ) f_data;
    // статусная строка
    char temp[256];
    strcpy(temp,"test");
  mqd_t mqd; // идентификатор очереди
    char nik[256];

        attr.mq_maxmsg = 25;//максимальное количество сообщений в очереди
        attr.mq_msgsize =256; //максимальный размер сообщений
        attr.mq_flags = 0;//флаг - 0 или O_NONBLOCK
        attr.mq_curmsgs = 0;//текущее сообщение
  mq_unlink(QUEUE_NAME);
  //  perror("Removing queue error");
 // return 0;
    if ((mqd = mq_open(QUEUE_NAME, O_CREAT | O_RDWR ,0777, NULL)) == (mqd_t)-1){
   // if ((mqd = mq_open(QUEUE_NAME, O_RDWR ,0777, &attr)) == (mqd_t)-1){
    perror("Creating queue error");
    sleep(3);
  endwin();// разрушаем окно
    return -1;
    }
    else
    {   
	    unsigned int prio = 1;
    WINDOW *win_c = newwin(4,COLS-1 , LINES-4, 1);
        mvwprintw(win_c, 1, 1,"%d",mqd);
 
      wrefresh(win_c);
  sleep(1);
	   for (int i=0;i<10;i++)
	   {
		   if(mq_send(mqd,temp,strlen(temp),prio) == -1){
                   
                   mvwprintw(win_c, 1, 1,"%i",i);  
    
    wrefresh(win_c);
sleep(1);
		   }               
	   }
		  // mq_send(mqd,temp,strlen(temp),prio);
	   
   werase(win_c); //чистим экран

   mvwprintw(win_c, 1, 1,"%i",mqd);  
   //  fgets(displey.User_Name, sizeof(displey.User_Name), stdin);

     //printf("%s%s\n","your nickname:",displey.User_Name);
    // sleep(3);
    char hello[] = "Hello, world2!";
    pthread_mutex_lock(&mut);
   
   // box(win_c, 0, 0);
      mvwaddstr(win_c,1, 1, "Enter your nickname:");
    wrefresh(win_c);
    pthread_mutex_unlock(&mut);
      mvwgetstr(win_c,2, 1, nik);
    strcpy(temp,"");

      strcat(temp,"Your nickname: ");
     strcat(temp,nik);

    pthread_mutex_lock(&mut);
   werase(win_c); //чистим экран
  //  box(win_c, 0, 0);
      mvwaddstr(win_c,0, 1, temp);

//    box(win, 0, 0);
    wrefresh(win_c);
    pthread_mutex_unlock(&mut);
   while(1)
   {
    mvwgetstr(win_c,1, 1, temp);
   int n= mq_send(mqd,temp,strlen(temp),1);
   mvwprintw(win_c, 2, 1,"%i",n);  
//   mvwaddstr(win_c,2, 1,n);
    wrefresh(win_c);
      sleep(2);
   }
   mq_close(mqd);
    delwin(win_c);

    }      // refresh();
	   pthread_exit(0);
 }

