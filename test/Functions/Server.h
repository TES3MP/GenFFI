#ifndef OPENMW_SERVERAPI_HPP
#define OPENMW_SERVERAPI_HPP

#include "../api.h"

NAMESPACE_BEGIN(ServerFunctions)
    /**
    * \brief Shut down the server.
    *
    * \param code The shutdown code.
    * \return void
    */
    API_FUNCTION void CDECL StopServer(int code) NOEXCEPT;

    /**
    * \brief Kick a certain player from the server.
    *
    * \param pid The player ID.
    * \return void
    */
    API_FUNCTION void CDECL Kick(PlayerId pid) NOEXCEPT;

    /**
    * \brief Ban a certain IP address from the server.
    *
    * \param ipAddress The IP address.
    * \return void
    */
    API_FUNCTION void CDECL BanAddress(const char *ipAddress) NOEXCEPT;

    /**
    * \brief Unban a certain IP address from the server.
    *
    * \param ipAddress The IP address.
    * \return void
    */
    API_FUNCTION void CDECL UnbanAddress(const char *ipAddress) NOEXCEPT;

    /**
    * \brief Get the type of the operating system used by the server.
    *
    * Note: Currently, the type can be "Windows", "Linux", "OS X" or "Unknown OS".
    *
    * \return The type of the operating system.
    */
    API_FUNCTION const char *CDECL GetOperatingSystemType() NOEXCEPT;

    /**
    * \brief Get the architecture type used by the server.
    *
    * Note: Currently, the type can be "64-bit", "32-bit", "ARMv#" or "Unknown architecture".
    *
    * \return The architecture type.
    */
    API_FUNCTION const char *CDECL GetArchitectureType() NOEXCEPT;

    /**
    * \brief Get the TES3MP version of the server.
    *
    * \return The server version.
    */
    API_FUNCTION const char *CDECL GetServerVersion() NOEXCEPT;

    /**
    * \brief Get the protocol version of the server.
    *
    * \return The protocol version.
    */
    API_FUNCTION const char *CDECL GetProtocolVersion() NOEXCEPT;

    /**
    * \brief Get the average ping of a certain player.
    *
    * \param pid The player ID.
    * \return The average ping.
    */
    API_FUNCTION int CDECL GetAvgPing(PlayerId pid) NOEXCEPT;

    /**
    * \brief Get the IP address of a certain player.
    *
    * \param pid The player ID.
    * \return The IP address.
    */
    API_FUNCTION const CDECL char* GetIP(PlayerId pid) NOEXCEPT;

    /**
     * \brief Get the port used by the server.
     *
     * \return Port
     */
    API_FUNCTION unsigned short CDECL GetPort() NOEXCEPT;

    /**
     * \brief Get the maximum number of players.
     *
     * \return Max players
     */
    API_FUNCTION unsigned int CDECL GetMaxPlayers() NOEXCEPT;

    /**
     * \brief Checking if the server requires a password to connect.
     *
     * @return
     */
    API_FUNCTION bool CDECL HasPassword() NOEXCEPT;

    /**
    * \brief Get the plugin enforcement state of the server.
    *
    * If true, clients are required to use the same plugins as set for the server.
    *
    * \return The enforcement state.
    */
    API_FUNCTION bool CDECL GetPluginEnforcementState() NOEXCEPT;

    /**
    * \brief Get the script error ignoring state of the server.
    *
    * If true, script errors will not crash the server.
    *
    * \return The script error ignoring state.
    */
    API_FUNCTION bool CDECL GetScriptErrorIgnoringState() NOEXCEPT;

    /**
    * \brief Set the game mode of the server, as displayed in the server browser.
    *
    * \param name The new game mode.
    * \return void
    */
    API_FUNCTION void CDECL SetGameMode(const char* gameMode) NOEXCEPT;

    /**
    * \brief Set the name of the server, as displayed in the server browser.
    *
    * \param name The new name.
    * \return void
    */
    API_FUNCTION void CDECL SetHostname(const char* name) NOEXCEPT;

    /**
    * \brief Set the password required to join the server.
    *
    * \param password The password.
    * \return void
    */
    API_FUNCTION void CDECL SetServerPassword(const char *password) NOEXCEPT;

    /**
    * \brief Set the plugin enforcement state of the server.
    *
    * If true, clients are required to use the same plugins as set for the server.
    *
    * \param state The new enforcement state.
    * \return void
    */
    API_FUNCTION void CDECL SetPluginEnforcementState(bool state) NOEXCEPT;

    /**
    * \brief Set whether script errors should be ignored or not.
    *
    * If true, script errors will not crash the server, but could have any number
    * of unforeseen consequences, which is why this is a highly experimental
    * setting.
    *
    * \param state The new script error ignoring state.
    * \return void
    */
    API_FUNCTION void CDECL SetScriptErrorIgnoringState(bool state) NOEXCEPT;

    /**
    * \brief Set a rule string for the server details displayed in the server browser.
    *
    * \param key The name of the rule.
    * \param value The string value of the rule.
    * \return void
    */
    API_FUNCTION void CDECL SetRuleString(const char *key, const char *value) NOEXCEPT;

    /**
    * \brief Set a rule value for the server details displayed in the server browser.
    *
    * \param key The name of the rule.
    * \param value The numerical value of the rule.
    * \return void
    */
    API_FUNCTION void CDECL SetRuleValue(const char *key, double value) NOEXCEPT;

    /**
     * \brief Adds plugins to the internal server structure to validate players.
     * @param pluginName Name with extension of the plugin or master file.
     * @param hash Hash string
     */
    API_FUNCTION void CDECL AddPluginHash(const char *pluginName, const char *hash) NOEXCEPT;

    API_FUNCTION const char *CDECL GetModDir() NOEXCEPT;
    API_FUNCTION const char *CDECL GetPluginDir() NOEXCEPT;
NAMESPACE_END()

#endif //OPENMW_SERVERAPI_HPP
