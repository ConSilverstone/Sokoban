// Project Includes
#include "Level.h"

// Library Includes
#include <iostream>
#include <fstream>

Level::Level()
	: m_currentLevel(0)
{
	LoadLevel(1);
}

void Level::Draw(sf::RenderTarget & _target)
{
	// Create and update
	sf::View camera = _target.getDefaultView();
	//TODO: Adjust camera as needed
	// Draw game world to the window
	_target.setView(camera);
	// TODO: Draw game objects

	// Reset View
	_target.setView(_target.getDefaultView());
}

void Level::Update(sf::Time _frameTime)
{
	 // TODO
}

void Level::LoadLevel(int _levelToLoad)
{
	// Clean up the old level

	// TODO: Delete any data already in the level

	// TODO: Clear out our lists

	// Set the current level
	m_currentLevel = _levelToLoad;

	// Set up the new level

	// Open our file for reading
	std::ifstream inFile;
	std::string fileName = "levels/Level" + std::to_string(m_currentLevel) + ".txt";
	inFile.open(fileName);

	// Make sure the file was opened
	if (!inFile) 
	{
		std::cerr << "Unable to open file" + fileName;
		exit(1); // Call System to stop program with error
	}

	// Set the starting xand y coordinates used to position level objects
	float x = 0.0f;
	float y = 0.0f;

	// Define the spacing we will use for our grid
	const float X_SPACE = 105.0f;
	const float Y_SPACE = 105.0f;

	// Read each character one by one from the file...
	char ch;
	// Each time, try to read the next character
	// If successful, execute body of loop
	// the "noskipws" means our input from the file will include the
	// white space (spaces and new lines)
	while (inFile >> std::noskipws >> ch)
	{
		// Perform actions based on what character was read in

		if (ch == ' ')
		{
			x += X_SPACE;
		} 
		else if (ch == '\n')
		{
			y += Y_SPACE;
			x = 0;
		}
		else if (ch == '-')
		{
			// Do nothing
		}
		else
		{
			std::cerr << "Unrecognised character in level file: " << ch;
		}
	}

	// Close the file now that we are done with it
	inFile.close();
}

void Level::ReloadLevel()
{
	LoadLevel(m_currentLevel);
}

void Level::LoadNextLevel()
{
	LoadLevel(m_currentLevel + 1);
}
