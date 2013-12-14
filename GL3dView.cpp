// GL3dView.cpp : implementation file


#include "stdafx.h"
#include <math.h>	
#include <gl\glut.h>
#include "GL3dView.h"
#include "gl\gl.h"
#include "gl\glu.h"
#include "gl\glaux.h"
#include "resource.h"
#include "ArchDoc.h"
#include "EnBitmap.h"
#include "tex.h"
#include<vector>
#include<fstream>
using namespace std;
#define MAX_TEXTURES 100
UINT g_Texture[MAX_TEXTURES] = {0};	
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




#define PRIMARY       0x4D4D

//>------ Main Chunks
#define OBJECTINFO    0x3D3D				// This gives the version of the mesh and is found right before the material and object information
#define VERSION       0x0002				// This gives the version of the .3ds file
#define EDITKEYFRAME  0xB000				// This is the header for all of the key frame info

//>------ sub defines of OBJECTINFO
#define MATERIAL	  0xAFFF				// This stored the texture info
#define OBJECT		  0x4000				// This stores the faces, vertices, etc...

//>------ sub defines of MATERIAL
#define MATNAME       0xA000				// This holds the material name
#define MATDIFFUSE    0xA020				// This holds the color of the object/material
#define MATMAP        0xA200				// This is a header for a new material
#define MATMAPFILE    0xA300				// This holds the file name of the texture

#define OBJECT_MESH   0x4100				// This lets us know that we are reading a new object

//>------ sub defines of OBJECT_MESH
#define OBJECT_VERTICES     0x4110			// The objects vertices
#define OBJECT_FACES		0x4120			// The objects faces
#define OBJECT_MATERIAL		0x4130			// This is found if the object has a material, either texture map or color
#define OBJECT_UV			0x4140			// The UV texture coordinates


// Here is our structure for our 3DS indicies (since .3DS stores 4 unsigned shorts)
struct tIndices {							

	unsigned short a, b, c, bVisible;		// This will hold point1, 2, and 3 index's into the vertex array plus a visible flag
};

// This holds the chunk info
struct tChunk
{
	unsigned short int ID;					// The chunk's ID		
	unsigned int length;					// The length of the chunk
	unsigned int bytesRead;					// The amount of bytes read within that chunk
};
struct tFace
{
	int vertIndex[3];			// indicies for the verts that make up this triangle
	int coordIndex[3];			// indicies for the tex coords to texture this face
};

struct tMaterialInfo
{
	char  strName[255];			// The texture name
	char  strFile[255];			// The texture file name (If this is set it's a texture map)
	BYTE  color[3];				// The color of the object (R, G, B)
	int   texureId;				// the texture ID
	float uTile;				// u tiling of texture  (Currently not used)
	float vTile;				// v tiling of texture	(Currently not used)
	float uOffset;			    // u offset of texture	(Currently not used)
	float vOffset;				// v offset of texture	(Currently not used)
} ;
struct t3DObject 
{
	int  numOfVerts;			// The number of verts in the model
	int  numOfFaces;			// The number of faces in the model
	int  numTexVertex;			// The number of texture coordinates
	int  materialID;			// The texture ID to use, which is the index into our texture array
	bool bHasTexture;			// This is TRUE if there is a texture map for this object
	char strName[255];			// The name of the object
	CVector3  *pVerts;			// The object's vertices
	CVector3  *pNormals;		// The object's normals
	CVector2  *pTexVerts;		// The texture's UV coordinates
	tFace *pFaces;				// The faces information of the object
};

// This holds our model information.  This should also turn into a robust class.
// We use STL's (Standard Template Library) vector class to ease our link list burdens. :)
struct t3DModel 
{
	int numOfObjects;					// The number of objects in the model
	int numOfMaterials;					// The number of materials for the model
	vector<tMaterialInfo> pMaterials;	// The list of material information (Textures and colors)
	vector<t3DObject> pObject;			// The object list for our model
};
// This class handles all of the loading code
struct fspoint{
	long x1,y1;
	long x2,y2;
};
class CLoad3DS
{
public:
	CLoad3DS();								// This inits the data members
t3DModel g_3DModel[5];	
	// This is the function that you call to load the 3DS
	bool Import3DS(t3DModel *pModel, char *strFileName);
	void Draw(int d);
private:
	// This reads in a string and saves it in the char array passed in
	int GetString(char *);

	// This reads the next chunk
	void ReadChunk(tChunk *);

	// This reads the next large chunk
	void ProcessNextChunk(t3DModel *pModel, tChunk *);

	// This reads the object chunks
	void ProcessNextObjectChunk(t3DModel *pModel, t3DObject *pObject, tChunk *);

	// This reads the material chunks
	void ProcessNextMaterialChunk(t3DModel *pModel, tChunk *);

	// This reads the RGB value for the object's color
	void ReadColorChunk(tMaterialInfo *pMaterial, tChunk *pChunk);

	// This reads the objects vertices
	void ReadVertices(t3DObject *pObject, tChunk *);

	// This reads the objects face information
	void ReadVertexIndices(t3DObject *pObject, tChunk *);

	// This reads the texture coodinates of the object
	void ReadUVCoordinates(t3DObject *pObject, tChunk *);

	// This reads in the material name assigned to the object and sets the materialID
	void ReadObjectMaterial(t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk);
	
	// This computes the vertex normals for the object (used for lighting)
	void ComputeNormals(t3DModel *pModel);

	// This frees memory and closes the file
	void CleanUp();
	
	// The file pointer
	FILE *m_FilePointer;
	
	// These are used through the loading process to hold the chunk information
	tChunk *m_CurrentChunk;
	tChunk *m_TempChunk;
};
CLoad3DS g_Load3ds[5];	
fspoint fsp[100];
CLoad3DS::CLoad3DS()
{
	m_CurrentChunk = new tChunk;				// Initialize and allocate our current chunk
	m_TempChunk = new tChunk;					// Initialize and allocate a temporary chunk
}

///////////////////////////////// IMPORT 3DS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This is called by the client to open the .3ds file, read it, then clean up
/////
///////////////////////////////// IMPORT 3DS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool CLoad3DS::Import3DS(t3DModel *pModel, char *strFileName)
{
	char strMessage[255] = {0};

	// Open the 3DS file
	m_FilePointer = fopen(strFileName, "rb");

	// Make sure we have a valid file pointer (we found the file)
	if(!m_FilePointer) 
	{
		sprintf(strMessage, "Unable to find the file: %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}

	// Once we have the file open, we need to read the very first data chunk
	// to see if it's a 3DS file.  That way we don't read an invalid file.
	// If it is a 3DS file, then the first chunk ID will be equal to PRIMARY (some hex num)

	// Read the first chuck of the file to see if it's a 3DS file
	ReadChunk(m_CurrentChunk);

	// Make sure this is a 3DS file
	if (m_CurrentChunk->ID != PRIMARY)
	{
		sprintf(strMessage, "Unable to load PRIMARY chuck from file: %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}

	// Now we actually start reading in the data.  ProcessNextChunk() is recursive

	// Begin loading objects, by calling this recursive function
	ProcessNextChunk(pModel, m_CurrentChunk);

	// After we have read the whole 3DS file, we want to calculate our own vertex normals.
	ComputeNormals(pModel);

	// Clean up after everything
	CleanUp();

	return true;
}

///////////////////////////////// CLEAN UP \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function cleans up our allocated memory and closes the file
/////
///////////////////////////////// CLEAN UP \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CLoad3DS::CleanUp()
{

	fclose(m_FilePointer);						// Close the current file pointer
	delete m_CurrentChunk;						// Free the current chunk
	delete m_TempChunk;							// Free our temporary chunk
}
void CLoad3DS::Draw(int d)
{

		for(int i = 0; i < g_3DModel[0].numOfObjects; i++) //changings bieng made
	{
		// Make sure we have valid objects just in case. (size() is in the vector class)
		if(g_3DModel[0].pObject.size() <= 0) break;

		// Get the current object that we are displaying
		t3DObject *pObject = &g_3DModel[0].pObject[i];
			
		// Check to see if this object has a texture map, if so bind the texture to it.
		if(pObject->bHasTexture) {

			// Turn on texture mapping and turn off color
			glEnable(GL_TEXTURE_2D);

			// Reset the color to normal again
			glColor3ub(255, 255, 255);

			// Bind the texture map to the object by it's materialID
			glBindTexture(GL_TEXTURE_2D, g_Texture[pObject->materialID]);
		} else {

			// Turn off texture mapping and turn on color
			glDisable(GL_TEXTURE_2D);

			// Reset the color to normal again
			glColor3ub(255, 255, 255);
		}

		// This determines if we are in wireframe or normal mode
		glBegin(GL_TRIANGLES);					// Begin drawing with our selected mode (triangles or lines)

			// Go through all of the faces (polygons) of the object and draw them
			for(int j = 0; j < pObject->numOfFaces; j++)
			{
				// Go through each corner of the triangle and draw it.
				for(int whichVertex = 0; whichVertex < 3; whichVertex++)
				{
					// Get the index for each point of the face
					int index = pObject->pFaces[j].vertIndex[whichVertex];
			
					// Give OpenGL the normal for this vertex.
					glNormal3f(pObject->pNormals[ index ].x, pObject->pNormals[ index ].z, pObject->pNormals[ index ].y);
				
					// If the object has a texture associated with it, give it a texture coordinate.
					if(pObject->bHasTexture) {

						// Make sure there was a UVW map applied to the object or else it won't have tex coords.
						if(pObject->pTexVerts) {
							glTexCoord2f(pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);
						}
					} else {

						// Make sure there is a valid material/color assigned to this object.
						// You should always at least assign a material color to an object, 
						// but just in case we want to check the size of the material list.
						// if the size is at least one, and the material ID != -1,
						// then we have a valid material.
						if(g_3DModel[d].pMaterials.size() && pObject->materialID >= 0) 
						{
							// Get and set the color that the object is, since it must not have a texture
							BYTE *pColor = g_3DModel[d].pMaterials[pObject->materialID].color;

							// Assign the current color to this model
							glColor3ub(pColor[0], pColor[1], pColor[2]);
						}
					}

					// Pass in the current vertex of the object (Corner of current face)
					glVertex3f(pObject->pVerts[ index ].x, pObject->pVerts[ index ].z, pObject->pVerts[ index ].y);
				}
			}

		glEnd();								// End the drawing
	}
//		SwapBuffers(m_pDC->GetSafeHdc());

}

///////////////////////////////// PROCESS NEXT CHUNK\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function reads the main sections of the .3DS file, then dives deeper with recursion
/////
///////////////////////////////// PROCESS NEXT CHUNK\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CLoad3DS::ProcessNextChunk(t3DModel *pModel, tChunk *pPreviousChunk)
{
	t3DObject newObject = {0};					// This is used to add to our object list
	tMaterialInfo newTexture = {0};				// This is used to add to our material list
	unsigned int version = 0;					// This will hold the file version
	int buffer[50000] = {0};					// This is used to read past unwanted data

	m_CurrentChunk = new tChunk;				// Allocate a new chunk				

	// Below we check our chunk ID each time we read a new chunk.  Then, if
	// we want to extract the information from that chunk, we do so.
	// If we don't want a chunk, we just read past it.  

	// Continue to read the sub chunks until we have reached the length.
	// After we read ANYTHING we add the bytes read to the chunk and then check
	// check against the length.
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		// Read next Chunk
		ReadChunk(m_CurrentChunk);

		// Check the chunk ID
		switch (m_CurrentChunk->ID)
		{
		case VERSION:							// This holds the version of the file
			
			// This chunk has an unsigned short that holds the file version.
			// Since there might be new additions to the 3DS file format in 4.0,
			// we give a warning to that problem.

			// Read the file version and add the bytes read to our bytesRead variable
			m_CurrentChunk->bytesRead += fread(&version, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);

			// If the file version is over 3, give a warning that there could be a problem
			if (version > 0x03)
				MessageBox(NULL, "This 3DS file is over version 3 so it may load incorrectly", "Warning", MB_OK);
			break;

		case OBJECTINFO:						// This holds the version of the mesh
			
			// This chunk holds the version of the mesh.  It is also the head of the MATERIAL
			// and OBJECT chunks.  From here on we start reading in the material and object info.

			// Read the next chunk
			ReadChunk(m_TempChunk);

			// Get the version of the mesh
			m_TempChunk->bytesRead += fread(&version, 1, m_TempChunk->length - m_TempChunk->bytesRead, m_FilePointer);

			// Increase the bytesRead by the bytes read from the last chunk
			m_CurrentChunk->bytesRead += m_TempChunk->bytesRead;

			// Go to the next chunk, which is the object has a texture, it should be MATERIAL, then OBJECT.
			ProcessNextChunk(pModel, m_CurrentChunk);
			break;

		case MATERIAL:							// This holds the material information

			// This chunk is the header for the material info chunks

			// Increase the number of materials
			pModel->numOfMaterials++;

			// Add a empty texture structure to our texture list.
			// If you are unfamiliar with STL's "vector" class, all push_back()
			// does is add a new node onto the list.  I used the vector class
			// so I didn't need to write my own link list functions.  
			pModel->pMaterials.push_back(newTexture);

			// Proceed to the material loading function
			ProcessNextMaterialChunk(pModel, m_CurrentChunk);
			break;

		case OBJECT:							// This holds the name of the object being read
				
			// This chunk is the header for the object info chunks.  It also
			// holds the name of the object.

			// Increase the object count
			pModel->numOfObjects++;
		
			// Add a new tObject node to our list of objects (like a link list)
			pModel->pObject.push_back(newObject);
			
			// Initialize the object and all it's data members
			memset(&(pModel->pObject[pModel->numOfObjects - 1]), 0, sizeof(t3DObject));

			// Get the name of the object and store it, then add the read bytes to our byte counter.
			m_CurrentChunk->bytesRead += GetString(pModel->pObject[pModel->numOfObjects - 1].strName);
			
			// Now proceed to read in the rest of the object information
			ProcessNextObjectChunk(pModel, &(pModel->pObject[pModel->numOfObjects - 1]), m_CurrentChunk);
			break;

		case EDITKEYFRAME:

			// Because I wanted to make this a SIMPLE tutorial as possible, I did not include
			// the key frame information.  This chunk is the header for all the animation info.
			// In a later tutorial this will be the subject and explained thoroughly.

			//ProcessNextKeyFrameChunk(pModel, m_CurrentChunk);

			// Read past this chunk and add the bytes read to the byte counter
			m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;

		default: 
			
			// If we didn't care about a chunk, then we get here.  We still need
			// to read past the unknown or ignored chunk and add the bytes read to the byte counter.
			m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		}

		// Add the bytes read from the last chunk to the previous chunk passed in.
		pPreviousChunk->bytesRead += m_CurrentChunk->bytesRead;
	}

	// Free the current chunk and set it back to the previous chunk (since it started that way)
	delete m_CurrentChunk;
	m_CurrentChunk = pPreviousChunk;
}


///////////////////////////////// PROCESS NEXT OBJECT CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function handles all the information about the objects in the file
/////
///////////////////////////////// PROCESS NEXT OBJECT CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CLoad3DS::ProcessNextObjectChunk(t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk)
{
	int buffer[50000] = {0};					// This is used to read past unwanted data

	// Allocate a new chunk to work with
	m_CurrentChunk = new tChunk;

	// Continue to read these chunks until we read the end of this sub chunk
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		// Read the next chunk
		ReadChunk(m_CurrentChunk);

		// Check which chunk we just read
		switch (m_CurrentChunk->ID)
		{
		case OBJECT_MESH:					// This lets us know that we are reading a new object
		
			// We found a new object, so let's read in it's info using recursion
			ProcessNextObjectChunk(pModel, pObject, m_CurrentChunk);
			break;

		case OBJECT_VERTICES:				// This is the objects vertices
			ReadVertices(pObject, m_CurrentChunk);
			break;

		case OBJECT_FACES:					// This is the objects face information
			ReadVertexIndices(pObject, m_CurrentChunk);
			break;

		case OBJECT_MATERIAL:				// This holds the material name that the object has
			
			// This chunk holds the name of the material that the object has assigned to it.
			// This could either be just a color or a texture map.  This chunk also holds
			// the faces that the texture is assigned to (In the case that there is multiple
			// textures assigned to one object, or it just has a texture on a part of the object.
			// Since most of my game objects just have the texture around the whole object, and 
			// they aren't multitextured, I just want the material name.

			// We now will read the name of the material assigned to this object
			ReadObjectMaterial(pModel, pObject, m_CurrentChunk);			
			break;

		case OBJECT_UV:						// This holds the UV texture coordinates for the object

			// This chunk holds all of the UV coordinates for our object.  Let's read them in.
			ReadUVCoordinates(pObject, m_CurrentChunk);
			break;

		default:  

			// Read past the ignored or unknown chunks
			m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		}

		// Add the bytes read from the last chunk to the previous chunk passed in.
		pPreviousChunk->bytesRead += m_CurrentChunk->bytesRead;
	}

	// Free the current chunk and set it back to the previous chunk (since it started that way)
	delete m_CurrentChunk;
	m_CurrentChunk = pPreviousChunk;
}


///////////////////////////////// PROCESS NEXT MATERIAL CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function handles all the information about the material (Texture)
/////
///////////////////////////////// PROCESS NEXT MATERIAL CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CLoad3DS::ProcessNextMaterialChunk(t3DModel *pModel, tChunk *pPreviousChunk)
{
	int buffer[50000] = {0};					// This is used to read past unwanted data

	// Allocate a new chunk to work with
	m_CurrentChunk = new tChunk;

	// Continue to read these chunks until we read the end of this sub chunk
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		// Read the next chunk
		ReadChunk(m_CurrentChunk);

		// Check which chunk we just read in
		switch (m_CurrentChunk->ID)
		{
		case MATNAME:							// This chunk holds the name of the material
			
			// Here we read in the material name
			m_CurrentChunk->bytesRead += fread(pModel->pMaterials[pModel->numOfMaterials - 1].strName, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;

		case MATDIFFUSE:						// This holds the R G B color of our object
			ReadColorChunk(&(pModel->pMaterials[pModel->numOfMaterials - 1]), m_CurrentChunk);
			break;
		
		case MATMAP:							// This is the header for the texture info
			
			// Proceed to read in the material information
			ProcessNextMaterialChunk(pModel, m_CurrentChunk);
			break;

		case MATMAPFILE:						// This stores the file name of the material

			// Here we read in the material's file name
			m_CurrentChunk->bytesRead += fread(pModel->pMaterials[pModel->numOfMaterials - 1].strFile, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		
		default:  

			// Read past the ignored or unknown chunks
			m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		}

		// Add the bytes read from the last chunk to the previous chunk passed in.
		pPreviousChunk->bytesRead += m_CurrentChunk->bytesRead;
	}

	// Free the current chunk and set it back to the previous chunk (since it started that way)
	delete m_CurrentChunk;
	m_CurrentChunk = pPreviousChunk;
}

///////////////////////////////// READ CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function reads in a chunk ID and it's length in bytes
/////
///////////////////////////////// READ CHUNK \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CLoad3DS::ReadChunk(tChunk *pChunk)
{
	// This reads the chunk ID which is 2 bytes.
	// The chunk ID is like OBJECT or MATERIAL.  It tells what data is
	// able to be read in within the chunks section.  
	pChunk->bytesRead = fread(&pChunk->ID, 1, 2, m_FilePointer);

	// Then, we read the length of the chunk which is 4 bytes.
	// This is how we know how much to read in, or read past.
	pChunk->bytesRead += fread(&pChunk->length, 1, 4, m_FilePointer);
}

///////////////////////////////// GET STRING \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function reads in a string of characters
/////
///////////////////////////////// GET STRING \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

int CLoad3DS::GetString(char *pBuffer)
{
	int index = 0;

	// Read 1 byte of data which is the first letter of the string
	fread(pBuffer, 1, 1, m_FilePointer);

	// Loop until we get NULL
	while (*(pBuffer + index++) != 0) {

		// Read in a character at a time until we hit NULL.
		fread(pBuffer + index, 1, 1, m_FilePointer);
	}

	// Return the string length, which is how many bytes we read in (including the NULL)
	return strlen(pBuffer) + 1;
}


///////////////////////////////// READ COLOR \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function reads in the RGB color data
/////
///////////////////////////////// READ COLOR \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CLoad3DS::ReadColorChunk(tMaterialInfo *pMaterial, tChunk *pChunk)
{
	// Read the color chunk info
	ReadChunk(m_TempChunk);

	// Read in the R G B color (3 bytes - 0 through 255)
	m_TempChunk->bytesRead += fread(pMaterial->color, 1, m_TempChunk->length - m_TempChunk->bytesRead, m_FilePointer);

	// Add the bytes read to our chunk
	pChunk->bytesRead += m_TempChunk->bytesRead;
}


///////////////////////////////// READ VERTEX INDECES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function reads in the indices for the vertex array
/////
///////////////////////////////// READ VERTEX INDECES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CLoad3DS::ReadVertexIndices(t3DObject *pObject, tChunk *pPreviousChunk)
{
	unsigned short index = 0;					// This is used to read in the current face index

	// In order to read in the vertex indices for the object, we need to first
	// read in the number of them, then read them in.  Remember,
	// we only want 3 of the 4 values read in for each face.  The fourth is
	// a visibility flag for 3D Studio Max that doesn't mean anything to us.

	// Read in the number of faces that are in this object (int)
	pPreviousChunk->bytesRead += fread(&pObject->numOfFaces, 1, 2, m_FilePointer);

	// Alloc enough memory for the faces and initialize the structure
	pObject->pFaces = new tFace [pObject->numOfFaces];
	memset(pObject->pFaces, 0, sizeof(tFace) * pObject->numOfFaces);

	// Go through all of the faces in this object
	for(int i = 0; i < pObject->numOfFaces; i++)
	{
		// Next, we read in the A then B then C index for the face, but ignore the 4th value.
		// The fourth value is a visibility flag for 3D Studio Max, we don't care about this.
		for(int j = 0; j < 4; j++)
		{
			// Read the first vertice index for the current face 
			pPreviousChunk->bytesRead += fread(&index, 1, sizeof(index), m_FilePointer);

			if(j < 3)
			{
				// Store the index in our face structure.
				pObject->pFaces[i].vertIndex[j] = index;
			}
		}
	}
}


///////////////////////////////// READ UV COORDINATES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function reads in the UV coordinates for the object
/////
///////////////////////////////// READ UV COORDINATES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CLoad3DS::ReadUVCoordinates(t3DObject *pObject, tChunk *pPreviousChunk)
{
	// In order to read in the UV indices for the object, we need to first
	// read in the amount there are, then read them in.

	// Read in the number of UV coordinates there are (int)
	pPreviousChunk->bytesRead += fread(&pObject->numTexVertex, 1, 2, m_FilePointer);

	// Allocate memory to hold the UV coordinates
	pObject->pTexVerts = new CVector2 [pObject->numTexVertex];

	// Read in the texture coodinates (an array 2 float)
	pPreviousChunk->bytesRead += fread(pObject->pTexVerts, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);
}


///////////////////////////////// READ VERTICES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function reads in the vertices for the object
/////
///////////////////////////////// READ VERTICES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CLoad3DS::ReadVertices(t3DObject *pObject, tChunk *pPreviousChunk)
{
	// Like most chunks, before we read in the actual vertices, we need
	// to find out how many there are to read in.  Once we have that number
	// we then fread() them into our vertice array.

	// Read in the number of vertices (int)
	pPreviousChunk->bytesRead += fread(&(pObject->numOfVerts), 1, 2, m_FilePointer);

	// Allocate the memory for the verts and initialize the structure
	pObject->pVerts = new CVector3 [pObject->numOfVerts];
	memset(pObject->pVerts, 0, sizeof(CVector3) * pObject->numOfVerts);

	// Read in the array of vertices (an array of 3 floats)
	pPreviousChunk->bytesRead += fread(pObject->pVerts, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);

	// Now we should have all of the vertices read in.  Because 3D Studio Max
	// Models with the Z-Axis pointing up (strange and ugly I know!), we need
	// to flip the y values with the z values in our vertices.  That way it
	// will be normal, with Y pointing up.  If you prefer to work with Z pointing
	// up, then just delete this next loop.  Also, because we swap the Y and Z
	// we need to negate the Z to make it come out correctly.

	// Go through all of the vertices that we just read and swap the Y and Z values
	for(int i = 0; i < pObject->numOfVerts; i++)
	{
		// Store off the Y value
		float fTempY = pObject->pVerts[i].y;

		// Set the Y value to the Z value
		pObject->pVerts[i].y = pObject->pVerts[i].z;

		// Set the Z value to the Y value, 
		// but negative Z because 3D Studio max does the opposite.
		pObject->pVerts[i].z = -fTempY;
	}
}


///////////////////////////////// READ OBJECT MATERIAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function reads in the material name assigned to the object and sets the materialID
/////
///////////////////////////////// READ OBJECT MATERIAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CLoad3DS::ReadObjectMaterial(t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk)
{
	char strMaterial[255] = {0};			// This is used to hold the objects material name
	int buffer[50000] = {0};				// This is used to read past unwanted data

	// *What is a material?*  - A material is either the color or the texture map of the object.
	// It can also hold other information like the brightness, shine, etc... Stuff we don't
	// really care about.  We just want the color, or the texture map file name really.

	// Here we read the material name that is assigned to the current object.
	// strMaterial should now have a string of the material name, like "Material #2" etc..
	pPreviousChunk->bytesRead += GetString(strMaterial);

	// Now that we have a material name, we need to go through all of the materials
	// and check the name against each material.  When we find a material in our material
	// list that matches this name we just read in, then we assign the materialID
	// of the object to that material index.  You will notice that we passed in the
	// model to this function.  This is because we need the number of textures.
	// Yes though, we could have just passed in the model and not the object too.

	// Go through all of the textures
	for(int i = 0; i < pModel->numOfMaterials; i++)
	{
		// If the material we just read in matches the current texture name
		if(strcmp(strMaterial, pModel->pMaterials[i].strName) == 0)
		{
			// Set the material ID to the current index 'i' and stop checking
			pObject->materialID = i;

			// Now that we found the material, check if it's a texture map.
			// If the strFile has a string length of 1 and over it's a texture
			if(strlen(pModel->pMaterials[i].strFile) > 0) {

				// Set the object's flag to say it has a texture map to bind.
				pObject->bHasTexture = true;
			}	
			break;
		}
		else
		{
			// Set the ID to -1 to show there is no material for this object
			pObject->materialID = -1;
		}
	}

	// Read past the rest of the chunk since we don't care about shared vertices
	// You will notice we subtract the bytes already read in this chunk from the total length.
	pPreviousChunk->bytesRead += fread(buffer, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);
}			

// *Note* 
//
// Below are some math functions for calculating vertex normals.  We want vertex normals
// because it makes the lighting look really smooth and life like.  You probably already
// have these functions in the rest of your engine, so you can delete these and call
// your own.  I wanted to add them so I could show how to calculate vertex normals.

//////////////////////////////	Math Functions  ////////////////////////////////*

// This computes the magnitude of a normal.   (magnitude = sqrt(x^2 + y^2 + z^2)
#define Mag(Normal) (sqrt(Normal.x*Normal.x + Normal.y*Normal.y + Normal.z*Normal.z))

// This calculates a vector between 2 points and returns the result
CVector3 Vector(CVector3 vPoint1, CVector3 vPoint2)
{
	CVector3 vVector;							// The variable to hold the resultant vector

	vVector.x = vPoint1.x - vPoint2.x;			// Subtract point1 and point2 x's
	vVector.y = vPoint1.y - vPoint2.y;			// Subtract point1 and point2 y's
	vVector.z = vPoint1.z - vPoint2.z;			// Subtract point1 and point2 z's

	return vVector;								// Return the resultant vector
}

// This adds 2 vectors together and returns the result

CVector3 AddVector(CVector3 vVector1, CVector3 vVector2)
{
	CVector3 vResult;							// The variable to hold the resultant vector
	
	vResult.x = vVector2.x + vVector1.x;		// Add Vector1 and Vector2 x's
	vResult.y = vVector2.y + vVector1.y;		// Add Vector1 and Vector2 y's
	vResult.z = vVector2.z + vVector1.z;		// Add Vector1 and Vector2 z's

	return vResult;								// Return the resultant vector
}

// This divides a vector by a single number (scalar) and returns the result
CVector3 DivideVectorByScaler(CVector3 vVector1, float Scaler)
{
	CVector3 vResult;							// The variable to hold the resultant vector
	
	vResult.x = vVector1.x / Scaler;			// Divide Vector1's x value by the scaler
	vResult.y = vVector1.y / Scaler;			// Divide Vector1's y value by the scaler
	vResult.z = vVector1.z / Scaler;			// Divide Vector1's z value by the scaler

	return vResult;								// Return the resultant vector
}

// This returns the cross product between 2 vectors

void CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID)
{
	AUX_RGBImageRec *pBitmap = NULL;
	//int pBitmap;
	if(!strFileName)									// Return from the function if no file name was passed in
		return;
     CEnBitmap b;
//	pBitmap=b.LoadImage(strFileName);
	pBitmap = auxDIBImageLoad(strFileName);				// Load the bitmap and store the data
	
	if(pBitmap == NULL)									// If we can't load the file, quit!
		exit(0);

	// Generate a texture with the associative texture ID stored in the array
	glGenTextures(1, &textureArray[textureID]);

	// This sets the alignment requirements for the start of each pixel row in memory.
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	// Bind the texture to the texture arrays index and init the texture
	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);

	// Build Mipmaps (builds different versions of the picture for distances - looks better)
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitmap->sizeX, pBitmap->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pBitmap->data);

	// Lastly, we need to tell OpenGL the quality of our texture map.  GL_LINEAR_MIPMAP_LINEAR
	// is the smoothest.  GL_LINEAR_MIPMAP_NEAREST is faster than GL_LINEAR_MIPMAP_LINEAR, 
	// but looks blochy and pixilated.  Good for slower computers though.  
		
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

	// Now we need to free the bitmap data that we loaded since openGL stored it as a texture

	if (pBitmap)										// If we loaded the bitmap
	{
		if (pBitmap->data)								// If there is texture data
		{
			free(pBitmap->data);						// Free the texture data, we don't need it anymore
		}

		free(pBitmap);									// Free the bitmap structure
	}
}
CVector3 Cross(CVector3 vVector1, CVector3 vVector2)
{
	CVector3 vCross;								// The vector to hold the cross product
												// Get the X value
	vCross.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
												// Get the Y value
	vCross.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
												// Get the Z value
	vCross.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

	return vCross;								// Return the cross product
}

// This returns the normal of a vector
CVector3 Normalize(CVector3 vNormal)
{
	double Magnitude;							// This holds the magitude			

	Magnitude = Mag(vNormal);					// Get the magnitude

	vNormal.x /= (float)Magnitude;				// Divide the vector's X by the magnitude
	vNormal.y /= (float)Magnitude;				// Divide the vector's Y by the magnitude
	vNormal.z /= (float)Magnitude;				// Divide the vector's Z by the magnitude

	return vNormal;								// Return the normal
}

///////////////////////////////// COMPUTER NORMALS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function computes the normals and vertex normals of the objects
/////
///////////////////////////////// COMPUTER NORMALS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CLoad3DS::ComputeNormals(t3DModel *pModel)
{
	CVector3 vVector1, vVector2, vNormal, vPoly[3];

	// If there are no objects, we can skip this part
	if(pModel->numOfObjects <= 0)
		return;

	// What are vertex normals?  And how are they different from other normals?
	// Well, if you find the normal to a triangle, you are finding a "Face Normal".
	// If you give OpenGL a face normal for lighting, it will make your object look
	// really flat and not very round.  If we find the normal for each vertex, it makes
	// the smooth lighting look.  This also covers up blocky looking objects and they appear
	// to have more polygons than they do.    Basically, what you do is first
	// calculate the face normals, then you take the average of all the normals around each
	// vertex.  It's just averaging.  That way you get a better approximation for that vertex.

	// Go through each of the objects to calculate their normals
	for(int index = 0; index < pModel->numOfObjects; index++)
	{
		// Get the current object
		t3DObject *pObject = &(pModel->pObject[index]);

		// Here we allocate all the memory we need to calculate the normals
		CVector3 *pNormals		= new CVector3 [pObject->numOfFaces];
		CVector3 *pTempNormals	= new CVector3 [pObject->numOfFaces];
		pObject->pNormals		= new CVector3 [pObject->numOfVerts];

		// Go though all of the faces of this object
		for(int i=0; i < pObject->numOfFaces; i++)
		{												
			// To cut down LARGE code, we extract the 3 points of this face
			vPoly[0] = pObject->pVerts[pObject->pFaces[i].vertIndex[0]];
			vPoly[1] = pObject->pVerts[pObject->pFaces[i].vertIndex[1]];
			vPoly[2] = pObject->pVerts[pObject->pFaces[i].vertIndex[2]];

			// Now let's calculate the face normals (Get 2 vectors and find the cross product of those 2)

			vVector1 = Vector(vPoly[0], vPoly[2]);		// Get the vector of the polygon (we just need 2 sides for the normal)
			vVector2 = Vector(vPoly[2], vPoly[1]);		// Get a second vector of the polygon

			vNormal  = Cross(vVector1, vVector2);		// Return the cross product of the 2 vectors (normalize vector, but not a unit vector)
			pTempNormals[i] = vNormal;					// Save the un-normalized normal for the vertex normals
			vNormal  = Normalize(vNormal);				// Normalize the cross product to give us the polygons normal

			pNormals[i] = vNormal;						// Assign the normal to the list of normals
		}

		//////////////// Now Get The Vertex Normals /////////////////

		CVector3 vSum;
		vSum.x=0;
		vSum.y=0;
		vSum.z=0;
		CVector3 vZero = vSum;
		int shared=0;

		for (i = 0; i < pObject->numOfVerts; i++)			// Go through all of the vertices
		{
			for (int j = 0; j < pObject->numOfFaces; j++)	// Go through all of the triangles
			{												// Check if the vertex is shared by another face
				if (pObject->pFaces[j].vertIndex[0] == i || 
					pObject->pFaces[j].vertIndex[1] == i || 
					pObject->pFaces[j].vertIndex[2] == i)
				{
					vSum = AddVector(vSum, pTempNormals[j]);// Add the un-normalized normal of the shared face
					shared++;								// Increase the number of shared triangles
				}
			}      
			
			// Get the normal by dividing the sum by the shared.  We negate the shared so it has the normals pointing out.
			pObject->pNormals[i] = DivideVectorByScaler(vSum, float(-shared));

			// Normalize the normal for the final vertex normal
			pObject->pNormals[i] = Normalize(pObject->pNormals[i]);	

			vSum = vZero;									// Reset the sum
			shared = 0;										// Reset the shared
		}
	
		// Free our memory and start over on the next object
		delete [] pTempNormals;
		delete [] pNormals;
	}
}





/////////////////////////////////////////////////////////////////////////////
// GL3dView

IMPLEMENT_DYNCREATE(GL3dView, CView)

const char* const GL3dView::_ErrorStrings[]={
	("one"),
		("two"),
		("three"),
		("our"),
		("five"),
		("six"),
		("seven")
};

GL3dView::GL3dView() : piover180 (0.0174532925f)
{

pflag=0;
 walkbias = 0;
 walkbiasangle = 0;
 lookupdown = 0.0f;
 z=0.0f;				// Depth Into The Screen
 zaxis=0;
 fHeight=0;
 i=j=0;
 Rflag=true;
 rotS =1.0;
 //C1=(0,0);
 //C2=(0,0);
/* for(int a=0;a<100;a++)
 {
	 fsp[a].xy1=(0,0);
	 fsp[a].xy2=(0,0);
 	 
 }*/
count_fs=0;
count_element=0;
total_element=0;
fc=0;
loc=loc1=loc2=0;
s_count=fw_count=sp_count=cw_count=0;
count_loc=0;
}

GL3dView::~GL3dView()
{
	
}


BEGIN_MESSAGE_MAP(GL3dView, CView)
	//{{AFX_MSG_MAP(GL3dView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GL3dView drawing

void GL3dView::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();
	
	//ASSERT_VALID(pDoc);
	// TODO: add draw code here

	glEnable(GL_DEPTH_TEST);

	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	
	
	
	PreRenderScene();

	//::glPushMatrix();
	RenderStockScene();
	//::glPopMatrix();

//	::glPushMatrix();
	RenderScene();
//	::glPopMatrix();

	::glFinish();
	if(FALSE == SwapBuffers(m_pDC->GetSafeHdc()))
	{  
		SetError(7);
	}

}

/////////////////////////////////////////////////////////////////////////////
// GL3dView diagnostics

#ifdef _DEBUG
void GL3dView::AssertValid() const
{
	CView::AssertValid();
}

void GL3dView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// GL3dView message handlers


void GL3dView::SetError(int e)
{
	if(_ErrorStrings[0] == m_ErrorString )
	{
		m_ErrorString = _ErrorStrings[e];
	}
}


//////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

BOOL GL3dView::SetupPixelFormat()
	{

		static PIXELFORMATDESCRIPTOR pfd=
		{
			sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW |
				PFD_SUPPORT_OPENGL |
				PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA,
				24,
				0,0,0,0,0,0,
				0,
				0,
				0,
				0,0,0,0,
				16,
				0,
				0,
				PFD_MAIN_PLANE,
				0,
				0,0,0
		};

		int pixelFormat;

		if(0==(pixelFormat =
			::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)))
		{
			SetError(2);
			return FALSE;
		}

		if (FALSE ==
			::SetPixelFormat(m_pDC->GetSafeHdc(),pixelFormat, &pfd))
		{
			SetError(3);
			return FALSE;
		}
		return TRUE;
	}

//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
		



//////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
BOOL GL3dView::SetupViewport(int cx,int cy)
{
	::glViewport(0,0,cx,cy);
    return TRUE;
}


/////////////////////////////////////////////////////////////////////
BOOL GL3dView::SetupViewingFrustum(GLint aspect_ratio)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	::gluPerspective(45.0f, aspect_ratio, 0.1f, 200.0f);
	glOrtho(0,10,0,10,0,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//	::gluPerspective(20.0f,aspect_ratio , 0.5f, 300.0f);
	return TRUE;
}


////////////////////////////////////////////////////////////////////
BOOL GL3dView::RenderScene()
{

	
	CArchDoc*  pDoc = (CArchDoc*) GetDocument();
	ASSERT_VALID(pDoc);
	CRect R;
	GetClientRect(&R);
	CVector3 V1,V2,V3,V4;
	V1=ConvertPoint(R.left, 0, R.top);
	V2=ConvertPoint(R.right,0, R.top);
	V3=ConvertPoint(R.right,0, R.bottom);
	V4=ConvertPoint(R.left, 0, R.bottom);

	gluLookAt(g_Camera.m_vPosition.x, g_Camera.m_vPosition.y,  g_Camera.m_vPosition.z,	
			  g_Camera.m_vView.x,	  g_Camera.m_vView.y,      g_Camera.m_vView.z,	
			  g_Camera.m_vUpVector.x, g_Camera.m_vUpVector.y,  g_Camera.m_vUpVector.z);

	glColor3ub(150,100, 50);
	glPushMatrix();
		DrawGrid();
	glPopMatrix();

	CFloor* pCurFlr;
	CBuildingElement *pBE;
	glPushMatrix();



	for ( i=pDoc->m_Building.GetFloorCount()-1;i>=0; i--)
	{
		pCurFlr = pDoc->m_Building.GetFloorAt(i);
	    fc=i;
		fHeight = 20.0f * (i-1);

		glPushMatrix();
	    	
			glTranslatef(0,fHeight,0);
			glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	

	glBegin(GL_QUADS);
	

	
xSpeed +=1.0;
 	//glColor3ub(128,0,0);						// Set The Color // 
	glColor4f(0.5,0.0,0.0,0.5);


glVertex3f(V1.x,V1.y,V1.z);
		glVertex3f(V2.x,V2.y,V2.z);
		glVertex3f(V3.x,V3.y,V3.z);
		glVertex3f(V4.x,V4.y,V4.z);		
	glEnd();

		// Stop drawing lines
		glEnd();

			for ( j=0; j < pCurFlr->GetElementCount(); j++)
			{
		   //char c[10];
		   //itoa(fHeight,c,10);
		   //AfxMessageBox(c);
		
		
				pBE = pCurFlr->GetElement(j);
				switch (pBE->GetType())
				{
				case BUILDING_ELEMENT_ROUNDPILLAR:
					DrawPillar((CPillar*)pBE,i);
					break;
				case BUILDING_ELEMENT_SQUAREPILLAR:
					DrawPillar((CPillar*)pBE,i);
					break;
				case BUILDING_ELEMENT_WALL:
						DrawWall((CWall*) pBE,i);
						//CStraightWallDlg* swg1;//= (CStraightWallDlg*) pWall;
					break;
			   case BUILDING_ELEMENT_FIXTUREWALL:
	                DrawFixtureWall((CFixtureWall*) pBE);
					    			
				
				case BUILDING_ELEMENT_CEILING:
					DrawCeiling((CCeiling*) pBE,i);
					break;

				case BUILDING_ELEMENT_CURVEDWALL:
					DrawCurvedWall((CCurvedWall*) pBE);
					break;
				case BUILDING_ELEMENT_STAIRS:
					DrawStairs((CStairs *)pBE);
					break;
				case BUILDING_ELEMENT_SPIRALSTAIR:
					DrawSpiralStair((CSpiralstair *)pBE);
					break;

					 case BUILDING_ELEMENT_CHAIR1:
					{
						chairvalue1=1;
                        	DrawChair((CChairObject *)pBE,1/*chairvalue18*/);
					}break;
				case BUILDING_ELEMENT_CHAIR2:
					{
						chairvalue1=2;
                        	DrawChair((CChairObject *)pBE,chairvalue1);
					}break;
				case BUILDING_ELEMENT_CHAIR3:
					{
						chairvalue1=3;
                        	DrawChair((CChairObject *)pBE,chairvalue1);
					}break;
				case BUILDING_ELEMENT_CHAIR4:
					{
						chairvalue1=4;
                        	DrawChair((CChairObject *)pBE,chairvalue1);
					}break;
				case BUILDING_ELEMENT_CHAIR5:
					{
						chairvalue1=5;
                        	DrawChair((CChairObject *)pBE,chairvalue1);
					}break;
				
				case BUILDING_ELEMENT_TABLE1:
				{
                   DrawTable((CTableobject *)pBE);
				}
				break;
				case BUILDING_ELEMENT_SOFA1:
				{
                   DrawSofa((CSofaobject *)pBE);
				}
				break;

			}
	glPopMatrix();
			}
		glPopMatrix();

	}
//Stairs();
//// Code for floor;
	/*CRect R;
	GetClientRect(&R);
	CVector3 V1,V2,V3,V4;
	V1=ConvertPoint(R.left, 0, R.top);
	V2=ConvertPoint(R.right,0, R.top);
	V3=ConvertPoint(R.right,0, R.bottom);
	V4=ConvertPoint(R.left, 0, R.bottom);
*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	

	glBegin(GL_QUADS);
	

	
xSpeed +=1.0;
 	//glColor3ub(128,0,0);						// Set The Color // 
	glColor4f(0.5,0.0,0.0,0.5);


glVertex3f(V1.x,V1.y,V1.z);
		glVertex3f(V2.x,V2.y,V2.z);
		glVertex3f(V3.x,V3.y,V3.z);
		glVertex3f(V4.x,V4.y,V4.z);		
	glEnd();

/*	
	glBegin(GL_QUADS);
	
	//glColor3ub(128,0,0);						// Set The Color // 
	glColor4f(0.5,0.0,0.0,1.0);
        glVertex3f(-50  , V1.y-8.0 , V1.z);
		glVertex3f(50 , V2.y-8.0 , V2.z);
		glVertex3f(V3.x , V3.y-8.0 , -50);
		glVertex3f(V4.x , V4.y-8.0 , 50);		
	glEnd();
	
*/

	return TRUE;
}
///////////////////////////////////////////////////////

BOOL GL3dView::setupViewingTransform()
{
	
	return TRUE;
}



////////////////////////////////////////////////////////////////

void GL3dView:: RenderStockScene()
{
	CRect rect;
	GetClientRect(&rect);
	glClearColor(0.7f,0.75f,0.92f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//	GLint x,y,x1,y1;
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();
	
	gluPerspective(45.0f,(GLfloat)rect.Width()/(GLfloat)rect.Height(), 1.0f, 150.0f);
}
		
/*********************************************************************************************/

BOOL GL3dView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
		return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

void GL3dView::OnSize(UINT nType, int cx, int cy) 
{
	
	CView::OnSize(nType, cx, cy);

	GLfloat aspect_ratio;

	if(0>= cx || 0>= cy)
	{
		return;

	}

	SetupViewport(cx,cy);

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	aspect_ratio=(float)cx/(float)cy;

	SetupViewingFrustum(aspect_ratio);
	glDepthFunc(GL_LEQUAL);

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	setupViewingTransform();
	
	// TODO: Add your message handler code here
	
}

void GL3dView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	InitializeOpenGL();
}

BOOL GL3dView::InitializeOpenGL()
{
	 //g_Load3ds[0].Import3DS(&g_Load3ds[0].g_3DModel[0],"data\\chair1.3DS");
	 //g_Load3ds[0].Import3DS(g_Load3ds[0].g_3DModel,"data\\teapot.3ds"); /*Bloacked temporarely*/
	
/*	for(int i = 0; i < g_Load3ds[0].g_3DModel[0].numOfMaterials; i++)
	{
		// Check to see if there is a file name to load in this material
	if(strlen(g_Load3ds[0].g_3DModel[0].pMaterials[i].strFile) > 0)
		{
			// Use the name of the texture file to load the bitmap, with a texture ID (i).
			// We pass in our global texture array, the name of the texture, and an ID to reference it.	
			//CreateTexture(g_Texture, g_Load3ds[0].g_3DModel[0].pMaterials[i].strFile, i);			
		 }

		// Set the texture ID for this material
		g_Load3ds[0].g_3DModel[0].pMaterials[i].texureId = i;
	}
	
	g_Load3ds[1].Import3DS(&g_Load3ds[1].g_3DModel[1],"data\\a3_chaisebridge.3DS");
	
	for(int j= 0; j< g_Load3ds[1].g_3DModel[1].numOfMaterials; j++)
	{
		// Check to see if there is a file name to load in this material
		if(strlen(g_Load3ds[1].g_3DModel[1].pMaterials[j].strFile) > 0)
		{
			// Use the name of the texture file to load the bitmap, with a texture ID (i).
			// We pass in our global texture array, the name of the texture, and an ID to reference it.	
	//		CreateTexture(g_Texture, g_Load3ds.g_3DModel.pMaterials[i].strFile, i);			
		}

		// Set the texture ID for this material
		g_Load3ds[1].g_3DModel[1].pMaterials[j].texureId = j;
	}
	
	 g_Load3ds[2].Import3DS(&g_Load3ds[2].g_3DModel[2],"data\\a3_chaisebridge.3DS");
	
	for( j= 0; j< g_Load3ds[2].g_3DModel[2].numOfMaterials; j++)
	{
		// Check to see if there is a file name to load in this material
		if(strlen(g_Load3ds[2].g_3DModel[2].pMaterials[j].strFile) > 0)
		{
			// Use the name of the texture file to load the bitmap, with a texture ID (i).
			// We pass in our global texture array, the name of the texture, and an ID to reference it.	
		//	CreateTexture(g_Texture, g_Load3ds.g_3DModel.pMaterials[i].strFile, i);			
		}

		// Set the texture ID for this material
		g_Load3ds[2].g_3DModel[2].pMaterials[j].texureId = j;
	}
	g_Load3ds[3].Import3DS(&g_Load3ds[3].g_3DModel[3],"data\\a3_chaisebridge.3DS");
	
	for( j= 0; j< g_Load3ds[3].g_3DModel[3].numOfMaterials; j++)
	{
		// Check to see if there is a file name to load in this material
		if(strlen(g_Load3ds[3].g_3DModel[3].pMaterials[j].strFile) > 0)
		{
			// Use the name of the texture file to load the bitmap, with a texture ID (i).
			// We pass in our global texture array, the name of the texture, and an ID to reference it.	
		//	CreateTexture(g_Texture, g_Load3ds.g_3DModel.pMaterials[i].strFile, i);			
		}

		// Set the texture ID for this material
		g_Load3ds[3].g_3DModel[3].pMaterials[j].texureId = j;
	}
	g_Load3ds[4].Import3DS(&g_Load3ds[4].g_3DModel[4],"data\\a3_chaisebridge.3DS");
	
	for( j= 0; j< g_Load3ds[4].g_3DModel[4].numOfMaterials; j++)
	{
		// Check to see if there is a file name to load in this material
		if(strlen(g_Load3ds[4].g_3DModel[4].pMaterials[j].strFile) > 0)
		{
			// Use the name of the texture file to load the bitmap, with a texture ID (i).
			// We pass in our global texture array, the name of the texture, and an ID to reference it.	
		//	CreateTexture(g_Texture, g_Load3ds.g_3DModel.pMaterials[i].strFile, i);			
		}

		// Set the texture ID for this material
		g_Load3ds[4].g_3DModel[4].pMaterials[j].texureId = j;
	}
	*/

	CArchDoc*  pDoc = (CArchDoc*)GetDocument();
	m_pDC= new CClientDC(this);

	if (NULL==m_pDC)
	{
		SetError(1);
		return FALSE;
	}

	if (!SetupPixelFormat())
	{
		return FALSE;
	}
		if(0==(m_hRC =
			::wglCreateContext(m_pDC->GetSafeHdc())))
		{
			SetError(4);
			return FALSE;
		}

		if(FALSE==::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC))
		{
			SetError(5);
			return FALSE;

		}

		::glClearColor(.0f,.0f,.0f,.0f);
		::glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		//CRect r;
		//GetClientRect(&r);
		//CVector3 vPos,vView,vUp;
		//vPos=ConvertPoint((r.left+r.right)/2,1.5,-5);
		g_Camera.PositionCamera(0.0f, 1.5f, 6,   0, 1.5f, 0,   0, 1, 0);
		//g_Camera.m_vPosition=vPos;
		g_Camera.RotateView(-65,0,1,0);
		//g_Camera.PositionCamera(vPos.x,vPos.y,vPos.z,0,1.5f,0,0,1,0);

//	}
		
		
		
		return TRUE;
	}

/*
void GL3dView::OnView2d() 
{
	// TODO: Add your command handler code here
	if (FALSE== ::wglDeleteContext(m_hRC))
			{
				SetError(6);
			}
			if(m_pDC)
			{
				delete m_pDC;
			}
			//AfxMessageBox("b from 3DHome");	
	((CChildFrame*)GetParentFrame())->SelectView(1);
}
*/

/*void GL3dView::OnKeyDown(int key, int x ,int y)
{
	switch(key)
	{
	case GLUT_KEY_UP: glTranslatef(0,0,5);break;
	case GLUT_KEY_DOWN:glTranslatef(0,0,-5);break;
	}
RenderScene();
}*/


void GL3dView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CString c,d;
	char a[10];
	char b[10];
	
	
	CArchDoc*  pDoc = (CArchDoc*)GetDocument();
    CFloor* pCurFlr;
            for(int k=pDoc->m_Building.GetFloorCount()-1;k>=0;k--)
			{
	    	pCurFlr= pDoc->m_Building.GetFloorAt(k);
	 	    total_element=total_element+pCurFlr->GetElementCount();
			fHeight = 6.0f * (k-1);
            
	switch (nChar)
	{
	
	case VK_INSERT:
		{
	      	g_Camera.MoveCamera(kSpeed-0.1);
			g_Camera.m_vPosition.y += 0.5;
			g_Camera.m_vUpVector.y += 0.5;
			g_Camera.m_vView.y += 0.5;
		}
		break;
	
	case VK_SHIFT:
		{
			if(k==0&&pDoc->loc3>=1)
			{
				if (g_Camera.m_vPosition.y>-5.0)
				{
	      			g_Camera.MoveCamera(kSpeed-0.1);
				g_Camera.m_vPosition.y -= 0.5;
			g_Camera.m_vUpVector.y -= 0.5;
					g_Camera.m_vView.y -= 0.5;
				}
			}
			else
			{
				g_Camera.m_vPosition.y += 0;
				g_Camera.m_vUpVector.y += 0;
				g_Camera.m_vView.y += 0;
			}
		}
		break;
	
	
	case VK_ESCAPE:
		{
		/*	if (g_Camera.m_vPosition.y>1.5)
			{
				g_Camera.MoveCamera(kSpeed-0.1);
				g_Camera.m_vPosition.y -= 0.5;
				g_Camera.m_vUpVector.y -= 0.5;
				g_Camera.m_vView.y -= 0.5;
			}*/
		}
		break;
	case VK_HOME:
		{
			if(collision_detect(total_element))
			{
		    g_Camera.m_vPosition.y += 0;
			g_Camera.m_vUpVector.y += 0;
			g_Camera.m_vView.y += 0;
			}
			else

			{	
			g_Camera.m_vPosition.y += 1;
			g_Camera.m_vUpVector.y += 1;
			g_Camera.m_vView.y += 1;
		}
		}
			break;
	case VK_NUMPAD0: 
		g_Camera.MoveCamera(-kSpeed);
		break;
	
	case VK_END:
		if(collision_detect(total_element))
			{
		    g_Camera.m_vPosition.y += 0;
			g_Camera.m_vUpVector.y += 0;
			g_Camera.m_vView.y += 0;
			}
			else
			if (g_Camera.m_vPosition.y>1.5)
		//	{
				g_Camera.m_vPosition.y -= 1;
				g_Camera.m_vUpVector.y -= 1;
				g_Camera.m_vView.y -= 1;
		//	}
			break;
	case VK_UP:
	   	//gcvt(g_Camera.m_vPosition.z, 3, a); 
		//gcvt(CV1[0].z, 3, b); 
	//	d=CString(b);
	//	c=CString(a);
	//	AfxMessageBox(c);
    //     AfxMessageBox(d);
		//{
		if(collision_detect(total_element))
           g_Camera.MoveCamera(0.0);
		else	
			g_Camera.MoveCamera(kSpeed+0.01);
		/*if(collision_detect(pCurFlr[1]->GetElementCount()))
           g_Camera.MoveCamera(0.0);
		else	
			g_Camera.MoveCamera(kSpeed);
		if(collision_detect(pCurFlr[2]->GetElementCount()))
           g_Camera.MoveCamera(0.0);
		else	
			g_Camera.MoveCamera(kSpeed);*/
	//	if(collision_detect(pCurFlr[3]->GetElementCount()))
      //     g_Camera.MoveCamera(0.0);
	//	else	
	//		g_Camera.MoveCamera(kSpeed);
		//}
			break;
	case VK_DOWN:
		if(collision_detect(total_element))
           g_Camera.MoveCamera(0.0);
		else	
		g_Camera.MoveCamera(-kSpeed);
			break;
	case VK_RIGHT:
		      g_Camera.RotateView(-kSpeed, 0, 1, 0);
		   	
		//g_Camera.RotateAroundPoint(g_Camera.m_vView, -kSpeed, 0, 1, 0);
			break;
	case VK_LEFT:
		g_Camera.RotateView(kSpeed, 0, 1, 0);
			
		//g_Camera.RotateAroundPoint(g_Camera.m_vView, kSpeed, 0, 1, 0);
			break;
	}
	}
	GetDocument()->UpdateAllViews(0);	

}




void GL3dView::Stairs()
{
	double d;
	const double Max=6.0;
	for (d=0.0; d<Max; d += 0.5)
	{
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
			glTranslated(0,d,d);
			glScaled(2.0,1.0,1.0);
			glutSolidCube(0.5);
		glPopMatrix();
		
		//glColor3f(0.5f,0.25f,0.125f);
		glColor3ub(150,100, 50);
		glPushMatrix();
			glTranslated(0.45,d+0.5,d);
			glScaled(1.0,10.0,3.0);
			glutSolidCube(0.1);
		glPopMatrix();
	}
	glPushMatrix();
		glRotatef(-45.0f,1.0,0.0,0.0);
		glTranslated(0.5,0.90,4.50);
		glScaled(1.0,1.0,40.0);
		glutSolidCube(0.2);
	glPopMatrix();
}

void GL3dView::DrawGrid()
{
	// This function was added to give a better feeling of moving around.
	// A black background just doesn't give it to ya :)  We just draw 100
	// green lines vertical and horizontal along the X and Z axis.

	// Turn the lines GREEN
/*	glColor3ub(0, 255, 0);
	BITMAP  bmp;
	CBitmap b;
	b.LoadBitmap(IDB_BITMAP1);
	b.GetBitmap(&bmp);*/
	
	// Draw a 1x1 grid along the X and Z axis'
	for(float i = -100; i <= 100; i += 1)
	{
		// Start drawing some lines
		glBegin(GL_LINE_STRIP);

			// Do the horizontal lines (along the X)
			glVertex3f(-100, -10, i);
			glVertex3f(100, -10, i);
			

			// Do the vertical lines (along the Z)
			glVertex3f(i, -10, -100);
			glVertex3f(i, -10, 100);

		// Stop drawing lines
		glEnd();
	}
}

void GL3dView::DrawWall(CWall *pWall,int i)
{
	CArchDoc*  pDoc = (CArchDoc*) GetDocument();
	ASSERT_VALID(pDoc);
	CPoint P1,P2;
	float BPY,TPY,h1;
	BPY=pWall->m_basep;
	TPY=pWall->m_topp;
	h1=TPY/20.0f;
	if ((pWall->m_ptFirstPosition.x < pWall->m_ptSecondPosition.x &&  pWall->m_ptFirstPosition.y <  pWall->m_ptSecondPosition.y)||
       (pWall->m_ptFirstPosition.x == pWall->m_ptSecondPosition.x &&  pWall->m_ptFirstPosition.y <  pWall->m_ptSecondPosition.y)||
	   (pWall->m_ptFirstPosition.x <  pWall->m_ptSecondPosition.x &&  pWall->m_ptFirstPosition.y == pWall->m_ptSecondPosition.y))
	{
		P1 = pWall->m_ptFirstPosition;
		P2 = pWall->m_ptSecondPosition;
	}
	
	else 
	
	{
		P1 = pWall->m_ptSecondPosition;
		P2 = pWall->m_ptFirstPosition;
	}
	//loadtextures(pWall->m_SideATexture,pWall->m_SideATexture);
  
	CVector3 V1,V2,V3,V4;
	w_count1[loc2]=count_loc;
	loc2=loc2+1;
    count_loc=count_loc+1; 	
	/*if(BPY>0&&TPY<120)
	{
		V1=ConvertPoint(P1.x,BPY,P1.y);
		V2=ConvertPoint(P2.x,BPY,P2.y);
		V3=ConvertPoint(P1.x,0,P1.y);
		V4=ConvertPoint(P2.x,0,P2.y);
		
		if(i==0)
		{
			CV1[count_fs].y=V1.y;
			CV2[count_fs].y=V2.y;
		}	
		else
			if(i==1)
			{
				CV1[count_fs].y=V1.y;
				CV2[count_fs].y=V2.y;
			}	
			else
				if(i==2)
				{
					CV1[count_fs].y=V1.y;
					CV2[count_fs].y=V2.y;
				}	
				else
					if(i==3)
					{
						CV1[count_fs].y=V1.y;
						CV2[count_fs].y=V2.y;
					}	
    CV1[count_fs].x=V1.x;
    CV1[count_fs].z=V1.z;
	CV2[count_fs].x=V2.x;
	CV2[count_fs].z=V2.z;
	count_fs=count_fs+1;
	s_count++;
	//	spoint[count_s]=P2.y;
	//	count_s++;
	if(pWall->m_IsTexturizedSideA && pWall->m_IsTexturizedSideB)
	  DrawBlockTex(V1,V2,pWall->m_uiWidth,120.0-BPY,pWall->m_SideATexture,pWall->m_SideBTexture);
	else
     DrawBlock(V1,V2,pWall->m_uiWidth,120.0-BPY,pWall->m_SideAColor,pWall->m_SideBColor);
	
//DrawWidowBlock(V1,V2,V3,V4,pWall->m_uiWidth,120.0-BPY,120.0-TPY,pWall->m_SideAColor,pWall->m_SideBColor);
	}*/

	
	if(BPY>0&&BPY<120)
	{
		V1=ConvertPoint(P1.x,BPY,P1.y);
		V2=ConvertPoint(P2.x,BPY,P2.y);
		if(i==0)
		{
			CV1[count_fs].y=V1.y;
			CV2[count_fs].y=V2.y;
		}	
		else
			if(i==1)
			{
				CV1[count_fs].y=V1.y;
				CV2[count_fs].y=V2.y;
			}	
			else
				if(i==2)
				{
					CV1[count_fs].y=V1.y;
					CV2[count_fs].y=V2.y;
				}	
				else
					if(i==3)
					{
						CV1[count_fs].y=V1.y;
						CV2[count_fs].y=V2.y;
					}	
    CV1[count_fs].x=V1.x;
    CV1[count_fs].z=V1.z;
	CV2[count_fs].x=V2.x;
	CV2[count_fs].z=V2.z;
	count_fs=count_fs+1;
	s_count++;
	//	spoint[count_s]=P2.y;
	//	count_s++;
	if(pWall->m_IsTexturizedSideA && pWall->m_IsTexturizedSideB)
	  DrawBlockTex(V1,V2,pWall->m_uiWidth,120.0-BPY,pWall->m_SideATexture,pWall->m_SideBTexture);
	else
     DrawBlock(V1,V2,pWall->m_uiWidth,120.0-BPY,pWall->m_SideAColor,pWall->m_SideBColor);
	}
	else
		if(TPY>0&&TPY<120)
		{
			
			V1=ConvertPoint(P1.x,0,P1.y);
			V2=ConvertPoint(P2.x,0,P2.y);
			if(i==0)
			{
				CV1[count_fs].y=-6.0;
				CV2[count_fs].y=0.0;
			}	
			else
				if(i==1)
				{
					CV1[count_fs].y=0.0;
					CV2[count_fs].y=6.0;
				}		
				else
					if(i==2)
					{
						CV1[count_fs].y=6.0;
						CV2[count_fs].y=12.0;
					}	
					else
						if(i==3)
						{
							CV1[count_fs].y=12.0;
							CV2[count_fs].y=18.0;
						}	
	CV1[count_fs].x=V1.x;
    CV1[count_fs].z=V1.z;
	CV2[count_fs].x=V2.x;
	CV2[count_fs].z=V2.z;
	count_fs=count_fs+1;
	s_count++;
	//	spoint[count_s]=P2.y;
	//	count_s++;
	if(pWall->m_IsTexturizedSideA && pWall->m_IsTexturizedSideB)
	  DrawBlockTex(V1,V2,pWall->m_uiWidth,120.0-TPY,pWall->m_SideATexture,pWall->m_SideBTexture);
	else
     DrawBlock(V1,V2,pWall->m_uiWidth,120.0-TPY,pWall->m_SideAColor,pWall->m_SideBColor);
	}
	else
		if(BPY==0&&TPY==120)
		{
			V1=ConvertPoint(P1.x,0,P1.y);
			V2=ConvertPoint(P2.x,0,P2.y);
			if(i==0)
			{
				CV1[count_fs].y=-6.0;
				CV2[count_fs].y=0.0;
			}	
			else
				if(i==1)
				{
					CV1[count_fs].y=0.0;
					CV2[count_fs].y=6.0;
				}	
				else
					if(i==2)
					{
						CV1[count_fs].y=6.0;
						CV2[count_fs].y=12.0;
					}	
					else
						if(i==3)
						{
							CV1[count_fs].y=12.0;
							CV2[count_fs].y=18.0;
						}	
    CV1[count_fs].x=V1.x;
    CV1[count_fs].z=V1.z;
	CV2[count_fs].x=V2.x;
	CV2[count_fs].z=V2.z;
	count_fs=count_fs+1;
	//s_count++;
	//	spoint[count_s]=P2.y;
	//	count_s++;
	if(pWall->m_IsTexturizedSideA && pWall->m_IsTexturizedSideB)
	  DrawBlockTex(V1,V2,pWall->m_uiWidth,120.0,pWall->m_SideATexture,pWall->m_SideBTexture);
		else
			DrawBlock(V1,V2,pWall->m_uiWidth,120.0,pWall->m_SideAColor,pWall->m_SideBColor);
	}
/*CPoint P1,P2;
	float PY;
	PY=pWall->m_basep;
	if ((pWall->m_ptFirstPosition.x < pWall->m_ptSecondPosition.x &&  pWall->m_ptFirstPosition.y <  pWall->m_ptSecondPosition.y)||
       (pWall->m_ptFirstPosition.x == pWall->m_ptSecondPosition.x &&  pWall->m_ptFirstPosition.y <  pWall->m_ptSecondPosition.y)||
	   (pWall->m_ptFirstPosition.x <  pWall->m_ptSecondPosition.x &&  pWall->m_ptFirstPosition.y == pWall->m_ptSecondPosition.y))
	{
		P1 = pWall->m_ptFirstPosition;
		P2 = pWall->m_ptSecondPosition;
	}
	
	else 
	
	{
		P1 = pWall->m_ptSecondPosition;
		P2 = pWall->m_ptFirstPosition;
	}
	//loadtextures(pWall->m_SideATexture,pWall->m_SideATexture);
  
	CVector3 V1,V2;
	fw_count1[loc1]=loc1;
    loc1=loc1+1;
	V1=ConvertPoint(P1.x,PY,P1.y);
	V2=ConvertPoint(P2.x,PY,P2.y);
		//	glTranslatef(0,fHeight,0);
   if(i==0)
   {
    CV1[count_fs].y=-6.0;
    CV2[count_fs].y=0.0;
   // CV3[count_fs].y=-6.0;
   // CV4[count_fs].y=0.0;
   
   }	
   else

	 if(i==1)
	 {
      CV1[count_fs].y=0.0;
	  CV2[count_fs].y=6.0;
	//  CV3[count_fs].y=0.0;
	  //CV4[count_fs].y=6
	 }	
   
	else
	 if(i==2)
	 {
      CV1[count_fs].y=6.0;
	  CV2[count_fs].y=12.0;
//	  CV3[count_fs].y=6.0;
//	  CV4[count_fs].y=12.0;
	 
	 }	
   else
	 if(i==3)
	 {
      CV1[count_fs].y=12.0;
	  CV2[count_fs].y=18.0;
//	  CV3[count_fs].y=6.0;
//	  CV4[count_fs].y=12.0;
	 
	 }	
    
	 
	CV1[count_fs].x=V1.x;
    CV1[count_fs].z=V1.z;
	CV2[count_fs].x=V2.x;
	CV2[count_fs].z=V2.z;
//	CV3[count_fs].x=V1.x;
  //  CV3[count_fs].z=V1.z;
	//CV4[count_fs].x=V2.x;
//	CV4[count_fs].z=V2.z;
	
	count_fs=count_fs+1;
	s_count++;
	
	
	
//	spoint[count_s]=P2.y;
//	count_s++;
	
	
	
	if(pWall->m_IsTexturizedSideA && pWall->m_IsTexturizedSideB)
	  DrawBlockTex(V1,V2,pWall->m_uiWidth,120.0,pWall->m_SideATexture,pWall->m_SideBTexture);
	else
     DrawBlock(V1,V2,pWall->m_uiWidth,120.0,pWall->m_SideAColor,pWall->m_SideBColor);
*/	
  }

void GL3dView::ChangeGLColor(COLORREF color)
{
	glColor3ub(GetRValue(color), GetGValue(color),GetBValue(color));
}

CVector3 GL3dView::ConvertPoint(long x, long y, long z)
{
	
	CVector3 Point;
	Point.x = x/20.0f;
	Point.y = y/20.0f;
	Point.z = z/20.0f;
	return Point;

}

void GL3dView::DrawPillar(CPillar *pPillar,int i)
{
		CArchDoc*  pDoc = (CArchDoc*) GetDocument();
	ASSERT_VALID(pDoc);
	CVector3 vPos(pPillar->m_ptPosition.x,pPillar->m_uiHeight/2,pPillar->m_ptPosition.y);
	vPos = ConvertPoint(vPos.x,0,vPos.z);
	UINT Type    = pPillar->m_uiType;
	float Height = 0;
	float Width  = pPillar->m_uiWidth/20.0f;
	if(i==0)
	{
		CV1[count_fs].y=6.0;
		CV2[count_fs].y=0.0;
	}	
	else
	if(i==1)
	{
		CV1[count_fs].y=0.0;
		CV2[count_fs].y=6.0;
	}	
	else
	if(i==2)
	{
		CV1[count_fs].y=6.0;
		CV2[count_fs].y=12.0;
	}	
	else
	if(i==3)
	{
		CV1[count_fs].y=12.0;
		CV2[count_fs].y=18.0;
	}	
    CV1[count_fs].x=vPos.x-(Width/2);
    CV1[count_fs].z=vPos.z-(Width/2) ;
    CV2[count_fs].x=vPos.x+(Width/2);
    CV2[count_fs].z=vPos.z+(Width/2);
    count_fs=count_fs+1;
//	w_count1[loc2]=count_loc;
//	loc2=loc2+1;
//	count_loc=count_loc+1;
	pflag=1;
	ChangeGLColor(pPillar->m_Color);
	//glColor3ub(GetRValue(color),GetGValue(color),GetBValue(color));
	if(Type==1)
	{
		glPushMatrix();
		if(j==0)
			glTranslatef(vPos.x,0+3.0,vPos.z);
			else
            glTranslatef(vPos.x,fHeight+3.0,vPos.z);
			 
		glScalef(1.0f,10.0f,1.0f);
		glutSolidCube(Width);
		glPopMatrix();
	}
	else
	{
		GLUquadricObj *obj=gluNewQuadric();
		glPushMatrix();
		if(j==0) 
			glTranslated(vPos.x,0,vPos.z);
			else
		    glTranslated(vPos.x,fHeight,vPos.z);
		glRotatef(-90,1,0,0);
		gluCylinder(obj,Width/2.0,Width/2.0,6.0f,360,2);//converted into diametere
		glPopMatrix();
	}
}


void GL3dView::DrawFixtureWall(CFixtureWall *pfWall)
{
	CArchDoc*  pDoc = (CArchDoc*) GetDocument();
	ASSERT_VALID(pDoc);
	CPoint P1,P2;
	CPoint LP3,RP4;
    CPoint WLP,WRP; 
	P1 = pfWall->m_ptFirstPosition;
	P2 = pfWall->m_ptSecondPosition;
	LP3=pfWall->m_door.m_ConnectedPoint;
	RP4=pfWall->m_door.m_bottompoint;
  	WLP=pfWall->m_window.m_ConnectedPoint;
	WRP=pfWall->m_window.m_bottompoint;
	
	CVector3 V1,V2,V3,V4,V5,V6,V7,V8;
	V1=ConvertPoint(P1.x,0,P1.y);
	V2=ConvertPoint(P2.x,0,P2.y);
	V3=ConvertPoint(P1.x+LP3.x,0,P1.y);
	V4=ConvertPoint(P1.x+RP4.x,0,P1.y);
	V5=ConvertPoint(P1.x+WLP.x,0,P1.y);
	V6=ConvertPoint(P1.x+WRP.x,0,P1.y);


		//	glTranslatef(0,fHeight,0);
   	fw_count1[loc1]=count_loc;
	loc1=loc1+1;
    count_loc=count_loc+1; 	
//	s_count=s_count+1;
	
if(pfWall->m_isdoor==TRUE && pfWall->m_iswindow==TRUE)
	{
	DrawBothBlock(V1, V2, V3, V4,V5,V6,  pfWall->m_uiWidth,120.0, pfWall->m_SideAColor,pfWall->m_SideBColor);
//pfWall->m_isdoor=FALSE;
//pfWall->m_iswindow=FALSE;
	}
else	
 if (pfWall->m_isdoor==TRUE)
{
   if(i==0)
   {
    CV3[fw_count].y=-6.0;
    CV4[fw_count].y=0.0;
	CV5[fw_count].y=2.25;
    CV6[fw_count].y=0.0;

   }	
   else

	 if(i==1)
	 {
		CV3[fw_count].y=0.0;
		CV4[fw_count].y=6.0;
		CV5[fw_count].y=3.75;
		CV6[fw_count].y=6.0;
 	 }	
   
else
	 if(i==2)
	 {
	    CV3[fw_count].y=6.0;
		CV4[fw_count].y=12.0;
		CV5[fw_count].y=9.75;
		CV6[fw_count].y=12.0;
	 }	
   else
	 if(i==3)
	 {
		CV3[fw_count].y=12.0;
		CV4[fw_count].y=18.0;
		CV5[fw_count].y=15.75;
		CV6[fw_count].y=18.0;
	 }	
    
	 
	CV3[fw_count].x=V1.x;
    CV3[fw_count].z=V1.z;
	CV4[fw_count].x=V2.x;
	CV4[fw_count].z=V2.z;
    CV5[fw_count].x=V3.x;
    CV5[fw_count].z=V3.z;
	CV6[fw_count].x=V4.x;
	CV6[fw_count].z=V4.z;
	fw_count=fw_count+1;
	s_count++;
	
		DrawBlockDoor(V1,V2,V3,V4,pfWall->m_uiWidth,120.0,pfWall->m_SideAColor,pfWall->m_SideBColor);

	}
else
	if (pfWall->m_iswindow==TRUE)
	{
			
			DrawBlockWindow(V1,V2,V5,V6,pfWall->m_uiWidth,120.0,pfWall->m_SideAColor,pfWall->m_SideBColor);
	
	
	}
	
	
}
void GL3dView::DrawBlock(CVector3 P1, CVector3 P2, float Width, float Height, COLORREF aColor, COLORREF bColor)
{
	CVector3 T1=P1,V1=P1,V2=P2,T2=V2;
	float Theta=(float)atan2((V2.z-V1.z),(V2.x-V1.x));
	float Angle= -(Theta * 180.0 / 3.1416f);
	float l,w,h;
    l=V2.Difference(V1);
	h=Height/20.0f;
	w=Width/20.0f;
	CVector3 U1(0,0,0),U2(l,0,0),U3(l,0,w),U4(0,0,w);
	glPushMatrix();
		if(j==0)
			glTranslatef(T1.x,T1.y,T1.z);
			else
			glTranslatef(T1.x,T1.y+fHeight,T1.z);
		glRotatef(Angle,0,1,0);
		glBegin(GL_QUADS);
		//Bottom	
		glVertex3f(U1.x,U1.y,U1.z);
		glVertex3f(U2.x,U2.y,U2.z);
	    glVertex3f(U3.x,U3.y,U3.z);
	    glVertex3f(U4.x,U4.y,U4.z);
		//Front sideA	
		ChangeGLColor(aColor);
		glVertex3f(U1.x,U1.y,U1.z);
		glVertex3f(U2.x,U2.y,U2.z);
		glVertex3f(U2.x,U2.y+h,U2.z);
		glVertex3f(U1.x,U1.y+h,U1.z);
		//Back sideB
		ChangeGLColor(bColor);
		glVertex3f(U3.x,U3.y,U3.z);
		glVertex3f(U4.x,U4.y,U4.z);
		glVertex3f(U4.x,U4.y+h,U4.z);
		glVertex3f(U3.x,U3.y+h,U3.z);
		// Side c
		glVertex3f(U1.x,U1.y,U1.z);
		glVertex3f(U4.x,U4.y,U4.z);
		glVertex3f(U4.x,U4.y+h,U4.z);
		glVertex3f(U1.x,U1.y+h,U1.z);
		// Side d
		glVertex3f(U2.x,U2.y,U2.z);
		glVertex3f(U3.x,U3.y,U3.z);
		glVertex3f(U3.x,U3.y+h,U3.z);
		glVertex3f(U2.x,U2.y+h,U2.z);
		glEnd();
	glPopMatrix();
} 





void GL3dView::DrawCurvedWall(CCurvedWall *pCWall)
{
	 CPoint FirstPosition;
	 CPoint SecondPosition;
	 CPoint ControlPoint1=pCWall->m_ptControlPosition1;
	 CPoint ControlPoint2=pCWall->m_ptControlPosition2;

//	if ((pCWall->m_ptFirstPosition.x < pCWall->m_ptSecondPosition.x &&  pCWall->m_ptFirstPosition.y <  pCWall->m_ptSecondPosition.y)||
  //     (pCWall->m_ptFirstPosition.x == pCWall->m_ptSecondPosition.x &&  pCWall->m_ptFirstPosition.y <  pCWall->m_ptSecondPosition.y)||
//	   (pCWall->m_ptFirstPosition.x <  pCWall->m_ptSecondPosition.x &&  pCWall->m_ptFirstPosition.y == pCWall->m_ptSecondPosition.y))/
//	{
		FirstPosition = pCWall->m_ptFirstPosition;
		SecondPosition = pCWall->m_ptSecondPosition;
//	}
	
//	else 
	
//	{
//		FirstPosition =  pCWall->m_ptSecondPosition;
//		SecondPosition = pCWall->m_ptFirstPosition;
//	}

	float m_uiHeight=120/20.0f;
    float m_uiWidth=9/20.0f;
    CVector3 V1,V2,V3,V4;
	V1 = ConvertPoint(FirstPosition.x,0,FirstPosition.y);
	V2 = ConvertPoint(SecondPosition.x,0,SecondPosition.y);
	V3 = ConvertPoint(ControlPoint1.x,0,ControlPoint1.y);
	V4 = ConvertPoint(ControlPoint2.x,0,ControlPoint2.y);


       if(i==0)
		{
			CV9[cw_count].y=-6.0;
			CV10[cw_count].y=0.0;
		    CV11[cw_count].y=-6.0;
			CV12[cw_count].y=0.0;
			
	   
	   }	
		else
			if(i==1)
			{
				CV9[cw_count].y=0.0;
				CV10[cw_count].y=6.0;
				CV11[cw_count].y=-6.0;
			    CV12[cw_count].y=0.0;
		
			}	
			else
				if(i==2)
				{
					CV9[cw_count].y=6.0;
					CV10[cw_count].y=12.0;
			    	CV11[cw_count].y=-6.0;
					CV12[cw_count].y=0.0;
		
				}	
				else
					if(i==3)
					{
						CV9[cw_count].y=12.0;
						CV10[cw_count].y=18.0;
						CV11[cw_count].y=-6.0;
						CV12[cw_count].y=0.0;
		
					}	
    CV9[cw_count].x=V1.x;
    CV9[cw_count].z=V1.z;
	CV10[cw_count].x=V2.x;
	CV10[cw_count].z=V2.z;
	CV11[cw_count].x=V3.x;
    CV11[cw_count].z=V3.z;
	CV12[cw_count].x=V4.x;
	CV12[cw_count].z=V4.z;
	
	
	//count_fs=count_fs+1;
	cw_count=cw_count+1;
	s_count++;

	 COLORREF m_SideAColor=pCWall->m_SideAColor;
	 COLORREF m_SideBColor=pCWall->m_SideBColor;

//	 CBitMap m_SideATexture;
//	 CBitMap m_SideBTexture;
//	   BOOL   m_IsTexturizedSideA;
//	   BOOL   m_IsTexturizedSideB;
	 
	 

		
	float surface[3][4][3]= {{{V1.x,0,V1.z},{V3.x,0,V3.z},{V4.x,0,V4.z},{V2.x,0,V2.z} },
							{{V1.x,m_uiHeight/2,V1.z},{V3.x,m_uiHeight/2,V3.z},{V4.x,m_uiHeight/2,V4.z},{V2.x,m_uiHeight/2,V2.z} },
							{{V1.x,m_uiHeight,V1.z},{V3.x,m_uiHeight,V3.z},{V4.x,m_uiHeight,V4.z},{V2.x,m_uiHeight,V2.z} }
							};



	
	glColor3ub(GetRValue(m_SideAColor),GetGValue(m_SideAColor),GetBValue(m_SideAColor));
	glMap2f(GL_MAP2_VERTEX_3,0.0,10.0,3,4,0.0,10.0,12,3,&surface[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEvalMesh2(GL_FILL,0,10,0,10);
			
	
/*	float surface2[3][4][3]= {  {	{V1.x,0,V1.z+m_uiWidth},{V3.x,0,V3.z+m_uiWidth},{V4.x,0,V4.z+m_uiWidth},{V2.x,0,V2.z+m_uiWidth} },
								{	{V1.x,m_uiHeight/2,V1.z+m_uiWidth},{V3.x,m_uiHeight/2,V3.z+m_uiWidth},{V4.x,m_uiHeight/2,V4.z+m_uiWidth},{V2.x,m_uiHeight/2,V2.z+m_uiWidth} },
								{	{V1.x,m_uiHeight,V1.z+m_uiWidth},{V3.x,m_uiHeight,V3.z+m_uiWidth},{V4.x,m_uiHeight,V4.z+m_uiWidth},{V2.x,m_uiHeight,V3.z+m_uiWidth} }
								
							};




	glColor3ub(GetRValue(m_SideBColor),GetGValue(m_SideBColor),GetBValue(m_SideBColor));
	glMap2f(GL_MAP2_VERTEX_3,0.0,10.0,3,4,0.0,10.0,12,3,&surface2[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEvalMesh2(GL_FILL,0,10,0,10);
	
	glBegin(GL_QUADS);

		//glColor3ub(128,0,0);
		glVertex3f(V1.x,0,V1.y);					// Bottom Left Of The Quad (left)
		glVertex3f(V1.x, 0 ,V1.y+m_uiWidth);			// Bottom Right Of The Quad (left)
		glVertex3f(V1.x, m_uiHeight,V1.y+m_uiWidth);			// Top Right Of The Quad (left)
		glVertex3f(V1.x,m_uiHeight,V1.y);					// Top Left Of The Quad (left)
		
	
	

	//glColor3ub(128,0,0);						// Set The Color // 
		glVertex3f(V2.x,0,V2.y);							// Bottom Left Of The Quad (right)
		glVertex3f(V2.x,0,V2.y+m_uiWidth);					// Bottom Right Of The Quad (right)
		glVertex3f(V2.x,m_uiHeight,V2.y+m_uiWidth);					// Top Right Of The Quad (right)
		glVertex3f(V2.x,m_uiHeight,V2.y);							// Top Left Of The Quad (right)
	glEnd();*/	


	glPointSize(6.0);
		glBegin(GL_POINTS);
glColor3ub(128,128,0);
			for(int i=0; i<3; i++)
				for(int j=0; j<4; j++)
					glVertex3fv(&surface[i][j][0]);
		glEnd();



 	
}

void GL3dView::DrawStairs(CStairs *pStair)
{
	CArchDoc*  pDoc = (CArchDoc*) GetDocument();
	ASSERT_VALID(pDoc);
	CPoint P1,P2;
	P1 = pStair->m_ptFirstPosition;
	P2 = pStair->m_ptSecondPosition;
	CVector3 V1(P1.x,0,P1.y);
	CVector3  V2(P2.x,0,P2.y),T1,T2;
	V1=ConvertPoint(V1.x , 0 , V1.z);     //Changing Made MN   p.z
	V2=ConvertPoint(V2.x , 0 , V2.z);    //Changeing made MN   
	if(i==0)
	{
		CV7[sp_count].y=-6.0;
		CV8[sp_count].y=0.0;
	}	
	else
	if(i==1)
	{
		CV7[sp_count].y=0.0;
		CV8[sp_count].y=6.0;
	}	
	else
	if(i==2)
	{
		CV7[sp_count].y=6.0;
		CV8[sp_count].y=12.0;
	}	
	else
	if(i==3)
	{
		CV7[sp_count].y=12.0;
		CV8[sp_count].y=18.0;
	}	
    CV7[sp_count].x=V1.x;
    CV7[sp_count].z=V1.z;
	CV8[sp_count].x=V2.x;
    CV8[sp_count].z=V2.z;
	sp_count=sp_count+1;
	s_count1[loc2]=loc2;
	loc2=loc2+1;
	//count_loc=count_loc+1;
	//s_count=s_count+1;
	T1=V1;
	T2=V2;
	float Height=pStair->m_uiHeight;
	float Width=pStair->m_uiWidth;
	float Theta=(float)atan2((V2.z-V1.z),(V2.x-V1.x));
	float Angle= -(Theta * 180.0 / 3.1416f)+90.0;
	float Angle1= -(Theta * 180.0 / 3.1416f)+270.0;
	float l,w,h,l1,s;
	//AfxMessageBox("%d",)
	l=V2.Difference(V1);
	h=Height/20.0f;
	w=Width/20.0f;
	l1=l/12;
	double d;
	const double Max=0.0;
	
	glPushMatrix();
	if(i==0)
	{
		for (d=-6.0; d<Max; d += 0.5)
		{
			ChangeGLColor(pStair->m_StairColor);
		//	glColor3f(1.0,1.0,0.0);
			glPushMatrix();
			if(j==0)
			glTranslatef(T1.x,T1.y-d,T1.z);
			else
			glTranslatef(T1.x,T1.y+d,T1.z);	
		//	glTranslated(T1.x,d,T1.z);
				glRotated(Angle1,0,1,0);
				glTranslated(0,0,d);
    			glScaled(4.0,1.0,1.0);
				glutSolidCube(0.5);
			glPopMatrix();
		//	glColor3ub(150,100, 50);
		//	glPushMatrix();
		//		glTranslated(T1.x,d,T1.z);
		//		glRotated(Angle1,0,1,0);
		//		glTranslated(0.80,1.0,d);
		//			glScaled(1.0,10.0,3.0);
		//			glutSolidCube(0.1);
		//	glPopMatrix();
		}
		// glPushMatrix();
		//		glTranslated(T1.x,d,T1.z);
		//		glRotatef(-45.0f,0.0,1.0,0.0);
		//		glTranslated(T1.x,d,T1.z);
		//		glRotated(Angle,0,1,0);
		//		glRotated(-Angle1,1,0,0);
		//	glScaled(1.0,1.0,40.0);
		//	glutSolidCube(0.2);
		//   glPopMatrix();
	}
	else
	if(i==1)
	{
		for (d=0.0; d<l&&d<Max+6.0; d += 0.5)
		{
			ChangeGLColor(pStair->m_StairColor);
		//	glColor3f(1.0,1.0,0.0);
			glPushMatrix();
				glTranslated(T1.x,d,T1.z);
				glRotated(Angle,0,1,0);
				glTranslated(0,0,d);
				glScaled(4.0,1.0,l1+1.0);
				glutSolidCube(0.5);
			glPopMatrix();
		//	glColor3ub(150,100, 50);
		//  glPushMatrix();
		//		glTranslated(T1.x,d,T1.z);
		//		glRotated(Angle,0,1,0);
		//		glTranslated(0.80,1.0,d);
		//		glScaled(1.0,10.0,3.0);
		//		glutSolidCube(0.1);
		//	glPopMatrix();
		}  
		//	glPushMatrix();
		//		glRotatef(-45.0f,1.0,0.0,0.0);
		//		glTranslated(T1.x+0.5,6.0,T1.z+0.6);
		//		glScaled(1.0,1.0,40.0);
		//		glutSolidCube(0.2);
		//	glPopMatrix();
	}
	else
	if(i==2)
	{	
		s=l+6.0;
				
		for (d=6.0;d<s&&d<Max+12.0; d += 0.5)
		{
			ChangeGLColor(pStair->m_StairColor);
		//	glColor3f(1.0,1.0,0.0);
			glPushMatrix();
				glTranslated(T1.x,0,T1.z);
				glRotated(Angle,0,1,0);
				//glTranslated(T1.x,d,T1.z);
				glTranslated(0,d,d-6.0);
				glScaled(4.0,1.0,l1+1.0);
				glutSolidCube(0.5);
			glPopMatrix();
		//	glColor3ub(150,100, 50);
		//	glPushMatrix();
		//		glTranslated(T1.x,d,T1.z);
		//		glRotated(Angle,0,1,0);
		//		glTranslated(0.80,1.0,d);
		//		glScaled(1.0,10.0,3.0);
		//		glutSolidCube(0.1);
		//	glPopMatrix();
		}
		//	glPushMatrix();
		//		glRotatef(-45.0f,1.0,0.0,0.0);
		//		glTranslated(T1.x+0.5,12.0,T1.z+0.6);
		//		glScaled(1.0,1.0,40.0);
		//		glutSolidCube(0.2);
		//	glPopMatrix();
	}		 
	else
	if(i==3)
	{	
		s=l+12.0;
		for (d=12.0; d<s&&d<Max+18.0; d += 0.5)
		{
			ChangeGLColor(pStair->m_StairColor);	
		//	glColor3f(1.0,1.0,0.0);
			glPushMatrix();
				glTranslated(T1.x,0,T1.z);
				glRotated(Angle,0,1,0);
				glTranslated(0,d,d-12.0);
				glScaled(4.0,1.0,l1+1.0);
				glutSolidCube(0.5);
			glPopMatrix();
		    //	
			//	glColor3ub(150,100, 50);
		//	glPushMatrix();
		//		glTranslated(T1.x,d,T1.z);
		//		glRotated(Angle,0,1,0);
		//		glTranslated(0.80,1.0,d);
		//		glScaled(1.0,10.0,3.0);
		//		glutSolidCube(0.1);
		//	glPopMatrix();
		}
	}
	glPopMatrix();
}
void GL3dView::DrawCeiling(CPlane *pPlane)
{
	/*COLORREF Color=pPlane->m_Color;
	float Height=120/20.0f;
	//CArray<CPoint,CPoint&> BoundaryPoints;
	//BoundaryPoints.
	pPlane->m_BoundaryPoints;
	pPlane->m_TextureFile;
	glBegin(GL_POLYGON);
	
	for(int i=0; i < pPlane->m_BoundaryPoints.GetSize();i++)
	{
	glVertex3f(pPlane->m_BoundaryPoints[i].x,Height,pPlane->m_BoundaryPoints[i].y);
	}
*/
}

//DEL GL3dView::DrawCeiling(CCeiling *ceil)
//DEL {
//DEL 
//DEL }

void GL3dView::DrawCeiling(CCeiling *pCeil,int i)
{	CArchDoc*  pDoc = (CArchDoc*) GetDocument();
	ASSERT_VALID(pDoc);
CPoint P1,P2;
UINT d,L,ctp;
ctp=pCeil->m_uiHeight;
	if ((pCeil->m_ptFirstPosition.x < pCeil->m_ptSecondPosition.x &&  pCeil->m_ptFirstPosition.y <  pCeil->m_ptSecondPosition.y)||
       (pCeil->m_ptFirstPosition.x == pCeil->m_ptSecondPosition.x &&  pCeil->m_ptFirstPosition.y <  pCeil->m_ptSecondPosition.y)||
	   (pCeil->m_ptFirstPosition.x <  pCeil->m_ptSecondPosition.x &&  pCeil->m_ptFirstPosition.y == pCeil->m_ptSecondPosition.y))
	{
		P1 = pCeil->m_ptFirstPosition;
		P2 = pCeil->m_ptSecondPosition;
	}
	
	else 
	
	{
		P1 = pCeil->m_ptSecondPosition;
		P2 = pCeil->m_ptFirstPosition;
	}
	
	CVector3 V1,V2;
	
	V1=ConvertPoint(P1.x,ctp,P1.y);
	V2=ConvertPoint(P2.x,ctp,P2.y);
if(i==0)
   {
    CV1[count_fs].y=V2.y-1;
    CV2[count_fs].y=V2.y+3;
   }	
   else

	 if(i==1)
	 {
      CV1[count_fs].y=V2.y-1;
	  CV2[count_fs].y=V2.y+3;
	 }	
   
else
	 if(i==2)
	 {
      CV1[count_fs].y=V2.y-1;
	  CV2[count_fs].y=V2.y+3;
	 }	
   else
	 if(i==3)
	 {
      CV1[count_fs].y=V2.y-1;
	   CV2[count_fs].y=V2.y+3;
	 }	
    
	 
	CV1[count_fs].x=V1.x;
    CV1[count_fs].z=V1.z-0.2;
	CV2[count_fs].x=V2.x;
    CV2[count_fs].z=V2.z+0.2;
	count_fs=count_fs+1;
    s_count++;
	w_count1[loc2]=count_loc;
	loc2=loc2+1;
	count_loc=count_loc+1;
	d=pCeil->m_ptSecondPosition.x - pCeil->m_ptFirstPosition.x;
	L=pCeil->m_ptSecondPosition.y - pCeil->m_ptFirstPosition.y;
//pCeil->m_uiWidth=d;

	DrawBlock1(V1,V2,d,12.0,L,pCeil->m_SideAColor,pCeil->m_SideBColor);

}

void GL3dView::DrawBlock1(CVector3 P1, CVector3 P2, float Width, float Height,float Length, COLORREF aColor, COLORREF bColor)
{
	CVector3 T1=P1,V1=P1,V2=P2,T2=P2;
	float Theta=(float)atan2((V2.z-V1.z),(V2.x-V1.x));
	float Angle= -(Theta * 180.0 / 3.1416f);
	float l,w,h;
//	l=V2.Difference(V1);
	h=Height/20.0f;
    l=Length/20.0f;
	w=Width/20.0f;
	CVector3 U1(0,0,0),U2(w,0,0),U3(w,0,l),U4(0,0,l);
	
	glPushMatrix();
		if(j==0)
		{
			glTranslatef(T1.x,T1.y,T1.z);
		}
		else
		if(j!=0)
		{
			glTranslatef(T1.x,T1.y+fHeight,T1.z);
		}
		
		/*if(fHeight<0)
		{
		glBegin(GL_QUADS);
		//Bottom
        glColor4f(1.0,0.0,0.0,0.4); 
		//ChangeGLColor(aColor);
		glVertex3f(U1.x,U1.y+0.2,U1.z);
		glVertex3f(U2.x,U2.y+0.2,U2.z);
		glVertex3f(U3.x,U3.y+0.2,U3.z);
		glVertex3f(U4.x,U4.y+0.2,U4.z);
		}
		else
		{*/
		glBegin(GL_QUADS);
		//Bottom
       // glColor4f(1.0,0.0,0.0,0.4); 
		ChangeGLColor(aColor);
		glVertex3f(U1.x,U1.y+0.2,U1.z);
		glVertex3f(U2.x,U2.y+0.2,U2.z);
		glVertex3f(U3.x,U3.y+0.2,U3.z);
		glVertex3f(U4.x,U4.y+0.2,U4.z);
		//Front sideA	
		ChangeGLColor(aColor);
		glVertex3f(U1.x,U1.y,U1.z);
		glVertex3f(U2.x,U2.y,U2.z);
		glVertex3f(U2.x,U2.y+h,U2.z);
		glVertex3f(U1.x,U1.y+h,U1.z);
		//Back sideB
		ChangeGLColor(bColor);
		glVertex3f(U3.x,U3.y,U3.z);
		glVertex3f(U4.x,U4.y,U4.z);
		glVertex3f(U4.x,U4.y+h,U4.z);
		glVertex3f(U3.x,U3.y+h,U3.z);
		// Side c
		ChangeGLColor(aColor);
		glVertex3f(U1.x,U1.y,U1.z);
		glVertex3f(U4.x,U4.y,U4.z);
		glVertex3f(U4.x,U4.y+h,U4.z);
		glVertex3f(U1.x,U1.y+h,U1.z);
		// Side d
		ChangeGLColor(aColor);
		glVertex3f(U2.x,U2.y,U2.z);
		glVertex3f(U3.x,U3.y,U3.z);
		glVertex3f(U3.x,U3.y+h,U3.z);
		glVertex3f(U2.x,U2.y+h,U2.z);
		
		glVertex3f(U1.x,U1.y+h,U1.z);
		glVertex3f(U2.x,U2.y+h,U2.z);
		glVertex3f(U3.x,U3.y+h,U3.z);
		glVertex3f(U4.x,U4.y+h,U4.z);
		glEnd();
	//	}
	glPopMatrix();
}





void GL3dView::DrawBlockDoor(CVector3 P1, CVector3 P2, CVector3 P3, CVector3 P4, float Width, float Height, COLORREF aColor, COLORREF bColor)
{
	CVector3 T1=P1,V1=P1,V2=P2,T2=V2;
	float Theta=(float)atan2((V2.z-V1.z),(V2.x-V1.x));
	float Angle= -(Theta * 180.0 / 3.1416f);
	float l,l1,l2,w,h;
    l=V2.Difference(V1);
	l1=P3.Difference(V1);
	l2=P4.Difference(V1);
	h=Height/20.0f;
	w=Width/20.0f;
	CVector3 U1(0,0,0),U2(l,0,0),U3(l,0,w),U4(0,0,w);
	glPushMatrix();
	    if(j==0)
			glTranslatef(T1.x,T1.y,T1.z);
			else
			glTranslatef(T1.x,T1.y+fHeight,T1.z);
		
		glRotatef(Angle,0,1,0);
		ChangeGLColor(aColor);
		glBegin(GL_QUAD_STRIP);
			glVertex3f(U1.x,U1.y,U1.z);
			glVertex3f(U1.x,U1.y+h,U1.z);
			glVertex3f(U1.x+l1,U1.y,U1.z);
			glVertex3f(U1.x+l1,U1.y+h,U1.z);
			glVertex3f(U1.x+l1,U1.y+3.75,U1.z);
			glVertex3f(U1.x+l1,U1.y+h,U1.z);
			glVertex3f(U1.x+l2,U1.y+3.75,U1.z);
			glVertex3f(U1.x+l2,U1.y+h,U1.z);
			glVertex3f(U1.x+l2,U1.y,U1.z);
			glVertex3f(U1.x+l2,U1.y+h,U1.z);
			glVertex3f(U1.x+l,U1.y,U1.z);
			glVertex3f(U1.x+l,U1.y+h,U1.z);
		glEnd();
		ChangeGLColor(bColor);
		glBegin(GL_QUAD_STRIP);
			glVertex3f(U1.x,U1.y,U1.z+w);
			glVertex3f(U1.x,U1.y+h,U1.z+w);
			glVertex3f(U1.x+l1,U1.y,U1.z+w);
			glVertex3f(U1.x+l1,U1.y+h,U1.z+w);
		    glVertex3f(U1.x+l1,U1.y+3.75,U1.z+w);
			glVertex3f(U1.x+l1,U1.y+h,U1.z+w);
			glVertex3f(U1.x+l2,U1.y+3.75,U1.z+w);
			glVertex3f(U1.x+l2,U1.y+h,U1.z+w);
			glVertex3f(U1.x+l2,U1.y,U1.z+w);
			glVertex3f(U1.x+l2,U1.y+h,U1.z+w);
			glVertex3f(U1.x+l,U1.y,U1.z+w);
			glVertex3f(U1.x+l,U1.y+h,U1.z+w);
		glEnd();
	    glBegin(GL_QUAD_STRIP);
			glVertex3f(U1.x,U1.y,U1.z);
			glVertex3f(U1.x,U1.y+h,U1.z);
			glVertex3f(U1.x,U1.y,U1.z+w);
			glVertex3f(U1.x,U1.y+h,U1.z+w);
		glEnd();
	    glBegin(GL_QUAD_STRIP);
			glVertex3f(U1.x,U1.y+h,U1.z);
			glVertex3f(U1.x+l,U1.y+h,U1.z);
			glVertex3f(U1.x,U1.y+h,U1.z+w);
			glVertex3f(U1.x+l,U1.y+h,U1.z+w);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glVertex3f(U1.x+l,U1.y,U1.z);
			glVertex3f(U1.x+l,U1.y+h,U1.z);
			glVertex3f(U1.x+l,U1.y,U1.z+w);
			glVertex3f(U1.x+l,U1.y+h,U1.z+w);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glVertex3f(U1.x+l1,U1.y,U1.z);
			glVertex3f(U1.x+l1,U1.y+3.75,U1.z);
			glVertex3f(U1.x+l1,U1.y,U1.z+w);
			glVertex3f(U1.x+l1,U1.y+3.75,U1.z+w);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glVertex3f(U1.x+l1,U1.y+3.75,U1.z);
			glVertex3f(U1.x+l2,U1.y+3.75,U1.z);
			glVertex3f(U1.x+l1,U1.y+3.75,U1.z+w);
			glVertex3f(U1.x+l2,U1.y+3.75,U1.z+w);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glVertex3f(U1.x+l2,U1.y,U1.z);
			glVertex3f(U1.x+l2,U1.y+3.75,U1.z);
			glVertex3f(U1.x+l2,U1.y,U1.z+w);
			glVertex3f(U1.x+l2,U1.y+3.75,U1.z+w);
		glEnd();
	glPopMatrix();
}

void GL3dView::DrawBlockWindow(CVector3 P1, CVector3 P2, CVector3 P3, CVector3 P4, float Width, float Height, COLORREF aColor, COLORREF bColor)
{
	CVector3 T1=P1,V1=P1,V2=P2,T2=V2;
	float Theta=(float)atan2((V2.z-V1.z),(V2.x-V1.x));
	float Angle= -(Theta * 180.0 / 3.1416f);
	float wl,wl1,wl2,w,h;
    wl=V2.Difference(V1);
	wl1=P3.Difference(V1);
	wl2=P4.Difference(V1);
	h=Height/20.0f;
	w=Width/20.0f;
	CVector3 W1(0,0,0),W2(wl,0,0),W3(wl,0,w),W4(0,0,w);
	glPushMatrix();
		if(j==0)
			glTranslatef(T1.x,T1.y,T1.z);
			else
			glTranslatef(T1.x,T1.y+fHeight,T1.z);
		
		glRotatef(Angle,0,1,0);
		ChangeGLColor(aColor);
    	glBegin(GL_QUAD_STRIP);
			glVertex3f(W1.x,W1.y,W1.z);
			glVertex3f(W1.x,W1.y+h,W1.z);
			glVertex3f(W1.x+wl1,W1.y,W1.z);
			glVertex3f(W1.x+wl1,W1.y+h,W1.z);
			glVertex3f(W1.x+wl1,W1.y+3.75,W1.z);
			glVertex3f(W1.x+wl1,W1.y+h,W1.z);
			glVertex3f(W1.x+wl2,W1.y+3.75,W1.z);
			glVertex3f(W1.x+wl2,W1.y+h,W1.z);
			glVertex3f(W1.x+wl2,W1.y,W1.z);
			glVertex3f(W1.x+wl2,W1.y+h,W1.z);
			glVertex3f(W1.x+wl,W1.y,W1.z);
			glVertex3f(W1.x+wl,W1.y+h,W1.z);
			glVertex3f(W1.x+wl2,W1.y,W1.z);
			glVertex3f(W1.x+wl2,W1.y+1.0,W1.z);
			glVertex3f(W1.x+wl1,W1.y,W1.z);
			glVertex3f(W1.x+wl1,W1.y+1.0,W1.z);
		glEnd();
		ChangeGLColor(bColor);
		glBegin(GL_QUAD_STRIP);
			glVertex3f(W1.x,W1.y,W1.z+w);
			glVertex3f(W1.x,W1.y+h,W1.z+w);
			glVertex3f(W1.x+wl1,W1.y,W1.z+w);
			glVertex3f(W1.x+wl1,W1.y+h,W1.z+w);
			glVertex3f(W1.x+wl1,W1.y+3.75,W1.z+w);
			glVertex3f(W1.x+wl1,W1.y+h,W1.z+w);
			glVertex3f(W1.x+wl2,W1.y+3.75,W1.z+w);
			glVertex3f(W1.x+wl2,W1.y+h,W1.z+w);
			glVertex3f(W1.x+wl2,W1.y,W1.z+w);
			glVertex3f(W1.x+wl2,W1.y+h,W1.z+w);
			glVertex3f(W1.x+wl,W1.y,W1.z+w);
			glVertex3f(W1.x+wl,W1.y+h,W1.z+w);
			glVertex3f(W1.x+wl2,W1.y,W1.z+w);
			glVertex3f(W1.x+wl2,W1.y+1.0,W1.z+w);
			glVertex3f(W1.x+wl1,W1.y,W1.z+w);
			glVertex3f(W1.x+wl1,W1.y+1.0,W1.z+w);
		glEnd();
	    glBegin(GL_QUAD_STRIP);
			glVertex3f(W1.x,W1.y,W1.z);
			glVertex3f(W1.x,W1.y+h,W1.z);
			glVertex3f(W1.x,W1.y,W1.z+w);
			glVertex3f(W1.x,W1.y+h,W1.z+w);
		glEnd();
	    glBegin(GL_QUAD_STRIP);
			glVertex3f(W1.x,W1.y+h,W1.z);
			glVertex3f(W1.x+wl,W1.y+h,W1.z);
			glVertex3f(W1.x,W1.y+h,W1.z+w);
			glVertex3f(W1.x+wl,W1.y+h,W1.z+w);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glVertex3f(W1.x+wl,W1.y,W1.z);
			glVertex3f(W1.x+wl,W1.y+h,W1.z);
			glVertex3f(W1.x+wl,W1.y,W1.z+w);
			glVertex3f(W1.x+wl,W1.y+h,W1.z+w);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glVertex3f(W1.x+wl1,W1.y+1.0,W1.z);
			glVertex3f(W1.x+wl1,W1.y+3.75,W1.z);
			glVertex3f(W1.x+wl1,W1.y+1.0,W1.z+w);
			glVertex3f(W1.x+wl1,W1.y+3.75,W1.z+w);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glVertex3f(W1.x+wl1,W1.y+3.75,W1.z);
			glVertex3f(W1.x+wl2,W1.y+3.75,W1.z);
			glVertex3f(W1.x+wl1,W1.y+3.75,W1.z+w);
			glVertex3f(W1.x+wl2,W1.y+3.75,W1.z+w);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glVertex3f(W1.x+wl2,W1.y+1.0,W1.z);
			glVertex3f(W1.x+wl2,W1.y+3.75,W1.z);
			glVertex3f(W1.x+wl2,W1.y+1.0,W1.z+w);
			glVertex3f(W1.x+wl2,W1.y+3.75,W1.z+w);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glVertex3f(W1.x+wl1,W1.y+1.0,W1.z);
			glVertex3f(W1.x+wl1,W1.y+1.0,W1.z+w);
			glVertex3f(W1.x+wl2,W1.y+1.0,W1.z);
			glVertex3f(W1.x+wl2,W1.y+1.0,W1.z+w);
		glEnd();
	glPopMatrix();
}

void GL3dView::DrawBothBlock(CVector3 P1, CVector3 P2, CVector3 P3, CVector3 P4,CVector3 P5, CVector3 P6, float Width, float Height, COLORREF aColor, COLORREF bColor)
{
	CVector3 T1=P1,V1=P1,V2=P2,T2=V2;
	float Theta=(float)atan2((V2.z-V1.z),(V2.x-V1.x));
	float Angle= -(Theta * 180.0 / 3.1416f);
	float wl,wl1,wl2,wl3,wl4,w,h;
    wl=V2.Difference(V1);
	wl1=P3.Difference(V1);
	wl2=P4.Difference(V1);
	wl3=P5.Difference(V1);
	wl4=P6.Difference(V1);
	h=Height/20.0f;
	w=Width/20.0f;
	CVector3 W1(0,0,0),W2(wl,0,0),W3(wl,0,w),W4(0,0,w);
	glPushMatrix();
		if(j==0)
			glTranslatef(T1.x,T1.y,T1.z);
			else
			glTranslatef(T1.x,T1.y+fHeight,T1.z);
		
		glRotatef(Angle,0,1,0);
     	ChangeGLColor(aColor);
		if(wl1<wl3)
		{
			glBegin(GL_QUAD_STRIP);
				glVertex3f(W1.x,W1.y,W1.z);
				glVertex3f(W1.x,W1.y+h,W1.z);
				glVertex3f(W1.x+wl1,W1.y,W1.z);
				glVertex3f(W1.x+wl1,W1.y+h,W1.z);
		  		glVertex3f(W1.x+wl1,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl1,W1.y+h,W1.z);
				glVertex3f(W1.x+wl2,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl2,W1.y+h,W1.z);
		 		glVertex3f(W1.x+wl2,W1.y,W1.z);
				glVertex3f(W1.x+wl2,W1.y+h,W1.z);
				glVertex3f(W1.x+wl3,W1.y,W1.z);
				glVertex3f(W1.x+wl3,W1.y+h,W1.z);
				glVertex3f(W1.x+wl3,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl3,W1.y+h,W1.z);
				glVertex3f(W1.x+wl4,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl4,W1.y+h,W1.z);
				glVertex3f(W1.x+wl4,W1.y,W1.z);
				glVertex3f(W1.x+wl4,W1.y+h,W1.z);
				glVertex3f(W1.x+wl,W1.y,W1.z);
				glVertex3f(W1.x+wl,W1.y+h,W1.z);
				glVertex3f(W1.x+wl4,W1.y,W1.z);
				glVertex3f(W1.x+wl4,W1.y+1.0,W1.z);
				glVertex3f(W1.x+wl3,W1.y,W1.z);
				glVertex3f(W1.x+wl3,W1.y+1.0,W1.z);
			glEnd();
			 	ChangeGLColor(bColor);
	
			glBegin(GL_QUAD_STRIP);
    			glVertex3f(W1.x,W1.y,W1.z+w);
				glVertex3f(W1.x,W1.y+h,W1.z+w);
				glVertex3f(W1.x+wl1,W1.y,W1.z+w);
				glVertex3f(W1.x+wl1,W1.y+h,W1.z+w);
		 		glVertex3f(W1.x+wl1,W1.y+3.75,W1.z+w);
				glVertex3f(W1.x+wl1,W1.y+h,W1.z+w);
				glVertex3f(W1.x+wl2,W1.y+3.75,W1.z+w);
				glVertex3f(W1.x+wl2,W1.y+h,W1.z+w);
				glVertex3f(W1.x+wl2,W1.y,W1.z+w);
				glVertex3f(W1.x+wl2,W1.y+h,W1.z+w);
				glVertex3f(W1.x+wl3,W1.y,W1.z+w);
				glVertex3f(W1.x+wl3,W1.y+h,W1.z+w);
				glVertex3f(W1.x+wl3,W1.y+3.75,W1.z+w);
				glVertex3f(W1.x+wl3,W1.y+h,W1.z+w);
				glVertex3f(W1.x+wl4,W1.y+3.75,W1.z+w);
				glVertex3f(W1.x+wl4,W1.y+h,W1.z+w);
				glVertex3f(W1.x+wl4,W1.y,W1.z+w);
				glVertex3f(W1.x+wl4,W1.y+h,W1.z+w);
				glVertex3f(W1.x+wl,W1.y,W1.z+w);
				glVertex3f(W1.x+wl,W1.y+h,W1.z+w);
				glVertex3f(W1.x+wl4,W1.y,W1.z+w);
				glVertex3f(W1.x+wl4,W1.y+1.0,W1.z+w);
				glVertex3f(W1.x+wl3,W1.y,W1.z+w);
				glVertex3f(W1.x+wl3,W1.y+1.0,W1.z+w);
			 glEnd();
			 glBegin(GL_QUAD_STRIP);
				glVertex3f(W1.x,W1.y,W1.z);
				glVertex3f(W1.x,W1.y+h,W1.z);
				glVertex3f(W1.x,W1.y,W1.z+w);
				glVertex3f(W1.x,W1.y+h,W1.z+w);
		 	 glEnd();
			 glBegin(GL_QUAD_STRIP);
				glVertex3f(W1.x,W1.y+h,W1.z);
				glVertex3f(W1.x+wl,W1.y+h,W1.z);
				glVertex3f(W1.x,W1.y+h,W1.z+w);
				glVertex3f(W1.x+wl,W1.y+h,W1.z+w);
		 	 glEnd();
			 glBegin(GL_QUAD_STRIP);
				glVertex3f(W1.x+wl,W1.y,W1.z);
				glVertex3f(W1.x+wl,W1.y+h,W1.z);
				glVertex3f(W1.x+wl,W1.y,W1.z+w);
				glVertex3f(W1.x+wl,W1.y+h,W1.z+w);
			 glEnd();
			 glBegin(GL_QUAD_STRIP);
				glVertex3f(W1.x+wl1,W1.y,W1.z);
				glVertex3f(W1.x+wl1,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl1,W1.y,W1.z+w);
				glVertex3f(W1.x+wl1,W1.y+3.75,W1.z+w);
		     glEnd();
			 glBegin(GL_QUAD_STRIP);
				glVertex3f(W1.x+wl1,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl2,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl1,W1.y+3.75,W1.z+w);
				glVertex3f(W1.x+wl2,W1.y+3.75,W1.z+w);
			 glEnd();
			 glBegin(GL_QUAD_STRIP);
				glVertex3f(W1.x+wl2,W1.y,W1.z);
				glVertex3f(W1.x+wl2,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl2,W1.y,W1.z+w);
				glVertex3f(W1.x+wl2,W1.y+3.75,W1.z+w);
		  	 glEnd();
		     glBegin(GL_QUAD_STRIP);
				glVertex3f(W1.x+wl3,W1.y+1.0,W1.z);
				glVertex3f(W1.x+wl3,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl3,W1.y+1.0,W1.z+w);
				glVertex3f(W1.x+wl3,W1.y+3.75,W1.z+w);
		     glEnd();
			 glBegin(GL_QUAD_STRIP);
				glVertex3f(W1.x+wl3,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl4,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl3,W1.y+3.75,W1.z+w);
				glVertex3f(W1.x+wl4,W1.y+3.75,W1.z+w);
			 glEnd();
			 glBegin(GL_QUAD_STRIP);
				glVertex3f(W1.x+wl4,W1.y+1.0,W1.z);
				glVertex3f(W1.x+wl4,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl4,W1.y+1.0,W1.z+w);
				glVertex3f(W1.x+wl4,W1.y+3.75,W1.z+w);
		  	 glEnd();
			 glBegin(GL_QUAD_STRIP);
				glVertex3f(W1.x+wl3,W1.y+1.0,W1.z);
				glVertex3f(W1.x+wl4,W1.y+1.0,W1.z);
				glVertex3f(W1.x+wl3,W1.y+1.0,W1.z+w);
				glVertex3f(W1.x+wl4,W1.y+1.0,W1.z+w);
		     glEnd();
		}
		else
		if(wl1>wl3)
		{
			glBegin(GL_QUAD_STRIP);
				glVertex3f(W1.x+wl,W1.y,W1.z);
				glVertex3f(W1.x+wl,W1.y+h,W1.z);
				glVertex3f(W1.x+wl2,W1.y,W1.z);
				glVertex3f(W1.x+wl2,W1.y+h,W1.z);
		 
				glVertex3f(W1.x+wl2,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl2,W1.y+h,W1.z);
				glVertex3f(W1.x+wl1,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl1,W1.y+h,W1.z);
			
				glVertex3f(W1.x+wl1,W1.y,W1.z);
				glVertex3f(W1.x+wl1,W1.y+h,W1.z);
				glVertex3f(W1.x+wl4,W1.y,W1.z);
				glVertex3f(W1.x+wl4,W1.y+h,W1.z);
	
			    glVertex3f(W1.x+wl4,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl4,W1.y+h,W1.z);
				glVertex3f(W1.x+wl3,W1.y+3.75,W1.z);
				glVertex3f(W1.x+wl3,W1.y+h,W1.z);
		 
				glVertex3f(W1.x+wl3,W1.y,W1.z);
				glVertex3f(W1.x+wl3,W1.y+h,W1.z);
				glVertex3f(W1.x,W1.y,W1.z);
				glVertex3f(W1.x,W1.y+h,W1.z);
	
				glVertex3f(W1.x+wl3,W1.y,W1.z);
				glVertex3f(W1.x+wl3,W1.y+1.0,W1.z);
				glVertex3f(W1.x+wl4,W1.y,W1.z);
				glVertex3f(W1.x+wl4,W1.y+1.0,W1.z);
 			glEnd();

 /*
		glBegin(GL_QUAD_STRIP);
    		glVertex3f(W1.x,W1.y,W1.z+w);
			glVertex3f(W1.x,W1.y+h,W1.z+w);
			glVertex3f(W1.x+wl1,W1.y,W1.z+w);
			glVertex3f(W1.x+wl1,W1.y+h,W1.z+w);
		  
			glVertex3f(W1.x+wl1,W1.y+3.75,W1.z+w);
			glVertex3f(W1.x+wl1,W1.y+h,W1.z+w);
			glVertex3f(W1.x+wl2,W1.y+3.75,W1.z+w);
			glVertex3f(W1.x+wl2,W1.y+h,W1.z+w);
		 
			glVertex3f(W1.x+wl2,W1.y,W1.z+w);
			glVertex3f(W1.x+wl2,W1.y+h,W1.z+w);
			glVertex3f(W1.x+wl3,W1.y,W1.z+w);
			glVertex3f(W1.x+wl3,W1.y+h,W1.z+w);
	
			glVertex3f(W1.x+wl3,W1.y+3.75,W1.z+w);
			glVertex3f(W1.x+wl3,W1.y+h,W1.z+w);
			glVertex3f(W1.x+wl4,W1.y+3.75,W1.z+w);
			glVertex3f(W1.x+wl4,W1.y+h,W1.z+w);

			glVertex3f(W1.x+wl4,W1.y,W1.z+w);
			glVertex3f(W1.x+wl4,W1.y+h,W1.z+w);
			glVertex3f(W1.x+wl,W1.y,W1.z+w);
			glVertex3f(W1.x+wl,W1.y+h,W1.z+w);
	
			glVertex3f(W1.x+wl3,W1.y,W1.z+w);
			glVertex3f(W1.x+wl4,W1.y,W1.z+w);
			glVertex3f(W1.x+wl3,W1.y+1.0,W1.z+w);
			glVertex3f(W1.x+wl4,W1.y+1.0,W1.z+w);
	
		 
		 glEnd();

	 glBegin(GL_QUAD_STRIP);
	     glVertex3f(W1.x,W1.y,W1.z);
		 glVertex3f(W1.x,W1.y+h,W1.z);
		 glVertex3f(W1.x,W1.y,W1.z+w);
		 glVertex3f(W1.x,W1.y+h,W1.z+w);
		  
	glEnd();
	
    glBegin(GL_QUAD_STRIP);
	     glVertex3f(W1.x,W1.y+h,W1.z);
		 glVertex3f(W1.x+wl,W1.y+h,W1.z);
		 glVertex3f(W1.x,W1.y+h,W1.z+w);
		 glVertex3f(W1.x+wl,W1.y+h,W1.z+w);
		  
	glEnd();
	glBegin(GL_QUAD_STRIP);
	     glVertex3f(W1.x+wl,W1.y,W1.z);
		 glVertex3f(W1.x+wl,W1.y+h,W1.z);
		 glVertex3f(W1.x+wl,W1.y,W1.z+w);
		 glVertex3f(W1.x+wl,W1.y+h,W1.z+w);
		  
	glEnd();
	glBegin(GL_QUAD_STRIP);
	     glVertex3f(W1.x+wl1,W1.y,W1.z);
		 glVertex3f(W1.x+wl1,W1.y+3.75,W1.z);
		 glVertex3f(W1.x+wl1,W1.y,W1.z+w);
		 glVertex3f(W1.x+wl1,W1.y+3.75,W1.z+w);
		  
	glEnd();
	glBegin(GL_QUAD_STRIP);
	     glVertex3f(W1.x+wl1,W1.y+3.75,W1.z);
		 glVertex3f(W1.x+wl2,W1.y+3.75,W1.z);
		 glVertex3f(W1.x+wl1,W1.y+3.75,W1.z+w);
		 glVertex3f(W1.x+wl2,W1.y+3.75,W1.z+w);
		  
	glEnd();
	glBegin(GL_QUAD_STRIP);
	     glVertex3f(W1.x+wl2,W1.y,W1.z);
		 glVertex3f(W1.x+wl2,W1.y+3.75,W1.z);
		 glVertex3f(W1.x+wl2,W1.y,W1.z+w);
		 glVertex3f(W1.x+wl2,W1.y+3.75,W1.z+w);
		  
	glEnd();
		 
	glBegin(GL_QUAD_STRIP);
	     glVertex3f(W1.x+wl3,W1.y+1.0,W1.z);
		 glVertex3f(W1.x+wl3,W1.y+3.75,W1.z);
		 glVertex3f(W1.x+wl3,W1.y+1.0,W1.z+w);
		 glVertex3f(W1.x+wl3,W1.y+3.75,W1.z+w);
		  
	glEnd();
		glBegin(GL_QUAD_STRIP);
	     glVertex3f(W1.x+wl3,W1.y+3.75,W1.z);
		 glVertex3f(W1.x+wl4,W1.y+3.75,W1.z);
		 glVertex3f(W1.x+wl3,W1.y+3.75,W1.z+w);
		 glVertex3f(W1.x+wl4,W1.y+3.75,W1.z+w);
		  
	glEnd();
		glBegin(GL_QUAD_STRIP);
	     glVertex3f(W1.x+wl4,W1.y+1.0,W1.z);
		 glVertex3f(W1.x+wl4,W1.y+3.75,W1.z);
		 glVertex3f(W1.x+wl4,W1.y+1.0,W1.z+w);
		 glVertex3f(W1.x+wl4,W1.y+3.75,W1.z+w);
		  
	glEnd();
		glBegin(GL_QUAD_STRIP);
	     glVertex3f(W1.x+wl3,W1.y+1.0,W1.z);
		 glVertex3f(W1.x+wl4,W1.y+1.0,W1.z);
		 glVertex3f(W1.x+wl3,W1.y+1.0,W1.z+w);
		 glVertex3f(W1.x+wl4,W1.y+1.0,W1.z+w);
		  
	glEnd();*/
		}
	glPopMatrix();
}


void GL3dView::DrawChair(CChairObject *pChair, int chair_v)
{	
	CArchDoc*  pDoc = (CArchDoc*) GetDocument();
	ASSERT_VALID(pDoc);
    
	CPoint p;
	p=pChair->m_ptPosition;
	CVector3 V(p.x,0,p.y);
	V = ConvertPoint(V.x,0,V.z);
	//float Height = ;
	//float Width  = pChair->m_uiWidth/20.0f;
		 if(i==0)
   {
    CV1[count_fs].y=-6.0;
    CV2[count_fs].y=0.0;
   }	
   else

	 if(i==1)
	 {
      CV1[count_fs].y=0.0;
	  CV2[count_fs].y=6.0;
	 }	
   
else
	 if(i==2)
	 {
      CV1[count_fs].y=6.0;
	  CV2[count_fs].y=12.0;
	 }	
   else
	 if(i==3)
	 {
      CV1[count_fs].y=12.0;
	   CV2[count_fs].y=18.0;
	 }	
  
/*	if(i==0)
	{
		CV1[count_fs].y=6.0;
		CV2[count_fs].y=0.0;
	}	
	else
	if(i==1)
	{
		CV1[count_fs].y=0.0;
		CV2[count_fs].y=6.0;
	}	
	else
	if(i==2)
	{
		CV1[count_fs].y=6.0;
		CV2[count_fs].y=12.0;
	}	
	else
	if(i==3)
	{
		CV1[count_fs].y=12.0;
		CV2[count_fs].y=18.0;
	}	
	 
	CV1[count_fs].x=V.x-0.5;
    CV1[count_fs].z=V.z-0.5 ;
    CV2[count_fs].x=V.x+0.5;
    CV2[count_fs].z=V.z+0.5;
	*/
    count_fs=count_fs+1;
	s_count++;
	w_count1[loc2]=count_loc;
	loc2=loc2+1;
	count_loc=count_loc+1;
	ChangeGLColor(pChair->m_Color);

	//glColor3ub(GetRValue(color),GetGValue(color),GetBValue(color));
	
		glPushMatrix();

			if(j==0)
		      glTranslatef(V.x,V.y+3,V.z);
			else
              glTranslatef(V.x,V.y+fHeight+3,V.z);
			  
	//if(chair_v==1)
	//{
//    }	
//	else
//		if(chair_v==2)
//		{
/*
			g_Load3ds.Import3DS(&g_Load3ds.g_3DModel,"data\\face.3DS");
	
    	for(int i = 0; i < g_Load3ds.g_3DModel.numOfMaterials; i++)
		{
		// Check to see if there is a file name to load in this material
		if(strlen(g_Load3ds.g_3DModel.pMaterials[i].strFile) > 0)
		{
			// Use the name of the texture file to load the bitmap, with a texture ID (i).
			// We pass in our global texture array, the name of the texture, and an ID to reference it.	
		//	CreateTexture(g_Texture, g_Load3ds.g_3DModel.pMaterials[i].strFile, i);			
		}

		// Set the texture ID for this material
		g_Load3ds.g_3DModel.pMaterials[i].texureId = i;
		}
    
    }*/	

CVector3  chV;
          chV=V;


/*==========================Drawing Chair form CSTCubes ========================*/

  //      Vector, XLength XLength  XLength  
	CSTCube(V,         3      ,3      ,0.2);  //////////\/  BAck of chair
	CSTCube(V,         3       ,0.2    ,4   );  /////////\/   Seet of char

chV.y +=1.5;	
	CSTCube(chV   ,    0.4     ,0.3    ,3   );  /////////\/   Left Arm of chair
chV.x +=3;
    CSTCube(chV   ,    -0.4     ,0.3    ,3   );  /////////\/   RightArm of chair

chV.z +=2;   
    CSTCube(chV   ,    -0.3     ,-1.5    ,0.4   );  /////////\/   Hold of Left "chair Arm"
chV.x -=3;
	CSTCube(chV   ,    0.3     ,-1.5   ,0.4   );  /////////\/   Hold of Right "chair Arm"

chV = V;
	CSTCube(V     ,    0.3     , -3.0     ,0.3 ); /////////\/Left back leg of chair
chV.x +=3;
    CSTCube(chV   ,    -0.3     , -3.0     ,0.3 ); /////////\/Right back leg of chair

chV.z += 3; 
    CSTCube(chV   ,    -0.3     , -3.0     ,0.3 ); /////////\/Right front leg of chair
chV =V;
chV.z +=3;
    CSTCube(chV   ,    0.3     , -3.0     ,0.3 ); /////////\/Left front leg of chair
												   
/*	
		if(chair_v==1)
	    g_Load3ds[0].Draw(0);
     		  else
		if(chair_v==2)
		 g_Load3ds[1].Draw(1);
			else
		if(chair_v==3)
		  g_Load3ds[2].Draw(2);
		else
        if(chair_v==4)
		 g_Load3ds[3].Draw(3);
		else
		if(chair_v==5)
       g_Load3ds[4].Draw(4);
*/
  
		
	glPopMatrix();


}

void GL3dView::DrawBlockTex(CVector3 P1, CVector3 P2, float Width, float Height, CString aTexture, CString bTexture)
{
CVector3 T1=P1,V1=P1,V2=P2,T2=V2;
	float Theta=(float)atan2((V2.z-V1.z),(V2.x-V1.x));
	float Angle= -(Theta * 180.0 / 3.1416f);
	float l,w,h;
    //l=P2.x-P1.x;
	l=V2.Difference(V1);
	h=Height/20.0f;
	w=Width/20.0f;

	CVector3 U1(0,0,0),U2(l,0,0),U3(l,0,w),U4(0,0,w);
    
	glPushMatrix();
		//glLoadIdentity();
	    if(j==0)
			glTranslatef(T1.x,T1.y,T1.z);
		//glTranslatef(T2.x,T2.y,T2.z);
		
		else
		  glTranslatef(T1.x,T1.y+fHeight,T1.z);
		glRotatef(Angle,0,1,0);
		glBegin(GL_QUADS);
		//Bottom	
		glVertex3f(U1.x,U1.y,U1.z);
		glVertex3f(U2.x,U2.y,U2.z);
	    glVertex3f(U3.x,U3.y,U3.z);
	    glVertex3f(U4.x,U4.y,U4.z);
		//Front sideA	
		//	ChangeGLColor(aColor);
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D,textures[0].texID);
		glTexCoord2f(0,0);	glVertex3f(U1.x,U1.y,U1.z);
		glTexCoord2f(1,0);	glVertex3f(U2.x,U2.y,U2.z);
		glTexCoord2f(1,1);	glVertex3f(U2.x,U2.y+h,U2.z);
		glTexCoord2f(0,1);	glVertex3f(U1.x,U1.y+h,U1.z);
        //glDisable(GL_TEXTURE_2D); 
		//Back sideB
			//ChangeGLColor(bColor);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textures[1].texID);
		
	glTexCoord2f(0,0);	    glVertex3f(U3.x,U3.y,U3.z);
	glTexCoord2f(1,0);		glVertex3f(U4.x,U4.y,U4.z);
	glTexCoord2f(1,1);		glVertex3f(U4.x,U4.y+h,U4.z);
	glTexCoord2f(0,1);		glVertex3f(U3.x,U3.y+h,U3.z);
	    glDisable(GL_TEXTURE_2D); 
		
	// Side c
			glVertex3f(U1.x,U1.y,U1.z);
			glVertex3f(U4.x,U4.y,U4.z);
			glVertex3f(U4.x,U4.y+h,U4.z);
			glVertex3f(U1.x,U1.y+h,U1.z);
		// Side d
			glVertex3f(U2.x,U2.y,U2.z);
			glVertex3f(U3.x,U3.y,U3.z);
			glVertex3f(U3.x,U3.y+h,U3.z);
			glVertex3f(U2.x,U2.y+h,U2.z);
		glEnd();
	
		
		glPopMatrix();
}

int GL3dView::collision_detect(int e_count)
{
	CArchDoc*  pDoc = (CArchDoc*) GetDocument();
	ASSERT_VALID(pDoc);

   
	for(int e=0;e<e_count;e++)
	{

		for(int f=0;f<pDoc->loc1;f++)
		{
			if(((g_Camera.m_vPosition.x>=(CV7[e].x-1.8) && g_Camera.m_vPosition.x<=(CV8[e].x+1.5))||
				(g_Camera.m_vPosition.x<=(CV7[e].x+1.8) && g_Camera.m_vPosition.x>=(CV8[e].x-1.5))) && 
				((g_Camera.m_vPosition.z>=(CV7[e].z-1.5) && g_Camera.m_vView.z<=(CV8[e].z+1.5))|| 
				(g_Camera.m_vPosition.z<=(CV7[e].z+1.5) && g_Camera.m_vView.z>=(CV8[e].z+1.5)))&&
				(g_Camera.m_vView.y>=(CV7[e].y) && g_Camera.m_vView.y<=(CV8[e].y)))
				{
				return 1;
				}
		}
			for( f=0;f<pDoc->loc2;f++)
		
			{
		//	if(fw_count1[f]==e)
		//	{	
				if(((g_Camera.m_vPosition.x>=(CV3[f].x) && g_Camera.m_vPosition.x<=(CV5[f].x)) ||
					(g_Camera.m_vPosition.x<=(CV3[f].x) && g_Camera.m_vPosition.x>=(CV5[f].x)))&&
					((g_Camera.m_vPosition.z>=(CV3[f].z) && g_Camera.m_vView.z<=(CV5[f].z))||
					 (g_Camera.m_vPosition.z<=(CV3[f].z) && g_Camera.m_vView.z>=(CV5[f].z))&&
					(g_Camera.m_vView.y>=(CV3[f].y) && g_Camera.m_vView.y<=(CV4[f].y))))
					{
						return 1;
					}	
			else
				 if(((g_Camera.m_vPosition.x>=(CV6[f].x) && g_Camera.m_vPosition.x<=(CV4[f].x))||
					(g_Camera.m_vPosition.x<=(CV6[f].x) && g_Camera.m_vPosition.x>=(CV4[f].x))) && 
				   ((g_Camera.m_vPosition.z>=(CV6[f].z) && g_Camera.m_vView.z<=(CV4[f].z-1.5))||
					(g_Camera.m_vPosition.z<=(CV6[f].z) && g_Camera.m_vView.z>=(CV4[f].z+1.5)))&&
				   (g_Camera.m_vView.y>=(CV3[f].y) && g_Camera.m_vView.y<=(CV4[f].y)))
					{	
						return 1;
					}
		//	}
		}/*
					 if((g_Camera.m_vPosition.x>=(CV3[e].x-1.8) && g_Camera.m_vPosition.x<=(CV3[e].x-0.5))&&
					(g_Camera.m_vPosition.z>=(CV3[e].z-1.5) && g_Camera.m_vView.z<=(CV3[e].z))&&
					(g_Camera.m_vView.y>=(CV3[e].y) && g_Camera.m_vView.y<=(CV4[e].y)))
					{
						return 1;
					}
		//			else
				 if((g_Camera.m_vPosition.x>=(CV4[e].x-0.5) && g_Camera.m_vPosition.x<=(CV2[e].x+1.8)) && 
				    (g_Camera.m_vPosition.z>=(CV4[e].z) && g_Camera.m_vView.z<=(CV2[e].z-1.5))&&
				    (g_Camera.m_vView.y>=(CV1[e].y) && g_Camera.m_vView.y<=(CV2[e].y)))
					{	
						return 1;
					}
					else
				 if((g_Camera.m_vPosition.x>=(CV3[e].x-1.5) && g_Camera.m_vPosition.x<=(CV4[e].x+1.5))&&
					(g_Camera.m_vPosition.z>=(CV3[e].z) && g_Camera.m_vView.z<=(CV4[e].z)) && 
					(g_Camera.m_vView.y>=(CV3[e].y) && g_Camera.m_vView.y<=(CV4[e].y)))
					{
						return 1;
					}
	
	  	
		//	else*/
	//	}
		for(  f=0;f<pDoc->loc3;f++)
		{
		//	if(w_count1[f]==e)
		//	{
	 				if(((g_Camera.m_vPosition.x>=(CV1[e].x-1.0) && g_Camera.m_vPosition.x<=(CV2[e].x+0.5))||
						(g_Camera.m_vPosition.x<=(CV1[e].x+1.8) && g_Camera.m_vPosition.x>=(CV2[e].x-1.5))) && 
						((g_Camera.m_vPosition.z>=(CV1[e].z-1.5) && g_Camera.m_vView.z<=(CV2[e].z-1.5)) || 
						(g_Camera.m_vPosition.z<=(CV1[e].z+1.5) && g_Camera.m_vView.z>=(CV2[e].z+1.5)))&&
						(g_Camera.m_vView.y>=(CV1[e].y) && g_Camera.m_vView.y<=(CV2[e].y)))
						{
							return 1;    
						} 
				
		//}
	}
	for( f=0;f<pDoc->loc4;f++)
		{
		//	if(w_count1[f]==e)
		//	{
	 		if(((g_Camera.m_vPosition.x>=(CV9[e].x-1.8) && g_Camera.m_vPosition.x<=(CV11[e].x+1.5))||
				(g_Camera.m_vPosition.x<=(CV9[e].x+1.8) && g_Camera.m_vPosition.x>=(CV11[e].x-1.5))) && 
				((g_Camera.m_vPosition.z>=(CV9[e].z-1.5) && g_Camera.m_vView.z<=(CV11[e].z-1.5)) || 
				(g_Camera.m_vPosition.z<=(CV9[e].z+1.5) && g_Camera.m_vView.z>=(CV11[e].z+1.5)))&&
				(g_Camera.m_vView.y>=(CV9[e].y) && g_Camera.m_vView.y<=(CV10[e].y)))
				{
					return 1;    
				} 
			if(((g_Camera.m_vPosition.x>=(CV11[e].x-1.8) && g_Camera.m_vPosition.x<=(CV12[e].x+1.5))||
				(g_Camera.m_vPosition.x<=(CV11[e].x+1.8) && g_Camera.m_vPosition.x>=(CV12[e].x-1.5))) && 
				((g_Camera.m_vPosition.z>=(CV11[e].z-1.5) && g_Camera.m_vView.z<=(CV12[e].z-1.5)) || 
				(g_Camera.m_vPosition.z<=(CV11[e].z+1.5) && g_Camera.m_vView.z>=(CV12[e].z+1.5)))&&
				(g_Camera.m_vView.y>=(CV9[e].y) && g_Camera.m_vView.y<=(CV10[e].y)))
				{
					return 1;    
				} 
			if(((g_Camera.m_vPosition.x>=(CV12[e].x-1.8) && g_Camera.m_vPosition.x<=(CV10[e].x+1.5))||
				(g_Camera.m_vPosition.x<=(CV12[e].x+1.8) && g_Camera.m_vPosition.x>=(CV10[e].x-1.5))) && 
				((g_Camera.m_vPosition.z>=(CV12[e].z-1.5) && g_Camera.m_vView.z<=(CV10[e].z-1.5)) || 
				(g_Camera.m_vPosition.z<=(CV12[e].z+1.5) && g_Camera.m_vView.z>=(CV10[e].z+1.5)))&&
				(g_Camera.m_vView.y>=(CV9[e].y) && g_Camera.m_vView.y<=(CV10[e].y)))
				{
					return 1;    
				} 
				
		//}
	}
	
	}
	return 0;
		
}

void GL3dView::DrawSpiralStair(CSpiralstair *pstair)
{
	CPoint P1,P2;
	P1 = pstair->m_ptPosition;
	CVector3 V1,V2,T1;
	V1=ConvertPoint(P1.x,0,P1.y);
	V2=ConvertPoint(P2.x,0,P2.y);
	T1=V1;
	float Height=pstair->m_uiHeight;
	float Width=pstair->m_uiWidth;
	float Theta=(float)atan2((V2.z-V1.z),(V2.x-V1.x));
	float Angle= -(Theta * 180.0 / 3.1416f)+90.0;
	float Angle1= -(Theta * 180.0 / 3.1416f)+90.0;
	float l,w,h;
	//AfxMessageBox("%d",)
	l=V2.Difference(V1);
	h=Height/20.0f;
	w=Width/20.0f;
	GLUquadricObj *obj;
	obj=gluNewQuadric();
	if(i==0)
	{
		CV1[count_fs].y=-6.0;
		CV2[count_fs].y=0.0;
	}	
	else
	if(i==1)
	{
		CV1[count_fs].y=0.0;
		CV2[count_fs].y=6.0;
	}	
	else
	if(i==2)
	{
		CV1[count_fs].y=6.0;
		CV2[count_fs].y=12.0;
	}	
	else
	if(i==3)
	{
		CV1[count_fs].y=12.0;
		CV2[count_fs].y=18.0;
	}	
    CV1[count_fs].x=V1.x-(w/2);
    CV1[count_fs].z=V1.z-(w/2) ;
    CV2[count_fs].x=V1.x+(w/2);
    CV2[count_fs].z=V1.z+(w/2);
    count_fs=count_fs+1;
	//gluQuadricOrientation(obj,GLU_OUTSIDE);
	//gluQuadricTexture(obj,GL_TRUE);
	if(i==1)
	{
		glPushMatrix();
			glColor3f(0,0,0.5);
			if(j==0)
				glTranslatef(T1.x,0,T1.z);
				else
				glTranslatef(T1.x,fHeight,T1.z);
			glRotated(-90,1,0,0);	
			gluCylinder(obj,0.2,0.2,h,360,3);
		glPopMatrix();
		int nostairs=h*2;
		for(int i=0;i<nostairs;i++)	
		{
			glPushMatrix();
				glTranslatef(T1.x,T1.y+fHeight,T1.z);
				ChangeGLColor(pstair->m_Color);
				//glColor3f(1,1,1);
			glPushMatrix();
			ChangeGLColor(pstair->m_Color);	
			glRotatef(Angle,0,1,0);
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.5,0,0.2);
						glVertex3f(0.2,0,1);
						glVertex3f(1.5,0,1.2);
						glVertex3f(1.2,0,2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
					Angle1+=6;
				glEnd();
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.5,0.1,0.2);
						glVertex3f(0.2,0.1,1);
						glVertex3f(1.5,0.1,1.2);
						glVertex3f(1.2,0.1,2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
				Angle1+=6;
				glEnd();
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.5,0,0.2);
						glVertex3f(0.5,0.1,0.2);
						glVertex3f(0.2,0,1);
						glVertex3f(0.2,0.1,1);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
					Angle1+=6;
				glEnd();
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.5,0,0.2);
						glVertex3f(0.5,0.1,0.2);
						glVertex3f(1.5,0,1.2);
						glVertex3f(1.5,0.1,1.2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
					Angle1+=6;
				glEnd();
				
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(1.5,0,1.2);
						glVertex3f(1.5,0.5,1.2);
						glVertex3f(1.2,0,2);
						glVertex3f(1.2,0.5,2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
					Angle1+=6;
				glEnd();
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.2,0,1);
						glVertex3f(0.2,0.1,1);
						glVertex3f(1.2,0,2);
						glVertex3f(1.2,0.1,2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
				Angle1+=6;
				glEnd();
			glPopMatrix();
			T1.y+=0.5;
		glPopMatrix();
		Angle+=30;
		}
	}
	
	if(i==2)
	{
		glPushMatrix();
			glColor3f(0,0,0.5);
			if(j==0)
			glTranslatef(T1.x,0,T1.z);
			else
			glTranslatef(T1.x,0+fHeight,T1.z);
			
			glRotated(-90,1,0,0);	
			gluCylinder(obj,0.1,0.1,h,360,3);
		glPopMatrix();
		int nostairs=h*2;
		for(int i=0;i<nostairs;i++)	
		{
			glPushMatrix();
				glTranslatef(T1.x,T1.y+fHeight,T1.z);
				ChangeGLColor(pstair->m_Color);
				//glColor3f(1,1,1);
			glPushMatrix();
			ChangeGLColor(pstair->m_Color);
				glRotatef(Angle,0,1,0);
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.5,0,0.2);
						glVertex3f(0.2,0,1);
						glVertex3f(1.5,0,1.2);
						glVertex3f(1.2,0,2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
					Angle1+=6;
				glEnd();
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.5,0.1,0.2);
						glVertex3f(0.2,0.1,1);
						glVertex3f(1.5,0.1,1.2);
						glVertex3f(1.2,0.1,2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
				Angle1+=6;
				glEnd();
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.5,0,0.2);
						glVertex3f(0.5,0.1,0.2);
						glVertex3f(0.2,0,1);
						glVertex3f(0.2,0.1,1);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
					Angle1+=6;
				glEnd();
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.5,0,0.2);
						glVertex3f(0.5,0.1,0.2);
						glVertex3f(1.5,0,1.2);
						glVertex3f(1.5,0.1,1.2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
					Angle1+=6;
				glEnd();
				//glColor3f(3,0,0);
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(1.5,0,1.2);
						glVertex3f(1.5,0.5,1.2);
						glVertex3f(1.2,0,2);
						glVertex3f(1.2,0.5,2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
					Angle1+=6;
				glEnd();
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.2,0,1);
						glVertex3f(0.2,0.1,1);
						glVertex3f(1.2,0,2);
						glVertex3f(1.2,0.1,2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
				Angle1+=6;
				glEnd();
			glPopMatrix();
			T1.y+=0.5;
		glPopMatrix();
		Angle+=30;
		}
	}
	else
	if(i==3)
	{
		glPushMatrix();
			glColor3f(0,0,0.5);
			if(j==0)
			glTranslatef(T1.x,T1.y,T1.z);
			else
			glTranslatef(T1.x,T1.y+fHeight,T1.z);
			
			glRotated(-90,1,0,0);	
			gluCylinder(obj,0.1,0.1,h,360,3);
		glPopMatrix();
		int nostairs=h*2;
		for(int i=0;i<nostairs;i++)	
		{
			glPushMatrix();
				glTranslatef(T1.x,T1.y+fHeight,T1.z);
				ChangeGLColor(pstair->m_Color);
				//glColor3f(1,1,1);
			glPushMatrix();
			ChangeGLColor(pstair->m_Color);
				glRotatef(Angle,0,1,0);
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.5,0,0.2);
						glVertex3f(0.2,0,1);
						glVertex3f(1.5,0,1.2);
						glVertex3f(1.2,0,2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
					Angle1+=6;
				glEnd();
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.5,0.1,0.2);
						glVertex3f(0.2,0.1,1);
						glVertex3f(1.5,0.1,1.2);
						glVertex3f(1.2,0.1,2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
				Angle1+=6;
				glEnd();
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.5,0,0.2);
						glVertex3f(0.5,0.1,0.2);
						glVertex3f(0.2,0,1);
						glVertex3f(0.2,0.1,1);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
					Angle1+=6;
				glEnd();
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.5,0,0.2);
						glVertex3f(0.5,0.1,0.2);
						glVertex3f(1.5,0,1.2);
						glVertex3f(1.5,0.1,1.2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
					Angle1+=6;
				glEnd();
				//glColor3f(3,0,0);
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(1.5,0,1.2);
						glVertex3f(1.5,0.5,1.2);
						glVertex3f(1.2,0,2);
						glVertex3f(1.2,0.5,2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
					Angle1+=6;
				glEnd();
				glBegin(GL_QUAD_STRIP);
					glPushMatrix();
						glVertex3f(0.2,0,1);
						glVertex3f(0.2,0.1,1);
						glVertex3f(1.2,0,2);
						glVertex3f(1.2,0.1,2);
						glRotatef(Angle1,0,1,0);  
					glPopMatrix();
				Angle1+=6;
				glEnd();
			glPopMatrix();
			T1.y+=0.5;
		glPopMatrix();
		Angle+=30;
		}
	}
}


void GL3dView::DrawWidowBlock(CVector3 P1, CVector3 P2, float Width, float Height,float Height1, COLORREF aColor, COLORREF bColor)
{
CVector3 T1=P1,V1=P1,V2=P2,T2=V2;
	float Theta=(float)atan2((V2.z-V1.z),(V2.x-V1.x));
	float Angle= -(Theta * 180.0 / 3.1416f);
	float l,w,h,h1;
    l=V2.Difference(V1);
	h=Height/20.0f;
	h1=Height1/20.0f;
	w=Width/20.0f;
	CVector3 U1(0,0,0),U2(l,0,0),U3(l,0,w),U4(0,0,w);
	glPushMatrix();
		if(j==0)
			glTranslatef(T1.x,T1.y,T1.z);
			else
			glTranslatef(T1.x,T1.y+fHeight,T1.z);
		glRotatef(Angle,0,1,0);
		glBegin(GL_QUADS);
		//Bottom	
		glVertex3f(U1.x,U1.y,U1.z);
		glVertex3f(U2.x,U2.y,U2.z);
	    glVertex3f(U3.x,U3.y,U3.z);
	    glVertex3f(U4.x,U4.y,U4.z);
		//Front sideA	
		ChangeGLColor(aColor);
		glVertex3f(U1.x,U1.y,U1.z);
		glVertex3f(U2.x,U2.y,U2.z);
		glVertex3f(U2.x,U2.y+h,U2.z);
		glVertex3f(U1.x,U1.y+h,U1.z);
		//Back sideB
		ChangeGLColor(bColor);
		glVertex3f(U3.x,U3.y,U3.z);
		glVertex3f(U4.x,U4.y,U4.z);
		glVertex3f(U4.x,U4.y+h,U4.z);
		glVertex3f(U3.x,U3.y+h,U3.z);
		// Side c
		glVertex3f(U1.x,U1.y,U1.z);
		glVertex3f(U4.x,U4.y,U4.z);
		glVertex3f(U4.x,U4.y+h,U4.z);
		glVertex3f(U1.x,U1.y+h,U1.z);
		// Side d
		glVertex3f(U2.x,U2.y,U2.z);
		glVertex3f(U3.x,U3.y,U3.z);
		glVertex3f(U3.x,U3.y+h,U3.z);
		glVertex3f(U2.x,U2.y+h,U2.z);
		glEnd();
		
		glPushMatrix();
		if(j==0)
			glTranslatef(T1.x,T1.y,T1.z);
			else
			glTranslatef(T1.x,T1.y+fHeight,T1.z);
		glRotatef(Angle,0,1,0);
		glBegin(GL_QUADS);
		//Bottom	
		glVertex3f(U1.x,U1.y,U1.z);
		glVertex3f(U2.x,U2.y,U2.z);
	    glVertex3f(U3.x,U3.y,U3.z);
	    glVertex3f(U4.x,U4.y,U4.z);
		//Front sideA	
		ChangeGLColor(aColor);
		glVertex3f(U1.x,U1.y,U1.z);
		glVertex3f(U2.x,U2.y,U2.z);
		glVertex3f(U2.x,U2.y+h1,U2.z);
		glVertex3f(U1.x,U1.y+h1,U1.z);
		//Back sideB
		ChangeGLColor(bColor);
		glVertex3f(U3.x,U3.y,U3.z);
		glVertex3f(U4.x,U4.y,U4.z);
		glVertex3f(U4.x,U4.y+h1,U4.z);
		glVertex3f(U3.x,U3.y+h1,U3.z);
		// Side c
		glVertex3f(U1.x,U1.y,U1.z);
		glVertex3f(U4.x,U4.y,U4.z);
		glVertex3f(U4.x,U4.y+h1,U4.z);
		glVertex3f(U1.x,U1.y+h1,U1.z);
		// Side d
		glVertex3f(U2.x,U2.y,U2.z);
		glVertex3f(U3.x,U3.y,U3.z);
		glVertex3f(U3.x,U3.y+h1,U3.z);
		glVertex3f(U2.x,U2.y+h1,U2.z);
		glEnd();
			glPopMatrix();
		glPopMatrix();
}
/************************************************************************************************/
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
/************************************************************************************************/
void GL3dView::CSTCube(CVector3 initVec,float xLent,float yLent,float zLent)
{

	CVector3 iV = initVec;


/*/\/\/\/\/\/Initali points */
	glBegin(GL_QUADS);      //1st quad
	 glVertex3f(iV.x , iV.y , iV.z);
	 glVertex3f(iV.x , iV.y+yLent , iV.z);
	 glVertex3f(iV.x , iV.y+yLent , iV.z+zLent);
	 glVertex3f(iV.x , iV.y       ,iV.z+zLent);
	glEnd();

	glBegin(GL_QUADS);      //2nd quad
	 glVertex3f(iV.x+xLent , iV.y , iV.z);
	 glVertex3f(iV.x+xLent , iV.y+yLent , iV.z);
	 glVertex3f(iV.x+xLent , iV.y+yLent , iV.z+zLent);
	 glVertex3f(iV.x+xLent , iV.y       ,iV.z+zLent);
	glEnd();
/*/\/\/\/\/\/EO Initali points */
/*/\/\/\/\/\/Covering remaining sides part cube*/
/////////////////////////////////////////////////Covering Sides Of Cube
glColor3ub(12,12,12);
    glBegin(GL_QUADS);
     glVertex3f(iV.x        , iV.y       , iV.z);               //1st vertix of 1st quad
	 glVertex3f(iV.x+xLent  , iV.y       , iV.z);        // //  //    // 2nd //   
     glVertex3f(iV.x+xLent  , iV.y+yLent , iV.z);  
	 glVertex3f(iV.x        , iV.y+yLent , iV.z);
	glEnd();

	glBegin(GL_QUADS);
     glVertex3f(iV.x        , iV.y        ,iV.z + zLent);
	 glVertex3f(iV.x+xLent  , iV.y        ,iV.z + zLent);
	 glVertex3f(iV.x+xLent  , iV.y+yLent  ,iV.z + zLent);
	 glVertex3f(iV.x        , iV.y+yLent  ,iV.z + zLent);
	glEnd();
////////////////////////////////////////////////// Filing Up And Down Side Of Cube
glColor3ub(102,102,102);
    glBegin(GL_QUADS);                            
     glVertex3f(iV.x        , iV.y+yLent  , iV.z+zLent); 
	 glVertex3f(iV.x        , iV.y+yLent  ,iV.z);
	 glVertex3f(iV.x+xLent , iV.y+yLent  , iV.z);
	 glVertex3f(iV.x+xLent , iV.y+yLent  ,iV.z+zLent);
	glEnd();

	glBegin(GL_QUADS);
     glVertex3f(iV.x        , iV.y       ,iV.z+zLent);
	 glVertex3f(iV.x        , iV.y       ,iV.z);
	 glVertex3f(iV.x+xLent , iV.y , iV.z);
	 glVertex3f(iV.x+xLent , iV.y       , iV.z+zLent);
   glEnd(); 
//////////////////////////////////////////////////

/*/\/\/\/\/\/EO Covering remaining sides part cube*/

/**********************EO Procedure*******************/
}
/************************************************************************************************/
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
/************************************************************************************************/
void GL3dView::CSTCube(CVector3 initVec,float xLent,float yLent,float zLent,char texFile[20])
{

	CVector3 iV = initVec;


/*/\/\/\/\/\/Initali points */
	glBegin(GL_QUADS);      //1st quad
	 glVertex3f(iV.x , iV.y , iV.z);
	 glVertex3f(iV.x , iV.y+yLent , iV.z);
	 glVertex3f(iV.x , iV.y+yLent , iV.z+zLent);
	 glVertex3f(iV.x , iV.y       ,iV.z+zLent);
	glEnd();

	glBegin(GL_QUADS);      //2nd quad
	 glVertex3f(iV.x+xLent , iV.y , iV.z);
	 glVertex3f(iV.x+xLent , iV.y+yLent , iV.z);
	 glVertex3f(iV.x+xLent , iV.y+yLent , iV.z+zLent);
	 glVertex3f(iV.x+xLent , iV.y       ,iV.z+zLent);
	glEnd();
/*/\/\/\/\/\/EO Initali points */
/*/\/\/\/\/\/Covering remaining sides part cube*/
/////////////////////////////////////////////////Covering Sides Of Cube
glColor3ub(12,12,12);
    glBegin(GL_QUADS);
     glVertex3f(iV.x        , iV.y       , iV.z);               //1st vertix of 1st quad
	 glVertex3f(iV.x+xLent  , iV.y       , iV.z);        // //  //    // 2nd //   
     glVertex3f(iV.x+xLent  , iV.y+yLent , iV.z);  
	 glVertex3f(iV.x        , iV.y+yLent , iV.z);
	glEnd();

	glBegin(GL_QUADS);
     glVertex3f(iV.x        , iV.y        ,iV.z + zLent);
	 glVertex3f(iV.x+xLent  , iV.y        ,iV.z + zLent);
	 glVertex3f(iV.x+xLent  , iV.y+yLent  ,iV.z + zLent);
	 glVertex3f(iV.x        , iV.y+yLent  ,iV.z + zLent);
	glEnd();
////////////////////////////////////////////////// Filing Up And Down Side Of Cube
glColor3ub(102,102,102);
    glBegin(GL_QUADS);                            
     glVertex3f(iV.x        , iV.y+yLent  , iV.z+zLent); 
	 glVertex3f(iV.x        , iV.y+yLent  ,iV.z);
	 glVertex3f(iV.x+xLent , iV.y+yLent  , iV.z);
	 glVertex3f(iV.x+xLent , iV.y+yLent  ,iV.z+zLent);
	glEnd();

	glBegin(GL_QUADS);
     glVertex3f(iV.x        , iV.y       ,iV.z+zLent);
	 glVertex3f(iV.x        , iV.y       ,iV.z);
	 glVertex3f(iV.x+xLent , iV.y , iV.z);
	 glVertex3f(iV.x+xLent , iV.y       , iV.z+zLent);
   glEnd(); 
//////////////////////////////////////////////////

/*/\/\/\/\/\/EO Covering remaining sides part cube*/

/**********************EO Procedure*******************/
}
/************************************************************************************************/
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
/************************************************************************************************/

void GL3dView::DrawTable(CTableobject *pTable)
{
	CArchDoc*  pDoc = (CArchDoc*) GetDocument();
	ASSERT_VALID(pDoc);
    
	CPoint p;
	p=pTable->m_ptPosition;
	CVector3 V(p.x,0,p.y);
	V = ConvertPoint(V.x,0,V.z);
////////////////////////////
if(i==0)
	{
		CV1[count_fs].y=6.0;
		CV2[count_fs].y=0.0;
	}	
	else
	if(i==1)
	{
		CV1[count_fs].y=0.0;
		CV2[count_fs].y=6.0;
	}	
	else
	if(i==2)
	{
		CV1[count_fs].y=6.0;
		CV2[count_fs].y=12.0;
	}	
	else
if(i==3)
	{
		CV1[count_fs].y=12.0;
		CV2[count_fs].y=18.0;
	}	
///////////////////////////	 
	CV1[count_fs].x=V.x-0.5;
    CV1[count_fs].z=V.z-0.5 ;
    CV2[count_fs].x=V.x+0.5;
    CV2[count_fs].z=V.z+0.5;
    count_fs=count_fs+1;
	s_count++;
	w_count1[loc2]=count_loc;
	loc2=loc2+1;
	count_loc=count_loc+1;
	ChangeGLColor(pTable->m_Color);

	//glColor3ub(GetRValue(color),GetGValue(color),GetBValue(color));
	
		glPushMatrix();
			if(j==0)
		      glTranslatef(V.x,V.y,V.z);
			else
              glTranslatef(V.x,V.y+fHeight,V.z);    
	
CVector3 chV =V;  //this variable is only used funiture drawing Functions, every Furniture Buliding function have its on.
/********Actuall Table Drawing********/
	CSTCube(V,	7,	0.2,	5); //The main table sheet

    CSTCube(V,  0.5,	-4.5,	0.5); //1st leg or we can say left back leg

chV.x +=6.5; //changeing the position of X axes
	CSTCube(chV,  0.5,	-4.5,	0.5); //1st leg or we can say right back leg

chV.z +=4.5; //changeing the position of X axes
	CSTCube(chV,  0.5,	-4.5,	0.5); //1st leg or we can say right back leg

chV.x -=6.5; //changeing the position of X axes 
               //all these x's changings are made to put all legs of table 
	CSTCube(chV,  0.5,	-4.5,	0.5); //1st leg or we can say right back leg

/********EO Actuall Table Drawing********/


}

/************************************************************************************************/
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
/************************************************************************************************/
void GL3dView::DrawSofa(CSofaobject *pSofa)
{

	CArchDoc*  pDoc = (CArchDoc*) GetDocument();
    ASSERT_VALID(pDoc);
    
	CPoint p;
	p=pSofa->m_ptPosition;
	CVector3 V(p.x,0,p.y);
	V = ConvertPoint(V.x,0,V.z);
////////////////////////////
	if(i==0)
	{
		CV1[count_fs].y=6.0;
		CV2[count_fs].y=0.0;
	}	
	else
	if(i==1)
	{
		CV1[count_fs].y=0.0;
		CV2[count_fs].y=6.0;
	}	
	else
	if(i==2)
	{
		CV1[count_fs].y=6.0;
		CV2[count_fs].y=12.0;
	}	
	else
if(i==3)
	{
		CV1[count_fs].y=12.0;
		CV2[count_fs].y=18.0;
	}	
///////////////////////////	 
	CV1[count_fs].x=V.x-0.5;
    CV1[count_fs].z=V.z-0.5 ;
    CV2[count_fs].x=V.x+0.5;
    CV2[count_fs].z=V.z+0.5;
    
	count_fs=count_fs+1;
	s_count++;
	w_count1[loc2]=count_loc;
	loc2=loc2+1;
	count_loc=count_loc+1;
	ChangeGLColor(pSofa->m_Color);

  /**********************************/
 /*     Acctual drawing of Sofa    */
/********************************/
   glPushMatrix(); 
         if(j==0)
		      glTranslatef(V.x,V.y,V.z);
			else
              glTranslatef(V.x,V.y+fHeight,V.z);    
	
CVector3 chV =V;  //this variable is only used funiture drawing Functions, every function have its on.
/***********Main Building Of Sofa*****************/
//       Vector       Xlentth    Ylength  Zlength  
	CSTCube(V,	      4,	      3,	    0.5); //Main back supourt of sofa

	CSTCube(V,        0.7,          1.5,        2); //Right arm of sofa

   CSTCube(V,	      4,	      0.5,	    3); //Seet supourt of sofa

chV.x += 3.5;

   CSTCube(chV ,     0.5,          1.5,        2);


/*************EOf Sofa Building**************/

	glPopMatrix();

}

