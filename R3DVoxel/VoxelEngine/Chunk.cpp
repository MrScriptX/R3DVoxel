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
				m_blocktypes.at(x + y * Voxel::CHUNK_SIZE + z * Voxel::CHUNK_SIZE_SQR) = TBlock::DEFAULT;
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
					bool x_neg = false;
					if (x > 0)
					{
						x_neg = m_active_voxel[(x - 1) + y * Voxel::CHUNK_SIZE + z * Voxel::CHUNK_SIZE_SQR];
					}

					bool x_pos = false;
					if (x < Voxel::CHUNK_SIZE - 1)
					{
						x_pos = m_active_voxel[(x + 1) + y * Voxel::CHUNK_SIZE + z * Voxel::CHUNK_SIZE_SQR];
					}

					bool y_neg = false;
					if (y > 0)
					{
						y_neg = m_active_voxel[x + (y - 1) * Voxel::CHUNK_SIZE + z * Voxel::CHUNK_SIZE_SQR];
					}

					bool y_pos = false;
					if (y < Voxel::CHUNK_SIZE - 1)
					{
						y_pos = m_active_voxel[x + (y + 1) * Voxel::CHUNK_SIZE + z * Voxel::CHUNK_SIZE_SQR];
					}

					bool z_neg = false;
					if (z > 0)
					{
						z_neg = m_active_voxel[x + y * Voxel::CHUNK_SIZE + (z - 1) * Voxel::CHUNK_SIZE_SQR];
					}

					bool z_pos = false;
					if (z < Voxel::CHUNK_SIZE - 1)
					{
						z_pos = m_active_voxel[x + y * Voxel::CHUNK_SIZE + (z + 1) * Voxel::CHUNK_SIZE_SQR];
					}

					CreateCube(mesh, x_neg, x_pos, y_neg, y_pos, z_neg, z_pos, x, y, z);
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

void Chunk::CreateCube(Geometry& mesh, const bool x_neg, const bool x_pos, const bool y_neg, const bool y_pos, const bool z_neg, const bool z_pos, uint32_t x, uint32_t y, uint32_t z)
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
	glm::vec3 color;
	switch (m_blocktypes[x + y * Voxel::CHUNK_SIZE + z * Voxel::CHUNK_SIZE_SQR])
	{
	case TBlock::DEFAULT:
		color = { 1.0f, 1.0f, 1.0f };
		break;
	default:
		color = { 1.0f, 0.3f, 0.0f };
		break;
	}

	//declare vertex
	uint32_t index_0 = mesh.addVertex(p1, color, t1);
	uint32_t index_1 = mesh.addVertex(p2, color, t2);
	uint32_t index_2 = mesh.addVertex(p3, color, t3);
	uint32_t index_3 = mesh.addVertex(p4, color, t4);
	uint32_t index_4 = mesh.addVertex(p5, color, t1);
	uint32_t index_5 = mesh.addVertex(p6, color, t2);
	uint32_t index_6 = mesh.addVertex(p7, color, t3);
	uint32_t index_7 = mesh.addVertex(p8, color, t4);

	//front
	if (!z_neg)
	{
		mesh.addIndices(index_0, index_2, index_1);
		mesh.addIndices(index_1, index_2, index_3);
	}

	//back
	if (!z_pos)
	{
		mesh.addIndices(index_5, index_7, index_4);
		mesh.addIndices(index_4, index_7, index_6);
	}

	//right
	if (!x_pos)
	{
		mesh.addIndices(index_1, index_3, index_5);
		mesh.addIndices(index_5, index_3, index_7);
	}

	//left
	if (!x_neg)
	{
		mesh.addIndices(index_4, index_6, index_0);
		mesh.addIndices(index_0, index_6, index_2);
	}

	//top
	if (!y_pos)
	{
		mesh.addIndices(index_2, index_6, index_3);
		mesh.addIndices(index_3, index_6, index_7);
	}

	//bot
	if (!y_neg)
	{
		mesh.addIndices(index_4, index_0, index_5);
		mesh.addIndices(index_5, index_0, index_1);
	}
}
