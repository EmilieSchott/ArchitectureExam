# TeamWork

## Les antipatterns répérés

### Loi de Brooks

L'auteur de l’article parle des allers-retours qu’il a fait sur le projet. Cela nous informe donc que les membres de l’équipe ne sont pas restés sur le projet d’un bout à l’autre.
Les onboardings des membres arrivant sur le projet qui fait perdre beaucoup de temps afin de ratrapper ce qui a été fait par le reste de l’équipe. La montée en compétence est lente et difficile surtout sur un projet aussi énorme que l’est skull and bone.

Vu l’ambition du projet, la taille de l’équipe était énorme. Le jeu a été développé par une équipe à Singapour mais on nous dit dans l’équipe qu’il y avait également une équipe à Paris.
La communication qu’il devait falloir pour coordonner les équipes devaient être extrêmement importants mais en plus s’ajoutait à cela la difficulté de se trouver sur des fuseaux horaires différents. 

Ces temps perdus par les membres de l’équipe en onboarding et en difficulté de communication pointe vers la loi de Brooks qui stipule que la vitesse d’exécution d’un projet ne dépend pas du nombre de développeur sur le projet parce qu’il y a (entre autre) des coûts de communication et d’oboarding incompressibles.

On peut ajouter que ses arrivées de nouvelles personnes sur le projet, notamment à des postes clés, ont changé la direction du projet et on donc fait perdre du temps à l’équipe en explorant d’autres pistes. Le projet a ainsi connu de nombreux reboots. 

### GoldPlating 

L’article nous apprend que pour justifier le prix du jeu, on a ajouté des features qui avaient des difficultés techniques importantes mais qui n’apporaient pas pour autant grand-chose au coeur du jeu : le fait d’être un jeu online, systemique et open-ended.
Ces aspects ont tellement prix le pas sur le coeur du jeu et gameplay que cela est passé au second plan, rendant l’expérience vide et sans âme. 

### Conception Waterfall

Le jeu a suivi plutôt un développement waterfall. Les développeurs avaient dès le début une feuille de route des fonctionnalités minimales que devaient posséder le jeu et sur où il devait aller : jeu  online, systemique et open-ended.
Le processus n’a ainsi pas été itératif visant tout de suite une scope extrêmement ambitieux au lieu de créer d’abord un jeu plus petit avec seulement un de ces critères. 

### Feature Factory 

L’auteur nous dit que les équipes étaient exténués de travailler incessamment sur le même jeu sans avoir le temps de respirer. Ils étaient donc quelque part appelé à produire feature sur feature. Il fallait produire vite étant donné que le jeu avait déjà énormément de retard. Pas le temps de faire de la qualité, de refactoriser ou même de prendre du recul pour voir ce qui fonctionne ou pas en terme de gameplay.

### Hero of the day

On nous dit que les équipes étaient exténués. Cela laisse supposer qu’il y avait également une culture du Héros du jour, qui demandaient constamment aux équipes des efforts pour produire le jeu le plus rapidement possible en faisant des heures supplémentaires afin de le sauver de la catastrophe.

## Changements de management suggérés

Le jeu aurait probablement mieux profiter d’un management plus agile :
- prioriser le coeur de l’expérience plutôt que les services annexes qui font vendre
- ajouter les features au projet au fur et à mesure afin d’avoir toujours un jeu jouable. On aurait pu ainsi fixer une fin de projet à n’importe quel moment et avoir un projet jouable et fini qu’on aurait pu continuer à faire évoluer ensuite en live. Ainsi pas besoin d’avoir des sauveurs de projet qui crunchent.
- des features indépendantes les unes des autres que l’on rajoute au fur et à mesure.
- ces features aurait gagné à être développées par des petites équipes constitués au moment du besoin pour que tout le monde arrive en même temps sur ce sujet. Cela aurait permis une fois la mission réalisée de les laisser reparrtir et ainsi de ne pas user leur force.

