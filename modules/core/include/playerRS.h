#ifndef __PLAYERRS_H
#define __PLAYERRS_H

#include <stdint.h>

#include "player.h"

namespace memdynedition
{

class SecurizerRS;

class PlayerRS : public Player
{
public:
    PlayerRS();

    void useBomb() override;
    void dropCoin() override;
private:
    SecurizerRS* _secItems;

    bool checkIntegrity() override;
};

}   /* namespace memdynedition */

#endif /* __PLAYERRS_H */
