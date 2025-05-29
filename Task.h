#ifndef TASK_H
#define TASK_H

//#include <_types/_uint32_t.h>
#include <cmath>
#include <string>
#include <iostream>

/**
 * The interface for a task that organisms can complete.
 */
class Task {
public:
  /**
   * Given the output value the organism produced, and the last four inputs it
   * received, this function returns the points the organism should get for
   * completing this task (or 0 if the task was not completed.)
   */
  virtual double CheckOutput(uint32_t output, uint32_t inputs[4]) = 0;

  /** Returns the human-readable name of the task. */
  virtual std::string name() const = 0;
};

class NOT : public Task {

    public:
        /**
         * @brief Evaluates the given output against the expected result based on the task's criterion.
         *
         * This function processes an organism's output by comparing it against values derived from the input array.
         * For instance, in a SquareTask, it computes a square value from the inputs and if the absolute difference 
         * between the output and the computed value is less than 0.001, it returns a high score (50.0). Otherwise,
         * it returns a default value (1.0).
         *
         * @param output The output value produced by an organism.
         * @param inputs An array of input values used for evaluation.
         * @return double The score awarded based on how closely the output matches the expected value.
         */
        double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
            // did they calculate NOT of a number?
            for (int i = 0; i < 4; i++) {
            uint32_t not_val = ~inputs[i]; //~ is bitwise NOT in C++
                if (not_val == output) {
                    // 10 points for success
                    return 20.0;
                }
            }
            // 0 points for failure
            return 1.0;
        }

        /**
         * @brief Returns the name of the task.
         *
         * This function provides a string identifier for the task, which can be used for logging, debugging, 
         * or display purposes.
         *
         * @return std::string The name of the task.
         */
        std::string name() const override { return "NOT"; }
};

class NAND : public Task {

    public:
        /**
         * @brief Evaluates the given output against the expected result based on the task's criterion.
         *
         * This function processes an organism's output by comparing it against values derived from the input array.
         * For instance, in a SquareTask, it computes a square value from the inputs and if the absolute difference 
         * between the output and the computed value is less than 0.001, it returns a high score (50.0). Otherwise,
         * it returns a default value (1.0).
         *
         * @param output The output value produced by an organism.
         * @param inputs An array of input values used for evaluation.
         * @return double The score awarded based on how closely the output matches the expected value.
         */
        double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
            // did they calculate NOT of a number?
            for (int i = 0; i < 3; i++) {
                int plusOne = i + 1;
                uint32_t val = inputs[i]; //~ is bitwise NOT in C++
                uint32_t val_2 = inputs[plusOne];
                uint32_t nand_val = ~(val & val_2);
                if (nand_val == output) {
                    // 10 points for success
                    return 21.0;
                }
            }
            // 0 points for failure
            return 1.0;
        }

        /**
         * @brief Returns the name of the task.
         *
         * This function provides a string identifier for the task, which can be used for logging, debugging, 
         * or display purposes.
         *
         * @return std::string The name of the task.
         */
        std::string name() const override { return "NAND"; }
};

class AND : public Task {

    public:
        /**
         * @brief Evaluates the given output against the expected result based on the task's criterion.
         *
         * This function processes an organism's output by comparing it against values derived from the input array.
         * For instance, in a SquareTask, it computes a square value from the inputs and if the absolute difference 
         * between the output and the computed value is less than 0.001, it returns a high score (50.0). Otherwise,
         * it returns a default value (1.0).
         *
         * @param output The output value produced by an organism.
         * @param inputs An array of input values used for evaluation.
         * @return double The score awarded based on how closely the output matches the expected value.
         */
        double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
            // did they calculate NOT of a number?
            for (int i = 0; i < 3; i++) {
                int plusOne = i + 1;
                uint32_t val = inputs[i]; //~ is bitwise NOT in C++
                uint32_t val_2 = inputs[plusOne];
                uint32_t and_val = val & val_2;
                if (and_val == output) {
                    // 10 points for success
                    return 40.0;
                }
            // 0 points for failure
            }
            return 1.0;
        }

        /**
         * @brief Returns the name of the task.
         *
         * This function provides a string identifier for the task, which can be used for logging, debugging, 
         * or display purposes.
         *
         * @return std::string The name of the task.
         */
        std::string name() const override { return "AND"; }
};

class ORN : public Task {

    public:
        /**
         * @brief Evaluates the given output against the expected result based on the task's criterion.
         *
         * This function processes an organism's output by comparing it against values derived from the input array.
         * For instance, in a SquareTask, it computes a square value from the inputs and if the absolute difference 
         * between the output and the computed value is less than 0.001, it returns a high score (50.0). Otherwise,
         * it returns a default value (1.0).
         *
         * @param output The output value produced by an organism.
         * @param inputs An array of input values used for evaluation.
         * @return double The score awarded based on how closely the output matches the expected value.
         */
        double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
            // did they calculate NOT of a number?
            for (int i = 0; i < 3; i++) {
                int plusOne = i + 1;
                uint32_t val = inputs[i]; //~ is bitwise NOT in C++
                uint32_t val_2 = inputs[plusOne];
                uint32_t orn_val = val | ~val_2;
                if (orn_val == output) {
                    // 10 points for success
                    return 41.0;
                }
            // 0 points for failure
            }
            return 1.0;
        }

        /**
         * @brief Returns the name of the task.
         *
         * This function provides a string identifier for the task, which can be used for logging, debugging, 
         * or display purposes.
         *
         * @return std::string The name of the task.
         */
        std::string name() const override { return "ORN"; }
};

class OR : public Task {

    public:
        /**
         * @brief Evaluates the given output against the expected result based on the task's criterion.
         *
         * This function processes an organism's output by comparing it against values derived from the input array.
         * For instance, in a SquareTask, it computes a square value from the inputs and if the absolute difference 
         * between the output and the computed value is less than 0.001, it returns a high score (50.0). Otherwise,
         * it returns a default value (1.0).
         *
         * @param output The output value produced by an organism.
         * @param inputs An array of input values used for evaluation.
         * @return double The score awarded based on how closely the output matches the expected value.
         */
        double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
            // did they calculate NOT of a number?
            for (int i = 0; i < 3; i++) {
                int plusOne = i + 1;
                uint32_t val = inputs[i]; //~ is bitwise NOT in C++
                uint32_t val_2 = inputs[plusOne];
                uint32_t or_val = val | val_2;
                if (or_val == output) {
                    // 10 points for success
                    return 80.0;
                }
            // 0 points for failure
            }
            return 1.0;
        }

        /**
         * @brief Returns the name of the task.
         *
         * This function provides a string identifier for the task, which can be used for logging, debugging, 
         * or display purposes.
         *
         * @return std::string The name of the task.
         */
        std::string name() const override { return "OR"; }
};

class ANDN : public Task {

    public:
        /**
         * @brief Evaluates the given output against the expected result based on the task's criterion.
         *
         * This function processes an organism's output by comparing it against values derived from the input array.
         * For instance, in a SquareTask, it computes a square value from the inputs and if the absolute difference 
         * between the output and the computed value is less than 0.001, it returns a high score (50.0). Otherwise,
         * it returns a default value (1.0).
         *
         * @param output The output value produced by an organism.
         * @param inputs An array of input values used for evaluation.
         * @return double The score awarded based on how closely the output matches the expected value.
         */
        double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
            // did they calculate NOT of a number?
            for (int i = 0; i < 3; i++) {
                int plusOne = i + 1;
                uint32_t val = inputs[i]; //~ is bitwise NOT in C++
                uint32_t val_2 = inputs[plusOne];
                uint32_t andn_val = val & ~val_2;
                if (andn_val == output) {
                    // 10 points for success
                    return 81.0;
                }
            // 0 points for failure
            }
            return 1.0;
        }

        /**
         * @brief Returns the name of the task.
         *
         * This function provides a string identifier for the task, which can be used for logging, debugging, 
         * or display purposes.
         *
         * @return std::string The name of the task.
         */
        std::string name() const override { return "ANDN"; }
};

class NOR : public Task {

    public:
        /**
         * @brief Evaluates the given output against the expected result based on the task's criterion.
         *
         * This function processes an organism's output by comparing it against values derived from the input array.
         * For instance, in a SquareTask, it computes a square value from the inputs and if the absolute difference 
         * between the output and the computed value is less than 0.001, it returns a high score (50.0). Otherwise,
         * it returns a default value (1.0).
         *
         * @param output The output value produced by an organism.
         * @param inputs An array of input values used for evaluation.
         * @return double The score awarded based on how closely the output matches the expected value.
         */
        double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
            // did they calculate NOT of a number?
            for (int i = 0; i < 3; i++) {
                int plusOne = i + 1;
                uint32_t val = inputs[i]; //~ is bitwise NOT in C++
                uint32_t val_2 = inputs[plusOne];
                uint32_t nor_val = ~(val | val_2);
                if (nor_val == output) {
                    // 10 points for success
                    return 160.0;
                }
            // 0 points for failure
            }
            return 1.0;
        }

        /**
         * @brief Returns the name of the task.
         *
         * This function provides a string identifier for the task, which can be used for logging, debugging, 
         * or display purposes.
         *
         * @return std::string The name of the task.
         */
        std::string name() const override { return "NOR"; }
};

class XOR : public Task {

    public:
        /**
         * @brief Evaluates the given output against the expected result based on the task's criterion.
         *
         * This function processes an organism's output by comparing it against values derived from the input array.
         * For instance, in a SquareTask, it computes a square value from the inputs and if the absolute difference 
         * between the output and the computed value is less than 0.001, it returns a high score (50.0). Otherwise,
         * it returns a default value (1.0).
         *
         * @param output The output value produced by an organism.
         * @param inputs An array of input values used for evaluation.
         * @return double The score awarded based on how closely the output matches the expected value.
         */
        double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
            // did they calculate NOT of a number?
            for (int i = 0; i < 3; i++) {
                int plusOne = i + 1;
                uint32_t val = inputs[i]; //~ is bitwise NOT in C++
                uint32_t val_2 = inputs[plusOne];
                uint32_t xor_val = val ^ val_2;
                if (xor_val == output) {
                    // 10 points for success
                    return 161.0;
                }
            // 0 points for failure
            }
            return 1.0;
        }

        /**
         * @brief Returns the name of the task.
         *
         * This function provides a string identifier for the task, which can be used for logging, debugging, 
         * or display purposes.
         *
         * @return std::string The name of the task.
         */
        std::string name() const override { return "XOR"; }
};

class EQU : public Task {

    public:
        /**
         * @brief Evaluates the given output against the expected result based on the task's criterion.
         *
         * This function processes an organism's output by comparing it against values derived from the input array.
         * For instance, in a SquareTask, it computes a square value from the inputs and if the absolute difference 
         * between the output and the computed value is less than 0.001, it returns a high score (50.0). Otherwise,
         * it returns a default value (1.0).
         *
         * @param output The output value produced by an organism.
         * @param inputs An array of input values used for evaluation.
         * @return double The score awarded based on how closely the output matches the expected value.
         */
        double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
            // did they calculate NOT of a number?
            for (int i = 0; i < 3; i++) {
                int plusOne = i + 1;
                uint32_t val = inputs[i]; //~ is bitwise NOT in C++
                uint32_t val_2 = inputs[plusOne];
                uint32_t equ_val = ~(val ^ val_2);
                if (equ_val == output) {
                    // 10 points for success
                    return 320.0;
                }
            // 0 points for failure
            }
            return 1.0;
        }

        /**
         * @brief Returns the name of the task.
         *
         * This function provides a string identifier for the task, which can be used for logging, debugging, 
         * or display purposes.
         *
         * @return std::string The name of the task.
         */
        std::string name() const override { return "EQU"; }
};

#endif