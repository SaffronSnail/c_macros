#include <string>
  
template <typename InChunk, typename OutOfChunk>
void DoOnChunks(const std::string &target,
                const std::string &chunk_start, const std::string &chunk_end,
                const InChunk &in_operation, const OutOfChunk &out_operation
               )
{
  if (target.empty())
    return;

  //these values are reference multiple times in the following code
  size_t start_size = chunk_start.size();
  size_t end_size   = chunk_end.size();

  size_t beginning = 0; //this tells us how much of the target we've processed

  if (target.substr(beginning, start_size) != chunk_start)
  {
    out_operation(target.substr(beginning, target.find(chunk_start)));
    beginning = target.find(chunk_start, beginning);
  }

  while (beginning != std::string::npos)
  {
    if (target.substr(beginning, start_size) != chunk_start)
      throw "Ummm... yeah. Good luck.";

    beginning += start_size;
    size_t end = target.find(chunk_end, beginning);
    
    if (end == std::string::npos)
      throw std::string("Missing close of chunk. Started at \"" + chunk_start + "\" expeced a matching \"" + chunk_end + "\""); //cause a run-time error

    in_operation(target.substr(beginning, end - beginning));

    beginning = end + end_size;
    if (beginning >= target.size())
      beginning = std::string::npos;
    out_operation(target.substr(beginning, target.find(chunk_start, beginning) - beginning));
    beginning = target.find(chunk_start, beginning);
  }
}

