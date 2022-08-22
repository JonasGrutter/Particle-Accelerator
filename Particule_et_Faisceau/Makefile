CXX = g++
CC = $(CXX)

CXXFLAGS += -std=c++11
CXXFLAGS += -pedantic -Wall     # pour les purs et durs
CXXFLAGS += -g                  # pour debugger
#CXXFLAGS += -pg                 # pour profiler
#LDFLAGS  += -pg                 # pour profiler
#CXXFLAGS += -O2                 # pour optimiser la vitesse


all: testAccell ExerciceP11 

Vecteur3D.o: Vecteur3D.cc Vecteur3D.h

particules.o: particules.cc particules.h Vecteur3D.h  constante.h dessinable.h support_a_dessin.h

element.o : Vecteur3D.h particules.h element.cc element.h constante.h dessinable.h support_a_dessin.h

testAccell : testAccell.o accelerateur.o Vecteur3D.o particules.o element.o faisceau.o

testAccell.o : testAccell.cc accelerateur.h particules.h element.h constante.h dessinable.h support_a_dessin.h faisceau.h

accelerateur.o : accelerateur.cc particules.h element.h constante.h dessinable.h support_a_dessin.h faisceau.h

text_viewer.o : text_viewer.cc text_viewer.h support_a_dessin.h element.h accelerateur.h particules.h faisceau.h

faisceau.o : faisceau.h faisceau.cc dessinable.h support_a_dessin.h accelerateur.h particules.h

ExerciceP11 : ExerciceP11.o Vecteur3D.o particules.o element.o faisceau.o accelerateur.o 

ExerciceP11.o : ExerciceP11.cc  accelerateur.h particules.h element.h constante.h dessinable.h support_a_dessin.h faisceau.h



