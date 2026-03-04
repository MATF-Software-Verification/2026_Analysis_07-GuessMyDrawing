# Analiza projekta GuessMyDrawing

U ovom direktorijumu nalazi se analiza softverskog projekta **GuessMyDrawing** izrađena u okviru seminarskog rada iz kursa *Verifikacija softvera* na master studijama Matematičkog fakulteta Univerziteta u Beogradu.

## Autor

Ime i prezime: Jelena Ivanović  
Broj indeksa: 1133/25


## Opis projekta

GuessMyDrawing je aplikacija implementirana u programskom jeziku C++ uz korišćenje Qt framework-a. Aplikacija predstavlja igru u kojoj jedan korisnik dobija zadatak da nacrta određenu reč, dok ostali učesnici pokušavaju da pogode šta je nacrtano. Sistem se sastoji iz serverskog dela koji upravlja komunikacijom između klijenata i koordinira tok igre, kao i klijentskog dela koji omogućava korisnicima da učestvuju u igri.

Originalni projekat dostupan je na adresi:  
https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2021-2022/07-GuessMyDrawing

Grana projekta na kojoj je izvršena analiza: master.

## Prevođenje projekta

Za prevođenje projekta potrebno je instalirati Qt i CMake alate. Nakon instalacije zavisnosti projekat se može prevesti kreiranjem build direktorijuma, pokretanjem CMake konfiguracije i kompilacijom projekta pomoću alata make.

## Pokretanje aplikacije

Nakon uspešne kompilacije moguće je pokrenuti server i klijent. Server se pokreće izvršavanjem programa Server, dok se klijentska aplikacija pokreće izvršavanjem programa Application.

---
# Doxygen

Doxygen je alat koji omogućava automatsko generisanje dokumentacije na osnovu komentara u izvornom kodu. Korišćenjem ovog alata generisana je HTML dokumentacija projekta koja omogućava lakši pregled strukture sistema, klasa i funkcija.

Instalacija alata:

sudo apt install doxygen

Pokretanje generisanja dokumentacije vrši se pomoću skripte.

Najpre je potrebno dati dozvolu za izvršavanje skripte:

chmod +x run_doxygen.sh

Nakon toga skripta se pokreće komandom:

./run_doxygen.sh

---

# Catch2

Catch2 je C++ biblioteka koja omogućava pisanje i izvršavanje testova. U okviru projekta korišćena je za implementaciju unit i integracionih testova.

Instalacija biblioteke:

sudo apt install catch2

Pokretanje testova vrši se pomoću skripte.

chmod +x run_tests.sh

./run_tests.sh

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

Pokretanje analize memorije:

chmod +x run_valgrind.sh

./run_valgrind.sh

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

Na osnovu sprovedene statičke i dinamičke analize može se zaključiti da projekat GuessMyDrawing poseduje stabilnu osnovnu funkcionalnost i relativno dobar nivo pokrivenosti testovima. Analiza memorije nije ukazala na značajna curenja memorije tokom izvršavanja programa, dok su alati za statičku analizu identifikovali manji broj upozorenja koja se uglavnom odnose na stil koda i potencijalna poboljšanja implementacije. Kombinacija različitih alata omogućila je detaljan uvid u kvalitet softverskog sistema i ukazala na moguće pravce daljeg unapređenja.