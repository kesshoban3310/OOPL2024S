#ifndef CHARACTER_ATTRIBUTE_HPP
#define CHARACTER_ATTRIBUTE_HPP
/*
 * This class is an object pool for every character, including enemy and rock
 * man. Including and inherit the attribute you want.
 */
class Attackable {
public:
    virtual void attack() = 0;
};

class Moveable {
public:
    virtual void move() = 0;
};

#endif
