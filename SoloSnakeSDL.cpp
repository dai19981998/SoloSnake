#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<SDL.h>
#include<stdio.h>
using namespace std;
  int l=10, l2=510; //chieu dai ran l va l2-500
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
    cout<<"DON'T CLICK ANYWHERE ELSE WHEN YOU PLAY THIS GAME\n\n";
    Sleep(1000);
    c:SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    int maps[41][41];

    for(int i=0;i<41;i++)
        for(int j=0;j<41;j++) maps[i][j]=997;
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
    move(21, 21, 4, l, maps,11, 11, 4, l2,  window, renderer);
    quitSDL(window, renderer);
    cout<<"PRESS ' R ' TO REPLAY\nANY KEY ELSE TO QUIT\n\n";
    char r;
    r=getch();
    if(r=='r'){
        goto c;
    }
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
        srand(time(NULL));
        i=rand()%39+1;j=rand()%39+1;
        if(maps[i][j]!=997) food(maps, window, renderer);
        maps[i][j]=999;
        SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
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
    SDL_Rect filled_rect;//khai bao bien chu nhat
    if(i==i2&&j==j2){
        cout<<"DRAW\n";
        return;
    }
    int  daux=i, dauy=j;
    fflush(stdin); //ve dau ran
    SDL_SetRenderDrawColor(renderer, 255, 0,0 , 255);
    filled_rect.x = i*10+1;
    filled_rect.y = j*10+1;
    filled_rect.w = 8;
    filled_rect.h = 8;
    SDL_RenderFillRect(renderer, &filled_rect);
    SDL_RenderPresent(renderer);

    int  daux2=i2, dauy2=j2;
    fflush(stdin); //ve dau ran con thu 2
    SDL_SetRenderDrawColor(renderer, 50, 55,255 , 255);
    filled_rect.x = i2*10+1;
    filled_rect.y = j2*10+1;
    filled_rect.w = 8;
    filled_rect.h = 8;
    SDL_RenderFillRect(renderer, &filled_rect);
    SDL_RenderPresent(renderer);

    if(maps[i][j]<997) {        //check die
        cout<<"BLUE WIN \n";
        return ;
    }
    for(int a=1;a<41;a++)   // xoa duoi ran
        for(int b=1;b<41;b++)
                    {
                    if(maps[a][b]!=997&&maps[a][b]!=999) {
                                                    maps[a][b]++;
                                                        }
                    if(maps[a][b]>l&&maps[a][b]<500&&maps[a][b]!=997&&maps[a][b]!=999||maps[a][b]>l2&&maps[a][b]!=997&&maps[a][b]!=999)  {
                            SDL_SetRenderDrawColor(renderer,255, 255,255, 255);
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
    maps[i][j]=1;
    if(x==999) {
        food(maps,window, renderer);
        l+=2;
    }
    if(GetAsyncKeyState(VK_UP)&&h!=2) {j--;h=1;}
    else if(GetAsyncKeyState(VK_DOWN)&&h!=1) {j++;h=2;}
    else if(GetAsyncKeyState(VK_LEFT)&&h!=4) {i--;h=3;}
    else if(GetAsyncKeyState(VK_RIGHT)&&h!=3) {i++;h=4;}
    else {if(h==1) j--;
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
    maps[i2][j2]=501;
    if(x2==999) {
        food(maps,window, renderer);
        l2+=2;
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
     // than con 1
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
     // than con 2
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


     move(i, j, h, l, maps, i2, j2, h2, l2, window, renderer);

}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)

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

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
