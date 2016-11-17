// Reverse the words. Given a String that contains words separated by single
// space, reverse the words in the String. You can assume that no leading or
// trailing spaces are there. 
// 
// For example: "Man bites dog" => "dog bites Man”
// 
// String reverseWords(String value) {
//     // Insert implementation
// }
//

#include <string>
#include <iostream>

using std::string;

namespace
{
  void reverse(char* buf, size_t start, size_t end)
  {
    while(start < end)
    {
      char tmp = buf[start];
      buf[start] = buf[end];
      buf[end] = tmp;
      ++start;
      --end;
    }
  }

  string reverseWords(const string& str)
  {
    const size_t count = str.size();
    char* buf = new char[count+1];
    strncpy(buf, str.c_str(), count);
    buf[count] = 0;

    reverse(buf, 0, count-1);

    size_t startWord = 0;

    for(size_t i = 0; i < count; ++i)
    {
      if(buf[i] == ' ')
      {
        reverse(buf, startWord, i-1);

        if(i < count-1)
        {
          startWord = i+1;
        }
      }
    }

    reverse(buf, startWord, count-1);

    string reversed(buf);
    delete [] buf;
    return reversed;
  }
}

int main(int argc, char* argv[])
{
  std::cerr << "Enter string to reverse: ";
  string str;
  std::getline(std::cin, str);

  std::cerr << "Reversed: " << reverseWords(str) << std::endl;
  return 0;
}


