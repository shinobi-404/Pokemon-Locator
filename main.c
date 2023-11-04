

// liabaries needed
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leak_detector_c.h"

// all nessary structs
typedef struct monster{ 

 char *name; 
 char *element; 
 int population; 
 
} monster;

typedef struct region{ 

 char *name; 
 int monster_cnt; 
 int total_population; 
 monster **monsters; 
 
} region; 

typedef struct itinerary{ 

  int region_cnt; 
  region **regions; 
  int captures; 
 
} itinerary; 

typedef struct trainer{ 

 char *name; 
 itinerary *visits; 

} trainer; 


// all nessary functions calls 
monster* makeMonster(char *name, char *element, int population);
monster** readMonsters(int *monsterCount);
region* makeRegions(char *name,int monsterCount , monster **monsterList,int mcount);
region** readRegions(int *countRegions, monster** monsterList, int monsterCount);
trainer* loadTrainers(int *trainerCount, region** regionList, int countRegions);
void processInputs(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount);
void releaseMemory(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount);


int main(void) {
  
  atexit(report_mem_leak);//scans for memory leak 
  int mcount, rcount, tcount;// initialzies variables 

  //scans variables and calls functions, linking functions together 
  scanf("%d",&mcount);
  monster** mont = readMonsters(&mcount);
  scanf("%d",&rcount);
  region** reg = readRegions(&rcount, mont, mcount);
  scanf("%d",&tcount);
  trainer* train =loadTrainers(&tcount, reg, rcount);
  processInputs(mont, mcount, reg, rcount, train, tcount);
  releaseMemory(mont, mcount, reg, rcount, train, tcount);
    

  return 0;
}


monster* makeMonster(char *name, char *element, int population){
  //This function returns a dynamically allocated monster filled with the provided parameters 
  monster *m = (monster*)malloc(sizeof(monster));

  m->name = (char*)malloc((strlen(name)+1)*sizeof(char));
  strcpy(m->name,name);
  
  m->element = (char*)malloc((strlen(element)+1)*sizeof(char));
  strcpy(m->element,element);

  m->population = population;
  
  return m;
  
  }
 

monster** readMonsters(int *monsterCount){
  // This function returns an array of monster pointers 
  // where each monster pointer points to the dynamically allocated monsters with fill-up information from the 
  // provided inputs. It can use the makeMonster function in this process. **This function also updates the passed <- come back to this
  // variable reference pointed by monsterCount so that the caller to this function knows how many monsters are 
  // returned from the function. 

  // initializes variables 
  char name[51], element[51];
  int population;

  //int LengthofMonCoun = sizeof(*monsterCount)/sizeof(monsterCount[0]);

  // creates an array of monster pointers 
  monster **m = (monster**)malloc((*monsterCount)*sizeof(monster*));

  // scans data and calls make monsters and stores it in the monster pointer array 
  for(int i = 0; i < *monsterCount;i++){
    scanf("%s %s %d", name, element, &population);
    m[i] = makeMonster(name, element, population);
    
    // scanf("%d", monsterCount); // updates monster count 
 
  }
return m;
  
}



region* makeRegions(char *name,int monsterCount , monster **monsterList,int mcount){

  // creates array for a region
  region *makereg = (region*)malloc(sizeof(region));

  //creates name of region and stores it 
  makereg->name = (char*)malloc((strlen(name)+1)*sizeof(char));
  strcpy(makereg->name,name);

  //creates array of monster pointers and stores the amount of monsters
  makereg->monsters = (monster**)malloc(mcount*sizeof(monster*));
  makereg->monster_cnt = mcount;

  // initializes variables
  int total_population = 0;
  int stringcmp = 0;
  char mname[51];

  // scans and stores monster name trough the loop, 
  for(int i = 0; i < mcount; i++){

    scanf("%s",mname);
    
    for(int j = 0; j < monsterCount; j++){
      stringcmp = strcmp(monsterList[j]->name, mname);// compares monster for name and for the one in the region 
      if (stringcmp == 0){
          
          total_population += monsterList[j]->population;//updates total popualtion 
          makereg->monsters[i] = monsterList[j];// stores monsters from mosnters list 

      }
    }
  }
   makereg->total_population = total_population;

  return makereg;
}



region** readRegions(int *countRegions, monster** monsterList, int monsterCount){
  // This function returns an array of region pointers where each region pointer points to a dynamically allocated 
  // region, filled up with the information from the inputs, and the region’s monsters member points to an 
  // appropriate list of monsters from the monsterList passed to this function. This function also updates the passed 
  // variable reference pointed by countRegions (to inform the caller about this count). As the loadMonsters(readMonster) 
  // function has created all the monsters using dynamic memory allocation, you are getting this feature to use/re-
  // use those monsters in this process. 
  
  //initialize variables 
  char rname[51];
  int mcount;

  //create ana rray for region pointers 
  region **r = (region**)malloc(*countRegions*sizeof(region*));

  //scans and calls the makeRegions function 
  for(int i = 0; i < *countRegions;i++){
    scanf("%s %d",rname, &mcount);
    
    r[i]=makeRegions(rname, monsterCount, monsterList, mcount );
   
  }

  return r;
    
}
 

trainer* loadTrainers(int *trainerCount, region** regionList, int countRegions){
  
  // This function returns a dynamically allocated array of trainers, filled up with the information from the inputs, 
  // and the trainer’s visits field points to a dynamically allocated itinerary which is filled based on the passed 
  // regionList. This function also updates the passed variable reference pointed by trainerCount. As the 
  // loadRegions function has crated all the regions using dynamic memory allocation, you are getting this feature 
  // to use/re-use those regions in this process.  

  // initializes variables
  char tname[51], regionName[51];
  int nRegions = 0, capt = 0, stringcmp;

  //creates array for trainers that point to regions and monsters 
  trainer *mtrainer = (trainer*)malloc(*trainerCount*sizeof(trainer));

  // scans and stores trainer name 
  for(int i = 0; i < *trainerCount; i++){

    scanf("%s",tname);
    mtrainer[i].name = (char*)malloc((strlen(tname)+1)*sizeof(char));
    strcpy(mtrainer[i].name, tname);

    //scans capture creates arrauy of vists and than stores the amount of captures 
    scanf("%d", &capt);
    mtrainer[i].visits = (itinerary*)malloc(sizeof(itinerary));
    mtrainer[i].visits->captures = capt;  

    //scans number of regions and stores total amount of them 
    scanf("%d",&nRegions);
    mtrainer[i].visits->regions = malloc(nRegions*sizeof(region));
    mtrainer[i].visits->region_cnt = nRegions;
    
  // scans and stores and compares region with trainers and their destinations 
    for(int j = 0; j < nRegions; j++){

      scanf("%s",regionName);

      for(int k = 0; k < countRegions;k++){
        
        stringcmp = strcmp(regionName, regionList[k]->name);
        
        if(stringcmp == 0){
          
          mtrainer[i].visits->regions[j] = regionList[k];
        
        }
      }
    }
  }

  return mtrainer;
 
}

// processes and calcualtes dyanmically allocated arrays 
void processInputs(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount ){

  // This function processes all the data and produce the output. During this process, you can create/use more functions if you want. 
  
  // initislizes variables 
  float  rates, captAmount;

  // process the inputs and than display them on the screen
  for(int i = 0; i < trainerCount;i++){
    
    printf("%s\n",trainerList[i].name);
    
      for(int j = 0; j < trainerList[i].visits->region_cnt; j++ ){
        
        printf("%s\n", trainerList[i].visits->regions[j]->name);

        // calculates theaccurate rate capture rate for each trainer and monster  in the region 
        for(int k = 0; k < trainerList[i].visits->regions[j]->monster_cnt; k++){
          // calculates capture rate and floats 
          rates = (double)trainerList[i].visits->regions[j]->monsters[k]->population / trainerList[i].visits->regions[j]->total_population;
          
          captAmount = trainerList[i].visits->captures * rates;
          
          // rounds answer 
          int truecaptAm = round(captAmount);
          
          // prints calculated rate if it is greater than 0
          if(truecaptAm > 0){
            
            printf("%d-%s\n",truecaptAm,trainerList[i].visits->regions[j]->monsters[k]->name);
          }
          
          
      }
    }  
     printf("\n");
  }
   
}

// frees memory 
void releaseMemory(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount){
  //This function takes all the dynamically allocated arrays and free-up all the memory. You can create/use more function in this process if you want. 


  //frees memory for monsters 
  for(int i = 0; i < monsterCount; i++){
    free(monsterList[i]->name);
    free(monsterList[i]->element);
    free(monsterList[i]);
  }
  free(monsterList);

  // frees memory for regions
  for(int j = 0; j < regionCount; j++){
    free(regionList[j]->name);
    free(regionList[j]->monsters);
    free(regionList[j]);
    
  }
  free(regionList);

  // frees memory for trainers
  for(int k = 0; k < trainerCount; k++){
    free(trainerList[k].name);
    free(trainerList[k].visits);
    free(trainerList[k].visits->regions);
  }
  free(trainerList);
  
}



