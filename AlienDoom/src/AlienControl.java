/*
 * Author@ Colt Campbell
 * 
 * LOC: 594 aside from this file. 
 * 
 * Game Version: 3.0
 */

import java.util.Random;
import java.util.Scanner;
import java.util.ArrayList;
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.MenuEvent;
import javax.swing.event.MenuListener;

public class AlienControl implements ActionListener, MenuListener
{
    private int expNeeded;

    private String playerName, equippedWeapon, equippedArmor, previousWeapon, previousArmor;

    private boolean weaponSwapped = false, armorSwapped = false, isAlienDead = false, isUserDead = false;
    private boolean dcounted = false, bcounted = false, hcounted = false, scounted = false, hscounted = false; //solution to keep from multiplying too many new menuitems to show count of items
    private boolean cuircounted = false, chacounted = false, placounted = false, demcounted = false, hevcounted = false;
    
    private ArrayList<String> weaponList;
    private ArrayList<String> armorList;
    private ArrayList<String> store_weapons;
    private ArrayList<String> store_armor;
    
    private Aliens alienStats;
    private User playerStats;
    private Random generator;

    private JFrame gameMenu;
    private JFrame mainMenu;
    private JTextArea textArea;
    private JTextArea statsDisplay;
    private JMenuBar gameMenuBar = new JMenuBar();
    
    //the battle menu, allowing the user to choose which creatures he/she wishes to battle
    //note: Zarvox is not a created monster in the game yet. 
    private JMenu battle = new JMenu(" Battle ");
    private JMenuItem zorg = new JMenuItem(" Zorg ");
    private JMenuItem zarvox = new JMenuItem(" Zarvox ");
    private JMenuItem zirvex = new JMenuItem(" Zirvex ");
    private JMenuItem zarkonaut = new JMenuItem(" Zarkonaut ");
    private JMenuItem zekorov = new JMenuItem(" Zekorov ");
    private JMenuItem zandrex = new JMenuItem(" Zandrex ");
    
    //the weapons menu to sell or equip the weapons in your inventory
    private JMenu weapons = new JMenu(" Weapons ");
    private JMenuItem unequipWeapon = new JMenuItem(" Unequip Weapon ");
    private JMenuItem daggercount, bladecount, hammercount, swordcount, hevswordcount;
    private JMenu dagger = new JMenu(" Dagger ");
    private JMenuItem equipdagger = new JMenuItem(" Equip ");
    private JMenuItem selldagger = new JMenuItem(" Sell ");
    private JMenu blade = new JMenu(" Blade ");
    private JMenuItem equipblade = new JMenuItem(" Equip ");
    private JMenuItem sellblade = new JMenuItem(" Sell ");
    private JMenu hammer = new JMenu(" Hammer ");
    private JMenuItem equiphammer = new JMenuItem(" Equip ");
    private JMenuItem sellhammer = new JMenuItem(" Sell ");
    private JMenu sword = new JMenu(" Sword ");
    private JMenuItem equipsword = new JMenuItem(" Equip ");
    private JMenuItem sellsword = new JMenuItem(" Sell ");
    private JMenu hevSword = new JMenu(" Heavenly Sword ");
    private JMenuItem equiphevSword = new JMenuItem(" Equip ");
    private JMenuItem sellhevSword = new JMenuItem(" Sell ");
    
    //the armor menu to sell or equip the armor in your inventory
    private JMenu armor = new JMenu(" Armor ");
    private JMenuItem unequipArmor = new JMenuItem(" Unequip Armor ");
    private JMenuItem cuirasscount, chamailcount, plamailcount, demarmcount, hevarmcount;
    private JMenu cuirass = new JMenu(" Cuirass ");
    private JMenuItem equipcuirass = new JMenuItem(" Equip ");
    private JMenuItem sellcuirass = new JMenuItem(" Sell ");
    private JMenu chamail = new JMenu(" Chain Mail ");
    private JMenuItem equipchamail = new JMenuItem(" Equip ");
    private JMenuItem sellchamail = new JMenuItem(" Sell ");
    private JMenu plamail = new JMenu(" Plate Mail ");
    private JMenuItem equipplamail = new JMenuItem(" Equip ");
    private JMenuItem sellplamail = new JMenuItem(" Sell ");
    private JMenu demarmor = new JMenu(" Demon Armor ");
    private JMenuItem equipdemarmor = new JMenuItem(" Equip ");
    private JMenuItem selldemarmor = new JMenuItem(" Sell ");
    private JMenu hevarmor = new JMenu(" Heavenly Armor ");
    private JMenuItem equiphevarmor = new JMenuItem(" Equip ");
    private JMenuItem sellhevarmor = new JMenuItem(" Sell ");
    
    //the user's store, to buy items
    private JMenu store = new JMenu(" Store ");
    private JMenu health = new JMenu(" Health Vials ");
    private JMenuItem healthpot = new JMenuItem(" HP Potion ");
    private JMenuItem maxhealth = new JMenuItem(" Max Health Potion ");
    private JMenuItem supermaxhealth = new JMenuItem(" Super Max HP ");
    private JMenuItem buydagger = new JMenuItem(" Dagger ");
    private JMenuItem buyblade = new JMenuItem(" Blade ");
    private JMenuItem buyhammer = new JMenuItem(" Hammer ");
    private JMenuItem buysword = new JMenuItem(" Sword ");
    private JMenuItem buyhevsword = new JMenuItem(" Heavenly Sword ");
    private JMenuItem buycuirass = new JMenuItem(" Cuirass ");
    private JMenuItem buychamail = new JMenuItem(" Chain Mail ");
    private JMenuItem buyplamail = new JMenuItem(" Plate Mail ");
    private JMenuItem buydemarmor = new JMenuItem(" Demon Armor ");
    private JMenuItem buyhevarmor = new JMenuItem(" Heavenly Armor ");
    
    //the quit menu for the game itself
    private JMenu gamefilemenu = new JMenu(" File ");
    private JMenuItem save = new JMenuItem(" Save ");
    private JMenuItem ingameload = new JMenuItem(" Load ");
    private JMenuItem gamequit = new JMenuItem(" Exit to Main Menu ");
    
    //the main menu for the main screen before the actual game play begins
    private JMenuBar mainMenuBar = new JMenuBar();
    private JMenu mainfilemenu = new JMenu(" File ");
    private JMenuItem start = new JMenuItem(" New Game");
    private JMenuItem load = new JMenuItem(" Load ");
    private JMenuItem exiter = new JMenuItem(" Exit Program");
    

    protected AlienControl()
    {
            expNeeded = 10;
            playerName = "";

            playerStats = new User(15,15,10,10,10,10,1,2,7,7,6,6);
            alienStats = new Aliens(10,10,7,7,2,2,5,5,10,10,0,0);
            Help faq = new Help();
            weaponList = new ArrayList<>();
            armorList = new ArrayList<>();
            store_weapons = new ArrayList<>();
            store_armor = new ArrayList<>();
            store_weapons.add("Fists");
            store_weapons.add("Dagger");
            store_weapons.add("Blade");
            store_weapons.add("Hammer");
            store_weapons.add("Sword");
            store_weapons.add("Heavenly Sword");
            store_armor.add("Sack Cloth");
            store_armor.add("Cuirass");
            store_armor.add("Chain Mail");
            store_armor.add("Plate Mail");
            store_armor.add("Demon Armor");
            store_armor.add("Heavenly Armor");
            armorList.add("Sack Cloth");
            weaponList.add("Fists");
            equippedWeapon = weaponList.get(0);
            equippedArmor = armorList.get(0);
            previousWeapon = weaponList.get(0);
            previousArmor = armorList.get(0);
            generator = new Random();
    }
        
    private int getWeaponNumber(String s)
    {
        return store_weapons.indexOf(s);
    }
    private int getArmorNumber(String s)
    {
        return store_armor.indexOf(s);
    }

    private void clearTextArea()
    {
        textArea.selectAll();
        textArea.replaceSelection("");
    }

    private void updateStatsDisplay()
    {
        statsDisplay.selectAll();
        statsDisplay.replaceSelection("");
        statsDisplay.append("Your current weapon is a(n) " + equippedWeapon + ".\n");
        statsDisplay.append("Your current armor is a(n) " + equippedArmor + ".\n");
        statsDisplay.append("Your level is " + playerStats.getLvl() + ".\n");
        statsDisplay.append("The experience needed to level up is " + expNeeded + ".\n");
        statsDisplay.append("Your health is " + playerStats.getHp() + ".\n");
        statsDisplay.append("Your maximum health is " + playerStats.getIHp() + ".\n");
        statsDisplay.append("Your strength/attack is " + playerStats.getStr() + ".\n");
        statsDisplay.append("Without your weapon, your strength is " + playerStats.getIStr() + ".\n");
        statsDisplay.append("Your agility is " + playerStats.getAgil() + ".\n");
        statsDisplay.append("Your endurance is " + playerStats.getEdnce() + ".\n");
        statsDisplay.append("Your defense is " + playerStats.getDef() + ".\n");
        statsDisplay.append("Without your armor, your defense is " + playerStats.getIDef() + ".\n");
        statsDisplay.append("You also have " + alienStats.getCrystals() + " crystals.\n");
        statsDisplay.append("And " + alienStats.getExp() + " experience.\n");
        statsDisplay.append("Your max inventory is " + playerStats.getIinv() + ".\n");
        statsDisplay.append("You currently have " + playerStats.getInv() + " available inventory slots.\n");
        statsDisplay.append("You also have probability to hit of " + playerStats.getProb() + ".\n");

    }

    private void battle()
    {
        clearTextArea();
        while(isAlienDead != true && isUserDead != true)
        {
            //actual battle code here, which needs some serious thinking and recoding
            int temp = generator.nextInt(playerStats.getProb()%20+1); //plus 1 ensures positive alignment 
            if (temp == 0 || temp == 1 || temp == 2 || temp == 3)
            {
                    if (generator.nextInt(alienStats.getEdef()) > playerStats.getStr())
                    {
                            alienStats.setEhp((alienStats.getEdef() + alienStats.getEhp()) - playerStats.getStr());
                    }
                    else
                            alienStats.setEhp(alienStats.getEhp() - playerStats.getStr());
            }
            if (generator.nextInt(alienStats.getAprob()) != 0)
            {
                    if (generator.nextInt(playerStats.getAgil()) > alienStats.getEAgil())
                    {
                            textArea.append("You dodged the alien.\n");
                    }
                    else if (generator.nextInt(playerStats.getDef()) < alienStats.getEatk())
                    {
                            textArea.append("You took a hit from the alien!\n");
                            playerStats.setHp((playerStats.getHp() + playerStats.getDef()) - alienStats.getEatk());
                    }
            }

            //none of this needs to change, it's just the death of the alien, or you
            if (alienStats.getEhp() <= 0)
            {
                textArea.append("You defeated the alien!\n");

                alienStats.setAnyExp();
                textArea.append("You have gained " + alienStats.getExp() + " experience.\n");

                alienStats.setAnyCrys();
                textArea.append("You have gained " + alienStats.getCrystals() + " crystals.\n");

                //now the level up sequence (also needs work, why is the user experience bar part of alien stats?)
                if (alienStats.getExp() >= expNeeded)
                {
                        do{
                                playerStats.lvlUp();
                                textArea.append("You have leveled up!\n");
                                alienStats.setExp(alienStats.getExp() - expNeeded);

                                expNeeded = expNeeded + 3;
                        }while(alienStats.getExp()>=expNeeded);

                        alienStats.setExp(alienStats.getExp() % expNeeded);
                }

                //random health vile pick up
                if (generator.nextInt(10) == 0)
                {
                        playerStats.setHp(playerStats.getIHp());
                        textArea.append("You have found a health vile off of the alien's corpse. Your health is restored.\n");
                }
                isAlienDead = true;
            }
            if (playerStats.getHp() <= 0)
            {
                isUserDead = true; 
                textArea.append("You've died. Please try again!\n");
                JOptionPane.showMessageDialog(gameMenu, "You've died. Please try again!", "Alert", JOptionPane.INFORMATION_MESSAGE);
                gameMenu.dispose();
                AlienControl next = new AlienControl();
                next.generateMainMenuGUI();
            }
        }
        updateStatsDisplay();
        alienStats.setAlienType(""); //re-initializes alientype after battle
        isAlienDead = false;//once we realize the battle is over, reset isDead
    }

    @Override
    public void menuCanceled(MenuEvent e)
    {
        if (e.getSource() == weapons)
        {
            textArea.append("The menu has been canceled.");
        }
    }

    @Override
    public void menuDeselected(MenuEvent e)
    {
        if (e.getSource() == weapons)
        {
            weapons.removeAll();
        }
        else if (e.getSource() == armor)
        {
            armor.removeAll();
        }
    }

    @Override
    public void menuSelected(MenuEvent e)
    {
        if (e.getSource() == weapons)
        {
            int countd = 0, countb = 0, counth = 0, counts = 0, counths = 0;
            if (!(equippedWeapon.equals("Fists")))
            {
                weapons.add(unequipWeapon);
            }

            for (int i = 0; i < weaponList.size(); i++)
            {
                if (weaponList.get(i).equals("Dagger"))
                {
                    weapons.add(dagger); 
                    countd += 1;
                }
                if (weaponList.get(i).equals("Blade"))
                {
                    weapons.add(blade);
                    countb += 1;
                }
                if (weaponList.get(i).equals("Hammer"))
                {
                    weapons.add(hammer);
                    counth += 1;
                }
                if (weaponList.get(i).equals("Sword"))
                {
                    weapons.add(sword);
                    counts += 1;
                }
                if (weaponList.get(i).equals("Heavenly Sword"))
                {
                    weapons.add(hevSword);
                    counths += 1;
                }
            }
            if (dcounted == true)
            {
                dagger.remove(daggercount);
            }
            daggercount = new JMenuItem(" Count: " + countd + " ");
            dcounted = true;
            dagger.add(daggercount);

            if (bcounted == true)
            {
                blade.remove(bladecount);
            }
            bladecount = new JMenuItem(" Count: " + countb + " ");
            bcounted = true;
            blade.add(bladecount);

            if (hcounted == true)
            {
                hammer.remove(hammercount);
            }
            hammercount = new JMenuItem(" Count: " + counth + " ");
            hcounted = true;
            hammer.add(hammercount);

            if (scounted == true)
            {
                sword.remove(swordcount);
            }
            swordcount = new JMenuItem(" Count: " + counts + " ");
            scounted = true;
            sword.add(swordcount);

            if (hscounted == true)
            {
                hevSword.remove(hevswordcount);
            }
            hevswordcount = new JMenuItem(" Count: " + counths + " ");
            hscounted = true;
            hevSword.add(hevswordcount);
        }
        else if (e.getSource() == armor)
        {
            int countcuir = 0, countcha = 0, countpla = 0, countdem = 0, counthev = 0;
            if (!(equippedArmor.equals("Sack Cloth")))
            {
                armor.add(unequipArmor);
            }
            for (int i = 0; i < armorList.size(); i++)
            {
                if (armorList.get(i).equals("Cuirass"))
                {
                    armor.add(cuirass);
                    countcuir += 1;
                }
                if (armorList.get(i).equals("Chain Mail"))
                {
                    armor.add(chamail);
                    countcha += 1;
                }
                if (armorList.get(i).equals("Plate Mail"))
                {
                    armor.add(plamail);
                    countpla += 1;
                }
                if (armorList.get(i).equals("Demon Armor"))
                {
                    armor.add(demarmor);
                    countdem += 1;
                }
                if (armorList.get(i).equals("Heavenly Armor"))
                {
                    armor.add(hevarmor);
                    counthev += 1;
                }
            }
            if (cuircounted == true)
            {
                cuirass.remove(cuirasscount);
            }
            cuirasscount = new JMenuItem(" Count: " + countcuir + " ");
            cuircounted = true;
            cuirass.add(cuirasscount);

            if (chacounted == true)
            {
                chamail.remove(chamailcount);
            }
            chamailcount = new JMenuItem(" Count: " + countcha + " ");
            chacounted = true;
            chamail.add(chamailcount);

            if (placounted == true)
            {
                plamail.remove(plamailcount);
            }
            plamailcount = new JMenuItem(" Count: " + countpla + " ");
            placounted = true;
            plamail.add(plamailcount);

            if (demcounted == true)
            {
                demarmor.remove(demarmcount);
            }
            demarmcount = new JMenuItem(" Count: " + countdem + " ");
            demcounted = true;
            demarmor.add(demarmcount);

            if (hevcounted == true)
            {
                hevarmor.remove(hevarmcount);
            }
            hevarmcount = new JMenuItem(" Count: " + counthev + " ");
            hevcounted = true;
            hevarmor.add(hevarmcount);
        }

        if (e.getSource() == store)
        {
            clearTextArea();
            textArea.append("The health potion to restore your health costs 3 times your level.\n");
            textArea.append("The max health potion gives plus 100 max health for 7500 crystals.\n");
            textArea.append("The super max health potion gives plus 10000 health for 100000 crystals.\n");
            textArea.append("Dagger - cost 5000 crystals, give 100 attack.\n");
            textArea.append("Blade - cost 10000 crystals, give 500 attack.\n");
            textArea.append("Hammer - cost 15000 crystals, give 1000 attack.\n");
            textArea.append("Sword - cost 20000 crystals, give 5000 attack.\n");
            textArea.append("Heavenly Sword - cost 100000 crystals, give 20000 attack.\n");
            textArea.append("Cuirass - cost = 5000 crystals, gives 100 defense\n");
            textArea.append("Chain Mail - cost = 10000 crystals, gives 500 defense\n");
            textArea.append("Plate Mail - cost = 15000 crystals, gives 1000 defense\n");
            textArea.append("Demon Armor - cost = 20000 crystals, gives 5000 defense\n");
            textArea.append("Heavenly Armor - cost = 100000 crystals, gives 20000 defense\n");
        }
    }

    private byte[] intToByteArray(int num)
    {
        byte[] temp = new byte[4];
        temp[3] = (byte)(num & 0xFF);
        temp[2] = (byte)((num >> 8) & 0xFF);
        temp[1] = (byte)((num >> 16) & 0xFF);
        temp[0] = (byte)((num >> 24) & 0xFF);
        return temp;
    }

    private int byteArrayToInt(byte[] b)
    {
        return  b[3] & 0xFF |
               (b[2] & 0xFF) << 8 |
               (b[1] & 0xFF) << 16 |
               (b[0] & 0xFF) << 24;
    }
    
    private void battleDecision(String alienName)
    {
        alienStats.setAlienType(alienName); 
        alienStats.getAtype();
        battle();
    }
    
    private void equipWeapon(String weaponName, int addedStrength)
    {
        clearTextArea();
        equippedWeapon = weaponList.get(weaponList.indexOf(weaponName));

        textArea.append("You've equipped " + equippedWeapon + ".\n");
        textArea.append("Your last weapon was " + previousWeapon + ".\n");

        if(!previousWeapon.equals(weaponName))
        {
            weaponSwapped = true;
        }
        if(weaponSwapped == true)
        {
            playerStats.setStr(playerStats.getIStr() + addedStrength);
        }

        previousWeapon = equippedWeapon;
        weaponSwapped = false;
        updateStatsDisplay();
    }
    
    private void sellWeapon(String weaponName, int refundedCrystals)
    {
        clearTextArea();
        if (equippedWeapon.equals(weaponName))
        {
            textArea.append("Cannot sell. Weapon is equipped.\n");
        }
        else
        {
            weaponList.remove(weaponName);
            alienStats.setCrystals(alienStats.getCrystals() + refundedCrystals);
            playerStats.setInv(playerStats.getInv()+1);
            textArea.append("You have sold a(n) " + weaponName + ".\n");
        }
        updateStatsDisplay();
    }
    
    private void buyWeapon(String weaponName, int neededCrystals)
    {
        clearTextArea();
        if(alienStats.getCrystals() < neededCrystals)
            textArea.append("You do not have enough money to buy this weapon.\n");
        else
        {
            alienStats.setCrystals(alienStats.getCrystals()-neededCrystals);
            playerStats.setInv(playerStats.getInv()-1);
            weaponList.add(weaponName);
            textArea.append("You have purchased " + weaponName + ".\n");
        }
        updateStatsDisplay();
    }
    
    private void equipArmor(String armorName, int addedDefense)
    {
        clearTextArea();
        equippedArmor = armorList.get(armorList.indexOf(armorName));

        textArea.append("You have selected the armor, " + equippedArmor + ".\n");
        textArea.append("Your previous armor was " + previousArmor + ".\n");

        if(!previousArmor.equals(armorName))
        {
            armorSwapped = true;
        }
        if(armorSwapped == true)
        {
            playerStats.setDef(playerStats.getIDef() + addedDefense);
        }

        previousArmor = equippedArmor;
        armorSwapped = false;
        updateStatsDisplay();
    }
    
    private void sellArmor(String armorName, int refundedCrystals)
    {
        clearTextArea();
        if (equippedArmor.equals(armorName))
        {
            textArea.append("Cannot sell. Armor is equipped.\n");
        }
        else
        {
            armorList.remove(armorName);
            alienStats.setCrystals(alienStats.getCrystals() + refundedCrystals);
            playerStats.setInv(playerStats.getInv()+1);
            textArea.append("You have sold a(n) " + armorName + ".\n");
        }
        updateStatsDisplay();
    }
    
    private void buyArmor(String armorName, int neededCrystals, int neededEdnce)
    {
        clearTextArea();
        if(alienStats.getCrystals() < neededCrystals || playerStats.getEdnce() < neededEdnce)
        {
            if (alienStats.getCrystals()<neededCrystals)
                textArea.append("You do not have enough money to buy this armor.\n");
            if (playerStats.getEdnce() < neededEdnce)
                textArea.append("You need " + neededEdnce + " endurance to use this armor.\n");
        }
        else
        {
            alienStats.setCrystals(alienStats.getCrystals()-neededCrystals);
            playerStats.setInv(playerStats.getInv()-1);
            armorList.add(armorName);
            textArea.append("You have purchased " + armorName + ".\n");
        }
        updateStatsDisplay();
    }

    @Override
    public void actionPerformed(ActionEvent evt)
    { 
        //in-game file menu listeners
        if (evt.getSource() == save)
        {
            clearTextArea();
            try
            {
                FileOutputStream fstream = new FileOutputStream("savefile.zed");
                BufferedOutputStream out = new BufferedOutputStream(fstream);
                byte[] b = intToByteArray(weaponList.size());
                out.write(b);
                int x = weaponList.size();
                for (int i = 0; i < x; i++)
                {
                    int temp = getWeaponNumber(weaponList.get(i));
                    byte[] weps = intToByteArray(temp);
                    out.write(weps);
                }
                int r = armorList.size();
                byte[] c = intToByteArray(r);
                out.write(c);
                for (int i = 0; i < r; i++)
                {
                    int temp = getArmorNumber(armorList.get(i));
                    byte[] defs = intToByteArray(temp);
                    out.write(defs);
                    //String str = new String(armorList.get(i).getBytes());
                    //out.write(str + "\n");
                }
                byte[] lvl = intToByteArray(playerStats.getLvl());
                byte[] hp = intToByteArray(playerStats.getHp());
                byte[] ihp = intToByteArray(playerStats.getIHp());
                byte[] str = intToByteArray(playerStats.getStr());
                byte[] istr = intToByteArray(playerStats.getIStr());
                byte[] agil = intToByteArray(playerStats.getAgil());
                byte[] ednce = intToByteArray(playerStats.getEdnce());
                byte[] def = intToByteArray(playerStats.getDef());
                byte[] idef = intToByteArray(playerStats.getIDef());
                byte[] prob = intToByteArray(playerStats.getProb());
                byte[] crystals = intToByteArray(alienStats.getCrystals());
                byte[] exp = intToByteArray(alienStats.getExp());
                byte[] iinv = intToByteArray(playerStats.getIinv());
                byte[] inv = intToByteArray(playerStats.getInv());
                byte[] expneed = intToByteArray(expNeeded);
                out.write(lvl);
                out.write(hp);
                out.write(ihp);
                out.write(str);
                out.write(istr);
                out.write(agil);
                out.write(ednce);
                out.write(def);
                out.write(idef);
                out.write(prob);
                out.write(crystals);
                out.write(exp);
                out.write(iinv);
                out.write(inv);
                out.write(expneed);
                out.write(intToByteArray(getWeaponNumber(equippedWeapon)));
                out.write(intToByteArray(getArmorNumber(equippedArmor)));

                out.close();
                fstream.close();
                textArea.append("Game save was successful.");
            }
            catch(Exception e)
            {
                System.err.println("Error: " + e.getMessage());
            }
        }
        else if (evt.getSource() == ingameload)
        {
            // code goes here to read in the file that was saved previously
            try
            {
                clearTextArea();
                FileInputStream inputs = new FileInputStream("savefile.zed");
                BufferedInputStream buffedInputs = new BufferedInputStream(inputs);

                //clears out inventory so no items are repeated upon loading a different character file
                weaponList.clear();
                armorList.clear();

                //this retrieves the number of items that were in the weapons part of inventory
                byte[] b = new byte[4];
                buffedInputs.read(b);
                int x = byteArrayToInt(b);

                //this adds the weapons back into your inventory
                for (int i = 0; i < x; i++)
                {
                    //add in your weapons here
                    byte[] c = new byte[4];
                    buffedInputs.read(c);
                    int temp = byteArrayToInt(c);
                    weaponList.add(store_weapons.get(temp));
                }

                //retrieves the number of armor items you had
                buffedInputs.read(b);
                x = byteArrayToInt(b);

                //then fetches them and puts them into armorList here
                for (int i = 0; i < x; i++)
                {
                    //adds in armor here
                    byte[] c = new byte[4];
                    buffedInputs.read(c);
                    int temp = byteArrayToInt(c);
                    armorList.add(store_armor.get(temp));
                }

                //gather all other numerical user stats (15 total of them)
                for (int i = 0; i < 15; i++)
                {
                    buffedInputs.read(b);
                    x = byteArrayToInt(b);
                    switch(i)
                    {
                        case 0:
                            playerStats.setLvl(x);
                            break;
                        case 1:
                            playerStats.setHp(x);
                            break;
                        case 2:
                            playerStats.setIHp(x);
                            break;
                        case 3:
                            playerStats.setStr(x);
                            break;
                        case 4:
                            playerStats.setIStr(x);
                            break;
                        case 5:
                            playerStats.setAgil(x);
                            break;
                        case 6:
                            playerStats.setEdnce(x);
                            break;
                        case 7:
                            playerStats.setDef(x);
                            break;
                        case 8:
                            playerStats.setIDef(x);
                            break;
                        case 9:
                            playerStats.setProb(x);
                            break;
                        case 10:
                            alienStats.setCrystals(x);
                            break;
                        case 11:
                            alienStats.setExp(x);
                            break;
                        case 12:
                            playerStats.setIinv(x);
                            break;
                        case 13:
                            playerStats.setInv(x);
                            break;
                        case 14:
                            expNeeded = x;
                            break;
                        default: 
                            textArea.append("There was a strange error that caused the loop to go above its limits! :3");
                            break;
                    }
                }

                //these two sequences get the current equipped weapon and armor 
                buffedInputs.read(b);
                x = byteArrayToInt(b);
                equippedWeapon = store_weapons.get(x);

                buffedInputs.read(b);
                x = byteArrayToInt(b);
                equippedArmor = store_armor.get(x);

                previousWeapon = equippedWeapon;
                previousArmor = equippedArmor;

                //closes the input streams, like a good girl. 
                buffedInputs.close();
                inputs.close();
                updateStatsDisplay();
            }
            catch(Exception e)
            {
                System.err.println("Error: " + e.getMessage());
            }
        }
        else if (evt.getSource() == gamequit)
        {
            gameMenu.dispose();
            AlienControl next = new AlienControl();
            next.generateMainMenuGUI();
        }

        //in-game menu battle action listeners
        if (evt.getSource() == zorg)
        {
            battleDecision("zorg");
        }
        else if (evt.getSource() == zarvox)
        {
            battleDecision("zarvox");
        }
        else if (evt.getSource() == zirvex)
        {
            battleDecision("zirvex");
        }
        else if (evt.getSource() == zarkonaut)
        {
            battleDecision("zarkonaut");
        }
        else if (evt.getSource() == zekorov)
        {
            battleDecision("zekorov");
        }

        //weapons menu in-game listeners
        if (evt.getSource() == unequipWeapon)
        {
            clearTextArea();
            equippedWeapon = weaponList.get(0);
            textArea.append("You have unequipped your " + previousWeapon + ".\n");
            previousWeapon = equippedWeapon;
            playerStats.setStr(playerStats.getIStr());
            updateStatsDisplay();
        }
        else if (evt.getSource() == equipdagger)
        {
            equipWeapon("Dagger", 100);
        }
        else if (evt.getSource() == selldagger)
        {
            sellWeapon("Dagger", 2500);
        }
        else if (evt.getSource() == equipblade)
        {
            equipWeapon("Blade", 500);
        }
        else if (evt.getSource() == sellblade)
        {
            sellWeapon("Blade", 5000);
        }
        else if (evt.getSource() == equiphammer)
        {
            equipWeapon("Hammer", 1000);
        }
        else if (evt.getSource() == sellhammer)
        {
            sellWeapon("Hammer", 7500);
        }
        else if (evt.getSource() == equipsword)
        {
            equipWeapon("Sword", 5000);
        }
        else if (evt.getSource() == sellsword)
        {
            sellWeapon("Sword", 10000);
        }
        else if (evt.getSource() == equiphevSword)
        {
            equipWeapon("Heavenly Sword", 20000);
        }
        else if (evt.getSource() == sellhevSword)
        {
            sellWeapon("Heavenly Sword", 50000);
        }

        //armor in-game listeners
        if (evt.getSource() == unequipArmor)
        {
            clearTextArea();
            equippedArmor = armorList.get(0);
            textArea.append("You have unequipped your " + previousArmor + ".\n");
            previousArmor = equippedArmor;
            playerStats.setDef(playerStats.getIDef());
            updateStatsDisplay();
        }
        else if (evt.getSource() == equipcuirass)
        {
            equipArmor("Cuirass", 100);
        }
        else if (evt.getSource() == sellcuirass)
        {
            sellArmor("Cuirass", 2500);
        }
        else if (evt.getSource() == equipchamail)
        {
            equipArmor("Chain Mail", 500);
        }
        else if (evt.getSource() == sellchamail)
        {
            sellArmor("Chain Mail", 5000);
        }
        else if (evt.getSource() == equipplamail)
        {
            equipArmor("Plate Mail", 1000);
        }
        else if (evt.getSource() == sellplamail)
        {
            sellArmor("Plate Mail", 7500);
        }
        else if (evt.getSource() == equipdemarmor)
        {
            equipArmor("Demon Armor", 5000);
        }
        else if (evt.getSource() == selldemarmor)
        {
            sellArmor("Demon Armor", 10000);
        }
        else if (evt.getSource() == equiphevarmor)
        {
            equipArmor("Heavenly Armor", 20000);
        }
        else if (evt.getSource() == sellhevarmor)
        {
            sellArmor("Heavenly Armor", 50000);
        }

        //store in-game listeners
        //the health potion part
        if (evt.getSource() == healthpot)
        {
            clearTextArea();
            if(alienStats.getCrystals() < (playerStats.getLvl()*playerStats.getLvl()*playerStats.getLvl()))
            {
                textArea.append("You do not have enough crystals to buy a health vile.\n");
            }
            else
            {
                alienStats.setCrystals(alienStats.getCrystals() - (playerStats.getLvl()*playerStats.getLvl()*playerStats.getLvl()));
                playerStats.setHp(playerStats.getIHp());

                textArea.append("Your health has been fully restored.\n");
            }
            updateStatsDisplay();
        }
        else if (evt.getSource() == maxhealth)
        {
            clearTextArea();
            if(alienStats.getCrystals() < 7500)
            {
                textArea.append("You do not have enough crystals to buy the max health vile.\n");
            }
            else
            {
                alienStats.setCrystals(alienStats.getCrystals() - 7500);
                playerStats.setIHp(playerStats.getIHp() + 100);
                playerStats.setHp(playerStats.getIHp());

                textArea.append("You now have " + playerStats.getHp() + " health.\n");
            }
            updateStatsDisplay();
        }
        else if (evt.getSource() == supermaxhealth)
        {
            clearTextArea();
            if(alienStats.getCrystals() < 100000)
            {
                textArea.append("You do not have enough crystals to buy a super max health vile.\n");
            }
            else
            {
                alienStats.setCrystals(alienStats.getCrystals() - 100000);
                playerStats.setIHp(playerStats.getIHp() + 10000);
                playerStats.setHp(playerStats.getIHp());

                textArea.append("You now have " + playerStats.getHp() + " health.\n");
            }
            updateStatsDisplay();
        }
        //the item part of the store
        else if (evt.getSource() == buydagger)
        {
            buyWeapon("Dagger", 5000);
        }
        else if (evt.getSource() == buyblade)
        {
            buyWeapon("Blade", 10000);
        }
        else if (evt.getSource() == buyhammer)
        {
            buyWeapon("Hammer", 15000);
        }
        else if (evt.getSource() == buysword)
        {
            buyWeapon("Sword", 20000);
        }
        else if (evt.getSource() == buyhevsword)
        {
            buyWeapon("Heavenly Sword", 100000);
        }
        else if (evt.getSource() == buycuirass)
        {
            buyArmor("Cuirass", 5000, 170);
        }
        else if (evt.getSource() == buychamail)
        {
            buyArmor("Chain Mail", 10000, 500);
        }
        else if (evt.getSource() == buyplamail)
        {
            buyArmor("Plate Mail", 15000, 1500);
        }
        else if (evt.getSource() == buydemarmor)
        {
            buyArmor("Demon Armor", 20000, 2000);
        }
        else if (evt.getSource() == buyhevarmor)
        {
            buyArmor("Heavenly Armor", 100000, 10000);
        }

        //main/file menu action listeners
        if (evt.getSource() == start)
        {
            mainMenu.dispose();
            AlienControl next = new AlienControl();
            next.generateGameGUI();
        }
        //load here
        //this code is exactly the same as the in-game load sequence
        //There is only one difference, and that is to actually create 
        //a new game sequence out of this load and dispose of the main menu
        //frame
        else if (evt.getSource() == load)
        {   
            // code goes here to read in the file that was saved previously
            try
            {
                FileInputStream inputs = new FileInputStream("savefile.zed");
                BufferedInputStream buffedInputs = new BufferedInputStream(inputs);

                //creates the new game, then loads in the user stats from 
                //saved file
                mainMenu.dispose();
                AlienControl next = new AlienControl();
                generateGameGUI();

                //clears out inventory so no items are repeated upon loading a different character file
                weaponList.clear();
                armorList.clear();
                
                //this retrieves the number of items that were in the weapons part of inventory
                byte[] b = new byte[4];
                buffedInputs.read(b);
                int x = byteArrayToInt(b);

                //this adds the weapons back into your inventory
                for (int i = 0; i < x; i++)
                {
                    //add in your weapons here
                    byte[] c = new byte[4];
                    buffedInputs.read(c);
                    int temp = byteArrayToInt(c);
                    weaponList.add(store_weapons.get(temp));
                }

                //retrieves the number of armor items you had
                buffedInputs.read(b);
                x = byteArrayToInt(b);

                //then fetches them and puts them into armorList here
                for (int i = 0; i < x; i++)
                {
                    //adds in armor here
                    byte[] c = new byte[4];
                    buffedInputs.read(c);
                    int temp = byteArrayToInt(c);
                    armorList.add(store_armor.get(temp));
                }

                //gather all other numerical user stats (15 total of them)
                for (int i = 0; i < 15; i++)
                {
                    buffedInputs.read(b);
                    x = byteArrayToInt(b);
                    switch(i)
                    {
                        case 0:
                            playerStats.setLvl(x);
                            break;
                        case 1:
                            playerStats.setHp(x);
                            break;
                        case 2:
                            playerStats.setIHp(x);
                            break;
                        case 3:
                            playerStats.setStr(x);
                            break;
                        case 4:
                            playerStats.setIStr(x);
                            break;
                        case 5:
                            playerStats.setAgil(x);
                            break;
                        case 6:
                            playerStats.setEdnce(x);
                            break;
                        case 7:
                            playerStats.setDef(x);
                            break;
                        case 8:
                            playerStats.setIDef(x);
                            break;
                        case 9:
                            playerStats.setProb(x);
                            break;
                        case 10:
                            alienStats.setCrystals(x);
                            break;
                        case 11:
                            alienStats.setExp(x);
                            break;
                        case 12:
                            playerStats.setIinv(x);
                            break;
                        case 13:
                            playerStats.setInv(x);
                            break;
                        case 14:
                            expNeeded = x;
                            break;
                        default: 
                            textArea.append("There was a strange error that caused the loop to go above its limits! :3");
                            break;
                    }
                }

                //these two sequences get the current equipped weapon and armor 
                buffedInputs.read(b);
                x = byteArrayToInt(b);
                equippedWeapon = store_weapons.get(x);

                buffedInputs.read(b);
                x = byteArrayToInt(b);
                equippedArmor = store_armor.get(x);

                previousWeapon = equippedWeapon;
                previousArmor = equippedArmor;

                //closes the input streams, like a good girl. 
                buffedInputs.close();
                inputs.close();
                textArea.append("Game successfully loaded.\n");
                updateStatsDisplay();
            }
            catch(Exception e)
            {
                System.err.println("Error: " + e.getMessage());
            }
        }
        else if (evt.getSource() == exiter)
        {
            System.exit(0);
        }
    }

    private void generateGameGUI()
    {
        //in game file menu for quit to menu, save and load.
        //the quit to main menu section
        gamefilemenu.add(save);
        gamefilemenu.add(ingameload);
        gamefilemenu.add(gamequit);
        gameMenuBar.add(gamefilemenu);
        gamequit.addActionListener(this);
        save.addActionListener(this);
        ingameload.addActionListener(this);

        //battle stuff
        battle.add(zorg);
        zorg.addActionListener(this);
        battle.add(zarvox);
        zarvox.addActionListener(this);
        battle.add(zirvex);
        zirvex.addActionListener(this);
        battle.add(zarkonaut);
        zarkonaut.addActionListener(this);
        battle.add(zekorov);
        zekorov.addActionListener(this);
        battle.add(zandrex);
        zandrex.addActionListener(this);
        gameMenuBar.add(battle);

        //weapons/armor and user stats stuff
        weapons.addMenuListener(this);
        gameMenuBar.add(weapons);
        armor.addMenuListener(this);
        gameMenuBar.add(armor);
        dagger.add(equipdagger);
        dagger.add(selldagger);
        blade.add(equipblade);
        blade.add(sellblade);
        hammer.add(equiphammer);
        hammer.add(sellhammer);
        sword.add(equipsword);
        sword.add(sellsword);
        hevSword.add(equiphevSword);
        hevSword.add(sellhevSword);
        unequipWeapon.addActionListener(this);
        unequipArmor.addActionListener(this);
        equipdagger.addActionListener(this);
        selldagger.addActionListener(this);
        equipblade.addActionListener(this);
        sellblade.addActionListener(this);
        equiphammer.addActionListener(this);
        sellhammer.addActionListener(this);
        equipsword.addActionListener(this);
        sellsword.addActionListener(this);
        equiphevSword.addActionListener(this);
        sellhevSword.addActionListener(this);
        cuirass.add(equipcuirass);
        cuirass.add(sellcuirass);
        chamail.add(equipchamail);
        chamail.add(sellchamail);
        plamail.add(equipplamail);
        plamail.add(sellplamail);
        demarmor.add(equipdemarmor);
        demarmor.add(selldemarmor);
        hevarmor.add(equiphevarmor);
        hevarmor.add(sellhevarmor); 
        equipcuirass.addActionListener(this);
        sellcuirass.addActionListener(this);
        equipchamail.addActionListener(this);
        sellchamail.addActionListener(this);
        equipplamail.addActionListener(this);
        sellplamail.addActionListener(this);
        equipdemarmor.addActionListener(this);
        selldemarmor.addActionListener(this);
        equiphevarmor.addActionListener(this);
        sellhevarmor.addActionListener(this);

        //store stuff
        store.addMenuListener(this);
        health.add(healthpot);
        health.add(maxhealth);
        health.add(supermaxhealth);
        store.add(health);
        store.add(buydagger);
        store.add(buyblade);
        store.add(buyhammer);
        store.add(buysword);
        store.add(buyhevsword);
        store.add(buycuirass);
        store.add(buychamail);
        store.add(buyplamail);
        store.add(buydemarmor);
        store.add(buyhevarmor);
        gameMenuBar.add(store);
        healthpot.addActionListener(this);
        maxhealth.addActionListener(this);
        supermaxhealth.addActionListener(this);
        buydagger.addActionListener(this);
        buyblade.addActionListener(this);
        buyhammer.addActionListener(this);
        buysword.addActionListener(this);
        buyhevsword.addActionListener(this);
        buycuirass.addActionListener(this);
        buychamail.addActionListener(this);
        buyplamail.addActionListener(this);
        buydemarmor.addActionListener(this);
        buyhevarmor.addActionListener(this);

        textArea = new JTextArea(25,30);
        textArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(textArea);
        scrollPane.setVisible(true);

        statsDisplay = new JTextArea(25,30);
        statsDisplay.setEditable(false);
        JScrollPane statsPanel = new JScrollPane(statsDisplay);
        statsPanel.setVisible(true);

        gameMenu = new JFrame("In-Game Menu");
        gameMenu.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        gameMenu.setJMenuBar(gameMenuBar);

        gameMenu.setSize(700,500);
        gameMenu.setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.fill = GridBagConstraints.HORIZONTAL;
        gameMenu.add(scrollPane, c);
        gameMenu.add(statsPanel, c);
        gameMenu.setVisible(true);

        updateStatsDisplay();
    }

    protected void generateMainMenuGUI()
    {
        mainfilemenu.add(start);
        start.addActionListener(this);
        mainfilemenu.add(load);
        load.addActionListener(this);
        mainfilemenu.add(exiter);
        exiter.addActionListener(this);
        mainMenuBar.add(mainfilemenu);

        mainMenu = new JFrame("Main Menu");
        mainMenu.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        mainMenu.setJMenuBar(mainMenuBar);

        mainMenu.setSize(300, 100);
        mainMenu.setVisible(true);
    }

    /*
                    if (evt.getSource() == help)
                    {
                        textArea.append(faq.helpOut());
                    }
    */
}