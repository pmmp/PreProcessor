
#include <rules/Binary.h>

#define COMPILE 1
#undef __FILE__
#undef __LINE__

#define World::chunkHash(chunkX, chunkZ) morton2d_encode((chunkX), (chunkZ))
#define World::getXZ(hash, chunkX, chunkZ) [chunkX, chunkZ] = morton2d_decode(hash)
