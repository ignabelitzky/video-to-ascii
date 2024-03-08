#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <string>
#include <stdexcept>
#include "../include/helper.hpp"

class Audio {
    public:
        Audio(std::string filename);
        ~Audio();
        void play();
    private:
        ma_result result;
        ma_decoder decoder;
        ma_device_config deviceConfig;
        ma_device device;
};

#endif