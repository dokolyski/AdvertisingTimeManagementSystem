#pragma once
#include <SFML/Graphics.hpp>

class Style 
{
public:
	sf::Color BackgroundColor, BordersColor, TextColor, CursorHoveringColor, SelectingColor;
	sf::Font Font;
	int BordersThickness;
	Style(sf::Color _BackgroundColor, sf::Color _BordersColor, sf::Color _TextColor, sf::Color _CursorHoveringColor, sf::Color _SelectingColor, sf::Font  _f);
};