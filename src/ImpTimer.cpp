#include "CommonFunc.h"
#include "ImpTimer.h"

ImpTimer::ImpTimer()
{
    start_tick = 0;
    pause_tick = 0;
    isPaused = false;
    isStarted = false;
};
ImpTimer::~ImpTimer()
{

};
void ImpTimer::Start()
{
    isStarted = true;
    isPaused = false;

    start_tick = SDL_GetTicks();

}
void ImpTimer::Stop()
{
    isPaused = false;
    isStarted = false;
}
void ImpTimer::Paused()
{
    if(isStarted == true && isPaused == false)
    {
        isPaused = true;
        pause_tick = SDL_GetTicks() - start_tick;
    }
}
void ImpTimer::UnPaused()
{
    if(isPaused == true)
    {
        isPaused = false;
        start_tick = SDL_GetTicks() - pause_tick;
        pause_tick = 0;
    }
}
int ImpTimer::GetTicks()
{
    if(isStarted == true)
    {
        if(isPaused == true)
        {
            return pause_tick;
        }
        else
        {
            return SDL_GetTicks() - start_tick;
        }
    }
    return 0;
}
bool ImpTimer::is_started()
{
    return isStarted;
}
bool ImpTimer::is_paused()
{
    return isPaused;
}