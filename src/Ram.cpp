#include "Ram.h"

Ram::Ram(int width, int height, string imgDirectory){
    // initialise sprite and positioning
    this->width = width;
    this->height = height;
    texture = new Texture();
    sprite = new Sprite();
    if (!texture->loadFromFile(imgDirectory)){
        cout << "Ram sprite was unable to load" << endl;
    }
    texture->setSmooth(true);
    sprite->setTexture(*texture);
    sprite->setOrigin(width/2,height/2);
    sprite->scale(1.4,1.4);

    alive = false;
    srand(time(NULL));
}

void Ram::draw(RenderWindow* win){
    if (alive == true){
        win->draw(*sprite);
        position = Vector2f(sprite->getPosition().x, sprite->getPosition().y);
    }
}

void Ram::spawn(int winX, int winY){
    // spawns ram randomly outside of the window
    int side = rand() % 4;

    int ramRandX, ramRandY;
    switch (side) {
        case 0:
            ramRandX = rand() % winX;
            ramRandY = -50;
            break;
        case 1:
            ramRandX = winX + 50;
            ramRandY = rand() % winY;
            break;
        case 2:
            ramRandX = rand() % winX;
            ramRandY = winY + 50;
            break;
        case 3:
            ramRandX = -50;
            ramRandY = rand() % winY;
            break;
    }

    sprite->setPosition(static_cast<float>(ramRandX), static_cast<float>(ramRandY));
    position = Vector2f(sprite->getPosition().x, sprite->getPosition().y);
    alive = true;
}

void Ram::movePath(Vector2f castlePosition){
    // calculates required direction of movement
    this->castlePosition = castlePosition;
    Vector2f direction;
    direction.x = castlePosition.x - position.x;
    direction.y = castlePosition.y - position.y;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    direction.x /= length;
    direction.y /= length;

    speed = 4;
    sprite->move(direction.x/speed, direction.y/speed);
    position = Vector2f(sprite->getPosition().x, sprite->getPosition().y);

    // rotates the sprite towards castle
    float angleRadians = atan2(direction.y, direction.x);
    float angleDegrees = (angleRadians * 180 / 3.14159265)+180;

    sprite->setRotation(angleDegrees);

}

Ram::~Ram(){
    delete sprite;
}