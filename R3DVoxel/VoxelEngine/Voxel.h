#ifndef VOXEL_H
#define VOXEL_H

#include <memory>

namespace Voxel
{
	constexpr int32_t CHUNK_SIZE = 16;
	constexpr int32_t CHUNK_SIZE_SQR = CHUNK_SIZE * CHUNK_SIZE;
	constexpr int32_t CHUNK_SIZE_CUBE = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

	constexpr float VOXEL_SIZE = 0.5f;
}


#endif