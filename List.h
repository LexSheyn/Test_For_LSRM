#pragma once

#include "TextBox.h"
#include "Button.h"

class List
{
private:

// Variables:

	sf::RectangleShape container;

	std::vector<TextBox*> textBoxes;
	std::vector<Button*> buttons;

	sf::Texture& texture;
	sfx::SoundEngine* soundEngine;

	sf::Font& font;	
	unsigned int charSize;
	sf::Color textColor;
	bool buttonPressed;

	int amount;
	int capacity;

// private: Functions:

	void initVariables();

public:

// Constructors and Destructor:

	List(float x, float y, sf::Font& font, unsigned int char_size, sf::Color text_color, sf::Texture& texture, sfx::SoundEngine* sound_engine = nullptr);
	virtual ~List();

// Accessors:

	const sf::Vector2f getElementPosition(const int index) const;
	const TextBox& getLastElement() const;
	const TextBox& getElement(const int index) const;
	const int& getAmount() const;
	const int& getCapacity() const;

// Modifiers:

	void setString(const std::string str);

// Functions:

	bool add(const std::string str);
	bool remove(const unsigned int index);

	void updatePositions();
	void updateInputEvents(sf::Event& input);
	void updateInput();
	void update(sf::Vector2i& mouse_position);

	void render(sf::RenderTarget& target);
};

