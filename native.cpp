// Compile with `c++ -std=c++17 -Isignalgp-lite/include native.cpp`

#include <iostream>
#include "emp/config/ArgManager.hpp"

#include "World.h"
#include "ConfigSetup.h"

MyConfigType config;

/**
 * @brief Initializes the configuration settings for the simulation.
 *
 * This function attempts to read the configuration from "MySettings.cfg". If the file cannot
 * be read, it writes a new configuration file with default settings and reads it again.
 * It then processes command line options to override any settings from the configuration file.
 * If any errors are encountered during processing (either in the options file or due to unknown arguments),
 * an error message is printed and the program exits.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 */
void InitializeConfig(int argc, char *argv[]) {
  bool success = config.Read("MySettings.cfg");
  if (!success) { config.Write("MySettings.cfg"); }
  config.Read("MySettings.cfg");

  auto args = emp::cl::ArgManager(argc, argv);
  if (args.ProcessConfigOptions(config, std::cout, "MySettings.cfg") == false) {
    std::cerr << "There was a problem in processing the options file." << std::endl;
    exit(1);
  }
  if (args.TestUnknown() == false) {
    std::cerr << "Leftover args no good." << std::endl;
    exit(1);
  }
}

/**
 * @brief Sets up and runs the simulation world.
 *
 * This function configures the simulation world by setting up the data file, adjusting the timing
 * parameters, and initializing the simulation with the starting number of organisms defined in the
 * configuration. It prepares the world for subsequent simulation steps.
 *
 * @param world A reference to the OrgWorld instance representing the simulation world.
 */
void RunWorld(OrgWorld &world) {
  world.SetupDataFile(config.FILE_NAME()).SetTimingRepeat(10);
  world.SetReward(config.REWARD());
  
  for (int i = 0; i < 3600; i++) {
    Organism* new_org = new Organism(&world);
    world.AddOrgAt(new_org, i);
  }
  world.Resize(60,60);
  for (int update = 0; update < config.UPDATES(); update++) {
    world.Update();
  }
}

// This is the main function for the NATIVE version of this project.
int main(int argc, char *argv[]) {
  InitializeConfig(argc, argv);

  emp::Random random(config.SEED());
  OrgWorld world(random);
  // Some SignalGP-Lite functionality uses its own emp::Random instance
  // so it's important to set that seed too when the main Random is created
  sgpl::tlrand.Get().ResetSeed(2);

  RunWorld(world);
}