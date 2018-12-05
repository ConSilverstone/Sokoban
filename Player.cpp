// Project Includes
# include "Player.h"
# include "Framework/AssetManager.h"
# include "Level.h"
# include "SFML/Audio.hpp"

Player::Player()
	: GridObject()
	, m_pendingMove(0,0)
	, m_playerMoveSound()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandDown.png"));
	m_playerMoveSound.setBuffer(AssetManager::GetSoundBuffer("audio/footstep1.ogg"));
}

void Player::Input(sf::Event _gameEvent)
{
	// Read the mput from the keyoboard and covert it to a direction 
	// for the player to move and then move

	// Was the event a key press
	if (_gameEvent.type == sf::Event::KeyPressed)
	{
		// Yes it was a key press!

		// What key was pressed?
		if (_gameEvent.key.code == sf::Keyboard::W)
		{
			// It was W!
			// Move up
			m_pendingMove = sf::Vector2i(0, -1);
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandUp.png"));
		}
		// What key was pressed?
		else if (_gameEvent.key.code == sf::Keyboard::S)
		{
			// It was S!
			// Move down
			m_pendingMove = sf::Vector2i(0, 1);
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandDown.png"));
		}
		else if (_gameEvent.key.code == sf::Keyboard::A)
		{
			// It was A!
			// Move down
			m_pendingMove = sf::Vector2i(-1, 0);
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandLeft.png"));
		}
		else if (_gameEvent.key.code == sf::Keyboard::D)
		{
			// It was D!
			// Move down
			m_pendingMove = sf::Vector2i(1, 0);
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandRight.png"));
		}
	}
}

void Player::Update(sf::Time _frameTime)
{
	// IF we have movement waiting to be processed,
	if (m_pendingMove.x != 0 || m_pendingMove.y != 0)
	{
		// Move in that direction
		AttemptMove(m_pendingMove);
		// clear pending move.
		m_pendingMove = sf::Vector2i(0, 0);
		// Play walking sound
		m_playerMoveSound.play();
		
	}
}

bool Player::AttemptMove(sf::Vector2i _direction)
{
	//Attempt to move in the given direction

	// Get current position
	// Calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;

	//TODO: Check if the spaces are empty

	// If empty, move there
	return m_level->MoveObjectTo(this, targetPos);
}
