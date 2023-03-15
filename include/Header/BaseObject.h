#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int& x, const int& y) {objectRect.x = x; objectRect.y = y;}
    SDL_Rect GetRect() const {return objectRect;}
    SDL_Texture* GetObject() const {return p_object;}
    virtual bool LoadImg(std::string path, SDL_Renderer* des);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();
protected:
    SDL_Texture* p_object = NULL;
    SDL_Rect objectRect;
};

#endif