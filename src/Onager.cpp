#include "Onager.h"

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

void Onager::draw(RenderWindow* win){
    if (alive == true){
        win->draw(*sprite);
        position = Vector2f(sprite->getPosition().x, sprite->getPosition().y);
    }
}

void Onager::spawn(int winX, int winY){
    int onagerRandX = rand() % (winX - 20);
    int onagerRandY = rand() % (winY - 20);
    sprite->setPosition(static_cast<float>(onagerRandX), static_cast<float>(onagerRandY));
    position = Vector2f(sprite->getPosition().x, sprite->getPosition().y);
    alive = true;
}

void Onager::movePath(Vector2f castlePosition){
    this->castlePosition = castlePosition;
    Vector2f direction;
    direction.x = castlePosition.x - position.x;
    direction.y = castlePosition.y - position.y;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    direction.x /= length;
    direction.y /= length;
    speed = 5;
    sprite->move(direction.x/speed, direction.y/speed);
    position = Vector2f(sprite->getPosition().x, sprite->getPosition().y);

}

Onager::~Onager(){
    delete sprite;
}