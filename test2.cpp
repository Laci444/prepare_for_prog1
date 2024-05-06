// Copiright [2024] <Laszlo Szilagyi>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <vector>

using namespace std;

struct Apple {
  string type;
  string color;
};

ostream &operator<<(ostream &ou, Apple apple) {
  ou << "Apple(" << apple.type << ", " << apple.color << ")";
  return ou;
}

bool isPrime(int number) {
  if (number < 2)
    return false;
  if (number == 2)
    return true;
  if (number % 2 == 0)
    return false;
  for (int i = 3; (i * i) <= number; i += 2) {
    if (number % i == 0)
      return false;
  }
  return true;
}

int primes_between(int n1, int n2) {
  int counter = 0;
  for (int i = n1; i < n2; i++) {
    if (isPrime(i))
      counter++;
  }
  return counter;
}

template <typename TwoD> void sum_rows(TwoD *in, int rows, int cols, int *out) {
  int sum = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; i < cols; i++) {
      sum += in[i][j];
    }
    out[i] = sum;
    sum = 0;
  }
}

void the_fuck_is_this(int *arr, int &a, int b) { a = arr[b]; }

double average(int *numbers, int n) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += numbers[i];
  }
  return static_cast<double>(sum) / n;
}

template <typename T> vector<T> split(string &in, char delimeter) {
  istringstream iss(in);
  vector<T> tokens;
  T token;
  while (iss >> token) {
    tokens.push_back(static_cast<T>(token));
  }
  return tokens;
}

vector<vector<int>> sort_rows_from_file(ifstream &in) {
  // this is bad i know but in cpp its pain to join strings
  vector<vector<int>> lines;
  string line;
  while (getline(in, line)) {
    vector<int> numbers = split<int>(line, ' ');
    sort(numbers.begin(), numbers.end());
    lines.push_back(numbers);
  }
  return lines;
}

int main() {
  // 1. feladat
  cout << "Primes between two number (10, 53): " << primes_between(10, 53)
       << endl;

  // 2. feladat
  int matrix[4][4] = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  int output[4];
  sum_rows(matrix, 4, 4, output);
  cout << "Sum of rows in declared matrix: ";
  for (int i = 0; i < 4; i++) {
    cout << output[i] << " ";
  }
  cout << endl;

  // 3. feladat
  int in_array[5] = {1, 2, 3, 4, 5};
  int storage;
  the_fuck_is_this(in_array, storage, 3);

  // 4. feladat
  int numbers[3];
  cout << "You have to input 3 numbers!" << endl;
  for (int i = 0; i < 3; i++) {
    cout << i + 1 << ". number: ";
    cin >> numbers[i];
  }
  cout << "Average of 3 numbers: " << round(average(numbers, 3) * 100) / 100
       << endl;

  // 5. feladat
  Apple basket[5] = {{"idared", "piros"},
                     {"mittudomen", "kek"},
                     {"almaaaaa", "zold"},
                     {"hanyas", "zold"},
                     {"elegem van", "killmepls"}};
  vector<Apple> greens;
  vector<Apple> reds;

  for (int i = 0; i < 5; i++) {
    if (basket[i].color == "piros")
      reds.push_back(basket[i]);
    if (basket[i].color == "zold")
      greens.push_back(basket[i]);
  }

  cout << "Green apples: ";
  for (Apple app : greens) {
    cout << app << " ";
  }
  cout << endl;

  cout << "Red apples: ";
  for (Apple app : reds) {
    cout << app << " ";
  }
  cout << endl;

  // 6. feladat
  ifstream infile("szamok.txt");
  ofstream oufile("rendezett_szamok.txt");

  auto returns = sort_rows_from_file(infile);

  for (vector<int> line : returns) {
    for (int i = 0; i < line.size(); i++) {
      oufile << line[i];
      if (i != line.size() - 1)
        oufile << " ";
    }
    oufile << endl;
  }
  cout << "File is written!" << endl;

  infile.close();
  oufile.close();

  return 0;
}
