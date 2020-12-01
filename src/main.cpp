#include "main.hpp"
#include <chrono>
using namespace GlobalNamespace;

// Stores the ID and version of our mod, and is sent to the modloader upon startup
static ModInfo modInfo;


// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
const Logger& getLogger() {
    static const Logger logger(modInfo);
    return logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = "unhealthyandunsafe";
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

MAKE_HOOK_OFFSETLESS(HealthWarningFlowCoordinator_DidActivate, void, HealthWarningFlowCoordinator* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    HealthWarningFlowCoordinator_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    self->GoToNextScene();
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    INSTALL_HOOK_OFFSETLESS(HealthWarningFlowCoordinator_DidActivate, il2cpp_utils::FindMethodUnsafe("", "HealthWarningFlowCoordinator", "DidActivate", 3));
    getLogger().info("Installed all hooks!");
}
