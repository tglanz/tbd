#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <volk.h>
#include <vulkan/vulkan.h>

int SDL_main(int argc, char* argv[]) {
    // Initialize SDL (for Vulkan)
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        spdlog::error("SDL_Init failed: {}", SDL_GetError());
        return -1;
    }

    // Initialize Vulkan using volk
    if (volkInitialize() != VK_SUCCESS) {
        spdlog::error("volkInitialize failed!");
        SDL_Quit();
        return -1;
    }

    // Create a simple glm vector
    glm::vec3 vec(1.0f, 2.0f, 3.0f);
    spdlog::info("Created glm vector: ({}, {}, {})", vec.x, vec.y, vec.z);

    // Log a message using spdlog
    spdlog::info("Hello from Vulkan + SDL2 + glm + volk!");

    // Cleanup SDL
    SDL_Quit();

    return 0;
}

