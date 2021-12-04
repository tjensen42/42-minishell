

# Expander

// Split zu list umwandeln

char	**cmd; 		->string_liste
char	**redirs;	->string_liste
char	**files;	->string_liste

=> dann Wildcards & variables gleichzeitig
=> List to split conversion


=== keine Wildcards in Quotes

heikelste Sache:
"$ARG1"$ARG2

// Split struktur behalten

- Variablen und Wildcards gleichzeitig Ersetzen ???
	- Variablen erfordern nur string manipulation
	- Wildcards erfordern split manipulation


# Resources

https://superuser.com/questions/420295/how-do-i-see-a-list-of-all-currently-defined-environment-variables-in-a-linux-ba


-> path_get unset PATH execution with or without "./"

-> connected token in printer

-> PATH test: wenn / vorhanden nur direkt ohne an PATH-Folder anzuhaengen, wenn keins vorhanden nur an alle PATHs anhaengen, auch an einen leeren







// EXECUTION OPTIMIERUNG

-> einfache SCMD's nicht in Pipelines packen
-> exitten by pipe error...
-> error management / fork() fail
+ Builtin_check
+ Builtin_exec


env


04.12
-> PATH holen
-> env check with Valgrind
-> execution pipeline protections

