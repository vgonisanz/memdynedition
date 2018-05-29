#ifndef __PLAYERCRC32_H
#define __PLAYERCRC32_H

#include <stdint.h>

#include "player.h"
#include "securizer.h"

namespace memdynedition
{

class PlayerCRC32 : public Player
{
public:
    PlayerCRC32();

    void useBomb() override;
    void dropCoin() override;
private:
    Securizer _secItems;

    bool checkIntegrity() override;
};

}   /* namespace memdynedition */

#endif /* __PLAYERCRC32_H */
