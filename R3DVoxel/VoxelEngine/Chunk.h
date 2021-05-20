#ifndef R3DENGINE_CHUNK_H_
#define R3DENGINE_CHUNK_H_

#include <bitset>
#include <Engine.h>

#include "Voxel.h"

class Chunk
{
public:
	Chunk(const int32_t posx, const int32_t posy, const int32_t posz);

	void CreateChunk(std::shared_ptr<GameObject> world, std::shared_ptr<Material> mat);
	void UpdateMesh();
	void DeleteChunk(std::shared_ptr<GameObject> world);

private:
	int32_t m_mesh_id;
	glm::vec3 m_position;

	std::bitset<Voxel::CHUNK_SIZE_CUBE> m_active_voxel;
};

#endif //!R3DENGINE_CHUNK_H_