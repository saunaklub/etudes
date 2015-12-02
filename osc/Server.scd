s = Server.supernova.local;
s.options.device = "Saffire"
s.options.hardwareBufferSize = 64;
s.options.threads = 4;
s.reboot;
s.plotTree

~patric =  NetAddr.new("192.168.0.26", 6666);
~patric =  NetAddr.new("192.168.0.11", 6666);
~patric.sendMsg("/test",1.5);
s.quit
