// #includes, using, etc
#include "Mesh.h"
#include "..//dependencies/glCore/gl_core_4_5.h"

//--------------------------------------------------------------------------------------
// Default Destructor.
//--------------------------------------------------------------------------------------
Mesh::~Mesh()
{
	// delete vertex array and buffers
	glDeleteVertexArrays(1, &m_unVAO);
	glDeleteBuffers(1, &m_unVBO);
	glDeleteBuffers(1, &m_unIBO);
}

//--------------------------------------------------------------------------------------
// InitialiseQuad: Initialises the mesh visually as a quad.
//--------------------------------------------------------------------------------------
void Mesh::InitialiseQuad() 
{	
	// check that the mesh is not initialized already.
	assert(m_unVAO == 0);

	// generate buffers.
	glGenBuffers(1, &m_unVBO);
	glGenVertexArrays(1, &m_unVAO);

	// bind vertex array.
	glBindVertexArray(m_unVAO);
	
	// bind vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_unVBO);

	// define 6 vertices for 2 triangles.
	Vertex Vertices[6];

	// set positions.
	Vertices[0].m_v4Position = { -0.5f, 0, 0.5f, 1 };
	Vertices[1].m_v4Position = { 0.5f, 0, 0.5f, 1 };
	Vertices[2].m_v4Position = { -0.5f, 0, -0.5f, 1 };
	Vertices[3].m_v4Position = { -0.5f, 0, -0.5f, 1 };
	Vertices[4].m_v4Position = { 0.5f, 0, 0.5f, 1 };
	Vertices[5].m_v4Position = { 0.5f, 0, -0.5f, 1 };

	// set normals.
	Vertices[0].m_v4Normal = { 0, 1, 0, 0 };
	Vertices[1].m_v4Normal = { 0, 1, 0, 0 };
	Vertices[2].m_v4Normal = { 0, 1, 0, 0 };
	Vertices[3].m_v4Normal = { 0, 1, 0, 0 };
	Vertices[4].m_v4Normal = { 0, 1, 0, 0 };
	Vertices[5].m_v4Normal = { 0, 1, 0, 0 };

	// Set texture coords.
	Vertices[0].m_v4TexCoord = { 0, 1 }; // bottom left
	Vertices[1].m_v4TexCoord = { 1, 1 }; // bottom right
	Vertices[2].m_v4TexCoord = { 0, 0 }; // top left
	Vertices[3].m_v4TexCoord = { 0, 0 }; // top left
	Vertices[4].m_v4TexCoord = { 1, 1 }; // bottom right
	Vertices[5].m_v4TexCoord = { 1, 0 }; // top right

	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), Vertices, GL_STATIC_DRAW);

	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	// enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// quad has 2 triangles
	m_unTriCount = 2;
}

//--------------------------------------------------------------------------------------
// Initialise: Initialises the mesh visually.
//
// Params:
//		unVertexCount: unsigned int for vertex count.
//		kpVertices: const Vertex pointer for vertices.
//		unIndexCount: unsigned int indices index.
//		unpIndices: unsigned int pointer for indices.
//--------------------------------------------------------------------------------------
void Mesh::Initialise(unsigned int unVertexCount, const Vertex* kpVertices, unsigned int unIndexCount, unsigned int* unpIndices)
{
	// assert if VAO is 0
	assert(m_unVAO == 0);
	
	// generate buffers
	glGenBuffers(1, &m_unVBO);
	glGenVertexArrays(1, &m_unVAO);
	
	// bind vertex array aka a mesh wrapper
	glBindVertexArray(m_unVAO);
	
	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_unVBO);
	
	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, unVertexCount * sizeof(Vertex), kpVertices, GL_STATIC_DRAW);
	
	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	// enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);
	
	// bind indices if there are any
	if (unIndexCount != 0) {
		
		// generate buffers
		glGenBuffers(1, &m_unIBO);
		
		// bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_unIBO);
		
		// fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, unIndexCount * sizeof(unsigned int), unpIndices, GL_STATIC_DRAW);
		
		// triangle count is now index / 3 
		m_unTriCount = unIndexCount / 3;
	}
	else 
	{
		// triangle count is now index / 3 
		m_unTriCount = unVertexCount / 3;
	}
	
	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//--------------------------------------------------------------------------------------
// Draw: Render the mesh to the engine window.
//--------------------------------------------------------------------------------------
void Mesh::Draw() 
{
	// rebind VAO
	glBindVertexArray(m_unVAO);
	
	// using indices or just vertices?
	if (m_unIBO != 0)
	{
		// draw using index buffer
		glDrawElements(GL_TRIANGLES, 3 * m_unTriCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		// draw mesh using vertices 
		glDrawArrays(GL_TRIANGLES, 0, 3 * m_unTriCount);
	}
}