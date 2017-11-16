// Space Spiel

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <iostream>
#include <math.h>
#include <ctime>
  
#include <sstream>
#include <string>


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

  double scale;
  int angle;
  
public:
  Objekt();
  virtual void tick() = 0;
  virtual void draw() = 0;  

  int getX();
  
  int getY();

  int getW();

  int getH();

  int getA();

  bool inField(int viw_x, int viw_y, int viw_w, int viw_h);

  bool collisionP(int p_x, int p_y);

  
  bool overLine(int l_y);

  bool overlaps(int b_x, int b_y, int b_w, int b_h);
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
  
int Objekt::getA()
{
  return angle;
}



//this viw_x and viw_y  are in the upper left corner, not in the center
bool Objekt::inField(int viw_x, int viw_y, int viw_w, int viw_h)
{
  if(x + (w /2.0) >= viw_x && x - (w /2.0) <= viw_x + viw_w)
    {
      if(y - (h /2.0) <= viw_y && y + (h /2.0) >= viw_y - viw_h)
	 {
	   return true;
	 }
    }
  return false;
}


bool Objekt::collisionP(int p_x, int p_y)
{
  if(p_x >= x - (w/2.0) && p_x  <= x + (w/2.0))
    {
      if(p_y <= y + (h/2.0) && p_y  >= y - (h/2.0))
	 {
	   return true;
	 }
    }
  return false;
}

bool Objekt::overLine(int l_y)
{
  if(y + (h/2.0) >= l_y)
  {
    return true;
  }
  return false;
}


bool Objekt::overlaps(int b_x, int b_y, int b_w, int b_h)
{
  int b_l = b_x - (b_w / 2.0);
  int b_r = b_x + (b_w / 2.0);
  int b_t = b_y + (b_h / 2.0);
  int b_b = b_y - (b_h / 2.0);
  
  
  int l = x - (w / 2.0);
  int r = x + (w / 2.0);
  int t = y + (h / 2.0);
  int b = y - (h / 2.0);


  
  
  if(r > b_l && b < b_t && r <= b_r && b >= b_b)
    return true;
  if(l < b_r && b < b_t && l >= b_l && b >= b_b)
    return true;
  if(r > b_l && t > b_b && r < b_r && t <= b_t)
    return true;
  if(l < b_r && t > b_b && l >= b_l && t <= b_t)
    return true;

  return false;
  
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

  
public:
  Ship(Gosu::Image &ship, GameWindow &screen);

  void tick();

  void moveRight();
  
  void moveLeft();
  
  void draw();

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

  //move vektor
  int v_x;
  int v_y;


public:
  Fireball(Gosu::Image &fireball, GameWindow &screen, int x, int y, int angle);

  void tick();

  void draw();

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
  Gosu::Font font;

  int lives;
  std::string live;

public:
  Enemie(Gosu::Image &enemie, Gosu::Font font, GameWindow &screen, int x, int y);

  void tick();

  void draw();

  void hit();

  bool isDead();
  
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
  Gosu::Image pic_enemie;

  Ship player;

  std::vector<Fireball*> rockets;

  std::vector<Enemie*> enemies;
  
  int shotcount;

  Gosu::Font font;
  Gosu::Font fontBig;
  Gosu::Font fontBiger;
  
  
  std::string heightStr;

  bool running;
  
  void draw() override;
  void update() override;
  
  void drawBackground();
  void drawHeight();
  void updateView();
  
  void exploitKeys();
  
  void deleteFireballs();
  void deleteEnemies();


  void generateEnemies();

  
  void collisionEnemies();
  void collisionShip();

  void drawDeadScreen();
  
public:

  GameWindow();

  //translate X to onScreen X Position
  int onScX(int xPos);

  //translate Y to onScreen Y Position
  int onScY(int yPos);

  
  
};

//################################################################################
// Ship Functions
//################################################################################

Ship::Ship(Gosu::Image &ship, GameWindow &screen): pic_ship(ship), scr(screen)
{
  // std::cout << "Ship created" << std::endl;
  x = 0;
  y = 0;

  //shoud be const // but for animation purpose var
  scale = 0.5;
  
  angle = 0;

  w = pic_ship.width() * scale;
  h = pic_ship.height() * scale;
}

  
void Ship::tick()
{
      //move up :)
      y += 5;

      //rotate back
      if(angle > 0)
	angle -= 1;
      else if(angle < 0)
	angle += 1;

}

void Ship::moveRight()
{
  x += 3;
  //rotate right
  if (angle < 40)
    angle +=3;
}

  
void Ship::moveLeft()
{
  x -= 3;
  //rotate left
  if(angle > -40)
    angle -= 3;
}
  
void Ship::draw()
{
  //player in ebene 4
  pic_ship.draw_rot(scr.onScX(x), scr.onScY(y), 4, angle, 0.5, 0.5, scale, scale);
}
 
 
 

//################################################################################
// Fireball Functions
//################################################################################

Fireball::Fireball(Gosu::Image &fireball, GameWindow &screen, int x, int y, int angle): pic_fireball(fireball), scr(screen)
{
  //std::cout << "Fireball created" << std::endl;

  this->x = x;
  this->y = y;
  
  //shoud be const // but for animation purpose var
  scale = 0.1;
  this->angle = angle;
  
  w = pic_fireball.width() * scale;
  h = pic_fireball.height() * scale;

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


  


//################################################################################
// Enemie Functions
//################################################################################

Enemie::Enemie(Gosu::Image &enemie, Gosu::Font font, GameWindow &screen, int x, int y): pic_enemie(enemie), scr(screen), font(font)
{
  //std::cout << "Fireball created" << std::endl;

  //shoud be const // but for animation purpose var
  scale = 0.15;
  angle = 0;
  
  this->x = x;
  this->y = y;
  
  
  w = pic_enemie.width() * scale;
  h = pic_enemie.height() * scale;
  
  lives = std::rand() % 5 + 1;
  
  std::stringstream ss;
  for(int i = 0; i < lives; i++)
    {
      ss << "♥";
    }
  
  live = ss.str();
  
}


  
void Enemie::tick()
{
  //do enemie animation
}
  
void Enemie::draw()
{
  //enemie in ebene 2
  font.draw(live, scr.onScX(x - (w/4.0)), scr.onScY(y + (h/2.0) + 20), 3);
  pic_enemie.draw_rot(scr.onScX(x), scr.onScY(y), 2, angle, 0.5, 0.5, scale, scale);
}



void Enemie::hit()
{
  if(lives>0)
    {
      lives--;
      std::stringstream ss;
      for(int i = 0; i < lives; i++)
	{
	  ss << "♥";
	}
  
      live = ss.str();
      
    }
}


bool Enemie::isDead()
{
  return lives == 0;
}




//################################################################################
// GameWindow Functions
//################################################################################


  
GameWindow::GameWindow()
  : viw_h(HEIGHT), viw_w(WIDTH), Window(WIDTH, HEIGHT), pic_sternenhimmel("media/sternenhimmel.png"),
    pic_ship("media/ship.png"), pic_fireball("media/fireball.png"), pic_enemie("media/enemie.png"), player(pic_ship, *this), font(16), fontBig(24), fontBiger(60)
{
  set_caption("RAR Shot");

  //Get width and height for background calculation
  pic_b_w = pic_sternenhimmel.width();
  pic_b_h = pic_sternenhimmel.height();

  viw_x = 0;
  viw_y = 0;
  shotcount = 0;

  running = true;
   
 
  
  heightStr = "";
  
}

void GameWindow::draw() {
  //Draw the background (sternenhimmel) in the background :D
  drawBackground(); //z = 0
  drawHeight(); //z = 10
  player.draw();

  //draw Fireballs
  for(Fireball* ball : rockets) {
    ball->draw();
  }

  
  //draw Enemies
  for(Enemie* eny : enemies) {
    eny->draw();
  }


  if(!running)
    {
      drawDeadScreen();
    }
  

  
}


  
void GameWindow::drawDeadScreen() {
  //std::string

  fontBiger.draw("Game Over - Du hast eine Entfernung von " + std::to_string(player.getY()) + "m geschafft", 150, viw_h / 2.0, 12);
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


void GameWindow::drawHeight() {
  
  
  fontBig.draw(heightStr, 20, 20, 10);
}

  
void GameWindow::update() {
  
  if(running)
    {
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


      //update Enemie
      for(Enemie* eny : enemies) {
	eny->tick();
      }
      generateEnemies();
      deleteEnemies();


      //check collisions
      collisionEnemies();
      collisionShip();
  
    }
}

void GameWindow::updateView()
{
  viw_x = (player.getX()) - (viw_w / 2.0);
  viw_y = (player.getY() - (player.getH() / 2.0)) + (viw_h);

   
  heightStr = "Entfernung: " + std::to_string(player.getY()) + "m";
}

void GameWindow::deleteEnemies()
{
  //remove Enemies not in view
  for(std::vector<Enemie*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
    if(!(*it)->overLine(viw_y - viw_h))
    {
      delete (*it);  //Spiecher freigeben
      enemies.erase(it);
      //std::cout << "Delete enemie" << std::endl;
      it--;
      continue;
    }

    if((*it)->isDead())
    {
      //TODO: Enemie explode
      //TODO: Count dead enemies --- for fun reason
      delete (*it);  //Speiehcer freigeben
      enemies.erase(it);
      //std::cout << "Delete enemie" << std::endl;
      it--;
    }
  }
}


void GameWindow::generateEnemies()
{
  //There should be allways 20 Enemies in space
  if (enemies.size() < 32)
    {

      Enemie* temp;
      bool block = true;
      
      while(block){
	block = false;

	int randX = viw_x + (std::rand() % viw_w);
	int randY = viw_y + (std::rand() % 1500);
      
	temp = new Enemie(pic_enemie, font, *this, randX, randY);
	for(std::vector<Enemie*>::iterator en = enemies.begin(); en != enemies.end(); ++en) {
	  if(temp->overlaps((*en)->getX(), (*en)->getY(), (*en)->getW(),(*en)->getH()))
	    {
	      block = true;
	      delete temp;
	      break;
	    }
	}
	
      }
      enemies.push_back(temp);
    }
 
}

void GameWindow::deleteFireballs()
{
  //remove fireball not in view
  for(std::vector<Fireball*>::iterator it = rockets.begin(); it != rockets.end(); ++it) {
    if(!(*it)->inField(viw_x, viw_y, viw_w, viw_h))
    {
      delete (*it);  //Speicher freigeben
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
  
void GameWindow::collisionEnemies()
{
 for(std::vector<Fireball*>::iterator it = rockets.begin(); it != rockets.end(); ++it) {
    
   bool hit = false;
   
    for(std::vector<Enemie*>::iterator en = enemies.begin(); en != enemies.end(); ++en) {
      if((*en)->collisionP((*it)->getX(), (*it)->getY()))
	{
	  hit = true;
	  (*en)->hit();
	  //std::cout << "Delete enemie" << std::endl;
	  break;
	}
    }
    
    if(hit)
      {
	  delete (*it);  //Speicher freigeben
	  rockets.erase(it);
	  //std::cout << "Delete fireball" << std::endl;
	  it--;
      }
    
  }
 
 
}

void GameWindow::collisionShip()
{
   
    for(std::vector<Enemie*>::iterator en = enemies.begin(); en != enemies.end(); ++en) {
      if((*en)->overlaps(player.getX(), player.getY(), player.getW(), player.getH()))
	{
	  //Todo: Ship explode
	  running = false;
	  break;
	}
    }
 
 
}

  

//################################################################################
// Main
//################################################################################




int main(int argc, const char** argv)
{
  std::srand(std::time(0));
  GameWindow window;
  window.show();
  return 0;
}
