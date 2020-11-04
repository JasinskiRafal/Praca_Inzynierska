function [Port] = AplikacjaPomoc()
            Tytul = 'Port';
            Wiadomosc = 'Podaj port COM arduino, np.: COM3';
            Port = inputdlg(Wiadomosc,Tytul);
            Port = char(Port);
end
