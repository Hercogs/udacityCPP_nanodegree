#include <iostream>
#include <vector>

using std::cout;

void PrintBoard(std::vector<std::vector<int>> v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        for (size_t j = 0; j < v[0].size(); j++)
        {
            cout << v[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
  // TODO: Declare a "board" variable here, and store
  // the data provided above.
  std::vector<std::vector<int>> board = {{0, 1, 0, 0, 0, 0},
                                         {0, 1, 0, 0, 0, 0},
                                         {0, 1, 0, 0, 0, 0},
                                         {0, 1, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 1, 0}};

  PrintBoard(board);
}