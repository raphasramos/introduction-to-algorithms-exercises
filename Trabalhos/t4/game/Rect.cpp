//
// Created by jasf on 3/23/16.
//

#include "Rect.h"

Rect::Rect(float x, float y, float h, float w): x(x), y(y), h(h), w(w){

}

Rect::Rect(): x(-1), y(-1), h(-1), w(-1){

}

Vec2 Rect::getTopLeft(){
    return Vec2(x,y);
}

std::vector<Vec2> Rect::getCorners() {
    if(corners.empty()) {
        auto tl = getTopLeft();
        corners.push_back(tl);
        //BL
        corners.push_back(tl + Vec2(0, h));
        //BR
        corners.push_back(tl + Vec2(w, 0) + Vec2(0, h));
        //TR
        corners.push_back(tl + Vec2(w, 0));

    }
    return corners;
}
Vec2 Rect::getCenter() const{
    return Vec2(x + w/2.0, y + h/2.0);
}

double Rect::distanceFromRectCenters(const Rect & A, const Rect & B){
    return Vec2::distanceBetweenPoints(A.getCenter(), B.getCenter());
}

bool Rect::isPointInside(const Vec2 & p) {
    auto vertices = getCorners();
    auto LT = vertices[0];
    auto RB = vertices[2];

    float xmin = std::min(LT.x, RB.x);
    float xmax = std::max(LT.x, RB.x);

    float ymin = std::min(LT.y, RB.y);
    float ymax = std::max(LT.y, RB.y);

    // works for axis aligned rectangle
    if (p.x < xmin || p.x > xmax || p.y < ymin || p.y > ymax) {
        return false;
    }
    return true;

}

Rect::Rect(Vec2 LT, float h, float w) : x(LT.x), y(LT.y), h(h), w(w) {

}

bool Rect::isPointInside(const float &x, const float &y) {
    return isPointInside(Vec2(x,y));
}
