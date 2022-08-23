#ifndef WORKLOG_HPP
#define WORKLOG_HPP

#include <iostream>
#include <string>
#include <cstdlib>

class Worklog {
    std::string s;
    int exid;

   public:
    const char *getstr() const {
        return s.c_str();
    }
    int geteid() {
        return exid;
    }
    void exit() {
        std::exit(exid);
    }
    void post() {
        std::perror(s.c_str());
    }
    Worklog(std::string _s, int _e = -1) : s(_s), exid(_e) {}
    std::ostream& operator<<(std::ostream& out) {
        return out << s << std::endl;
    }
    bool has_error() { return exid != 0; }
};

#endif