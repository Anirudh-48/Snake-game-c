#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#include"input.cpp"
using namespace std;
int score=0;
int l = b_length();
int w = b_width();
char snk_skn = snk_sk();
void gtxy(int x, int y);
void GtXY(int x, int y);
void Delay(long double k);
//==== struct list;
typedef struct tail
{
 int x;
 int y;
 tail* next; // pointer to next node
 tail* prev; // pointer to previous node 
 }temp;
// d used to set the direction
int d = 4; // up = 1 , down = 2 , left =3 , right = 4;
class snake
{
public:
 int wallsX, wallsY; // wall start position
 int walleX, walleY; // wall end position
 int wall[10][5];
 int foodx, foody,bonusx,bonusy;
 HANDLE console_handle; // handle for the console
 COORD cur_cord; // COORD struct to keep the coordinate
 temp* start, * current, * newtail;
 snake(); // construct to initalise tail variable to null
 void insert(int x, int y); // insert the body of snake append to next node
 void draw(); // draw the snake
 void Wall(); // draw the wall
 void move(); // control the movement
 bool collision(); //check snake collision with itself or wall
 void food(int x = 0);
 void bonus(int x = 5);
};
// implement snake class
snake::snake()
{
 start = NULL;
 current = NULL;
 newtail = NULL;
 console_handle = GetStdHandle(STD_OUTPUT_HANDLE); // getting console handle
 foodx = 8;
 foody = 5;
 bonusx = 6;
 bonusy = 9;
}
void snake::insert(int x, int y)
{
 // check if start is null
 if (start == NULL)
 {
 newtail = new temp;
 newtail->x = x;
 newtail->y = y;
 newtail->next = NULL;
 newtail->prev = NULL;
 start = newtail;
 current = newtail;
 }
 else // insert new node to start node
 {
 newtail = new temp;
 newtail->x = x;
 newtail->y = y;
 newtail->next = NULL;
 newtail->prev = current;
 current->next = newtail;
 current = newtail;
 }
}
void snake::move()
{
 tail* tmp, * cur; // cur no use
 tmp = current; // point tmp to last node
 //cur =start->next;
 while (tmp->prev != NULL)
 {
 tmp->x = tmp->prev->x; // copy val from revious to last
 tmp->y = tmp->prev->y;
 tmp = tmp->prev; // set tmp to previous node
 }
 /*
 check for the value of d in order to change its direction
 */

 if (d == 1)
 start->y--;
 if (d == 2)
 start->y++;
 if (d == 3)
 start->x--;
 if (d == 4)
 start->x++;
}
void snake::draw()
{
 temp* tmp, * last;
 tmp = start;
 last = current;
 while (tmp != NULL)
 {
 cur_cord.X = tmp->x;
 cur_cord.Y = tmp->y;
 SetConsoleCursorPosition(console_handle, cur_cord);
 //cout << "*" << cur_cord.X <<"-" << cur_cord.Y ;
 cout << snk_skn;
 tmp = tmp->next;
 }
 // remove tail
 cur_cord.X = last->x;
 cur_cord.Y = last->y;

 SetConsoleCursorPosition(console_handle, cur_cord);
 cout << ' ';
 //draw the food
 cur_cord.X = foodx;
 cur_cord.Y = foody;
 SetConsoleCursorPosition(console_handle, cur_cord);
 cout << "?";
 cur_cord.X = bonusx;
 cur_cord.Y = bonusy;
 SetConsoleCursorPosition(console_handle, cur_cord);
 cout << "B";
}
void snake::Wall()
{
 int size = sizeof(wall) / sizeof(wall[0][0]);
 // draw left column
 cur_cord.X = 0;
 for (int y = 0; y <= l; y++)
 {
 cur_cord.Y = y;
 SetConsoleCursorPosition(console_handle, cur_cord);
 cout << '#';
 }
 // draw top row
 cur_cord.Y = 0;
 for (int x = 0; x <= w; x++)
 {
 cur_cord.X = x;
 SetConsoleCursorPosition(console_handle, cur_cord);
 cout << '#';
 }
 // draw right column
 cur_cord.X = w;
 for (int y = 0; y <= l; y++)
 {
 cur_cord.Y = y;
 SetConsoleCursorPosition(console_handle, cur_cord);
 cout << '#';
 }
 // draw bottom row
 cur_cord.Y = l;
 for (int x = 0; x <= w; x++)
 {
 cur_cord.X = x;
 SetConsoleCursorPosition(console_handle, cur_cord);
 cout << '#';
 }
 }
void snake::food(int x)

{
 temp* tmp;
 tmp = start->next;
 if (x == 1) // draw new food
 {
 foodx = rand() % w;
 foody = rand() % l;
 // check if food not created on snake body
 while (tmp->next != NULL)
 {
 if (foodx == tmp->x && foody == tmp->y)
 {
 food(1); // draw food at new position
 }
 tmp = tmp->next;
 }
 }
}
void snake::bonus(int x)
{
 temp* tmp;
 tmp = start->next;
 if (x == 5) // draw new food
 {
 bonusx = rand() % w;
 bonusy = rand() % l;
  // check if food not created on snake body
 while (tmp->next != NULL)
 {
 if (bonusx == tmp->x && bonusy == tmp->y)
 {
 bonus(5);
 }
 tmp = tmp->next;
 }
 }
}
bool snake::collision()
{
 temp* tmp;
 tmp = start->next;
 //check collision with itself
 while (tmp->next != NULL)
 {
 if (start->x == tmp->x && start->y == tmp->y)
 return true;
 tmp = tmp->next;
 }
 if (start->x == foodx && start->y == foody)
 {
 insert(foodx, foody);
 food(1);
 score += 1;
 }
 if (start->x == bonusx && start->y == bonusy)
 {
 insert(bonusx, bonusy);
 insert(bonusx, bonusy);
 insert(bonusx, bonusy);
 insert(bonusx, bonusy);
 bonus(5);
 score += 4;
 }
 //check collision with wall
 //collision top
 for (int x = 0; x <= w; x++)
 {
 if (start->x == x && start->y == 0)
 {
 return true;

}
 }
 //collision left
 for (int y = 0; y <= l; y++)
 {
 if (start->x == 0 && start->y == y)
 {
 return true;
 }
 }
 for (int y = 0; y <= l; y++)
 {
 if (start->x == w && start->y == y)
 {
 return true;
 }
 }
 //collision bottom
 for (int x = 0; x <= w; x++)
 {
 if (start->x == x && start->y == l)
 {
 return true;
 }
 }
 return false;
}
void play_data()
{
 char name[20], plname[20], ch, c;
 int i, j, px;
 FILE* info;
 info = fopen("record.txt", "w+");
 _getch();system("cls");
 printf("Enter your name\n");
 cin >> name;
 for (j = 0; name[j] != '\0'; j++)
{
 plname[0] = toupper(name[0]);
 if (name[j - 1] == ' ') {
 plname[j] = toupper(name[j]);
 plname[j - 1] = name[j - 1];
 }
 else plname[j] = name[j];
 }
 plname[j] = '\0';
 fprintf(info, "Player Name :%s\n", plname);
 time_t mytime;
 mytime = time(NULL);
 fprintf(info, "Played Date:%s", ctime(&mytime));
 fprintf(info, "Score:%d\n", px = score); //call score to display score
 for (i = 0; i <= 50; i++)
 fprintf(info, "%c", '_');
 fprintf(info, "\n");
 fclose(info);
 printf("wanna see past records press 'y'\n");
 ch = _getch();
 system("cls");if (ch == 'y') {
 info = fopen("record.txt", "r");
 do {
 putchar(c = getc(info));
 } while (c != EOF);
 }
 fclose(info);
}
void gtxy(int x, int y)
{
 COORD coord;
 coord.X = x;
 coord.Y = y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void GtXY(int x, int y)
{
 HANDLE a;
 COORD b;
 fflush(stdout);
 b.X = x;
 b.Y = y;
 a = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleCursorPosition(a, b);
}
void load() {
 int j, c, i;
 gtxy(l/2, w/2);
 printf("loading...");
 gtxy(l/2+1,w/2+1);
 for (i = 1; i <= 20; i++) {
 for (j = 0; j <= 99999999; j++);
 printf("%c", 210);
 }
 _getch();
}
void Delay(long double k)
{
 GtXY(l + 33, 8);
 printf("SCORE : %d", score);
 long double i;
 for (i = 0; i <= (9999990); i++);
}
int main()
{
 system("cls");
 cout<<"\t\tWELCOME TO THE SNAKE GAME"<<endl;
 cout<<"In order to make the snake move, the directional keys are to be used.";

 cout<<"\nThe normal food denoted by a '?' is worth 1 point whereas the bonus food
denoted by 'B' is worth 4 points";
 cout<<"\nAfter the game is over, the users shall be allowed to save their scores and look
at the scores of other players";
 cout<<"\nPress any key to continue";
 _getch();
system("cls");
load();
 snake ob;
 ob.insert(l / 2, 5);
 ob.insert(l / 2, 4);
 ob.insert(l / 2, 3);
 ob.insert(l / 2, 2);
 //ob.draw();
 int dir = 1; // initial direction
 while (1)
 {
 ob.draw();
 ob.Wall();
 Delay(l);
 system("CLS");
 if (ob.collision())// check for collision
 {
 cout << " You died ";
cout<<"\nYour score is:"<<score;
cout<<"\nCongratulations";
 break;
 }
 if (_kbhit())// check if keyboard key is pressed
 {
 switch (_getch())
 {
 case 72:d = 1;
 break;
 case 80:d = 2;
 break;
 case 75:d = 3;
 break;
 case 77:d = 4;
 break;
 }
 }
 ob.move();
 }
 play_data();
 _getch();
 return 0;
}
