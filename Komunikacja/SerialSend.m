function results = SerialSend(Send)
    s=serial('COM4');
    fopen(s);
    fwrite(s,Send);
    fclose(s);
    clear s;
end