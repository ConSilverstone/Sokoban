// Project Includes
# include "StorageObject.h"
# include "Framework/AssetManager.h"

StorageSpace::StorageSpace()
	: GridObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/storage.png"));
}