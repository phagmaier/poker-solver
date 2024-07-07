#include "raylib.h"
//#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <utility>
#include <fstream>

#define CARDFONTSIZE 16 
#define BUTTONFONTSIZE 20 
#define SPACING 5


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
  int screenW = 1000; 
  int screenH = 500;
  int boxX = 0;
  int boxY=0;
  float boxW, boxH;
  bool clickedBox = false;
  int clickedX = -1;
  int clickedY;
  int wordSize=3;
  
  Rectangle textBoxes[13][13];
  std::string cards[13][13];
  bool clicked[13][13];
  //InitWindow(0,0,"RANGES"); 
  InitWindow(screenW,screenH + 100,"RANGES"); 
  Font font_20 = LoadFontEx("../assets/ubuntu.regular.ttf", 20, NULL, 0); 
  Font font_16 = LoadFontEx("../assets/ubuntu.regular.ttf", 16, NULL, 0); 
  //screenW = GetMonitorWidth(GetCurrentMonitor())/2;
  //screenH = GetMonitorHeight(GetCurrentMonitor())/2;

  //SetWindowSize(screenW,screenH);
  boxW = (float)screenW/13;
  boxH = (float)screenH/13;
  std::cout <<"Box height: " << boxH << "\n";

  SetTargetFPS(40);
  int count = 0;
  int offsuite = -1;
  std::string s;
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
      textBoxes[i][x] = Rectangle{w,h,(float)boxW,(float)boxH};
      cards[i][x] = dic[i] + " " + dic[x] + s;
      clicked[i][x] = false;
    }
    offsuite++;
  }

  float buttonH = 50;
  float buttonW = 125;
  Rectangle done_box = Rectangle{(float)(screenW)/2,textBoxes[12][12].y+boxH + 25 ,buttonW,buttonH };

  while (!WindowShouldClose()){

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      std::pair<int,int> box = on_box(textBoxes, &done_box, clicked,cards,&dic);
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
          DrawRectangleRec(textBoxes[i][x], MAROON);
        }
        else{
        DrawRectangleRec(textBoxes[i][x], LIGHTGRAY);
        }
        DrawRectangleLines(textBoxes[i][x].x, textBoxes[i][x].y, boxW, boxH, DARKGRAY);
        //DrawText(cards[i][x].c_str(), textBoxes[i][x].x+5, textBoxes[i][x].y+5, 16, BLACK);
        DrawTextEx(font_16,cards[i][x].c_str(), {textBoxes[i][x].x+10, textBoxes[i][x].y+15}, CARDFONTSIZE, SPACING, BLACK);
      }
    }
    DrawRectangleRec(done_box, BLACK);
    DrawRectangleLines(done_box.x, done_box.y, 125, 50, DARKGRAY);
    //DrawText("Finished", done_box.x+10, done_box.y+10, 20, BLACK);
    DrawTextEx(font_20,"DONE", {done_box.x+30, done_box.y+15}, BUTTONFONTSIZE, SPACING, WHITE);


    EndDrawing();

  }
  CloseWindow();

  return 0;
}
