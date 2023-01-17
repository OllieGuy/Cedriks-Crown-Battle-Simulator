// Cedrik Battle Simulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include<string>

using namespace std;
int seedChanger = 0;
class Enemy
{
public:
    int health;
    int rollUnder;
    int attack;
    string name;
    Enemy(int h, int r, int a, string n)
    {
        health = h;
        rollUnder = r;
        attack = a;
        name = n;
    }
};
class Player
{
public:
    int health;
    int attack;
    int defence;
    Player(int h, int a, int d)
    {
        health = h;
        attack = a;
        defence = d;
    }
};
class Battler
{
public:
    static int randomNum(int min, int max)
    {
        //int seedChanger = 0;
        srand(time(NULL) + seedChanger);
        int generatedNum = rand() % (max - min + 1) + min;
        seedChanger = seedChanger + 1;
        return(generatedNum);
    }
    static void battle(Player player, Enemy enemy, int battleTimes)
    {
        //initialisations
        int totalDmgToPlayer = 0;
        int playerWins = 0;
        int enemyWins = 0;
        int wonDamaged = 0;
        int tmpEHealth;
        int tmpPHealth;

        //for the amount of battles specified
        for (int i = 0; i < battleTimes; i++)
        {
            //uses temp variables as to not affect main variables
            tmpEHealth = enemy.health;
            tmpPHealth = player.health;
            while (tmpEHealth > 0 && tmpPHealth > 0) //while neither the player nor enemy is dead
            {
                //player turn
                int hit = randomNum(1, 6);
                tmpEHealth -= hit + player.attack;
                //enemy turn
                if (tmpEHealth > 0) //if the enemy is still alive after the player attack, attack the player
                {
                    int rollForHit = randomNum(1, 6);
                    if (rollForHit <= enemy.rollUnder)
                    {
                        tmpPHealth -= enemy.attack - player.defence;
                        totalDmgToPlayer += enemy.attack - player.defence;
                    }
                }
                else if (tmpEHealth <= 0) //if the player has killed the enemy
                {
                    playerWins++;
                    wonDamaged += player.health - tmpPHealth;
                }
                if (tmpPHealth <= 0) //if the enemy has killed the player
                {
                    enemyWins++;
                }
            }
        }
        //calculations
        float avgDmgWhenWon = (float)wonDamaged / (float)playerWins;
        float avgDmg = (float)totalDmgToPlayer / (float)battleTimes;
        string playerWinPercent = to_string((((float)playerWins / (float)battleTimes) * 100)) + "%";

        //output
        cout << "\nBattle between player: \n Health: " << player.health << "\n Attack: " << player.attack << "\n Defence: " << player.defence << "\n";
        cout << "And enemy(" << enemy.name + "): \n Health: " << enemy.health << "\n Attack: " << enemy.attack << "\n Roll under to hit: " << enemy.rollUnder << "\n\nFIGHT " << battleTimes << " TIMES!";
        cout << "\nPlayer wins: " << playerWins << "\nEnemy wins: " << enemyWins << "\nPlayer win percent: " << playerWinPercent << "\nAverage damage: " << avgDmg << "\nAverage damage when fight won: " << avgDmgWhenWon;
    }
    void statsAndDisplay()
    {
        //seedChanger = 0;
        //Health, Roll under, Damage, Points
        Enemy Goblin(8, 3, 6, "Goblin");
        Enemy Spider(7, 5, 5, "Spider");
        Enemy Skeleton(9, 2, 7, "Skeleton");
        Enemy Slime(6, 2, 7, "Slime");
        Enemy Fish(1, 1, 1, "Fish");

        Enemy Shadow(14, 2, 8, "Shadow");
        Enemy TombRaider(11, 2, 8, "Tomb Raider");
        Enemy Cultist(13, 4, 6, "Cultist");
        Enemy RatKing(11, 1, 10, "RatKing");
        Enemy Mimic(9, 5, 6, "Mimic");

        Enemy Orc(18, 3, 9, "Orc");
        Enemy EvilWarlock(16, 3, 10, "Evil Warlock");
        Enemy Reaper(20, 1, 12, "Reaper");
        Enemy Cedrik(40, 3, 10, "Cedrik");

        //Health, attack, defence
        Player player1(5, 2, 3); //low level player
        Player player2(7, 5, 4); //medium level player
        Player player3(7, 7, 6); //high level player
        Player player4(8, 10, 8); //overleveled player - should win almost every fight

        //sets the enemy then makes them all fight
        Enemy currentEnemy = RatKing;
        cout << "\n\n----------";
        cout << "\nLowest Power\n";
        battle(player1, currentEnemy, 1000000);
        cout << "\n\n----------";
        cout << "\nMedium Power\n";
        battle(player2, currentEnemy, 1000000);
        cout << "\n\n----------";
        cout << "\nHigh Power\n";
        battle(player3, currentEnemy, 1000000);
        cout << "\n\n----------";
        cout << "\nOverpowered\n";
        battle(player4, currentEnemy, 1000000);
    }
};
int main()
{
    Battler b;
    b.statsAndDisplay();
};
