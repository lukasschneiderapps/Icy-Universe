#pragma once

#include "point.hpp"

#include "SFML/Graphics.hpp"

bool pointInRect(sf::FloatRect rect, Point p)
{
	if (p.x >= rect.left && p.x <= rect.left + rect.width) {
		if (p.y >= rect.top && p.y <= rect.top + rect.height) {
			return true;
		}
	}
	return false;
}

bool rectIntersectsTriangle(sf::FloatRect rect, Point a, Point b, Point c)
{
	return
		pointInRect(rect, a) ||
		pointInRect(rect, b) ||
		pointInRect(rect, c);
}