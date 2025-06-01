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

#ifndef CRYPTOUTILS_H
#define CRYPTOUTILS_H
#include <cstdint>
#include <memory>
#include <openssl/evp.h>
#include <openssl/types.h>
#include <string>
#include <vector>

namespace stratos {
using EVPKeyPtr = std::unique_ptr<EVP_PKEY, decltype(&EVP_PKEY_free)>;

EVPKeyPtr generateEncryptionKey();
std::vector<uint8_t> encodeServerPublicKey(const EVPKeyPtr* key);
std::vector<uint8_t> rsaEncrypt(const EVPKeyPtr* key, const std::vector<uint8_t>& payload);
std::vector<uint8_t> rsaDecrypt(const EVPKeyPtr* key, const std::vector<uint8_t>& payload);
std::vector<uint8_t> aesEncryptCFB8(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv, const std::vector<uint8_t>& plaintext);
std::vector<uint8_t> aesDecryptCFB8(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv, const std::vector<uint8_t>& ciphertext);
std::vector<uint8_t> generateRandomBytes(size_t size);
} // namespace stratos
#endif //CRYPTOUTILS_H
