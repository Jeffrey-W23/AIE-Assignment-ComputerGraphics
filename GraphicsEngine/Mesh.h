// #includes, using, etc
#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//--------------------------------------------------------------------------------------
// Mesh object. 
//--------------------------------------------------------------------------------------
class Mesh 
{
public:
	
	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	Mesh() : m_unTriCount(0), m_unVAO(0), m_unVBO(0), m_unIBO(0) {}
	
	//--------------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------------
	virtual ~Mesh();
	
	//--------------------------------------------------------------------------------------
	// Struct Vertex: holds 3 vec4 values for the vertex position, normal and texture coord.
	//--------------------------------------------------------------------------------------
	struct Vertex 
	{
		glm::vec4 m_v4Position;
		glm::vec4 m_v4Normal;
		glm::vec2 m_v4TexCoord;
	};

	//--------------------------------------------------------------------------------------
	// InitialiseQuad: Initialises the mesh visually as a quad.
	//--------------------------------------------------------------------------------------
	void InitialiseQuad();

	//--------------------------------------------------------------------------------------
	// Initialise: Initialises the mesh visually.
	//
	// Params:
	//		unVertexCount: unsigned int for vertex count.
	//		kpVertices: const Vertex pointer for vertices.
	//		unIndexCount: unsigned int indices index.
	//		unpIndices: unsigned int pointer for indices.
	//--------------------------------------------------------------------------------------
	void Initialise(unsigned int unVertexCount, const Vertex* kpVertices, unsigned int unIndexCount = 0, unsigned int* unpIndices = nullptr);

	//--------------------------------------------------------------------------------------
	// Draw: Render the mesh to the engine window.
	//--------------------------------------------------------------------------------------
	virtual void Draw();

protected:

	//--------------------------------------------------------------------------------------
	// unsigned int for the triangle count of the mesh.
	//--------------------------------------------------------------------------------------
	unsigned int m_unTriCount;

	//--------------------------------------------------------------------------------------
	// unsigned int for the VAO, VBO and IBO.
	//--------------------------------------------------------------------------------------
	unsigned int m_unVAO, m_unVBO, m_unIBO;
};