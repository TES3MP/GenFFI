/**
 * @file api.h
 * @brief External API for plugins.
 * @authors koncord
 * @date 08.01.19
 */

#ifndef NEWNATIVE_API_H
#define NEWNATIVE_API_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "Platform.h"
#endif

#include "CTypes.h"

#if !(defined _HOST || defined _GENFFI)

/** @addtogroup PluginCallbacks Plugin Callbacks
 *  @brief Those callbacks can be implemented by plugin.
 * @{
 */

/*! @brief This function must be implemented by every plugin.
 *
 * Called by the server on initialization process, there is no possible to call any API functions in this function.
 * If this function returns 0, PluginFree() will be called
 *
 * @return 1 on success 0 on fail
 */
EXPORT_FUNCTION int CDECL PluginInit();

/*! @brief This function must be implemented by every plugin.
 *
 * Called by the server on qutitting or failing to initialize plugin by PluginInit()
 */
EXPORT_FUNCTION void CDECL PluginFree();

EXPORT_FUNCTION void CDECL OnServerInit();
EXPORT_FUNCTION void CDECL OnServerPostInit();
EXPORT_FUNCTION void CDECL OnServerExit(bool code);
EXPORT_FUNCTION void CDECL OnPlayerConnect(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerDisconnect(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerDeath(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerResurrect(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerCellChange(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerAttribute(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerSkill(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerLevel(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerBounty(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerReputation(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerEquipment(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerInventory(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerJournal(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerFaction(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerShapeshift(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerQuickKeys(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerTopic(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerDisposition(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerBook(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerItemUse(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerMiscellaneous(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerInput(PlayerId pid);
EXPORT_FUNCTION void CDECL OnPlayerRest(PlayerId pid);
EXPORT_FUNCTION void CDECL OnRecordDynamic(PlayerId pid);

EXPORT_FUNCTION void CDECL OnCellLoad(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnCellUnload(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnCellDeletion(const char *cellDescription);

EXPORT_FUNCTION void CDECL OnContainer(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnDoorState(PlayerId pid, const char *cellDescription);

EXPORT_FUNCTION void CDECL OnObjectActivate(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnObjectPlace(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnObjectState(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnObjectSpawn(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnObjectDelete(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnObjectLock(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnObjectScale(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnObjectTrap(PlayerId pid, const char *cellDescription);

EXPORT_FUNCTION void CDECL OnVideoPlay(PlayerId pid, const char *cellDescription);

EXPORT_FUNCTION void CDECL OnActorList(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnActorEquipment(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnActorAI(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnActorDeath(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnActorCellChange(PlayerId pid, const char *cellDescription);
EXPORT_FUNCTION void CDECL OnActorTest(PlayerId pid, const char *cellDescription);

EXPORT_FUNCTION void CDECL OnPlayerSendMessage(PlayerId pid, const char *message);

EXPORT_FUNCTION void CDECL OnPlayerEndCharGen(PlayerId pid);
EXPORT_FUNCTION void CDECL OnGUIAction(PlayerId pid, const char *data);
EXPORT_FUNCTION void CDECL OnWorldKillCount(PlayerId pid);
EXPORT_FUNCTION void CDECL OnWorldMap(PlayerId pid);
EXPORT_FUNCTION void CDECL OnWorldWeather(PlayerId pid);
EXPORT_FUNCTION void CDECL OnMpNumIncrement(int mpNum);
EXPORT_FUNCTION void CDECL OnRequestPluginList();

/** @}*/
#endif

#endif //NEWNATIVE_API_H
