#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "chunk.h"

static const std::string starting_tag = "#compiletime";
static const std::string ending_tag   = "#end compiletime";

static std::ofstream outfile;

std::string AddEscapes(const std::string &s)
{
  std::string retval;
  for (const char &c : s)
  {
    if (c == '\"' || c == '\\' || c == '\'' || c == '\?')
      retval.append(std::string("\\") + c);
    else if (c == '\n')
      retval.append("\\n");
    else
      retval.push_back(c);

  }
  
  return retval;
}

void ProcessOutputCode(const std::string &code)
{
  outfile << "\n{\n";
  DoOnChunks(code, "#", "#",
             [] (const std::string &s) {outfile << "std::cout << " << s << ";\n";}, 
             [] (const std::string &s) {outfile << "std::cout << \"" << AddEscapes(s) << "\";\n";}
            );
  outfile << "std::cout << std::endl;\n}\n";
}

void ProcessMacroCode(const std::string &code)
{
  //set up the output file
  static std::string filename("temporary_file");
  static std::string extension(".cpp");
  static unsigned count = 0;
  
  outfile.open(filename + std::to_string(++count) + extension);

  outfile << "#include <iostream>\n";
  outfile << "int main(void)\n{";

  DoOnChunks(code,
             "|", "|",
             ProcessOutputCode,
             [] (const std::string &s) {outfile << s;;}
            );

  outfile << "\n  return 0;\n}";
  outfile.close();

  std::string command(std::string("g++ -std=c++11 -o temporary_exe.out ") + filename + std::to_string(count) + extension);
  system(command.c_str());
  system("./temporary_exe.out");
}

int main(void)
{
  //get all of std::cin
  std::string input(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());
  DoOnChunks(input,
             starting_tag, ending_tag, 
             ProcessMacroCode, [] (const std::string &s) {std::cout << s; std::cout.flush();}
            );
  return 0;
}

