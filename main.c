#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
//
//
//
//
//            FUNCTION TESTING AT THE VERY BOTTOM
//
//
//
//
//
int totalPokeCount;

//Struct Definitions
  typedef struct Pokedex { //Pokedex structure to hold both the pokemon & player head.
    struct pokemonNode *pokemonHead;
    struct playerNode *playerHead;
  } Pokedex;

  typedef struct playerNode {
    char playerName[20]; //Name of player
    int pokeCount; //Num of captured pokemon
    struct pokemonNode *playerPoke[20];//The names of pokemon caught

    struct playerNode* next; //Holds the pointer for the next player in the list
  } playerNode;

  typedef struct pokemonNode {
    char pokemonName[20];//Name of pokemon
    char pokemonType[20];//What type      
    char pokemonAbility[20];//Best ability it has

    struct pokemonNode* next; //Holds the pointer for the next pokemon in the list
  } pokemonNode;

//Functions List

  //Pokemon functions

    //Create new pokemon
    pokemonNode* newPokemonNode(char pokemonName[20], char pokemonType[20], char pokemonAbility[20]);

    //Adding new pokemon to the list
    void addPokemonToList(Pokedex *pokedex, char pokemonName[20], char pokemonType[20], char pokemonAbility[20]);

    //Find if a pokemon exists
    struct pokemonNode *findPokemon(Pokedex pokedex, char userSearch[20]);

  //Player functions

    //Create new player
    struct playerNode *newPlayerNode(char playerName[20]);

    //Add new player to the list
    void addPlayerToList(Pokedex *pokedex, char playerName[20]);

    //Find if player exists
    struct playerNode *findPlayer(Pokedex pokedex, char userSearch[20]);

    //Add pokemon to player
    void addPokemonToPlayer(Pokedex pokedex, char playerName[20], char pokemonName[20]);

  //Pokedex functions

    //List players
    void listPlayers(Pokedex pokedex);

    //List pokemon
    void listPokemon(Pokedex pokedex);

    //Display player details
    void displayPlayerDetails(Pokedex pokedex, char playerName[20]);

    //Displayer pokemon details
    void displayPokemonDetails(struct Pokedex pokedex, char pokemonName[20]);








//Functions Methods
  //Pokemon function methods
    
    //Creating a new pokemon
      struct pokemonNode *newPokemonNode(char pokemonName[20], char pokemonType[20], char pokemonAbility[20]) {
        struct pokemonNode *newNode = NULL; //Creating a temp node before adding to the list with another function
        newNode = malloc(sizeof(struct pokemonNode)); //Allocating memory for the said node
        if (newNode != NULL) { 
          strcpy(newNode -> pokemonName, pokemonName);
          strcpy(newNode -> pokemonType, pokemonType);           //Adding arguments to values
          strcpy(newNode -> pokemonAbility, pokemonAbility);

          newNode -> next = NULL; // once details added move onto next node
        }
        return newNode; //bring the new pokemon details 
      }

    //Adding pokemon to the list
      void addPokemonToList(Pokedex *pokedex, char pokemonName[20], char pokemonType[20], char pokemonAbility[20]) {
      if (pokedex -> pokemonHead == NULL) { // If already null or no pokemon in array
        pokedex -> pokemonHead = newPokemonNode(pokemonName,pokemonType,pokemonAbility);
        totalPokeCount++; //add 1 when a new pokemon is added
      } else {
        struct pokemonNode *tempNode = pokedex -> pokemonHead;
        while (tempNode -> next != NULL) { //While it does not equal Null basically just skip them till you find a null to input pokemon
          if (strcasecmp(pokemonName, tempNode -> pokemonName) == 0) { return; }
          tempNode = tempNode -> next;
        }
        if (strcasecmp(pokemonName, tempNode -> pokemonName) == 0)  { return; }
        tempNode -> next = newPokemonNode(pokemonName,pokemonType,pokemonAbility);
        totalPokeCount++;
      }
      }
      
    //Find if pokemon exists
      struct pokemonNode *findPokemon(Pokedex pokedex, char userSearch[20]) {
        struct pokemonNode *tempNode = pokedex.pokemonHead; //Initializing current selection
        while (tempNode -> next != NULL) {
          if (strcasecmp(userSearch, tempNode -> pokemonName) == 0) { //If pokemon is in the list it returns pointer
            return tempNode;
          }
          tempNode = tempNode -> next; //Moves onto next node in the list
        }
        return NULL;
      }

    //pokemon details
      void displayPokemonDetails(struct Pokedex pokedex, char pokemonName[20]){
        struct pokemonNode *tempSelect = findPokemon(pokedex, pokemonName);
        if(tempSelect){
          printf("Name: %s\n",tempSelect -> pokemonName);
          printf("Type: %s\n",tempSelect -> pokemonType); //Prints Name type and ability of the pokemon used in the function
          printf("Best Ability: %s\n", tempSelect -> pokemonAbility);
          }
        }
  
  //player function methods
  
    //Create new player function
      struct playerNode *newPlayerNode(char playerName[20]) {
        struct playerNode *newNode = NULL; //Creating a temp node before adding to the list with another function
        newNode = malloc(sizeof(struct playerNode)); //Allocating memory for the said node
        if (newNode != NULL) { 
          strcpy(newNode -> playerName, playerName); //setting variable for new node

          newNode -> next = NULL;// selects next node
        }
        return newNode; //returns pointer for the next node
      }
    
    //Adding player to list
      void addPlayerToList(Pokedex *pokedex, char playerName[20]) {
      if (pokedex -> playerHead == NULL) { //Checks if player list is empty
        pokedex -> playerHead = newPlayerNode(playerName);//Creates the inital node for use 
      } else {
        struct playerNode *tempNode = pokedex -> playerHead;
        while (tempNode -> next != NULL) { //while each node is not null or already taken with a name move onto the next one
          if (strcasecmp(playerName, tempNode -> playerName) == 0) { return; }
          tempNode = tempNode -> next;
        }
        if (strcasecmp(playerName, tempNode -> playerName) == 0)  { return; }
        tempNode -> next = newPlayerNode(playerName);
      }
      }
    
    //Find if player exists
      struct playerNode *findPlayer(Pokedex pokedex, char userSearch[20]) {
        struct playerNode *tempNode = pokedex.playerHead; //Initializing current selection
        while (tempNode -> next != NULL) {
          if (strcasecmp(userSearch, tempNode -> playerName) == 0) { //If player is found return it
            return tempNode;
          }
          tempNode = tempNode -> next; //pointer next node
        }
        return NULL; //if not found return NULL
      }

    //Adding pokemon to player
      void addPokemonToPlayer(struct Pokedex pokedex, char playerName[20], char pokemonName[20]){
        struct pokemonNode *pokemonTemp = findPokemon(pokedex, pokemonName);
        struct playerNode *playerTemp = findPlayer(pokedex, playerName);
        if(playerTemp && pokemonTemp){ //And statement to check if that pokemon exists
          int tempCount = 0;
          for(int i = 0; i < 20; i++){ //checks through player poke array for said pokemon
            if(playerTemp -> playerPoke[i] != NULL){
              if(strcmp(playerTemp->playerPoke[i] -> pokemonName, pokemonName ) == 0){
              tempCount+=1;
              }
            }
            if(playerTemp -> playerPoke[i]==NULL && tempCount==0){ //Once tempcount returns null value we can then add that pokemon to the list
              playerTemp -> playerPoke[i] = pokemonTemp;
              playerTemp -> pokeCount+=1;
              return;
            }
          }
        }
      }
    
    //Player details
      void displayPlayerDetails(struct Pokedex pokedex, char playerName[20]){
        struct playerNode *tempSelect = findPlayer(pokedex, playerName); //Uses the find player function to ensure the player we're trying to display details of exists
        if(tempSelect){
          printf("Name: %s\n",tempSelect -> playerName);
          printf("No. Pokemon: %d\n",tempSelect -> pokeCount);  //simple display of each of the players details
          printf("Pokemon Owned: \n");
          for(int i = 0; i < 20; i++){
            if(tempSelect -> playerPoke[i] != NULL){ //for statment used to make sure every pokemon in the players pokeCount or the array is outputted up to 20
              printf("- %s\n", tempSelect -> playerPoke[i] -> pokemonName);
            }
          }
        }
      }

  //pokedex function methods

    //List players function
      void listPlayers(Pokedex pokedex) {
        printf("This is all the players you have details for: \n ");
        struct playerNode *tempNode = pokedex.playerHead; //Find the players head with all the player nodes
        if(tempNode == NULL) { //If player list is empty
          printf("You have no players on record.\n");
        }
        while(tempNode != NULL) { //While player list is not empty print out all their names
          printf("%s\n", tempNode -> playerName);
          tempNode = tempNode -> next;
         }        
      }

    //list pokemon function
      void listPokemon(Pokedex pokedex) {
        printf("This is all the pokemon you have details for: \n ");
        struct pokemonNode *tempNode = pokedex.pokemonHead; //Find the pokemons head with all the pokemon nodes
        if(tempNode == NULL) { //If pokemon List is empty
          printf("You have no pokemon on record.\n");
        }
        while(tempNode != NULL) { //While pokemon list is not empty print out all of their names
          printf("%s\n", tempNode -> pokemonName);
          tempNode = tempNode -> next;
         }       
      }

  //Optional Function Methods
    
    //Sort by specific ability
      void displayPokemonWithAbility(Pokedex pokedex, char pokemonAbility[20]){
        struct pokemonNode *tempSelect = pokedex.pokemonHead;
        printf("Pokemon who own :%s: are: \n",pokemonAbility);
        while(tempSelect != NULL){ //Going through each pokemon ability and finding one with the ability searched until found
          if(strcasecmp(pokemonAbility, tempSelect -> pokemonAbility) == 0){
            printf("- %s\n", tempSelect -> pokemonName); //This is finding the name of the pokemon with that ability (if any)
          }
          tempSelect = tempSelect -> next; //next node
        }
      }

    //Sort by specific type
      void displayPokemonWithType(Pokedex pokedex, char pokemonType[20]){
        struct pokemonNode *tempSelect = pokedex.pokemonHead;
        printf("Pokemon that are :%s: type are: \n",pokemonType);
        while(tempSelect != NULL){ //Going through each pokemon type and finding one with the type searched until found
          if(strcasecmp(pokemonType, tempSelect -> pokemonType) == 0){
            printf("- %s\n", tempSelect -> pokemonName); //This is finding the name of the pokemon with that type (if any)
          }
          tempSelect = tempSelect -> next; //next node
        }
      }
    //sort type list
      //                          N/A
    //sort ability list
      //                          N/A

    //sort player with pokemon
      void displayPlayersWithPokemon(Pokedex pokedex, char pokemonName[20]) {
      struct playerNode *tempSelect = pokedex.playerHead;
      printf("Players who own %s are:\n", pokemonName);
      while(tempSelect != NULL) { //Finding all counts of the pokemon and which playernodes have this pokemon in their array
        for (int i = 0; i < tempSelect->pokeCount; i++)  {
          if(strcasecmp(tempSelect -> playerPoke[i]->pokemonName, pokemonName) == 0) {
           printf("%s\n", tempSelect -> playerName); //Returning the player names of each player with the searched pokemon
          }
        }
        tempSelect = tempSelect -> next; //next node
      }
    }
    //sort player with type
    void displayPlayersWithType(Pokedex pokedex, char pokemonType[20]) {
      struct playerNode *tempSelect = pokedex.playerHead;
      printf("Players with %s type pokemon are:\n", pokemonType);
      while(tempSelect != NULL) {//Finding all counts of the pokemon and which playernodes have this type in their pokemon array
        for (int i = 0; i < tempSelect->pokeCount; i++)  {
          if(strcasecmp(tempSelect -> playerPoke[i] -> pokemonType, pokemonType) == 0) {
           printf("%s\n", tempSelect -> playerName);//Returning the player names of each player with the searched type
          }
        }
        tempSelect = tempSelect -> next;//next node
      }
    }
    //sort player with abilityw
    void displayPlayersWithAbility(Pokedex pokedex, char pokemonAbility[20]) {
      struct playerNode *tempSelect = pokedex.playerHead;
      printf("Players with %s ability pokemon are:\n", pokemonAbility);
      while(tempSelect != NULL) {//Finding all counts of the pokemon and which playernodes have this ability in their pokemon array
        for (int i = 0; i < tempSelect->pokeCount; i++)  {
          if(strcasecmp(tempSelect -> playerPoke[i] -> pokemonAbility, pokemonAbility) == 0) {
           printf("%s\n", tempSelect -> playerName);//Returning the player names of each player with the searched ability
          }
        }
        tempSelect = tempSelect -> next;//next node
      }
    }
      

//main method
  int main() {
  int userChoice = 1;   //Initializing variables
  struct Pokedex pokedex;

  
  pokedex.playerHead = NULL;      //Starting the lists
  pokedex.pokemonHead = NULL; 

  //Player and Pokemon Import
    //Pokemon import to pokedex
      addPokemonToList(&pokedex, "Snorlax", "Normal", "Body Slam");
      addPokemonToList(&pokedex, "Blissey", "Normal", "Dazzling Gleam");
      addPokemonToList(&pokedex, "Lucario", "Fighting", "Aura Sphere");
      addPokemonToList(&pokedex, "Machamp", "Fighting", "Dynamic Punch");
      addPokemonToList(&pokedex, "Rayquaza", "Flying", "Aerial Ace");
      addPokemonToList(&pokedex, "Moltres", "Flying", "Sky Attack");
      addPokemonToList(&pokedex, "Roserade", "Poison", "Sludge Bomb");
      addPokemonToList(&pokedex, "Toxic Croak", "Poison", "Poison Jab");
      addPokemonToList(&pokedex, "Goudon", "Ground", "Mud Shot");
      addPokemonToList(&pokedex, "Garchomp", "Ground", "Earthquake");
      addPokemonToList(&pokedex, "Rampardos", "Rock", "Rock Slide");
      addPokemonToList(&pokedex, "Terrakion", "Rock", "Smack Down");
      addPokemonToList(&pokedex, "Pinsir", "Bug", "X-Scissor");
      addPokemonToList(&pokedex, "Scizor", "Bug", "Bug Buzz");
      addPokemonToList(&pokedex, "Giratina", "Ghost", "Shadow Ball");
      addPokemonToList(&pokedex, "Gengar", "Ghost", "Shadow Claw");
      addPokemonToList(&pokedex, "Metagross", "Steel", "Meteor Mash");
      addPokemonToList(&pokedex, "Excadrill", "Steel", "Metal Claw");
      addPokemonToList(&pokedex, "Darmanitan", "Fire", "Fire Fang");
      addPokemonToList(&pokedex, "Entei", "Fire", "Overheat");
      addPokemonToList(&pokedex, "Kyogre", "Water", "Waterfall");
      addPokemonToList(&pokedex, "Gyarados", "Water", "Hydropump");
      addPokemonToList(&pokedex, "Alolan Exeggutor", "Grass", "Razor Leaf");
      addPokemonToList(&pokedex, "Tangrowth", "Grass", "Vine Whip");
      addPokemonToList(&pokedex, "Raikou", "Electric", "Thunderbolt");
      addPokemonToList(&pokedex, "Electivire", "Electric", "Thunder Shock");
      addPokemonToList(&pokedex, "Mewtwo", "Pyschic", "Confusion");
      addPokemonToList(&pokedex, "Latios", "Pyschic", "Zen Headbutt");
      addPokemonToList(&pokedex, "Glaceon", "Ice", "Avalanche");
      addPokemonToList(&pokedex, "Weavile", "Ice", "Ice Shard");
      addPokemonToList(&pokedex, "Palkia", "Dragon", "Outrage");
      addPokemonToList(&pokedex, "Garchomp", "Dragon", "Dragon Tail");
      addPokemonToList(&pokedex, "Darkrai", "Dark", "Dark Pulse");
      addPokemonToList(&pokedex, "Tyranitar", "Dark", "Bite");
      addPokemonToList(&pokedex, "Granbull", "Fairy", "Charm");
      addPokemonToList(&pokedex, "Togekiss", "Fairy", "Snarl");

    //Add players to list
      addPlayerToList(&pokedex, "Brock");
      addPlayerToList(&pokedex, "Ash");
      addPlayerToList(&pokedex, "Cora");
      addPlayerToList(&pokedex, "Jessie");
      addPlayerToList(&pokedex, "May");
      addPlayerToList(&pokedex, "Harvey");
      addPlayerToList(&pokedex, "Bella");
      addPlayerToList(&pokedex, "Mike");
      addPlayerToList(&pokedex, "Victoria");
      addPlayerToList(&pokedex, "Freddy");

    
    //Pokemon import to playerHead
      addPokemonToPlayer(pokedex, "Brock", "Palkia");
      addPokemonToPlayer(pokedex, "Brock", "Darkrai");
      addPokemonToPlayer(pokedex, "Brock", "Tyranitar");
      addPokemonToPlayer(pokedex, "Ash", "Garchomp");
      addPokemonToPlayer(pokedex, "Ash", "Glaceon");
      addPokemonToPlayer(pokedex, "Ash", "Weavile");
      addPokemonToPlayer(pokedex, "Ash", "Snorlax");
      addPokemonToPlayer(pokedex, "Cora", "Darmanitan");
      addPokemonToPlayer(pokedex, "Cora", "Mewtwo");
      addPokemonToPlayer(pokedex, "Cora", "Latios");
      addPokemonToPlayer(pokedex, "Jessie", "Kyogre");
      addPokemonToPlayer(pokedex, "Jessie", "Entei");
      addPokemonToPlayer(pokedex, "May", "Metagross");
      addPokemonToPlayer(pokedex, "May", "Giratina");
      addPokemonToPlayer(pokedex, "Harvey", "Gyarados");
      addPokemonToPlayer(pokedex, "Harvey", "Gengar");
      addPokemonToPlayer(pokedex, "Harvey", "Togekiss");
      addPokemonToPlayer(pokedex, "Bella", "Granbull");
      addPokemonToPlayer(pokedex, "Bella", "Moltres");
      addPokemonToPlayer(pokedex, "Bella", "Rayquaza");
      addPokemonToPlayer(pokedex, "Bella", "Raikou");
      addPokemonToPlayer(pokedex, "Mike", "Roserade");
      addPokemonToPlayer(pokedex, "Mike", "Rampardos");
      addPokemonToPlayer(pokedex, "Victoria", "Tyranitar");
      addPokemonToPlayer(pokedex, "Freddy", "Blissey");

  //FUNCTION TESTING
    //listPokemon(pokedex);
    //listPlayers(pokedex);
    //displayPlayerDetails(pokedex, "Harvey");
    //displayPokemonDetails(pokedex, "Gyarados");
    //displayPokemonWithAbility(pokedex, "Hydropump");
    //displayPokemonWithType(pokedex, "Water");
    //displayPlayersWithPokemon(pokedex, "Gyarados");
    //displayPlayersWithType(pokedex, "Water");
   // displayPlayersWithAbility(pokedex, "Hydropump");
  }
