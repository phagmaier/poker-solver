//CURRENTLY WHEN A BOX IS clicked it draws won't draw the 
//[i][x] boxes background so need to fix that need to run another check 
//to make sure the other boxes of cards weren't clicked (just adjust the function to)
//take both boxes i guess and also have to check to see if they clicked on positions 
//
//would probably also be more efficient to get the min and max of both height and width for the 
//text boxes and only if it is in that range of x,y cordinates do you check
//
//Also for now you can have it keep exporting a file of ranges but in the future that shouldn't happen
//in fact it should say run sim 
//it should then render drawings to the screen statically so it doesn't waste threads and shit 
//and when it's done it reduces the ranges to small and there will be another little window where 
//you can click on cards and get a break down of ranges and shit

#include "raylib.h"
//#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <utility>
#include <fstream>

#define CARDFONTSIZE 16
#define BUTTONFONTSIZE 20 
#define SPACING 3


void write_ranges(bool clicked[13][13], std::string cards[13][13],
                  std::map<int,std::string> *dic){

  std::ofstream outFile;

  outFile.open("ranges.txt");
  for (int i=0; i< 13; ++i){
    for (int x=0; x<13; ++x){
      if (clicked[i][x]){
        outFile << cards[i][x] << "\n";
      }
    }
  }
  outFile.close();
}




std::pair<int, int> on_box(Rectangle boxes[13][13], Rectangle *done, bool clicked[13][13], std::string cards[13][13],
                           std::map<int,std::string> *dic){
  Vector2 pos = GetMousePosition();
  for (int i=0; i<13;++i){
    for (int x=0; x<13; ++x){
      if (CheckCollisionPointRec(pos, boxes[i][x])){
        return {i,x};
      }
    }
  }
  if (CheckCollisionPointRec(pos, *done)){
   write_ranges(clicked, cards, dic); 
  }
  return {-1,-1};
}


int main(){
  std::map<int,std::string> dic = {{12,"2"}, {11,"3"},{10,"4"},{9,"5"},
    {8,"6"},{7,"7"},{6,"8"}, {5,"9"}, {4,"T"}, {3,"J"}, {2,"Q"},
    {1,"K"}, {0,"A"}};
  int rows = 13;
  int cols = 13;
  int screenW = 1200; 
  int screenH = 900;
  int boxX = 0;
  int boxY=0;
  float boxW, boxH;
  bool clickedBox = false;
  int clickedX = -1;
  int clickedY;
  int wordSize=3;

  int box2W = 125; 
  int box2H = 50;
  int box3W = 50;
  int box3H = 50;

  const float mid_box3 = box3H * .5;
  
  Rectangle textBoxes1[13][13];
  Rectangle textBoxes2[13][13];
  Rectangle pos1[6]; //need to add
  Rectangle pos2[6]; // need to add
  std::string pos_str[6] = {"UTG", "HJ","CO","BTN","SB","BB"};
  std::string cards[13][13];
  bool clicked[13][13];
  //InitWindow(0,0,"RANGES"); 
  //InitWindow(screenW,screenH,"RANGES"); 
  InitWindow(0,0,"RANGES"); 
  screenW = GetScreenWidth() * .75;
  screenH = GetScreenHeight() * .75;

  SetWindowSize(screenW, screenH);

  Font font_20 = LoadFontEx("../assets/ubuntu.regular.ttf", BUTTONFONTSIZE , NULL, 0); 
  Font font_16 = LoadFontEx("../assets/ubuntu.regular.ttf", CARDFONTSIZE, NULL, 0); 
  //screenW = GetMonitorWidth(GetCurrentMonitor())/2;
  //screenH = GetMonitorHeight(GetCurrentMonitor())/2;
  
  int temp_screenW = screenW-10;

  //SetWindowSize(screenW,screenH);
  boxW = (float)temp_screenW/(13*2);
  float temp_box_h = (float)screenH / 13;
  boxH = temp_box_h * .75;
  float mid_box = boxH * .5;
  std::cout <<"Box height: " << boxH << "\n";

  SetTargetFPS(40);
  int count = 0;
  int offsuite = -1;
  std::string s;
  float h_offset = 100;
  for (int i=0; i<13;++i){
    float h = i * boxH;
    for (int x=0;x<13;++x){
      if (x<=offsuite ){
        s = " O";
       }
      else{
       s = " S";
       }
      float w = x * boxW;
      float w2 = (boxW * 13) + 10 + x * boxW;
      
      textBoxes1[i][x] = Rectangle{w,h+h_offset,(float)boxW,(float)boxH};
      //will have to account for  small space in between them
      textBoxes2[i][x] = Rectangle{w2,h+h_offset,(float)boxW,(float)boxH};
      cards[i][x] = dic[i] + " " + dic[x] + s;
      clicked[i][x] = false;
    }
    offsuite++;
  }


  Rectangle hero = Rectangle{textBoxes1[4][4].x,5,(float)box2W,(float)box2H};
  Rectangle vill = Rectangle{textBoxes2[4][4].x,5,(float)box2W,(float)box2H};

  for (int i=0; i<3; ++i){
    int offset = i * box3W;
    pos1[i] = Rectangle {textBoxes1[0][10].x+offset, 5,(float)box3W,(float)box3H};
    pos2[i] = Rectangle {textBoxes2[0][10].x+offset, 5,(float)box3W,(float)box3H};
  }

  for (int i=3; i<6; ++i){
    int offset = i * box3W;
    pos1[i] = Rectangle {pos1[i-3].x, (float)box3H,(float)box3W,(float)box3H};
    pos2[i] = Rectangle {pos2[i-3].x, (float)box3H,(float)box3W,(float)box3H};
  }


  float buttonH = 50;
  float buttonW = 125;
  Rectangle done_box = Rectangle{textBoxes1[5][5].x,textBoxes1[12][12].y+boxH + 50,buttonW,buttonH };
  Rectangle reset_box = Rectangle{textBoxes2[5][5].x,textBoxes2[12][12].y+boxH + 50 ,buttonW,buttonH };

  while (!WindowShouldClose()){
    
    //adjust function to also take in the second textbox
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      std::pair<int,int> box = on_box(textBoxes1, &done_box, clicked,cards,&dic);
      if (box.first > -1){
        if (clicked[box.first][box.second]){
          clicked[box.first][box.second] = false;
        }
        else{
          clicked[box.first][box.second] = true;
        }
      }
    }
      

    BeginDrawing();

    ClearBackground(RAYWHITE);
    for (int i=0;i < 13;++i){
      for (int x=0;x < 13; ++x){
        if (clicked[i][x]){
          //have to add the second text boxes as well
          DrawRectangleRec(textBoxes1[i][x], YELLOW);
        }
        else{
        DrawRectangleRec(textBoxes1[i][x], LIGHTGRAY);
        DrawRectangleRec(textBoxes2[i][x], LIGHTGRAY);
        }
        DrawRectangleLines(textBoxes1[i][x].x, textBoxes1[i][x].y, boxW, boxH, DARKGRAY);
        DrawRectangleLines(textBoxes2[i][x].x, textBoxes2[i][x].y, boxW, boxH, DARKGRAY);
        //DrawText(cards[i][x].c_str(), textBoxes1[i][x].x+5, textBoxes1[i][x].y+5, 16, BLACK);
        DrawTextEx(font_16,cards[i][x].c_str(), {textBoxes1[i][x].x + 8, textBoxes1[i][x].y + mid_box}, CARDFONTSIZE, SPACING, BLACK);
        DrawTextEx(font_16,cards[i][x].c_str(), {textBoxes2[i][x].x + 8, textBoxes2[i][x].y + mid_box}, CARDFONTSIZE, SPACING, BLACK);
      }
    }
    DrawRectangleRec(done_box, BLACK);
    DrawRectangleLines(done_box.x, done_box.y, box2W, box2H, DARKGRAY);
    DrawTextEx(font_20,"DONE", {done_box.x+30, done_box.y+15}, BUTTONFONTSIZE, SPACING, WHITE);
    
    DrawRectangleRec(reset_box, BLACK);
    DrawRectangleLines(reset_box.x, reset_box.y, box2W, box2H, DARKGRAY);
    DrawTextEx(font_20,"RESET", {reset_box.x+30, reset_box.y+15}, BUTTONFONTSIZE, SPACING, WHITE);

    DrawRectangleRec(hero, BLACK);
    DrawRectangleLines(hero.x, hero.y, box2W, box2H, DARKGRAY);
    DrawTextEx(font_20,"HERO", {hero.x+30, hero.y+15}, BUTTONFONTSIZE, SPACING, WHITE);

    DrawRectangleRec(vill, BLACK);
    DrawRectangleLines(vill.x, vill.y, box2W, box2H, DARKGRAY);
    DrawTextEx(font_20,"VILLIAN", {vill.x+20, vill.y+15}, BUTTONFONTSIZE, SPACING, WHITE);

    for (int i=0; i<6; ++i){
      DrawRectangleRec(pos1[i], BLACK);
      DrawRectangleLines(pos1[i].x, pos1[i].y, box3W, box3H, DARKGRAY);
      DrawTextEx(font_16,pos_str[i].c_str(), {pos1[i].x+5, pos1[i].y + mid_box3 }, CARDFONTSIZE, SPACING, WHITE);

      DrawRectangleRec(pos2[i], BLACK);
      DrawRectangleLines(pos2[i].x, pos1[i].y, box3W, box3H, DARKGRAY);
      DrawTextEx(font_16,pos_str[i].c_str(), {pos2[i].x+5, pos2[i].y + mid_box3 }, CARDFONTSIZE, SPACING, WHITE);



    }






    EndDrawing();

  }
  CloseWindow();

  return 0;
}
