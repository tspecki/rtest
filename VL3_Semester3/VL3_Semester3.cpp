// VL3_Semester3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

const int Fensterbreite = 1080;
const int Fensterhöhe = 800;

double mausx, mausy;
double Rotation;

class GameWindow : public Gosu::Window {
public:
	Gosu::Image bild;
	Gosu::Image bild1;
	GameWindow()
		: Window(Fensterbreite,Fensterhöhe)
		, bild("Felix.png")
		, bild1("Scope.png")
	{
		set_caption("Gaertnershooter");
	}

	void update() override {
		mausx = input().mouse_x();
		mausy = input().mouse_y();
		Rotation += 1;
	}

	void draw() override {
		
		/*graphics().draw_line(
			10, 20, Gosu::Color::RED,
			200, 100, Gosu::Color::GREEN,
			0.0
		);
		graphics().draw_triangle(100, 100, Gosu::Color::GREEN,
			250, 150, Gosu::Color::AQUA,
			150, 300, Gosu::Color::BLUE,
			0.1
		);*/
		bild.draw_rot(Fensterbreite/2,Fensterhöhe/2, 0.0,
			Rotation, // Rotationswinkel in Grad
			0.5, 0.5 // Position der "Mitte" relativ zu x, y
		);

		bild1.draw_rot(mausx, mausy, 0.0,
			0, // Rotationswinkel in Grad
			0.5, 0.5 // Position der "Mitte" relativ zu x, y
		);
	}
};


int main()
{
GameWindow window;
window.show();
}
