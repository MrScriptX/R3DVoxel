#include "Chunk.h"

Chunk::Chunk(const int32_t posx, const int32_t posy, const int32_t posz)
{
	m_position = { posx, posy, posz };
	m_mesh_id = -1;

	for (int32_t x = 0; x < Voxel::CHUNK_SIZE; x++)
	{
		for (int32_t y = 0; y < Voxel::CHUNK_SIZE; y++)
		{
			for (int32_t z = 0; z < Voxel::CHUNK_SIZE; z++)
			{
				m_active_voxel.flip(x + y * Voxel::CHUNK_SIZE + z * Voxel::CHUNK_SIZE_SQR);
			}
		}
	}
}

void Chunk::CreateChunk(std::shared_ptr<GameObject> world, std::shared_ptr<Material> mat)
{
	Geometry mesh;
	for (uint32_t x = 0; x < Voxel::CHUNK_SIZE; x++)
	{
		for (uint32_t y = 0; y < Voxel::CHUNK_SIZE; y++)
		{
			for (uint32_t z = 0; z < Voxel::CHUNK_SIZE; z++)
			{
				if (m_active_voxel[x + y * Voxel::CHUNK_SIZE + z * Voxel::CHUNK_SIZE_SQR])
				{
					//vertex
					glm::vec3 p1(m_position.x * Voxel::CHUNK_SIZE + x - Voxel::VOXEL_SIZE, m_position.y * Voxel::CHUNK_SIZE + y - Voxel::VOXEL_SIZE, m_position.z * Voxel::CHUNK_SIZE + z - Voxel::VOXEL_SIZE);
					glm::vec3 p2(m_position.x * Voxel::CHUNK_SIZE + x + Voxel::VOXEL_SIZE, m_position.y * Voxel::CHUNK_SIZE + y - Voxel::VOXEL_SIZE, m_position.z * Voxel::CHUNK_SIZE + z - Voxel::VOXEL_SIZE);
					glm::vec3 p3(m_position.x * Voxel::CHUNK_SIZE + x - Voxel::VOXEL_SIZE, m_position.y * Voxel::CHUNK_SIZE + y + Voxel::VOXEL_SIZE, m_position.z * Voxel::CHUNK_SIZE + z - Voxel::VOXEL_SIZE);
					glm::vec3 p4(m_position.x * Voxel::CHUNK_SIZE + x + Voxel::VOXEL_SIZE, m_position.y * Voxel::CHUNK_SIZE + y + Voxel::VOXEL_SIZE, m_position.z * Voxel::CHUNK_SIZE + z - Voxel::VOXEL_SIZE);
					glm::vec3 p5(m_position.x * Voxel::CHUNK_SIZE + x - Voxel::VOXEL_SIZE, m_position.y * Voxel::CHUNK_SIZE + y - Voxel::VOXEL_SIZE, m_position.z * Voxel::CHUNK_SIZE + z + Voxel::VOXEL_SIZE);
					glm::vec3 p6(m_position.x * Voxel::CHUNK_SIZE + x + Voxel::VOXEL_SIZE, m_position.y * Voxel::CHUNK_SIZE + y - Voxel::VOXEL_SIZE, m_position.z * Voxel::CHUNK_SIZE + z + Voxel::VOXEL_SIZE);
					glm::vec3 p7(m_position.x * Voxel::CHUNK_SIZE + x - Voxel::VOXEL_SIZE, m_position.y * Voxel::CHUNK_SIZE + y + Voxel::VOXEL_SIZE, m_position.z * Voxel::CHUNK_SIZE + z + Voxel::VOXEL_SIZE);
					glm::vec3 p8(m_position.x * Voxel::CHUNK_SIZE + x + Voxel::VOXEL_SIZE, m_position.y * Voxel::CHUNK_SIZE + y + Voxel::VOXEL_SIZE, m_position.z * Voxel::CHUNK_SIZE + z + Voxel::VOXEL_SIZE);

					//texture
					glm::vec2 t1(0.0f, 0.0f);
					glm::vec2 t2(0.0f, 2.0f);
					glm::vec2 t3(2.0f, 0.0f);
					glm::vec2 t4(2.0f, 2.0f);

					//color
					glm::vec3 c1(1.f, 0.f, 0.f);
					glm::vec3 c2(0.f, 1.f, 0.f);
					glm::vec3 c3(0.f, 0.f, 1.f);
					glm::vec3 c4(0.f, 1.f, 0.f);

					//declare vertex
					uint32_t index_0 = mesh.addVertex(p1, c1, t1);
					uint32_t index_1 = mesh.addVertex(p2, c2, t2);
					uint32_t index_2 = mesh.addVertex(p3, c3, t3);
					uint32_t index_3 = mesh.addVertex(p4, c4, t4);
					uint32_t index_4 = mesh.addVertex(p5, c1, t1);
					uint32_t index_5 = mesh.addVertex(p6, c2, t2);
					uint32_t index_6 = mesh.addVertex(p7, c3, t3);
					uint32_t index_7 = mesh.addVertex(p8, c4, t4);

					//front
					mesh.addIndices(index_0, index_2, index_1);
					mesh.addIndices(index_1, index_2, index_3);

					//back
					mesh.addIndices(index_5, index_7, index_4);
					mesh.addIndices(index_4, index_7, index_6);

					//right
					mesh.addIndices(index_1, index_3, index_5);
					mesh.addIndices(index_5, index_3, index_7);

					//left
					mesh.addIndices(index_4, index_6, index_0);
					mesh.addIndices(index_0, index_6, index_2);

					//top
					mesh.addIndices(index_2, index_6, index_3);
					mesh.addIndices(index_3, index_6, index_7);

					//bot
					mesh.addIndices(index_4, index_0, index_5);
					mesh.addIndices(index_5, index_0, index_1);
				}
			}
		}
	}

	m_mesh_id = world->LoadMesh(mesh.vertices, mesh.indices);// get mesh id
	world->bindMatToMesh(m_mesh_id, mat); // <- mesh id
}

void Chunk::UpdateMesh()
{
	
}

void Chunk::DeleteChunk(std::shared_ptr<GameObject> world)
{
	world->RemoveMesh(m_mesh_id); // remove mesh id
}
