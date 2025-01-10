#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::cout;
using std::string;
using std::vector;

// TODO: Add the ReadBoardFile function here.
void ReadBoardFile(std::string path)
{
    std::fstream my_file;
    my_file.open(path);
    if (my_file)
    {
        std::string line;
        while (std::getline(my_file, line))
        {
            cout << line;
            cout << "\n";
        }
    }
}

// PrintBoard not used in this exercise
void PrintBoard(const vector<vector<int>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << board[i][j];
    }
    cout << "\n";
  }
}

int main() {
  // TODO: Call the ReadBoardFile function here.
  std::string path;
  path = "./files/1.board";
  ReadBoardFile(path);
  
  // Leave the following line commented out.
  //PrintBoard(board);
}

// string a("1 2 3");

// istringstream my_stream(a);

// int n;
// my_stream >> n;