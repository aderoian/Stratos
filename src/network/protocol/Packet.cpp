/*
 *
 *               _____  _                 _
 *              /  ___|| |               | |
 *              \ `--. | |_  _ __   __ _ | |_   ___   ___
 *               `--. \| __|| '__| / _` || __| / _ \ / __|
 *              /\__/ /| |_ | |   | (_| || |_ | (_) |\__ \
 *              \____/  \__||_|    \__,_| \__| \___/ |___/
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Copyright (C) 2025 Armen Deroian
 *
 */

#include "Packet.h"

#include "PacketCodec.h"

#define REGISTER_CLIENTBOUND(state, clazz) \
    registerPacket({state, Clientbound, clazz::ID}, [] { return std::make_unique<clazz>(); })
#define REGISTER_SERVERBOUND(state, clazz) \
    registerPacket({state, Serverbound, clazz::ID}, [] { return std::make_unique<clazz>(); })

void stratos::PacketRegistry::setup() {
    // Handshaking Packets
    REGISTER_SERVERBOUND(ProtocolState::Handshaking, ClientHandshake);
    REGISTER_SERVERBOUND(ProtocolState::Handshaking, LegacyServerListPing);
    REGISTER_CLIENTBOUND(ProtocolState::Handshaking, LegacyServerListPong);

    // Status Packets
    REGISTER_SERVERBOUND(ProtocolState::Status, StatusRequest);
    REGISTER_SERVERBOUND(ProtocolState::Status, PingRequest);
    REGISTER_CLIENTBOUND(ProtocolState::Status, StatusResponse);
    REGISTER_CLIENTBOUND(ProtocolState::Status, PongResponse);

    // Login Packets
    REGISTER_SERVERBOUND(ProtocolState::Login, LoginStart);
    REGISTER_SERVERBOUND(ProtocolState::Login, EncryptionResponse);
    REGISTER_SERVERBOUND(ProtocolState::Login, LoginPluginResponse);
    REGISTER_SERVERBOUND(ProtocolState::Login, LoginAcknowledge);
    REGISTER_SERVERBOUND(ProtocolState::Login, LoginCookieResponse);
    REGISTER_CLIENTBOUND(ProtocolState::Login, LoginDisconnect);
    REGISTER_CLIENTBOUND(ProtocolState::Login, EncryptionRequest);
    REGISTER_CLIENTBOUND(ProtocolState::Login, LoginSuccess);
    REGISTER_CLIENTBOUND(ProtocolState::Login, SetCompression);
    REGISTER_CLIENTBOUND(ProtocolState::Login, LoginPluginRequest);
    REGISTER_CLIENTBOUND(ProtocolState::Login, LoginCookieRequest);


    // Configuration Packets
    REGISTER_SERVERBOUND(ProtocolState::Configuration, ConfigurationClientInformation);
    REGISTER_SERVERBOUND(ProtocolState::Configuration, ConfigurationCookieResponse);
    REGISTER_SERVERBOUND(ProtocolState::Configuration, ConfigurationServerPluginMessage);
    REGISTER_SERVERBOUND(ProtocolState::Configuration, AcknowledgeFinishConfiguration);
    REGISTER_SERVERBOUND(ProtocolState::Configuration, ConfigurationServerboundKeepAlive);
    REGISTER_SERVERBOUND(ProtocolState::Configuration, ConfigurationPong);
    REGISTER_SERVERBOUND(ProtocolState::Configuration, ConfigurationResourcePackResponse);
    REGISTER_SERVERBOUND(ProtocolState::Configuration, ServerboundKnownPacks);

    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ConfigurationCookieRequest);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ConfigurationClientboundPluginMessage);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ConfigurationDisconnect);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, FinishConfiguration);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ConfigurationClientboundKeepAlive);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ConfigurationPing);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ResetChat);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, RegistryDataPacket);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ConfigurationRemoveRemoveResourcePack);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ConfigurationAddResourcePack);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ConfigurationStoreCookie);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ConfigurationTransfer);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, FeatureFlags);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ConfigurationUpdateTags);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ClientboundKnownPacks);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ConfigurationCustomReportDetails);
    REGISTER_CLIENTBOUND(ProtocolState::Configuration, ConfigurationServerLinks);

    // Play Packets
    REGISTER_CLIENTBOUND(ProtocolState::Play, GameEventPacket);
    REGISTER_CLIENTBOUND(ProtocolState::Play, LoginPlay);
}
