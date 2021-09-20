#pragma once

#include "SoundEngine.h"

enum class ButtonStates
{
	Idle = 0,
	Hover,
	Active
};

class Button
{
private:

// Variables:

	ButtonStates buttonState;
	int id;

	sf::RectangleShape shape;

	sf::Color buttonIdleColor;
	sf::Color buttonHoverColor;
	sf::Color buttonActiveColor;

	sf::Color currentColorButton;

	std::map<int, sf::Color> idleToHoverColor;

	int colorNumberButton;
	int colorMaxStagesButton;
	float stepButton;

	float buttonTimer;
	float buttonTimerMax;

	float coefficientButton;

	bool highlighted;
	bool pressed;
	sfx::SoundEngine* soundEngine;
	sfx::Sound soundHover;
	sfx::Sound soundPress;

// private: Functions:

	void initVariables();

public:

// Constructors and Destructor:

	Button
	(
		float x, float y, float width, float height,
		sf::Color auto_button_hover_color,
		sfx::SoundEngine* sound_engine = nullptr,
		sfx::Sound sound_hover = sfx::Sound::Button_Hover,
		sfx::Sound sound_press = sfx::Sound::Button_Add
	);
	virtual ~Button();

// Accessors:

	const bool isPressed() const;
	const sf::Vector2f& getPosition() const;
	const int& getId() const;
	const ButtonStates& getButtonState() const;
	const bool isHighlighted(const sf::Vector2i& mouse_position) const;

// Modifiers:

	void setPosition(const float x, const float y);
	void setId(const int id);
	void setTexture(sf::Texture& texture);

// Fucntions:

	void update(const sf::Vector2i& mouse_position);
	void updateButtonColor();

	void render(sf::RenderTarget& target);
};

