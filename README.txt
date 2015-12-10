	-------------------------------
	| Projet SDD L2 C - MORA - TO |
	-------------------------------
	
	Ce fichier est à lire de préférence sous Notepad++
	
	Auteurs
	-------
	
		Benjamin MORA
		John-Michaël TO
	
	Dates du projet
	---------------
	
		Début 	:	13/10/2012
		Fin 	:	16/12/2012
	
	Préambule
	---------
	
	Dans le cadre du projet de Structures de données, nous avons créé un
	framework permettant de jouer à divers jeux de puzzle du type sliding block.
	De plus, nous avons tenté de créer une Intelligence Artificielle permettant
	de résoudre ces divers jeux de la façon la plus générique possible.
	
	Séparation du framework et de l'IA
	----------------------------------
	
	Nous avons fait le choix de séparer le framework de l'IA du fait que l'IA
	que nous avons développée est générique, mais l'algorithme A* utilise une
	mémoire assez conséquente qui risque de faire planter le framework.
	
	Détail des fichiers du projet
	-----------------------------
	
	README.txt						Ce fichier
	
	Sources							Dossier des fichiers sources
		main_IA.cpp					main de l'IA
		main_Jeu.cpp				main du framework
		mainwindow.h/cpp
		vue.h/cpp
		pile.h/cpp
		liste.h/cpp
		configParser.h/cpp
		listeD.h/cpp
		jeu.h/cpp
		IA.h/cpp
		ClassListAStar.h/cpp
		ressources.qrc
		Jeux						Dossier des fichiers de configuration des jeux
		Ressources					Dossier contenant les ressources liées au framework
		
	Makefile						Dossier des scripts de compilation
		IA							Dossier des scripts de compilation de l'IA
			Makefile
			Makefile.Debug
			Makefile.Release
		Jeu							Dossier des scripts de compilation du framework
			Makefile
			Makefile.Debug
			Makefile.Release
	
	Compilation
	-----------

	1)	La compilation est effectuée sous Qt Creator avec gcc pour le framework

	2)	La compilation est effectuée sous Code Blocks avec gcc pour l'IA

	3)	L'exécutable du framework est généré dans un nouveau dossier à la racine dans debug ou release
	
	4)	L'exécutable de l'IA est généré dans le dossier bin/Debug ou bin/Release
	
	Etat d'avancement
	-----------------
	
	- Apprendre la programmation sous Qt								Fait
	- Création du plateau de jeu à l’aide de Qt							Fait
	- Création du parseur : chargement du fichier de configuration		Fait
	- Création des mécanismes de jeu									Fait
	- Création de l’IA													Fait
	- Ajout de l'option "tore"											A Faire
	- Création de l’éditeur de fichier de configuration					A Faire
	
	Références & Sources
	--------------------
	
	- Jeu de taquin et générateurs du groupe alterné - Michel Coste Université de Rennes
	- Recherche de chemin par l'algorithme A* - http://khayyam.developpez.com/articles/algo/astar/
	- Prologin : Up and Running - Nicolas Boumal
	- Real-time Heuristic Search for Pathfinding in Video Games - Vadim Bulitko
	- Solving Klotski - Karl Wiberg
	
	Fonctionnalités optionnelles
	----------------------------
	
	- Option pour annuler / rétablir un déplacement effectué
	- Affichage de l'état but à tout moment d'une partie en cours
	- Possibilité de sauvegarder une partie sauvegardée
	- Possibilité de charger une partie sauvegardée
	- Génération d'un guide de résolution à partir de l'IA