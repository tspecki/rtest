// Space Spiel
//

#include "stdafx.h"
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
//using namespace std;

class GameWindow : public Gosu::Window {
public:
	Gosu::Image bild, bild2, pic_fire;
	GameWindow()
		: Window(1500, 900)
		, bild("sternenhimmel.png")
		, bild2("rakete.png")
		, pic_fire("fire.png")
	{
		set_caption("Testspiel");
	}

	double x = 0.0;
	double y = 400.0;

	double rot_fire = 0.0;

	double ref_x = 0.0;
	double ref_y = 0.0;

	double flames(double min, double max)
	{
		double f = (double)rand() / RAND_MAX;
		return min + f*(max - min);
	}

	void rocket()
	{
		bild2.draw_rot(600.0, 650.0, 0.0, 0.0, 0.0, 0.0);

		if (input().down(Gosu::KB_UP))
		{
			pic_fire.draw_rot(756.0, 818.0, 0.0, rot_fire, 0.6, 0.0, 0.2, 0.2);
		}
	}
	void background()
	{
		double x0 = x;
		double y0 = y;

		while (x0 > 0)
		{
			x0 -= 500.0;
		}

		for (double x1 = x0; x1 < graphics().width(); x1 += 500.0)
		{
			bild.draw_rot(x1, y, 0.0, 0.0, 0.0, 0.0);
			bild.draw_rot(x1, y - 500.0, 0.0, 0.0, 0.0, 0.0);
			bild.draw_rot(x1, y - 1000.0, 0.0, 0.0, 0.0, 0.0);
		}
	}

	void update() override {

		if (input().down(Gosu::KB_LEFT))
		{
			x = x + 2;
			ref_x = ref_x - 1;
		}
		else if (input().down(Gosu::KB_RIGHT))
		{
			x = x - 2;
		}
		if (input().down(Gosu::KB_UP))
		{
			y = y + 2;
			rot_fire = flames(-9.0, 9.0);
		}
	}
	void draw() override {
		background();
		rocket();
	}
};
int main()
{
	GameWindow window;
	window.show();
}
