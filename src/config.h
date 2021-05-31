#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>

namespace Countdown {
struct Config {
    bool pretty_print;
    std::string filename;

    Config();
};
}

#endif
