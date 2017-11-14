// Space Spiel

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <iostream>

class Schuss
{
  
private:
  double shot_x;
  double shot_y;

public:
  void set_x(double x) 
  {
    shot_x = x;
  }
  
  void set_y(double y)
  {
    shot_y = y;
  }
  
  double get_x()
  {
    return shot_x;
  }
  
  double get_y()
  {
    return shot_y;
  }
};

  
#define WIDTH 1900
#define HEIGHT 900

class GameWindow : public Gosu::Window {
private:

  //View Port position
  signed int viw_x;		    
  signed int viw_y;

  //real view = virtual view ... so no second variables
  const int viw_w = WIDTH;
  const int viw_h = HEIGHT;

  //Background size
  int pic_b_w;
  int pic_b_h;
  
public:
  Gosu::Image pic_sternenhimmel;

  
  GameWindow()
    :  Window(WIDTH, HEIGHT), pic_sternenhimmel("media/sternenhimmel.png")
  {
    set_caption("RAR Shot");

    //Get width and height for background calculation
    pic_b_w = pic_sternenhimmel.width();
    pic_b_h = pic_sternenhimmel.height();

    viw_x = 0;
    viw_y = 0;
  }

  void draw() override {
    //Draw the background (sternenhimmel) in the background :D
    drawBackground(); //z = 0
    
    
  }

  //translate X to onScreen X Position
  int onScX(int xPos)
  {
    return (xPos - viw_x);
  }

  //translate Y to onScreen Y Position
  int onScY(int yPos)
  {
    return -(yPos - viw_y);
  }

  
  void drawBackground() {
    
    signed int pic_x = 0;
    signed int pic_y = 0;

    if (viw_x < 0)
      pic_x = ((viw_x / pic_b_w) - 1) * pic_b_w;
    else
      pic_x = (viw_x / pic_b_w) * pic_b_w;

    if(viw_y > 0)
      pic_y = ((viw_y / pic_b_h) + 1) * pic_b_h;
    else
      pic_y = (viw_y / pic_b_h) * pic_b_h;

    //draw vars
    signed int pic_x_d = 0;
    signed int pic_y_d = 0;
    
    pic_y_d = pic_y;

    //render tiles
    while(pic_y_d >  viw_y - viw_h)
      {
	pic_x_d = pic_x;
	
	while(pic_x_d <  viw_x + viw_w)
	  {
	
	    std::cout << pic_x_d << std::endl;
	    std::cout << pic_y_d << std::endl;
    
	    pic_sternenhimmel.draw(onScX(pic_x_d), onScY(pic_y_d), 0);

	    pic_x_d += pic_b_w;
	  }
	pic_y_d -= pic_b_h;
      }
      
  }
  
  void update() override {
    //move up :D
    viw_y += 2;
    
    if (input().down(Gosu::KB_LEFT))
      {
	viw_x -= 1;
      }
    
    else if (input().down(Gosu::KB_RIGHT))
      {
	viw_x += 1;
      }
    
    if (input().down(Gosu::KB_SPACE))
      {
	
      }
  }

  
};




int main(int argc, const char** argv)
{
  GameWindow window;
  window.show();
  return 0;
}
