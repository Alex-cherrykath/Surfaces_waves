# Surfaces_waves
simulation d'eau 2D avec reflexion, diffraction, sources multiples controlables.
Le projet se nomme Surface_waves

    Parlons des ondes de surfaces.
 c'est quoi une onde de surface? 
c'est une onde qui se propage le long d'un milieu. 
les vagues océaniques sont les exemples les plus connus 
d'ondes de surface.

-Dans une onde de surface, les particules du milieu se déplaçent de haut
en bas ainsi que d'avant en arriere dans un mouvement globalement
circulaire. les particules ne se rapprochent pas effectivement
du rivage quand les vagues passent.

Il existe differents types d'onde de surface:
-les ondes de Rayleigh qui se caractérisent par un mouvement vertical de 
la surface du sol comme les ondes sur l'eau.
-les onde de Love se caractérisent par un mouvement horizontal

nb: les onde de surface ont generalich une plus grande amplitude que les
ondes de volume et elles causent plus de degats.


qu'est ce que la reflexion d'une onde?
    -l'experience nous montre que qd la vague frappe le bord d'un mur de
    face, elle repart en arrière.
    -si elle ne se présente pas face au bord, elle est reflechie de sorte
    que le front fasse le meme angle avec le bord après la reflexion.
    -la reflexion de Descates.

c'est quoi la diffraction?
    Qd les vagues rencontrent un obstacle,elle sont pertubées, c'est ca qu
    on appelle la diffraction.

   Stack Technique & Dépendances de Langage :
  C++ (Standard 17 ou 20 recommandé).
  Graphismes : SDL3 (Version de développement).
  Interface : Dear ImGui (Docking branch pour le support SDL3).
  Physique : Algorithmes basés sur The Nature of Code de Daniel Shiffman.
  
   Concepts Physiques Implémentés
Le projet repose sur la discrétisation de l'espace pour simuler les ondes de surface.
1. Oscillation de base
Inspiré par le chapitre 3 (Oscillations) de Shiffman, chaque point de la surface suit une fonction harmonique :
 X= amplitude * cos(TWO_PI * frameCount / period)
Réflexion (Descartes) : Lorsqu'une onde frappe une paroi rigide, elle est renvoyée avec un angle incident égal à l'angle de réflexion.Diffraction : Les ondes contournent les obstacles, créant de nouveaux fronts d'ondes circulaires aux points de contact.

2. Types d'ondes gérées
Ondes de Rayleigh : Mouvement elliptique des particules (haut/bas et avant/arrière).
Ondes de Love : Mouvement horizontal de cisaillement (mouvement de surface pur).

3.Contrôles & UI
L'interface ImGui permet de manipuler les paramètres en temps réel :Amplitude & Période : Modifier la force et la fréquence des sources.Source Placement : Ajouter des sources d'ondes par clic gauche.Obstacles : Dessiner des murs pour observer la diffraction et la réflexion.

 Références
 The Nature of Code, Daniel Shiffman (Chapitre 3 : Oscillations, p. 110).
 Lois de Snell-Descartes pour la réflexion.

 la suite sera rempli apres lecture d'autres documents.
