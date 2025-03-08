# Racing game Umjaho

This is a project for the [Motorola Science Cup 2025](https://science-cup.pl/) contest.


## TODO

Soboty przed 04.01:
- 03.01
- 03.08
- 03.15
- 03.22
- 03.29

jak mi się nie chce tego robić <br>
zróbmy w canvasie

```
SceneElement
    Circuit?
    Obstacle
        Barrier
        Gate
        Puddle
        ...
    Car
        Player
        Opponent
```

### 1) Sceny `(SceneManager)`
- Sceny półprzezroczyste (np. by mieć Level, menu z escape, potem ustawienia itp). Do tego w SceneManager musiałby być Vector ze scenami
- Przechodzenie między scenami, w jakikolwiek sposób
- Renderowanie zawartości scen

### 2) Eventy? 

### 3) Auto i fizyka, sterowanie
- Żeby w ogóle wyświetlić auto
- sterowanie autem
  - dodać pola speed, maxSpeed, acceleration, itp. do Car, niech się liczy samo
  - np. za każdym checkiem klawisza (co ileś czasu) `if (speed < maxSpeed-acceleration) speed += acceleration`
  - podejrzanie proste, ale się zobaczy
- fizyka

### 4) Poziomy
- nawierzchnie? // Nawierzchnie to może po fizyce
- przeszkody, power upy
- start/meta

### 5) Przeciwnicy 

### 6) Tabela wyników

### 7) "Oprawa graficzna i dźwiękowa"