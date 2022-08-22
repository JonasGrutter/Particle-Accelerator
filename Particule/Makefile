CXX = g++
CC = $(CXX)

CXXFLAGS += -std=c++11
CXXFLAGS += -pedantic -Wall     # pour les purs et durs
CXXFLAGS += -g                  # pour debugger
#CXXFLAGS += -pg                 # pour profiler
#LDFLAGS  += -pg                 # pour profiler
#CXXFLAGS += -O2                 # pour optimiser la vitesse


all: test_particules testVecteur3D testAccell exerciceP9 exerciceP10 

testVecteur3D: Vecteur3D.o testVecteur3D.o

Vecteur3D.o: Vecteur3D.cc Vecteur3D.h

testVecteur3D.o: testVecteur3D.cc Vecteur3D.h

test_particules: test_particules.o particules.o Vecteur3D.o 

test_particules.o: test_particules.cc particules.h Vecteur3D.h constante.h support_a_dessin.h

particules.o: particules.cc particules.h Vecteur3D.h  constante.h dessinable.h support_a_dessin.h

element.o : Vecteur3D.h particules.h element.cc element.h constante.h dessinable.h support_a_dessin.h

testAccell : testAccell.o accelerateur.o Vecteur3D.o particules.o element.o 

testAccell.o : testAccell.cc accelerateur.h particules.h element.h constante.h dessinable.h support_a_dessin.h

accelerateur.o : accelerateur.cc particules.h element.h constante.h dessinable.h support_a_dessin.h

exerciceP9 : exerciceP9.o texte_viewer.o  accelerateur.o Vecteur3D.o particules.o element.o 

exerciceP9.o : exerciceP9.cc texte_viewer.h  accelerateur.h particules.h element.h 

texte_viewer.o : texte_viewer.cc texte_viewer.h support_a_dessin.h element.h accelerateur.h particules.h 

exerciceP10 : exerciceP10.o accelerateur.o Vecteur3D.o particules.o element.o

exerciceP10.o : exerciceP10.cc  accelerateur.h Vecteur3D.h particules.h element.h


