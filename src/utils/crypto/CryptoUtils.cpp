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

#include "CryptoUtils.h"

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <stdexcept>

stratos::EVPKeyPtr stratos::generateEncryptionKey() {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_from_name(nullptr, "RSA", nullptr);
    if (!ctx) throw std::runtime_error("Failed to create EVP_PKEY_CTX");

    if (EVP_PKEY_keygen_init(ctx) <= 0 || EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 1024) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw std::runtime_error("Failed to initialize RSA key generation");
    }

    EVP_PKEY* pkey = nullptr;
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw std::runtime_error("Failed to generate RSA key");
    }
    EVP_PKEY_CTX_free(ctx);

    return {pkey, &EVP_PKEY_free};
}
std::vector<uint8_t> stratos::encodeServerPublicKey(const EVPKeyPtr* key) {
    std::vector<uint8_t> result;
    const int            len = i2d_PUBKEY(key->get(), nullptr);
    if (len <= 0) {
        throw std::runtime_error("Failed to determine DER length");
    }

    result.resize(len);
    unsigned char* ptr = result.data();
    if (i2d_PUBKEY(key->get(), &ptr) <= 0) {
        throw std::runtime_error("Failed to encode DER public key");
    }

    return result;
}
std::vector<uint8_t> stratos::rsaEncrypt(const EVPKeyPtr* key, const std::vector<uint8_t>& payload) {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(key->get(), nullptr);
    if (!ctx) throw std::runtime_error("Failed to create encrypt context");

    if (EVP_PKEY_encrypt_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw std::runtime_error("Failed to initialize encryption");
    }

    size_t outLen = 0;
    if (EVP_PKEY_encrypt(ctx, nullptr, &outLen, payload.data(), payload.size()) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw std::runtime_error("Failed to determine encrypted length");
    }

    std::vector<uint8_t> ciphertext(outLen);
    if (EVP_PKEY_encrypt(ctx, ciphertext.data(), &outLen, payload.data(), payload.size()) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw std::runtime_error("Encryption failed");
    }

    ciphertext.resize(outLen);
    EVP_PKEY_CTX_free(ctx);
    return ciphertext;
}
std::vector<uint8_t> stratos::rsaDecrypt(const EVPKeyPtr* key, const std::vector<uint8_t>& payload) {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(key->get(), nullptr);
    if (!ctx) throw std::runtime_error("Failed to create decrypt context");

    if (EVP_PKEY_decrypt_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw std::runtime_error("Failed to initialize decryption");
    }

    size_t outLen = 0;
    if (EVP_PKEY_decrypt(ctx, nullptr, &outLen, payload.data(), payload.size()) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw std::runtime_error("Failed to determine decrypted length");
    }

    std::vector<uint8_t> plaintext(outLen);
    if (EVP_PKEY_decrypt(ctx, plaintext.data(), &outLen, payload.data(), payload.size()) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw std::runtime_error("Decryption failed");
    }

    plaintext.resize(outLen);
    EVP_PKEY_CTX_free(ctx);
    return plaintext;
}
std::vector<uint8_t> stratos::aesEncryptCFB8(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv, const std::vector<uint8_t>& plaintext) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("Failed to create AES encryption context");

    if (EVP_EncryptInit_ex(ctx, EVP_aes_128_cfb8(), nullptr, key.data(), iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to initialize AES encryption");
    }

    std::vector<uint8_t> ciphertext(plaintext.size());
    int outlen = 0;
    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &outlen, plaintext.data(), static_cast<int>(plaintext.size())) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("AES encryption failed");
    }

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext;
}

std::vector<uint8_t> stratos::aesDecryptCFB8(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv, const std::vector<uint8_t>& ciphertext) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("Failed to create AES decryption context");

    if (EVP_DecryptInit_ex(ctx, EVP_aes_128_cfb8(), nullptr, key.data(), iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to initialize AES decryption");
    }

    std::vector<uint8_t> plaintext(ciphertext.size());
    int                  outlen = 0;
    if (EVP_DecryptUpdate(ctx, plaintext.data(), &outlen, ciphertext.data(), static_cast<int>(ciphertext.size())) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("AES decryption failed");
    }

    EVP_CIPHER_CTX_free(ctx);
    return plaintext;
}
std::vector<uint8_t> stratos::generateRandomBytes(const size_t size) {
    std::vector<uint8_t> randomBytes(size);
    if (RAND_bytes(randomBytes.data(), static_cast<int>(size)) != 1)
        throw std::runtime_error("Failed to generate random bytes");
    return randomBytes;
}