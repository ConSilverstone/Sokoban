#pragma once

//Project Includes
#include <SFML/Graphics.hpp>

class Level
{
public:

	Level();

	void Draw(sf::RenderTarget& _target);
	void Update(sf::Time _frameTime);

	void LoadLevel(int _levelToLoad);
	void ReloadLevel();
	void LoadNextLevel();

private:

	int m_currentLevel;
};