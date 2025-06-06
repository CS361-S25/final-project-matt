#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "OrgState.h"
#include "sgpl/library/OpLibraryCoupler.hpp"
#include "sgpl/library/prefab/ArithmeticOpLibrary.hpp"
#include "sgpl/library/prefab/NopOpLibrary.hpp"
#include "sgpl/operations/flow_global/Anchor.hpp"
#include "sgpl/program/Instruction.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
//#include <_types/_uint32_t.h>

constexpr bool xor_bool = true; // Set to true or false as needed

/**
 * A custom instruction that outputs the value of a register as the (possible)
 * solution to a task, and then gets a new input value and stores it in the same
 * register.
 */
struct IOInstruction {
  template <typename Spec>
  static void run(sgpl::Core<Spec> &core, const sgpl::Instruction<Spec> &inst,
                  const sgpl::Program<Spec> &,
                  typename Spec::peripheral_t &state) noexcept {
    uint32_t output = core.registers[inst.args[0]];
    bool reward = state.world->GetReward();
    state.world->CheckOutput(reward, output, state);

    uint32_t input = sgpl::tlrand.Get().GetUInt();
    core.registers[inst.args[0]] = input;
    state.add_input(input);
  }

  static std::string name() { return "IO"; }
  static size_t prevalence() { return 1; }
};

struct NandInstruction {
  template <typename Spec>
  static void run(sgpl::Core<Spec> &core, const sgpl::Instruction<Spec> &inst,
                  const sgpl::Program<Spec> &,
                  typename Spec::peripheral_t &state) noexcept {
                    uint32_t reg_b = core.registers[inst.args[1]];
                    uint32_t reg_c = core.registers[inst.args[2]];
                    uint32_t nand_val = ~(reg_b & reg_c);

                    core.registers[inst.args[0]] = nand_val;
                  }
  static std::string name() { return "Nand"; }
  static size_t prevalence() { return 1; }
};

struct NotInstruction {
  template <typename Spec>
  static void run(sgpl::Core<Spec> &core, const sgpl::Instruction<Spec> &inst,
                  const sgpl::Program<Spec> &,
                  typename Spec::peripheral_t &state) noexcept {
                    uint32_t reg_b = core.registers[inst.args[1]];
                    uint32_t not_val = ~reg_b;

                    core.registers[inst.args[0]] = not_val;
                  }
  static std::string name() { return "Not"; }
  static size_t prevalence() { return 1; }
};

struct AndInstruction {
  template <typename Spec>
  static void run(sgpl::Core<Spec> &core, const sgpl::Instruction<Spec> &inst,
                  const sgpl::Program<Spec> &,
                  typename Spec::peripheral_t &state) noexcept {
                    uint32_t reg_b = core.registers[inst.args[1]];
                    uint32_t reg_c = core.registers[inst.args[2]];
                    uint32_t and_val = reg_b & reg_c;

                    core.registers[inst.args[0]] = and_val;
                  }
  static std::string name() { return "And"; }
  static size_t prevalence() { return 1; }
};

struct OrnInstruction {
  template <typename Spec>
  static void run(sgpl::Core<Spec> &core, const sgpl::Instruction<Spec> &inst,
                  const sgpl::Program<Spec> &,
                  typename Spec::peripheral_t &state) noexcept {
                    uint32_t reg_b = core.registers[inst.args[1]];
                    uint32_t reg_c = core.registers[inst.args[2]];
                    uint32_t orn_val = reg_b | ~reg_c;

                    core.registers[inst.args[0]] = orn_val;
                  }
  static std::string name() { return "Orn"; }
  static size_t prevalence() { return 1; }
};

struct OrInstruction {
  template <typename Spec>
  static void run(sgpl::Core<Spec> &core, const sgpl::Instruction<Spec> &inst,
                  const sgpl::Program<Spec> &,
                  typename Spec::peripheral_t &state) noexcept {
                    uint32_t reg_b = core.registers[inst.args[1]];
                    uint32_t reg_c = core.registers[inst.args[2]];
                    uint32_t or_val = reg_b | reg_c;

                    core.registers[inst.args[0]] = or_val;
                  }
  static std::string name() { return "Or"; }
  static size_t prevalence() { return 1; }
};

struct AndnInstruction {
  template <typename Spec>
  static void run(sgpl::Core<Spec> &core, const sgpl::Instruction<Spec> &inst,
                  const sgpl::Program<Spec> &,
                  typename Spec::peripheral_t &state) noexcept {
                    uint32_t reg_b = core.registers[inst.args[1]];
                    uint32_t reg_c = core.registers[inst.args[2]];
                    uint32_t andn_val = reg_b & ~reg_c;

                    core.registers[inst.args[0]] = andn_val;
                  }
  static std::string name() { return "Andn"; }
  static size_t prevalence() { return 1; }
};

struct NorInstruction {
  template <typename Spec>
  static void run(sgpl::Core<Spec> &core, const sgpl::Instruction<Spec> &inst,
                  const sgpl::Program<Spec> &,
                  typename Spec::peripheral_t &state) noexcept {
                    uint32_t reg_b = core.registers[inst.args[1]];
                    uint32_t reg_c = core.registers[inst.args[2]];
                    uint32_t nor_val = ~(reg_b | ~reg_c);

                    core.registers[inst.args[0]] = nor_val;
                  }
  static std::string name() { return "Nor"; }
  static size_t prevalence() { return 1; }
};

struct XorInstruction {
  template <typename Spec>
  static void run(sgpl::Core<Spec> &core, const sgpl::Instruction<Spec> &inst,
                  const sgpl::Program<Spec> &,
                  typename Spec::peripheral_t &state) noexcept {
                    uint32_t reg_b = core.registers[inst.args[1]];
                    uint32_t reg_c = core.registers[inst.args[2]];
                    uint32_t xor_val = reg_b ^ reg_c;

                    core.registers[inst.args[0]] = xor_val;
                  }
  static std::string name() { return "Xor"; }
  static size_t prevalence() { return 1; }
};

/**
 * A custom instruction that attempts to reproduce and produce a child organism,
 * if this organism has enough points.
 */
struct ReproduceInstruction {
  template <typename Spec>
  static void run(sgpl::Core<Spec> &core, const sgpl::Instruction<Spec> &inst,
                  const sgpl::Program<Spec> &,
                  typename Spec::peripheral_t &state) noexcept {
    if (state.points > 189) {
      state.world->ReproduceOrg(state.current_location);
      state.points = 0;
    }
    
  }

  static std::string name() { return "Reproduce"; }
  static size_t prevalence() { return 1; }
};


using Library = std::conditional_t<
    xor_bool,
    sgpl::OpLibraryCoupler<sgpl::NopOpLibrary, sgpl::BitwiseShift, sgpl::Increment, sgpl::Decrement,
                           sgpl::Add, sgpl::Subtract, sgpl::global::JumpIfNot, sgpl::local::JumpIfNot, sgpl::global::Anchor, IOInstruction, NandInstruction,
                           //NotInstruction, AndInstruction, OrnInstruction, OrInstruction, AndnInstruction, NorInstruction,
                           XorInstruction, ReproduceInstruction>,
    sgpl::OpLibraryCoupler<sgpl::NopOpLibrary, sgpl::BitwiseShift, sgpl::Increment, sgpl::Decrement,
                           sgpl::Add, sgpl::Subtract, sgpl::global::JumpIfNot, sgpl::local::JumpIfNot, sgpl::global::Anchor, IOInstruction, NandInstruction,
                           //NotInstruction, AndInstruction, OrnInstruction, OrInstruction, AndnInstruction, NorInstruction,
                           ReproduceInstruction>
>;

using Spec = sgpl::Spec<Library, OrgState>;

#endif  