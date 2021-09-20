#include "stdafx.h"
#include "TextBox.h"

// private: Functions:

void TextBox::initVariables()
{
	this->size = sf::Vector2f(140.f, 24.f);
	this->welcomeString = "Enter here";

	this->digitsOnly = false;
	this->hasLimit = false;
	this->limit = 10;

	this->selected = false;

	this->picked = false;
	this->pickable = false;

	this->pressed = false;
}

void TextBox::inputChar(int char_typed)
{
	if (char_typed != static_cast<int>(Keys::BackSpace) 
		&& char_typed != static_cast<int>(Keys::Enter) 
		&& char_typed != static_cast<int>(Keys::Escape))
	{
		this->textString << static_cast<char>(char_typed);
	}
	else if (char_typed == static_cast<int>(Keys::BackSpace))
	{
		this->deleteLastChar();
	}
}


// Constructors and Destructor:

TextBox::TextBox(sf::Font& font, unsigned int char_size, sf::Color color)
{
	this->initVariables();

	this->back.setSize(this->size);
	this->back.setFillColor(sf::Color(80, 60, 0));
	this->back.setOutlineColor(sf::Color(125, 100, 0));
	this->back.setOutlineThickness(-1.f);

	this->fill.setSize(this->size);
	this->fill.setFillColor(sf::Color(0, 255, 255, 50));

	this->text.setFont(font);
	this->text.setCharacterSize(char_size);
	this->text.setFillColor(color);

	this->updateText();
}

TextBox::TextBox
(
	float width, float height, 
	sf::Font& font, unsigned int char_size, sf::Color color
)
{
	this->initVariables();

	this->back.setSize(sf::Vector2f(width, height));
	this->back.setFillColor(sf::Color(80, 60, 0));
	this->back.setOutlineColor(sf::Color(125, 100, 0));
	this->back.setOutlineThickness(-1.f);

	this->fill.setSize(sf::Vector2f(width, height));
	this->fill.setFillColor(sf::Color(0, 255, 255, 50));

	this->text.setFont(font);
	this->text.setCharacterSize(char_size);
	this->text.setFillColor(color);

	this->updateText();
}

TextBox::~TextBox()
{

}


// Accessors:

const std::string TextBox::getString() const
{
	return this->textString.str();
}

const float TextBox::getSizeX() const
{
	return this->size.x;
}

const float TextBox::getSizeY() const
{
	return this->size.y;
}

const sf::Vector2f& TextBox::getPosition() const
{
	return this->back.getPosition();
}

const sf::Vector2f& TextBox::getSize() const
{
	return this->back.getSize();
}

const sf::FloatRect TextBox::getGlobalBounds() const
{
	return this->back.getGlobalBounds();
}

const bool& TextBox::isSelected() const
{
	return this->selected;
}

const bool& TextBox::isPicked() const
{
	return this->picked;
}


// Modifiers:

void TextBox::setFont(sf::Font& font)
{
	this->text.setFont(font);
}

void TextBox::setString(const std::string str)
{
	this->textString.str(str);
}

void TextBox::setWelcomeString(const std::string str)
{
	this->welcomeString = str;
}

void TextBox::setPosition(const float x, const float y)
{
	this->back.setPosition(x, y);
	this->fill.setPosition(x, y);
	this->text.setPosition
	(
		this->back.getPosition().x + (this->back.getSize().x / 20.f), 
		this->back.getPosition().y - (this->back.getSize().y / 10.f)
	);
}

void TextBox::setLimit(bool has_limit, int limit)
{
	this->hasLimit = has_limit;

	this->limit = limit;
}

void TextBox::setDigitsOnly(bool only_digits)
{
	this->digitsOnly = only_digits;
}

void TextBox::setSelected(bool selected)
{
	this->selected = selected;

	if (!selected)
	{
		std::string text_str = this->textString.str();
		std::string new_text = "";

		for (size_t i = 0; i < text_str.length(); i++)
		{
			new_text += text_str[i];
		}
		this->textString.str("");
		this->textString << new_text;
	}
}

void TextBox::setPicked(const bool picked)
{
	if (this->pickable)
	{
		this->picked = picked;
	}	
}

void TextBox::setPickable(const bool pickable)
{
	this->pickable = pickable;
}


// Functions:

void TextBox::deleteLastChar()
{
	if (!this->textString.str().empty())
	{
		std::string text_str = textString.str();
		std::string new_text = "";
		for (size_t i = 0; i < text_str.length() - 1; i++)
		{
			new_text += text_str[i];
		}
		this->textString.str("");
		this->textString << new_text;
	}
}

void TextBox::updateInputEvents(sf::Event& input)
{
	if (this->selected)
	{
		int char_typed = input.text.unicode;

		if (this->digitsOnly)
		{
			if (char_typed >= 48 && char_typed <= 57 || char_typed == static_cast<int>(Keys::BackSpace)) // Digits
			{
				if (this->hasLimit)
				{
					if (static_cast<int>(this->textString.str().length()) < this->limit || char_typed == static_cast<int>(Keys::BackSpace))
					{
						this->inputChar(char_typed);
					}
				}
				else
				{
					this->inputChar(char_typed);
				}
			}
		}
		else
		{
			if (char_typed < 128
				&& char_typed != 92
				&& char_typed != 47
				&& char_typed != 58
				&& char_typed != 42
				&& char_typed != 63
				&& char_typed != 34
				&& char_typed != 60
				&& char_typed != 62
				&& char_typed != 124) // Symbols
			{
				if (this->hasLimit)
				{
					if (static_cast<int>(this->textString.str().length()) < this->limit || char_typed == static_cast<int>(Keys::BackSpace))
					{
						this->inputChar(char_typed);
					}
				}
				else
				{
					this->inputChar(char_typed);
				}
			}
		}
//		std::cout << "Code: " << char_typed << std::endl;
	}
}

void TextBox::updateInput(sf::Vector2i& mouse_position)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
	{
		if (this->pressed == false)
		{
			this->pressed = true;

			if (this->back.getGlobalBounds().contains(sf::Vector2f(mouse_position)))
			{
				if (!this->picked)
				{
					this->setPicked();
				}
				else
				{
					this->setPicked(false);
				}
			}
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (this->pressed == false)
		{
			this->pressed = true;

			if (this->back.getGlobalBounds().contains(sf::Vector2f(mouse_position)))
			{
				this->setSelected();
			}
			else
			{
				this->setSelected(false);
			}
		}
	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
//	{
//		if (this->selected)
//		{
//			this->setSelected(false);
//		}
//	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		if (this->pressed == false)
		{
			this->pressed = true;

			if (this->selected)
			{
				this->setSelected(false);
			}

			if (this->picked)
			{
				this->setPicked(false);
			}
		}
	}
	else
	{
		this->pressed = false;
	}
}

void TextBox::updateText()
{
	if (this->selected)
	{
		this->text.setFillColor(sf::Color::White);
		this->text.setString(this->textString.str() + "_");
	}
	else
	{
		if (this->textString.str().empty())
		{
			this->text.setFillColor(sf::Color(200, 200, 200, 150));
			this->text.setString(this->welcomeString);
		}
		else
		{
			this->text.setFillColor(sf::Color::White);
			this->text.setString(this->textString.str());
		}
	}
}

void TextBox::update(sf::Vector2i& mouse_position)
{
	this->updateInput(mouse_position);
	this->updateText();
}

void TextBox::render(sf::RenderTarget& target)
{
	target.draw(this->back);
	target.draw(this->text);

	if (this->picked)
	{
		target.draw(this->fill);
	}
}
