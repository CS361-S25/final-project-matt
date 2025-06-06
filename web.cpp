#define UIT_VENDORIZE_EMP
#define UIT_SUPPRESS_MACRO_INSEEP_WARNINGS

#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/Document.hpp"
#include "emp/web/web.hpp"
#include "emp/config/ArgManager.hpp"
#include "emp/prefab/ConfigPanel.hpp"
#include "emp/web/UrlParams.hpp"

#include "World.h"
#include "Org.h"
#include "ConfigSetup.h"

emp::web::Document doc("target");
emp::web::Document settings("settings");
emp::web::Document buttons("buttons");
emp::web::Document text("text");
MyConfigType config;

class AEAnimator : public emp::web::Animate {

    // arena width and height
    const int num_h_boxes = 60;
    const int num_w_boxes = 60;
    const double RECT_SIDE = 5;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};
    emp::Random random{config.SEED()};
    OrgWorld world{random};

    emp::web::Canvas canvas{width, height, "canvas"};

    public:

    AEAnimator() {
        // apply configuration query params and config files to config
        auto specs = emp::ArgManager::make_builtin_specs(&config);
        emp::ArgManager am(emp::web::GetUrlParams(), specs);
        am.UseCallbacks();
        if (am.HasUnused()) std::exit(EXIT_FAILURE);

        // setup configuration panel
        emp::prefab::ConfigPanel config_panel(config);
        config_panel.ExcludeSetting("FILE_NAME");
        config_panel.ExcludeSetting("UPDATES");
        settings << config_panel;
        random.ResetSeed(config.SEED());
    
        // shove canvas into the div
        // along with a control button
        doc << canvas;
        buttons << GetToggleButton("Toggle");
        buttons << GetStepButton("Step");
        text << "This is a visual representation of a world containing 3600 organisms in a 60 x 60\
        grid, in which the organisms can evolve to perform logic tasks of increasing complexity. A black\
        square represents an organism that has not completed any task. If an organism has complete a task,\
        the color of its most difficult task will be shown. The colors, in ascending order of difficulty, are:\
        NOT - brown, NAND - red, AND - orange, ORN - yellow, OR - green, ANDN - teal, NOR - blue, XOR - purple,\
        EQU - cyan. There are two experiments that can be performed. One uses the 'Reward' slider, which\
        allows you to switch rewards from 'on' (where more complex tasks are rewarded with more points), and 'off'\
        (where all tasks are rewarded equally). The other experiment cannot be carried out using config sliders,\
        since the changes necessary must be evaluated at compile time rather than at runtime. In the 'Instructions.h'\
        file, the xor_bool can be manipulated to allow organisms to either only have the NAND instruction built into\
        their genomes or to have both NAND and XOR built in. Change the seed slider to run multiple trials for the\
        same treatment.";

        world.Resize(num_h_boxes,num_w_boxes);
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);

        for (int i = 0; i < 3600; i++) {
            Organism* new_org = new Organism(&world);
            world.AddOrgAt(new_org, i);
        }
    }

    /**
     * @brief Renders a cell on the canvas based on the organism's current state.
     *
     * Depending on the flags set in cur_state, this function draws a cell with a color that represents
     * the state of an organism at the given grid position (x, y). The colors correspond to different properties
     * (i.e. squared is green, doubled is red, etc.). If no flag is set, a black rectangle is drawn. Called by
     * DoFrame.
     *
     * @param cur_state The current state of the organism containing flags such as hasSquared, hasDoubled, etc.
     * @param x The x-coordinate on the grid.
     * @param y The y-coordinate on the grid.
     */
    void CheckState(OrgState cur_state, int x, int y) {
        if (cur_state.doneEQU) {
            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "cyan", "black");
        } else if (cur_state.doneXOR) {
            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "purple", "black");
        } else if (cur_state.doneNOR) {
            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "blue", "black");
        } else if (cur_state.doneANDN) {
            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "teal", "black");
        } else if (cur_state.doneOR) {
            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "green", "black");
        } else if (cur_state.doneORN) {
            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "yellow", "black");
        } else if (cur_state.doneAND) {
            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "orange", "black");
        } else if (cur_state.doneNAND) {
            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "red", "black");
        } else if (cur_state.doneNOT) {
            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "brown", "black");
        } else {
            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "black");
        }
    }

    /**
     * @brief Executes a grid update; overrides the base DoFrame function.
     *
     * This function is responsible for updating the state of the animation for each frame.
     * Iterates through each cell individually to check what color it should be.
     */
    void DoFrame() override {
        canvas.Clear();
        world.Update();

        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++){
            for (int y = 0; y < num_h_boxes; y++) {
                OrgState cur_state = world.GetPopulation()[org_num]->getCPU().state;
                CheckState(cur_state, x, y);
                org_num++;
            }
        }
    }
};

AEAnimator animator;

int main() {animator.Step();}
