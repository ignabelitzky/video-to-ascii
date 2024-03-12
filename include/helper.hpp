#ifndef HELPER_HPP
#define HELPER_HPP

#include "../include/miniaudio.hpp"
#include <string>

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

char pixelToASCII(int pixel);

#endif