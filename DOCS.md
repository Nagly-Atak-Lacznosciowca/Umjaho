# Umjaho

## Autorzy:
Projekt stworzył pięcioosobowy zespół uczniów klasy 3P Technikum Łączności nr 14 w Krakowie, w składzie:
- Bartosz Kozub (@JDCombat)
- Oskar Biedroń (@bozgi)
- Oskar Zdechlik (@SokZKomucha)
- Patryk Niemiec (@niemiets)
- Szymon Urbaniak (@HexHyperion)

## O projekcie:
lorem ipsum coś tam coś tam wybraliśmy wyścigi i cierpimy

## Technologie:
Cały projekt został stworzony w języku C++ z wykorzystaniem biblioteki SDL3. Za budowanie projektu odpowiedzialny jest CMake, a do pisania kodu wykorzystywaliśmy program JetBrains CLion. Do zarządzania wersjami używamy Gita, a do hostowania kodu platformy GitHub (repozytorium znaleźć można pod [tym adresem](https://github.com/Nagly-Atak-Lacznosciowca/Umjaho)).


## Obsługa programu:
Po uruchomieniu programu użytkownik zostaje przeniesiony do ekranu tytułowego z menu głównym, w którym może wybrać jedną z czterech opcji:

### `Play` - uruchomienie wyścigu
Po wybraniu opcji `Play` użytkownik zostaje przeniesiony do menu wyboru poziomu, gdzie może wybrać jeden z trzech torów:
- `Level 1` - tor o niskiej trudności, w całości pokryty asfaltem.
- `Level 2` - tor o średniej trudności, część trasy jest nieutwardzona.
- `Level 3` - tor o najwyższej trudności, część trasy pokryta jest lodem.

Tory opisane są bardziej szczegółowo w dalszej części dokumentacji.<br>
Z menu wyboru poziomu można wrócić do menu głównego, naciskając klawisz `Esc` lub przycisk `Return`, widoczny w lewym górnym rogu aplikacji.


### `Settings` - panel ustawień
W tym panelu użytkownik może dostosować różne opcje gry. Znajdują się tam następujące opcje:
- `Volume` - kontrolki odpowiedzialne za ustawienie głośności gry.
- `Current car color` - wybór koloru samochodu. Użytkownik klikając na model auta może wybrać jeden z sześciu kolorów: czerwony, niebieski, zielony, żółty, pomarańczowy i fioletowy.
- `Show FPS` - przełącznik decydujący o tym, czy wyświetlać licznik FPS w rogu ekranu.

Tak jak menu wyboru poziomu, ustawienia zamknąć można klawiszem `Esc` lub przyciskiem `Return` w lewym górnym rogu programu.


### `Credits` - informacje o autorach
Opcja ta zawiera ekran końcowy, na którym znaleźć można informacje o autorach projektu. Widok ten opuścić można naciskając klawisz `Esc`.


### `Exit` - zamknięcie programu
Po wybraniu tej opcji gra zostaje zamknięta, a użytkownik wraca do pulpitu.


## Wyścig i sterowanie pojazdem
Po wybraniu toru, samochód gracza zostaje umieszczony na starcie, a na ekranie pojawia się licznik odliczający do rozpoczęcia wyścigu. Oprócz gracza, na torze znajduje się 4 przeciwników, którzy również biorą udział w wyścigu. Po zakończeniu odliczania, gracz może rozpocząć jazdę. Sterowanie pojazdem odbywa się za pomocą klawiatury:
- `W` - przyspieszenie
- `S` - hamulec / jazda wstecz
- `A` - skręt w lewo
- `D` - skręt w prawo
- `Space` - użycie nitro
- `X` - użycie gadżetu
- `Esc` - menu pauzy

Po puszczeniu klawisza `W` (lub `S` na wstecznym), pojazd będzie hamował silnikiem aż do całkowitego zatrzymania. Po puszczeniu `A` i `D` samochód samoczynnie wyprostuje koła.<br>
Menu pauzy `Esc` można otworzyć w dowolnym momencie, a po jego uruchomieniu gra zatrzymuje się. Zawiera ono następujące opcje:
- `Resume` - powrót do gry
- `Settings` - przejście do menu ustawień
- `Exit to title` - powrót do menu głównego
- `Exit to desktop` - zamknięcie gry i powrót do pulpitu

Celem wyścigu jest pokonanie wyznaczonej liczby okrążeń i dojechanie do mety w jak najkrótszym czasie, wyprzedzając przy tym przeciwników. Po zakończeniu wyścigu, gracz zostaje przeniesiony do tabeli wyników, na którym widoczne są następujące informacje:
[WIP]

Ekran ten opuścić można z użyciem klawisza `Esc` lub przycisku `Return` u dołu ekranu. Po zakończeniu wyścigu, gracz powraca do ekranu tytułowego, skąd może rozpocząć kolejny wyścig lub zamknąć program.


## Elementy poziomu
### Tor wyścigowy
Dostępną dla samochodów częścią poziomu jest tor wyścigowy, mający postać zamkniętej pętli - samochód nie może opuścić drogi; będzie się on obijał o jej krawędzie, wytracając prędkość. Nawierzchnia toru zmienia się w zależności od poziomu, a wraz z nią właściwości jezdne pojazdów.

### Nawierzchnie
- `Asfalt` - domyślna nawierzchnia toru, zapewniająca dobrą przyczepność i stabilność pojazdu. Samochód porusza się po nim z maksymalną prędkością, może skręcać i hamować bez przeszkód.
- `Tarka` - charakterystyczny biało-czerwony krawężnik o stosunkowo dobrej przyczepności, lecz znacznie spowalniające samochód.
- `Szuter` - nieutwardzona nawierzchnia o średniej przyczepności, spowalniająca samochód i utrudniająca skręcanie.
- `Lód` - nawierzchnia o niskiej przyczepności, niewpływająca na prędkość samochodu, lecz skrajnie utrudniająca skręcanie i wydłużająca drogę hamowania.

### Przeszkody
- `Bariera` - zapobiega opuszczeniu toru. Po kolizji z nimi samochód wytraca prędkość, lecz nie zostaje zniszczony.
- `Pachołek` - po wjechaniu w niego samochód traci prędkość. Po pierwszej kolizji zostaje zniszczony i znika z toru.
- `Brama` - otwiera się i zamyka co pewien czas. Zamknięta brama zachowuje się identycznie do barierek, otwarta nie wpływa na pojazd.
- `Próg zwalniający` - zmniejsza prędkość samochodu po najechaniu. Nie wpływa na kierunek jazdy pojazdu.
- `Woda` - nieco zmienia kierunek jazdy samochodu.
- `Olej` - znacznie zmienia kierunek jazdy samochodu. Po najechaniu na olej gracz może na chwilę stracić panowanie nad pojazdem.

### Doładowania
- `Nitro` - po najechaniu na nie, gracz zyskuje jeden ładunek nitro. Po trzykrotnym doładowaniu gracz ma możliwość użycia nitro, co na krótki czas zwiększa prędkość samochodu.
- `Gadżet` - po najechaniu na nie, gracz zyskuje ładunek gadżetu. Użycie gadżetu powoduje pozostawienie na torze tymczasowej przeszkody, która znika po pewnym czasie.

### Linia mety i punkty kontrolne
Na torze wyznaczone są niewidzialne punkty kontrolne, przez które należy przejechać, by okrążenie zostało zaliczone. Okrążenie nie będzie zaliczone, jeśli gracz ominie jakąkolwiek część toru (np. źle skręci na skrzyżowaniu) lub przejedzie przez linię mety przeciwnie do kierunku wyścigu.

### Przeciwnicy
[WIP]