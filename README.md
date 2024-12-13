# Objektinis-programavimas-C++

## Paleidimas
Norint paleisti programą: reikia įdiegti `CMake`, tada paleisti `run.bat` failą. Atsiradusiame `debug` aplanke rasite `.exe` failą, kuris gali būti naudojamas programos įjungimui.

## Versijų istorija
- **v0.1**: Sukurta funkcija, apskaičiuojanti studentų galutinį pažymį iš namų darbų ir egzamino balų bei išvedanti rezultatą į komandinę eilutę.
- **v0.2**: Programa gali skaityti ir rašyti duomenis į failą. Implementuotas studentų skirstymas į *vargšiukus* ir *kietiakius*.
- **v0.3**: Naudotojas gali pasirinkti, kurį konteinerį naudoti: `vector` ar `list`.
- **v1.0**: Pridėta galimybė pasirinkti strategiją (vieną iš trijų) studentų skirstymui į grupes.
- **v1.1**: Sukurta klasė su konstruktoriais ir destruktoriais.
- **v1.2**: Realizuoti metodai pagal *„Rule of Three“*. Perdengti įvesties ir išvesties operatoriai.
- **v1.5**: Sukurta abstrakti klasė *Zmogus*. Jos objektų kūrimas nėra leidžiamas.
- **v2.0**: Įkelta HTML dokumentacija ir atlikti vienetų testai.

## Operatoriai
### Įvesties operatorius (`>>`)
- Gavus `cin`: prašoma įvesti vardą, pavardę, namų darbų pažymius ir egzamino balą (arba sugeneruojami atsitiktiniai pažymiai).
- Gavus ne `cin` (skaitymas iš failo): skaitomi vardas, pavardė, namų darbų pažymiai, o paskutinis balas laikomas egzamino įvertinimu.

### Išvesties operatorius (`<<`)
Atspausdina sulygiuotą tekstą į ekraną arba į failą su studento vardu, pavarde ir galutiniu balu.

## Vienetų testavimas
Testavimas atliktas naudojant `googletest` framework. Tikrinta:
- Galutinio pažymio skaičiavimas pagal vidurkį.
- Galutinio pažymio skaičiavimas pagal medianą.

![Galutinio pažymio testavimas](https://github.com/user-attachments/assets/83a5c450-802c-414f-9861-e7df17074548)

## Veikimo greičio analizė
Atlikti testai su 1 000, 10 000, 100 000, 1 000 000 ir 10 000 000 studentų. 

### Rezultatų santrauka
- **Vector konteineris**: geriausiai veikia su pirmąja strategija.
- **List konteineris**: greičiausiai veikia su antrąja strategija.
- Lyginant konteinerius: `list` yra greitesnis rūšiavimo užduotyse.

### Testavimo rezultatai
#### Studentų generavimas ir apdorojimas
| Studentų skaičius | Generavimas (s) | Nuskaitymas (s) | Rūšiavimas (s) | Išvedimas (s) |
|--------------------|-----------------|-----------------|----------------|---------------|
| 1 000             | 0.024          | 0.02           | 0.004          | 0.006         |
| 10 000            | 0.169          | 0.19           | 0.03           | 0.05          |
| 100 000           | 1.554          | 1.85           | 0.34           | 0.512         |
| 1 000 000         | 16.54          | 18.177         | 3.012          | 5.111         |
| 10 000 000        | 155.6          | 192.5          | 42.76          | 52.13         |

#### Veikimo greičio palyginimai
- **Struct vs Class**: 
![Struct vs Class palyginimas](https://github.com/user-attachments/assets/5080c894-b8bd-4dc7-9c3e-a410b7771c3c)

- **Strategijų efektyvumas pagal konteinerius**:
![Strategijų palyginimas](https://github.com/user-attachments/assets/2cea66a4-53ac-4798-a12e-001de0c68034)

### Testavimo sistemos specifikacijos
- **CPU**: Intel i5-12500H
- **RAM**: 16GB (2x8GB)
- **Diskas**: NVMe SSD, 500GB
