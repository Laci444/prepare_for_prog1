// Copyright [2024] <Laszlo Szilagyi>

#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

class Box {
  int width;
  int height;
  int depth;

public:
  Box() {
    this->width = 0;
    this->height = 0;
    this->depth = 0;
  }
  Box(int width, int height, int depth) {
    this->width = width;
    this->height = height;
    this->depth = depth;
  }
  int getWidth() { return this->width; }
  int getHeight() { return this->height; }
  int getDepth() { return this->depth; }
  bool will_this_fit(int width, int height, int depth) {
    if (!(this->width >= width && this->height >= height &&
          this->depth >= depth))
      return false;
    return true;
  }
};

ostream &operator<<(ostream &os, Box in) {
  os << "Box(" << in.getWidth() << ", " << in.getHeight() << ", "
     << in.getDepth() << ")";
  return os;
}

int first_assessment(int n1, int n2) {
  int biggest = 0;
  for (int i = n1; i < n2; i++) {
    if (i % 3 == 0 && i % 2 == 0 && i > biggest) {
      biggest = i;
    }
  }
  return biggest;
}

// solutions time complexity is row * col * (n + 1)
// another solution would involve sorting, which is n log n
// this is more efficient when n + 1 is smaller than row * col
template <typename TwoDarr>
void return_smallest_n_number(int n, TwoDarr &arr, int row, int col,
                              int *output_arr) {
  // (we assume that the inputs are verifyed befor the function call)
  // first calculate the biggest of them
  // we will use this to set the already found smallest numbers
  // to the biggest to proceed to get the other smallests
  int biggest = arr[0][0];
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (arr[i][j] > biggest)
        biggest = arr[i][j];
    }
  }
  // than we get the n smallest number
  int *curr_smallest = &arr[0][0];
  for (int smallest_iter = 0; smallest_iter < n; smallest_iter++) {
    // simple min algo
    for (int row_iter = 0; row_iter < row; row_iter++) {
      for (int col_iter = 0; col_iter < col; col_iter++) {
        if (arr[row_iter][col_iter] < *curr_smallest) {
          curr_smallest = &arr[row_iter][col_iter];
        }
      }
    }
    // place the smallest number in the output array
    output_arr[smallest_iter] = *curr_smallest;
    // then we set the smallest number to the biggest to never find again
    *curr_smallest = biggest;
  }
}

void _swap_two_integers(int &a, int &b) {
  a = a + b;
  b = a - b;
  a = a - b;
}

void swap_integers(int &a, int &b, int &c) {
  _swap_two_integers(a, b);
  _swap_two_integers(c, b);
  _swap_two_integers(a, b);
  _swap_two_integers(c, b);
}

string *get_closest_to_average(string *arr, int n) {
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += arr[i].length();
  double average = (double)sum / n;
  string *closest = &arr[0];
  for (int i = 0; i < n; i++) {
    if (abs(arr[i].length() - average) < abs((*closest).length() - average)) {
      closest = &arr[i];
    }
  }
  return closest;
}

void read_from_file_than_write_to_another(ifstream &input, ofstream &output) {
  string line;
  int sum = 0;
  int count = 0;
  while (getline(input, line)) {
    output << line.length() << endl;
    sum += line.length();
    count++;
  }
  cout << "Average line length: " << round((double)sum / count * 100) / 100
       << endl;
}

int main() {
  // 1. feladat
  cout << "1. (10, 48)" << first_assessment(10, 48) << endl;

  // 2. feladat
  int numbers[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      numbers[i][j] = j + (10 * i);
    }
  }
  int return_size = 5;
  int return_arr[return_size];
  for (int i = 0; i < return_size; i++) {
    return_arr[i] = 0;
  }
  return_smallest_n_number(return_size, numbers, 10, 10, return_arr);
  for (int i = 0; i < return_size; i++) {
    cout << return_arr[i] << " ";
  }
  cout << endl;

  // 3. feladat
  int first = 5;
  int second = 10;
  int third = 15;
  swap_integers(first, second, third);
  cout << "First: " << first << endl
       << "Second: " << second << endl
       << "Third: " << third << endl;

  // 4. feladat
  int n;
  cout << "Input the number of expected strings: ";
  cin >> n;
  // assume that the input is valid
  string strs[n];
  for (int i = 0; i < n; i++) {
    cout << i + 1 << ". ";
    cin >> strs[i];
  }
  cout << "Closest to average: " << *get_closest_to_average(strs, n) << endl;

  // 5. feladat
  Box boxes[5] = {Box(1, 2, 3), Box(100, 200, 300), Box(50, 20, 30),
                  Box(4, 3, 6), Box(10, 10, 10)};
  cout << "These boxes can fit a 10x15x12 package: ";
  for (int i = 0; i < 5; i++) {
    if (boxes[i].will_this_fit(10, 15, 12))
      cout << boxes[i] << " ";
  }
  cout << endl;

  // 6. feladat
  ifstream infile("randomok.txt");
  ofstream oufile("sorhossz.txt");

  read_from_file_than_write_to_another(infile, oufile);

  infile.close();
  oufile.close();

  return 0;
}
