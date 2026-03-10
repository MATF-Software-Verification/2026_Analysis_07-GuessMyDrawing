# Analiza projekta GuessMyDrawing

U ovom direktorijumu nalazi se analiza softverskog projekta **GuessMyDrawing** izrađena u okviru samostalnog projekta iz kursa *Verifikacija softvera* na master studijama Matematičkog fakulteta Univerziteta u Beogradu.

## Autor

Ime i prezime: Jelena Ivanović  
Broj indeksa: 1133/25


## Opis projekta

GuessMyDrawing je aplikacija implementirana u programskom jeziku C++ uz korišćenje Qt framework-a. Aplikacija predstavlja igru u kojoj jedan korisnik dobija zadatak da nacrta određenu reč, dok ostali učesnici pokušavaju da pogode šta je nacrtano. Sistem se sastoji iz serverskog dela koji upravlja komunikacijom između klijenata i koordinira tok igre, kao i klijentskog dela koji omogućava korisnicima da učestvuju u igri.

Originalni projekat dostupan je na adresi:  
https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2021-2022/07-GuessMyDrawing

Grana projekta na kojoj je izvršena analiza: master.

## Prevođenje projekta

Najpre je potrebno kreirati direktorijum za build i preći u njega:

mkdir build
cd build

Zatim se pokreće generisanje Makefile fajla pomoću komande:

qmake ..

Nakon toga projekat se kompajlira pomoću komande:

make

## Pokretanje aplikacije

Nakon uspešne kompilacije moguće je pokrenuti serverski i klijentski deo aplikacije.

Server se pokreće komandom:

./Server

Nakon pokretanja servera može se pokrenuti klijentska aplikacija:

./Application

---


## Catch2

Catch2 je C++ biblioteka koja se koristi za pisanje i izvršavanje testova. U okviru projekta korišćena je za implementaciju unit i integracionih testova.

Instalacija biblioteke vrši se komandom:

sudo apt install catch2

## Pokretanje testova

Testovi se prevode korišćenjem CMake sistema za izgradnju.

Najpre je potrebno preći u direktorijum sa testovima i kreirati direktorijum za build:

mkdir build  
cd build  

Zatim se pokreće konfiguracija projekta:

cmake ..

Nakon toga se test program kompajlira:

make

Posle uspešne kompilacije generiše se izvršni fajl `seminar_tests`.  
Testovi se pokreću komandom:

./bin/seminar_tests

Moguće je pokrenuti i samo određene testove korišćenjem filtera. Na primer:

./bin/seminar_tests "[seminar][unit]" ili ./bin/seminar_tests "[seminar][integration]"

---

# LCOV

LCOV je alat koji se koristi za analizu pokrivenosti koda tokom izvršavanja testova. Na osnovu prikupljenih podataka generiše se HTML izveštaj koji prikazuje pokrivenost linija i funkcija u projektu.

Instalacija alata:

sudo apt install lcov

Pokretanje analize pokrivenosti:

chmod +x run_coverage.sh

./run_coverage.sh

---

# Valgrind

Valgrind je alat za dinamičku analizu memorije koji omogućava detekciju curenja memorije i drugih problema u radu sa dinamički alociranom memorijom.

Instalacija alata:

sudo apt install valgrind

## Pokretanje Memcheck analize

chmod +x run_valgrind.sh

./run_valgrind.sh

## Pokretanje Massif analize

chmod  +x run_massif.sh

./run_massif.sh

## Pregled Massif izveštaja

ms_print massif.out
---

# Cppcheck

Cppcheck je alat za statičku analizu C i C++ koda koji omogućava pronalaženje potencijalnih grešaka i problema u implementaciji bez izvršavanja programa.

Instalacija alata:

sudo apt install cppcheck

Pokretanje analize:

chmod +x run_cppcheck.sh

./run_cppcheck.sh

---

# Clang-Tidy

Clang-Tidy je alat zasnovan na Clang kompajleru koji omogućava statičku analizu koda i proveru stilskih i logičkih problema.

Instalacija alata:

sudo apt install clang-tidy

Pokretanje analize:

chmod +x run_clang.sh

./run_clang.sh

--- 

# Zaključak analize

Na osnovu sprovedene statičke i dinamičke analize može se zaključiti da projekat GuessMyDrawing poseduje stabilnu  funkcionalnost. Analiza memorije izvršena pomoću alata Valgrind nije ukazala na značajna curenja memorije tokom izvršavanja programa. Alati za statičku analizu, kao što su Cppcheck i Clang-Tidy, identifikovali su manji broj upozorenja koja se uglavnom odnose na stil koda i potencijalna poboljšanja implementacije. Kombinacija korišćenih alata omogućila je detaljniji uvid u kvalitet softverskog sistema i ukazala na moguće pravce njegovog daljeg unapređenja. Analiza pokrivenosti koda pokazala je da početna pokrivenost testovima nije bila naročito visoka, zbog čega su implementirani dodatni unit i integracioni testovi kako bi se obuhvatio veći deo funkcionalnosti sistema i povećala pouzdanost aplikacije.