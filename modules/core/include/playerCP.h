#ifndef __PLAYERCP_H
#define __PLAYERCP_H

#include <stdint.h>

#include "player.h"
#include "securizerCP.h"

namespace memdynedition
{

class PlayerCP : public Player
{
public:
    PlayerCP();

    void useBomb() override;
    void dropCoin() override;
private:
    SecurizerCP _secItems;
    
    bool checkIntegrity() override;
};

}   /* namespace memdynedition */

#endif /* __PLAYERCP_H */
