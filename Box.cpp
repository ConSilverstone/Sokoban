// Project Includes
#include "Box.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "Storage.h"

Box::Box()
	: GridObject()
	, m_stored(false)
	, m_pushSound()
	, m_storeSound()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/box.png"));
	m_blocksMovement = true;
	m_pushSound.setBuffer(AssetManager::GetSoundBuffer("audio/push.wav"));
	m_storeSound.setBuffer(AssetManager::GetSoundBuffer("audio/stored.wav"));
}


bool Box::AttemptPush(sf::Vector2i _direction)
{
	// Attempt to move the box in the given direction

	// Get current position
	// Calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;

	// Check if the space is empty

	// Get list of objects in our target position
	std::vector<GridObject*> targetCellContents = m_level->GetObjectAt(targetPos);

	// Check if any of those objects block movement
	bool blocked = false;
	for (int i = 0; i < targetCellContents.size(); ++i)
	{
		if (targetCellContents[i]->GetBlocksMovement() == true)
		{
			blocked = true;
		}
	}

	// If empty, move there
	if (blocked == false)
	{
		m_pushSound.play();
		bool moveSucceeded = m_level->MoveObjectTo(this, targetPos);

		// If we did successfuly move...
		if (moveSucceeded == true)
		{
			// Check if we are stored!

			// Assume we are not stored to start
			m_stored = false;

			// Loop through the contents and see if a storage object was found
			for (int i = 0; i < targetCellContents.size(); ++i) 
			{
				// Check if this element in the vector is a storage object
				// by doing a dynamic cast
				Storage* storageObject = dynamic_cast<Storage*>(targetCellContents[i]);

				// If dynamic cast succeeds, it will NOT a nullptr
				// aka, the object IS a storage object
				if (storageObject != nullptr)
				{
					// The object IS a storage object!

					// We are stored!
					m_stored = true;

					// Check if the level is complete!
					m_level->CheckComplete();
				}
			}

			// And change our sprite accordingly
			if (m_stored)
			{
				m_sprite.setTexture(AssetManager::GetTexture("graphics/boxStored.png"));
				m_storeSound.play();
			} else 
			{
				m_sprite.setTexture(AssetManager::GetTexture("graphics/box.png"));
			}

		}

		return moveSucceeded;
	}

	// If movement is blocked, do nothing, return false
	// Default
	return false;
}

bool Box::GetStored()
{
	return m_stored;
}
