#include "commonvars.h"
#include "helperfuncs.h"
#include "pd_api.h"
#include "savestate.h"


LCDBitmapTable* currentTiles;

void set_bkg_tile_xy(int ax, int ay, int tile)
{
    LCDBitmap* bitmap = pd->graphics->getTableBitmap(currentTiles, tile);
    if (bitmap)
    {
        pd->graphics->drawBitmap(bitmap, ax* tileSize, ay* tileSize, kBitmapUnflipped);
    }
}

void set_bkg_data(LCDBitmapTable* tiles)
{
    currentTiles = tiles;
}

void set_bkg_tiles(int ax, int ay, LCDBitmap* bitmap)
{
    pd->graphics->drawBitmap(bitmap, ax, ay, kBitmapUnflipped);
}

void setBlockTilesAsBackground(void)
{
    switch (skinSaveState())
    {
        case 1:
            set_bkg_data(blockTiles2);
            break;
        case 2:
            set_bkg_data(blockTiles3);
            break;
        case 3:
            set_bkg_data(blockTiles4);
            break;
        case 4:
            set_bkg_data(blockTiles5);
            break;
        case 5:
            set_bkg_data(blockTiles6);
            break;
        case 6:
            set_bkg_data(blockTiles7);
            break;
        case 7:
            set_bkg_data(blockTiles8);
            break;
        case 8:
            set_bkg_data(blockTiles9);
            break;
        case 9:
            set_bkg_data(blockTiles10);
            break;
        case 10:
            set_bkg_data(blockTiles11);
            break;
        case 11:
            set_bkg_data(blockTiles12);
            break;
        case 12:
            set_bkg_data(blockTiles13);
            break;
        case 13:
            set_bkg_data(blockTiles14);
            break;
        case 14:
            set_bkg_data(blockTiles15);
            break;
        case 15:
            set_bkg_data(blockTiles16);
            break;
        case 16:
            set_bkg_data(blockTiles17);
            break;
        case 17:
            set_bkg_data(blockTiles18);
            break;
        case 18:
            set_bkg_data(blockTiles19);
            break;
        case 19:
            set_bkg_data(blockTiles20);
            break;
        case 20:
            set_bkg_data(blockTiles21);
            break;
        case 21:
            set_bkg_data(blockTiles22);
            break;
        case 22:
            set_bkg_data(blockTiles23);
            break;
        case 23:
            set_bkg_data(blockTiles24);
            break;
        default:
            set_bkg_data(blockTiles);
            break;
    }
}

void setInverted(int inverted)
{
    pd->display->setInverted(inverted);
    pd->system->setMenuItemValue(InvertedColorsOptionMenuItem, isInvertedSaveState());
}