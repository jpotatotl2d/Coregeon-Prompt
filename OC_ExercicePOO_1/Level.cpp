#include "Level.hpp"
#include "Personnage.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include <map>
#include <limits>
#include "LocalizationManager.hpp"

using namespace std;

Level::Level()
{
    //m_totalLevelsTraveled = 0;
}

Level::Level(int level) : m_levelInstance(level)
{
    //m_totalLevelsTraveled = 0;
}


void Level::DisplayLevel(int levelInstance, const std::string &characterName, Personnage &player)
{
    m_returnedCharacterName = characterName;

    string cases[] = {"A", "B", "C", "D"};
    string line = "[";

    for (int i = 0; i < 4; ++i) {
        line += (i < m_resetPaysage) ? "X" : cases[i];
        line += "][][][][";
    }
    line += "BOSS]:[LV." + to_string(levelInstance) + "]";
    //cout << "\n" << line << endl;

    // cout << "################################ " << characterName << endl;

    static string paysages[] = {
        LocalizationManager::Instance().Get("str_Level_Scenery0"),
        LocalizationManager::Instance().Get("str_Level_Scenery1"),
        LocalizationManager::Instance().Get("str_Level_Scenery2"),
        LocalizationManager::Instance().Get("str_Level_Scenery3"),
        LocalizationManager::Instance().Get("str_Level_Scenery4"),
        LocalizationManager::Instance().Get("str_Level_Scenery5"),
        LocalizationManager::Instance().Get("str_Level_Scenery6"),
        LocalizationManager::Instance().Get("str_Level_Scenery7")
    };
    static string chemins[] = {
        LocalizationManager::Instance().Get("str_Level_Path0"),
        LocalizationManager::Instance().Get("str_Level_Path1"),
        LocalizationManager::Instance().Get("str_Level_Path2"),
        LocalizationManager::Instance().Get("str_Level_Path3"),
        LocalizationManager::Instance().Get("str_Level_Path4"),
        LocalizationManager::Instance().Get("str_Level_Path5"),
        LocalizationManager::Instance().Get("str_Level_Path6"),
        LocalizationManager::Instance().Get("str_Level_Path7"),
        LocalizationManager::Instance().Get("str_Level_Path8"),
        LocalizationManager::Instance().Get("str_Level_Path9"),
        LocalizationManager::Instance().Get("str_Level_Path10")
    };
    static string decor[] = {
        LocalizationManager::Instance().Get("str_Level_Decor0"),
        LocalizationManager::Instance().Get("str_Level_Decor1"),
        LocalizationManager::Instance().Get("str_Level_Decor2"),
        LocalizationManager::Instance().Get("str_Level_Decor3"),
        LocalizationManager::Instance().Get("str_Level_Decor4"),
        LocalizationManager::Instance().Get("str_Level_Decor5"),
        LocalizationManager::Instance().Get("str_Level_Decor6"),
        LocalizationManager::Instance().Get("str_Level_Decor7"),
        LocalizationManager::Instance().Get("str_Level_Decor8"),
        LocalizationManager::Instance().Get("str_Level_Decor9"),
        LocalizationManager::Instance().Get("str_Level_Decor10"),
        LocalizationManager::Instance().Get("str_Level_Decor11"),
        LocalizationManager::Instance().Get("str_Level_Decor12")
    };

    int paysageIndex = (m_resetPaysage <= 0) ? rand() % 8 : m_savedPaysage;
    int cheminIndex = rand() % 11;
    int decorIndex = rand() % 13;

    if (m_resetPaysage <= 0)
    {
        m_savedPaysage = paysageIndex;
        m_resetPaysage = 1;
        //cout << "reset paysage = 0, sauvegarde du niveau actuel : "
             //<< m_savedPaysage << " | Reset : " << m_resetPaysage << endl;
        UserInterface ui;
    ui.DisplayShopMenu(player);
    }
    else if (m_resetPaysage < 4)
    {
        ++m_resetPaysage;
        //cout << "On reste dans le même paysage : "
             //<< m_savedPaysage << " | Reset : " << m_resetPaysage << endl;
    }
    else
    {
        m_resetPaysage = 0;
        //cout << "Réinitialisation de la sauvegarde de paysage et passage au paysage suivant." << endl;
    }

    string paysageChoisi = paysages[m_savedPaysage];
    string cheminChoisi = chemins[cheminIndex];
    string decorChoisi = decor[decorIndex];

    cout << "\n" << line << endl;
    cout << "\n______________________________________________" << endl;
    cout << LocalizationManager::Instance().Get("str_Level_Desc1") << levelInstance << " : "
         << cheminChoisi << " " << paysageChoisi << ", " << LocalizationManager::Instance().Get("str_Level_Desc2") << " " << decorChoisi << "." << endl;
    cout << "______________________________________________\n" << endl;

    IncrementTotalLevels();
}

void Level::IncrementTotalLevels() {
    m_totalLevels++;
    // cout << "**************** Level ++ " << m_totalLevels << endl;
}

int Level::GetTotalLevels() const {
    return m_totalLevels;
}
