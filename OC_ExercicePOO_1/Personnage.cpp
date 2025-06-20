#include "Personnage.hpp"
#include "Level.hpp"
#include <cmath>
#include <ctime>
#include <thread>   // sleep
#include <chrono>   // chrono
#include "LocalizationManager.hpp"


using namespace std;


// -------------------------------------------------------------------- Initialize character :
Personnage::Personnage() : m_vie(100), m_mana(100)
{

}

Personnage::Personnage(int niveau, int vieMax, int manaMax, string nomArme, int degatsArme, string nomPersonnage, int giveExp, int giveMoney) : m_vie(vieMax), m_mana(manaMax), m_arme(nomArme, degatsArme), m_nom(nomPersonnage), m_giveExp(giveExp), m_giveMoney(giveMoney)
{
    m_actualPlayerLevel = niveau;
    m_maxHealth = m_vie;
    m_maxMana = m_mana;
    m_vie = m_maxHealth;
    m_mana = m_maxMana;
    m_statsLevelUp = 1;
    m_nextLevelExp = 100;
    m_currentExp = giveExp;

    // End game statistics init :
    m_ennemisVaincus = 0;
    m_totalExperience = 0;
    m_potionsVieUsed = 0;
    m_potionsManaUsed = 0;
    m_physicalHits = 0;
    m_magicalHits = 0;
    m_missedHits = 0;
    m_totalLevelsEarned = -1; // corrected issue with character at level 1.
    m_giveExp = giveExp;
    m_giveMoney = giveMoney;
    //m_arme.SetName(nomArme);
    //m_nom = LocalizationManager::Instance().Get(nomPersonnage);
    //int upgradeStatsLevelUp = static_cast<int>(((m_arme.getDegats() * m_actualPlayerLevel) / 100.0f) * 10.0f);
    //m_statsLevelUp = upgradeStatsLevelUp;
    //m_arme.setDegats(upgradeStatsLevelUp);
    AddPossessedWeapon(1, LocalizationManager::Instance().Get("str_Invent_Weapon_3"), 24);
    UpgradeStatsBonusRatio(m_arme.getDegats(), m_WpBonusRatio, m_actualPlayerLevel);
    m_arme.setDegats(*this);
    //m_playerPossessedWeapons.push_back({1, {"str_Invent_Weapon_3", 24}});

}

Personnage::~Personnage()
{

}

// Reset the HP and MP of the charactert :
void Personnage::reset()
{
    m_vie = m_maxHealth;
    m_mana = m_maxMana;
   //m_giveExp = m_giveExp;
}


 // return the character name as a method :
 std::string Personnage::GetName()
 {
     return m_nom;
 }

int Personnage::getGiveExp() const {
    return m_giveExp;
}

// return the character health to let use the private variable in other classes :
int Personnage::GetHealth()
{
    return m_vie;
}

int Personnage::getGiveMoney() const
 {
     return m_giveMoney;
 }

 int Personnage::GetTotalMoney ()
 {
     return m_totalPlayerMoney;
 }

 double Personnage::GetWpbonusRatio()
 {
     return m_WpBonusRatio;
 }

 int Personnage::GetActualPlayerLevel()
 {
     return m_actualPlayerLevel;
 }

 void Personnage::SubstractPlayerMoney(int receivedMoney)
 {
     m_totalPlayerMoney -= receivedMoney;

 }

 void Personnage::resetNbrAffichageStatus()
 {
     m_nbrAffichageStatus = 1;
 }

 int Personnage::GetNbrAffichageStatus()
 {
     return m_nbrAffichageStatus;
 }

 void Personnage::TotalWeaponBrought()
 {
     m_totalWeaponsBrougth += 1;
 }

void Personnage::AddPossessedWeapon(int id, const std::string& nom, int atk)
{
    m_playerPossessedWeapons.push_back({id, {nom, atk}});
}


void Personnage::UpdateWpDamage()
{
    UpgradeStatsBonusRatio(m_arme.getDegats(), m_WpBonusRatio, m_actualPlayerLevel);
    m_arme.setDegats(*this);

}

 std::vector<std::pair<int, std::pair<std::string, int>>> Personnage::GetPossessedWeapons()
 {
     return m_playerPossessedWeapons;
 }

// -------------------------------------------------------------------- Check if the character is alive :
bool Personnage::estVivant()
{
    if (m_vie > 0)
    {
        //std::cout << m_nom << " est vivant !" << endl;
        return true;
    }
    else
    {
        //std::cout << m_nom << " n'est pas vivant !" << endl;
        return false;
    }
}

// -------------------------------------------------------------------- Add value to the Defeated enemies statistics :
int Personnage::defeatedEnemies()
{
    int defeatedNpc;
    m_ennemisVaincus += 1;
    defeatedNpc = m_ennemisVaincus;
    return defeatedNpc;

}

void Personnage::recevoirDegats(int nbDegats)
{
    m_vie -= nbDegats;

     if(m_vie > 0)
    {

    //cout << m_nom << " recoit " << nbDegats << " degats !" << endl;
    }

    if (m_vie <= 0)
    {
        m_vie = 0;
        //cout << m_nom << " n'a plus de HP !" << endl;
        //afficherEtat();
    // Need to retrieve the player object and the totalLevels var, need to make a new method to update only player?
    //afficherStatsEnd((Personnage &player, int totalLevels));
    }
}

double Personnage::UpgradeStatsBonusRatio (int StatStatistic, double bonusRatio, int ActualPlayerLevel)
{
    //double upgradeDmg = (((StatStatistic / 100.0) * bonusRatio) * ActualPlayerLevel);
    double upgradedStat = StatStatistic * (1 + bonusRatio * log(ActualPlayerLevel + 1));


    // cout << "*/*/*/*/*/*/ Stat Upgrade is now : " << upgradedStat << endl;

    return upgradedStat;
}


// -------------------------------------------------------------------- Calculate the character's Experience Points :
void Personnage::LevelUp(int levelUpParam, int levelQty, string nomPersonnage)
{
    m_totalLevelsEarned += levelQty;



    // -------------------------------------------------- Issue with m_arme.setdegats() when changing weapon, need to use the UpdateStatsBonusRatio() when creating the weapon object.
    // Level up silently using a loop.
    if(levelUpParam == 1)
    {
        for(int i = 0; i < levelQty - 1; ++i)
        {
            m_actualPlayerLevel += 1;
            //m_statsLevelUp = upgradeStatsLevelUp;
            //int niveauPersonnage = m_actualPlayerLevel;
            m_maxHealth = UpgradeStatsBonusRatio (m_maxHealth, m_HpBonusRatio, m_actualPlayerLevel);
            // upgradeHealth;
            m_maxMana = UpgradeStatsBonusRatio (m_maxMana, m_MpBonusRatio, m_actualPlayerLevel);
            // upgradeMana;
            m_vie = m_maxHealth;
            m_mana = m_maxMana;
            m_nextLevelExp = UpgradeStatsBonusRatio (m_nextLevelExp, m_NextLevelBonusRatio, m_actualPlayerLevel);

            m_giveExp = UpgradeStatsBonusRatio (m_giveExp, m_GiveExpBonusRatio, m_actualPlayerLevel);
            m_giveMoney = UpgradeStatsBonusRatio (m_giveMoney, m_GiveMoneyBonusRatio, m_actualPlayerLevel);
            //m_arme.setDegats(m_statsLevelUp);
            //m_arme.setDegats(UpgradeStatsBonusRatio(m_arme.getDegats(), m_WpBonusRatio, m_actualPlayerLevel));
            m_arme.setDegats(*this);
        }

    }
    // Level up and notify of each level up.
    else if (levelUpParam == 2)
    {
        for(int i = 0; i < levelQty; ++i)
        {
            m_actualPlayerLevel += 1;
            //m_statsLevelUp = m_statsLevelUp;

            m_maxHealth = UpgradeStatsBonusRatio (m_maxHealth, m_HpBonusRatio, m_actualPlayerLevel);
            // upgradeHealth;
            m_maxMana = UpgradeStatsBonusRatio (m_maxMana, m_MpBonusRatio, m_actualPlayerLevel);
            // upgradeMana;
            m_vie = m_maxHealth;
            m_mana = m_maxMana;
            m_nextLevelExp = UpgradeStatsBonusRatio (m_nextLevelExp, m_NextLevelBonusRatio, m_actualPlayerLevel);

            m_giveExp = UpgradeStatsBonusRatio (m_giveExp, m_GiveExpBonusRatio, m_actualPlayerLevel);
            m_giveMoney = UpgradeStatsBonusRatio (m_giveMoney, m_GiveMoneyBonusRatio, m_actualPlayerLevel);
            //m_arme.setDegats(m_statsLevelUp);
            //m_arme.setDegats(UpgradeStatsBonusRatio(m_arme.getDegats(), m_WpBonusRatio, m_actualPlayerLevel));
            m_arme.setDegats(*this);
        }
            cout << "##" << nomPersonnage << " " << LocalizationManager::Instance().Get("str_Char_Earn") << " " << levelQty << " " << LocalizationManager::Instance().Get("str_Char_EarnLevLvls") << " : " << LocalizationManager::Instance().Get("str_Char_EarnLevel") << " = " << m_actualPlayerLevel << " HP = " << m_maxHealth << " MP = " << m_maxMana << endl;
    }
    // Simple level up that gives 1 level to the character.
    else if (levelUpParam == 0)
    {

            m_actualPlayerLevel += 1;
            //m_statsLevelUp = upgradeStatsLevelUp;
            //int niveauPersonnage = m_actualPlayerLevel;
            m_maxHealth = UpgradeStatsBonusRatio (m_maxHealth, m_HpBonusRatio, m_actualPlayerLevel);
            // upgradeHealth;
            m_maxMana = UpgradeStatsBonusRatio (m_maxMana, m_MpBonusRatio, m_actualPlayerLevel);
            // upgradeMana;
            m_vie = m_maxHealth;
            m_mana = m_maxMana;
            m_nextLevelExp = UpgradeStatsBonusRatio (m_nextLevelExp, m_NextLevelBonusRatio, m_actualPlayerLevel);

            m_giveExp = UpgradeStatsBonusRatio (m_giveExp, m_GiveExpBonusRatio, m_actualPlayerLevel);
            m_giveMoney = UpgradeStatsBonusRatio (m_giveMoney, m_GiveMoneyBonusRatio, m_actualPlayerLevel);
            //m_arme.setDegats(m_statsLevelUp);
            //m_arme.setDegats(UpgradeStatsBonusRatio(m_arme.getDegats(), m_WpBonusRatio, m_actualPlayerLevel));
            m_arme.setDegats(*this);

            cout << "## " << nomPersonnage << " " << LocalizationManager::Instance().Get("str_Char_EarnOne") << " " << LocalizationManager::Instance().Get("str_Char_EarnLevel") << " = " << m_actualPlayerLevel << " HP = " << m_maxHealth << " MP = " << m_maxMana << endl;
    }

}

// -------------------------------------------------------------------- Calculate character experience points :
void Personnage::EarnExpPoints(int expPointsEarned)
{
    //cout << "Calcul en cours... " << expPointsEarned << endl;

    cout << m_nom << " " << LocalizationManager::Instance().Get("str_Char_EarnXP") << " " << expPointsEarned << " XP !\n" << endl;

    int totalEarnedLevels = 0;
    int savedExp;
    m_currentExp += expPointsEarned;

    m_totalExperience += expPointsEarned;



    if(m_currentExp >= m_nextLevelExp)
    {
        while (m_currentExp >= m_nextLevelExp)
        {
            // cout << "Current Exp = " << m_currentExp << " Next level Exp = " << m_nextLevelExp << " Exp pts earned = " << expPointsEarned << " Saved Exp = " << savedExp << " Total Lvls = " << totalEarnedLevels << endl;

            totalEarnedLevels += 1;
            // sauvegarde du trop plein d'exp
            savedExp = m_currentExp - m_nextLevelExp;
            expPointsEarned -= m_nextLevelExp;
            // mise a jour de l'exp necessaire pour le niveau suivant
            //m_nextLevelExp += (m_nextLevelExp / 100) * 30;
            // mise a jour de l'exp actuel
            m_currentExp = savedExp;


        }

        LevelUp(2, totalEarnedLevels, m_nom);

    }

        //cout << "\n" << m_currentExp << " XP / " << m_nextLevelExp << " XP" << endl;
    return;

}

// -------------------------------------------------------------------- Manual attacks :
void Personnage::attaquer(Personnage &cible)
{
    int degats = rand() % m_arme.getDegats() + m_statsLevelUp;;
    cible.recevoirDegats(degats);
    std::cout << "----- "  << m_nom << " " << LocalizationManager::Instance().Get("str_Char_Inflict") << " " << degats << " " << LocalizationManager::Instance().Get("str_Char_DmgTo") << " " << cible.m_nom << " !" << std::endl;
    m_physicalHits += 1;
}

void Personnage::attaquerMagie(Personnage &cible)
{

  if (m_mana > 0 && m_mana - 45 >= 0)
            {
            int degats = rand() % m_arme.getDegats() + (m_statsLevelUp * 2);
    cible.recevoirDegats(degats);
    m_mana -= 45;
    std::cout << "----- " << m_nom << " " << LocalizationManager::Instance().Get("str_Char_Inflict") << " " << degats << " " << LocalizationManager::Instance().Get("str_Char_DmgManaTo") << " " << cible.m_nom << " !" << std::endl;
    m_magicalHits += 1;
            }

            return;
}


// -------------------------------------------------------------------- Change character weapon :
void Personnage::changerArme(string nomNouvelleArme, int degatsNouvelleArme)
{
    m_arme.changer(nomNouvelleArme, degatsNouvelleArme);
    m_arme.setDegats(*this);
}



// -------------------------------------------------------------------- Draw Character Status bars :
string Personnage::CalcExpBar()
{
    // Longueur de la barre = 10 unités (modifiable)
    int barLength = 10;

    // Pourcentage d'XP actuelle sur le total requis
    float percentage = (float)m_currentExp / m_nextLevelExp;

    int filledUnits = percentage * barLength;
    int emptyUnits = barLength - filledUnits;

    string bar = "[";
    for (int i = 0; i < filledUnits; ++i)
        bar += "#";
    for (int i = 0; i < emptyUnits; ++i)
        bar += ".";
    bar += "]";

    return bar;
}

string Personnage::CalcHealthBar()
{
    // Longueur de la barre = 10 unités (modifiable)
    int barLength = 10;

    // Pourcentage d'XP actuelle sur le total requis
    float percentage = (float)m_vie / m_maxHealth;

    int filledUnits = percentage * barLength;
    int emptyUnits = barLength - filledUnits;

    string bar = "[";
    for (int i = 0; i < filledUnits; ++i)
        bar += "|";
    for (int i = 0; i < emptyUnits; ++i)
        bar += ".";
    bar += "]";

    return bar;
}

string Personnage::CalcManaBar()
{
    // Longueur de la barre = 10 unités (modifiable)
    int barLength = 10;

    // Pourcentage d'XP actuelle sur le total requis
    float percentage = (float)m_mana / m_maxMana;

    int filledUnits = percentage * barLength;
    int emptyUnits = barLength - filledUnits;

    string bar = "[";
    for (int i = 0; i < filledUnits; ++i)
        bar += "$";
    for (int i = 0; i < emptyUnits; ++i)
        bar += ".";
    bar += "]";

    return bar;
}

// -------------------------------------------------------------------- Draw Character Status window :

void Personnage::afficherEtat()
{
    cout << "\n______________________________________________[" << m_nbrAffichageStatus << "]" << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Name") << m_nom << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Level") << m_actualPlayerLevel << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Player_Exp") << CalcExpBar() << " ";
    cout << m_currentExp << " XP / " << m_nextLevelExp << " XP" << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Health") << CalcHealthBar() << " ";
    cout << m_vie << " / " << m_maxHealth << " HP" << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Mana") << CalcManaBar() << " ";
    cout << m_mana << " / " << m_maxMana << " MP" << endl;
    m_arme.afficherPlayer(m_statsLevelUp);
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Player_Money") << m_totalPlayerMoney << " $" << endl;
    cout << "______________________________________________\n" << endl;
    m_nbrAffichageStatus += 1;
}

void Personnage::afficherEtatNpc(bool showWinItems, Personnage &player)
{
    cout << "\n______________________________________________[" << player.GetNbrAffichageStatus() << "]" << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Name") << m_nom << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Level") << m_actualPlayerLevel << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Health") << CalcHealthBar() << " ";
    cout << m_vie << " / " << m_maxHealth << " HP" << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Mana") << CalcManaBar() << " ";
    cout << m_mana << " / " << m_maxMana << " MP" << endl;
    m_arme.afficher(m_statsLevelUp);
    if(showWinItems)
    {
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Npc_Exp") << m_giveExp << " XP" << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Npc_Money") << m_giveMoney << " $" << endl;
    }
    cout << "______________________________________________\n" << endl;
    m_nbrAffichageStatus += 1;
}

// -------------------------------------------------------------------- Automatic usage :
void Personnage::utiliserPotionGenerique(Personnage &cible, bool isMana)
{
    long long& valeurActuelle = isMana ? cible.m_mana : cible.m_vie;
    long long& valeurMax = isMana ? cible.m_maxMana : cible.m_maxHealth;
    int& potionsRestantes = isMana ? cible.m_totalPotionsMP : cible.m_totalPotionsHP;
    int& compteurUtilisation = isMana ? cible.m_potionsManaUsed : cible.m_potionsVieUsed;
    std::string typePotion = isMana ? LocalizationManager::Instance().Get("str_Char_UsePotion_TypeMana") : LocalizationManager::Instance().Get("str_Char_UsePotion_TypeHealth");
    std::string typeAbr = isMana ? "MP" : "HP";

    if (potionsRestantes <= 0)
    {
        std::cout << cible.m_nom << " " << LocalizationManager::Instance().Get("str_Char_UsePotion_HasNoMoreP") << " " << typePotion << " !" << std::endl;
        return;
    }

    if (valeurActuelle >= valeurMax)
    {
        std::cout << "----- " << cible.m_nom << " " << LocalizationManager::Instance().Get("str_Char_UsePotion_HealWithP") << " " << typePotion << " " << LocalizationManager::Instance().Get("str_Char_UsePotion_PotionUseless") << std::endl;
        return;
    }

    int launchDice = rand() % 4;
    int gain = 15;
    int percentMax = valeurMax / 100;

    if (launchDice == 1 || launchDice == 3)
    {
        gain = percentMax * (rand() % 25 + 15); // (rand() % 11 + 5) 5% à 15%
        std::cout << "----- " << cible.m_nom << " " << LocalizationManager::Instance().Get("str_Char_UsePotion_UseMiddleP") << " " << typePotion << " ";
    }
    else if (launchDice == 2 || launchDice == 4)
    {
        gain = percentMax * (rand() % 15 + 10); // 5% à 10%
        std::cout << "----- " << cible.m_nom << " " << LocalizationManager::Instance().Get("str_Char_UsePotion_UseLittleP") << " " << typePotion << " ";
    }
    else
    {
        potionsRestantes--;
        std::cout << "----- " << cible.m_nom << " " << LocalizationManager::Instance().Get("str_Char_UsePotion_UseDropP") << " " << typePotion
                  << " (x" << potionsRestantes << ") " << LocalizationManager::Instance().Get("str_Char_UsePotion_UseBreakP") << std::endl;
        return;
    }

    if (gain <= 0){
        gain = 45;
    }
    valeurActuelle += gain;
    if (valeurActuelle > valeurMax) valeurActuelle = valeurMax;

    potionsRestantes--;
    compteurUtilisation++;

    std::cout << "(x" << potionsRestantes << ") " << LocalizationManager::Instance().Get("str_Char_UsePotion_AndRestoreP") << " " << gain << " " << typeAbr << " !" << std::endl;
}

// -------------------------------------------------------------------- Automatic attacks :

void Personnage::attaquePhysique(Personnage &cible)
{
    if(cible.estVivant())
    {
int launchDice = rand() % 5 + 1; // Tire un nombre entre 1 et 3
        if (launchDice != 1) // Utiliser '==' pour comparaison
        {
    int degats = rand() % m_arme.getDegats() + m_statsLevelUp;
    cible.recevoirDegats(degats);
    std::cout << "----- "  << m_nom << " " << LocalizationManager::Instance().Get("str_Char_Inflict") << " " << degats << " " << LocalizationManager::Instance().Get("str_Char_DmgTo") << " " << cible.m_nom << " !" << std::endl;
    cible.m_physicalHits += 1;
    return;
        }
        std::cout << "----- " << m_nom << " " << LocalizationManager::Instance().Get("str_Char_MissAtk") << std::endl;
        cible.m_missedHits += 1;
    }

}

void Personnage::attaqueMagique(Personnage &cible)
{
    if(cible.estVivant())
    {

  int launchDice = rand() % 2 + 1; // Tire un nombre entre 1 et 3
        if (launchDice == 1) // Utiliser '==' pour comparaison
        {

            // Attaque la cible avec du mana
            // Diminution du mana

            if (m_mana > 0 && m_mana - 45 * m_actualPlayerLevel > 0)
            {
            int degats = rand() % m_arme.getDegats() + (m_statsLevelUp * 2);
    cible.recevoirDegats(degats);
    m_mana -= 45 * m_actualPlayerLevel;
    std::cout << "----- " << m_nom << " " << LocalizationManager::Instance().Get("str_Char_Inflict") << " " << degats << " " << LocalizationManager::Instance().Get("str_Char_DmgManaTo") << " " << cible.m_nom << " !" << std::endl;
    cible.m_magicalHits += 1;

            return; // Ne pas attaquer si potion utilisée
            }
        }
        std::cout << "----- " << m_nom << " " << LocalizationManager::Instance().Get("str_Char_MissAtk") << std::endl;
        cible.m_missedHits += 1;
        // attaquePhysique(cible);
}
}

// -------------------------------------------------------------------- AutoFight script :

void Personnage::autoFight(Personnage &cible)
{
    if (!estVivant() || !cible.estVivant())
        return;

    // Calcul des % de vie/mana
    double vieRatio = static_cast<double>(m_vie) / m_maxHealth;
    double manaRatio = static_cast<double>(m_mana) / m_maxMana;

    // Comportement défensif : soin d’urgence si PV trop bas
    // ------------------ Probleme car le NPC utilise le meme script que le personnage = combats interminables et hasardeux. !!!!!!!!!!!!!!!!!!!!
    if (vieRatio < 0.25 && m_totalPotionsHP > 0)
    {
        std::cout << m_nom << " " << LocalizationManager::Instance().Get("str_Char_HealthCritP") << std::endl;
        utiliserPotionGenerique(*this, false);
    }
    else if (manaRatio < 0.2 && m_totalPotionsMP > 0)
    {
        std::cout << m_nom << " " << LocalizationManager::Instance().Get("str_Char_ManaCritP") << std::endl;
        utiliserPotionGenerique(*this, true);
    }
    else
    {
        // Tactique : aléatoire entre physique/magique (avec préférence magie si mana suffisant)
        int choix = rand() % 100;

        if (manaRatio > 0.3 && choix < 60)
        {
            attaqueMagique(cible);
        }
        else
        {
            attaquePhysique(cible);
        }
    }

    // Petite pause pour lisibilité (optionnelle)
    //std::this_thread::sleep_for(std::chrono::milliseconds(400));
}


// -------------------------------------------------------------------- Draw Character statistics :
 void Personnage::afficherStatsEnd(Personnage &player, int totalLevels)
 {
     // problème de comptage du nombre de coups portés car il n'y a pas de
     // personnage spécifié dans la mise a jour de la variable.
     // corrigé avec (Personnage &cible), à améliorer.
    cout << "\n*______________________________________________*" << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_StatsEnd_DefeatedNpc") << " " << player.m_ennemisVaincus << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_StatsEnd_LevelsEarned") << " " << player.m_totalLevelsEarned << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_StatsEnd_TotalXp") << " " << player.m_totalExperience << endl;
    cout << "________________________________________________" << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_StatsEnd_TotalUsedHp") << " " << player.m_potionsVieUsed << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_StatsEnd_TotalUsedMp") << " " << player.m_potionsManaUsed << endl;
    cout << "________________________________________________" << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_StatsEnd_PhyAtks") << " " << player.m_physicalHits << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_StatsEnd_MagAtks") << " " << player.m_magicalHits << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_StatsEnd_MissAtks") << " " << player.m_missedHits << endl;
    cout << "________________________________________________" << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_StatsEnd_TotalMoney") << " " << player.m_totalGameMoney << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_StatsEnd_TotalBrgt1Wp") << " " << player.m_totalWeaponsBrougth << endl;
    cout << "________________________________________________" << endl;
    cout << " " << LocalizationManager::Instance().Get("str_Char_StatsEnd_VistdLvls") << " " << totalLevels << endl;
    cout << "*______________________________________________*\n" << endl;
 }

 // -------------------------------------------------------------------- Manage character money :
 void Personnage::receiveMoney(int receiveMoney)
 {
     m_totalPlayerMoney += receiveMoney;
     m_totalGameMoney += receiveMoney;
     cout << "+ " << receiveMoney << " = " << m_totalPlayerMoney << " $" << endl;

 }

 // -------------------------------------------------------------------- Methods for Shop Menu and character inventory :
 void Personnage::SetInventPotionsHP(Personnage &player, int potionQty)
 {
     m_totalPotionsHP += potionQty;

 }

 void Personnage::SetInventPotionsMP(Personnage &player, int potionQty)
 {
     m_totalPotionsMP += potionQty;

 }

 void Personnage::SetInventPotionsDeath(Personnage &player, int potionQty)
 {
     m_totalDeathPotions += potionQty;

 }

 void Personnage::SetInventLvlUpItem(Personnage &player, int potionQty)
 {
     m_totalLvlUpItem += potionQty;

 }

 void Personnage::DisplayInventory()
 {

    cout << "\n_________________________________________________________" << endl;
    cout << "                        Inventaire" << endl;
    cout << "_________________________________________________________" << endl;
    cout << LocalizationManager::Instance().Get("str_Invent_Entry1") << " " << m_totalPlayerMoney << endl;
    cout << LocalizationManager::Instance().Get("str_Invent_Entry2") << " " << m_totalPotionsHP << endl;
    cout << LocalizationManager::Instance().Get("str_Invent_Entry3") << " " << m_totalPotionsMP << endl;
    cout << LocalizationManager::Instance().Get("str_Invent_Entry4") << " " << m_totalDeathPotions << endl;
    cout << LocalizationManager::Instance().Get("str_Invent_Entry5") << " " << m_totalLvlUpItem << endl;
    cout << "_________________________________________________________\n" << endl;
 }

