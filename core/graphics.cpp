#include <util/vec2.h>
#include <util/ext_math.h>

#include "graphics.h"

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

TGraphics::TGraphics(std::shared_ptr<sf::RenderWindow> win, TVec2<int> ws)
{
	Window = win;
	FillColor = TColor(0, 0, 0, 255);
	WindowSize = ws;
	SetDefaultCamera();
}

TGraphics::TGraphics(std::shared_ptr<sf::RenderWindow> win, TVec2<int> ws, TCamera::SPtr camera)
{
	Window = win;
	FillColor = TColor(0, 0, 0, 255);
	WindowSize = ws;
	Camera = camera;
}

void TGraphics::DrawPoint(float x, float y)
{
	DrawPoint(TVec2<float>(x, y));
}
void TGraphics::DrawPoint(TVec2<float> pos)
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(1, 1));
	rectangle.setPosition(pos.X, pos.Y);

	rectangle.setFillColor(sf::Color(FillColor.R, FillColor.G, FillColor.B, FillColor.A));

	Window->draw(rectangle);
}

void TGraphics::DrawCircle(float x, float y, float radius)
{
	DrawCircle(TVec2<float>(x, y), radius);
}
void TGraphics::DrawCircle(TVec2<float> pos, float radius)
{
	sf::CircleShape circle;
	circle.setRadius(radius);
	circle.setPosition(pos.X - radius, pos.Y - radius);

	circle.setFillColor(sf::Color(FillColor.R, FillColor.G, FillColor.B, FillColor.A));

	Window->draw(circle);
}

void TGraphics::DrawBrokenLine(std::vector<TVec2<float>> t, TVec2<float> a, float s)
{
	for (size_t i = 1; i < t.size(); i++)
	{
		DrawLine(t[i - 1] * s + a, t[i] * s + a);
	}
}

void TGraphics::DrawLine(TVec2<float> v1, TVec2<float> v2)
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(v1.X, v1.Y), sf::Color(FillColor.R, FillColor.G, FillColor.B, FillColor.A)),
		sf::Vertex(sf::Vector2f(v2.X, v2.Y), sf::Color(FillColor.R, FillColor.G, FillColor.B, FillColor.A))
	};

	Window->draw(line, 2, sf::Lines);
}

void TGraphics::DrawLine(float x1, float y1, float x2, float y2)
{
	DrawLine(TVec2<float>(x1, y1), TVec2<float>(x2, y2));
}


void TGraphics::DrawRect(float x, float y, float W, float h)
{
	DrawRect(TVec2<float>(x, y), TVec2<float>(W, h));
}

void TGraphics::DrawRect(TVec2<float> pos, TVec2<float> size)
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(size.X, size.Y));
	rectangle.setPosition(pos.X, pos.Y);

	rectangle.setFillColor(sf::Color(FillColor.R, FillColor.G, FillColor.B, FillColor.A));

	Window->draw(rectangle);
}

void TGraphics::DrawTexture(sf::Texture& tex, float x, float y, float W, float h)
{
	DrawTexture(tex, TVec2<float>(x, y), TVec2<float>(W, h));
}

void TGraphics::DrawTexture(sf::Texture& tex, TVec2<float> pos, TVec2<float> size)
{
	sf::Sprite sprite;
	sprite.setTexture(tex);

	sf::Vector2u s = tex.getSize();

	sprite.setPosition(pos.X - size.X / 2, pos.Y - size.Y / 2);
	sprite.setScale(size.X / s.x, size.Y / s.y);

	Window->draw(sprite);
}

void TGraphics::DrawTexture(sf::Texture& tex, TVec2<float> pos, TVec2<float> size, float a)
{
	sf::Sprite sprite;
	sprite.setTexture(tex);

	sf::Vector2u s = tex.getSize();

	sprite.setPosition(pos.X - size.X / 2, pos.Y - size.Y / 2);
	sprite.setScale(size.X / s.x, size.Y / s.y);

	sprite.setOrigin(size.X / 2, size.Y / 2);
	sprite.setRotation(NExtMath::ToDegrees(a));

	Window->draw(sprite);
}

void TGraphics::Present()
{
	Window->display();
}

void TGraphics::SetFillColor(float r, float g, float b, float a)
{
	FillColor.R = r;
	FillColor.G = g;
	FillColor.A = b;
	FillColor.A = a;
}

void TGraphics::SetFillColor(TColor col)
{
	FillColor = col;
}

void TGraphics::Fill()
{
	TCamera::SPtr c = std::make_shared<TCamera>();

	ApplyCamera(c);
	DrawRect(0, 0, Window->getSize().x, Window->getSize().y);
	ApplyCamera(Camera);
}

void TGraphics::Clear()
{
	Window->clear();
}

void TGraphics::FillText(const std::string& text, float x, float y, float size, sf::Font& font)
{
	sf::Text t;

	t.setFont(font);
	t.setString(text);
	t.setPosition(x, y);
	t.setCharacterSize(size);
	t.setFillColor(sf::Color(FillColor.R, FillColor.G, FillColor.B, FillColor.A));
	Window->draw(t);
}

void TGraphics::ApplyCamera(TCamera::SPtr camera)
{
	sf::View view;
	TVec2<float> p = camera->Position - WindowSize / 2;
	TVec2<float> s = WindowSize * camera->Scale;

	view.reset(sf::FloatRect(p.X, p.Y, s.X, s.Y));
	view.rotate(camera->Angle);
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	Window->setView(view);
}

void TGraphics::SetCamera(TCamera::SPtr camera)
{
	Camera = camera;
}

void TGraphics::UpdateViewport()
{
	ApplyCamera(Camera);
}

void TGraphics::SetDefaultCamera()
{
	Camera = std::make_shared<TCamera>();
}
