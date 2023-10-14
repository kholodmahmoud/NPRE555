Kholod H. Mahmoud
#########################################################################################################
This code calculates the multiplication factor and the neutron flux in a slab of 1 m thickness.
The code is written in C++ and plotting the flux using matplotlib
The code runs 1000 cycles each cycle with 10000 particles.
The user can modify the number of particles or cycles by changing the N_neutrons and N_cycle in the CP1.cc file.
##############################################################################################################
 How to run :
 Download the file CP1_kholodmahmoud
 in the terminal and run the shell script run.sh after you run 'chmod +x run.sh'  
 The multiplication factor will print in the terminal, and the graph of the neutron flux will appear on the screen. 
 
 The code is written with documentation that can easily create a doxygen file for it by run doxygen -g <config_file_name> 
 open the <config_file> in the INPUT section write the .cpp file name, and it will create it automatically. 

Included in this branch is the latex doxygen version. 
