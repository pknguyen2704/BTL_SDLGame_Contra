#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <iostream>
#include <string>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

// set FPS
const int FRAME_PER_SECOND = 60;
//window dimension
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;

// Map
#define TILE_SIZE 64 // kich thuoc mat luoi
#define BLANK_TILE 0
#define MAX_MAP_X 400 // so o max theo chieu ngang
#define MAX_MAP_Y 10 // so o max theo chieu rong
struct Input
{
    int left;
    int right;
    int up;
    int down;
    int jump;
};
struct Map
{
    // vi tri cua map
    int start_x;
    int start_y;

    // Chi so cua o day (o thu bao nhiu)
    int max_x; //== start/TILE_SIZE;
    int max_y; 

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* filename;
};



#endif