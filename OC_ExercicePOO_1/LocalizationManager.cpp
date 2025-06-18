// LocalizationManager.cpp
#include "LocalizationManager.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

LocalizationManager& LocalizationManager::Instance() {
    static LocalizationManager instance;
    return instance;
}

void LocalizationManager::Load(const std::string& languageCode) {
    m_translations.clear();
    std::ifstream file("lang/" + languageCode + ".lang");
    if (!file) {
        std::cerr << "Fichier de langue introuvable : " << languageCode << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            m_translations[key] = value;
        }
    }
}

std::string LocalizationManager::Get(const std::string& key) const {
    auto it = m_translations.find(key);
    return (it != m_translations.end()) ? it->second : "[[" + key + "]]";
}

char LocalizationManager::GetChar(const std::string& key) const {
    auto it = m_translations.find(key);
    return (it != m_translations.end() && !it->second.empty()) ? it->second[0] : '\0';
}
