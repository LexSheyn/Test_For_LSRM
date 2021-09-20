#pragma once

#include "Button.h"
#include "TextBox.h"
#include "List.h"
#include "SoundEngine.h"

enum class Textures
{
	Add = 0,
	Add_File,
	Remove
};

enum class FileParts : unsigned int
{
	Name = 0,
	Extension
};

class Window
{
private:

// Window:
	sf::RenderWindow* window;
	sf::Event windowEvent;
	sf::Image icon;
	sf::Font font;

	unsigned int framerateLimit;
	sf::Vector2i resolution;

	sf::Vector2i mousePositionWindow;

// Variables:

	sf::RectangleShape guiContainer;
	std::map<const Textures, sf::Texture> textures;
	bool buttonPressed;
	bool buttonHover;
	float keyTime;
	float keyTimeMax;
	float keyTimeTick;

	TextBox* nameTextBox;
	Button* addButton;
	List* list;

	std::map<const FileParts, TextBox*> fileTextBoxes;
	Button* fileAddButton;
	sf::Text popUpText;
	sf::Color popUpTextColor;

	sfx::SoundEngine soundEngine;

// private: Functions:

	void initVariables();
	void initIcon(const std::string file_path);
	void initTexture(const Textures name, const std::string file_path);
	// Should use ../ before file path to run witout Visual Studio.
	void initFont(const std::string file_path);
	void initTextBox();
	void initButtons();
	void initList();
	void initSound();
	
public:

// Constructors and Destructor:

	Window();
	virtual ~Window();

// Accessors:

	const bool getKeyTime();
	const bool fileExist(const std::string file_path) const;

// Functions:

	void run();
	// Should use '\\' instead of '/' in the file path and put this file to the .exe location
	// to be able to run app without Visual Studio... or... test this.
	std::string createFile(const std::string file_name);
	std::string createFile(const std::string file_name, const std::string file_extension);

	void updatePollEvents();
	void updateMousePositions();
	void updateKeyTime();
	void updateInput();
	void updateTextBoxes();
	void updateButtons();
	void updatePopUpText();
	void updateSound();

	void update();
	void render();
};

