clear all;

podatki = importdata("naloga1_1.txt", ';');

t = podatki.data

podatki_P = fopen("naloga1_2.txt", 'r');

line = fgetl(podatki_P);

stevilke = sscanf(line, 'stevilo_podatkov_P: %d');

P = zeros(1, stevilke);

for i = 1:stevilke
    vrstica = fgetl(podatki_P);
    P(i) = str2double(vrstica);
end

fclose(podatki_P);

figure;
plot(t, P)

xlabel('t [s]');
ylabel('P [W]');
title('graf P(t)');

n = length(P);
integral = 0;

for i = 1:n-1
    dt = t(i+1) - t(i);
    integral = integral + (P(i) + P(i+1)) * dt/2;
end

integral_trapezna_metoda = trapz(t,P);

razlika = integral - integral_trapezna_metoda
