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

    void useBomb();
    void dropCoin();
private:
    Securizer _secItems;

    bool checkIntegrity();
};

}   /* namespace memdynedition */

#endif /* __PLAYERCRC32_H */
