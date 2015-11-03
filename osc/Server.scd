s = Server.supernova.local;
s.options.hardwareBufferSize = 64;
s.options.threads = 4;
s.reboot;

~patric =  NetAddr.new("192.168.0.26", 6666);
~patric.sendMsg("/test",1.0);