#ifndef DEF_USERINTERFACE
#define DEF_USERINTERFACE

#include <iostream>
#include <string>
#include <vector>

#include "Personnage.hpp"

class Personnage;

    struct characterDataStruct
{
  std::string name;
  int level;
  std::string id;
};

class UserInterface
{
public:

    //Personnage();
    UserInterface();
    void startScreenDraw();
    void CreditsDraw();
    void SettingsDraw(std::string selectedLanguage);
    bool GetBoolActiverAudio();

    characterDataStruct CustomCharacter();

    void EquipementMenuDraw(Personnage &player);

    void DisplayShopMenu(Personnage &player);
    void AjouterArme(const std::string& nom, int atk, Personnage &player, bool drawText);
    bool ArmeExiste(const std::string& nom, Personnage &player) const;

    std::string GetNewLang();

private:

    bool m_activerAudio = true;
    bool m_startScreenWasDrawn = false;
    std::vector<std::pair<int, std::pair<std::string, int>>> m_possessedWeapons = {{1, {"str_Invent_Weapon_3", 24}}};
    std::string m_SelectedLanguage = "fr";

};


#endif // DEF_USERINTERFACE

