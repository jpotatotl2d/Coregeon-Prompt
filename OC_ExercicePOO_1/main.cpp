#include <iostream>
#include <string>
#include "Personnage.hpp"
#include "Level.hpp"
#include "UserInterface.hpp"
#include "LocalizationManager.hpp"
#include <ctime>
#include <map>
#include <vector>
#include <thread>
#include <chrono>
#include <windows.h>
//#include <cstdlib>

using namespace std;


    //LocalizationManager loc;
    UserInterface UI;
    Personnage player;

// Character personalization variables :
string characterName("Name");
int characterBaseLevel(1);
int characterHealth(100);
int characterMana(90);
string characterWeapon("Epee legere 2");
int characterWeaponDamage(30);
string characterID("ID");
int characterGiveExp(0);

char keyYes;
char keyNo;
string gameLanguage = "fr";

// Define the number of levels that the enemies gain when defeating the Boss level:
int npcLevelUp = 5;

        void setupLocalization()
        {
            LocalizationManager::Instance().Load(gameLanguage);

    //ShowPrompt(); // Maintenant les clés sont valides

    //return 0;
            //loc.Load(language);
            //language = "fr";
            keyYes = LocalizationManager::Instance().GetChar("key_Yes");
            keyNo = LocalizationManager::Instance().GetChar("key_No");
        }

        // Pre-declaration of function:
int startGame();

    map<string, Personnage> enemies = {
        // {"Localized var", Personnage(Level, Health, Mana, "Weapon", Damage, "ID", Exp, Money}
    {"str_NpcEnemy_Sql", Personnage(2, 150, 400, "str_Weapon_BoneHammer", 4, "SQL", 26, 130)},
    {"str_NpcEnemy_Ogr", Personnage(3, 150, 80, "str_Weapon_BrokenMass", 6, "OGR", 43, 140)},
    {"str_NpcEnemy_Gob", Personnage(4, 240, 115, "str_Weapon_RustedKnife", 8, "GOB", 53, 150)},
    {"str_NpcEnemy_Pha", Personnage(4, 200, 320, "str_Weapon_SpectralGriffe", 8, "PHA", 64, 160)},
    {"str_NpcEnemy_Rli", Personnage(6, 400, 500, "str_Weapon_GigaSword", 14, "RLI", 128, 170)},
    {"str_NpcEnemy_Rat", Personnage(3, 190, 80, "str_Weapon_Griffe", 18, "RAT", 4, 180)},
    {"str_NpcEnemy_Sli", Personnage(3, 210, 350, "str_Weapon_AcidSpit", 10, "SLI", 61, 190)},
    {"str_NpcEnemy_Slz", Personnage(4, 200, 50, "str_Weapon_RustedSword", 8, "SLZ", 78, 200)},
    {"str_NpcEnemy_Vam", Personnage(4, 300, 600, "str_Weapon_BloodyFangs", 10, "VAM", 123, 210)},
    {"str_NpcEnemy_Spi", Personnage(4, 190, 220, "str_Weapon_PoisonBite", 12, "SPI", 49, 220)},
    {"str_NpcEnemy_Wor", Personnage(4, 220, 180, "str_Weapon_SandSyphon", 8, "WOR", 65, 230)},
    {"str_NpcEnemy_Drk", Personnage(5, 150, 180, "str_Weapon_DarkSword", 16, "DRK", 152, 259)},
    {"str_NpcEnemy_Moc", Personnage(5, 150, 180, "str_Weapon_HighPressureJet", 18, "MOC", 254, 312)},
    {"str_NpcEnemy_DrM", Personnage(5, 220, 450, "str_Weapon_SorcererStick", 10, "DRM", 123, 240)},
    {"str_NpcEnemy_Mim", Personnage(4, 220, 800, "str_Weapon_DimensionalBite", 2, "MIM", 366, 18594)}
};


vector<string> bossNames = {"str_NpcEnemy_Rli", "str_NpcEnemy_Drk", "str_NpcEnemy_Moc"};
vector<string> enemyNames;

string getRandomBoss() {
    int i = rand() % bossNames.size();
    cout << "<<<<<<<<<<<<<< " << LocalizationManager::Instance().Get("str_Game_BossAppear") <<" >>>>>>>>>>>>>" << endl;
    return bossNames[i];
}

string getRandomEnemy() {
    int i = rand() % enemyNames.size();
    // generate another enemy if the actual map level is not a Boss level and enemy is a Boss :
     for(size_t j = 0; j < bossNames.size(); ++j)
    {
    cout << "Debug enemyNames " << enemyNames[j] << endl;
        while(enemyNames[i] == bossNames[j]) // changement du if en while
    {
        //cout << "Boss detecte avant le niveau du boss, generation d'un nouvel ennemi : " << endl;

    i = rand() % enemyNames.size();
    }
    }

    return enemyNames[i];
}

void mainGameMenu(UserInterface &UI)
{
    //UserInterface UI;
    char menuUserInput;
    char userInput;
    //setupLocalization(); // Need to set a get in UserInterface to retrieve the modified language and set it to gameLanguage, then update setupLocalization.

    while(menuUserInput != 'n') // if not 'start new game' input
    {

            if(gameLanguage != UI.GetNewLang())
    {

    gameLanguage = UI.GetNewLang();
    cout << "+++++++++++++++++++++++++++ New Lang = " << gameLanguage << endl;
    setupLocalization();
    cout << "---------------------++++++ Updating Localization" << endl;
    }

    if(UI.GetBoolActiverAudio())Beep(800, 200); // fréquence 750 Hz, durée 300 ms

    // Character personalization v1 :
    cout << "\n_________________________________________________________" << endl;
    cout << "                  -- Coregeon/_Prompt; --" << endl;
    cout << "             " << LocalizationManager::Instance().Get("str_MainMenu_TitleQuote") << endl;
    cout << "_________________________________________________________" << endl;
    cout << LocalizationManager::Instance().Get("str_MainMenu_Selectors") << endl;
    cout << "_________________________________________________________\n" << endl;
    cout << LocalizationManager::Instance().Get("str_MainMenu_Selection") << " ";
    cin >> menuUserInput;

    menuUserInput = tolower(menuUserInput);

    if (menuUserInput == 'x')  // 27 = code ASCII de la touche Échap
    {
        cout << "\n" << LocalizationManager::Instance().Get("str_MainMenu_Exit") << endl;
        exit(0);  // termine immédiatement le programme
    }
    if (menuUserInput == 'o')
    {
        UI.SettingsDraw(gameLanguage);
    }
    if(menuUserInput == 'n') // if start new game
    {
    cout << "\n" << LocalizationManager::Instance().Get("str_MainMenu_CreateChar") << "(" << LocalizationManager::Instance().Get("key_Yes") << "/" << LocalizationManager::Instance().Get("key_No") << ")"  << endl;
    cin >> userInput;
    userInput = tolower(userInput);

    if(userInput == tolower(keyYes))
    {
      characterDataStruct cd = UI.CustomCharacter();

      characterName = cd.name;
      characterBaseLevel = cd.level;
      characterID = cd.id;

    }
    cout << "_________________________________________________________\n" << endl;
    startGame();
    }
    if(menuUserInput == 'c')
    {
        UI.CreditsDraw();
    }
    }// end while menuUserInput != 'n'

}


int main()
{
    setupLocalization();
    UI.startScreenDraw();
    mainGameMenu(UI);

    return 0;
}

int startGame ()
{
// used to correct issue with class and string of characterName :
// characterName = class, myCharacterName = string.
string myCharacterName = characterName;

    // initialisation des rand() :
        srand(time(0));

    // Création des personnages
    // class PersonnageID(StartPlayerLevel, MaxHealth, MaxMana, WP name, WP base damage, Name)
    Personnage characterName(1, 100, 90, LocalizationManager::Instance().Get("str_Invent_Weapon_3") , 24, characterID, 0, 0);

    //Personnage.LevelUp(int levelUpParam, int levelQty, string nomPersonnage)
    // levelUpParam: 1 = initialise characters levels. 2 = Upgrade levels with a loop. 0 = Upgrade only one level.
    characterName.LevelUp(1, characterBaseLevel, "characterName"); // update character level


    // Initialise le point de départ:
    int currentLevel = 1;
    // permet de générer plusieurs niveaux en une fois:
    int totalOfLevels = 1;
    // Creation de l'objet Level:
    Level Level(currentLevel);
    // Init of the traveling stats:

    for(int i = 0; i < totalOfLevels; ++i)
    {
    Level.DisplayLevel(currentLevel, myCharacterName, characterName);

      if(totalOfLevels > 1)
       {
         ++currentLevel;
       }

    }

    cout << "\n****** " << LocalizationManager::Instance().Get("str_Game_Start") <<  " ******\n" << endl;
    cout << myCharacterName << endl;
    //UI.EquipementMenuDraw();
    characterName.afficherEtat();
    if(characterName.GetHealth() <= 0)
    {
        characterName.afficherStatsEnd(characterName, Level.GetTotalLevels());
        return 2;
    }

    while (characterName.estVivant())
    {


    // Selection du chemin pour générer le level suivant:

    char pathInput;

    cout << "++ " << LocalizationManager::Instance().Get("str_Game_SelectPath") << " :";
    cin >> pathInput;
    pathInput = tolower(pathInput);

    if(pathInput == 'z')
    {
    cout << "\n_________________________________________________________" << endl;
    cout << ">>>>> " << myCharacterName << " " << LocalizationManager::Instance().Get("str_Game_SelectPath_F") << endl;
    cout << "_________________________________________________________\n" << endl;
    ++currentLevel;
    Level.DisplayLevel(currentLevel, myCharacterName, characterName);
    //cout << " Total levels : " << Level.GetTotalLevels() << endl;
    //Level.IncrementTotalLevels();
    }
    else if(pathInput == 'd')
    {
    cout << "\n_________________________________________________________" << endl;
    cout << ">>>>> " << myCharacterName << " " << LocalizationManager::Instance().Get("str_Game_SelectPath_R") << endl;
    cout << "_________________________________________________________\n" << endl;
    ++currentLevel;
    Level.DisplayLevel(currentLevel, myCharacterName, characterName);
    }
    else if(pathInput == 'q')
    {
    cout << "\n_________________________________________________________" << endl;
    cout << ">>>>> " << myCharacterName << " " << LocalizationManager::Instance().Get("str_Game_SelectPath_L") << endl;
    cout << "_________________________________________________________\n" << endl;
    ++currentLevel;
    Level.DisplayLevel(currentLevel, myCharacterName, characterName);
    }
    else
    {
    cout << "\n_________________________________________________________" << endl;
        cout << ">>>>> " << myCharacterName << " " << LocalizationManager::Instance().Get("str_Game_SelectPath_S") << endl;
    cout << "_________________________________________________________\n" << endl;
    }



// ------------------------------------------------------------- Select random enemy and enable BOSS types :
for (const auto& pair : enemies)
{
    enemyNames.push_back(pair.first);
}

string enemyName;
if (Level.GetTotalLevels() % 5 == 0) {
    enemyName = getRandomBoss();
    //cout << "Niveau multiple de 5, boss selectionne : " << enemyName << endl;
} else {
    enemyName = getRandomEnemy();

    // cout << "Niveau standard, ennemi selectionne : " << enemyName << endl;
}

    cout << "\n****** " << LocalizationManager::Instance().Get("str_Game_EnemyAppear") << " " << LocalizationManager::Instance().Get(enemyName) << " ! ******" << endl;

    // ___________________________________________________________________________________________________________

    // Au combat !
    //characterName.changerArme("Epee lourde", 99);
    //cout << myCharacterName << " equipe : Epee lourde (99 atk)" << endl;
    //goliath.changerArme("Double hache tranchante vénéneuse de la mort", 40);

    cout << "\n****** " << LocalizationManager::Instance().Get("str_Game_StartFight") << " ******\n" << endl;

char userInput;

        // Draw characters status:
        characterName.afficherEtat();
        cout << "           VS" << endl;
        enemies[enemyName].afficherEtatNpc(true, characterName);

cout << "\n####### " << LocalizationManager::Instance().Get("str_Game_SlctAutoFight") <<  " (" << LocalizationManager::Instance().Get("key_Yes") << "/" << LocalizationManager::Instance().Get("key_No") << ")" << " #######" << endl;
cin >> userInput;
userInput = tolower(userInput);

// char keyYes & keyNo unfound from there.
/*gameLanguage = UI.GetNewLang();
setupLocalization();
keyYes = LocalizationManager::Instance().GetChar("key_Yes");
keyNo = LocalizationManager::Instance().GetChar("key_No");*/

if (userInput != tolower(keyYes) && userInput != tolower(keyNo)) {
    cout << LocalizationManager::Instance().Get("str_Game_AutoFightErr") << keyYes << keyNo << endl;
    userInput = tolower(keyYes);
}
// -------------------------------------------------------------------- Starting Autofight loop :
while (characterName.estVivant() && enemies[enemyName].estVivant())
{
    if (userInput == tolower(keyYes))
    {
        characterName.afficherEtat();
        characterName.autoFight(enemies[enemyName]);
        enemies[enemyName].afficherEtatNpc(false, characterName);
        enemies[enemyName].autoFight(characterName);
    }
    else
    {
        char userInput2;
        cout << LocalizationManager::Instance().Get("str_Game_FightSelector") << endl;
        cout << LocalizationManager::Instance().Get("str_Game_FightSelectEntry") << endl;
        cin >> userInput2;

        switch (userInput2)
        {
            case '1': characterName.attaquer(enemies[enemyName]); break;
            case '2': characterName.attaquerMagie(enemies[enemyName]); break;
            case '3': characterName.utiliserPotionGenerique(characterName, false); break; // false = potion HP
            case '4': characterName.utiliserPotionGenerique(characterName, true); break; // true = potion MP
            default: cout << LocalizationManager::Instance().Get("str_Game_FightSelectErr") << endl; break;
        }

        if (enemies[enemyName].estVivant() && characterName.estVivant())
        enemies[enemyName].afficherEtatNpc(false, characterName);
        enemies[enemyName].autoFight(characterName);
        characterName.afficherEtat();
    }

}

cout << "\n****** " << LocalizationManager::Instance().Get("str_Game_EndFight") << " ******\n" << endl;
characterName.afficherEtat();
enemies[enemyName].afficherEtatNpc(false, characterName);

//enemyName = LocalizationManager::Instance().Get("str_NpcEnemy_Sql");

//string enemyId = getRandomEnemy(); // "str_NpcEnemy_Sql"
//enemyName = LocalizationManager::Instance().Get(getRandomEnemy());
//string enemyWeapon = LocalizationManager::Instance().Get(enemies[enemyId].getWeaponId());

//cout << "Un ennemi apparaît : " << enemyName << " équipé de " << enemyWeapon << " !" << endl;


if (characterName.estVivant()) {
    cout << myCharacterName << " " << LocalizationManager::Instance().Get("str_Game_FightCharDefeated") << " " << LocalizationManager::Instance().Get(enemyName) << " !\n" << endl;
    characterName.EarnExpPoints(enemies[enemyName].getGiveExp());
    characterName.receiveMoney(enemies[enemyName].getGiveMoney());
    characterName.defeatedEnemies();
    characterName.afficherEtat();
}
else {
    cout << "\n****** " << LocalizationManager::Instance().Get("str_Game_GameEnd") << " ******\n" << endl;
    cout << LocalizationManager::Instance().Get(enemyName) << " " << LocalizationManager::Instance().Get("str_Game_FightCharDefeated") << " " << myCharacterName << " !!\n" << endl;
    characterName.afficherStatsEnd(characterName, Level.GetTotalLevels());

    // ------------------------------------------------------------------------ Display credits and return to Main Menu :
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    UI.CreditsDraw();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    mainGameMenu(UI);
}
     // ---------------------------------------------------- Trying to update enemies level, may need a bool to stop the for():
// Level up automatique des ennemis tous les 5 niveaux
if (Level.GetTotalLevels() % 5 == 0 && characterName.estVivant()) {

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
{
    std::string name = it->first;
    Personnage& enemy = it->second;
    enemy.LevelUp(1, npcLevelUp, enemy.GetName());
}
    cout << "\n++++++ " << LocalizationManager::Instance().Get("str_Game_NpcLevelUpTitle") << " " << npcLevelUp << " " << LocalizationManager::Instance().Get("str_Game_NpcLevelUpLvl") << "\n" << endl;
    characterName.afficherStatsEnd(characterName, Level.GetTotalLevels());
}
characterName.resetNbrAffichageStatus();
enemies[enemyName].resetNbrAffichageStatus();


}
    return 0;
}
