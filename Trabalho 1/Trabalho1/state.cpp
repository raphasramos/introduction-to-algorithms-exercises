#include "state.hpp"
#include "game.hpp"

State::State() : quitRequested(false), bg("img/ocean.jpg") {

}

State::~State() {

}

void State::Update(float dt) {

    if(SDL_QuitRequested())
        quitRequested = true;

}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Render() {
    bg.Render(0,0);
}

Sprite State::getBg(){
    return bg;
}


