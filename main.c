
#include "func.h"

int main (int argc, char *argv[])
{
struct displey displey;
    setlocale(LC_ALL, "Russian");
char * temp;
//инициализируем окно ncurses
  initscr();
  start_color();
  keypad (stdscr, TRUE);
   // setlocale(LC_ALL,"");
 // noecho();

     
MEVENT event;// мышь
//создаем цветовые пары
  init_pair (1, COLOR_RED, COLOR_BLACK);
  init_pair (2, COLOR_WHITE, COLOR_BLACK);
  init_pair (3,  COLOR_BLACK,   COLOR_GREEN);
  init_pair (4, COLOR_WHITE,   COLOR_BLUE);
  init_pair (5,  COLOR_WHITE,   COLOR_RED);
 // update_screen(DCom); // выводим начальное состояние
//объявляем переменную для хранения нажатой клавиши
  int ch = 0;
  // инициализируем очередь
 // struct mq_attr attr;
 //       attr.mq_maxmsg = 25;//максимальное количество сообщений в очереди
 //       attr.mq_msgsize =SIZE; //максимальный размер сообщений - 256
  //   mqd = mq_open(QUEUE_NAME, O_CREAT|O_RDWR, 0600, &attr);

    pthread_t Server_tid; // идентификатор потока копирования 
    pthread_t Client_tid; // идентификатор потока статуса копирования 
    pthread_attr_t Server_attr; // атрибуты потока копирования 
    pthread_attr_t Client_attr; // атрибуты потока статуса копирования 
    pthread_attr_init(&Server_attr);
    pthread_attr_init(&Client_attr);
   // f_name_data.Sourse_Dir=Sourse_Dir;// назначаем аргументы
   // f_name_data.Dest_Dir=Dest_Dir;
   // f_name_data.File_Name=File_Name;
   // f_name_data.copy_progress=30;
    pthread_mutex_init(&mut,NULL);
   pthread_create(&Server_tid,&Server_attr,Server_mq,NULL);// создаем новый поток
  pthread_create(&Client_tid,&Client_attr,Client_mq,NULL);// создаем новый поток
  // pthread_create(&Status_tid,&Status_attr,Copy_Progress,&f_name_data);
  pthread_join(Client_tid,NULL);
 
  while (ch != KEY_F(9))
   ch = getch();
 
/*
//считываем клавиши, пока не будет нажата 'F3' (по F3 - выход)
  while (ch != KEY_F(9))
        {
         //обновляем экран
         update_screen(DCom);
         mousemask (ALL_MOUSE_EVENTS, NULL);// инициализируем считывание мыши
	      //ожидаем нажатия на клавишу и
         //получаем её код в ch
         ch = getch();

         switch (ch)
                {
//если нажата "F1", то активируем левую панель
                 case KEY_F(1):
                            DCom.current_panel=1;
                             break;
//если нажата "F2", то активируем правую панель
                 case KEY_F(2):
			       DCom.current_panel=0;
                             break;
//если нажата "F5", то копируем файл
                 case KEY_F(5):
                        if(strcmp(DCom.L.Type[DCom.L.current_position],"<DIR>"))  //проверяем, чтоб это не был каталог
			   {   char  File_Name[256];
			         strcpy(File_Name,DCom.L.List[DCom.L.current_position]);
			        if(DCom.L.Type[DCom.L.current_position]!="")
			         {strcat(File_Name,".");
			          strcat(File_Name,DCom.L.Type[DCom.L.current_position]);
				 }


                              Th_Copy_file(DCom.L.Current_Dir,DCom.R.Current_Dir, File_Name );
			      strcpy(DCom.Status,"File copied: ");
			      strcat(DCom.Status,File_Name);
			  }
                         DCom.R= ReadDir(DCom.R.Current_Dir);
                             break;
//если нажата "вверх"
                 case KEY_UP:
			    if ( DCom.current_panel) // левая панель
				    {if(DCom.L.current_position>0)
                         DCom.L.current_position--;}
                else
                    {if(DCom.R.current_position>0)
                         DCom.R.current_position--;}
                             break;
//если нажата "вниз"
                case KEY_DOWN:
			    if ( DCom.current_panel) // левая панель
				    {if(DCom.L.current_position<DCom.L.str_count)
                         DCom.L.current_position++;}
                else
                    {if(DCom.R.current_position<DCom.R.str_count)
                         DCom.R.current_position++;}
                             break;
//если нажата "влево"
                case KEY_LEFT:
			    DCom.current_panel=1;
                             break;
//если нажата "вправо"
                case KEY_RIGHT:
			    DCom.current_panel=0;
                             break;

//если нажата "BACKSPACE" // выйти на каталог выше
                case KEY_BACKSPACE:
                            if(DCom.current_panel) // левая панель
                              {  if(strlen(DCom.L.Current_Dir)>2)
                                 strcpy(strrchr(DCom.L.Current_Dir,'/'),""); // находим / с конца строки,  все, что после него - убиваем
                                 DCom.L= ReadDir(DCom.L.Current_Dir);}
                              else
                              { if(strlen(DCom.R.Current_Dir)>2)
                                strcpy(strrchr(DCom.R.Current_Dir,'/'),"");
                                DCom.R= ReadDir(DCom.R.Current_Dir);}
                                break;
//обработка нажатия Enter
                 case '\n':
                     DCom= press_enter(DCom);
                                break;
// обработка нажатия мыши - не контролирует, какая клавиши нажата, только факт нажатия
	         //case  KEY_MOUSE:
                               if (getmouse(&event) == OK)
			          if(event.y==LINES-2) // попали в функциональные клавиши
				     if(event.x<COLS/3) // F1
                                         MyNote=Open_File();
				     if((event.x>COLS/3)&&(event.x<COLS*2/3)) // F2
			                 MyNote= File_Save(MyNote);
				     if(event.x>COLS*2/3) // F3
                                        ch = KEY_F(3);
				  else	 // просто установим курсор туда, куда попала мышь
				   {
                                    curposY=event.y;
			            curposX=event.x;
				   }
                  //            break;
// все остальные клавиши
		default  :
                    // mvaddstr(LINES,0,ch);
                               break;
                }
        }*/
  endwin();// разрушаем окно
  return 0;
}
