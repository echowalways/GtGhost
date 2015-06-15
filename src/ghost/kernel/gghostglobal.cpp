#include "gghostglobal.h"

const char *Ghost::toString(Ghost::Status status)
{
    static const char s_invalid[] = "Invalid";
    static const char s_standBy[] = "StandBy";
    static const char s_running[] = "Running";
    static const char s_success[] = "Success";
    static const char s_failure[] = "Failure";
    static const char s_stopped[] = "Stopped";

    switch (status) {
    case Ghost::Invalid:
        return s_invalid;
        break;
    case Ghost::StandBy:
        return s_standBy;
        break;
    case Ghost::Running:
        return s_running;
        break;
    case Ghost::Success:
        return s_success;
        break;
    case Ghost::Failure:
        return s_failure;
        break;
    case Ghost::Stopped:
        return s_stopped;
        break;
    }

    Q_UNREACHABLE();
    return 0;
}
