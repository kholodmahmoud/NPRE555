/**
 * @file CP1.cc
 *
 * @brief Neutron transport simulation and flux calculation.
 *
 * This program simulates neutron transport and calculates the multiplication factor (k_eff) and neutron flux.
 *
 * @author Kholod Mahmoud
 */
#include <random>
#include <cmath>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
#include "gnuplot-iostream.h"

/**
 * @class Interact
 *
 * @brief Class responsible for neutron interactions and calculations.
 *
 * This class handles neutron interactions, including absorption, scattering, and fission, and calculates related parameters.
 */
class Interact{
    public:
    double I;        /**< Number of fission neutrons. */
    double l;        /**< Distance to the next collision in case of fission. */
    double angle_sc; /**< Scattering angle. */
    double ls;       /**< Distance to the next collision in case of scattering. */

      /**
     * @brief Calculate absorption interaction.
     *
     * @param sigma_f Fission cross section.
     * @param sigma_a Absorption cross section.
     * @param sigma_t Total cross section.
     */
    void absorption(double sigma_f, double sigma_a,double sigma_t){  
          double N_new = sigma_f/sigma_a;
          double R_n = N_new - std::floor(N_new);
          double eta = (double) rand()/RAND_MAX;
          if (R_n>eta){
          I=floor(N_new)+1;
          }
          else{
            I = floor(N_new);
          }
        l = (-log((double) rand()/RAND_MAX))/sigma_t;
    }
    /**
     * @brief Calculate scattering interaction.
     *
     * @param sigma_t Total cross section.
     */
        void scattering(double sigma_t){
        ls = -log((double) rand()/RAND_MAX)/sigma_t;
        angle_sc = 2* ((double) rand()/RAND_MAX)-1;
    }
};

/**
 * @class Sampling
 *
 * @brief Class for sampling neutron interactions.
 *
 * This class is responsible for sampling neutron interactions to determine whether scattering or absorption occurs.
 */
class sampling{
    public:
    /**
 * @brief Sample neutron interactions to determine type.
 *
 * @param sigma_a Absorption cross section.
 * @param sigma_s Scattering cross section.
 * @return true if scattering, false if absorption.
 */
    bool sample(double sigma_a,double sigma_s){
        double sigma_t = sigma_a+sigma_s;
        double ps =sigma_s/sigma_t;
        double pa =sigma_a/sigma_t;
        double m = (double) rand()/RAND_MAX;
        if (m<ps){
            return true;
        }
        else {
            return false;
        }

    }
};
/**
 * @class Initialization
 *
 * @brief Initialization class for setting neutron starting position and cross sections.
 *
 * This class determines the neutron's starting region and sets cross sections accordingly.
 */
    class initialization{
        public:
        double sigma_a;
        double sigma_s;
        double sigma_f;
        
    /**
     * @brief Determine the region based on a.
     *
     * @param a Region parameter.
     */
    void region(double a){
        if((a>0) && (a<0.5)){
            sigma_a = 0.12;
            sigma_s = 0.05;
            sigma_f = 0.15;
        }

        else if((a>0.5) && (a<1)){
            sigma_a = 0.10;
            sigma_s = 0.05;
            sigma_f = 0.12;
        }

    }
    /**
     * @brief Initialize neutron's starting position.
     *
     * @return Randomly generated starting position.
     */
        double position(){
        return (double) rand()/RAND_MAX;
    }
    
};
/**
 * @class Scoring
 *
 * @brief Class for scoring neutron flux.
 *
 * This class is responsible for scoring neutron flux by tallying it in different regions.
 */
class Scoring{
    public:
    double tally_f[10]; /**< Tally for neutron flux in different regions. */
        /**
     * @brief Calculate neutron flux and tally it in different regions.
     *
     * @param x Neutron's position.
     * @param track_length Neutron's track length.
     * @param I Number of fission neutrons.
     */
    void flux(double x,double track_length,int I) {
        if (x>0 && x <0.1){
            tally_f[0] += I*track_length/0.1;
        }
        if (x>0.1 && x <0.2){
            tally_f[1] += I*track_length/0.1;
        }
        if (x>0.2 && x <0.3){
            tally_f[2] += I*track_length/0.1;
        }
        if (x>0.3 && x <0.4){
            tally_f[3] += I*track_length/0.1;
        }
        if (x>0.4 && x <0.5){
            tally_f[4] += I*track_length/0.1;
        }
        if (x>0.5 && x <0.6){
            tally_f[5] += I*track_length/0.1;
        }
        if (x>0.6 && x <0.7){
            tally_f[6] += I*track_length/0.1;
        }
        if (x>0.7 && x <0.8){
            tally_f[7] += I*track_length/0.1;
        }
        if (x>0.8 && x <0.9){
            tally_f[8] += I*track_length/0.1;
        }
        if (x>0.9 && x <1){
            tally_f[9] += I*track_length/0.1;
        }

    }

};

/**
 * @brief Main function to simulate neutron transport and calculate k_eff and neutron flux.
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments.
 * @return Program exit code.
 */
int main(){
    std::ofstream flux_output ("flux_output.txt");
    int multiplicity=0;
    double flux[10];
    int N_cycle=1000;
    int N_neutrons=10000;
    int i=0;
    int j=0;
    double k;
    initialization start;
    Interact Interaction;
    sampling my_sampling;
    Scoring tally;
    

    while (i<N_cycle){
        while(j<N_neutrons) {
          // here we initialize the position and region 
          double x = start.position();
          start.region(x);
          double a = start.sigma_a;
          double s = start.sigma_s;
          double f = start.sigma_f;
          int condition=1; 
          while (condition==1){
             start.region(x);
             // sampling to determine the type of interaction
          if (my_sampling.sample(a,s) == true){
             Interaction.scattering(a+s);
             double angle = Interaction.angle_sc;
             double ls = Interaction.ls;
             // this if condition is for stop tracking the particle if it is outside the region.
             if (ls > 1){
                break;
             }
             // This conditions for determining the direction of the neutron after scattering 
             if (angle >0){
                 x = x+ls;
             if (angle<0){
                x= x-ls;
             } 
             }
              tally.flux(x,(ls),1); // calculate the flux
              condition =1;
          }
          else {
            Interaction.absorption(f,a,s); // absorption take place
            double l = Interaction.l;
            if (l > 1){
                break;
             }
            multiplicity= multiplicity+ Interaction.I; // calculate the multiplicity accordingly
            x = l;
            tally.flux(x,(l),Interaction.I);
            N_neutrons = N_neutrons+Interaction.I;
            condition=1;
          }
          }
         
          j++;
        }
        // calculate the keff and multiplication factor.
        k = static_cast<double>(multiplicity)/N_neutrons;
     
        i++;
    }
    std::cout << "keff= " << k <<std::endl;

    // safe the flux data in txt file to be plot in python.
    for (int h=0; h<10;h++)
    {
    flux_output << tally.tally_f[h]<<std::endl;
    }
 return 0;
}