# Objektinis-progrmavimas-C-
Norint paleisti programą: reikia įdetgti cmake, tada paleisti run.bat failą ir atsiradusiame debug aplankale .exe failas yra galimas naudoti norit įjungti programą.

v0.1 Sukurta funkciją, kurį gaunant studentų pažymius, gali apskaičiavus jų galutini pažymį išvesti į komandinę eilutę.
v0.2 Programa išmoko skaityti ir išvestį į failą. Pradėjo dalinti studentus į vargšiukus ir kietiakius.
v0.3 Naudotojas gavo galimybę pasirinkti kokį konteinerį naudoti: vector ar list.
v1.0 Galima pasirinkti kokią strategiją (vieną iš trijų) naudoti, kad padalintume studentus į dų tipus.
v1.1 Sukurta Klase su konstruktoriais ir destruktoriumi
v1.2 Realizuoti metodai atitinkantis ,,Rule of three". Perdengti ivesties ir isvesties metodai.
v1.5 Padaryta abstrakti klasė Zmogus, jos objektų kūrimas negalimas.
v2.0 Įkelta html dokumentacija ir padarytį Unit testai.

įvesties operatorius ">>":
Gavus 'cin' - Klausia: vardą, pavardę, namų darbų pažymius ir egzamino pažymį. (Gali sugeneruoti atsitiktinius pažymius).
Gavus ne 'cin' (skaitymas iš failo) skaito: vardą, pavardę, namų darbų pažymius, o paskutinį pažymį priskiria prie egzamino įvertinimo.

Išvesties operatorius "<<":
Atspausdina sulygiota teksta arba į ekraną , arba į failą, kur yra studento vardas, pavardė ir galutinis balas.


Realizuotas Unit testas per googletest framework. Čia pavaizduoti kaip buvo tikrinta ar gerai skaičiuoja galutini balą per vidurkį ir per medianą.
![image](https://github.com/user-attachments/assets/83a5c450-802c-414f-9861-e7df17074548)


Atliktos programos veikimo greičio analizę su 1 000, 10 000, 100 000, 1 000 000, 10 000 000 studentu.
Iš greičio rezultatų matome, kad geriausia strategiją veikianti vector konteineriui yra 1.
Tuomet list konteineriui - 2.
Jei palygintume list ir vector konteinerius tai galima daryti išvada, kad  list yra greitesnis rūšiavime į grupes.
![image](https://github.com/user-attachments/assets/2cea66a4-53ac-4798-a12e-001de0c68034)

Taip pat palyginimo greitį tarp Struct ir Class: 
![image](https://github.com/user-attachments/assets/5080c894-b8bd-4dc7-9c3e-a410b7771c3c)
![image](https://github.com/user-attachments/assets/52b28d6f-3eee-44d1-8deb-9904a72839db)




Su 10 000 000 studentu:
Asitiktiniu kūrimas: 155.6
Nuskaitymas is failų: 192.5
Rūšiavimas į grupes: 42.76
Išvedimas į failus: 52.13

Su 1 000 000 studentu:
Asitiktiniu kūrimas: 16.54
Nuskaitymas is failų: 18.177
Rūšiavimas į grupes: 3.012
Išvedimas į failus: 5.111

Su 100 000 studentu:
Asitiktiniu kūrimas: 1.554
Nuskaitymas is failų: 1.85
Rūšiavimas į grupes: 0.34
Išvedimas į failus: 0.512

Su 10 000 studentu:
Asitiktiniu kūrimas: 0.169
Nuskaitymas is failų: 0.19
Rūšiavimas į grupes: 0.03
Išvedimas į failus: 0.05

Su 1 000 studentu:
Asitiktiniu kūrimas:0.024
Nuskaitymas is failų: 0.02
Rūšiavimas į grupes: 0.004
Išvedimas į failus: 0.006



Su list vietoje vector:

Su 1 000 studentu:
Nuskaitymas is failų: 0.02
Rūšiavimas į grupes: 0.0032
Išvedimas į failus: 0.012

Su 10 000 studentu:
Nuskaitymas is failų: 0.19
Rūšiavimas į grupes: 0.019
Išvedimas į failus: 0.0535

Su 100 000 studentu:
Nuskaitymas is failų: 1.92
Rūšiavimas į grupes: 0.36
Išvedimas į failus: 0.524

Su 1 000 000 studentu:
Nuskaitymas is failų: 19.177
Rūšiavimas į grupes: 2.964
Išvedimas į failus: 5.391

Su 10 000 000 studentu
Nuskaitymas is failų: 191.5
Rūšiavimas į grupes: 59.723
Išvedimas į failus: 59.04



Rusiavimas i du failus pagal 1 strategiją (List):
Su 1 000 studentų:
Rūšiavimas į grupes: 0.0018
Išvedimas į failus: 0.008

Su 10 000 studentų:
Rūšiavimas į grupes: 0.0496
Išvedimas į failus: 0.099

Su 100 000 studentų:
Rūšiavimas į grupes: 0.1077
Išvedimas į failus: 0.5301

Su 1 000 000 studentų:
Rūšiavimas į grupes: 0.9595
Išvedimas į failus: 4.7606

Su 10 000 000 studentų:
Rūšiavimas į grupes: 16.4492
Išvedimas į failus: 51.3006



Rusiavimas i du failus pagal 2 strategiją (List):
Su 1 000 studentų:
Rūšiavimas į grupes:0.0017
Išvedimas į failus: 0.0076

Su 10 000 studentų:
Rūšiavimas į grupes: 0.0103
Išvedimas į failus: 0.0528

Su 100 000 studentų:
Rūšiavimas į grupes:  0.3750
Išvedimas į failus: 3.8433

Su 1 000 000 studentų:
Rūšiavimas į grupes: 0.778
Išvedimas į failus: 4.8245

Su 10 000 000 studentų:
Rūšiavimas į grupes: 8.0032
Išvedimas į failus: 51.6910


Rusiavimas i du failus pagal 3 strategiją (List):
Su 1 000 studentų:
Rūšiavimas į grupes: 0.0055
Išvedimas į failus: 0.0343


Su 10 000 studentų:
Rūšiavimas į grupes: 0.0165
Išvedimas į failus: 0.0532

Su 100 000 studentų:
Rūšiavimas į grupes: 0.1511
Išvedimas į failus: 0.5671

Su 1 000 000 studentų:
Rūšiavimas į grupes: 1.3092
Išvedimas į failus: 4.7587

Su 10 000 000 studentų:
Rūšiavimas į grupes: 19.7546
Išvedimas į failus: 52.8525

Rusiavimas i du failus pagal 1 strategiją (Vector):
Su 1 000 studentų:
Rūšiavimas į grups: 0.014
Išvedimas į failus: 0.0398


Su 10 000 studentų:
Rūšiavimas į grupes: 0.0368
Išvedimas į failus: 0.0639

Su 100 000 studentų:
Rūšiavimas į grupes: 0.3477
Išvedimas į failus: 0.5191

Su 1 000 000 studentų:
Rūšiavimas į grupes: 3.2113
Išvedimas į failus: 4.5960

Su 10 000 000 studentų:
Rūšiavimas į grupes: 40.5429
Išvedimas į failus: 51.6977


Rusiavimas i du failus pagal 2 strategiją (Vector):
Su 1 000 studentų:
Rūšiavimas į grupes: 0.0623
Išvedimas į failus: 0.0061


Su 10 000 studentų:
Rūšiavimas į grupes: 5.6662
Išvedimas į failus: 0.0536

Su 100 000 studentų:
Rūšiavimas į grupes: 2147.6912
Išvedimas į failus: 3.4982

Su 1 000 000 studentų:
Rūšiavimas į grupes: ___
Išvedimas į failus: 4.5960

Su 10 000 000 studentų:
Rūšiavimas į grupes: ___
Išvedimas į failus: 51.6977


Rusiavimas i du failus pagal 3 strategiją (Vector):
Su 1 000 studentų:
Rūšiavimas į grupes: 0.0059
Išvedimas į failus: 0.0074


Su 10 000 studentų:
Rūšiavimas į grupes: 0.1626
Išvedimas į failus: 0.3381

Su 100 000 studentų:
Rūšiavimas į grupes: 0.3872
Išvedimas į failus: 0.5352

Su 1 000 000 studentų:
Rūšiavimas į grupes: 3.4898
Išvedimas į failus: 4.6951

Su 10 000 000 studentų:
Rūšiavimas į grupes: 54.0266
Išvedimas į failus: 51.6146

Testavimo sistemos specifikacijos:

CPU: i5 12500H
RAM: 8x2GB  16GB RAM 
NVME: 500gb
