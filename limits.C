#include <iostream>
#include <limits>

int main(int argc , char* argv[])
{
  std::cerr << "max char: " 
            << (int)std::numeric_limits<char>::max() << std::endl;
}

