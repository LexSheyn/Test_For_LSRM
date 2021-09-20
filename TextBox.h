#pragma once

enum class Keys
{
	BackSpace = 8,
	Enter = 13,
	Escape = 27
};

class TextBox
{
private:

// Variables:

	sf::RectangleShape back;
	sf::RectangleShape fill;
	sf::Vector2f size;
	sf::Text text;
	std::stringstream textString;
	std::string welcomeString;

	bool digitsOnly;
	bool hasLimit;
	int limit;

	bool selected;

	bool picked;
	bool pickable;

	bool pressed;

// private: Functions:

	void initVariables();
	void inputChar(int char_typed);

public:

//Constructors and Destructor:

	TextBox(sf::Font& font, unsigned int char_size, sf::Color color);
	TextBox
	(
		float width, float height,
		sf::Font& font, unsigned int char_size, sf::Color color
	);
	virtual ~TextBox();

// Accessors:

	const std::string getString() const;
	const float getSizeX() const;
	const float getSizeY() const;
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getSize() const;
	const sf::FloatRect getGlobalBounds() const;
	const bool& isSelected() const;
	const bool& isPicked() const;

// Modifiers:

	void setFont(sf::Font& font);
	void setString(const std::string str);
	void setWelcomeString(const std::string str);
	void setPosition(const float x, const float y);
	void setLimit(const bool has_limit = true, const int limit = 10);
	void setDigitsOnly(const bool only_digits = true);
	void setSelected(const bool selected = true);
	void setPicked(const bool picked = true);
	void setPickable(const bool pickable = true);

// Functions:

	void deleteLastChar();

	void updateInputEvents(sf::Event& input);
	void updateInput(sf::Vector2i& mouse_position);
	void updateText();
	void update(sf::Vector2i& mouse_position);

	void render(sf::RenderTarget& target);
};

