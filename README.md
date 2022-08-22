# Particle-Accelerator
This was my first coding project when I was a first year student at EPFL in 2019. I did this project with my friend Chloé Mondon.

This programming project simulates a particle accelerator. 3 ways to use the accelerator are offered. The first is to simulate single particles without taking into account the interactions between them, the second is to use particle beams, again without taking into account the interactions. Finally, our accelerator allows us to simulate particle beams taking into account the forces between the particles.

# How does it work ?

This project is coded in C++. To make it work (text simulation), you need a compiler supporting the C++ 17 standard norm. For the graphics part Qt is needed. The project is separated in 3 files:
- "Particule"
- "Particule_et_Faisceau"
- "Mailles fodo"

The first file allows the simulation of particles (ExerciseP10) and beams without taking into account the interactions for the particles (ExerciseP11).
The second file allows a graphical simulation of particles and beams without taking into account the interactions between the particles using QT.
The last file allows a simulation of beams taking into account the interactions between the particles(ExerciseP13). The last file allows a simulation of beams taking into account the interactions between particles (ExerciseP13), as well as another by dividing the accelerator into boxes (ExerciseP14) so as not to have to go through the entire accelerator to make the particles interact with each other.

To compile and run the first and last file, proceed as follows:
- Open the terminal
- Go to the file in question
- Use the "make" command to compile the files together
- Execute the desired file with the command "filename.exe" (Windows) or with "./filename" (Linux)

The tests launched when running the "ExercisePx" files create an accelerator, display the 20 elements that compose it and the characteristics of the two particles/beams to be added. Then the particles/beams are added to the accelerator and their evolution is followed by displaying their main characteristics.
We have created two graphics files, one simulating particles and the other simulating beams (Graphics_Beams, Graphics_Particles)
To simulate the graphical part, proceed as follows
- Open the terminal
- Go to the file in question ( )
- Use the "Qmake" command to generate an assembler file
- Use the "make" command to compile the files together
- Open the "VueOpenGL" folder and click on "Nom_fichier_graphique
And you will see particles/beams spinning in an accelerator!
