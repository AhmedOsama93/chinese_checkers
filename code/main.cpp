#include <iostream>
#include<bits/stdc++.h>
#define FAST_IO  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
struct node{
    int row;
    int column;
    char color;
};
vector<node>loadBoard(){
    vector<node>board(122);
    int i=0;
    fstream boardFile;
    boardFile.open("input.txt", ios::in);
    while(i<121) {
        char state[6];
        boardFile.read(state, 5);
        string str1, str2, str=state;
        char col;
        str1=str.substr(0,2);
        str2=str.substr(2,2);
        col=str[4];
        board[i].row= stoi(str1);
        board[i].column= stoi(str2);
        board[i].color= col;
        i++;
    }
    return board;
}
vector<node>board=loadBoard();

char myColor(int curRow, int curColumn) {
    for (int i = 0; i < board.size(); ++i) {
        if (board[i].row == curRow && board[i].column == curColumn) {
            return board[i].color;
        }
    }
}

bool isItInBoardAndWhite(int r, int c){
    for (int i = 0; i < board.size(); ++i) {
        if (board[i].row==r && board[i].column==c
        &&board[i].color=='W'){
            return true;
        }
    }
    return false;
}

bool isItInBoardAndNotWhite(int r, int c){
    for (int i = 0; i < board.size(); ++i) {
        if (board[i].row==r && board[i].column==c
        &&  (board[i].color!='W')){
            return true;
        }
    }
    return false;
}
vector<node>availableMoves(int curRow, int curColumn){
    char currentColor;
    vector<node>availableMoves(6);
    //currRow=5&curColumn=11-> parent node
    //children nodes:5,12 &5,10 &6,11 &6,10 &4,12 &4,11
    curColumn++;
    //currRow=5&curColumn=12
    if (isItInBoardAndWhite(curRow, curColumn) ){
        availableMoves[0].row=curRow;
        availableMoves[0].column=curColumn;
        availableMoves[0].color=myColor(curRow,curColumn);
    }
    curColumn--;
    //currRow=5&curColumn=11 -> parent node
    curColumn--;
    //currRow=5&curColumn=10
    if (isItInBoardAndWhite(curRow, curColumn) ){
        availableMoves[1].row=curRow;
        availableMoves[1].column=curColumn;
        availableMoves[1].color=myColor(curRow,curColumn);;
    }
    curColumn++;
    //currRow=5&curColumn=11 -> parent node
    curRow--;
    //currRow=4&curColumn=11
    if (isItInBoardAndWhite(curRow, curColumn) ){
        availableMoves[2].row=curRow;
        availableMoves[2].column=curColumn;
        availableMoves[2].color=myColor(curRow,curColumn);
    }
    curColumn++;
    //currRow=4&curColumn=12
    if (isItInBoardAndWhite(curRow, curColumn) ){
        availableMoves[3].row=curRow;
        availableMoves[3].column=curColumn;
        availableMoves[3].color=myColor(curRow,curColumn);
    }
    curColumn--;
    curRow++;
    //currRow=5&curColumn=11-> parent node
    curRow++;
    //currRow=6&curColumn=11 ->child node
    if (isItInBoardAndWhite(curRow, curColumn) ){
        availableMoves[4].row=curRow;
        availableMoves[4].column=curColumn;
        availableMoves[4].color=myColor(curRow,curColumn);
    }
    curColumn--;
    //currRow=6&curColumn=10 ->child node
    if (isItInBoardAndWhite(curRow, curColumn) ){
        availableMoves[5].row=curRow;
        availableMoves[5].column=curColumn;
        availableMoves[5].color=myColor(curRow,curColumn);
    }
    return availableMoves;
}

vector<node>availableLeaps(int curRow, int curColumn){
    vector<node>availableLeaps(6);
    //currRow=5&curColumn=11-> parent node
    //children nodes:
    curColumn+=2;
    //currRow=5&curColumn=13
    if (isItInBoardAndWhite(curRow, curColumn)
    && isItInBoardAndNotWhite(curRow, curColumn-1)){
        availableLeaps[0].row=curRow;
        availableLeaps[0].column=curColumn;
        availableLeaps[0].color='W';
    }
    curColumn-=2;//11
    //currRow=5&curColumn=11 -> parent node
    curColumn-=2;//9
    //currRow=5&curColumn=9
    if (isItInBoardAndWhite(curRow, curColumn)
    && isItInBoardAndNotWhite(curRow, curColumn+1)){
        availableLeaps[1].row=curRow;
        availableLeaps[1].column=curColumn;
        availableLeaps[1].color='W';
    }
    curColumn+=2;
    //currRow=5&curColumn=11 -> parent node
    curRow-=2;//3
    //currRow=3&curColumn=11
    if (isItInBoardAndWhite(curRow, curColumn)
        && isItInBoardAndNotWhite(curRow+1, curColumn)){
        availableLeaps[2].row=curRow;
        availableLeaps[2].column=curColumn;
        availableLeaps[2].color='W';
    }
    curColumn+=2;
    //currRow=3&curColumn=13
    if (isItInBoardAndWhite(curRow, curColumn)
    && isItInBoardAndNotWhite(curRow+1, curColumn-1)){
        availableLeaps[3].row=curRow;
        availableLeaps[3].column=curColumn;
        availableLeaps[3].color='W';
    }
    curColumn-=2;//11
    curRow+=2;//5
    //currRow=5&curColumn=11-> parent node
    curRow+=2;
    //currRow=7&curColumn=11 ->child node
    if (isItInBoardAndWhite(curRow, curColumn)
        && isItInBoardAndNotWhite(curRow-1, curColumn)){
        availableLeaps[4].row=curRow;
        availableLeaps[4].column=curColumn;
        availableLeaps[4].color='W';
    }

    curColumn-=2;
    //currRow=6&curColumn=10 ->child node
    if (isItInBoardAndWhite(curRow, curColumn)
        && isItInBoardAndNotWhite(curRow-1, curColumn+1)){
        availableLeaps[5].row=curRow;
        availableLeaps[5].column=curColumn;
        availableLeaps[5].color='W';
    }
    return availableLeaps;
}

void printAvailableMoves(vector<node>availableMoves){
    cout<<"Available Moves are : \n";
    for (int i = 0; i < 6; ++i) {
        if (availableMoves[i].row !=0 &&availableMoves[i].column!=0) {
            cout << availableMoves[i].row <<
            " "  << availableMoves[i].column <<
            " "  << availableMoves[i].color << endl;
        }
    }
}


void printAvailableLeaps(vector<node> availableMoves) {
    cout << "Available Leaps are : \n";
    for (int i = 0; i < 6; ++i) {
        if (availableMoves[i].row != 0 && availableMoves[i].column != 0) {
            cout << availableMoves[i].row <<
                 " " << availableMoves[i].column <<
                 " " << availableMoves[i].color << endl;
        }
    }
}
int main() {
    FAST_IO
    printAvailableMoves(availableMoves(5, 12));
    printAvailableLeaps(availableLeaps(5, 12));
    return 0;
}
