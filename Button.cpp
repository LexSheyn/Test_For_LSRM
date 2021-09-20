#include "stdafx.h"
#include "Button.h"

// private: Functions:
void Button::initVariables()
{
	this->colorNumberButton = 0;

	this->colorMaxStagesButton = 6;

	this->stepButton = 0.1f;

	this->buttonTimer = 0.f;
	this->buttonTimerMax = 1.f;

	this->coefficientButton = 0.4f;

	this->highlighted = false;
	this->pressed = false;
	this->soundEngine = nullptr;
}


// Constructors and Destructor:

Button::Button
(
	float x, float y, float width, float height,
	sf::Color auto_button_hover_color,
	sfx::SoundEngine* sound_engine,
	sfx::Sound sound_hover,
	sfx::Sound sound_press
)
{
	this->initVariables();

	this->buttonState = ButtonStates::Idle;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

// Button colors:

	// Idle color
	this->buttonIdleColor.r = static_cast<unsigned int>(static_cast<float>(auto_button_hover_color.r) * this->coefficientButton);
	this->buttonIdleColor.g = static_cast<unsigned int>(static_cast<float>(auto_button_hover_color.g) * this->coefficientButton);
	this->buttonIdleColor.b = static_cast<unsigned int>(static_cast<float>(auto_button_hover_color.b) * this->coefficientButton);
	this->buttonIdleColor.a = 200;

	// Hover color
	this->buttonHoverColor = auto_button_hover_color;
	this->buttonHoverColor.a = 200;

	// Active color
	this->buttonActiveColor.r = static_cast<unsigned int>(static_cast<float>(auto_button_hover_color.r) * this->coefficientButton / 2.f);
	this->buttonActiveColor.g = static_cast<unsigned int>(static_cast<float>(auto_button_hover_color.g) * this->coefficientButton / 2.f);
	this->buttonActiveColor.b = static_cast<unsigned int>(static_cast<float>(auto_button_hover_color.b) * this->coefficientButton / 2.f);
	this->buttonActiveColor.a = 200;

	//Button idle to hover color
	this->idleToHoverColor[0] = this->buttonIdleColor;
	this->coefficientButton += this->stepButton;
	for (int i = 1; i < this->colorMaxStagesButton; i++)
	{
		this->idleToHoverColor[i].r = static_cast<unsigned int>(static_cast<float>(auto_button_hover_color.r) * this->coefficientButton);
		this->idleToHoverColor[i].g = static_cast<unsigned int>(static_cast<float>(auto_button_hover_color.g) * this->coefficientButton);
		this->idleToHoverColor[i].b = static_cast<unsigned int>(static_cast<float>(auto_button_hover_color.b) * this->coefficientButton);
		this->coefficientButton += this->stepButton;
	}

	this->shape.setFillColor(this->buttonIdleColor);

	this->soundEngine = sound_engine;
	this->soundHover = sound_hover;
	this->soundPress = sound_press;
}

Button::~Button()
{

}

// Accessors:

const bool Button::isPressed() const
{
	if (this->buttonState == ButtonStates::Active)
	{
		return true;
	}

	return false;
}

const sf::Vector2f& Button::getPosition() const
{
	return this->shape.getPosition();
}

const int& Button::getId() const
{
	return this->id;
}

const ButtonStates& Button::getButtonState() const
{
	return this->buttonState;
}

const bool Button::isHighlighted(const sf::Vector2i& mouse_position) const
{
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_position)))
	{
		return true;
	}

	return false;
}


// Modifiers:

void Button::setPosition(const float x, const float y)
{
	this->shape.setPosition(x, y);
}

void Button::setId(const int id)
{
	this->id = id;
}

void Button::setTexture(sf::Texture& texture)
{
	this->shape.setTexture(&texture);
}


// Functions:

// Updates the booleans for hover and pressed.
void Button::update(const sf::Vector2i& mouse_position)
{
	// Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_position)))
	{
		this->buttonState = ButtonStates::Hover;

		// Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = ButtonStates::Active;

			if (this->pressed == false)
			{
				this->pressed = true;

				if (this->soundEngine)
				{
					this->soundEngine->playSound(this->soundPress);
				}
			}
		}
		else
		{
			this->pressed = false;
		}
	}
	else
	{
		// Idle
		this->buttonState = ButtonStates::Idle;
	}

	switch (this->buttonState)
	{
	case ButtonStates::Idle:

		this->shape.setFillColor(this->currentColorButton);

		break;

	case ButtonStates::Hover:

		this->shape.setFillColor(this->currentColorButton);

		break;

	case ButtonStates::Active:

		this->shape.setFillColor(this->buttonActiveColor);

		break;

	default:

		this->shape.setFillColor(sf::Color::Red);

		break;
	}

	if (this->isHighlighted(mouse_position))
	{
		if (this->highlighted == false)
		{
			this->highlighted = true;

			if (this->soundEngine)
			{
				this->soundEngine->playSound(this->soundHover);
			}
		}
	}
	else
	{
		this->highlighted = false;
	}

	this->updateButtonColor();
}

void Button::updateButtonColor()
{
	if (this->buttonState == ButtonStates::Hover)
	{
		this->buttonTimer += 1.0f;
		if (this->buttonTimer >= this->buttonTimerMax)
		{
			this->buttonTimer = 0.f;
			this->currentColorButton = this->idleToHoverColor[colorNumberButton];

			if (this->colorNumberButton < (this->colorMaxStagesButton - 1))
			{
				this->colorNumberButton++;
			}
		}
	}
	else if (this->buttonState == ButtonStates::Idle)
	{
		this->buttonTimer += 1.f;
		if (this->buttonTimer >= this->buttonTimerMax)
		{
			this->buttonTimer = 0.f;
			this->currentColorButton = this->idleToHoverColor[colorNumberButton];

			if (this->colorNumberButton != 0)
			{
				this->colorNumberButton--;
			}
		}
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}