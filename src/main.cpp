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

int elapsedTime = 40;

void TimerCallback() {
    g_playerManager->SendMsg(HUD_PRINTTALK, "Remaining time: %d seconds\n", elapsedTime);
    print("Remaining time: %d seconds\n", elapsedTime);
    print("UNIX Time: %llu\n", GetTime());
    elapsedTime--;  // decrement elapsedTime.
    if (elapsedTime == 0) {
        timers->DestroyTimer(timerid);
    }
}

void OnBombPlanted(Player *player, unsigned short site) {
    print("%s planted a bomb.\n", player->GetName());
    print("UNIX Time: %llu\n", GetTime());
    elapsedTime = 40;
    timerid = timers->RegisterTimer(1000, TimerCallback);  
    print("Timer registered.\n");
    print("UNIX Time: %llu\n", GetTime());
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