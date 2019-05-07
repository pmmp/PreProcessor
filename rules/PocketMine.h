
#include <rules/Binary.h>

#define COMPILE 1
#undef __FILE__
#undef __LINE__

#define World::chunkHash(chunkX, chunkZ) (((chunkX) & 0xFFFFFFFF) << 32) | ((chunkZ) & 0xFFFFFFFF)
#define World::blockHash(x, y, z) (((x) & 0xFFFFFFF) << 36) | (((y) & 0xff) << 28) | ((z) & 0xFFFFFFF)
#define World::getXZ(hash, chunkX, chunkZ) chunkX = (hash >> 32); chunkZ = (hash & 0xFFFFFFFF) << 32 >> 32
#define World::getBlockXYZ(hash, X, Y, Z) X = (hash >> 36); Y = ((hash >> 28) & 0xff); Z = (hash & 0xFFFFFFF) << 36 >> 36
