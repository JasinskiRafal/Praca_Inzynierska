function [s,flag] = setupSerial(comPort)

flag = 1;
s = serial(comPort);
fopen(s);
pause(2);
a='b';
fwrite(s,'a,');
while(a~='a')
    a=fread(s,1,'uchar');
end
mbox = msgbox('Komunikacja nawi¹zana');
uiwait(mbox);
end
