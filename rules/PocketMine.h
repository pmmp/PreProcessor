
#include <rules/Binary.h>

#define COMPILE 1
#undef __FILE__
#undef __LINE__

#define World::chunkHash(chunkX, chunkZ) (((chunkX) & 0xFFFFFFFF) << 32) | ((chunkZ) & 0xFFFFFFFF)
#define World::blockHash(x, y, z) (((x) & 0x7ffffff) << 37) | ((((y) - World::HALF_Y_MAX) & 0x3ff) << 27) | ((z) & 0x7ffffff)
#define World::getXZ(hash, chunkX, chunkZ) chunkX = (hash >> 32); chunkZ = (hash & 0xFFFFFFFF) << 32 >> 32
#define World::getBlockXYZ(hash, X, Y, Z) X = (hash) >> 37; Y = ((hash) << 27 >> 54) + World::HALF_Y_MAX; Z = (hash) << 37 >> 37
