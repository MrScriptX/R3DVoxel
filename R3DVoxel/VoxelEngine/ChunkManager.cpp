#include "ChunkManager.h"

ChunkManager::ChunkManager(std::shared_ptr<GameObject> pworld, std::shared_ptr<Material> p_world_mat, std::shared_ptr<Camera> p_camera) : mp_world(pworld), mp_world_mat(p_world_mat)
{
	mp_terrain_generator = std::make_unique<TerrainGenerator>();
	m_render_position = p_camera->GetPosition();
	m_render_max = { m_render_position.x + m_load_radius, m_render_position.y + m_load_radius, m_render_position.z + m_load_radius };
	m_render_min = { m_render_position.x - m_load_radius, m_render_position.y - m_load_radius, m_render_position.z - m_load_radius };
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::CreateWorld()
{
	//CreateNewChunk(0, 0, 0);
	for (int32_t x = m_render_min.x; x <= m_render_max.x; x++)
	{
		for (int32_t y = m_render_min.y; y <= m_render_max.y; y++)
		{
			for (int32_t z = m_render_min.z; z <= m_render_max.z; z++)
			{
				CreateNewChunk(x, y, z);
			}
		}
	}
}

void ChunkManager::UpdateWorld(std::shared_ptr<Scene> p_scene, std::shared_ptr<Camera> p_camera)
{
	bool scene_need_update = false;

	if (p_camera->GetPosition().x > m_render_position.x + Voxel::CHUNK_SIZE)
	{
		m_render_position.x = p_camera->GetPosition().x;

		m_render_max.x = m_render_max.x + 1;

		for (int32_t z = m_render_min.z; z <= m_render_max.z; z++)
		{
			for (int32_t y = m_render_min.y; y <= m_render_max.y; y++)
			{
				CreateNewChunk(m_render_max.x, y, z);
				DestroyChunk(m_render_min.x, y, z);
			}
		}

		m_render_min.x = m_render_min.x + 1;

		scene_need_update = true;
	}
	else if (p_camera->GetPosition().x < m_render_position.x - Voxel::CHUNK_SIZE)
	{
		m_render_position.x = p_camera->GetPosition().x;

		m_render_min.x = m_render_min.x - 1;

		for (int32_t z = m_render_min.z; z <= m_render_max.z; z++)
		{
			for (int32_t y = m_render_min.y; y <= m_render_max.y; y++)
			{
				CreateNewChunk(m_render_min.x, y, z);
				DestroyChunk(m_render_max.x, y, z);
			}
		}

		m_render_max.x = m_render_max.x - 1;

		scene_need_update = true;
	}

	if (p_camera->GetPosition().z > m_render_position.z + Voxel::CHUNK_SIZE)
	{
		m_render_position.z = p_camera->GetPosition().z;

		m_render_max.z = m_render_max.z + 1;

		for (int32_t x = m_render_min.x; x <= m_render_max.x; x++)
		{
			for (int32_t y = m_render_min.y; y <= m_render_max.y; y++)
			{
				CreateNewChunk(x, y, m_render_max.z);
				DestroyChunk(x, y, m_render_min.z);
			}
		}

		m_render_min.z = m_render_min.z + 1;

		scene_need_update = true;
	}
	else if (p_camera->GetPosition().z < m_render_position.z - Voxel::CHUNK_SIZE)
	{
		m_render_position.z = p_camera->GetPosition().z;

		m_render_min.z = m_render_min.z - 1;

		for (int32_t x = m_render_min.x; x <= m_render_max.x; x++)
		{
			for (int32_t y = m_render_min.y; y <= m_render_max.y; y++)
			{
				CreateNewChunk(x, y, m_render_min.z);
				DestroyChunk(x, y, m_render_max.z);
			}	
		}

		m_render_max.z = m_render_max.z - 1;

		scene_need_update = true;
	}

	if (scene_need_update)
	{
		p_scene->ToUpdate();
	}
}

void ChunkManager::CreateNewChunk(int32_t x, int32_t y, int32_t z)
{
	ChunkKey key = { x, y, z };

	std::unique_ptr<Chunk> p_chunk = mp_terrain_generator->SetupWorld(x, y, z);
	p_chunk->CreateChunk(m_chunk_map, mp_world, mp_world_mat);

	m_chunk_map.insert(std::pair<ChunkKey, std::unique_ptr<Chunk>>(key, std::move(p_chunk)));
}

void ChunkManager::DestroyChunk(const int32_t x, const int32_t y, const int32_t z)
{
	ChunkKey key = { x, y, z };

	m_chunk_map.at(key)->DeleteChunk(mp_world);

	m_chunk_map.erase(key);
}
