#include "../include/helper.hpp"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == nullptr) {
        return;
    }

    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, nullptr);

    (void)pInput;
}