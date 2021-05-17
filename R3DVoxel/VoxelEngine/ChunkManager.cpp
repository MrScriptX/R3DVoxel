#include "ChunkManager.h"

ChunkManager::ChunkManager(std::shared_ptr<GameObject> pworld, std::shared_ptr<Material> p_world_mat) : mp_world(pworld), mp_world_mat(p_world_mat)
{
	m_render_position = { 0, 0, 0 };
	m_render_max = { m_load_radius , m_load_radius, m_load_radius };
	m_render_min = { 0, 0, 0 };
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::InitWorld()
{
	for (uint32_t x = 0; x < m_load_radius; x++)
	{
		for (uint32_t z = 0; z < m_load_radius; z++)
		{
			CreateNewChunk(x, 0, z);
		}
	}
}

void ChunkManager::UpdateWorld(std::shared_ptr<Scene> p_scene, std::shared_ptr<Camera> p_camera)
{
	if (p_camera->GetPosition().x > m_render_position.x + Voxel::CHUNK_SIZE)
	{
		m_render_position.x = p_camera->GetPosition().x;

		for (int32_t z = m_render_min.z; z < m_render_max.z; z++)
		{
			CreateNewChunk(m_render_max.x, 0, z);
			DestroyChunk(m_render_min.x, 0, z);
		}

		m_render_min.x = m_render_min.x + 1;
		m_render_max.x = m_render_max.x + 1;

		p_scene->ToUpdate();
	}
}

void ChunkManager::CreateNewChunk(int32_t x, int32_t y, int32_t z)
{
	ChunkKey key = { x, y, z };

	std::unique_ptr<Chunk> p_chunk = std::make_unique<Chunk>(x, y, z);
	p_chunk->CreateChunk(mp_world, mp_world_mat);

	m_chunk_map.insert(std::pair<ChunkKey, std::unique_ptr<Chunk>>(key, std::move(p_chunk)));
}

void ChunkManager::DestroyChunk(const int32_t x, const int32_t y, const int32_t z)
{
	ChunkKey key = { x, y, z };

	m_chunk_map.at(key)->DeleteChunk(mp_world);

	m_chunk_map.erase(key);
}
