use pocketmine\utils\Binary;

#include <rules/BinaryIO.h>

#define $this->reset() $this->buffer = chr(static::NETWORK_ID); $this->offset = 0
