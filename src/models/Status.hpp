#ifndef STATUS
#define STATUS

#include <string>

enum class Status {
    Proposed,
    Accepted,
    Planned,
    Completed,
    Missed
};

inline std::string stringStatus(Status status) {
    switch (status) {
        case Status::Proposed:  return "Proposed";
        case Status::Accepted:  return "Accepted";
        case Status::Planned:   return "Planned";
        case Status::Completed: return "Completed";
        case Status::Missed:    return "Missed";
    }
    return "Unknown";
}

#endif