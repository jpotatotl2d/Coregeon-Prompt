#include "UserInterface.hpp"
#include "Personnage.hpp"
#include <vector>
#include <thread>   // sleep
#include <chrono>
#include <windows.h>
#include <map>
#include "LocalizationManager.hpp"

using namespace std;

    bool alreadyInInventory = false;
    char keyYes1;
    char keyNo1;


// Constructor :
UserInterface::UserInterface()
{

}

bool UserInterface::GetBoolActiverAudio()
{
    return m_activerAudio;
}

// Draw a screen design, intended to be used when starting the program :
void UserInterface::startScreenDraw()
{
    if(!m_startScreenWasDrawn){ // draw start screen only if false.
    cout << "\n[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]" << endl;
      cout << "[]                  COREGEON/_PROMPT;                     []" << endl;
      cout << "[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    cout << "\n" << LocalizationManager::Instance().Get("str_StartScreen_Entry1") << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cout << LocalizationManager::Instance().Get("str_StartScreen_Entry2") << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    //sleep(2); // Attente pour effet dramatique
    cout << LocalizationManager::Instance().Get("str_StartScreen_Entry3")       <<    endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cout << LocalizationManager::Instance().Get("str_StartScreen_Entry4") <<    endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cout << LocalizationManager::Instance().Get("str_StartScreen_Entry5") <<    endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    };


    m_startScreenWasDrawn = true;

}

// Draw Credits :
void UserInterface::CreditsDraw()
{
    vector<pair<string, string>> developpers = {
    {"\n2025 CC - CoreSpectrum Studio - BY NC SA 4.0", ""},
    {">> https://CoreSpectrumStudio.DeviantArt.com <<", "\n"},
    {"Programmation, Design, Scenario :: ", "JpotatO"},
    {">> https://JpotatOTL2D.DeviantArt.com <<", "\n"},
    {"Code corrected & enhanced by :: ", "ChatGPT-4o\n"},
    {"Text domain3 :: ", "Txt Name3\n"},
    {"Text domain4 :: ", "Txt Name4\n"},
    {"Text domain5 :: ", "Txt Name5\n"},
    {"Text domain6 :: ", "Txt Name6\n"},
    {"Text domain7 :: ", "Txt Name7\n"},
    {"Text domain8 :: ", "Txt Name8\n"},
    {"Text domain9 :: ", "Txt Name9\n"},
    {"Text domain10 :: ", "Txt Name10\n"},
    {"Text domain11 :: ", "Txt Name11\n"},
    {"Text domain12 :: ", "Txt Name12\n"}
    };

    vector<pair<string, string>> testers = {
    {"\nTester Name - ", "http://Tester.URL"},
    {"\nTester Name - ", "http://Tester.URL"},
    {"\nTester Name - ", "http://Tester.URL"},
    {"\nTester Name - ", "http://Tester.URL"},
    {"\nTester Name - ", "http://Tester.URL"},
    {"\nTester Name - ", "http://Tester.URL"},
    {"\nTester Name - ", "http://Tester.URL"},
    {"\nTester Name - ", "http://Tester.URL"},
    {"\nTester Name - ", "http://Tester.URL"},
    {"\nTester Name - ", "http://Tester.URL"},
    {"\nTester Name - ", "http://Tester.URL"}
    };

    if(m_activerAudio)Beep(800, 200); // fréquence 750 Hz, durée 300 ms
    cout << "\n_________________________________________________________" << endl;
    cout << "                         " << LocalizationManager::Instance().Get("str_Credits_Title") << endl;
    cout << "_________________________________________________________" << endl;
    cout << "\nV-------------------- " << LocalizationManager::Instance().Get("str_Credits_Entry1") << " --------------------V\n" << endl;

    // Temporary credit's text:
    for(const auto& entry : developpers)
    {
    if(m_activerAudio)Beep(250, 200); // fréquence 750 Hz, durée 300 ms
    cout << entry.first << entry.second << endl;
    // Petite pause pour lisibilité (optionnelle)
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    cout << "_________________________________________________________\n" << endl;

    cout << "\nV----------------------- " << LocalizationManager::Instance().Get("str_Credits_Entry2") << " -----------------------V\n" << endl;
    // Temporary credit's text:
    for(const auto& entry : testers)
    {
    if(m_activerAudio)Beep(350, 200); // fréquence 750 Hz, durée 300 ms
    cout << entry.first << entry.second << endl;
    // Petite pause pour lisibilité (optionnelle)
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    cout << "_________________________________________________________\n" << endl;
    cout << "         " << LocalizationManager::Instance().Get("str_Credits_EndLine") << endl;
    cout << "_________________________________________________________\n" << endl;

}

std::string UserInterface::GetNewLang()
{
    cout << "Language = " << m_SelectedLanguage << endl;
    return m_SelectedLanguage;
}

// Draw Settings :
void UserInterface::SettingsDraw(std::string selectedLanguage)
{
    char userInput;
    cout << "\n_________________________________________________________" << endl;
    cout << "                         " << LocalizationManager::Instance().Get("str_Setting_Title") << endl;
    cout << "_________________________________________________________" << endl;
    cout << LocalizationManager::Instance().Get("str_Setting_LangSelector") << " : ";
    cin >> userInput;
    switch(userInput)
    {
    case 'f':
        cout << LocalizationManager::Instance().Get("str_Setting_SlctFr") << endl;
        selectedLanguage = "fr";
        break;

        case 'e':
        cout << LocalizationManager::Instance().Get("str_Setting_SlctEn") << endl;
        selectedLanguage = "en";
            break;
    }

    m_SelectedLanguage = selectedLanguage;
    LocalizationManager::Instance().Load(selectedLanguage);
    keyYes1 = LocalizationManager::Instance().GetChar("key_Yes");
    keyNo1 = LocalizationManager::Instance().GetChar("key_No");

    cout << LocalizationManager::Instance().Get("str_Setting_AudioSlct") << " (" << keyYes1 << "/" << keyNo1 << ")" << " : ";
    cin >> userInput;
    userInput = tolower(userInput);

    if(userInput == tolower(keyYes1))
    {
    //case keyYes :
        m_activerAudio = true;
        cout << LocalizationManager::Instance().Get("str_Setting_AudioOn") << endl;
        //break;
    }
    if(userInput == tolower(keyNo1))
    {
    m_activerAudio = false;
        cout << LocalizationManager::Instance().Get("str_Setting_AudioOff") << endl;
            //return;
    }
    cout << "_________________________________________________________\n" << endl;

}


characterDataStruct UserInterface::CustomCharacter()
{
    characterDataStruct data;
    // Character personalization v1 :
    cout << "\n_________________________________________________________" << endl;
    cout << "                " << LocalizationManager::Instance().Get("str_CharCreate_Title") << endl;
    cout << "_________________________________________________________" << endl;
    cout << LocalizationManager::Instance().Get("str_CharCreate_Entry1") << " ";
    cin >> data.name;
    cout << LocalizationManager::Instance().Get("str_CharCreate_Entry2") << " ";
    cin >> data.level;
    cout << LocalizationManager::Instance().Get("str_CharCreate_Entry3") <<" ";
    cin >> data.id;
    cout << "_________________________________________________________\n" << endl;
    cout << "1************** " << data.name << " / " << data.level << " / " << data.id << endl;

    return data;
}

void UserInterface::DisplayShopMenu(Personnage &player)
{
    map<char, ShopItem> shopItems = {
        {'a', {"str_Invent_Item_1", LocalizationManager::Instance().Get("str_Invent_Item_Desc_1"), 50}},
        {'z', {"str_Invent_Item_2", LocalizationManager::Instance().Get("str_Invent_Item_Desc_2"), 125}},
        {'e', {"str_Invent_Item_3", LocalizationManager::Instance().Get("str_Invent_Item_Desc_3"), 1}},
        {'r', {"str_Invent_Item_4", LocalizationManager::Instance().Get("str_Invent_Item_Desc_4"), 1000}},
        {'t', {"str_Invent_Weapon_1", LocalizationManager::Instance().Get("str_Invent_Weapon_Desc_1"), 100000}},
        {'y', {"str_Invent_Weapon_2", LocalizationManager::Instance().Get("str_Invent_Weapon_Desc_2"), 100}},
        {'u', {"str_Invent_Weapon_3", LocalizationManager::Instance().Get("str_Invent_Weapon_Desc_3"), 200}},
        {'i', {"str_Invent_Weapon_4", LocalizationManager::Instance().Get("str_Invent_Weapon_Desc_4"), 5000}}
    };

    char userInput;
    char userInput2 = 'o';
    int itemQty;
    int calcTotalPrice;

    // calculer la longueur total de la string pour l'adapter a la longueur du menu, puis calculer le nombre de '-' qui peuvent être entrés et ensuite les partager a gauche et droite aléatoirement.
    while (tolower(userInput2) != 'n') {
        cout << "\n_________________________________________________________" << endl;
        cout << "---------------------- " << LocalizationManager::Instance().Get("str_Shop_Title") << " ------------------------" << endl;
        cout << "_________________________________________________________" << endl;
        cout << "---- " << LocalizationManager::Instance().Get(shopItems['a'].name) << " : " << shopItems['a'].price <<                           "$ (A) ----"
     << LocalizationManager::Instance().Get(shopItems['z'].name) << " : " << shopItems['z'].price << "$ (Z) ----" << endl;
        cout << "------------------ " << LocalizationManager::Instance().Get(shopItems['e'].name) << " : " << shopItems['e'].price <<  "$ (E) ---------------" << endl;
        cout << "-- " << LocalizationManager::Instance().Get(shopItems['r'].name) << " : " << shopItems['r'].price << "$ (R) --------------------------------" << endl;
        cout << "------------------------ " << LocalizationManager::Instance().Get(shopItems['t'].name) << " : " << shopItems['t'].price <<       "$ (T) ----" << endl;
        cout << "---- " << LocalizationManager::Instance().Get(shopItems['y'].name) << " : " << shopItems['y'].price <<    "$ (Y) ---------------------------" << endl;
        cout << "---------------- " << LocalizationManager::Instance().Get(shopItems['u'].name) << " : " << shopItems['u'].price <<  "$ (U) -----------------" << endl;
        cout << "--------------------------- " << LocalizationManager::Instance().Get(shopItems['i'].name) << " : " << shopItems['i'].price << "$ (I) -" << endl;



        /*cout << "---- Potion HP : 50 $ (A) ---- Potion MP : 125 $ (Z) ----" << endl;
        cout << "------------------ Death potion : 1 $ (E) ---------------" << endl;
        cout << "-- Level Up : 1000 $ (R) --------------------------------" << endl;
        cout << "------------------------ Cheat Sword : 100.000 $ (T) ----" << endl;
        cout << "---- Wooden Sword : 100 $ (Y) ---------------------------" << endl;
        cout << "---------------- Epee Legere: 200 $ (U) -----------------" << endl;
        cout << "--------------------------- Dark Aura Sword: 5000 $ (U) -" << endl;*/


        cout << "_________________________________________________________\n" << endl;

        cout << "[*********************************************************************************************]" << endl;
        cout << "                  " << LocalizationManager::Instance().Get("str_Shop_Entry1") << endl;
        cout << "       " << LocalizationManager::Instance().Get("str_Shop_Entry2") << " : " << player.GetTotalMoney() << " $) - :" << endl;
        cout << "\n[.............................................................................................]" << endl;
        cout << "\n" << LocalizationManager::Instance().Get("str_Shop_Choice") << " : ";
        cin >> userInput2;
        userInput2 = tolower(userInput2);
        if (userInput2 == 'n') break;

        if(userInput2 == 'o')
            {
        cout << "\n" << LocalizationManager::Instance().Get("str_Shop_ChoseItem") << " : ";
        cin >> userInput;
        userInput = tolower(userInput);

        if (shopItems.find(userInput) == shopItems.end()) {
        cout << "\n_________________________________________________________" << endl;
            cout << LocalizationManager::Instance().Get("str_Shop_ChoseErr") << endl;
        cout << "_________________________________________________________" << endl;
            continue;
        }

        const ShopItem &item = shopItems[userInput];


        cout << "\n_________________________________________________________" << endl;
        cout << LocalizationManager::Instance().Get("str_Shop_Chosed") << " : " << LocalizationManager::Instance().Get(item.name) << " - " << item.description << " (" << item.price << "$)" << endl;
        cout << "_________________________________________________________" << endl;

        while (true) { // Detection of incorrect itemQty
    cout << LocalizationManager::Instance().Get("str_Shop_SlctQty") << " : ";
    cin >> itemQty;

    if (!cin.fail() && itemQty >= 0) {
        break; // Quantité correcte, on sort de la boucle
    }

    // Gestion d’erreur
    cin.clear(); // Réinitialise le flag d'erreur
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore le reste de la mauvaise saisie


        cout << "\n_________________________________________________________" << endl;
        cout << LocalizationManager::Instance().Get("str_Shop_SlctQtyErr") << endl;
        cout << "_________________________________________________________" << endl;
}

        calcTotalPrice = item.price * itemQty;

        if (player.GetTotalMoney() < calcTotalPrice) {
        cout << "\n_________________________________________________________" << endl;
        cout << LocalizationManager::Instance().Get("str_Shop_MoneyNotEnough") << " : " << calcTotalPrice << "$" << endl;
        cout << "_________________________________________________________" << endl;
            continue;
        }

        // Traitement des achats selon le type
        switch (userInput) {
            case 'a':
                player.SetInventPotionsHP(player, itemQty);
                break;
            case 'z':
                player.SetInventPotionsMP(player, itemQty);
                break;
            case 'e':
                player.recevoirDegats(player.GetHealth());  // simulate "death"
                break;
            case 'r':
                player.LevelUp(2, itemQty, player.GetName());
                break;
            case 't':
    AjouterArme("Cheat Sword", 9999, player, true);
    break;
case 'y':
    AjouterArme("Wooden Sword", 1, player, true);
    break;
case 'u':
    AjouterArme("Epee legere", 24, player, true);
    break;
case 'i':
    AjouterArme("Dark Aura Sword", 250, player, true);
    break;

        }

        if(!alreadyInInventory)
            {
        player.SubstractPlayerMoney(calcTotalPrice);
        cout << "\n_________________________________________________________" << endl;
        cout << LocalizationManager::Instance().Get("str_Shop_ItemBrought1") << " : " << itemQty << " x " << item.name << " " << LocalizationManager::Instance().Get("str_Shop_ItemBrought2") << " " << calcTotalPrice << "$" << endl;
        cout << "_________________________________________________________" << endl;
            }
        }

    else if(userInput2 == 'i')
    {
    player.DisplayInventory();
    }
    else if(userInput2 == 'e')
    {
    EquipementMenuDraw(player);
    }

    alreadyInInventory = false;
    }
}

bool UserInterface::ArmeExiste(const std::string& nom) const {
    for (const auto& arme : m_possessedWeapons) {
        if (arme.second.first == nom)
            return true;
    }
    return false;
}

void UserInterface::AjouterArme(const std::string& nom, int atk, Personnage &player, bool drawText) {
    if (ArmeExiste(nom)) {
        if(drawText){
        cout << "\n_________________________________________________________" << endl;
                std::cout << LocalizationManager::Instance().Get("str_Shop_NoMoreItemType") << " " << nom << " !" << endl;
        cout << "_________________________________________________________" << endl;
        }
        alreadyInInventory = true;
        return;
    }

    int nextId = m_possessedWeapons.size() + 1;
    m_possessedWeapons.push_back({nextId, {nom, atk}});
    player.changerArme(nom, atk);
    player.TotalWeaponBrought();
    if(drawText){
        cout << "\n_________________________________________________________" << endl;
            std::cout << nom << " " << LocalizationManager::Instance().Get("str_Shop_AddToInventory") << endl;
        cout << "_________________________________________________________" << endl;
    }
}


void UserInterface::EquipementMenuDraw(Personnage &player)
{
        cout << "\n_________________________________________________________" << endl;
        cout << "------------------------ " << LocalizationManager::Instance().Get("str_WpMenu_Title") << " --------------------------" << endl;
        cout << "_________________________________________________________\n" << endl;
    for (const auto& weapon : m_possessedWeapons)
    {
        cout << weapon.first << ". " << weapon.second.first << " (" << weapon.second.second << " " << LocalizationManager::Instance().Get("str_WpMenu_Atk") << ")\n" << endl;
    }

    int userInput;
        cout << "\n_________________________________________________________" << endl;
    cout << LocalizationManager::Instance().Get("str_WpMenu_SlctWp") << " : " << endl;
    cin >> userInput;

    bool found = false;

    for (const auto& weapon : m_possessedWeapons)
    {
        if (weapon.first == userInput)
        {
        cout << "\n_________________________________________________________" << endl; // Trying to display the name and not the str_
            cout << LocalizationManager::Instance().Get("str_WpMenu_WpEquip") << " : " << weapon.second.first
                 << " (" << weapon.second.second << " " << LocalizationManager::Instance().Get("str_WpMenu_Atk") << ")\n" << endl;
        cout << "_________________________________________________________" << endl;
                 player.changerArme(weapon.second.first, weapon.second.second);
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\n_________________________________________________________" << endl;
        cout << LocalizationManager::Instance().Get("str_WpMenu_WpErr") <<endl;
        cout << "_________________________________________________________" << endl;
    }
}
