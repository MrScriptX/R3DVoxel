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
				if (std::sqrt((x - Voxel::CHUNK_SIZE / 2) * (x - Voxel::CHUNK_SIZE / 2) + (y - Voxel::CHUNK_SIZE / 2) * (y - Voxel::CHUNK_SIZE / 2) + (z - Voxel::CHUNK_SIZE / 2) * (z - Voxel::CHUNK_SIZE / 2)) < Voxel::CHUNK_SIZE / 2)
				{
					p_chunk->SetVoxel(x, y, z);
				}
				
				p_chunk->SetBlockType(x, y, z, TBlock::DEFAULT);
			}
		}
	}

    return std::move(p_chunk);
}

std::unique_ptr<Chunk> TerrainGenerator::SetupWorld(const int32_t posx, const int32_t posy, const int32_t posz)
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
			}
		}
	}

	return std::move(p_chunk);
}