/************************************************/
/* Name: Alana Gorukanti and Kathleen Schmidt   */
/* Date: 12/06/23                               */
/* Seat: 11,12                                  */
/* Assignment: SDP                              */
/* Instructor: Toney 10:20                      */
/************************************************/

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
//functions used
void menu();
void MenuButton();
void PlayGame();
void ViewInstructions();
void ViewCredits();
void Quit();
void collision();
void flyswatter();
void math();
void chooselevel();
void flyswattermult();
void collisionmult();
void mathmult();
int coincollect();
void ViewStats();
void title();

//global variable
int score_now; 
//class for point collection
class points{
  public:
    points();
    int high_score=0;

};
//constructor
points::points(){
    high_score;
}


//function that displays the title page
void title(){
  Sleep(2);
  FEHImage bkg;
  bkg.Open("mathymosquitoFEH.pic");
  bkg.Draw(0,0);
  bkg.Close();
  int x, y, trashx, trashy; 
  while(LCD.Touch(&x, &y)){};
  while(!LCD.Touch(&trashx, &trashy)){};
  if((LCD.Touch(&x, &y))){
    menu();
    Sleep(0.5);
  }
}

 //function for flyswatter opening
void flyswatter(){
  
    LCD.SetBackgroundColor(WHITE);
    LCD.Clear();
   LCD.ClearBuffer();
        // Declares an image for flyswatter
    FEHImage flyswatter;
    // Open the image
    flyswatter.Open("flysFEH.pic");
    // Draw a image in the top left corner
    flyswatter.Draw(0, 140);
    //x and y position of the flyswatter
    int xf=320;
    int yf=140;
    //create another flyswatter upside down
    FEHImage udflyswatter;
    udflyswatter.Open("udfFEH.pic");
    udflyswatter.Draw(90, 10);
    //create ints for the movement of the upside down across the screen
    int xudf=90;
    int yudf=10;
    //have the flyswatter move across the screen
  //create an image for the token
  FEHImage token;
    token.Open("tokenFEH.pic");
    //x and y positions of the tokens
    int yToken = 120;
    int xToken = 320;
 
  //x and y trash variables for click
    float x, y;
  // x and y coordinates for the mosquito
    int x1 = 150, y1 = 80;
  //radius of circle for clearing the previous image purposes
    int r = 10;
    // Draw mosquito
    FEHImage mosquito;
    mosquito.Open("mosquitocharFEH.pic");
    mosquito.Draw(x1, y1);
    LCD.Update();
    int disappear=0; //the token should not dissapear if =0
  while (true){
  // so the flyswatter positions don't go negative for comparison purposes
      if (xf < 0){
        xf=320;
      }
      if (xudf < 0){
        xudf=320;
      }
 
    //menu button
    float x_pos, y_pos, x_trash, y_trash;
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Menu", 260, 15);

    LCD.ClearBuffer();
    while(LCD.Touch(&x_pos, &y_pos)){};
    if(x_pos > 260 && y_pos < 30){
          menu();
    }
 
    // Change y coordinate
    y1 += 5;
  
    // Draw new jumper
    mosquito.Draw(x1, y1);
    LCD.Update();
    Sleep(.01);
    int disappear;
    //only redraw the token if it hasnt been through the whole screen
    if (xToken<=4){
      //create a variable that keeps track if the token has been hit or not
      //reset it every time through this loop
      disappear=0; //the token should not dissapear if =0
      //clear old tokens
      LCD.Clear(WHITE);
      //re-draw menu button first
      LCD.SetFontColor(BLACK);
      LCD.WriteAt("Menu", 260, 15);
      LCD.Update();
      //re-draw everything else to make the transition look smooth
      flyswatter.Draw(xf, yf);
      udflyswatter.Draw(xudf, yudf);
      LCD.Update();
      //create new token
      //seed of time(NULL) to make it more random
      srand(time(NULL));
      //random y position for token
      yToken = 70 + (rand() %60);
      //x position always starts out at beginning
      xToken=320;
      token.Draw(300, yToken); 
      LCD.Update();   
      Sleep(0.1);
    }  
    //gravity if not touched
    while ((!LCD.Touch(&x, &y))){
    //clears the old mosquito
        LCD.SetFontColor(WHITE);
        LCD.FillRectangle(x1, y1-10, 20, 40);
        LCD.Update();
        // Change y coordinate
        y1 += 10;
        //create movement for the token; clears old token
        LCD.SetFontColor(WHITE);
        LCD.FillCircle(xToken, yToken+5, r);
        LCD.Update();
        // Draw new jumper
        mosquito.Draw(x1, y1);
        LCD.Update();
        //normal flyswatter clear the old one
         LCD.SetFontColor(WHITE);
        LCD.DrawRectangle(xf, yf, 90, 100);
        LCD.FillRectangle(xf, yf, 90, 100);
        LCD.Update();
        //update the location
        xf=xf-10;
        LCD.Update();
        // Draw flyswatter
       flyswatter.Draw(xf, yf);
        LCD.Update();
        //upside down flyswatter delete the old one
        LCD.SetFontColor(WHITE);
        LCD.DrawRectangle(xudf, yudf, 50, 70);
        LCD.FillRectangle(xudf, yudf, 50, 70);
        LCD.Update();
        //menu button in top corner 
        LCD.SetFontColor(BLACK);
        LCD.WriteAt("Menu", 260, 15);
        LCD.Update();
        //update the location of the upside-down flyswatter
        xudf=xudf-10;
        LCD.Update();
        // Draw flyswatter and token
        //clear old token
        LCD.SetFontColor(WHITE);
        LCD.FillCircle(xToken, yToken+5, r);
        LCD.Update();
        //draw new token and flyswatter
        xToken=xToken-10;
        if (disappear==0){
          token.Draw(xToken, yToken); 
          LCD.Update();
          Sleep(0.1);
        }
        udflyswatter.Draw(xudf, yudf);
        LCD.Update();
        //if statements so that if the mosquito hits the fly swatter, it dies
        //so xf and xudf (position of flyswatter and upside down flyswatter) dont go negative
        if (xf < 0){
          xf=320;
        }
        if (xudf < 0){
         xudf=320;
        }
        Sleep(0.1);
        //if collides with flyswatter
        if (((100<=xf)&&(200>=xf)&&(y1>140))){
          Sleep(0.1);
          //pass to collision function
          collision(); 
        }
        if ((100<=xudf)&&(180>=xudf)&&((y1<50))){
          Sleep(0.1);
          collision();
        }
         //function for collsion with token
        if ((yToken>=y1-20)&&(yToken<=y1+20)&&(xToken>=x1-20)&&(xToken<=x1+20)&&(disappear ==0)){
          //have a little bit of a buffer
          //set the disappear = 1 because it has already collided
          disappear=1;
          //go to coin collect function
          coincollect();
        }
      }
      // Touch - use x and y
      // Jump into the air
     // Clear previous mosqito
      LCD.SetFontColor(WHITE);
      LCD.FillRectangle(x1, y1-10, 20, 40);
      LCD.Update();
      //clear previous token
      LCD.SetFontColor(WHITE);
      LCD.FillCircle(xToken+5, yToken+5, r);
      LCD.Update();
      // Change y coordinate of the mosquito
      y1 -= 40;
      if (xf < 0){
        xf=320;
      }
      // Draw new mosqito
      mosquito.Draw(x1, y1);
      LCD.Update();
      //clear previous mosqito
      LCD.SetFontColor(WHITE);
      LCD.FillRectangle(x1, y1-10, 20, 40);
      LCD.Update();
      // Change y coordinate
      y1 += 10;
      // Draw new mosqito
      mosquito.Draw(x1, y1);
      //clear old flyswatter
      LCD.SetFontColor(WHITE);
      LCD.DrawRectangle(xf, yf, 100, 100);
      LCD.FillRectangle(xf, yf, 100, 100);
      LCD.Update();
      //update the location of the flyswatter and token
      xf=xf-10;
      xToken=xToken-10;
      // so the locations don't go negative for comparison purposes
      if (xf < 0){
        xf=320;
      }
      if (xudf < 0){
        xudf=320;
      }
      xudf=xudf-10;
      LCD.Update();
      // Draw flyswatters and tokens
      flyswatter.Draw(xf, yf);
      udflyswatter.Draw(xudf, yudf);
      if (disappear==0){//draw token only if it has not been collided with yet
        token.Draw(xToken, yToken); 
        LCD.Update();
        Sleep(0.1);
      }
      LCD.Update();
      //upside down flyswatter reset
      LCD.SetFontColor(WHITE);
      LCD.DrawRectangle(xudf, yudf, 70, 70);
      LCD.FillRectangle(xudf, yudf, 70, 70);
      //menu button re-draw
      LCD.SetFontColor(BLACK);
      LCD.WriteAt("Menu", 260, 15);
      LCD.ClearBuffer();
      //if menu button is clicked, go to the menu
      if(x > 260 && y < 30){
        menu();
      }
      LCD.Update();
      //update the location of upside-down flyswatter
      xudf=xudf-10;
      udflyswatter.Draw(xudf, yudf);
      LCD.Update();
      Sleep(0.01);
      //if collides with bottom flyswatter   
      if (((100<=xf)&&(200>=xf)&&(y1>140))){
        collision();  
      }
      //if collides with top flyswatter
      if ((100<=xudf)&&(180>=xudf)&&((y1<50))){
        collision();
      }
      //function for collsion with token
      if ((yToken>=y1-7)&&(yToken<=y1+7)&&(xToken>=x1-20)&&(xToken<=x1+20)&&(disappear == 0)){
        //have a little bit of a buffer
        //set the disappear = 1 because it has already collided
        disappear=1;
        //go to coin collect function
        coincollect();
      }
    }
    //close all of the images
    flyswatter.Close();
    mosquito.Close();
    udflyswatter.Close();
    token.Close();
}// end of the function

//collision function
void collision (){
  LCD.Clear();
  //make the background red
  LCD.SetFontColor(RED);
  LCD.DrawRectangle(50, 50, 320, 240);
  LCD.FillRectangle(50, 50, 320, 240);
  LCD.Update();
  //print to screen
  LCD.SetFontColor(BLACK);
  LCD.WriteRC("YOU HIT THE FLY SWATTER.", 2, 1);
  LCD.WriteRC("COMPLETE THE MATH PROBLEM", 4, 1);
  LCD.WriteRC("TO STAY ALIVE\n", 6, 1);
  LCD.Update();
  Sleep(1000);
  //menu button
  LCD.SetFontColor(BLACK);
  //menu button
  float x_pos, y_pos, x_trash, y_trash;
  LCD.SetFontColor(BLACK);
  //write menu in the corner
  LCD.WriteAt("Menu", 260, 15);   
  LCD.ClearBuffer();
  LCD.Update();
  Sleep(1000);
  while(LCD.Touch(&x_pos, &y_pos)){};
  if(x_pos > 260 && y_pos < 30)
  {//go to the menu if the menu button is clicked

    menu();
  }
  else //pass it into the math function
  {
    math();
  }
}//end of collision function


void math () {
  //math equation
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(50, 50, 320, 240);
    LCD.FillRectangle(50, 50, 320, 240);
    LCD.Update();
    LCD.SetFontColor(BLACK);
    LCD.Update();
    //create a random integer between 1 and 100
    // set seed to time(0)
    srand(time(0));
    int a = rand() % 100 + 1;
    int b =  rand() % 100 + 1;
    //menu button (if clicked anywhere on the page else than the right answer it goes to game over)
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Menu", 260, 15);
    //generate the math problem
    LCD.WriteAt(a, 0, 10);
    LCD.WriteAt("+", 35, 10);
    LCD.WriteAt(b, 70, 10);
    LCD.Update();
    int c = a + b;
    //create multiple choice answers
    int f = rand() % 200 + 1;
    int d= rand() % 200 + 1;
    int e =  rand() % 200 + 1;
    //create a random place for the variables to be printed
      //create a vector for placement
    int vect [] = {70, 110, 150, 190};
    int fspot = rand() %4;
    int dspot = rand() %4;
    //make sure theyre not in the same place
    while (dspot == fspot){
       dspot = rand() %4;
    }
    int espot = rand() %4;
    //make sure theyre not in the same place
    while ((espot == fspot)||(espot == dspot)){
       espot = rand() %4;
    }
    //for c
    int cspot = rand() %4;
    //make sure theyre not in the same place
    while ((cspot == fspot)||(cspot == espot) || (cspot == dspot)){
       cspot = rand() %4;
    }
    //spot on y
    //place them
    LCD.WriteAt(f,100,vect[fspot]);
    LCD.WriteAt(d,100,vect[dspot]);
    LCD.WriteAt(c,100,vect[cspot]);
    LCD.WriteAt(e,100,vect[espot]);
    LCD.Update();
    int x_pos, y_pos, x, y;
    LCD.ClearBuffer();
    while(!LCD.Touch(&x_pos, &y_pos)){};
    while(LCD.Touch(&x_pos, &y_pos)){};
    if((y_pos < (vect[cspot]+19)) && (y_pos > (vect[cspot]-19))&&(x_pos > 100) && (x_pos < 240)){
       // go back to original function
      LCD.SetBackgroundColor(GREEN);
      LCD.WriteAt("Correct!", 0, 50);
      LCD.Update();
      Sleep (1000);
      LCD.SetBackgroundColor(WHITE);
      LCD.Clear();
      LCD.ClearBuffer();
      LCD.Update();
      flyswatter ();
    }
 //if anywhere else was clicked, including menu button (takes you back to menu and displays the score)
  else {
   LCD.SetBackgroundColor(WHITE);
   LCD.Clear();
   LCD.SetFontColor(BLACK);
   //prints game over and your score
   points p;
   LCD.WriteAt("GAME OVER.", 50, 50);
   LCD.WriteAt("Score:", 50, 100);
   LCD.WriteAt(score_now, 50, 150);
   LCD.Update();
   Sleep(3000);
    //takes you back to the menu
    menu();
  }
}//end of math function

int coincollect() {
  //add one to the score now
  points p;
  score_now = score_now + 1;
  if (score_now >= p.high_score){
    p.high_score = p.high_score +1;
  }
  return p.high_score;
  return score_now;
  flyswatter();
}// end of coincollect function
/*
  The mosquito jumps in the air
*/
void menu() {
  //initialize score_now as 0
  Sleep(2);
  score_now=0;
  float x_pos, y_pos, x_trash, y_trash;
  LCD.Clear(WHITE);
  LCD.SetFontColor(SKYBLUE);
  LCD.DrawRectangle(80, 20, 200, 210);
  LCD.FillRectangle(80, 20, 200, 210);
  // displaying the text for the menu
  LCD.SetFontColor(WHITE);
  LCD.WriteAt("Play Game",100,40);
  LCD.WriteAt("Instructions",100,80);
  LCD.WriteAt("Statistics",100,120);
  LCD.WriteAt("Credits",100,160);
  LCD.WriteAt("Quit",100,200);
  LCD.Update();
  while(true){
    LCD.ClearBuffer();
    //touch for where to go from the menu
    while(!LCD.Touch(&x_pos, &y_pos)){};
    while(LCD.Touch(&x_trash, &y_trash)){};
    if(y_pos < 80 && y_pos > 35 && x_pos > 100 && x_pos < 240){
      //play game
      PlayGame();
      //go out of loop
      break;
    }
    else if(y_pos < 120 && y_pos > 75 && x_pos > 100 && x_pos < 240){
      //view instructions
      ViewInstructions();
      //go out of loop
      break;
    }
    else if(y_pos < 160 && y_pos > 115 && x_pos > 100 && x_pos < 240){
      //view stats
      ViewStats();
      break;
    }
    else if(y_pos < 200 && y_pos > 155 && x_pos > 100 && x_pos < 240){
      //view credits
      ViewCredits();
      break;
    }
    else if(y_pos < 230 && y_pos > 195 && x_pos > 100 && x_pos < 240){
      //quit
      Quit();
      break;
    }
  }
}//end menu function
//game function for playing the game
void PlayGame(){
  //go to the choose level function
  chooselevel();
}//end of function
void MenuButton(){
  //trash variables for clicking
  float x_pos, y_pos, x_trash, y_trash;
  //creating a menu button
  LCD.SetFontColor(BLACK);
  LCD.WriteAt("Menu", 260, 15);
  while(true)
  {
    LCD.ClearBuffer();
    //looking for touch
    while(!LCD.Touch(&x_pos, &y_pos)){};
    while(LCD.Touch(&x_trash, &y_trash)){};
    if(x_pos > 260 && y_pos < 30)
    {
      menu();
      break;
    }
}
}//end of menu button function
void ViewInstructions(){
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
  //print the menu button
  MenuButton();
}//end of view instructions function
void ViewCredits(){
  LCD.Clear(LIGHTSEAGREEN);
  LCD.SetFontColor(WHITE);
  //print out the credits
  LCD.WriteRC("Developer Credits", 3, 1);
  LCD.WriteRC("Alana Gorukanti", 4, 1);
  LCD.WriteRC("Kathleen Schmidt", 5, 1);
  LCD.WriteRC("Instructor: Dr. Toney", 7, 1);
  LCD.WriteRC("November 2023", 10, 1);
  //option to return to menu
  MenuButton();
}//end of function
void ViewStats(){
  LCD.Clear(LIGHTSEAGREEN);
  //view the high score
  points p;
  LCD.WriteRC("High Score: ", 3, 1);
  LCD.WriteRC(p.high_score, 6, 1);
  //option to return to menu
  MenuButton();
}//end of function
void Quit(){
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
  //asks if you want to quit
  LCD.WriteAt("Are you sure ", 80, 60);
  LCD.WriteAt("you want to ", 80, 85);
  LCD.WriteAt("quit?", 125, 115);
  LCD.WriteAt("Yes", 102, 145);
  LCD.WriteAt("No", 177, 145);
  float x_pos, y_pos, x_trash, y_trash;
  while(true)
  {
    LCD.ClearBuffer();
    //looks for touch for the yes or no
    while(!LCD.Touch(&x_pos, &y_pos)){};
    while(LCD.Touch(&x_trash, &y_trash)){};
    if(x_pos > 100 && x_pos < 140 && y_pos > 140 && y_pos < 165)
    {//closes the game if no is said
      exit(0);
    }
    else{//returns to menu
      menu();
      break;
    } 
  }
}//end of function

void chooselevel(){
  //chose easy or hard level
  Sleep(2);
  int x_pos, y_pos, x_trash, y_trash;
  LCD.ClearBuffer();
  LCD.Clear();

  //create the background
  FEHImage bkg;
  bkg.Open("newlevelChooseFEH.pic");
  bkg.Draw(0,0);
  LCD.Update();

  //looks for touch for level chosen
  while(!LCD.Touch(&x_pos, &y_pos)){};
  while(LCD.Touch(&x_trash, &y_trash)){};

  if(y_pos < 160 && y_pos > 60 && x_pos > 0 && x_pos < 320){
    //play easier game
    flyswatter();
  }
  else {
    //do the harder level
    flyswattermult();
  }
}//end of function
//multiplication flyswatter function
//function for flyswatter opening
void flyswattermult(){
    LCD.SetBackgroundColor(WHITE);
    LCD.Clear();
    LCD.ClearBuffer();
        // Declares an image for flyswatter
    FEHImage flyswatter;
    // Open the image
    flyswatter.Open("flysFEH.pic");
    // Draw a image in the top left corner
    flyswatter.Draw(0, 140);
    //x and y position of the flyswatter
    int xf=320;
    int yf=140;
    //create another flyswatter upside down
    FEHImage udflyswatter;
    udflyswatter.Open("udfFEH.pic");
    udflyswatter.Draw(90, 10);
    //create ints for the movement of the upside down across the screen
    int xudf=90;
    int yudf=10;
    //have the flyswatter move across the screen
  //create an image for the token
  FEHImage token;
    token.Open("tokenFEH.pic");
    //x and y positions of the tokens
    int yToken = 120;
    int xToken = 320;
 
  //x and y trash variables for click
    float x, y;
  // x and y coordinates for the mosquito
    int x1 = 150, y1 = 80;
  //radius of circle for clearing the previous image purposes
    int r = 10;
    // Draw mosquito
    FEHImage mosquito;
    mosquito.Open("mosquitocharFEH.pic");
    mosquito.Draw(x1, y1);
    LCD.Update();
    int disappear=0; //the token should not dissapear if =0
  while (true){
  // so the flyswatter positions don't go negative for comparison purposes
      if (xf < 0){
        xf=320;
      }
      if (xudf < 0){
        xudf=320;
      }
 
    //menu button
    float x_pos, y_pos, x_trash, y_trash;
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Menu", 260, 15);

    LCD.ClearBuffer();
    while(LCD.Touch(&x_pos, &y_pos)){};
    if(x_pos > 260 && y_pos < 30){
          menu();
    }
 
    // Change y coordinate
    y1 += 5;
  
    // Draw new jumper
    mosquito.Draw(x1, y1);
    LCD.Update();
    Sleep(.01);
    int disappear;
    //only redraw the token if it hasnt been through the whole screen
    if (xToken<=4){
      //create a variable that keeps track if the token has been hit or not
      //reset it every time through this loop
      disappear=0; //the token should not dissapear if =0
      //clear old tokens
      LCD.Clear(WHITE);
      //re-draw menu button first
      LCD.SetFontColor(BLACK);
      LCD.WriteAt("Menu", 260, 15);
      LCD.Update();
      //re-draw everything else to make the transition look smooth
      flyswatter.Draw(xf, yf);
      udflyswatter.Draw(xudf, yudf);
      LCD.Update();
      //create new token
      //seed of time(NULL) to make it more random
      srand(time(NULL));
      //random y position for token
      yToken = 70 + (rand() %60);
      //x position always starts out at beginning
      xToken=320;
      token.Draw(300, yToken); 
      LCD.Update();   
      Sleep(0.1);
    }  
    //gravity if not touched
    while ((!LCD.Touch(&x, &y))){
    //clears the old mosquito
        LCD.SetFontColor(WHITE);
        LCD.FillRectangle(x1, y1-10, 20, 40);
        LCD.Update();
        // Change y coordinate
        y1 += 10;
        //create movement for the token; clears old token
        LCD.SetFontColor(WHITE);
        LCD.FillCircle(xToken, yToken+5, r);
        LCD.Update();
        // Draw new jumper
        mosquito.Draw(x1, y1);
        LCD.Update();
        //normal flyswatter clear the old one
         LCD.SetFontColor(WHITE);
        LCD.DrawRectangle(xf, yf, 90, 100);
        LCD.FillRectangle(xf, yf, 90, 100);
        LCD.Update();
        //update the location
        xf=xf-10;
        LCD.Update();
        // Draw flyswatter
       flyswatter.Draw(xf, yf);
        LCD.Update();
        //upside down flyswatter delete the old one
        LCD.SetFontColor(WHITE);
        LCD.DrawRectangle(xudf, yudf, 50, 70);
        LCD.FillRectangle(xudf, yudf, 50, 70);
        LCD.Update();
        //menu button in top corner 
        LCD.SetFontColor(BLACK);
        LCD.WriteAt("Menu", 260, 15);
        LCD.Update();
        //update the location of the upside-down flyswatter
        xudf=xudf-10;
        LCD.Update();
        // Draw flyswatter and token
        //clear old token
        LCD.SetFontColor(WHITE);
        LCD.FillCircle(xToken, yToken+5, r);
        LCD.Update();
        //draw new token and flyswatter
        xToken=xToken-10;
        if (disappear==0){
          token.Draw(xToken, yToken); 
          LCD.Update();
          Sleep(0.1);
        }
        udflyswatter.Draw(xudf, yudf);
        LCD.Update();
        //if statements so that if the mosquito hits the fly swatter, it dies
        //so xf and xudf (position of flyswatter and upside down flyswatter) dont go negative
        if (xf < 0){
          xf=320;
        }
        if (xudf < 0){
         xudf=320;
        }
        Sleep(0.1);
        //if collides with flyswatter
        if (((100<=xf)&&(200>=xf)&&(y1>140))){
          Sleep(0.1);
          //pass to collision function
          collisionmult(); 
        }
        if ((100<=xudf)&&(180>=xudf)&&((y1<50))){
          Sleep(0.1);
          collisionmult();
        }
         //function for collsion with token
        if ((yToken>=y1-20)&&(yToken<=y1+20)&&(xToken>=x1-20)&&(xToken<=x1+20)&&(disappear ==0)){
          //have a little bit of a buffer
          //set the disappear = 1 because it has already collided
          disappear=1;
          //go to coin collect function
          coincollect();
        }
      }
      // Touch - use x and y
      // Jump into the air
     // Clear previous mosqito
      LCD.SetFontColor(WHITE);
      LCD.FillRectangle(x1, y1-10, 20, 40);
      LCD.Update();
      //clear previous token
      LCD.SetFontColor(WHITE);
      LCD.FillCircle(xToken+5, yToken+5, r);
      LCD.Update();
      // Change y coordinate of the mosquito
      y1 -= 40;
      if (xf < 0){
        xf=320;
      }
      // Draw new mosqito
      mosquito.Draw(x1, y1);
      LCD.Update();
      //clear previous mosqito
      LCD.SetFontColor(WHITE);
      LCD.FillRectangle(x1, y1-10, 20, 40);
      LCD.Update();
      // Change y coordinate
      y1 += 10;
      // Draw new mosqito
      mosquito.Draw(x1, y1);
      //clear old flyswatter
      LCD.SetFontColor(WHITE);
      LCD.DrawRectangle(xf, yf, 100, 100);
      LCD.FillRectangle(xf, yf, 100, 100);
      LCD.Update();
      //update the location of the flyswatter and token
      xf=xf-10;
      xToken=xToken-10;
      // so the locations don't go negative for comparison purposes
      if (xf < 0){
        xf=320;
      }
      if (xudf < 0){
        xudf=320;
      }
      xudf=xudf-10;
      LCD.Update();
      // Draw flyswatters and tokens
      flyswatter.Draw(xf, yf);
      udflyswatter.Draw(xudf, yudf);
      if (disappear==0){//draw token only if it has not been collided with yet
        token.Draw(xToken, yToken); 
        LCD.Update();
        Sleep(0.1);
      }
      LCD.Update();
      //upside down flyswatter reset
      LCD.SetFontColor(WHITE);
      LCD.DrawRectangle(xudf, yudf, 70, 70);
      LCD.FillRectangle(xudf, yudf, 70, 70);
      //menu button re-draw
      LCD.SetFontColor(BLACK);
      LCD.WriteAt("Menu", 260, 15);
      LCD.ClearBuffer();
      //if menu button is clicked, go to the menu
      if(x > 260 && y < 30){
        menu();
      }
      LCD.Update();
      //update the location of upside-down flyswatter
      xudf=xudf-10;
      udflyswatter.Draw(xudf, yudf);
      LCD.Update();
      Sleep(0.01);
      //if collides with bottom flyswatter   
      if (((100<=xf)&&(200>=xf)&&(y1>140))){
        collisionmult();  
      }
      //if collides with top flyswatter
      if ((100<=xudf)&&(180>=xudf)&&((y1<50))){
        collisionmult();
      }
      //function for collsion with token
      if ((yToken>=y1-7)&&(yToken<=y1+7)&&(xToken>=x1-20)&&(xToken<=x1+20)&&(disappear == 0)){
        //have a little bit of a buffer
        //set the disappear = 1 because it has already collided
        disappear=1;
        //go to coin collect function
        coincollect();
      }
    }
    //close all of the images
    flyswatter.Close();
    mosquito.Close();
    udflyswatter.Close();
    token.Close();
}// end of the function

//collision function, passes into multiplication
void collisionmult (){
  LCD.Clear();
  //make the background red
  LCD.SetFontColor(RED);
  LCD.DrawRectangle(50, 50, 320, 240);
  LCD.FillRectangle(50, 50, 320, 240);
  LCD.Update();
  //print to screen
  LCD.SetFontColor(BLACK);
  LCD.WriteRC("YOU HIT THE FLY SWATTER.", 2, 1);
  LCD.WriteRC("COMPLETE THE MATH PROBLEM", 4, 1);
  LCD.WriteRC("TO STAY ALIVE\n", 6, 1);
  LCD.Update();
  Sleep(1000);
  //menu button
  LCD.SetFontColor(BLACK);
  //menu button
  float x_pos, y_pos, x_trash, y_trash;
  LCD.SetFontColor(BLACK);
  //write menu in the corner
  LCD.WriteAt("Menu", 260, 15);   
  LCD.ClearBuffer();
  LCD.Update();
  Sleep(1000);
  while(LCD.Touch(&x_pos, &y_pos)){};
  if(x_pos > 260 && y_pos < 30)
  {//go to the menu if the menu button is clicked

    menu();
  }
  else //pass it into the math function
  {
    mathmult();
  }
}//end of collision function

//math with multiplication function
void mathmult () {
  //math equation
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(50, 50, 320, 240);
    LCD.FillRectangle(50, 50, 320, 240);
    LCD.Update();
    LCD.SetFontColor(BLACK);
    LCD.Update();
    //create a random integer between 1 and 100
    // set seed to time(0)
    srand(time(0));
    int a = rand() % 100 + 1;
    int b =  rand() % 100 + 1;
    //menu button (if clicked anywhere on the page else than the right answer it goes to game over)
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Menu", 260, 15);
    //generate the math problem
    LCD.WriteAt(a, 0, 10);
    LCD.WriteAt("*", 35, 10);
    LCD.WriteAt(b, 70, 10);
    LCD.Update();
    int c = a * b;
    //create multiple choice answers
    int f = rand() % 2000 + 1;
    int d= rand() % 2000 + 1;
    int e =  rand() % 2000 + 1;
    //create a random place for the variables to be printed
      //create a vector for placement
    int vect [] = {70, 110, 150, 190};
    int fspot = rand() %4;
    int dspot = rand() %4;
    //make sure theyre not in the same place
    while (dspot == fspot){
       dspot = rand() %4;
    }
    int espot = rand() %4;
    //make sure theyre not in the same place
    while ((espot == fspot)||(espot == dspot)){
       espot = rand() %4;
    }
    //for c
    int cspot = rand() %4;
    //make sure theyre not in the same place
    while ((cspot == fspot)||(cspot == espot) || (cspot == dspot)){
       cspot = rand() %4;
    }
    //spot on y
    //place them
    LCD.WriteAt(f,100,vect[fspot]);
    LCD.WriteAt(d,100,vect[dspot]);
    LCD.WriteAt(c,100,vect[cspot]);
    LCD.WriteAt(e,100,vect[espot]);
    LCD.Update();
    int x_pos, y_pos, x, y;
    LCD.ClearBuffer();
    while(!LCD.Touch(&x_pos, &y_pos)){};
    while(LCD.Touch(&x_pos, &y_pos)){};
    if((y_pos < (vect[cspot]+19)) && (y_pos > (vect[cspot]-19))&&(x_pos > 100) && (x_pos < 240)){
       // go back to original function
      LCD.SetBackgroundColor(GREEN);
      LCD.WriteAt("Correct!", 0, 50);
      LCD.Update();
      Sleep (1000);
      LCD.SetBackgroundColor(WHITE);
      LCD.Clear();
      LCD.ClearBuffer();
      LCD.Update();
      flyswatter ();
    }
 //if anywhere else was clicked, including menu button (takes you back to menu and displays the score)
  else {
   LCD.SetBackgroundColor(WHITE);
   LCD.Clear();
   LCD.SetFontColor(BLACK);
   //prints game over and your score
   points p;
   LCD.WriteAt("GAME OVER.", 50, 50);
   LCD.WriteAt("Score:", 50, 100);
   LCD.WriteAt(score_now, 50, 150);
   LCD.Update();
    Sleep(4000);
    //takes you back to the menu
    menu();
  }
}//end of math function


int main(void)
{
  LCD.SetBackgroundColor(WHITE);
  LCD.Clear();
  LCD.Clear();
  title();
  while (1) {
    LCD.Update();
  }
  return 0;
}

