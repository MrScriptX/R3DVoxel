#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <map>
#include <utility>

#include "Chunk.h"

struct ChunkKey
{
	int32_t x;
	int32_t y;
	int32_t z;
};

inline bool const operator==(const ChunkKey& l, const ChunkKey& r)
{
	return l.x == r.x && l.y == r.y && l.z == r.z;
}

inline bool const operator<(const ChunkKey& l, const ChunkKey& r)
{
	if (l.x < r.x)  return true;
	if (l.x > r.x)  return false;

	if (l.y < r.y)  return true;
	if (l.y > r.y)  return false;

	if (l.z < r.z)  return true;
	if (l.z > r.z)  return false;

	return false;
}

class ChunkManager
{
public:
	ChunkManager(std::shared_ptr<GameObject> pworld, std::shared_ptr<Material> p_world_mat);
	~ChunkManager();

	void InitWorld();
	void UpdateWorld(std::shared_ptr<Scene> p_scene, std::shared_ptr<Camera> p_camera);

	void CreateNewChunk(int32_t x, int32_t y, int32_t z);
	void DestroyChunk(const int32_t x, const int32_t y, const int32_t z);

private:
	std::shared_ptr<GameObject> mp_world;
	std::shared_ptr<Material> mp_world_mat;

	std::map<ChunkKey, std::unique_ptr<Chunk>> m_chunk_map;
	const uint8_t m_load_radius = 1;
	glm::vec3 m_render_position;

	glm::vec3 m_render_max;
	glm::vec3 m_render_min;
};

#endif