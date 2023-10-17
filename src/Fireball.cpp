#include "Fireball.h"
#include <cmath>

Fireball::Fireball(string imgDirectory){
    // assign sprite and positioning
    texture = new Texture();
    sprite = new Sprite();
    if (!texture->loadFromFile(imgDirectory)){
        cout << "Fireball Texture didn't load" << endl;
    }
    texture->setSmooth(true);
    sprite->setTexture(*texture);
    sprite->setOrigin(21/2,21/2);
    alive = false;
    firePos.x = -100;
    firePos.y = -100;
}

void Fireball::move(float power, Vector2f startPos, Vector2f direction){
    // distance travelled of the fireball
    Vector2f currentPosition = sprite->getPosition();

    // Calculate the distance travelled by the fireball
    float distanceX = currentPosition.x - startPos.x;
    float distanceY = currentPosition.y - startPos.y;

    float travelledDistance = sqrt(distanceX * distanceX + distanceY * distanceY);

    // assigns power
    float distanceScale = 2.5;
    // assigns size of image
    float imgScale = 1;
    if (travelledDistance < distanceScale*power){
        // calculates the required change in coordinates to move the fireball
        float changeX = speed*-direction.x;
        float changeY = speed*-direction.y;
        sprite->move(changeX,changeY);
        // for majority of the path, the image increases in scale followed by a decrease
        if (travelledDistance < 2*(distanceScale*power)/3){
            imgScale += 0.005;
            sprite->scale(imgScale,imgScale);
        }
        else{
            imgScale -= 0.01;
            sprite->scale(imgScale,imgScale);
        }
    }
    else{
        // assigns fireball position to calculate collision and removes the image once the path has been completed
        firePos = Vector2f(sprite->getPosition().x,sprite->getPosition().y);
        alive = false;
    }
}

bool Fireball::isFired(){
    return alive;
}

void Fireball::reload(){
    alive = false;
}

void Fireball::draw(RenderWindow* win){
    win->draw(*sprite);
}

void Fireball::spawn(int endX, int endY){
    sprite->setPosition(endX,endY);
    alive = true;
}

Fireball::~Fireball(){
    delete this->sprite;
}