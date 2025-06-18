
#ifndef DEF_LOCALIZATION_MANAGER
#define DEF_LOCALIZATION_MANAGER

#include <unordered_map>
#include <string>

class LocalizationManager {
public:
    static LocalizationManager& Instance(); // Singleton

    void Load(const std::string& languageCode);
    std::string Get(const std::string& key) const;
    char GetChar(const std::string& key) const;

private:
    std::unordered_map<std::string, std::string> m_translations;
    LocalizationManager() = default;
};

#endif
