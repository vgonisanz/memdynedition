#ifndef __PLAYER_H
#define __PLAYER_H

#include <stdint.h>
#include "securizer.h"

namespace memdynedition
{

class Player
{
public:
    Player();
    ~Player() = default;

    struct Items
    {
        uint32_t coins;
        uint32_t bombs;
        uint32_t keys;

        Items():
        coins(10),
        bombs(3),
        keys(1) {}
    };

    struct Stats
    {
        uint8_t health;

        uint8_t strenght;
        uint8_t dexterity;
        uint8_t constitution;
        uint8_t defense;
        uint8_t charisma;
        uint8_t wisdom;
        uint8_t willpower;
        uint8_t perception;
        uint8_t luck;

        Stats():
        health(100),

        strenght(10),
        dexterity(10),
        constitution(10),
        defense(10),
        charisma(10),
        wisdom(10),
        willpower(10),
        perception(10),
        luck(10) {}
    };

    void printItems();
    void printStats();
    void useBomb();
private:
    Items _items;
    Securizer _secItems;
    Stats _stats;
};

}   /* namespace memdynedition */

#endif /* __PLAYER_H */
