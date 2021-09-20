#include "stdafx.h"
#include "Window.h"

#pragma warning( disable : 4996)

// private: Functions:

void Window::initVariables()
{
	this->resolution.x = 640;
	this->resolution.y = 360;

	this->framerateLimit = 30;

	this->buttonPressed = false;
	this->buttonHover = false;

	this->keyTime = 0.f;
	this->keyTimeMax = 5.f;
	this->keyTimeTick = 1.f;

	this->guiContainer.setSize(sf::Vector2f(260.f, 300.f));
	this->guiContainer.setPosition(sf::Vector2f(320.f, 40.f));
	this->guiContainer.setFillColor(sf::Color::Black);
	this->guiContainer.setOutlineColor(sf::Color::White);
	this->guiContainer.setOutlineThickness(-1.f);

	this->popUpTextColor = sf::Color::Yellow;
	this->popUpText.setFont(this->font);
	this->popUpText.setCharacterSize(20);
	this->popUpText.setFillColor(this->popUpTextColor);
	this->popUpText.setString("");
	this->popUpText.setPosition(350.f, 200.f);
}

void Window::initIcon(const std::string file_path)
{
	if (!this->icon.loadFromFile(file_path))
	{
		std::string className;
		className = typeid(*this).name();
		className.erase(0, 6);
		std::cout << "ERROR::" << className << "::setIcon::Failed to load: " << file_path << std::endl;
	}
}

void Window::initTexture(const Textures name, const std::string file_path)
{
	if (!this->textures[name].loadFromFile(file_path))
	{
		std::string className;
		className = typeid(*this).name();
		className.erase(0, 6);
		std::cout << "ERROR::" << className << "::initTexture::Failed to load: " << file_path << std::endl;
	}
}

void Window::initFont(const std::string file_path)
{
	if (!this->font.loadFromFile(file_path))
	{
		std::string className;
		className = typeid(*this).name();
		className.erase(0, 6);
		std::cout << "ERROR::" << className << "::initFont::Failed to load: " << file_path << std::endl;
	}
}

void Window::initTextBox()
{
	this->nameTextBox = new TextBox(this->font, 20u, sf::Color::White);
	this->nameTextBox->setPosition(350.f, 50.f);
	this->nameTextBox->setLimit();
	this->nameTextBox->setWelcomeString("Enter person name");

	this->fileTextBoxes[FileParts::Name] = new TextBox(70.f, 24.f, this->font, 20u, sf::Color::White);
	this->fileTextBoxes[FileParts::Name]->setPosition(350.f, 150.f);
	this->fileTextBoxes[FileParts::Name]->setLimit(true, 5);
	this->fileTextBoxes[FileParts::Name]->setDigitsOnly();
	this->fileTextBoxes[FileParts::Name]->setWelcomeString("123");

	this->fileTextBoxes[FileParts::Extension] = new TextBox(70.f, 24.f, this->font, 20u, sf::Color::White);
	this->fileTextBoxes[FileParts::Extension]->setPosition(420.f, 150.f);
	this->fileTextBoxes[FileParts::Extension]->setLimit(true, 5);
	this->fileTextBoxes[FileParts::Extension]->setWelcomeString(".txt");
}

void Window::initButtons()
{
	this->addButton = new Button
	(
		this->nameTextBox->getPosition().x + this->nameTextBox->getSize().x + 10.f,
		this->nameTextBox->getPosition().y, 
		this->nameTextBox->getSizeY(), this->nameTextBox->getSizeY(), 
		sf::Color::Yellow, &this->soundEngine,
		sfx::Sound::Button_Hover, sfx::Sound::Button_Add
	);
	this->addButton->setTexture(this->textures[Textures::Add]);

	this->fileAddButton = new Button
	(
		this->fileTextBoxes[FileParts::Extension]->getPosition().x + this->fileTextBoxes[FileParts::Extension]->getSize().x + 10.f,
		this->fileTextBoxes[FileParts::Extension]->getPosition().y, 
		this->fileTextBoxes[FileParts::Extension]->getSize().y, this->fileTextBoxes[FileParts::Extension]->getSize().y,
		sf::Color::Yellow, &this->soundEngine,
		sfx::Sound::Button_Hover, sfx::Sound::Button_Add
	);
	this->fileAddButton->setTexture(this->textures[Textures::Add_File]);
}

void Window::initList()
{
	this->list = new List(50.f, 40.f, this->font, 20u, sf::Color::White, this->textures[Textures::Remove], &this->soundEngine);
}

void Window::initSound()
{
	// Sounds
	this->soundEngine.initSound(sfx::Sound::Button_Add, "Resources/Sounds/Button_Add.mp3");
	this->soundEngine.initSound(sfx::Sound::Button_Remove, "Resources/Sounds/Button_Remove.mp3");
	this->soundEngine.initSound(sfx::Sound::Button_Hover, "Resources/Sounds/Button_Hover.mp3");

	// Music
	this->soundEngine.initMusic(sfx::Music::MainMenu, "Resources/Music/MainMenu.mp3");
}


// Constructors and Destructor:

Window::Window()
{
	this->initVariables();
	this->initIcon("Resources/Textures/LSMR_Test_add.png");
	this->initTexture(Textures::Add, "Resources/Textures/add_24x24.png");
	this->initTexture(Textures::Add_File, "Resources/Textures/add_file_24x24.png");
	this->initTexture(Textures::Remove, "Resources/Textures/remove_24x24.png");
	this->initFont("Fonts/PixellettersFull.ttf");
	this->initSound();

	this->window = new sf::RenderWindow
	(
		sf::VideoMode
		(
			this->resolution.x, 
			this->resolution.y
		), 
		"LSRM test application", 
		sf::Style::Close | sf::Style::Titlebar
	);

	this->window->setFramerateLimit(this->framerateLimit);
	this->window->setVerticalSyncEnabled(false);
	this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());

	this->initTextBox();
	this->initButtons();
	this->initList();

	this->soundEngine.playMusic(sfx::Music::MainMenu, true, false);
}

Window::~Window()
{
	// Deleting window
	delete this->window;

	// Deleting text boxes
	delete this->nameTextBox;
	for (auto& file_text_box : this->fileTextBoxes)
	{
		delete file_text_box.second;
	}
	this->fileTextBoxes.clear();

	// Deleting buttons
	delete this->addButton;
	delete this->fileAddButton;

	// Deleting list
	delete this->list;
}


// Accessors:

const bool Window::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}

	return false;
}

const bool Window::fileExist(const std::string file_path) const
{
	if (FILE* file = fopen(file_path.c_str(), "r"))
	{
		return true;
	}

	return false;
}


// Functions:

void Window::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		if (this->window->hasFocus())
		{
			this->update();
		}

		this->render();
	}
}

std::string Window::createFile(const std::string file_name)
{
	std::string path = "D:/Created Files/" + file_name;
//	std::string path = file_name;
	std::string path_new = "";
	
	if (this->fileExist(path))
	{
		std::string className;
		className = typeid(*this).name();
		className.erase(0, 6);
		std::cout << "ERROR::" << className << "::createFile::File is already exist: " << path << std::endl;

		for (int i = 0; i < 10; i++) // Limited for 10 just to be safe
		{
			path_new = path + "_" + std::to_string(i);

			if (this->fileExist(path_new))
			{
				std::string className;
				className = typeid(*this).name();
				className.erase(0, 6);
				std::cout << "ERROR::" << className << "::createFile::File is already exist: " << path_new << std::endl;
			}
			else
			{
				break;
			}
		}
		std::ofstream out{ path_new };
		out.close();
		return path_new;
	}
	else
	{
		std::ofstream out{ path };
		out.close();
		return path;
	}
}

std::string Window::createFile(const std::string file_name, const std::string file_extension)
{
//	std::string name = "D:/Created Files/" + file_name;
	std::string name = file_name;
	std::string extension = "." + file_extension;

	std::string name_new = "";

	if (this->fileExist(name + extension))
	{
		std::string className = typeid(*this).name();
		className.erase(0, 6);
		std::cout << "ERROR::" << className << "::createFile::File is already exist: " << name + extension << std::endl;

		for (int i = 0; i < 10; i++) // Limited for 10 just to be safe
		{
			 name_new = name + "_" + std::to_string(i);

			if (this->fileExist(name_new + extension))
			{
				std::string className = typeid(*this).name();
				className.erase(0, 6);
				std::cout << "ERROR::" << className << "::createFile::File is already exist: " << name_new + extension << std::endl;
			}
			else
			{
				break;
			}
		}
		std::ofstream out{ name_new + extension };
		out.close();
		return name_new + extension;
	}
	else
	{
		std::ofstream out{ name + extension };
		out.close();
		return name + extension;
	}
}

void Window::updatePollEvents()
{
	// Polling events
	while (this->window->pollEvent(this->windowEvent))
	{
		switch (this->windowEvent.Event::type)
		{
		case sf::Event::Closed:
			this->window->close();
		case sf::Event::TextEntered:
			this->list->updateInputEvents(this->windowEvent);
			this->nameTextBox->updateInputEvents(this->windowEvent);
			for (auto& file_text_box : this->fileTextBoxes)
			{
				file_text_box.second->updateInputEvents(this->windowEvent);
			}
		}		
	}
}

void Window::updateMousePositions()
{
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);
}

void Window::updateKeyTime()
{
	this->keyTime += this->keyTimeTick;
}

void Window::updateInput()
{
	// Button - Add
	if (this->addButton->isPressed() || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && this->nameTextBox->isSelected()))
	{
		if (this->buttonPressed == false)
		{
			this->buttonPressed = true;

			this->list->add(this->nameTextBox->getString());

			this->nameTextBox->setString("");
		}	
	}
	else if (this->fileAddButton->isPressed())
	{
		if (this->buttonPressed == false)
		{
			this->buttonPressed = true;

			if (this->fileTextBoxes[FileParts::Name]->getString() == "")
			{
				this->popUpText.setString("File name required");
			}
			else if (this->fileTextBoxes[FileParts::Extension]->getString() == "")
			{
				this->popUpText.setString("File extension required");
			}
			else
			{
				std::string file_name = this->createFile(this->fileTextBoxes[FileParts::Name]->getString(), this->fileTextBoxes[FileParts::Extension]->getString());
				this->popUpText.setString("File created: " + file_name);

				this->fileTextBoxes[FileParts::Name]->setString("");
				this->fileTextBoxes[FileParts::Extension]->setString("");
			}			
			
			this->popUpTextColor.a = 255;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && this->fileTextBoxes[FileParts::Name]->isSelected())
	{
		if (this->buttonPressed == false)
		{
			this->buttonPressed = true;

			if (this->fileTextBoxes[FileParts::Name]->getString() == "")
			{
				this->popUpText.setString("File name required");
				this->popUpTextColor.a = 255;
			}
			else
			{
				if (this->fileTextBoxes[FileParts::Extension]->getString() == "")
				{
					this->fileTextBoxes[FileParts::Name]->setSelected(false);
					this->fileTextBoxes[FileParts::Extension]->setSelected();
				}
				else
				{
					std::string file_name = this->createFile(this->fileTextBoxes[FileParts::Name]->getString(), this->fileTextBoxes[FileParts::Extension]->getString());
					this->popUpText.setString("File created: " + file_name);
					this->popUpTextColor.a = 255;

					this->fileTextBoxes[FileParts::Name]->setSelected();
					this->fileTextBoxes[FileParts::Extension]->setSelected(false);

					this->fileTextBoxes[FileParts::Name]->setString("");
					this->fileTextBoxes[FileParts::Extension]->setString("");
				}
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && this->fileTextBoxes[FileParts::Extension]->isSelected())
	{
		if (this->buttonPressed == false)
		{
			this->buttonPressed = true;

			if (this->fileTextBoxes[FileParts::Extension]->getString() == "")
			{
				this->popUpText.setString("File extension required");
				this->popUpTextColor.a = 255;
			}
			else
			{
				if (this->fileTextBoxes[FileParts::Name]->getString() == "")
				{
					this->fileTextBoxes[FileParts::Name]->setSelected();
					this->fileTextBoxes[FileParts::Extension]->setSelected(false);
				}
				else
				{
					std::string file_name = this->createFile(this->fileTextBoxes[FileParts::Name]->getString(), this->fileTextBoxes[FileParts::Extension]->getString());
					this->popUpText.setString("File created: " + file_name);
					this->popUpTextColor.a = 255;

					this->fileTextBoxes[FileParts::Name]->setSelected();
					this->fileTextBoxes[FileParts::Extension]->setSelected(false);

					this->fileTextBoxes[FileParts::Name]->setString("");
					this->fileTextBoxes[FileParts::Extension]->setString("");
				}
			}
		}
	}
	else
	{
		this->buttonPressed = false;
	}
}

void Window::updateTextBoxes()
{
	this->nameTextBox->update(this->mousePositionWindow);
	for (auto& file_text_box : this->fileTextBoxes)
	{
		file_text_box.second->update(this->mousePositionWindow);
	}
}

void Window::updateButtons()
{
	// Button - Add
	this->addButton->update(this->mousePositionWindow);

	// Button - File add
	this->fileAddButton->update(this->mousePositionWindow);
}

void Window::updatePopUpText()
{
	if (this->popUpTextColor.a > 0)
	{		
		this->popUpTextColor.a -= 3;

		if (this->popUpTextColor.a < 0)
		{
			this->popUpTextColor.a = 0;
		}
		this->popUpText.setFillColor(this->popUpTextColor);
	}
}

void Window::updateSound()
{
	this->soundEngine.fadeIn();
	this->soundEngine.update(0.f);
}

void Window::update()
{
	this->updateMousePositions();
	this->updateKeyTime();	
	this->updateTextBoxes();
	this->updateButtons();
	this->updateInput();
	this->list->update(this->mousePositionWindow);
	this->updatePopUpText();
	this->updateSound();
}

void Window::render()
{
	// Clearing window
	this->window->clear(sf::Color(0, 20, 40));

	// Text boxes
	this->nameTextBox->render(*this->window);
	for (auto& file_text_box : this->fileTextBoxes)
	{
		file_text_box.second->render(*this->window);
	}

	// Buttons Add
	this->addButton->render(*this->window);
	this->fileAddButton->render(*this->window);

	// List
	this->list->render(*this->window);

	// PopUp text
	this->window->draw(this->popUpText);

	// Displaying window
	this->window->display();
}