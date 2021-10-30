#include "lvgl/lvgl.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_IMG_SIGN3
#define LV_ATTRIBUTE_IMG_IMG_SIGN3
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG_IMG_SIGN3 uint8_t IMG_Sign3_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Alpha 8 bit, Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0xff, 0x90, 0xff, 0xc0, 0xff, 0x60, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0x80, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0x80, 0xff, 0x10, 0xff, 0x40, 0xff, 0x40, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0x80, 0xff, 0x40, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0x80, 0xff, 0x40, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0x80, 0xff, 0x40, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0x60, 0xff, 0x80, 0xff, 0x40, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0x80, 0xff, 0x40, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xc0, 0xff, 0xff, 0xff, 0x80, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0x80, 0xff, 0x40, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xc0, 0xff, 0xff, 0xff, 0x80, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0x80, 0xff, 0x40, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xc0, 0xff, 0xff, 0xff, 0x80, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0x80, 0xff, 0x40, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xc0, 0xff, 0xff, 0xff, 0x80, 
  0xff, 0x90, 0xff, 0xc0, 0xff, 0x60, 0xff, 0x30, 0xff, 0xc0, 0xff, 0xc0, 0xff, 0x00, 0xff, 0x90, 0xff, 0xc0, 0xff, 0x60, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0xbf, 0xff, 0x90, 0xbf, 0xff, 0xc0, 0xbf, 0xff, 0x60, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0x80, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0x80, 0xbf, 0xff, 0x10, 0xbf, 0xff, 0x40, 0xbf, 0xff, 0x40, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0x80, 0xbf, 0xff, 0x40, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0x80, 0xbf, 0xff, 0x40, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0x80, 0xbf, 0xff, 0x40, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0x00, 0xbf, 0xff, 0x60, 0xbf, 0xff, 0x80, 0xbf, 0xff, 0x40, 
  0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0x80, 0xbf, 0xff, 0x40, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0x00, 0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0x80, 
  0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0x80, 0xbf, 0xff, 0x40, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0x00, 0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0x80, 
  0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0x80, 0xbf, 0xff, 0x40, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0x00, 0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0x80, 
  0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0x80, 0xbf, 0xff, 0x40, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0x00, 0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0x80, 
  0xbf, 0xff, 0x90, 0xbf, 0xff, 0xc0, 0xbf, 0xff, 0x60, 0xbf, 0xff, 0x30, 0xbf, 0xff, 0xc0, 0xbf, 0xff, 0xc0, 0xff, 0xff, 0x00, 0xbf, 0xff, 0x90, 0xbf, 0xff, 0xc0, 0xbf, 0xff, 0x60, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0xff, 0xbf, 0x90, 0xff, 0xbf, 0xc0, 0xff, 0xbf, 0x60, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0x80, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0x80, 0xff, 0xbf, 0x10, 0xff, 0xbf, 0x40, 0xff, 0xbf, 0x40, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0x80, 0xff, 0xbf, 0x40, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0x80, 0xff, 0xbf, 0x40, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 
  0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0x80, 0xff, 0xbf, 0x40, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0x00, 0xff, 0xbf, 0x60, 0xff, 0xbf, 0x80, 0xff, 0xbf, 0x40, 
  0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0x80, 0xff, 0xbf, 0x40, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0x00, 0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0x80, 
  0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0x80, 0xff, 0xbf, 0x40, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0x00, 0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0x80, 
  0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0x80, 0xff, 0xbf, 0x40, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0x00, 0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0x80, 
  0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0x80, 0xff, 0xbf, 0x40, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0x00, 0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xff, 0xff, 0xbf, 0x80, 
  0xff, 0xbf, 0x90, 0xff, 0xbf, 0xc0, 0xff, 0xbf, 0x60, 0xff, 0xbf, 0x30, 0xff, 0xbf, 0xc0, 0xff, 0xbf, 0xc0, 0xff, 0xff, 0x00, 0xff, 0xbf, 0x90, 0xff, 0xbf, 0xc0, 0xff, 0xbf, 0x60, 
#endif
#if LV_COLOR_DEPTH == 32
  0xf5, 0xf5, 0xf5, 0x90, 0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0x60, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0x80, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0x80, 0xf5, 0xf5, 0xf5, 0x10, 0xf5, 0xf5, 0xf5, 0x40, 0xf5, 0xf5, 0xf5, 0x40, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0x80, 0xf5, 0xf5, 0xf5, 0x40, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0x80, 0xf5, 0xf5, 0xf5, 0x40, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 
  0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0x80, 0xf5, 0xf5, 0xf5, 0x40, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xff, 0xff, 0xff, 0x00, 0xf5, 0xf5, 0xf5, 0x60, 0xf5, 0xf5, 0xf5, 0x80, 0xf5, 0xf5, 0xf5, 0x40, 
  0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0x80, 0xf5, 0xf5, 0xf5, 0x40, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xff, 0xff, 0xff, 0x00, 0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0x80, 
  0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0x80, 0xf5, 0xf5, 0xf5, 0x40, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xff, 0xff, 0xff, 0x00, 0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0x80, 
  0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0x80, 0xf5, 0xf5, 0xf5, 0x40, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xff, 0xff, 0xff, 0x00, 0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0x80, 
  0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0x80, 0xf5, 0xf5, 0xf5, 0x40, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0xff, 0xff, 0xff, 0xff, 0x00, 0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xff, 0xf5, 0xf5, 0xf5, 0x80, 
  0xf5, 0xf5, 0xf5, 0x90, 0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0x60, 0xf5, 0xf5, 0xf5, 0x30, 0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0xc0, 0xff, 0xff, 0xff, 0x00, 0xf5, 0xf5, 0xf5, 0x90, 0xf5, 0xf5, 0xf5, 0xc0, 0xf5, 0xf5, 0xf5, 0x60, 
#endif
};

const lv_img_dsc_t IMG_Sign3 = {
  .header.always_zero = 0,
  .header.w = 10,
  .header.h = 11,
  .data_size = 110 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .data = IMG_Sign3_map,
};
