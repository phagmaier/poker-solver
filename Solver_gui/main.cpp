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
//
//need a functin to read the deafult ranges 
//
//
//NEED TO IMPLIMENT A DYAMIC FONT SIZE SO THAT YOU CAN DO LIKE 5 PIXELS FROM THE START 
//AND THEN FIND THE BIGGEST FONT YOU CAN

#include "raylib.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <utility>
#include <fstream>


#define CARDFONTSIZE 16
#define BUTTONFONTSIZE 20 
#define SPACING 3
#define TEMPFONT 10

enum BoxType{
  None,
  Done,
  Text1,
  Text2,
  Pos1,
  Pos2
};


using hand_pair = std::vector<std::pair<std::pair<int,char>, std::pair<int,char>>>;


void get_suited(char val1, char val2, hand_pair &vec){
  char suits[4] = {'h','s','d', 'c'};
  
  std::map<char,int> charDic = {
    {'A',14}, {'K',13},{'Q',12},
    {'J',10}, {'T',10},{'9',9},{'8',8},{'7',7},{'6',6},
    {'5',5},{'4',4},{'3',3},{'2',2}
  };
  int real_v1 = charDic[val1];
  int real_v2 = charDic[val2];

  for (int i=0; i< 4; ++i){
    vec.push_back({{real_v1,suits[i]},{real_v2,suits[i]}});    
  }
}

void get_off_suite(char val1, char val2, hand_pair &vec){
  char suits[4] = {'h','s','d', 'c'};
  
  std::map<char,int> charDic = {
    {'A',14}, {'K',13},{'Q',12},
    {'J',10}, {'T',10},{'9',9},{'8',8},{'7',7},{'6',6},
    {'5',5},{'4',4},{'3',3},{'2',2}
  };
  int real_v1 = charDic[val1];
  int real_v2 = charDic[val2];

  for (int i=0; i< 4; ++i){
    for (int x =0; x<4; ++x){
      if (i!=x){
        vec.push_back({{real_v1,suits[i]},{real_v2,suits[x]}});    
      }
    }
  }
}

std::pair<hand_pair,hand_pair> init_ranges(std::vector<std::string> &ranges1,std::vector<std::string> &ranges2){
  hand_pair one;
  hand_pair two;

  for (std::string &i : ranges1){
    if (i[5] == 'S' && i[0] != i[2]){
      get_suited(i[0], i[2], one);
    }
    else{
      get_off_suite(i[0],i[2],one);
    }
  }
  for (std::string &i : ranges2){
    if (i[5] == 'S' && i[0] != i[2]){
      get_suited(i[0], i[2], two);
    }
    else{
      get_off_suite(i[0],i[2],two);
    }
  }

  return {one,two}; 
}

void arr_to_vec(bool clicked[13][13], std::string cards[13][13], std::vector<std::string> &vec){
  for (int i=0;i<13;++i){
    for (int x=0; x<13; ++x){
      if (clicked[i][x]){
        vec.push_back(cards[i][x]);
      }
    }
  }
}

/*
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
*/



void reset(bool boxes1[13][13], bool boxes2[13][13], bool *pos1, bool *pos2){
  for (int i=0; i<13; ++i){
    for (int x =0; x<13;++x){
      boxes1[i][x] = false;
      boxes2[i][x] = false;
    }
  }
  for (int i=0; i<6; ++i){
    pos1[i] = false;
    pos2[i] = false;
  }
}


std::pair<BoxType,std::pair<int, int>> on_box(Rectangle boxes[13][13],Rectangle boxes2[13][13], Rectangle *done, 
                            bool clicked[13][13],bool clicked2[13][13],
                            Rectangle position1[6], Rectangle position2[6],bool pos1[6], bool pos2[6],
                            Rectangle *clear,std::string cards[13][13],std::map<int,std::string> *dic){
  Vector2 pos = GetMousePosition();
  for (int i=0; i<13;++i){
    for (int x=0; x<13; ++x){
      if (CheckCollisionPointRec(pos, boxes[i][x])){
        return {Text1,{i,x}};
      }
      if (CheckCollisionPointRec(pos, boxes2[i][x])){
        return {Text2,{i,x}};
    }
  }
  }
  for (int i=0; i<6; ++i){
      if (CheckCollisionPointRec(pos, position1[i])){
        return {Pos1, {i,-1}};
      }
      if (CheckCollisionPointRec(pos, position2[i])){
        return {Pos2, {i,-1}};
      }
  }
      if (CheckCollisionPointRec(pos, *done)){
        //just keeping this for now I won't need in the future
        //write_ranges(clicked, cards, dic);
        return {Done, {-1,-1}};
      }
      
      else if (CheckCollisionPointRec(pos, *clear)){
        reset(clicked,clicked2, pos1,pos2);
      }
      
  return {None,{-1,-1}};
}


int main(){
  std::vector<std::string> r1;
  std::vector<std::string> r2;

  std::map<int,std::string> dic = {{12,"2"}, {11,"3"},{10,"4"},{9,"5"},
    {8,"6"},{7,"7"},{6,"8"}, {5,"9"}, {4,"T"}, {3,"J"}, {2,"Q"},
    {1,"K"}, {0,"A"}};
  std::string suits[4] = {"h","s","d", "c"};
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
  Rectangle pos1[6]; 
  Rectangle pos2[6]; 
  Rectangle runout[52];
  std::string pos_str[6] = {"UTG", "HJ","CO","BTN","SB","BB"};
  std::string cards[13][13];
  bool clicked[13][13];
  bool clicked2[13][13];
  bool pos_clicked1[6] = {false,false,false,false,false,true};
  bool pos_clicked2[6] = {false,false,false,false,true,false};
  std::string runout_str[52];

  //InitWindow(0,0,"RANGES"); 
  //InitWindow(screenW,screenH,"RANGES"); 
  InitWindow(0,0,"SOLVER"); 
  screenW = GetScreenWidth() * .75;
  screenH = GetScreenHeight() * .75;

  SetWindowSize(screenW, screenH);

  Font font_20 = LoadFontEx("../assets/ubuntu.regular.ttf", BUTTONFONTSIZE , NULL, 0); 
  Font font_16 = LoadFontEx("../assets/ubuntu.regular.ttf", CARDFONTSIZE, NULL, 0); 
  Font font_10 = LoadFontEx("../assets/ubuntu.regular.ttf", TEMPFONT, NULL, 0); 
  //screenW = GetMonitorWidth(GetCurrentMonitor())/2;
  //screenH = GetMonitorHeight(GetCurrentMonitor())/2;
  
  int temp_screenW = screenW-20;

  //boxW = (float)temp_screenW/(13*2);
  boxW = (float)temp_screenW/((13 * 2) + 4);
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
      clicked2[i][x] = false;
    }
    offsuite++;
  }


  Rectangle hero = Rectangle{textBoxes1[4][4].x,5,(float)box2W,(float)box2H};
  Rectangle vill = Rectangle{textBoxes2[4][4].x,5,(float)box2W,(float)box2H};

  for (int i=0; i<3; ++i){
    int offset = i * box3W;
    pos1[i] = Rectangle {textBoxes1[0][8].x+offset, 5,(float)box3W,(float)box3H};
    pos2[i] = Rectangle {textBoxes2[0][8].x+offset, 5,(float)box3W,(float)box3H};
  }

  for (int i=3; i<6; ++i){
    int offset = i * box3W;
    pos1[i] = Rectangle {pos1[i-3].x, (float)box3H,(float)box3W,(float)box3H};
    pos2[i] = Rectangle {pos2[i-3].x, (float)box3H,(float)box3W,(float)box3H};
  }
  
  float my_w = boxW;
  float my_h = boxH;
  float my_offset = textBoxes2[12][12].x + boxW + 10;
  float my_h_off = textBoxes2[0][0].y;
  int temp_count = 0;
  for (int i=0; i<13; ++i){
    for (int x =0; x<4; ++x){
      runout[temp_count] = Rectangle{my_w*x+my_offset, my_h*i + my_h_off, my_w,my_h};
      runout_str[temp_count] = dic[i] + suits[x];
      ++temp_count;
    }
  }



  float buttonH = 50;
  float buttonW = 125;
  Rectangle done_box = Rectangle{textBoxes1[5][5].x,textBoxes1[12][12].y+boxH + 50,buttonW,buttonH };
  Rectangle reset_box = Rectangle{textBoxes2[5][5].x,textBoxes2[12][12].y+boxH + 50 ,buttonW,buttonH };

  while (!WindowShouldClose()){
    
    //adjust function to also take in the second textbox
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      std::pair<BoxType,std::pair<int,int>> box = on_box(textBoxes1, textBoxes2, &done_box, clicked,
                                                         clicked2, pos1, pos2, pos_clicked1, 
                                                         pos_clicked2, &reset_box,cards,&dic);
      if (box.first == Done){
        arr_to_vec(clicked,cards,r1);
        arr_to_vec(clicked2,cards,r2);
        //NEED TO MAKE SURE ALL FIELDS ARE INITIALIZED
        //cause after these gonna render it statically so gotta make sure this is fine to do
        //before sending off to the solver
        //if (r1.size() && r2.size() && ...)
        std::pair<hand_pair,hand_pair> final_ranges= init_ranges(r1,r2);
        //call some func to render statically until the solver solves
      }

      else if (box.first != None){
        if (box.first == Text1){
        if (clicked[box.second.first][box.second.second]){
          clicked[box.second.first][box.second.second] = false;
        }
        else{
          clicked[box.second.first][box.second.second] = true;
        }
        }
      if (box.first == Text2){
        if (clicked2[box.second.first][box.second.second]){
          clicked2[box.second.first][box.second.second] = false;
        }
        else{
          clicked2[box.second.first][box.second.second] = true;
        }
        }

      if (box.first == Pos1){
        if (pos_clicked1[box.second.first]){
          pos_clicked1[box.second.first] = false;
        }
        else{
          if (!pos_clicked2[box.second.first]){
          pos_clicked1[box.second.first] = true;
          for (int i=0; i<6; ++i){
                if (i!= box.second.first){
                  pos_clicked1[i] = false;
                }
              }
          }
        }
      }
      if (box.first == Pos2){
        if (pos_clicked2[box.second.first]){
          pos_clicked2[box.second.first] = false;
        }
        else{
          if (!pos_clicked1[box.second.first]){
            pos_clicked2[box.second.first] = true;
              for (int i=0; i<6; ++i){
                if (i!= box.second.first){
                  pos_clicked2[i] = false;
                }
              }
          }
        }
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
        }
        if (clicked2[i][x]){
          DrawRectangleRec(textBoxes2[i][x], YELLOW);
        }
        else{
          DrawRectangleRec(textBoxes2[i][x], LIGHTGRAY);
        }
        
        DrawRectangleLines(textBoxes1[i][x].x, textBoxes1[i][x].y, boxW, boxH, BLACK);
        DrawRectangleLines(textBoxes2[i][x].x, textBoxes2[i][x].y, boxW, boxH, BLACK);
        //DrawText(cards[i][x].c_str(), textBoxes1[i][x].x+5, textBoxes1[i][x].y+5, 16, BLACK);
        DrawTextEx(font_10,cards[i][x].c_str(), {textBoxes1[i][x].x + 8, textBoxes1[i][x].y + mid_box}, TEMPFONT, SPACING, BLACK);
        DrawTextEx(font_10,cards[i][x].c_str(), {textBoxes2[i][x].x + 8, textBoxes2[i][x].y + mid_box}, TEMPFONT, SPACING, BLACK);
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
      if (pos_clicked1[i]){
        DrawRectangleRec(pos1[i], MAROON);
      }
      else{
        DrawRectangleRec(pos1[i], BLACK);
      }
      DrawRectangleLines(pos1[i].x, pos1[i].y, box3W, box3H, DARKGRAY);
      DrawTextEx(font_20,pos_str[i].c_str(), {pos1[i].x+5, pos1[i].y + mid_box3 }, BUTTONFONTSIZE, SPACING, WHITE);
      
      if (pos_clicked2[i]){
        DrawRectangleRec(pos2[i], MAROON);
      }
      else{
        DrawRectangleRec(pos2[i], BLACK);
      }
      DrawRectangleLines(pos2[i].x, pos1[i].y, box3W, box3H, DARKGRAY);
      DrawTextEx(font_20,pos_str[i].c_str(), {pos2[i].x+5, pos2[i].y + mid_box3 }, BUTTONFONTSIZE, SPACING, WHITE);
    }

    for (int i=0; i<52; ++i){
      DrawRectangleRec(runout[i], LIGHTGRAY);
      DrawRectangleLines(runout[i].x, runout[i].y, boxW,boxH, BLACK);
      DrawTextEx(font_16,runout_str[i].c_str(), {runout[i].x + 8, runout[i].y + mid_box}, CARDFONTSIZE, SPACING, BLACK);
    }






    EndDrawing();

  }
  CloseWindow();

  return 0;
}
