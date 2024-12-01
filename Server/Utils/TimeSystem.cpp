#include "TimeSystem.h"

ImplSingleton(TimeSystem)

void TimeSystem::Initialize()
{
    _prevTime = _curTime = std::chrono::system_clock::now();
}

void TimeSystem::Update()
{
    _prevTime = _curTime;
    _curTime = std::chrono::system_clock::now();
    _deltaTime = std::chrono::duration<double>(_curTime - _prevTime).count();
}

double TimeSystem::GetDeltaTime()
{
    return _deltaTime;
}

double TimeSystem::GetFrameRate()
{
    if (_deltaTime == 0) return 0;
    return ceil((1.0f / _deltaTime));
}

std::string TimeSystem::GetTimeStamp()
{
    const TimePoint now = std::chrono::system_clock::now();
    time_t nowTime = std::chrono::system_clock::to_time_t(now);
    struct tm timeStruct;
    localtime_s(&timeStruct, &nowTime);

#if _HAS_CXX20 == 1
    std::string timeStamp =
        std::format(
            "{:0>4}-{:0>2}-{:0>2} {:0>2}:{:0>2}:{:0>2}",
            timeStruct.tm_year + 1900, timeStruct.tm_mon + 1, timeStruct.tm_mday,
            timeStruct.tm_hour, timeStruct.tm_min, timeStruct.tm_sec
        );
    return timeStamp;
#else
    char temp[128];
    snprintf(temp, sizeof(temp), "%04d-%02d-%02d %02d:%02d:%02d",
        timeStruct.tm_year + 1900, timeStruct.tm_mon + 1, timeStruct.tm_mday,
        timeStruct.tm_hour, timeStruct.tm_min, timeStruct.tm_sec);

    return std::string(temp);
#endif

}