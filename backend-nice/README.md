# nice-like
Backend pozwalający na zbudowanie dwupoziomowego menu i obsługi go za pomocą strzałek i klawisza Enter. Wywołanie występuje po naciśnięciu Esc.
## Kompilacja i uruchomienie
Poprawna kompilacja i możliwośc użycia nastąpi przy wcześniejszym połączeniu z toolem zgodnym z klasą abstrakcyjną Tool z pliku shared.hpp w następujący sposób:
```
Backend* nice-backend;
nice-backend = new nice();
b->tool = t \\ t - wskaźnik na używanego toola
```
## Główne metody
### Start
Metoda uruchamiająca główną pętlę programu.
Wywołanie poprzez ``` nice-backend->start(); ```
### Bindowanie
Bindowanie pozwala na dołączenie do menu własnych elementów wykonujących zdefiniowane przez siebie funkcje.
Wzór funkcji:
```
virtual void bind(std::string str, std::function<void()> func, std::string help);
```
Jest kilka możliwości wykorzystania tej funkcji, które są dokładniej opisane wraz z poniższymi przykładami.
Dwie podstawowe funkcje automatycznie dodawane do menu wraz z użyciem konstruktora.
```
bind(".File.Quit", [this]() { quit(); }, "Close program");
bind(".File.Help", [this]() { help(); }, "Show functions descriptions");
```
Kolejna funkcja, ten przykład można wykorzystać do dodania własnych funkcji w ```main()```:
```
bind(".Foo.Bar", [&](){foo();}, "Some help");
bind("#nice#.Foo.Bar", [&](){foo();}, "Some help"); \\Bind będzie interpretowany wyłącznie przez backend nice-like
```
Następny z przykładów pozwala na wywołanie funkcji wraz z dodatkowym okienkiem pobierającym parametr typu ```std::string```:
```
bind("#nice#.Foo.Bar${Komunikat do wyświetlenia w okienku|Entry}", [&](){foo();}, "Some help");
```
Entry zostanie przekazane poprzez ```setEntry(Entry, Pobrany_Wpis)```

**Obsługa klawiatury i klawisze specjalne**

W ramach obsługi specjalnego binda ```bind("<EDITION>", [&](){fun_edit();}, "");``` istnieje możliwość posługiwania się większością przycisków na klawiaturze, odbywa się to przez ustawienie ```setEntry("KEY", klawisz)``` i wywołania funkcji toola odpowiadającą za obsługę tych przycisków. Jednakże nie wszystkie klawisze mogą być przesłane jako char, dlatego są nazywane specjalnymi ciągami znaków. Poniżej podane są klawisze i ich nazwy przesyłane do toola:
- Enter ```<ENTER>```
- Backspace ```<BS>```
- Del ```<DEL>```
- strzałki ```<[U|D|L|R]ARROW>```
- F1-12 ```<F[1-12]>```

### Rebindowanie
Pozwala na zmianę działania zbindowanej funkcji w trakcie działania programu poprzez wywołanie funkcji o wzorze:
```
virtual void re_bind(std::string old_bind, std::string new_bind, std::function<void()> func);
```
***Funkcja nietestowana, może wywoławać błędy!***
