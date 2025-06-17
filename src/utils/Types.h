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

#ifndef TYPES_H
#define TYPES_H
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace stratos {
using ByteVec = std::vector<uint8_t>;

struct Identifier {
    std::string namespaceName;
    std::string name;

    Identifier(std::string ns, std::string n) : namespaceName(std::move(ns)), name(std::move(n)) {}

    bool operator==(const Identifier& other) const {
        return namespaceName == other.namespaceName && name == other.name;
    }

    bool operator!=(const Identifier& other) const {
        return !(*this == other);
    }
};

enum class HandshakeIntent {
    None = 0,
    Status = 0x01,
    Login = 0x02,
    Transfer = 0x03
};

struct LoginProperty {
    std::string name; // String(16)
    std::string value; // String(32767)
    std::optional<std::string> signature; // String(1024), prefixed optional
};

enum class ChatMode {
    Enabled = 0,
    CommandsOnly = 1,
    Hidden = 2
};

enum class Hand {
    Left = 0,
    Right = 1
};

enum class ParticleStatus {
    All = 0,
    Decreased = 1,
    Minimal = 2
};

enum class ResourcePackResult {
    SuccessfullyDownloaded = 0,
    Declined = 1,
    FailedDownload = 2,
    Accepted = 3,
    Downloaded = 4,
    InvalidURL = 5,
    FailedReload = 6,
    Discarded = 7
};

struct ResourcePackHeader {
    std::string packNamespace;
    std::string id;
    std::string version;
};

struct RegistryEntry {
    Identifier id;
    std::optional<ByteVec> data; // TODO: replace this with a NBT tag
};

struct RegistryTag {
    Identifier tagKey;
    int id;
};

struct RegistryTagData {
    Identifier registryKey;
    std::vector<RegistryTag> entries;
};

struct ReportDetail {
    std::string title;
    std::string description;
};

enum class LinkLabel {
    BugReport = 0,
    CommunityGuidelines = 1,
    Support = 2,
    Status = 3,
    Feedback = 4,
    Community = 5,
    Website = 6,
    Forums = 7,
    News = 8,
    Announcements = 9
};

struct ServerLink {
    bool isDefault; // Not sent over network
    LinkLabel defaultLabel;
    std::string customLabel; // Text Component
    std::string url;
};

enum class GameEvent {
    NoRespawnBlockAvailable = 0,
    BeginRaining = 1,
    EndRaining = 2,
    ChangeGameMode = 3,
    WinGame = 4,
    DemoEvent = 5,
    ArrowHitPlayer = 6,
    RainLevelChange = 7,
    ThunderLevelChange = 8,
    PlayPufferfishStingSound = 9,
    PlayElderGuardianCurseSound = 10,
    EnableRespawnScreen = 11,
    LimitedCrafting = 12,
    StartWaitingForChunks = 13
};

}
#endif //TYPES_H
