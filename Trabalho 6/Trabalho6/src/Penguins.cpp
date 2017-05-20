#include "Penguins.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include <SDL.h>

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define KEY_LOW_CASE_W SDLK_w
#define KEY_LOW_CASE_S SDLK_s
#define KEY_LOW_CASE_A SDLK_a
#define KEY_LOW_CASE_D SDLK_d
#define SPACE_BAR SDLK_SPACE

float Penguins::MAX_LIN_SPEED = 400.0;
float Penguins::MIN_LIN_SPEED = -400.0;
Penguins *Penguins::player;

Penguins::Penguins(float x, float y) :
        bodySp("img/penguin.png"), cannonSp("img/cubngun.png") {

    hp = 100;
    linearSpeed = 0.0;
    cannonSp.setCenter(Vec2(53, 22));
    int width = bodySp.GetWidth();
    int height = bodySp.GetHeight();
    pos = Vec2(x, y);
    rotation = 0;
    speed = Vec2::getVec2FromPolar(0, 0);
    penguint_LT_displacement = -0.5 * Vec2(width, height);
    center_LT_displacement = penguint_LT_displacement;
    box = Rect(Vec2(x, y) + penguint_LT_displacement, height, width);
    Penguins::player = this;
    width = cannonSp.GetWidth();
    height = cannonSp.GetHeight();
    cannon_center_LT_displacement = -0.5 * Vec2(width, height);
}

Penguins::~Penguins() {
    Penguins::player = nullptr;
}

void Penguins::update(float dt) {
    coolDownTimer.update(dt);

    auto im = InputManager::getInstance();

    float a = 0.0, w = 0.0;
    if (im.isKeyDown(KEY_LOW_CASE_W))
        a = +100;
    if (im.isKeyDown(KEY_LOW_CASE_S))
        a = -100;
    if (im.isKeyDown(KEY_LOW_CASE_A))
        w = +10;
    if (im.isKeyDown(KEY_LOW_CASE_D))
        w = -10;
    linearSpeed += a * dt;
    linearSpeed = max(linearSpeed, Penguins::MIN_LIN_SPEED);
    linearSpeed = min(linearSpeed, Penguins::MAX_LIN_SPEED);

    rotation += w * dt;
    box.setRotation(rotation);

    if (abs(linearSpeed) > 5)
        pos += Vec2::getVec2FromPolar(linearSpeed, rotation) * dt;

    box.setLT(pos + center_LT_displacement);

    Vec2 mousePos = InputManager::getInstance().getMouse();

    cannonAngle = (mousePos - getCenterPos()).ang_rad();

    if (im.mousePress(LEFT_MOUSE_BUTTON) && coolDownTimer.get() > 0.25) {
        shoot();
        coolDownTimer.restart();
    }
}

void Penguins::render() {
    Vec2 left_top = pos + penguint_LT_displacement - Camera::getPos(Camera::PLAYER_GROUND_VIEW);
    bodySp.Render(left_top.x, left_top.y, rotation);

    Vec2 cannonCenter =
            pos + Vec2(-5, 0).rotated(rotation) + cannon_center_LT_displacement -
            Camera::getPos(Camera::PLAYER_GROUND_VIEW);

    cannonSp.Render(cannonCenter.x, cannonCenter.y, cannonAngle);
}

bool Penguins::isDead() {
    return hp <= 0;
}

void Penguins::shoot() {
    Vec2 c = pos + Vec2(53, 0) + Vec2::getVec2FromPolar(65, cannonAngle);
    Bullet *b = new Bullet(c.x, c.y, cannonAngle, 200 + linearSpeed, 1000, "img/penguinbullet.png", 0.2, 4, false);

    Game::GetInstance().GetState().AddObject(b);
}

void Penguins::notifyCollision(GameObject &other) {

    if (other.is("Bullet") && ((Bullet &) other).getTargetsPlayer())
        damage(10);
}

bool Penguins::is(std::string type) {
    return type == "Penguins";
}

void Penguins::damage(int dm) {
    hp -= dm;
    if (isDead()) {
        Camera::Unfollow();

        float step = 0.05;
        int frameCount = 5;
        int repeat = 3;

        Game::GetInstance().GetState().AddObject(
                new Animation(pos.x, pos.y, 0, "img/penguindeath.png", repeat*step*frameCount, true, frameCount, step));
    }
}
