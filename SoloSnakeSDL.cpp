#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<SDL.h>
#include<stdio.h>
using namespace std;
int l=10, l2=510; //chieu dai hai con ran la luot la l va l2-500
//chieu dai toi da co the cua moi con la 450
//bien do dai khac nhau de khong bi trung chieu dai giua hai con
//gan mau sac
const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};

const char* number_bmp[3]= {"blue.bmp", "orange.bmp", "food.bmp"};
void logSDLError(std::ostream& os,
const std::string &msg, bool fatal = false);
void logSDLError(std::ostream& os,
const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
    SDL_Quit();
    exit(1);
    }
}
const int SCREEN_WIDTH = 410;
const int SCREEN_HEIGHT = 410;
const string WINDOW_TITLE = "Snake SDL";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
/////////////////////////////////////
void move(int i, int j, int h, int l,int maps[41][41],int i2, int j2, int h2, int l2, SDL_Window* window, SDL_Renderer* renderer);
void wall (SDL_Window* window, SDL_Renderer* renderer);
void food(int maps[41][41], SDL_Window* window, SDL_Renderer* renderer);
int main (int argc, char *args[])
{
    cout<<"DON'T CLICK ANYWHERE ELSE WHEN YOU PLAY THIS GAME, CLOSE CONSOLE WINDOW TO QUIT INSTANTLY\n\n";
    Sleep(1000); //delay 1000ms = 1s de nguoi dung xem notice
	do{//khoi tao vong lap de choi lai khi het tran
		SDL_Window* window;//khai bao cua so SDL
	    SDL_Renderer* renderer;//khai bao render
	    initSDL(window, renderer);//khoi tao cua so SDL
	    int maps[41][41];//mang hai chieu xu ly logic trong game
	
	    for(int i=0;i<41;i++)
	        for(int j=0;j<41;j++) maps[i][j]=997;//khoi tao mang voi tat ca gia tri la 997 ung voi vi tri o trong
	        //in hinh nen
	    SDL_SetRenderDrawColor(renderer,255, 255,255, 255);
	    SDL_Rect filled_rect;
	    filled_rect.x = 0;
	    filled_rect.y = 0;
	    filled_rect.w = 410;
	    filled_rect.h = 410;
	    SDL_RenderFillRect(renderer, &filled_rect);
	    SDL_RenderPresent(renderer);
	    //in food
	    SDL_SetRenderDrawColor(renderer,255, 50,150, 255);
	    food(maps, window, renderer);
	    SDL_RenderPresent(renderer);
	    //in tuong
	    wall(window, renderer);
	    //Ham di chuyen chinh
	    move(21, 21, 4, l, maps,11, 11, 4, l2,  window, renderer);//21 21 4 lan luot la vi tri dau(i, j) va huong di ban dau 
	    quitSDL(window, renderer);
	    cout<<"PRESS ' R ' TO REPLAY\nANY KEY ELSE TO QUIT\n\n";
	    char r;
	    r=getch();
	    if(r!='r'){
	        break;
	    }
	}while(true);
    return 0;
}
void wall (SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,55, 50,52, 255);
    for(int i=0;i<41;i++){SDL_Rect filled_rect;
    filled_rect.x = i*10;
    filled_rect.y = 400;
    filled_rect.w = 3;
    filled_rect.h = 3;
    SDL_RenderFillRect(renderer, &filled_rect);}
    for(int i=0;i<41;i++){SDL_Rect filled_rect;
    filled_rect.x = i*10;
    filled_rect.y = 0;
    filled_rect.w = 3;
    filled_rect.h = 3;
    SDL_RenderFillRect(renderer, &filled_rect);}
    for(int i=0;i<41;i++){SDL_Rect filled_rect;
    filled_rect.x = 400;
    filled_rect.y = i*10;
    filled_rect.w = 3;
    filled_rect.h = 3;
    SDL_RenderFillRect(renderer, &filled_rect);}
    for(int i=0;i<41;i++){SDL_Rect filled_rect;
    filled_rect.x = 0;
    filled_rect.y = i*10;
    filled_rect.w = 3;
    filled_rect.h = 3;
    SDL_RenderFillRect(renderer, &filled_rect);}
}
void food(int maps[41][41], SDL_Window* window, SDL_Renderer* renderer)
{
        int i, j;
        srand(time(NULL));//khoi tao hang random
        i=rand()%39+1;j=rand()%39+1;//tao gia tri random cho i va j trong khoang 0 den 39
        if(maps[i][j]!=997) food(maps, window, renderer);//neu vi tri vua random khong phai vi tri trong thi goi lai ham food() tim vi tri khac
        maps[i][j]=999;//gan vi tri tren map bang 999 tuong ung voi vi tri cua food
        SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);//ve food len cua so SDL
        SDL_Rect filled_rect;
        filled_rect.x = i*10;
        filled_rect.y = j*10;
        filled_rect.w = 10;
        filled_rect.h = 10;
        SDL_RenderFillRect(renderer, &filled_rect);
        SDL_RenderPresent(renderer);
}
void move(int i, int j, int h, int l, int maps[41][41], int i2, int j2, int h2, int l2, SDL_Window* window, SDL_Renderer* renderer)
{
	//i, j la diem dau con ran dang can di chuyen
	//l la chieu dai con ran
	//h la huong di chuyen 1 len, 2 xuong, 3 trai, 4 phai
    SDL_Rect filled_rect;//khai bao bien chu nhat
    if(i==i2&&j==j2){//neu vi tri dau hai con ran trung nhau tuc dam truc dien vao nhau thi tra ve ket qua hoa
        cout<<"DRAW\n";
        return;
    }
    int  daux=i, dauy=j;
    fflush(stdin); //xoa bo nho
	//ve dau ran con thu 1
    SDL_SetRenderDrawColor(renderer, 255, 0,0 , 255);
    filled_rect.x = i*10+1;
    filled_rect.y = j*10+1;
    filled_rect.w = 8;
    filled_rect.h = 8;
    SDL_RenderFillRect(renderer, &filled_rect);
    SDL_RenderPresent(renderer);

    int  daux2=i2, dauy2=j2;
    fflush(stdin); 
	//ve dau ran con thu 2
    SDL_SetRenderDrawColor(renderer, 50, 55,255 , 255);
    filled_rect.x = i2*10+1;
    filled_rect.y = j2*10+1;
    filled_rect.w = 8;
    filled_rect.h = 8;
    SDL_RenderFillRect(renderer, &filled_rect);
    SDL_RenderPresent(renderer);

    if(maps[i][j]<997) {        //neu vi tri map[i][j]<997 tuc la khac o trong hoac food thi tra ve blue win
        cout<<"BLUE WIN \n";
        return ;
    }
    for(int a=1;a<41;a++)   //ham di chuyen chinh
        for(int b=1;b<41;b++)
                    {
                    if(maps[a][b]!=997&&maps[a][b]!=999) {//khac o trong va khac food
                                                    maps[a][b]++;//map[a][b] la than ran thi tang len 1 don vi
                                                        }
                    if(maps[a][b]>l&&maps[a][b]<500&&maps[a][b]!=997&&maps[a][b]!=999||maps[a][b]>l2&&maps[a][b]!=997&&maps[a][b]!=999)  {
                    	//diem map[a][b] lon hon l tuc la diem cuoi cua con ran thi se duoc ve lai thanh o trong
                            SDL_SetRenderDrawColor(renderer,255, 255,255, 255);//ve diem a, b thanh o trong
                            SDL_Rect filled_rect;
                            filled_rect.x = a*10;
                            filled_rect.y = b*10;
                            filled_rect.w = 10;
                            filled_rect.h = 10;
                            SDL_RenderFillRect(renderer, &filled_rect);
                            SDL_RenderPresent(renderer);
                            maps[a][b]=997;
                    }
                    }
    int x=maps[i][j];
    maps[i][j]=1;//gan diem dau moi cua con ran 1
    if(x==999) {//neu an duoc food
        food(maps,window, renderer);//tao ra food moi
        if(l<450)l+=2;//tang do dai con ran neu l <450
    }
    if(GetAsyncKeyState(VK_UP)&&h!=2) {j--;h=1;}
    else if(GetAsyncKeyState(VK_DOWN)&&h!=1) {j++;h=2;}
    else if(GetAsyncKeyState(VK_LEFT)&&h!=4) {i--;h=3;}
    else if(GetAsyncKeyState(VK_RIGHT)&&h!=3) {i++;h=4;}
    else {
		if(h==1) j--;
	    if(h==2) j++;
	    if(h==3) i--;
	    if(h==4) i++;
	    }
     if(i==40) i=1;
     if(j==40) j=1;
     if(i==0) i=39;
     if(j==0) j=39;

    if(maps[i2][j2]<997) {
        cout<<"ORANGE WIN \n";        //check die
        return ;
    }
    int x2=maps[i2][j2];
    maps[i2][j2]=501;//gan diem dau moi cua con ran 2
    if(x2==999) {
        food(maps,window, renderer);
        if(l2<950)l2+=2;
    }
    if(GetAsyncKeyState('W')&&h2!=2) {j2--;h2=1;}
    else if(GetAsyncKeyState('S')&&h2!=1) {j2++;h2=2;}
    else if(GetAsyncKeyState('A')&&h2!=4) {i2--;h2=3;}
    else if(GetAsyncKeyState('D')&&h2!=3) {i2++;h2=4;}
    else {if(h2==1) j2--;
    if(h2==2) j2++;
    if(h2==3) i2--;
    if(h2==4) i2++;
    }
     if(i2==40) i2=1;
     if(j2==40) j2=1;
     if(i2==0) i2=39;
     if(j2==0) j2=39;
     // ve than con 1
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    filled_rect.x = daux*10;
    filled_rect.y = dauy*10;
    filled_rect.w = 10;
    filled_rect.h = 10;
    SDL_RenderFillRect(renderer, &filled_rect);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 155, 0, 255);
    filled_rect.x = daux*10+2;
    filled_rect.y = dauy*10+2;
    filled_rect.w = 6;
    filled_rect.h = 6;
    SDL_RenderFillRect(renderer, &filled_rect);
    SDL_RenderPresent(renderer);
     // ve than con 2
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    filled_rect.x = daux2*10;
    filled_rect.y = dauy2*10;
    filled_rect.w = 10;
    filled_rect.h = 10;
    SDL_RenderFillRect(renderer, &filled_rect);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
    filled_rect.x = daux2*10+2;
    filled_rect.y = dauy2*10+2;
    filled_rect.w = 6;
    filled_rect.h = 6;
    SDL_RenderFillRect(renderer, &filled_rect);
    SDL_RenderPresent(renderer);


     move(i, j, h, l, maps, i2, j2, h2, l2, window, renderer);//tiep tuc goi lai ham di chuyen khi game con tiep tuc

}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) //ham khoi tao cua so SDL

{

if (SDL_Init(SDL_INIT_EVERYTHING) != 0)

logSDLError(std::cout, "SDL_Init", true);

window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,

SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

if (window == NULL) logSDLError(std::cout, "CreateWindow", true);

renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |

SDL_RENDERER_PRESENTVSYNC);
if (renderer == NULL) logSDLError(std::cout, "CreateRenderer", true);

SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer) //ham nay de thoat cua so SDL
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
