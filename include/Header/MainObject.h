#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_MAIN_OBJECT_FRAMES 8
#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP 17
class MainObject:public BaseObject
{
    public:
        MainObject();
        ~MainObject() {;}
        enum WalkType
        {
            WALK_NONE = 0,
            WALK_LEFT = 1, 
            WALK_RIGHT = 2,
        };
        bool LoadImg(std::string path, SDL_Renderer* screen);
        void Show(SDL_Renderer* des);
        void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
        void SetClip();
        void DoPlayer(Map& mapData);
        void CheckToMap(Map& mapData);
        void SetMapXY(const int map_x_, const int map_y_) {map_x = map_x_; map_y = map_y_;}
        void CenterEntityOnMap(Map& mapData);
        void UpdateImgPlayer(SDL_Renderer* des);
    private:
        float x_val;
        float y_val;

        float x_pos;
        float y_pos;

        int widthFrame;
        int heightFrame;

        SDL_Rect frameClip[MAX_MAIN_OBJECT_FRAMES];
        Input inputType;
        int frame;
        int status;
        bool onGround;
        int map_x;
        int map_y;

        int comebackTime;
};


#endif