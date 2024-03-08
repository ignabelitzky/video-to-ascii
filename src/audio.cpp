#include "../include/audio.hpp"

Audio::Audio(std::string filename) {
    result = ma_decoder_init_file(filename.c_str(), NULL, &decoder);
    if (result != MA_SUCCESS) {
        throw std::runtime_error("Could not load file");
    }
    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate        = decoder.outputSampleRate;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = &decoder;
}


Audio::~Audio() {
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
}

void Audio::play() {
    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        throw std::runtime_error("Failed to open playback device");
    }
    if (ma_device_start(&device) != MA_SUCCESS) {
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
        throw std::runtime_error("Failed to start playback device");
    }
}