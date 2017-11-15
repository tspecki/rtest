// Space Spiel

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <iostream>

  

#define WIDTH 1900
#define HEIGHT 900



class Objekt
{
protected:
  int x;
  int y;
  
  int w;
  int h;

  
  
public:
  Objekt();
  virtual void tick() = 0;
  virtual void draw() = 0;  

  int getX();
  
  int getY();

  int getW();

  int getH();
};

  



Objekt::Objekt()
{
  
}

int Objekt::getX() {
  return x;
}
  
int Objekt::getY()
{
  return y;
}

int Objekt::getW()
{
  return w;
}

int Objekt::getH()
{
  return h;
}
  

class GameWindow;

class Ship : public Objekt
{
private:
  Gosu::Image pic_ship;
    
  //screen Pointer
  GameWindow &scr;

  int angle;
  
public:
  Ship(GameWindow &screen);

  void tick();

  void moveRight();
  
  void moveLeft();
  
  void draw(); 
};





class GameWindow : public Gosu::Window {
private:

  //View Port position
  signed int viw_x;		    
  signed int viw_y;

  //real view = virtual view ... so no second variables
  const int viw_w;
  const int viw_h;

  //Background size
  int pic_b_w;
  int pic_b_h;
  
  Gosu::Image pic_sternenhimmel;

  Ship player;
  
public:

  
  GameWindow();

  void draw() override;

  //translate X to onScreen X Position
  int onScX(int xPos);

  //translate Y to onScreen Y Position
  int onScY(int yPos);

  
  void drawBackground();

  
  void update() override;
  

  void updateView();
  
  void exploitKeys();
  
};


Ship::Ship(GameWindow &screen): pic_ship("media/ship.png"), scr(screen)
{
  // std::cout << "Ship created" << std::endl;
  x = 0;
  y = 0;
  angle = 0;

  w = pic_ship.width() / 2;
  h = pic_ship.height() / 2;
}

  
void Ship::tick()
{
  //move up :)
  y += 2;
  if(angle > 0)
    angle -= 1;
  else if(angle < 0)
    angle += 1;
    
}

void Ship::moveRight()
{
  x += 5;
  if (angle > -40)
    angle -=3;
}

  
void Ship::moveLeft()
{
  x -= 5;
  if(angle < 40)
    angle += 3;
}
  
void Ship::draw()
{
  pic_ship.draw_rot(scr.onScX(x), scr.onScY(y), 1, angle, 0.5, 0.5, 0.5, 0.5);
}
 
  


  
GameWindow::GameWindow()
  : viw_h(HEIGHT), viw_w(WIDTH), Window(WIDTH, HEIGHT), pic_sternenhimmel("media/sternenhimmel.png"), player(*this)
{
  set_caption("RAR Shot");

  //Get width and height for background calculation
  pic_b_w = pic_sternenhimmel.width();
  pic_b_h = pic_sternenhimmel.height();

  viw_x = 0;
  viw_y = 0;

}

void GameWindow::draw() {
  //Draw the background (sternenhimmel) in the background :D
  drawBackground(); //z = 0
  player.draw();
    
}

//translate X to onScreen X Position
int GameWindow::onScX(int xPos)
{
  return (xPos - viw_x);
}

//translate Y to onScreen Y Position
int GameWindow::onScY(int yPos)
{
  return -(yPos - viw_y);
}

  
void GameWindow::drawBackground() {
    
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
	
	  //std::cout << pic_x_d << "," <<  pic_y_d << std::endl;
    
	  pic_sternenhimmel.draw(onScX(pic_x_d), onScY(pic_y_d), 0);

	  pic_x_d += pic_b_w;
	}
      pic_y_d -= pic_b_h;
    }
      
}
  
void GameWindow::update() {
  //User interaction
  exploitKeys();

  //ship events
  player.tick();

  //Move movie 
  updateView();
    
    
}

void GameWindow::updateView()
{
  viw_x = (player.getX() + (player.getW()/2.0)) - (viw_w / 2.0);
  viw_y = (player.getY() - player.getH() - 20) + (viw_h);
  
     
}

void GameWindow::exploitKeys()
{
    
  if (input().down(Gosu::KB_LEFT))
    {
      player.moveLeft();
      //std::cout << "Move left" << std::endl;
	
    }
    
  else if (input().down(Gosu::KB_RIGHT))
    {
      player.moveRight();
      //std::cout << "Move right" << std::endl;
    }
    
  if (input().down(Gosu::KB_SPACE))
    {
      //std::cout << "Fire!" << std::endl; 
	
    }
}
  






int main(int argc, const char** argv)
{
  GameWindow window;
  window.show();
  return 0;
}
