#pragma once

class Timer {
public:
    Timer();
    void Update(int dt);
    void Restart();
    int Get();
private:
    int time;
};

