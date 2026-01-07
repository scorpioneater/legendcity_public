package com.msc.biff;

/* Dedicated Football Odds Engine
   Startegy: 
            1. Use p() value to find games that are expected to be lopsided and games that are a "coin toss"
            2. 

*/
public class Lombardi {

     //Command Line Input
     //java -cp com.msc.biff.Lombardi 290 3320 4906 24 0 4 355 1894 5951 12 11 223 4130 3806 10 1 10 234 1456 3567 14 5 lar sux
     private static final int N_P_FIELDS = 11;
     public static void main (String [] args) {
          
          float [] stats = new float[N_P_FIELDS];
          for(int n=0;n<N_P_FIELDS;n++){stats[n]=Float.parseFloat(args[n]);}
          System.out.println(args[args.length-1] + " - " + p(stats));
          for(int n=N_P_FIELDS;n<N_P_FIELDS*2;n++){stats[n]=Float.parseFloat(args[n]);}
          System.out.println(args[args.length] + " - " + p(stats));      
     }           

     private static float p(float [] stats){
          float s = 0;
          int ln = 0;
          float [] weights = {-0.0428
          for (float stat : stats){
              s+=weights[i]*(float)stats[i];
          }
      
          return 1/(1 + Math.pow(Math.E,-1*ln));  
     }

     private static void analyzeStandings(){
          
     }
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
