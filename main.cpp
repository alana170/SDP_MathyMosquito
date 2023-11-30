#include <FEHLCD.h>
#include "FEHUtility.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "FEHRandom.h"
#include <string>
#include "LCDColors.h"
#include "FEHImages.h"
using namespace std;

void menu();
void MenuButton();
void PlayGame();
void ViewInstructions();
void ViewCredits();
void ViewStats();
void Quit();
void collision(points);
void flyswatter(points);
void math(points);
void chooselevel();
void flyswattermult();
void collisionmult();
void mathmult();
void title();

class points
{
private:
  int high_score = 0;

public:
  int score_now = 0;
  points();
  void coincollect();
  void updateHighScore();
};

points::points()
{
  score_now = 0;
}

int main(void)
{
  LCD.SetBackgroundColor(WHITE);
  LCD.Clear();
  LCD.Clear();
  title();
  while (1)
  {
    LCD.Update();
  }
  return 0;
}

//displays the title page
void title(){
  FEHImage bkg;
  bkg.Open("mathymosquitoFEH.pic");
  bkg.Draw(0,0);
  bkg.Close();
  int x, y; 
  if((LCD.Touch(&x, &y))){
    menu();
  }
}

// function for flyswatter opening
void flyswatter(points p)
{
  LCD.SetBackgroundColor(WHITE);
  LCD.Clear();
  LCD.ClearBuffer();
  // Declares an image for flyswatter
  FEHImage flyswatter;
  // Open the image
  flyswatter.Open("flysFEH.pic");
  // Draw a image in the top left corner
  flyswatter.Draw(0, 140);
  int xf = 320;
  int yf = 140;

  // Declares and opens token image
  FEHImage token;
  token.Open("tokenFEH.pic");
  int yToken = 120;
  int xToken = 320;
  // create another flyswatter upside down
  FEHImage udflyswatter;
  udflyswatter.Open("udfFEH.pic");
  udflyswatter.Draw(90, 10);
  // create ints for the movement across the screen
  int xudf = 90;
  int yudf = 10;
  // have the flyswatter move across the screen

  // loop

  float x, y;
  int x1 = 150, y1 = 80;
  int r = 10;
  // Draw mosquito
  FEHImage mosquito;
  mosquito.Open("mosquitocharFEH.pic");
  mosquito.Draw(x1, y1);
  LCD.Update();
  // while (y1<= 220){
  while ((x1 > 0))
  {
    if (xf < 0)
    {
      xf = 320;
    }
    if (xudf < 0)
    {
      xudf = 320;
    }
    LCD.SetFontColor(WHITE);
    LCD.FillCircle(x1 + 5, y1 + 5, 2 * r);
    LCD.Update();
    // Change y coordinate
    y1 += 5;

    // Draw new jumper
    mosquito.Draw(x1, y1);
    LCD.Update();
    Sleep(.1);
    // for (y1= 80; y1<=220; y1+=5) {
    // gravity();
    while ((!LCD.Touch(&x, &y)))
    {
      LCD.SetFontColor(WHITE);
      LCD.FillCircle(x1 + 5, y1 + 5, 2 * r);
      LCD.Update();
      // Change y coordinate
      y1 += 10;

      // Draw new jumper
      mosquito.Draw(x1, y1);
      LCD.Update();
      Sleep(.1);
      // normal flyswatter
      LCD.SetFontColor(WHITE);
      LCD.DrawRectangle(xf, yf, 90, 100);
      LCD.FillRectangle(xf, yf, 90, 100);
      LCD.Update();
      // update the location
      xf = xf - 10;
      LCD.Update();

      // draws token
      token.Draw(xf, yToken);
      LCD.Update();

      // Draw Racer 1
      flyswatter.Draw(xf, yf);
      LCD.Update();
      // upside down flyswatter
      LCD.SetFontColor(WHITE);
      LCD.DrawRectangle(xudf, yudf, 50, 50);
      LCD.FillRectangle(xudf, yudf, 50, 50);
      LCD.DrawRectangle(xf, yToken, 20, 20);
      LCD.FillRectangle(xf, yToken, 20, 20);
      LCD.Update();
      // update the location
      xudf = xudf - 10;
      LCD.Update();
      // Draw Racer 1
      udflyswatter.Draw(xudf, yudf);
      LCD.Update();
      if (xf < 0)
      {
        xf = 320;
      }
      if (xudf < 0)
      {
        xudf = 320;
      }
      Sleep(0.1);

      // if you collide with a token within 7 pixels of your position
      if (abs(xToken - xf) < 7 && abs(yToken - yf) < 7)
      {
        p.score_now++;
      }
      // hits bottom flyswatter
      if (((100 <= xf) && (200 >= xf) && (y1 > 140)))
      {
        // make the screen red
        collision(p);
      }
      // hits top flyswatter
      if ((100 <= xudf) && (180 >= xudf) && ((y1 < 60)))
      {
        collision(p);
      }
    }
    // Touch - use x and y
    // Jump into the air
    // Clear previous jumper
    LCD.SetFontColor(WHITE);
    LCD.DrawCircle(x1 + 5, y1 + 5, 2 * r);
    LCD.FillCircle(x1 + 5, y1 + 5, 2 * r);
    LCD.Update();
    // Change y coordinate
    y1 -= 40;
    if (xf < 0)
    {
      xf = 320;

      // Draw new jumper
      mosquito.Draw(x1, y1);
      Sleep(.1);

      // clear previous jumper
      LCD.SetFontColor(WHITE);
      LCD.DrawCircle(x1 + 5, y1 + 5, 2 * r);
      LCD.FillCircle(x1 + 5, y1 + 5, 2 * r);
      LCD.Update();

      // Change y coordinate
      y1 += 10;

      // Draw new jumper
      mosquito.Draw(x1, y1);
      Sleep(.1);
      LCD.SetFontColor(WHITE);
      LCD.DrawRectangle(xf, yf, 100, 100);
      LCD.FillRectangle(xf, yf, 100, 100);
      LCD.Update();
      // update the location
      xf = xf - 10;
      if (xf < 0)
      {
        xf = 320;
      }
      if (xudf < 0)
      {
        xudf = 320;
      }
      LCD.Update();
      // Draw Racer 1
      flyswatter.Draw(xf, yf);
      LCD.Update();
      token.Draw(xf, yf);
      LCD.Update();
      // upside down flyswatter
      LCD.SetFontColor(WHITE);
      LCD.DrawRectangle(xudf, yudf, 50, 50);
      LCD.FillRectangle(xudf, yudf, 50, 50);
      LCD.DrawRectangle(xf, yToken, 20, 30);
      LCD.Update();
      // update the location
      xudf = xudf - 10;
      LCD.Update();
      // Draw Racer 1
      udflyswatter.Draw(xudf, yudf);
      LCD.Update();
      Sleep(0.1);
    }
    if (((100 <= xf) && (200 >= xf) && (y1 > 140)))
    {
      collision(p);
    }
    if ((100 <= xudf) && (180 >= xudf) && ((y1 < 60)))
    {
      collision(p);
    }
  }
  flyswatter.Close();
  mosquito.Close();
  token.Close();
  // menu button
  float x_pos, y_pos, x_trash, y_trash;
  LCD.SetFontColor(BLACK);
  LCD.WriteAt("Menu", 260, 15);
  while (true)
  {
    LCD.ClearBuffer();
    while (!LCD.Touch(&x_pos, &y_pos))
    {
    };
    while (LCD.Touch(&x_trash, &y_trash))
    {
    };
    if (x_pos > 260 && y_pos < 30)
    {
      menu();
      break;
    }
  }
}

void math(points p)
{
  // math equation
  LCD.SetFontColor(RED);
  LCD.DrawRectangle(50, 50, 320, 240);
  LCD.FillRectangle(50, 50, 320, 240);
  LCD.Update();
  LCD.SetFontColor(BLACK);
  LCD.Update();
  // create a random integer between 1 and 100
  //  set seed to time(0)
  srand(time(0));
  int a = rand() % 100 + 1;
  int b = rand() % 100 + 1;
  // generate the math problem
  LCD.WriteAt(a, 0, 10);
  LCD.WriteAt("+", 35, 10);
  LCD.WriteAt(b, 70, 10);
  LCD.Update();
  int c = a + b;
  // create multiple choice answers
  int f = rand() % 200 + 1;
  int d = rand() % 200 + 1;
  int e = rand() % 200 + 1;
  // create a random place for the variables to be printed
  // create a vector for placement
  int vect[] = {70, 110, 150, 190};
  int fspot = rand() % 4;
  int dspot = rand() % 4;
  // make sure theyre not in the same place
  while (dspot == fspot)
  {
    dspot = rand() % 4;
  }

  int espot = rand() % 4;
  // make sure theyre not in the same place
  while ((espot == fspot) || (espot == dspot))
  {
    espot = rand() % 4;
  }
  // for c
  int cspot = rand() % 4;
  // make sure theyre not in the same place
  while ((cspot == fspot) || (cspot == espot) || (cspot == dspot))
  {
    cspot = rand() % 4;
  }
  // spot on y
  // place them
  LCD.WriteAt(f, 100, vect[fspot]);
  LCD.WriteAt(d, 100, vect[dspot]);
  LCD.WriteAt(c, 100, vect[cspot]);
  LCD.WriteAt(e, 100, vect[espot]);
  // check for click
  LCD.Update();
  int x_pos, y_pos, x, y;

  LCD.ClearBuffer();
  while (!LCD.Touch(&x_pos, &y_pos))
  {
  };
  while (LCD.Touch(&x_pos, &y_pos))
  {
  };
  if ((y_pos < (vect[cspot] + 19)) && (y_pos > (vect[cspot] - 19)) && (x_pos > 100) && (x_pos < 240))
  {
    // go back to original function
    LCD.SetBackgroundColor(LIGHTGREEN);
    LCD.WriteAt("Correct!", 175, 50);
    Sleep(1000);
    LCD.Update();
    Sleep(2000);
    LCD.SetBackgroundColor(WHITE);
    LCD.Clear();
    LCD.ClearBuffer();
    LCD.Update();
    flyswatter(p);
  }

  else
  {
    LCD.Clear(RED);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("GAME OVER.", 100, 50);
    LCD.WriteAt("Score: ", 100, 150);
    LCD.WriteAt(p.score_now, 125, 150);
    LCD.Update();
    Sleep(4000);
    menu();
  }
}

/*
  The mosquito jumps in the air
*/
void menu()
{
  float x_pos, y_pos, x_trash, y_trash;
  LCD.Clear(WHITE);
  LCD.SetFontColor(SKYBLUE);
  LCD.DrawRectangle(80, 20, 200, 210);
  LCD.FillRectangle(80, 20, 200, 210);
  // displaying the text for the menu
  LCD.SetFontColor(WHITE);
  LCD.WriteAt("Play Game", 100, 40);
  LCD.WriteAt("Instructions", 100, 80);
  LCD.WriteAt("Statistics", 100, 120);
  LCD.WriteAt("Credits", 100, 160);
  LCD.WriteAt("Quit", 100, 200);
  LCD.Update();
  while (true)
  {
    LCD.ClearBuffer();
    while (!LCD.Touch(&x_pos, &y_pos))
    {
    };
    while (LCD.Touch(&x_trash, &y_trash))
    {
    };
    if (y_pos < 80 && y_pos > 35 && x_pos > 100 && x_pos < 240)
    {
      // play game
      PlayGame();
      break;
    }
    else if (y_pos < 120 && y_pos > 75 && x_pos > 100 && x_pos < 240)
    {
      // view instructions
      ViewInstructions();
      break;
    }
    else if (y_pos < 160 && y_pos > 115 && x_pos > 100 && x_pos < 240)
    {
      // view stats
      ViewStats();
      break;
    }
    else if (y_pos < 200 && y_pos > 155 && x_pos > 100 && x_pos < 240)
    {
      // view credits
      ViewCredits();
      break;
    }
    else if (y_pos < 230 && y_pos > 195 && x_pos > 100 && x_pos < 240)
    {
      // quit
      Quit();
      break;
    }
  }
}

void PlayGame()
{
  LCD.Clear();
  LCD.Clear(LIGHTSEAGREEN);
  LCD.Update();
  chooselevel();
}

void MenuButton()
{
  float x_pos, y_pos, x_trash, y_trash;
  LCD.SetFontColor(BLACK);
  LCD.WriteAt("Menu", 260, 15);
  while (true)
  {
    LCD.ClearBuffer();
    while (!LCD.Touch(&x_pos, &y_pos))
    {
    };
    while (LCD.Touch(&x_trash, &y_trash))
    {
    };
    if (x_pos > 260 && y_pos < 30)
    {
      menu();
      break;
    }
  }
}

void ViewInstructions()
{
  LCD.Clear(LIGHTSEAGREEN);
  LCD.WriteRC("How to Play:", 2, 1);
  LCD.WriteRC("Click anywhere to jump.", 4, 1);
  LCD.WriteRC("Avoid the fly swatters.", 5, 1);
  LCD.WriteRC("If you hit them, answer a", 6, 1);
  LCD.WriteRC("math question correctly", 7, 1);
  LCD.WriteRC("to continue playing.", 8, 1);
  LCD.WriteRC("Collect the red tokens", 9, 1);
  LCD.WriteRC("to earn points.", 10, 1);
  LCD.WriteRC("Your goal is to earn as", 11, 1);
  LCD.WriteRC("many points as possible.", 12, 1);
  MenuButton();
}

void ViewCredits()
{
  LCD.Clear(LIGHTSEAGREEN);
  LCD.SetFontColor(WHITE);
  LCD.WriteRC("Developer Credits", 3, 1);
  LCD.WriteRC("Alana Gorukanti", 4, 1);
  LCD.WriteRC("Kathleen Schmidt", 5, 1);
  LCD.WriteRC("Instructor: Dr. Toney", 7, 1);
  LCD.WriteRC("November 2023", 10, 1);
  MenuButton();
}

void ViewStats()
{
  LCD.Clear(LIGHTSEAGREEN);
  LCD.WriteRC("High Score: ", 3, 1);
  MenuButton();
}

void Quit()
{
  LCD.Clear(SKYBLUE);
  LCD.SetFontColor(GRAY);
  LCD.DrawRectangle(60, 50, 190, 120);
  LCD.FillRectangle(60, 50, 190, 120);
  LCD.SetFontColor(GREEN);
  LCD.DrawRectangle(100, 140, 40, 25);
  LCD.FillRectangle(100, 140, 40, 25);
  LCD.SetFontColor(RED);
  LCD.DrawRectangle(175, 140, 30, 25);
  LCD.FillRectangle(175, 140, 30, 25);
  LCD.SetFontColor(WHITE);
  LCD.WriteAt("Are you sure ", 80, 60);
  LCD.WriteAt("you want to ", 80, 85);
  LCD.WriteAt("quit?", 125, 115);
  LCD.WriteAt("Yes", 102, 145);
  LCD.WriteAt("No", 177, 145);
  float x_pos, y_pos, x_trash, y_trash;
  while (true)
  {
    LCD.ClearBuffer();
    while (!LCD.Touch(&x_pos, &y_pos))
    {
    };
    while (LCD.Touch(&x_trash, &y_trash))
    {
    };
    if (x_pos > 100 && x_pos < 140 && y_pos > 140 && y_pos < 165)
    {
      exit(0);
    }
    else
    {
      menu();
      break;
    }
  }
}

void chooselevel()
{
  Sleep(2);
  int x_pos, y_pos, x_trash, y_trash;
  LCD.ClearBuffer();
  LCD.SetFontColor(BLACK);
  LCD.WriteAt("Easy (ADDITION)", 20, 40);
  LCD.WriteAt("Hard (MULTIPLICATION)", 20, 120);
  LCD.Update();
  while (!LCD.Touch(&x_pos, &y_pos))
  {
  };
  while (LCD.Touch(&x_trash, &y_trash))
  {
  };
  if (y_pos < 80 && y_pos > 30 && x_pos > 100 && x_pos < 240)
  {
    // play easier game
    points newpoints;
    flyswatter(newpoints);
  }

  else
  {
    // do the harder level
    flyswattermult();
  }
}

// harder level functions
// function for flyswatter opening
void flyswattermult()
{
  LCD.SetBackgroundColor(WHITE);
  LCD.Clear();
  // Declares an image for flyswatter
  FEHImage flyswatter;
  // Open the image
  flyswatter.Open("flysFEH.pic");
  // Draw a image in the top left corner
  flyswatter.Draw(0, 140);
  int xf = 320;
  int yf = 140;
  // create another flyswatter upside down
  FEHImage udflyswatter;
  udflyswatter.Open("udfFEH.pic");
  udflyswatter.Draw(90, 10);
  // create ints for the movement across the screen
  int xudf = 90;
  int yudf = 10;
  // have the flyswatter move across the screen

  // loop

  float x, y;
  int x1 = 150, y1 = 80;
  int r = 10;
  // Draw jumper
  FEHImage mosquito;
  mosquito.Open("mosquitocharFEH.pic");
  mosquito.Draw(x1, y1);
  LCD.Update();
  // while (y1<= 220){
  while (((100 >= xf) || (200 <= xf)) || ((y1 < 140) && (y1 > 60)))
  {
    if (xf < 0)
    {
      xf = 320;
    }
    LCD.SetFontColor(WHITE);
    LCD.FillCircle(x1 + 5, y1 + 5, 2 * r);
    LCD.Update();
    // Change y coordinate
    y1 += 5;

    // Draw new jumper
    mosquito.Draw(x1, y1);
    LCD.Update();
    Sleep(.1);
    // for (y1= 80; y1<=220; y1+=5) {
    // gravity();
    while ((!LCD.Touch(&x, &y)))
    {
      LCD.SetFontColor(WHITE);
      LCD.FillCircle(x1 + 5, y1 + 5, 2 * r);
      LCD.Update();
      // Change y coordinate
      y1 += 10;

      // Draw new jumper
      mosquito.Draw(x1, y1);
      LCD.Update();
      Sleep(.1);
      // normal flyswatter
      LCD.SetFontColor(WHITE);
      LCD.DrawRectangle(xf, yf, 100, 100);
      LCD.FillRectangle(xf, yf, 100, 100);
      LCD.Update();
      // update the location
      xf = xf - 10;
      LCD.Update();
      // Draw Racer 1
      flyswatter.Draw(xf, yf);
      LCD.Update();
      // upside down flyswatter
      LCD.SetFontColor(WHITE);
      LCD.DrawRectangle(xudf, yudf, 50, 50);
      LCD.FillRectangle(xudf, yudf, 50, 50);
      LCD.Update();
      // update the location
      xudf = xudf - 10;
      LCD.Update();
      // Draw Racer 1
      udflyswatter.Draw(xudf, yudf);
      LCD.Update();
      // create a new xf so the statements can read the position
      if (xf < 0)
      {
        xf = 320;
      }
      Sleep(0.1);
      // if the fly hits the flyswatter
      if (((100 <= xf) && (200 >= xf) && (y1 > 140)) || ((100 <= xudf) && (220 >= xudf) && (y1 < 60)))
      {
        // make the screen red
        collisionmult();
      }
    }
    // Touch - use x and y
    // Jump into the air
    // Clear previous jumper
    if (((100 >= xf) || (200 <= xf)) || ((y1 < 140) && (y1 > 60)))
    {
      LCD.SetFontColor(WHITE);
      LCD.DrawCircle(x1 + 5, y1 + 5, 2 * r);
      LCD.FillCircle(x1 + 5, y1 + 5, 2 * r);
      LCD.Update();
      // Change y coordinate
      y1 -= 40;
      if (xf < 0)
      {
        xf = 320;
      }
      // Draw new jumper
      mosquito.Draw(x1, y1);
      LCD.Update();
      Sleep(.1);

      // clear previous jumber
      LCD.SetFontColor(WHITE);
      LCD.DrawCircle(x1 + 5, y1 + 5, 2 * r);
      LCD.FillCircle(x1 + 5, y1 + 5, 2 * r);
      LCD.Update();
      // Change y coordinate
      y1 += 10;

      // Draw new jumper
      mosquito.Draw(x1, y1);
      LCD.Update();
      Sleep(.1);
      LCD.SetFontColor(WHITE);

      LCD.DrawRectangle(xf, yf, 100, 100);
      LCD.FillRectangle(xf, yf, 100, 100);
      LCD.Update();
      // update the location
      xf = xf - 10;
      if (xf < 0)
      {
        xf = 320;
      }
      LCD.Update();
      // Draw Racer 1
      flyswatter.Draw(xf, yf);
      LCD.Update();
      // upside down flyswatter
      LCD.SetFontColor(WHITE);
      LCD.DrawRectangle(xudf, yudf, 50, 50);
      LCD.FillRectangle(xudf, yudf, 50, 50);
      LCD.Update();
      // update the location
      xudf = xudf - 10;
      LCD.Update();
      // Draw Racer 1
      udflyswatter.Draw(xudf, yudf);
      LCD.Update();
      Sleep(0.1);
    }
    if (((100 <= xf) && (200 >= xf) && (y1 > 140)) || ((100 <= xudf) && (200 >= xudf) && (y1 < 70)))
    {
      collisionmult();
    }
  }
  flyswatter.Close();
}

// collision function for addition
void collision(points p)
{
  LCD.Clear();
  LCD.SetFontColor(RED);
  LCD.DrawRectangle(50, 50, 320, 240);
  LCD.FillRectangle(50, 50, 320, 240);
  LCD.Update();
  // print to screen
  LCD.SetFontColor(BLACK);
  LCD.WriteRC("YOU HIT THE FLY SWATTER.", 2, 1);
  LCD.WriteRC("COMPLETE THE MATH PROBLEM", 4, 1);
  LCD.WriteRC("TO STAY ALIVE\n", 6, 1);
  LCD.Update();
  Sleep(3000);
  math(p);
}

// collision function
void collisionmult()
{
  LCD.Clear();
  LCD.SetFontColor(RED);
  LCD.DrawRectangle(50, 50, 320, 240);
  LCD.FillRectangle(50, 50, 320, 240);
  LCD.Update();
  // print to screen
  LCD.SetFontColor(BLACK);
  LCD.WriteRC("YOU HIT THE FLY SWATTER.", 2, 1);
  LCD.WriteRC("COMPLETE THE MATH PROBLEM", 4, 1);
  LCD.WriteRC("TO STAY ALIVE\n", 6, 1);
  LCD.Update();
  Sleep(3000);
  mathmult();
}

void mathmult()
{
  // math equation
  LCD.SetFontColor(RED);
  LCD.DrawRectangle(50, 50, 320, 240);
  LCD.FillRectangle(50, 50, 320, 240);
  LCD.Update();
  LCD.SetFontColor(BLACK);
  LCD.Update();
  // create a random integer between 1 and 100
  //  set seed to time(0)
  srand(time(0));
  int a = rand() % 100 + 1;
  int b = rand() % 100 + 1;
  // generate the math problem
  LCD.WriteAt(a, 0, 10);
  LCD.WriteAt("*", 35, 10);
  LCD.WriteAt(b, 70, 10);
  LCD.Update();
  int c = a * b;
  // create multiple choice answers
  int f = rand() % 2000 + 1;
  int d = rand() % 2000 + 1;
  int e = rand() % 2000 + 1;
  // create a random place for the variables to be printed
  // create a vector for placement
  int vect[] = {70, 110, 150, 190};
  int fspot = rand() % 4;
  int dspot = rand() % 4;
  // make sure theyre not in the same place
  while (dspot == fspot)
  {
    dspot = rand() % 4;
  }

  int espot = rand() % 4;
  // make sure theyre not in the same place
  while ((espot == fspot) || (espot == dspot))
  {
    espot = rand() % 4;
  }
  // for c
  int cspot = rand() % 4;
  // make sure theyre not in the same place
  while ((cspot == fspot) || (cspot == espot) || (cspot == dspot))
  {
    cspot = rand() % 4;
  }
  // spot on y
  // place them
  LCD.WriteAt(f, 100, vect[fspot]);
  LCD.WriteAt(d, 100, vect[dspot]);
  LCD.WriteAt(c, 100, vect[cspot]);
  LCD.WriteAt(e, 100, vect[espot]);
  // check for click
  LCD.Update();
  int x_pos, y_pos, x, y;

  LCD.ClearBuffer();
  while (!LCD.Touch(&x_pos, &y_pos))
  {
  };
  while (LCD.Touch(&x_pos, &y_pos))
  {
  };
  if ((y_pos < (vect[cspot] + 19)) && (y_pos > (vect[cspot] - 19)) && (x_pos > 100) && (x_pos < 240))
  {
    // go back to original function
    LCD.SetBackgroundColor(GREEN);
    LCD.Write("Correct!");
    LCD.Update();
    Sleep(1000);
    LCD.SetBackgroundColor(WHITE);
    LCD.Clear();
    LCD.ClearBuffer();
    LCD.Update();
    flyswattermult();
  }

  else
  {
    LCD.Clear(RED);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("GAME OVER.", 100, 50);
    LCD.WriteAt("Score: ", 100, 150);
    // LCD.WriteAt(p.score_now, 125, 150);
    LCD.Update();
    Sleep(4000);
    menu();
  }
}

// check if token is collected
void points::coincollect(){
    // logic
    // if the y position of the
};

// update high scores
void points::updateHighScore()
{
  if (score_now > high_score)
  {
    high_score = score_now;
  }
};