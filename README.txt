.___________. _______ .___  ___.      ___          ___  
|           ||   ____||   \/   |     /   \        |__ \ 
`---|  |----`|  |__   |  \  /  |    /  ^  \          ) |
    |  |     |   __|  |  |\/|  |   /  /_\  \        / / 
    |  |     |  |____ |  |  |  |  /  _____  \      / /_ 
    |__|     |_______||__|  |__| /__/     \__\    |____|



===Task 1===

	Functia number_of_occurences() returneaza numarul de aparitii ale unui
cuvant, word, in textul dat, retinut in variabila text. Foloseste o copie a
fiecarei linii si prin functia strtok() din <string.h> desparte in cuvintele din
linie in functie de separatorii dati (separatorii se afla in DELIMITATORS). Apoi
se compara word cu fiecare cuvant obtinut prin procedeul strtok(), iar in caz de
coincidenta se incrementeaza contorul nr_occurences, care la sfarsit se returneaza.

	Functia replace_words() inlocuieste toate aparitiile unui cuvant word cu
alt cuvant, replacer. Utilizand functia strstr() din <string.h> se cauta prima
aparitie a secventei (in cazul nostru cuvantului) word, care se retine in 
position_word. Apoi se copiaza toata linia ce urmeaza dupa secventa gasita in rest.
Se verifica daca ceea ce s-a gasit e intr-adevar cuvant si, daca e, se foloseste
functia strcpy() din <string.h> pentru a se copia cuvantul replacer in locul
cuvantului gasit (functia strcpy() suprapune noul sir de caractere peste cel vechi),
apoi se concateneaza la sfarsit restul textului salvat inainte de verificarea
secventei.

	Functia permute() permuta circular la dreapta cu k pozitii fiecare cuvant
din text. Se observa ca a se permuta de k este acelasi lucru cu a se permuta de
k % strlen(token) ori, unde token e cuvantul din text obtinut prin procedeul
strtok de la functia number_of_occurences(), apoi se inlocuieste in text folosind 
principiul de la functia replace_words().

	In programul principal se citeste numarul de linii ale textului, apoi fiecare
linie cu fgets(). Pentru ca fgets() retine si \n de la capatul liniei se foloseste o
variabila garbage pentru primul \n dat din cauza citirii numarului de linii, iar apoi
fiecare \n de pe fiecare linie care nu e goala (contine doar \n) este inlocuit cu \0.
Apoi se citesc numarul de optiuni si optiunile. La sfarsit se dezaloca memoria cu free().



===Task 2===

	Functia create_list() creeaza o lista de cuvinte unice si o lista de aparitii
ale acelor cuvinte. Se foloseste procedeul strtok() pe o copie a liniei si se verifica
daca cuvantul a fost retinut pana atunci: daca da, se incrementeaza numarul de aparitii;
daca nu, se adauga in lista si se initializeaza numarul de aparitii cu 1. Cele doua liste
sunt vectori. La final functia returneaza numarul de elemente ale listelor.

	Functia max_nr_words() returneaza numarul de cuvinte din text, folosind procedeul
strtok() amintit mai sus.

	Functia buble_sort sorteaza folosind algoritmul bubble sort cele doua liste astfel:
se sorteaza descrescator cuvintele din lista de cuvinte dupa numarul de aparitii, iar in caz
de egalitate crescator dupa cuvant.

	Functia dist() returneaza distanta dintre 2 cuvinte, unde distanta a 2 cuvinte e
definita in enunt.

	Functia sim() returneaza gradul de similitudine folosind formula din enunt.

	In programul principal se citesc cele doua texte prin aceeasi metoda ca la Task 1.
Apoi se creeaza cele doua liste pentru fiecare text, se sorteaza si se afiseaza gradul de
similitudine. La sfarsit se dezaloca memoria.




===Task 3===

	Functia wildcard_string_matching() verifica daca un cuvant word se potriveste
pentru sablonul (cuvantul pentru expresia regulata), retinut in pattern: returneaza 1 
in caz de potrivire sau 0 in caz contrar. 
	Se verifica daca cuvintele fara "*" fac match pentru sablon. In cazul in care 
cuvantul are "*" se verifica daca partea de dupa acesta (daca exista) face match. Pentru
ca "*" inseamna "orice caracter" ne intereseaza ce se afla dupa acest caracter in pattern:
retinem valoarea pattern-ului si a cuvantului de dupa match. Apoi verificam daca mai contine
caractere identice sau ".", care inseamna "un singur caracter". Toate acestea au loc pana
cand se ajunge la capatul lui word.
	Ultima verificare se face pentru cuvintele care se termina cu "*", facuta pentru
cazul in care cuvantul se termina inainte pattern-ului.

	In programul principal se citeste textul in aceeasi maniera ca si la celalalte Task-uri.
Apoi se citeste numarul de expresii regulate, si pentru fiecare se va verifica in text. Se
foloseste procedeul strtok() la fiecare copie a liniei, apoi se aplica functia creata pentru
fiecare cuvant de pe linie, respectiv din text. La final se afiseaza numarul de potriviri, 
apoi se dezaloca memoria.
