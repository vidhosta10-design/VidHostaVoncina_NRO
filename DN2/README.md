Najhitrejša metoda je griddedInterpolant. Razlog je v tem, da je mreža strukturirana, kar pomeni, da so vrednosti koordinat x in y razporejene na enakomernem pravokotnem gridu. MATLAB lahko zato pri uporabi griddedInterpolant izjemno hitro dostopa do pripadajočih elementov v matriki – gre za neposredno indeksiranje, ki je računsko zelo učinkovito.

Metoda scatteredInterpolant je počasnejša, ker mora MATLAB pred interpolacijo najprej izvesti triangulacijo nad vsemi razpršenimi točkami. Ta začetni korak je bistveno bolj zahteven od preprostega indeksiranja po mreži.

Moja lastna bilinearna interpolacija je prav tako razmeroma hitra, vendar moram pred izračunom vedno najti ustrezno celico, v kateri leži iskana točka. Prav ta dodatni postopek iskanja upočasni metodo, zaradi česar griddedInterpolant na koncu ostane najhitrejša rešitev.
