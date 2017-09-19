#include "CArray.h"
#include <time.h>
#include <iostream>
#include <algorithm>

using namespace std;

void Print(
    CArray<int>& _arr,
    const char* _functionName
  )
{
  cout << _functionName << endl;
  for (CArray<int>::iterator it = _arr.begin(); it != _arr.end(); it++)
  {
    cout << *it << " ";
  }
  cout << endl;
}

void Print(
    CArray<string>& _arr,
    const char* _functionName
  )
{
  cout << _functionName << endl;
  for (CArray<string>::iterator it = _arr.begin(); it != _arr.end(); it++)
  {
    cout << (*it).c_str() << " ";
  }
  cout << endl;
}

void Generate(
    CArray<int>& _arr,
    int _size
  )
{
  for (int i = 0; i < _size; i++)
  {
    _arr.push_back(rand() % 101);
  }
  Print(_arr, __FUNCTION__);
}

void Erase(
    CArray<int>& _arr
  )
{
  for (size_t i = 0, j = 1; i < _arr.size(); i++)
  {
    if (i % 2 == j % 2)
    {
      _arr.erase(i--);
      j++;
    }
  }
  Print(_arr, __FUNCTION__);
}

void Insert(
    CArray<int>& _arr,
    size_t _size
  )
{
  for (size_t i = 0; i < _size; i++)
  {
    const int pos = _arr.size() ? rand() % _arr.size() : 0;
    const int value = rand() % 101;
    _arr.insert(pos, value);
  }
  Print(_arr, __FUNCTION__);
}

string RandomString()
{
  const char chars[] = "abcdefghijklmnopqrstuvwxyz";
  const size_t size = sizeof(chars) - 1;
  string str;
  const int length = rand() % 10 + 1;
  for (int i = 0; i < length; i++)
  {
    str += chars[rand() % size];
  }
  return str;
}

void Generate(
    CArray<string>& _arr,
    int _size
  )
{
  for (int i = 0; i < _size; i++)
  {
    _arr.push_back(RandomString());
  }
  Print(_arr, __FUNCTION__);
}

bool StrContainsChars(
    const string& _str,
    const string& _charsToFind
  )
{
  for (size_t i = 0; i < _charsToFind.size(); i++)
  {
    if (strchr(_str.c_str(), _charsToFind[i]))
      return true;
  }
  return false;
}

void Erase(
    CArray<string>& _arr
  )
{
  for (size_t i = 0; i < _arr.size(); i++)
    if (StrContainsChars(_arr[i], "abcde"))
      _arr.erase(i--);
  Print(_arr, __FUNCTION__);
}

template<typename T>
void Sort(
    CArray<T>& _arr
  )
{
  sort(_arr.begin(), _arr.end());
  Print(_arr, __FUNCTION__);
}

void Insert(
    CArray<string>& _arr,
    size_t _size
  )
{
  for (size_t i = 0; i < _size; i++)
  {
    const int pos = _arr.size() ? rand() % _arr.size() : 0;
    const string str = RandomString();
    _arr.insert(pos, str);
  }
  Print(_arr, __FUNCTION__);
}

template<typename T>
void Clear(
    CArray<T>& _arr
  )
{
  _arr.clear();
  Print(_arr, __FUNCTION__);
}

void TestVectorInt()
{
  CArray<int> arr;
  Generate(arr, 20);
  Sort(arr);
  Erase(arr);
  Insert(arr, 10);
  Clear(arr);
}

void TestVectorString()
{
  CArray<string> arr;
  Generate(arr, 15);
  Sort(arr);
  Erase(arr);
  Insert(arr, 3);
  Clear(arr);
}

int main()
{
  srand(static_cast<unsigned int>(time(nullptr)));
  TestVectorInt();
  TestVectorString();
  return 0;
}
