#ifndef __PLAYERANTICP_H
#define __PLAYERANTICP_H

#include <stdint.h>

#include "player.h"
#include "securizerAntiCP.h"


namespace memdynedition
{

class PlayerAntiCP : public Player
{
public:
    PlayerAntiCP();

    void useBomb() override;
    void dropCoin() override;
private:
    SecurizerAntiCP _secItems;

    bool checkIntegrity() override;
};

}   /* namespace memdynedition */

#endif /* __PLAYERANTICP_H */
