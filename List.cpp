#include "stdafx.h"
#include "List.h"

// private: Functions:

void List::initVariables()
{
	this->buttonPressed = false;

	this->amount = 0;
	this->capacity = 8;
}


// Constructors and Destructor:

List::List(float x, float y, sf::Font& font, unsigned int char_size, sf::Color text_color, sf::Texture& texture, sfx::SoundEngine* sound_engine)
	: font(font), texture(texture)
{
	this->initVariables();

	this->charSize = char_size;
	this->textColor = text_color;

	this->container.setSize(sf::Vector2f(200.f, 300.f));
	this->container.setPosition(x, y);
	this->container.setFillColor(sf::Color(0, 30, 50));
	this->container.setOutlineColor(sf::Color(0, 60, 90));
	this->container.setOutlineThickness(-1.f);

	this->soundEngine = sound_engine;
}

List::~List()
{
	// Deleting text boxes
	for (auto* text_box : this->textBoxes)
	{
		delete text_box;
	}
	this->textBoxes.clear();

	// Deleting buttons
	for (auto* button : this->buttons)
	{
		delete button;
	}
	this->buttons.clear();
}

const sf::Vector2f List::getElementPosition(const int index) const
{
	if (index >= 0 && static_cast<size_t>(index) < this->textBoxes.size())
	{
		return this->textBoxes[index]->getPosition();
	}

	std::string className = typeid(*this).name();
	className.erase(0, 6);
	std::cout << "ERROR::" << className << "::getPositionText::Index is out of range" << std::endl;

	return sf::Vector2f();
}

const TextBox& List::getLastElement() const
{
	return *this->textBoxes.back();
}

const TextBox& List::getElement(const int index) const
{
	if (index >= 0 && static_cast<size_t>(index) < this->textBoxes.size())
	{
		return *this->textBoxes[index];
	}

	std::string className = typeid(*this).name();
	className.erase(0, 6);
	std::cout << "ERROR::" << className << "::getElement::Index is out of range" << std::endl;

	return this->getLastElement();
}

const int& List::getAmount() const
{
	return this->amount;
}

const int& List::getCapacity() const
{
	return this->capacity;
}


// Accessors:

//


// Modifiers:

void List::setString(const std::string str)
{

}

// Functions:

bool List::add(const std::string str)
{	
	if (this->amount < this->capacity)
	{
		this->textBoxes.push_back(new TextBox(this->font, this->charSize, this->textColor));
		this->textBoxes.back()->setLimit();
		this->textBoxes.back()->setPickable();
		this->textBoxes.back()->setWelcomeString("Enter person name");
		this->textBoxes.back()->setString(str);
		this->buttons.push_back
		(
			new Button
			(
				this->textBoxes.back()->getPosition().x + this->textBoxes.back()->getSize().x + this->textBoxes.back()->getSize().x / 10.f, 
				this->textBoxes.back()->getPosition().y, 
				this->textBoxes.back()->getSize().y, 
				this->textBoxes.back()->getSize().y, 
				sf::Color::Yellow, 
				this->soundEngine,
				sfx::Sound::Button_Hover,
				sfx::Sound::Button_Remove
			)
		);
		this->buttons.back()->setTexture(this->texture);

		++this->amount;
		this->updatePositions();

		return true;
	}
	
	return false;
}

bool List::remove(const unsigned int index)
{
	if (this->amount > 0)
	{
		delete this->textBoxes[index];
		this->textBoxes.erase(this->textBoxes.begin() + index);
		delete this->buttons[index];
		this->buttons.erase(this->buttons.begin() + index);

		--this->amount;
		this->updatePositions();

		return true;
	}
	
	return false;
}

void List::updatePositions()
{
	for (size_t i = 0; i < this->textBoxes.size(); i++)
	{
		if (i == 0)
		{
			this->textBoxes[i]->setPosition(this->container.getPosition().x + (this->container.getSize().x / 20.f), this->container.getPosition().y + ((this->container.getSize().y / 30.f) * static_cast<float>(i + 1u)));
			this->buttons[i]->setPosition(this->textBoxes[i]->getPosition().x + this->textBoxes[i]->getSize().x + this->textBoxes[i]->getSize().x / 20.f, this->textBoxes[i]->getPosition().y);
		}
		else
		{
			this->textBoxes[i]->setPosition(this->container.getPosition().x + (this->container.getSize().x / 20.f), this->container.getPosition().y + ((this->container.getSize().y / 30.f) * static_cast<float>(i + 1u) + (this->textBoxes[i]->getSize().y * static_cast<float>(i))));
			this->buttons[i]->setPosition(this->textBoxes[i]->getPosition().x + this->textBoxes[i]->getSize().x + this->textBoxes[i]->getSize().x / 20.f, this->textBoxes[i]->getPosition().y);
		}
	}
}

void List::updateInputEvents(sf::Event& input)
{
	for (auto* text_box : this->textBoxes)
	{
		text_box->updateInputEvents(input);
	}
}

void List::updateInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (this->buttonPressed == false)
		{
			this->buttonPressed = true;

			for (size_t i = 0; i < this->buttons.size(); i++)
			{
				if (this->buttons[i]->isPressed())
				{
					this->remove(i);
				}
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		if (this->buttonPressed == false)
		{
			this->buttonPressed = true;

			for (size_t i = 0; i < this->textBoxes.size(); i++)
			{
				if (this->textBoxes[i]->isSelected())
				{
					this->textBoxes[i]->setSelected(false);
				}
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Delete))
	{
		if (this->buttonPressed == false)
		{
			this->buttonPressed = true;

			uint32_t index = 0;

			for (auto* text_box : this->textBoxes)
			{
				if (this->textBoxes[index]->isPicked() || this->textBoxes[index]->isSelected())
				{
					this->remove(index);
					--index;
				}

				++index;
			}
		}
	}
	else
	{
		this->buttonPressed = false;
	}
}

void List::update(sf::Vector2i& mouse_position)
{
	// Updating text boxes
	for (auto * text_box : this->textBoxes)
	{
		text_box->update(mouse_position);
	}

	// Updating buttons
	for (auto* button : this->buttons)
	{
		button->update(mouse_position);
	}

	// Updating input
	this->updateInput();
}

void List::render(sf::RenderTarget& target)
{
	// Container
	target.draw(this->container);

	// Back
	for (auto* text_box : this->textBoxes)
	{
		text_box->render(target);
	}

	// Text
	for (auto* button : this->buttons)
	{
		button->render(target);
	}
}
