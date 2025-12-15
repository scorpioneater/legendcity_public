package com.msc.biff

public class Biff {

     private static final int N_P_FIELDS = 12;
     public static void main (Sting [] args) 
            
     }

     private static void getNFL() {
          
     }

     private float getP(float [N_P_FIELDS] weights, int [N_P_FIELDS] stats){
          float s = 0;
          int ln = 0;
          for (stats : int stat){
              s+=weights[i]*(float)stats[i];
          }
      
          return 1/(1 + Math.pow(Math.E,-1*ln))  
     }

     private static void analyzeStandings(){
          
     }

     private static void analyzeNHL() {
       
     }

     private static void analyzeNBA() {
       
     }

     private static void analyzeCFB() {
       
     }

     private static void analyzeCBB() {
       
     }

     private static void analyzeIFB() {
       
     }  


     class 
}

/*
p() calculation: 
def p(stats):
    print (stats)
    def_1st_down  = stats[0]#7
    def_pass_yds  = stats[1]#24
    def_total_yds = stats[2]#24 + 39
    def_turnovers = stats[3]#33 + 76
    home          = stats[4]#NA
    losses        = stats[5]#NA
    off_1st_downs = stats[6]#6
    off_rush_yds  = stats[7]#38
    off_total_yds = stats[8]#48
    off_turnovers = stats[9]#32 + 75
    wins          = stats[10]#NA
     
    ln = 0.0488                        \
         - 0.0428*def_1st_down   \
         + 0.00651*def_pass_yds  \
         - 0.0145*def_total_yds   \
         + 0.9124*def_turnovers  \
         + 0.5319*home           \
         - 0.0827*losses         \
         + 0.0331*off_1st_downs  \
         + 0.00794*off_rush_yds  \
         + 0.00806*off_total_yds \
         - 0.9686*off_turnovers  \
         + 0.0845*wins   

    return 
*/
