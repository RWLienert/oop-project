#include "Ram.h"

Ram::Ram(int width, int height, string imgDirectory){
    this->width = width;
    this->height = height;
    texture = new Texture();
    sprite = new Sprite();
    if (!texture->loadFromFile(imgDirectory)){
        cout << "ram sprite was unable to load" << endl;
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
    int ramRandX = rand() % (winX - 20);
    int ramRandY = rand() % (winY - 20);
    sprite->rotate(-50);
    sprite->setPosition(static_cast<float>(ramRandX), static_cast<float>(ramRandY));
    position = Vector2f(sprite->getPosition().x, sprite->getPosition().y);
    alive = true;
}

void Ram::movePath(Vector2f castlePosition){
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

}

Ram::~Ram(){
    delete sprite;
}