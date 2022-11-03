# Partie création de la base de données


```
Le but de cette partie est la création de la base de données où seront stockées les données. 
```

```
Au démarrage, le programme lis le fichier ressources pour obtenir le chemin
vers la base de données ainsi que la requête de création de la table.

Le programme est indépendant de la base et du contenu de la requête.
```

## Les valeurs lues dans le fichier properties :

```
Au démarrage, le programme lis le fichier ressources pour obtenir le chemin
vers la base de données ainsi que la requête de création de la table.
```

```
url_data_base
request_create_table
```

# Note

```
Pour plus d'informations, veuillez consulter le fichier values.properties à la racine.
```

# Construire les exécutables :

```
Construire l'exécutable : 
```
**make build** 
```
Regrouper dans un fichier zip les fichiers cpp, hpp et le makefie
```
**make zip**
```
Supprimer les fichiers *.o, l'exécutable le zip
```
**make clean**

```
Lancer l'exécutable
```
**./create_db ../values.properties**


