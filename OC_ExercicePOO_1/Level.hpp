#ifndef DEF_LEVEL
#define DEF_LEVEL

#include "Personnage.hpp"
#include "UserInterface.hpp"

class Personnage;

struct ShopItem {
    std::string name;
    std::string description;
    int price;
};

class Level
{
    public:

    Level();
    Level(int levelInstance);
    void DisplayLevel(int levelInstance, const std::string &characterName, Personnage &player);

    void IncrementTotalLevels(); // méthode d'incrémentation
    int GetTotalLevels() const;  // pour afficher si besoin


private:
    int m_levelInstance;
    int m_totalLevels = 0;
    int m_savedPaysage = 0;
    int m_resetPaysage = 0;
    std::string m_returnedCharacterName;
};

#endif // DEF_LEVEL

