#pragma once
#include <chrono>
#include <string>
#include "../Pattern.h"

class TimeSystem {
    using TimePoint = std::chrono::system_clock::time_point;

    DeclSingleton(TimeSystem)

public:
    TimeSystem() {}
    ~TimeSystem() {}

    void Initialize();
    void Update();
    double GetDeltaTime();

    double GetFrameRate();

    static std::string GetTimeStamp();

private:
    TimePoint _prevTime;
    TimePoint _curTime;

    double _deltaTime = 0;
};

