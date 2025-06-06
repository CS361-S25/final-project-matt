#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/data/DataFile.hpp"

#include "Org.h"
#include "Task.h"

class OrgWorld : public emp::World<Organism> {
  emp::vector<emp::WorldPosition> reproduce_queue;
  std::vector<Task*> tasks{new EQU(), new XOR(), new NOR(), new ANDN(), new OR(), new ORN(), new AND(), new NAND(), new NOT()};
  emp::Ptr<emp::DataMonitor<int>> EQUCount;
  emp::Ptr<emp::DataMonitor<int>> XORCount;
  emp::Ptr<emp::DataMonitor<int>> NORCount;
  emp::Ptr<emp::DataMonitor<int>> ANDNCount;
  emp::Ptr<emp::DataMonitor<int>> ORCount;
  emp::Ptr<emp::DataMonitor<int>> ORNCount;
  emp::Ptr<emp::DataMonitor<int>> ANDCount;
  emp::Ptr<emp::DataMonitor<int>> NANDCount;
  emp::Ptr<emp::DataMonitor<int>> NOTCount;
  bool reward;

public:
  OrgWorld(emp::Random &_random) : emp::World<Organism>(_random) {}

  ~OrgWorld() {
    if (EQUCount) {EQUCount.Delete();}
    if (XORCount) {XORCount.Delete();}
    if (NORCount) {NORCount.Delete();}
    if (ANDNCount) {ANDNCount.Delete();}
    if (ORCount) {ORCount.Delete();}
    if (ORNCount) {ORNCount.Delete();}
    if (ANDCount) {ANDCount.Delete();}
    if (NANDCount) {NANDCount.Delete();}
    if (NOTCount) {NOTCount.Delete();}
  }

  /**
   * @brief Returns the current population.
   *
   * This function provides access to the container holding all organisms in the world.
   *
   * @return const pop_t& A constant reference to the population container.
   */
  const pop_t &GetPopulation() { return pop; }

  void SetReward(bool rewardBool) { reward = rewardBool; }

  bool GetReward() { return reward; }

  /**
   * @brief Retrieves the data monitor tracking the count of organisms with the 'EQU' state.
   *
   * This function ensures that the data monitor for counting organisms whose state indicates 
   * they have performed "EQU" is properly instantiated and updated. On the first call, it initializes the 
   * monitor and registers an update callback that iterates over the population to count relevant organisms.
   *
   * @return emp::DataMonitor<int>& Reference to the data monitor tracking EQU counts.
   */
  emp::DataMonitor<int> & GetEQUCountDataNode() {
      if (!EQUCount) {
        EQUCount.New();
        OnUpdate([this](size_t){
          EQUCount->Reset();
          for (size_t i = 0; i < pop.size(); i++) {
            if (IsOccupied(i)) {
              if (pop[i]->getCPU().state.doneEQU) { EQUCount->AddDatum(1); }
            }
          }
        });
      }
      return *EQUCount;
  }

  /**
   * @brief Retrieves the data monitor tracking the count of organisms with the 'XOR' state.
   *
   * This function ensures that the data monitor for counting organisms whose state indicates 
   * they have performed "XOR" is properly instantiated and updated. On the first call, it initializes the 
   * monitor and registers an update callback that iterates over the population to count relevant organisms.
   *
   * @return emp::DataMonitor<int>& Reference to the data monitor tracking XOR counts.
   */
  emp::DataMonitor<int> & GetXORCountDataNode() {
      if (!XORCount) {
        XORCount.New();
        OnUpdate([this](size_t){
          XORCount->Reset();
          for (size_t i = 0; i < pop.size(); i++) {
            if (IsOccupied(i)) {
              if (pop[i]->getCPU().state.doneXOR) { XORCount->AddDatum(1); }
            }
          }
        });
      }
      return *XORCount;
  }

  /**
   * @brief Retrieves the data monitor tracking the count of organisms with the 'NOR' state.
   *
   * This function ensures that the data monitor for counting organisms whose state indicates 
   * they have performed "NOR" is properly instantiated and updated. On the first call, it initializes the 
   * monitor and registers an update callback that iterates over the population to count relevant organisms.
   *
   * @return emp::DataMonitor<int>& Reference to the data monitor tracking NOR counts.
   */
  emp::DataMonitor<int> & GetNORCountDataNode() {
      if (!NORCount) {
        NORCount.New();
        OnUpdate([this](size_t){
          NORCount->Reset();
          for (size_t i = 0; i < pop.size(); i++) {
            if (IsOccupied(i)) {
              if (pop[i]->getCPU().state.doneNOR) { NORCount->AddDatum(1); }
            }
          }
        });
      }
      return *NORCount;
  }

  /**
   * @brief Retrieves the data monitor tracking the count of organisms with the 'ANDN' state.
   *
   * This function ensures that the data monitor for counting organisms whose state indicates 
   * they have performed "ANDN" is properly instantiated and updated. On the first call, it initializes the 
   * monitor and registers an update callback that iterates over the population to count relevant organisms.
   *
   * @return emp::DataMonitor<int>& Reference to the data monitor tracking ANDN counts.
   */
  emp::DataMonitor<int> & GetANDNCountDataNode() {
      if (!ANDNCount) {
        ANDNCount.New();
        OnUpdate([this](size_t){
          ANDNCount->Reset();
          for (size_t i = 0; i < pop.size(); i++) {
            if (IsOccupied(i)) {
              if (pop[i]->getCPU().state.doneANDN) { ANDNCount->AddDatum(1); }
            }
          }
        });
      }
      return *ANDNCount;
  }

  /**
   * @brief Retrieves the data monitor tracking the count of organisms with the 'OR' state.
   *
   * This function ensures that the data monitor for counting organisms whose state indicates 
   * they have performed "OR" is properly instantiated and updated. On the first call, it initializes the 
   * monitor and registers an update callback that iterates over the population to count relevant organisms.
   *
   * @return emp::DataMonitor<int>& Reference to the data monitor tracking OR counts.
   */
  emp::DataMonitor<int> & GetORCountDataNode() {
      if (!ORCount) {
        ORCount.New();
        OnUpdate([this](size_t){
          ORCount->Reset();
          for (size_t i = 0; i < pop.size(); i++) {
            if (IsOccupied(i)) {
              if (pop[i]->getCPU().state.doneOR) { ORCount->AddDatum(1); }
            }
          }
        });
      }
      return *ORCount;
  }

  /**
   * @brief Retrieves the data monitor tracking the count of organisms with the 'ORN' state.
   *
   * This function ensures that the data monitor for counting organisms whose state indicates 
   * they have performed "ORN" is properly instantiated and updated. On the first call, it initializes the 
   * monitor and registers an update callback that iterates over the population to count relevant organisms.
   *
   * @return emp::DataMonitor<int>& Reference to the data monitor tracking ORN counts.
   */
  emp::DataMonitor<int> & GetORNCountDataNode() {
      if (!ORNCount) {
        ORNCount.New();
        OnUpdate([this](size_t){
          ORNCount->Reset();
          for (size_t i = 0; i < pop.size(); i++) {
            if (IsOccupied(i)) {
              if (pop[i]->getCPU().state.doneORN) { ORNCount->AddDatum(1); }
            }
          }
        });
      }
      return *ORNCount;
  }

  /**
   * @brief Retrieves the data monitor tracking the count of organisms with the 'AND' state.
   *
   * This function ensures that the data monitor for counting organisms whose state indicates 
   * they have performed "AND" is properly instantiated and updated. On the first call, it initializes the 
   * monitor and registers an update callback that iterates over the population to count relevant organisms.
   *
   * @return emp::DataMonitor<int>& Reference to the data monitor tracking AND counts.
   */
  emp::DataMonitor<int> & GetANDCountDataNode() {
      if (!ANDCount) {
        ANDCount.New();
        OnUpdate([this](size_t){
          ANDCount->Reset();
          for (size_t i = 0; i < pop.size(); i++) {
            if (IsOccupied(i)) {
              if (pop[i]->getCPU().state.doneAND) { ANDCount->AddDatum(1); }
            }
          }
        });
      }
      return *ANDCount;
  }

  /**
   * @brief Retrieves the data monitor tracking the count of organisms with the 'NAND' state.
   *
   * This function ensures that the data monitor for counting organisms whose state indicates 
   * they have performed "NAND" is properly instantiated and updated. On the first call, it initializes the 
   * monitor and registers an update callback that iterates over the population to count relevant organisms.
   *
   * @return emp::DataMonitor<int>& Reference to the data monitor tracking NAND counts.
   */
  emp::DataMonitor<int> & GetNANDCountDataNode() {
      if (!NANDCount) {
        NANDCount.New();
        OnUpdate([this](size_t){
          NANDCount->Reset();
          for (size_t i = 0; i < pop.size(); i++) {
            if (IsOccupied(i)) {
              if (pop[i]->getCPU().state.doneNAND) { NANDCount->AddDatum(1); }
            }
          }
        });
      }
      return *NANDCount;
  }

  /**
   * @brief Retrieves the data monitor tracking the count of organisms with the 'NOT' state.
   *
   * This function ensures that the data monitor for counting organisms whose state indicates 
   * they have performed "NOT" is properly instantiated and updated. On the first call, it initializes the 
   * monitor and registers an update callback that iterates over the population to count relevant organisms.
   *
   * @return emp::DataMonitor<int>& Reference to the data monitor tracking NOT counts.
   */
  emp::DataMonitor<int> & GetNOTCountDataNode() {
      if (!NOTCount) {
        NOTCount.New();
        OnUpdate([this](size_t){
          NOTCount->Reset();
          for (size_t i = 0; i < pop.size(); i++) {
            if (IsOccupied(i)) {
              if (pop[i]->getCPU().state.doneNOT) { NOTCount->AddDatum(1); }
            }
          }
        });
      }
      return *NOTCount;
  }

  /**
 * @brief Sets up the data file for logging simulation data.
 *
 * This function is responsible for creating or initializing the data file that will be used 
 * to record simulation metrics and states over time. It may involve specifying file paths, 
 * creating file headers, and defining the structure of the logged data.
 */
  emp::DataFile SetupDataFile(const std::string & filename) {
    auto & file = SetupFile(filename);
    auto & EQUNode = GetEQUCountDataNode();
    auto & XORNode = GetXORCountDataNode();
    auto & NORNode = GetNORCountDataNode();
    auto & ANDNNode = GetANDNCountDataNode();
    auto & ORNode = GetORCountDataNode();
    auto & ORNNode = GetORNCountDataNode();
    auto & ANDNode = GetANDCountDataNode();
    auto & NANDNode = GetNANDCountDataNode();
    auto & NOTNode = GetNOTCountDataNode();
    file.AddVar(update, "update", "Update");
    file.AddTotal(EQUNode, "EQU count", "Orgs that have successfully performed EQU");
    file.AddTotal(XORNode, "XOR count", "Orgs that have successfully performed XOR");
    file.AddTotal(NORNode, "NOR count", "Orgs that have successfully performed NOR");
    file.AddTotal(ANDNNode, "ANDN count", "Orgs that have successfully performed ANDN");
    file.AddTotal(ORNode, "OR count", "Orgs that have successfully performed OR");
    file.AddTotal(ORNNode, "ORN count", "Orgs that have successfully performed ORN");
    file.AddTotal(ANDNode, "AND count", "Orgs that have successfully performed AND");
    file.AddTotal(NANDNode, "NAND count", "Orgs that have successfully performed NAND");
    file.AddTotal(NOTNode, "NOT count", "Orgs that have successfully performed NOT");
    file.PrintHeaderKeys();
    return file;
  }

  /**
   * @brief Processes each organism in the world.
   *
   * This function generates a random permutation of the grid positions and calls the 
   * Process() method on each occupied organism in the shuffled order.
   */
  void CallProcess() {
    emp::vector<size_t> schedule = emp::GetPermutation(GetRandom(), GetSize());
    for (int i : schedule) {
      if (!IsOccupied(i)) {
        continue;
      }
      pop[i]->Process(i);
    }
  }

  /**
   * @brief Updates the state of the world and processes reproduction.
   *
   * This function performs the world update by:
   *  - Calling the base class update to handle standard update tasks.
   *  - Processing each organism by invoking CallProcess().
   *  - Then iterating over the reproduction queue to allow organisms that have signaled reproduction 
   *    to produce offspring. If an organism is found at the queued location and its reproduction check 
   *    succeeds, a new offspring is created via DoBirth().
   */
  void Update() {
    emp::World<Organism>::Update();
    // Process each organism
    CallProcess();
    // Time to allow reproduction for any organisms that ran the reproduce instruction
    for (emp::WorldPosition location : reproduce_queue) {
      if (!IsOccupied(location)) {
        return;
      }
      std::optional<Organism> offspring =
          pop[location.GetIndex()]->CheckReproduction();
      if (offspring.has_value()) {
        DoBirth(offspring.value(), location.GetIndex());
      }
    }
    reproduce_queue.clear();
  }

  /**
   * @brief Evaluates a given output against all registered tasks and updates the organism's state.
   *
   * This function iterates over each Task in the tasks container and calls its CheckOutput
   * method using the provided output value and the organism's last input values. Depending on the 
   * value of the reward parameter, either calculates whether an organism earns points for having
   * completed any of the nine tasks and rewards it accordingly, or calculates whether an organism
   * has completed the EQU task and rewards it accordingly.
   *
   * @param reward A boolean value indicating reward-all or reward-none condition.
   * @param output The output value produced by an organism.
   * @param state The current state of the organism that will be updated based on the task outcomes.
   */
  void CheckOutput(bool reward, uint32_t output, OrgState &state) {
    for (Task* task: tasks) {
        double task_points = task->CheckOutput(output, state.last_inputs);
        if (reward) { state.points += task_points; } // reward-all condition
        else { // reward-none condition
            if (task == tasks[0]) { state.points += task_points; }
            else { state.points += 1.0; }
        }
        if (task_points == 320.0) { state.doneEQU = true; }
        else if (task_points == 161.0) { state.doneXOR = true; }
        else if (task_points == 160.0) { state.doneNOR = true; }
        else if (task_points == 81.0) { state.doneANDN = true; }
        else if (task_points == 80.0) { state.doneOR = true; }
        else if (task_points == 41.0) { state.doneORN = true; }
        else if (task_points == 40.0) { state.doneAND = true; }
        else if (task_points == 21.0) { state.doneNAND = true; }
        else if (task_points == 20.0) { state.doneNOT = true; }
    }
  }

  /**
   * @brief Queues an organism for reproduction at a specified world location.
   *
   * This function adds the provided world position to the reproduction queue. Reproduction is
   * delayed until after all organisms have been processed, avoiding potential conflicts such as
   * a child organism overwriting its parent during the same update cycle.
   *
   * @param location The world position where the reproduction event will occur.
   */
  void ReproduceOrg(emp::WorldPosition location) {
    reproduce_queue.push_back(location);
  }
};

#endif