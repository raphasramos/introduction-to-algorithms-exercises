#include "TileSet.hpp"
#include "Vec2.hpp"
#include <iostream>
using std::cout;

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) : tileWidth(tileWidth), tileHeight(tileHeight) {
    tileSet.open(file);

    int totalHeight = tileSet.GetHeight();
    int totalWidth = tileSet.GetWidth();

    columns = totalWidth / tileWidth;
    rows = totalHeight / tileHeight;

}

void TileSet::Render(unsigned int index, float x, float y) {

    if (index < columns * rows && (index >> 31) == 0) {
        int row = index / columns;
        int col = index % columns;
        Vec2 tileLT = Vec2(tileWidth * col, tileHeight * row);

        tileSet.SetClip(tileLT.x, tileLT.y, tileWidth, tileHeight);
        tileSet.Render(x, y, 0);

    } else {
        if(index != (unsigned int)-1)
            cout << "Invalid tile index " << index << "!" << std::endl;
    }

}

int TileSet::getTileWidth() {
    return tileWidth;
}

int TileSet::getTileHeight() {
    return tileHeight;
}
