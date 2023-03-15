#include "MainObject.h"

MainObject::MainObject()
{
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    widthFrame = 0;
    heightFrame = 0;
    status = WALK_NONE;
    inputType.right = 0;
    inputType.left = 0;
    inputType.down = 0;
    inputType.up = 0;
    inputType.jump = 0;
    onGround = false;
    map_x = 0;
    map_y = 0;
    comebackTime = 0;
}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if(ret == true)
    {
        widthFrame = objectRect.w/MAX_MAIN_OBJECT_FRAMES;
        heightFrame = objectRect.h;
    }
    return ret;
}
void MainObject::SetClip()
{
    if(widthFrame > 0 && heightFrame > 0)
    {
        for(int i = 0; i < MAX_MAIN_OBJECT_FRAMES; i++)
        {
            frameClip[i].x = i*widthFrame;
            frameClip[i].y = 0;
            frameClip[i].w = widthFrame;
            frameClip[i].h = heightFrame;
        }
    }
}
void MainObject::Show(SDL_Renderer* des)
{
    UpdateImgPlayer(des);
    if(inputType.left == 1 || inputType.right == 1)
    {
        frame++;
    }
    else
        frame = 0;
    if(frame >= MAX_MAIN_OBJECT_FRAMES)
    {
        frame = 0;
    }
    if(comebackTime == 0)
    {
        objectRect.x = x_pos - map_x;
        objectRect.y = y_pos - map_y;
        SDL_Rect* currentClip = &frameClip[frame];
        SDL_Rect renderquad = {objectRect.x, objectRect.y, widthFrame, heightFrame};

        SDL_RenderCopy(des, p_object, currentClip, &renderquad);
    }
}
void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            status = WALK_RIGHT;
            inputType.right = 1;
            inputType.left = 0;
            inputType.jump = 0;
            UpdateImgPlayer(screen);
        }
            break;
        case SDLK_LEFT:
        {
            status = WALK_LEFT;
            inputType.left = 1;
            inputType.right = 0;
            inputType.jump = 0;
            UpdateImgPlayer(screen);
        }
            break;
        case SDLK_UP:
        {
            inputType.jump = 1;
            if(onGround == true)
            {
                if(inputType.right == 1)
                {
                    LoadImg("asset/img/jum_right.png", screen);
                }
                else if(inputType.left == 1)
                {
                    LoadImg("asset/img/jum_left.png", screen);
                }
            }
        }
            break;
        default:
            break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            inputType.right = 0;
        }
            break;
        case SDLK_LEFT:
        {
            inputType.left = 0;
        }
            break;
        case SDLK_UP:
        {
            inputType.jump = 0;
        }
            break;
        default:
            break;
        }
    }
}
void MainObject::DoPlayer(Map& mapData)
{
    if(comebackTime == 0)
    {
        x_val = 0;
        y_val += GRAVITY_SPEED;
        if(y_val >= MAX_FALL_SPEED)
        {
            y_val = MAX_FALL_SPEED;
        }
        if(inputType.left == 1)
        {
            x_val -= PLAYER_SPEED;
        }
        if(inputType.right == 1)
        {
            x_val += PLAYER_SPEED;
        }
        if(inputType.jump == 1)
        {
            if(onGround == true)
            {
                y_val = -PLAYER_JUMP;
                onGround = false;
            }
            inputType.jump = 0;
        }
        CheckToMap(mapData);
        CenterEntityOnMap(mapData);
    }
    if(comebackTime > 0)
    {
        comebackTime--;
        if(comebackTime == 0)
        {
            onGround = false;
            if(x_pos > 256)
            {
                x_pos -= 256;
            }
            else
                x_pos = 0;
            y_pos = 0;
            x_val = 0;
            y_val = 0;
        }
    }
}
void MainObject::CheckToMap(Map& mapData)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    // check horizontal - Chieu ngang
    int heightMin = heightFrame < TILE_SIZE ? heightFrame : TILE_SIZE;
    x1 = (x_pos + x_val)/TILE_SIZE;
    x2 = (x_pos + x_val + widthFrame-1)/TILE_SIZE;

    y1 = (y_pos)/TILE_SIZE;
    y2 = (y_pos + heightMin - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if(x_val > 0) // main Object move to right
        {
            if(mapData.tile[y1][x2] != BLANK_TILE || mapData.tile[y2][x2] != BLANK_TILE)
            {
                x_pos = x2*TILE_SIZE;
                x_pos -= widthFrame + 1;
                x_val = 0;
            }
        }
        else
        {
            if(mapData.tile[y1][x1] != BLANK_TILE || mapData.tile[y2][x1] != BLANK_TILE)
            {
                x_pos = (x1+1)*TILE_SIZE;
                x_val = 0;
            }
        }
    }
    // check Vertical
    int widthMin = widthFrame < TILE_SIZE ? widthFrame : TILE_SIZE;
    x1 = (x_pos)/TILE_SIZE;
    x2 = (x_pos + widthMin - 1)/TILE_SIZE;

    y1 = (y_pos + y_val)/TILE_SIZE;
    y2 = (y_pos + y_val + heightFrame - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if(y_val > 0) // main Object move to right
        {
            if(mapData.tile[y2][x1] != BLANK_TILE || mapData.tile[y2][x2] != BLANK_TILE)
            {
                y_pos = y2*TILE_SIZE;
                y_pos -= heightFrame + 1;
                y_val = 0;
                onGround = true;
                if(status == WALK_NONE)
                {
                    status = WALK_RIGHT;
                }
            }
        }
        else
        {
            if(mapData.tile[y1][x1] != BLANK_TILE || mapData.tile[y1][x2] != BLANK_TILE)
            {
                y_pos = (y1+1)*TILE_SIZE;
                y_val = 0;
            }
        }
    }
    x_pos += x_val;
    y_pos += y_val;
    if(x_pos < 0)
        x_pos = 0;
    else if(x_pos + widthFrame > mapData.max_x)
    {
        x_pos = mapData.max_x - widthFrame;
    }
    if(y_pos > mapData.max_y)
    {
        comebackTime = 60;
    }
}
void MainObject::CenterEntityOnMap(Map& mapData)
{
    mapData.start_x = x_pos - (SCREEN_WIDTH/2);
    if(mapData.start_x < 0)
    {
        mapData.start_x = 0;
    }
    else if(mapData.start_x + SCREEN_WIDTH >= mapData.max_x)
    {
        mapData.start_x = mapData.max_x-SCREEN_WIDTH;
    }
    mapData.start_y = y_pos - SCREEN_HEIGHT/2;
    if(mapData.start_y < 0)
    {
        mapData.start_y = 0;
    }
    else if(mapData.start_y + SCREEN_HEIGHT >= mapData.max_y)
    {
        mapData.start_y = mapData.max_y - SCREEN_HEIGHT;
    }
}
void MainObject::UpdateImgPlayer(SDL_Renderer* des)
{
    if(onGround == true)
    {
        if(status == WALK_LEFT)
        {
            LoadImg("asset/img/player_left.png", des);
        }
        if(status == WALK_RIGHT)
        {
            LoadImg("asset/img/player_right.png", des);
        }
    }
    else
    {
        if(status == WALK_LEFT)
        {
            LoadImg("asset/img/jum_left.png", des);
        }
        if(status == WALK_RIGHT)
        {
            LoadImg("asset/img/jum_right.png", des);
        }
    }
}