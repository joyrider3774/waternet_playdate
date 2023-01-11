#ifndef helperfuncs_h
#define helperfuncs_h

#include "pd_api.h"

void setBlockTilesAsBackground(void);
void set_bkg_tile_xy(int ax, int ay, int tile);
void set_bkg_data(LCDBitmapTable* tiles);
void set_bkg_tiles(int ax, int ay, LCDBitmap* tiles);
void setInverted(int inverted);
#endif