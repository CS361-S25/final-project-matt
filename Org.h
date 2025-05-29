#ifndef ORG_H
#define ORG_H

#include "CPU.h"
#include "OrgState.h"
#include "emp/Evolve/World_structure.hpp"

class Organism {
  CPU cpu;

public:
  Organism(emp::Ptr<OrgWorld> world, double points = 0.0) : cpu(world) {
    SetPoints(points);
  }

  /**
   * Sets the points in the OrgState to the specified value through the CPU
   * 
   * @param _in the desired number of points
   */
  void SetPoints(double _in) { cpu.state.points = _in; }

  /**
   * Adds the specified number of points to the OrgState through the CPU
   * 
   * @param _in the number of points to add
   */
  void AddPoints(double _in) { cpu.state.points += _in; }

  /**
   * Accesses the organism's points through the CPU
   * 
   * @return the organism's points
   */
  double GetPoints() { return cpu.state.points; }

  /**
   * Calls the CPU's Reset function
   */
  void Reset() { cpu.Reset(); }

  /**
   * Calls the CPU's Mutate function
   */
  void Mutate() { cpu.Mutate(); }

  /**
   * Accesses the organism's CPU
   * 
   * @return the CPU
   */
  CPU getCPU() { return cpu; }

  /**
   * Attempt to produce a child organism, if this organism has enough points.
   */
  std::optional<Organism> CheckReproduction() {
    Organism offspring = *this;
    offspring.Reset();
    offspring.Mutate();
    return offspring;
    return {};
  }

  /**
   * Uses the necessary CPU functionality to process an organism.
   */
  void Process(emp::WorldPosition current_location) {
    //cpu.state.task_done = false;
    cpu.state.current_location = current_location;
    cpu.RunCPUStep(10);
  }

  /**
   * Prints the organism's genome using its CPU.
   */
  void PrintGenome() {
    std::cout << "program ------------" << std::endl;
    cpu.PrintGenome();
    std::cout << "end ---------------" << std::endl;
  }
};

#endif