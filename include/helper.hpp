#ifndef HELPER_HPP
#define HELPER_HPP

#include "../include/miniaudio.hpp"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

#endif