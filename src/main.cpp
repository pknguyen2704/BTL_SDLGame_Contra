#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "ImpTimer.h"

BaseObject g_background;

bool Init();
bool LoadBackground();
void Close();

int main(int argc, char* argv[])
{
    // impTimer
    ImpTimer fps_timer;
    if(Init() == false)
        return -1;
    if(LoadBackground() == false)
        return -1;
    
    GameMap game_map;
    game_map.LoadMap("asset/map/map01.dat");
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("asset/img/player_right.png", g_screen);
    p_player.SetClip();
    bool isQuit = false;
    while(isQuit == false)
    {
        fps_timer.Start();
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                isQuit = true;
            }
            p_player.HandleInputAction(g_event, g_screen);
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        
        g_background.Render(g_screen, NULL);

        Map mapData = game_map.GetMap();

        p_player.SetMapXY(mapData.start_x, mapData.start_y);
        p_player.DoPlayer(mapData);
        p_player.Show(g_screen);
        
        game_map.SetMap(mapData);
        game_map.DrawMap(g_screen);
        SDL_RenderPresent(g_screen);
        int realImpTimer = fps_timer.GetTicks();
        int timeOneFrame = 1000/FRAME_PER_SECOND;
        if(realImpTimer < timeOneFrame)
        {
            int delayTime = timeOneFrame - realImpTimer;
            if(delayTime >= 0)
                SDL_Delay(delayTime);
        }
    }
    Close();
    return 0;
}

bool Init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("Contra v1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(g_window == NULL)
        success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlag = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlag) && imgFlag))
                success = false;
        }
    }
    return success;
}
bool LoadBackground()
{
    bool success = true;
    bool ret = g_background.LoadImg("asset/img/background.png", g_screen);
    if(ret == false)
        success = false;
    return success;
}
void Close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}