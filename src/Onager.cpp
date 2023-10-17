#include "Onager.h"
#include "Enemy.h"
#include "math.h"
using namespace std;

Onager::Onager(int width, int height, string imgDirectory){
    // initialise sprite and positioning
    this->width = width;
    this->height = height;
    this->fireDirection = Vector2f(0,0);
    for (int i = 0; i < 3; i++){
        ranShoot[i] = 0;
    }
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
    // set fireball array
    onagerFireball = new Fireball*[1];
    for (int i = 0; i < 1; i++){
        onagerFireball[i] = new Fireball("resources/fireball.png");
    }
    inPosition = false;
}

void Onager::draw(RenderWindow* win){
    if (alive == true){
        win->draw(*sprite);
        position = Vector2f(sprite->getPosition().x, sprite->getPosition().y);
        for (int i = 0; i < 1; i++){
            if (onagerFireball[i]->isFired()){
                onagerFireball[i]->draw(win);
                onagerFireball[i]->move(100,Vector2f(position.x,position.y),fireDirection);     
            }
        }
        
    }
}

void Onager::spawn(int winX, int winY){
    // spawns randomly outside of the window
    int side = rand() % 4;
    for(int i = 0; i < 3; i++){
        ranShoot[i] = rand() % (59-0+1);
        cout << ranShoot[i] << endl;
    }
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

void Onager::movePath(Vector2f castlePosition){
    // calculates required direction of movement
    this->castlePosition = castlePosition;
    Vector2f direction;
    direction.x = castlePosition.x- position.x;
    direction.y = castlePosition.y - position.y;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    // stops when it gets 300 pixels from the castle
    if (length > 300) {
        direction.x /= length;
        direction.y /= length;
        fireDirection = Vector2f(-direction.x,-direction.y);
        speed = 5;
        sprite->move(direction.x / speed, direction.y / speed);
        position = Vector2f(sprite->getPosition().x, sprite->getPosition().y);
    } else {
        inPosition = true;
    }

    // rotates sprite towards castle
    float angleRadians = atan2(direction.y, direction.x);
    float angleDegrees = (angleRadians * 180 / 3.14159265)+180;
    sprite->setRotation(angleDegrees);

}

void Onager::fire(){
    for (int i = 0; i < 1; i++){
        if (!onagerFireball[i]->isFired()){
            onagerFireball[i]->spawn(sprite->getPosition().x, sprite->getPosition().y);
            break;
        }
    }
}
void Onager::reload(){
    for (int i = 0; i < 1; i++){
        if (onagerFireball[i]->isFired()){
            onagerFireball[i]->reload();
        }
    }
}

int* Onager::getRand(){
    return ranShoot;
}


bool Onager::getInPosition(){
    return inPosition;
}

Fireball** Onager::getOnagerFireball(){
    return onagerFireball;
}

Onager::~Onager(){
    delete sprite;
    delete [] this->onagerFireball;
}