#include "pch.h"
#include "Style.h"

Style::Style(sf::Color _BackgroundColor, sf::Color _BordersColor, sf::Color _TextColor, sf::Color _CursorHoveringColor, sf::Color _SelectingColor, sf::Font _f)
{
	this->Font = _f;
	this->BackgroundColor = _BackgroundColor;
	this->BordersColor = _BordersColor;
	this->CursorHoveringColor = _CursorHoveringColor;
	this->SelectingColor = _SelectingColor;
	this->TextColor = _TextColor;
}