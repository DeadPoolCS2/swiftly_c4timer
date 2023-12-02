#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <swiftly/database.h>
#include <swiftly/commands.h>
#include <swiftly/configuration.h>
#include <swiftly/logger.h>
#include <swiftly/timers.h>

Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Database *db = nullptr;
Commands *commands = nullptr;
Configuration *config = nullptr;
Logger *logger = nullptr;
Timers *timers = nullptr;

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);

    server = new Server();
    g_playerManager = new PlayerManager();
    commands = new Commands(pluginName);
    config = new Configuration();
    logger = new Logger(mainFilePath, pluginName);
    timers = new Timers();
}

void OnPluginStart()
{
}

void Timer()
{
    print("There are %02d players on the server.\n", g_playerManager->GetPlayers());
}

unsigned long long timerid;

int elapsedTime = 0;  // Declare and initialize elapsedTime

void TimerCallback() {
    elapsedTime++;  // Increment elapsedTime
    print("Elapsed time: %d seconds\n", elapsedTime);
    if (elapsedTime == 40) {
        timers->DestroyTimer(timerid);  // Destroy the timer after 40 seconds
    }
}

void OnBombPlanted(Player *player, unsigned short site) {
    print("%s planted a bomb.\n", player->GetName());
    timerid = timers->RegisterTimer(1000, TimerCallback);  // Register a timer that triggers every second
    print("Timer registered.\n");
}

void OnPluginStop()
{
    timers->UnregisterTimers();
}

const char *GetPluginAuthor()
{
    return "";
}

const char *GetPluginVersion()
{
    return "1.0.0";
}

const char *GetPluginName()
{
    return "c4timer";
}

const char *GetPluginWebsite()
{
    return "";
}