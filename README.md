# Particle-Accelerator
This was my first coding project when I was a first year student at EPFL in 2019.

This programming project simulates a particle accelerator. 3 ways to use the accelerator are offered. The first is to simulate single particles without taking into account the interactions between them, the second is to use particle beams, again without taking into account the interactions. Finally, our accelerator allows us to simulate particle beams taking into account the forces between the particles.

# How does it work ?

This project is coded in C++. To make it work (text simulation), you need a compiler supporting the C++ 17 standard norm. For the graphics part Qt is needed. The project is separated in 3 files:
- "Particle_and_beam"
- "Graphics"
- "Interraction_and_Extension"

The first file allows the simulation of particles (ExerciseP10) and beams without taking into account the interactions for the particles (ExerciseP11).
The second file allows a graphical simulation of particles and beams without taking into account the interactions between the particles using QT.
The last file allows a simulation of beams taking into account the interactions between the particles(ExerciseP13). The last file allows a simulation of beams taking into account the interactions between particles (ExerciseP13), as well as another by dividing the accelerator into boxes (ExerciseP14) so as not to have to go through the entire accelerator to make the particles interact with each other.
