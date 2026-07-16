#include "libgpu.h"
#include "../../lib/CD.h"
#include "../../lib/GPU.h"
#include "../../lib/Controller.h"
#include "../../lib/Heap.h"
#include "../../lib/GTE.h"

#define NUM_VERTICES 8
#define NUM_FACES 6

static Controller *controller;

static SVECTOR vertices[] = {
    {-128, -128, -128},
    {128, -128, -128},
    {128, -128, 128},
    {-128, -128, 128},
    {-128, 128, -128},
    {128, 128, -128},
    {128, 128, 128},
    {-128, 128, 128}
};

static int16_t faces[] = {
    3, 2, 0, 1,  // Top Quad
    0, 1, 4, 5,  // Front Quad
    4, 5, 7, 6,  // Bottom Quad
    1, 2, 5, 6,  // Right Quad
    2, 3, 6, 7,  // Back Quad
    3, 0, 7, 4,  // Left Quad
};

static SVECTOR rotation = {0, 0, 0};
static VECTOR translation = {0, 0, 900};
static VECTOR scale = {ONE, ONE, ONE};

static MATRIX world_matrix = {0};

int main() {
    // Initialize system
    GPU_Init();

    Controller_Init();
    controller = Controller_Read(CONTROLLER_PAD_1);

    Heap_Init();
    CD_Init();
    // Load your resources here


    // Cappy is a sprite sheet, we want one frame only
    while (1) {
        // Clear ot
        GPU_ClearOT();
        FntPrint("rotating-cube\n");

        CONTROLLER_LOG_INPUT(controller); // Just for debugging purposes, remove later on!

        // Add your update and draw function calls here

        GPU_Display();
    }
}







