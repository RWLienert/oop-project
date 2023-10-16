#include "Onager.h"
#include "Enemy.h"
#include "math.h"
using namespace std;

Onager::Onager(int width, int height, string imgDirectory){
    this->width = width;
    this->height = height;
    texture = new Texture();
    sprite = new Sprite();
    if (!texture->loadFromFile(imgDirectory)){
        cout << "Onager sprite was unable to load" << endl;
    }
    texture->setSmooth(true);
    sprite->setTexture(*texture);
    sprite->setOrigin(width/2,height/2);
    sprite->scale(1.4,1.4);
    alive = false;
    srand(time(NULL));
}

void Onager::movePath(Vector2f castlePosition){
    this->castlePosition = castlePosition;
    Vector2f direction;
    direction.x = castlePosition.x- position.x;
    direction.y = castlePosition.y - position.y;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 300) {
        direction.x /= length;
        direction.y /= length;
        speed = 5;
        sprite->move(direction.x / speed, direction.y / speed);
        position = Vector2f(sprite->getPosition().x, sprite->getPosition().y);
    }
    float angleRadians = atan2(direction.y, direction.x);
    float angleDegrees = (angleRadians * 180 / 3.14159265)+180;
    sprite->setRotation(angleDegrees);

}
void Onager::draw(RenderWindow* win){
    if (alive == true){
        win->draw(*sprite);
        position = Vector2f(sprite->getPosition().x, sprite->getPosition().y);
    }
}

void Onager::spawn(int winX, int winY){
    int side = rand() % 4;

    int onagerRandX, onagerRandY;
    switch (side) {
        case 0:
            onagerRandX = rand() % winX;
            onagerRandY = -50;
            break;
        case 1:
            onagerRandX = winX + 50;
            onagerRandY = rand() % winY;
            break;
        case 2:
            onagerRandX = rand() % winX;
            onagerRandY = winY + 50;
            break;
        case 3:
            onagerRandX = -50;
            onagerRandY = rand() % winY;
            break;
    }

    sprite->setPosition(static_cast<float>(onagerRandX), static_cast<float>(onagerRandY));
    position = Vector2f(sprite->getPosition().x, sprite->getPosition().y);
    alive = true;
}

Onager::~Onager(){
    delete sprite;
}