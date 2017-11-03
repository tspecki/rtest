// Space Spiel

#include "stdafx.h"
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
//using namespace std;

class GameWindow : public Gosu::Window {
public:
	Gosu::Image bild, bild2, pic_fire, pic_shot;
	GameWindow()
		: Window(1500, 900)
		, bild("sternenhimmel.png")
		, bild2("rakete.png")
		, pic_fire("fire.png")
		, pic_shot("feuerball.png")
	{
		set_caption("Testspiel");
	}

	double x = 0.0;			//Parameter für Hintergrund
	double y = 400.0;

	double shot_x = 725.0;	//Parameter für Schuss
	double shot_y = 610.0;

	bool shot_anz = false;

	double rot_fire = 0.0;	//Feuer der Rakete

	double flames(double min, double max)
	{
		double f = (double)rand() / RAND_MAX;
		return min + f*(max - min);
	}

	void rocket()
	{
		bild2.draw_rot(600.0, 650.0, 1.0, 0.0, 0.0, 0.0);

		if (input().down(Gosu::KB_UP))
		{
			pic_fire.draw_rot(753.0, 818.0, 0.0, rot_fire, 0.6, 0.0, 0.07, 0.2);
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
	void shot(bool shot_anz)
	{
		if (shot_anz == true)
		{
			pic_shot.draw_rot(shot_x, shot_y, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1);
		}
	}

	void update() override {

		if (input().down(Gosu::KB_LEFT))
		{
			x = x + 2;
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
 		if (input().down(Gosu::KB_SPACE))
		{
			shot_anz = true;
		}
		if (shot_anz == true)
		{
			shot_y = shot_y - 8;
		}
		if (shot_y <= 0)
		{
			shot_anz = false;
			shot_y = 610.0;
		}
	}
	void draw() override {
		background();
		rocket();
		shot(shot_anz);
	}
};
int main()
{
	GameWindow window;
	window.show();
}
