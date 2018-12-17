#pragma once

// Project Includes
#include "GridObject.h"

// Library Includes
#include <SFML/Audio.hpp>

class Box : public GridObject
{

public:

	Box();

	bool AttemptPush(sf::Vector2i _direction);
	bool GetStored();

private:

	bool m_stored;
	sf::Sound m_pushSound;
	sf::Sound m_storeSound;
};