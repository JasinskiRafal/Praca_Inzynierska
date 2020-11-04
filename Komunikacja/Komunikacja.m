s = serial('COM3');

fopen(s);
fwrite(s,'a:0:3:500,');
TEST = fscanf(s,100);
fclose(s);
TEST = char(TEST);
