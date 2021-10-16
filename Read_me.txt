Le code de la voiture est divisé en deux programmes principaux à transférer sur l'arduino selon le scénario souhaité. 

Le premier répertoire ( Main ) contient six fichiers.ino qui sont :

main.ino, mainAuxFun.ino, motor.ino, Obstaclavoid.ino, Sensors.ino et steering.ino

Ces fichiers contiennent cinq scénarios : 

1 - Marche avant et marche arrière Demo 

2 - Avancer tourner droite et gauche 

3 - Se garer d'une manière autonome 

4 - Suivi d'un chemin prédéfinis

5 - doubler une autre voiture ( obstacle ) 


Par défauts la voiture est en mode repos selon le scénario choisi et elle exécute une routine pendant la durée de démonstration et pendant
cette routine qui est contrôlé par le temps la voiture reste en mode autonome, ce qui veut dire qu'on ne peut pas contrôler la voiture jusqu'à 
la fin de la démonstration.
Puis elle reste en mode repos jusqu'à elle reçoit un nouveau scénario qui sera appelé par la télécommande infrarouge.  


Le deuxième répertoire ( Main2 ) contient aussi six fichiers.ino qui sont:

main2.ino, mainAuxFun.ino, motor.ino, Obstaclavoid.ino, Sensors.ino et steering.ino

Dans ce fichier, main2, la voiture fonctionne d'une manière autonome à 100% c'est-à-dire au début elle marche en avant et en même temps tous les
capteurs (devant, droit, gauche, arrière) mesurent et fonctionnent d'une manière simultané et grâce à cela la voiture réagit d’une manière autonome.
Par exemple, si elle détecte un obstacle à droite elle se tourne à gauche ou si elle trouve un obstacle devant elle prend la décision de doubler en 
tenant compte de la distance à gauche et à droite.
Dans ce mode la seule méthode pour la voiture s’arrête il faut couper le courant en utilisant un bouton (on off).
