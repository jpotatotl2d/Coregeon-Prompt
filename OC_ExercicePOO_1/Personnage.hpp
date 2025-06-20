#ifndef DEF_PERSONNAGE
#define DEF_PERSONNAGE

#include <iostream>
#include <string>
#include <vector>
#include "Arme.hpp"
#include "Level.hpp"

class Personnage
{
    public:

    Personnage();
    //Personnage(int niveau, int vieMax, int manaMax, std::string nomArme, int degatsArme, std::string nomPersonnage, int giveExp);
    Personnage(int niveau, int vieMax, int manaMax, std::string nomArme, int degatsArme, std::string nomPersonnage, int giveExp, int giveMoney);
    ~Personnage();
    void recevoirDegats(int nbDegats);
    void attaquer(Personnage &cible);
    void attaquerMagie(Personnage &cible);
    void boirePotionDeVie(int quantitePotion);
    void boirePotionDeMana(int quantitePotion);
    void changerArme(std::string nomNouvelleArme, int degatsNouvelleArme);
    bool estVivant();
    void afficherEtat();
    void afficherEtatNpc(bool showWinItems, Personnage &player);
    void autoFight(Personnage &cible);
    void utiliserPotion(Personnage &cible);
    void utiliserPotionMana(Personnage &cible);
    void attaqueMagique(Personnage &cible);
    void attaquePhysique(Personnage &cible);

    void LevelUp(int levelUpParam, int LevelQty, std::string nomPersonnage);
    void EarnExpPoints(int expPointsEarned);

    int getGiveExp() const;
    int getGiveMoney() const;

    void afficherStatsEnd(Personnage &player, int totalLevels);

    std::string CalcExpBar();
    std::string CalcHealthBar();
    std::string CalcManaBar();

    int defeatedEnemies();
    void reset();

    void SetInventPotionsHP(Personnage &player, int potionQty);
    void SetInventPotionsMP(Personnage &player, int potionQty);
    void SetInventPotionsDeath(Personnage &player, int potionQty);
    void SetInventLvlUpItem(Personnage &player, int potionQty);

    void DisplayInventory();
    void receiveMoney(int receiveMoney);
    int GetTotalMoney ();
    void SubstractPlayerMoney(int receivedMoney);

    void utiliserPotionGenerique(Personnage &cible, bool isMana);

    std::string GetName();
    int GetHealth();

    void resetNbrAffichageStatus();
    int GetNbrAffichageStatus();

    void TotalWeaponBrought();
    std::vector<std::pair<int, std::pair<std::string, int>>> GetPossessedWeapons();
    void AddPossessedWeapon(int id, const std::string& nom, int atk);

    double UpgradeStatsBonusRatio (int StatStatistic, double bonusRatio, int ActualPlayerLevel);

    double GetWpbonusRatio();
     int GetActualPlayerLevel();
     void UpdateWpDamage();

    // ------------------------------------------------------------------ PRIVATE :

    private:

    long long m_vie = 0;
    long long m_mana = 0;
    Arme m_arme;
    std::string m_nom;

    int m_actualPlayerLevel = 0;
    int m_statsLevelUp = 0;
    long long m_currentExp = 0;
    long long m_nextLevelExp = 0;
    long long m_maxHealth = 0;
    long long m_maxMana = 0;
    long long m_giveExp = 0;
    long long m_giveMoney = 0;

    int m_nbrAffichageStatus = 1;

    int m_ennemisVaincus = 0;
    int m_totalExperience = 0;
    int m_potionsVieUsed = 0;
    int m_potionsManaUsed = 0;
    int m_physicalHits = 0;
    int m_magicalHits = 0;
    int m_missedHits = 0;
    int m_totalLevelsEarned = 0;
    int m_totalWeaponsBrougth = 0;

    // créer une methode pour assigner moins de potions aux NPCs !!!!!!!!!!!!!!!
    // probleme de décrementation des potions entre les variables de personnages?
    int m_totalPotionsHP = 3;
    int m_totalPotionsMP = 3;
    int m_totalDeathPotions = 0;
    int m_totalLvlUpItem = 0;

    long long m_totalPlayerMoney = 9999999999;
    long long m_totalGameMoney = 0;
    std::vector<std::pair<int, std::pair<std::string, int>>> m_playerPossessedWeapons; // = {{1, {"str_Invent_Weapon_3", 24}}};

    double m_WpBonusRatio = 0.06;
    double m_HpBonusRatio = 0.04;
    double m_MpBonusRatio = 0.03;
    double m_GiveExpBonusRatio = 0.08;
    double m_GiveMoneyBonusRatio = 0.08;
    double m_NextLevelBonusRatio = 0.08;




};

#endif
