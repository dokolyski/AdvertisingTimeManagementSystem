#include "pch.h"
#include "Form.h"

Form::Form(int w, int h, sf::String label, FilesManager * _fm, bool TitleBar)
{
	if(TitleBar)
		this->Window = new sf::RenderWindow(sf::VideoMode(w, h),label, sf::Style::Close);
	else
		this->Window = new sf::RenderWindow(sf::VideoMode(w, h), label, sf::Style::None);
	this->Background = new sf::RectangleShape(sf::Vector2f(w, h));
	this->Background->setFillColor(sf::Color(254, 230, 109));
	this->fm = _fm;
	this->Visible = true;
}

void Form::draw()
{
	this->Window->draw(*this->Background);
	int size = Content.size();
	for (int i = 0; i < size; i++)
		Content[i]->draw(*Window);
}

void Form::cursorHover()
{
	int size = Content.size();
	for (int i = 0; i < size; i++)
		Content[i]->cursorHover(sf::Mouse::getPosition(*this->Window).x, sf::Mouse::getPosition(*this->Window).y);
}

std::vector <Stuff*> Form::click()
{
	std::vector <Stuff*> vec;
	int size = Content.size();
	for (int i = 0; i < size; i++)
	{
		Stuff * clickedElement = NULL;
		clickedElement = Content[i]->clicked(sf::Mouse::getPosition(*this->Window).x, sf::Mouse::getPosition(*this->Window).y);
		if (clickedElement)
			vec.push_back(clickedElement);
	}
	return vec;
}

std::vector <Stuff*> Form::input(sf::Uint32 c)
{
	std::vector <Stuff*> vec;
	int size = Content.size();
	for (int i = 0; i < size; i++)
	{
		if(Content[i]->input(c))
			vec.push_back(Content[i]);
	}
	return vec;
}

void Form::setVisible(bool x)
{
	bool prev = this->isVisible();
	this->Window->setVisible(x);
	this->Window->setActive(x);
	this->Visible = x;
	if ((x) && (x != prev))
		this->afterVisible();
	if ((!x) && (x != prev))
		this->afterUnvisible();
}

void Form::newObject(Stuff * object) { Content.push_back(object); }

bool Form::isVisible(){ return this->Visible; }

bool Form::hasFocus() { return Window->hasFocus(); }

void Form::windowService()
{
	this->Window->clear();
	this->cursorHover();

	//std::cout << sf::Mouse::getPosition(*this->Window).x<<" "<< sf::Mouse::getPosition(*this->Window).y<<std::endl;

	sf::Event event;
	while (this->Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->setVisible(false);
			
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::vector <Stuff*> clickedElements = this->click();
				for (int i = 0; i < clickedElements.size(); i++)
					this->afterClick(clickedElements[i]);
			}
		}

		if (event.type == sf::Event::TextEntered)
		{
			std::vector <Stuff*> inputElements  = this->input(event.text.unicode);
			for (int i = 0; i < inputElements.size(); i++)
				this->afterInput(inputElements[i]);
		}
	}

	this->draw();
	this->Window->display();
}