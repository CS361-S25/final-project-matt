#include "emp/config/ArgManager.hpp"

EMP_BUILD_CONFIG(MyConfigType,
  VALUE(SEED, int, 10, "What value should the random seed be?"),
  VALUE(UPDATES, int, 100, "How many updates should the program run for?"),
  VALUE(FILE_NAME, std::string, "DataFile.dat", "Root output file name"),
  VALUE(REWARD, bool, true, "Should all tasks receive rewards?")
)