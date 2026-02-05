1. Description Projet


2. Modèle mental routine Philo :

Un thread boucle sur un cycle
-penser
-prendre les fourchettes (2 mutex)
-manger
-met à jour last_meal_time
-reposer les fourchettes
-dormir

3. Problèmatique :
-Deadlock (blocage total)
Cas classique :
Tous les philosophes prennent la fourchette gauche
Tous attendent la droite
Personne n’avance
➡️ Deadlock garanti

-Starvation (famine)
Un philosophe mange beaucoup moins que les autres
Il finit par dépasser time_to_die
➡️ Simulation invalide

Politique d acces aux fourchettes
-Pair / impair

4. Rôle du monitor :
Vérifier régulièrement :
si now - last_meal_time > time_to_die

Déclenche :
affichage de la mort
arrêt global de la simulation
➡️ Ce monitor est un threads dedie

5. piège classique
Règles
Chaque log est atomique
Une mort doit être affichée ≤ 10 ms après l’instant réel
Après une mort → plus aucun log
➡️ Donc :
mutex pour l’affichage
flag global partagé (protégé) : simulation_running

6. Cas limites
1 philosophe
Une seule fourchette
Il ne peut jamais manger
Il meurt après time_to_die

memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock

philo between 1 et 200
time must be positive
nbrs of meal must be positive