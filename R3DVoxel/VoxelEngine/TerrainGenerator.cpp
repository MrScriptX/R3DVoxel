#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator()
{
}

TerrainGenerator::~TerrainGenerator()
{
}

std::unique_ptr<Chunk> TerrainGenerator::SetupSphere(const int32_t posx, const int32_t posy, const int32_t posz)
{
    std::unique_ptr<Chunk> p_chunk = std::make_unique<Chunk>(posx, posy, posz);

	for (int32_t x = 0; x < Voxel::CHUNK_SIZE; x++)
	{
		for (int32_t y = 0; y < Voxel::CHUNK_SIZE; y++)
		{
			for (int32_t z = 0; z < Voxel::CHUNK_SIZE; z++)
			{
				p_chunk->SetVoxel(x, y, z);
				p_chunk->SetBlockType(x, y, z, TBlock::DEFAULT);

				//m_active_voxel.flip(x + y * Voxel::CHUNK_SIZE + z * Voxel::CHUNK_SIZE_SQR);
				//m_blocktypes.at(x + y * Voxel::CHUNK_SIZE + z * Voxel::CHUNK_SIZE_SQR) = TBlock::DEFAULT;
			}
		}
	}

    return std::move(p_chunk);
}
