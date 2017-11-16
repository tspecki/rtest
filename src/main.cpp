// Space Spiel

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <iostream>
#include <math.h>

  

#define WIDTH 1900
#define HEIGHT 900

#define PI 3.14159265




//################################################################################
// Ojekt
//################################################################################

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


//################################################################################
// Objekt Functions
//################################################################################


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
  


//################################################################################
// Ship
//################################################################################



class GameWindow;

class Ship : public Objekt
{
private:
  Gosu::Image &pic_ship;
    
  //screen Pointer
  GameWindow &scr;

  int angle;
  
public:
  Ship(Gosu::Image &ship, GameWindow &screen);

  void tick();

  void moveRight();
  
  void moveLeft();
  
  void draw();

  int getA();
};


//################################################################################
// Fireball
//################################################################################


class Fireball : public Objekt
{
private:
  Gosu::Image &pic_fireball;
    
  //screen Pointer
  GameWindow &scr;

  int angle;
  //move vektor
  int v_x;
  int v_y;

  //center point
  int c_x;
  int c_y;

  //image scale
  const double scale;
public:
  Fireball(Gosu::Image &fireball, GameWindow &screen, int x, int y, int angle);

  void tick();

  void draw();

  int getCX();
  int getCY();

  bool inField(int viw_x, int viw_y, int viw_w, int viw_h);
};


//################################################################################
// Enemie
//################################################################################


class Enemie : public Objekt
{
private:
  Gosu::Image &pic_enemie;
    
  //screen Pointer
  GameWindow &scr;

  //image scale
  const double scale;
public:
  Enemie(Gosu::Image &enemie, GameWindow &screen, int x, int y);

  void tick();

  void draw();

  bool collisionP(int p_x, int p_y);
};


//################################################################################
// GameWindow
//################################################################################




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
  Gosu::Image pic_ship;
  Gosu::Image pic_fireball;

  Ship player;

  std::vector<Fireball*> rockets;
  void deleteFireballs();

  int shotcount;
  
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

//################################################################################
// Ship Functions
//################################################################################

Ship::Ship(Gosu::Image &ship, GameWindow &screen): pic_ship(ship), scr(screen)
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

  //rotate back
  if(angle > 0)
    angle -= 1;
  else if(angle < 0)
    angle += 1;
    
}

void Ship::moveRight()
{
  x += 5;
  //rotate right
  if (angle < 40)
    angle +=3;
}

  
void Ship::moveLeft()
{
  x -= 5;
  //rotate left
  if(angle > -40)
    angle -= 3;
}
  
void Ship::draw()
{
  //player in ebene 4
  pic_ship.draw_rot(scr.onScX(x), scr.onScY(y), 4, angle, 0.5, 0.5, 0.5, 0.5);
}
 
int Ship::getA()
{
  return angle;
}
 

//################################################################################
// Fireball Functions
//################################################################################

Fireball::Fireball(Gosu::Image &fireball, GameWindow &screen, int x, int y, int angle): pic_fireball(fireball), scr(screen)
										      , angle(angle), scale(0.20)
{
  //std::cout << "Fireball created" << std::endl;

  this->x = x;
  this->y = y;
  
  w = pic_fireball.width() / 2;
  h = pic_fireball.height() / 2;

  v_x = -std::cos((angle + 90) * PI / 180.0) * 10.0;
  v_y = std::sin((angle + 90) * PI / 180.0) * 10.0;
}

  
void Fireball::tick()
{
  //move in direction (angle) :)
  x += v_x;
  y += v_y;
  
}
  
void Fireball::draw()
{
  //fireballs in ebene 3
  pic_fireball.draw_rot(scr.onScX(x), scr.onScY(y), 3, angle, 0.5, 0.5, scale, scale);
}


int Fireball::getCX()
{
  return x + ((w*scale) / 2.0);
}

int Fireball::getCY()
{
  return y + ((h*scale)/ 2.0);
}
 
  
bool Fireball::inField(int viw_x, int viw_y, int viw_w, int viw_h)
{
  if(getCX() >= viw_x && getCX() <= viw_x + viw_w)
    {
      if(getCY() <= viw_y && getCY() >= viw_y - viw_h)
	 {
	   return true;
	 }
    }
  return false;
}

//################################################################################
// GameWindow Functions
//################################################################################


  
GameWindow::GameWindow()
  : viw_h(HEIGHT), viw_w(WIDTH), Window(WIDTH, HEIGHT), pic_sternenhimmel("media/sternenhimmel.png"),
    pic_ship("media/ship.png"), pic_fireball("media/fireball.png"), player(pic_ship, *this)
{
  set_caption("RAR Shot");

  //Get width and height for background calculation
  pic_b_w = pic_sternenhimmel.width();
  pic_b_h = pic_sternenhimmel.height();

  viw_x = 0;
  viw_y = 0;
  shotcount = 0;
}

void GameWindow::draw() {
  //Draw the background (sternenhimmel) in the background :D
  drawBackground(); //z = 0
  player.draw();

  //draw Fireballs
  for(Fireball* ball : rockets) {
    ball->draw();
  }
    
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

	  //hintegrund in ebene 0
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

  
  //update Fireballs
  for(Fireball* ball : rockets) {
    ball->tick();
  }
  deleteFireballs();
  //update shotCounter
  if(shotcount > 0)
  {
      shotcount--;
  }
  
    
}

void GameWindow::updateView()
{
  viw_x = (player.getX() + (player.getW()/2.0)) - (viw_w / 2.0);
  viw_y = (player.getY() - player.getH() - 20) + (viw_h);
}



void GameWindow::deleteFireballs()
{
  //remove fireball not in view
  for(std::vector<Fireball*>::iterator it = rockets.begin(); it != rockets.end(); ++it) {
    if(!(*it)->inField(viw_x, viw_y, viw_w, viw_h))
    {
      rockets.erase(it);
      //std::cout << "Delete fireball" << std::endl;
      it--;
    }
  }
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
      if (shotcount == 0)
	{
	  
	  rockets.push_back(new Fireball(pic_fireball, *this, player.getX(), player.getY(), player.getA()));
	  shotcount = 16;
	}
     
    }
}
  


//################################################################################
// Main
//################################################################################




int main(int argc, const char** argv)
{
  GameWindow window;
  window.show();
  return 0;
}
