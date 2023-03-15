#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

class ImpTimer
{
    public:
        ImpTimer();
        ~ImpTimer();
        void Start();
        void Stop();
        void Paused();
        void UnPaused();

        int GetTicks();
        bool is_started();
        bool is_paused();
    private:
        int start_tick;
        int pause_tick;

        bool isPaused;
        bool isStarted;

};
#endif